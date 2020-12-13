#include <threads.h>
#include <stdio.h>

#include "backpropagation.h"
#include "../../math/analysis.h"

char *dataset_path;
size_t *batches_already_done;
size_t *batches_how_many;

mtx_t mutex;
int isStopped;

void configure_batch_io(struct Network *network, char *datasetpath, char **inputs, double **expected_output)
{
    for (size_t i = 0; i < MINIBATCH_SIZE; i++)
    {
        // Define one minibatch size to MINIBATCH_SIZE
        expected_output[i] = calloc(networkNbOutput(network), sizeof(double)); // expected_output[i] -> Target vector : (1 0 0 0 1 0 0 1 0 0 0)
        /* 
                    /!\ 
                    Implementation for charcters only
                */
        char letter = CHARS[rand() % CHARSLEN];
        if (rand() % 100 < 45)
        {
            letter = network->character;
        }

        // Check if the random letter is the one managed by the network
        if (letter == network->character)
            expected_output[i][0] = 1;

        inputs[i] = loadDataBase(datasetpath, letter, (rand() % 1000) + 1);
    }
}

void CalculateScores(struct Networks *networks, char *databasepath)
{
    double average_percentage = 0;
    for (size_t i = 0; i < networks->nb_networks; i++)
    {
        average_percentage += CalculateScore(networks->networks[i], databasepath);
    }

    average_percentage /= networks->nb_networks;

    printf("\n\nGlobal accuracy : %s%f%s\n", BLU, average_percentage, RST);
}

double CalculateScore(struct Network *network, char *databasepath)
{
    printf("SCORE : network '%c'\n", network->character);
    int number_of_test = 1000;
    int nb_success = 0;

    double cost_average = 0;
    for (int i = 0; i < number_of_test; i++)
    {
        char letter = CHARS[rand() % CHARSLEN];
        if (i < number_of_test / 2)
            letter = network->character;

        // Dataset loading
        char *inputs = loadDataBase(databasepath, letter, (rand() % 1000) + 1);

        // Feedforward
        double *outputs = calculateNetworkOutput(network, inputs);

        if (letter == network->character)
        {
            if (*outputs > 0.8)
                nb_success += 1;
        }
        else
        {
            if (*outputs < 0.5)
                nb_success += 1;
        }

        cost_average += cost(network, letter == network->character ? 0 : 45615);

        free(outputs);
        free(inputs);
    }

    cost_average /= number_of_test;
    float percentage_of_success = ((100 * nb_success) / number_of_test);
    char *color;

    if (percentage_of_success > 90)
        color = GRN;

    else if (percentage_of_success > 50)
        color = YEL;
    else
        color = RED;

    printf("\nCOST : %f\n", cost_average);
    printf("PERCENTAGE : %s%f%%%s. [%d/%d]\n", color, percentage_of_success, RST, nb_success, number_of_test);

    return percentage_of_success;
}

void MinibatchesStates(size_t batches_already_done[], size_t batches_how_many[])
{
    double average_percentage = 0;

    for (size_t i = 0; i < CHARSLEN; i++)
    {
        printf("MINIBACH for network '%c' : %ld/%d\n", CHARS[i], batches_already_done[i], NB_MINIBATCH);
        printf("\t↳[");

        double percent = (batches_how_many[i] / (double)NB_TRAINING_PER_MINIBATCH) * 100;
        average_percentage += percent;

        for (size_t j = 0; j < percent; j++)
        {
            printf("%s█%s", GRN, RST);
        }
        for (size_t j = percent; j < 100; j++)
        {
            printf(" ");
        }
        printf("] %f%%\n", percent);
    }
    average_percentage /= (double)NB_TRAINING_PER_MINIBATCH;
    printf("\nOverall progress\n");
    printf("[");
    for (size_t j = 0; j < average_percentage; j++)
    {
        printf("%s█%s", BLU, RST);
    }
    for (size_t j = average_percentage; j < 100; j++)
    {
        printf(" ");
    }
    printf("] %f%%\n", average_percentage);
}

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
        char **inputs = malloc(MINIBATCH_SIZE * sizeof(char *));
        double **expected_output = malloc(MINIBATCH_SIZE * sizeof(double *));
        configure_batch_io(network, dataset_path, inputs, expected_output);
        for (size_t i = 0; i < NB_TRAINING_PER_MINIBATCH; i++)
        {
            while (isStopped == 1)
            {
                mtx_lock(&mutex);
            }
            mtx_unlock(&mutex);

            batches_how_many[bpt->minibatch_list_index] = i;
            minibatch(network, inputs, expected_output);
        }

        // Free inputs & and expected ones
        for (size_t i = 0; i < MINIBATCH_SIZE; i++)
            free(inputs[i]);
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
    dataset_path = datasetpath;
    thrd_t threads[CHARSLEN];

    batches_already_done = calloc(CHARSLEN, sizeof(size_t));
    batches_how_many = calloc(CHARSLEN, sizeof(size_t));

    // Creation of 'available_cores' threads.
    printf("Training networks [a-zA-Z0-9]\n");
    struct _BackpropagTHREAD *backpropTHREAD = malloc(sizeof(struct _BackpropagTHREAD) * CHARSLEN);
    for (int i = 0; i < CHARSLEN; i++)
    {
        printf("Training started for network '%c'\n", networks->networks[i]->character);

        backpropTHREAD[i].net = networks->networks[i];
        backpropTHREAD[i].minibatch_list_index = i;

        if (thrd_create(&threads[i], trainNetworkTHREAD, &backpropTHREAD[i]) != thrd_success)
        {
            fprintf(stderr, "Threads creation failed for network n°%d\n", i);
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
            CalculateScores(networks, dataset_path);
            isStopped = 0;
            mtx_unlock(&mutex);
        }
        else
        {
            MinibatchesStates(batches_already_done, batches_how_many);
        }
    }

    CalculateScores(networks, dataset_path);

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

                neurone->weights[k] -= (LEARNINGRATE) * (sumweights / MINIBATCH_SIZE);
            }

            double sum_delta_bias = 0;
            for (size_t i = 0; i < MINIBATCH_SIZE; i++)
            {
                sum_delta_bias += neurone->delta_bias[i];
            }
            neurone->bias -= (LEARNINGRATE) * (sum_delta_bias / MINIBATCH_SIZE);
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
                // neurones[j] -> change | weights[i] don't change
                sum += network->layers[l + 1]->neurones[j]->delta_error * network->layers[l + 1]->neurones[j]->weights[i];
            }
            network->layers[l]->neurones[i]->delta_error = sum * actvation_fonction_derivate(network->layers[l]->neurones[i]);
        }
    }
}

char *loadDataBase(char *databasepath, char letter, size_t imagenumber)
{
    //Convert a imagenumber to a "12345" string
    char *imagename = malloc(6 * sizeof(char));
    imagename[5] = 0;
    for (size_t i = 5; i > 0; i--)
    {
        imagename[i - 1] = '0' + imagenumber % 10;
        imagenumber /= 10;
    }

    //Build the image path string
    char *imagepath = malloc((strlen(databasepath) + 150) * sizeof(char));
    sprintf(imagepath, "%s/%02x/train_%02x/train_%02x_%s.png", databasepath, letter, letter, letter, imagename);

    //Load image
    SDL_Surface *image = loadImage(imagepath);
    free(imagepath);
    free(imagename);

    char *imagebin = binarizationpointer(image, 128 / sqrt(NB_INPUTS));
    SDL_FreeSurface(image);
    return imagebin;
}

void PrintInput(double *input, size_t height, size_t with, char letter)
{
    printf("Input for %c:\n", letter);
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < with; j++)
        {
            if (*(input + i * with + j) > 0.5)
                printf("%i", 1);
            else
                printf(" ");
        }
        printf("|\n");
    }
}

void PrintOuput(double *output, char letter, char network_character)
{
    char *color = RED;
    if (letter == network_character)
    {
        if (*output > 0.8)
            color = YEL;
    }
    else if (*output < 0.5)
        color = GRN;

    printf(" ");
    printf("%s%c=%f%s", color, letter, *output, RST);
    printf(" |");
}