#include <threads.h>
#include <sys/sysinfo.h>

#include "../../struct/networks.h"
#include "../backpropagation.h"

char *dataset_path;
size_t *batches_already_done;

int trainNetworkTHREAD(void *data)
{
    struct Network *network = (struct Network *)data;

    printf("Training network '%c'\n", network->character);
    //Initializing neurones training parameters
    for (size_t l = 1; l < network->nb_layers; l++)
    {
        for (size_t n = 0; n < network->layers[l]->nb_neurones; n++)
        {
            if ((network->layers[l]->neurones[n]->delta_bias) != NULL && network->layers[l]->neurones[n]->delta_weight != NULL)
            {
                free(network->layers[l]->neurones[n]->delta_bias);
                free(network->layers[l]->neurones[n]->delta_weight);
            }
            network->layers[l]->neurones[n]->delta_bias = malloc(MINIBATCH_SIZE * sizeof(double));
            network->layers[l]->neurones[n]->delta_weight = malloc(network->layers[l - 1]->nb_neurones * MINIBATCH_SIZE * sizeof(double));
        }
    }

    // Create NB_MINIBATCH minibatches
    for (size_t b = 0; b < NB_MINIBATCH; b++)
    {
        char *datasetpath = NULL;
        double **inputs = NULL;
        double **expected_output = NULL;
        configure_batch_io(network, datasetpath, inputs, expected_output);

        printf("\rMINIBATCH:[%lu/%u]", b, NB_MINIBATCH);
        fflush(stdout);

        for (size_t i = 0; i < NB_TRAINING_PER_MINIBATCH; i++)
        {
            minibatch(network, inputs, expected_output);
        }

        // Free inputs & and expected ones
        for (size_t i = 0; i < MINIBATCH_SIZE; i++)
            free(inputs[i]);
        for (size_t i = 0; i < MINIBATCH_SIZE; i++)
            free(expected_output[i]);
        // dadim dam dam dadim dam dam dadadi dadadadi do dim dam dam
    }
    printf("\n");
    CalculateScore(network, dataset_path);

    return thrd_success;
}

int trainNetworksMULTITHREAD(struct Networks *networks, char *datasetpath)
{
    dataset_path = datasetpath;
    thrd_t threads[CHARSLEN];

    batches_already_done = calloc(CHARSLEN,sizeof(size_t));

    // Creation of 'available_cores' threads.
    for (int i = 0; i < CHARSLEN; i++)
    {
        if (thrd_create(&threads[i], trainNetworkTHREAD, networks->networks[i]) != thrd_success)
        {
            fprintf(stderr, "Threads creation failed for network n°%d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < CHARSLEN; i++)
    {
        int threadResultCode;
        if (thrd_join(threads[i], &threadResultCode) == thrd_error)
        {
            fprintf(stderr, "Impossible to wait to the thread '%d'\n", i);
            return EXIT_FAILURE;
        }
        if (threadResultCode != 0)
        {
            fprintf(stderr, "The thread '%d' ended with an error\n", i);
            return EXIT_FAILURE;

        }
    }

    free(batches_already_done);
    return 0;
}