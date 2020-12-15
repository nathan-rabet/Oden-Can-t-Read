#include "lib/backpropagMISC.h"
#include "backpropagation.h"
#include "lib/datasetFILES.h"

int trainNetworkTHREAD(void *data)
{
    struct _BackpropagTHREAD *bpt = (struct _BackpropagTHREAD *)data;
    struct Network *network = bpt->net;

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
        double **expected_output = malloc(MINIBATCH_SIZE * sizeof(double *));
        char **inputs = malloc(MINIBATCH_SIZE * sizeof(double *));
        configure_batch_io(network, datset_folders, inputs, expected_output);
        for (size_t i = 0; i < NB_TRAINING_PER_MINIBATCH; i++)
        {
            while (isStopped == 1)
            {
                thrd_sleep(&(struct timespec){.tv_nsec = 100000000}, NULL);
            }

            batches_how_many[bpt->minibatch_list_index] = i;
            minibatch(network, inputs, expected_output);
        }

        // Saving networks automaticaly
        isStopped = 1;
        char *c = malloc(sizeof(char) * 100);

        struct stat st = {0};

        if (stat("data/networks/~training/", &st) == -1)
        {
            mkdir("data/networks/~training/", 0700);
        }

        sprintf(c, "data/networks/~training/network_%d.json", (int)time(NULL));
        SaveNetworksToJSON(networksRef, c);
        free(c);
        isStopped = 0;

        for (size_t i = 0; i < MINIBATCH_SIZE; i++)
            free(expected_output[i]);
        // dadim dam dam dadim dam dam dadadi dadadadi do dim dam dam
        batches_already_done[bpt->minibatch_list_index] += 1;
    }
    return thrd_success;
}

int trainNetworks(struct Networks *networks, char *datasetpath)
{
    mtx_init(&mutex, mtx_plain);
    datset_folders = malloc(sizeof(struct Folders));

    loadDATASET(datset_folders, datasetpath);
    networksRef = networks;
    thrd_t threads[CHARSLEN];

    batches_already_done = calloc(CHARSLEN, sizeof(size_t));
    batches_how_many = calloc(CHARSLEN, sizeof(size_t));

    // Creation of 'available_cores' threads.
    printf("Training networks [a-z0-9]\n");
    struct _BackpropagTHREAD *backpropTHREAD = malloc(sizeof(struct _BackpropagTHREAD) * CHARSLEN);
    for (size_t i = 0; i < networks->nb_networks; i++)
    {
        printf("Training started for network '%s'\n", networks->networks[i]->characters);
        backpropTHREAD[i].net = networks->networks[i];
        backpropTHREAD[i].minibatch_list_index = i;

        if (thrd_create(&threads[i], trainNetworkTHREAD, &backpropTHREAD[i]) != thrd_success)
        {
            fprintf(stderr, "Threads creation failed for network n°%ld\n", i);
            return 1;
        }
    }

    int canExit = 0;
    while (!canExit)
    {
        canExit = 1;
        for (int i = 0; i < CHARSLEN; i++)
        {
            if (batches_already_done[i] < NB_MINIBATCH)
            {
                canExit = 0;
                break;
            }
        }

        char ch;
        scanf("%c", &ch);

        system("clear");

        if (ch == 't')
        {
            isStopped = 1;
            CalculateScores(networks);
            isStopped = 0;
        }

        else if (ch == 's')
        {
            isStopped = 1;
            char *c = malloc(sizeof(char) * 100);

            struct stat st = {0};

            if (stat("data/networks/~training/", &st) == -1)
            {
                mkdir("data/networks/~training/", 0700);
            }

            sprintf(c, "data/networks/~training/network_%d.json", (int)time(NULL));
            SaveNetworksToJSON(networks, c);
            printf("Networks saved at '%s'\n", c);
            free(c);
            isStopped = 0;
        }

        else
        {
            MinibatchesStates(batches_already_done, batches_how_many);
        }

        thrd_sleep(&(struct timespec){.tv_sec = 5}, NULL);
    }

    CalculateScores(networks);

    free(batches_already_done);
    return 0;
}

void minibatch(struct Network *network, char **inputs, double **expected_output)
{
    for (size_t i = 0; i < MINIBATCH_SIZE; i++)
    {
        // Define minibatch
        char *input = inputs[i];

        // Feedforward (run the network with input to set the z and activation values)
        double *output = calculateNetworkOutput(network, input);
        free(output);

        // Backpropagate the error
        backpropagation(network, expected_output[i]);

        // Set ∂cost
        for (size_t l = 1; l < network->nb_layers; l++)
        {
            for (size_t n = 0; n < network->layers[l]->nb_neurones; n++)
            {
                struct Neurone *neurone = (network->layers[l]->neurones[n]);

                // ∂cost/∂b_i = δl_i
                neurone->delta_bias[i] = neurone->delta_error;

                for (size_t k = 0; k < network->layers[l - 1]->nb_neurones; k++)
                {
                    // ∂cost/∂w_ij = a_j * δl_i
                    // i : image i
                    // k : data of the image i
                    neurone->delta_weight[k * MINIBATCH_SIZE + i] = activationFunction((network->layers[l - 1]->neurones[k])) * neurone->delta_error;
                }
            }
        }
    }
    double LEARNINGRATE = 0.01;

    // Update ∂bias and ∂weight
    for (size_t l = 1; l < network->nb_layers; l++)
    {
        for (size_t n = 0; n < network->layers[l]->nb_neurones; n++)
        {
            struct Neurone *neurone = (network->layers[l]->neurones[n]);

            for (size_t k = 0; k < network->layers[l]->neurones[0]->nb_inputs; k++)
            {
                double sumweights = 0;

                for (size_t i = 0; i < MINIBATCH_SIZE; i++)
                {

                    sumweights += neurone->delta_weight[k * MINIBATCH_SIZE + i];
                }

                neurone->weights[k] -= LEARNINGRATE * (sumweights / MINIBATCH_SIZE);
            }

            double sum_delta_bias = 0;
            for (size_t i = 0; i < MINIBATCH_SIZE; i++)
            {
                sum_delta_bias += neurone->delta_bias[i];
            }
            neurone->bias -= LEARNINGRATE * (sum_delta_bias / MINIBATCH_SIZE);
        }
    }
}

void backpropagation(struct Network *network, double *expected_output)
{
    // δL = cost'(a) * actvation_fonction'(z)
    for (size_t k = 0; k < networkNbOutput(network); k++)
    {
        struct Neurone *nk = (network->layers[network->nb_layers - 1]->neurones[k]);
        nk->delta_error = cost_derivate(network, expected_output) * actvation_fonction_derivate(nk);
    }

    // δl_i = actvation_fonction'(z) * ∑(w_ji * δ_j)
    //                               j
    // l=L−1,L−2,…,2

    //        *  *                         *  *
    //     *        *         00        *        *
    //    *    i0    *    --------->   *    j0    *
    //    *          *                 *          *
    //     *        *    \              *        *
    //        *  *         \ 10            *  *        | δl_i = actvation_fonction'(z) * ∑(w_ji * δ_j)
    //                       \                         |                                 j
    //        *  *             \           *  *        | l=L−1,L−2,…,2
    //     *        *            \      *        *
    //    *    i1    *             \   *    j1    *
    //    *          *              -- *          *
    //     *        *                   *        *
    //        *  *                         *  *

    for (size_t l = network->nb_layers - 2; l > 0; l--)
    {
        for (size_t i = 0; i < network->layers[l]->nb_neurones; i++)
        {
            double sum = 0;
            for (size_t j = 0; j < network->layers[l + 1]->nb_neurones; j++)
            {
                while (isStopped == 1)
                {
                    thrd_sleep(&(struct timespec){.tv_nsec = 100000000}, NULL);
                }

                // neurones[j] -> change | weights[i] don't change
                sum += network->layers[l + 1]->neurones[j]->delta_error * network->layers[l + 1]->neurones[j]->weights[i];
            }
            network->layers[l]->neurones[i]->delta_error = sum * actvation_fonction_derivate(network->layers[l]->neurones[i]);
        }
    }
}

char *loadDATASET_Image(char *databasepath, char letter, size_t imagenumber)
{
    //Convert a imagenumber to a "12345" string
    char *foldername = malloc(4 * sizeof(char));
    foldername[3] = 0;
    for (size_t i = 3; i > 0; i--)
    {
        foldername[i - 1] = '0' + letter % 10;
        letter /= 10;
    }

    //Build the image path string
    char *imagepath = malloc((strlen(databasepath) + 150) * sizeof(char));
    sprintf(imagepath, "%s/%s/%lu.bmp", databasepath, foldername, imagenumber);

    //Load image
    SDL_Surface *image = loadImage(imagepath);
    free(imagepath);
    free(foldername);

    char *imagebin = binarizationpointer(image, 2);
    SDL_FreeSurface(image);
    return imagebin;
}