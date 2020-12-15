#include <threads.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../backpropagation.h"
#include "../../../math/analysis.h"

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

char **imageForLearningRate;
struct Networks *networksRef;

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
        if (rand() % 100 < 10)
        {
            letter = network->character;
        }

        // Check if the random letter is the one managed by the network
        if (letter == network->character)
            expected_output[i][0] = 1;

        inputs[i] = loadDataBase(datasetpath, letter, (rand() % 1000));
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
        char *inputs = loadDataBase(databasepath, letter, (rand() % 1000));

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

    printf("COST : %f\n", cost_average);
    printf("PERCENTAGE : %s%f%%%s. [%d/%d]\n\n", color, percentage_of_success, RST, nb_success, number_of_test);

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

        average_percentage += NB_TRAINING_PER_MINIBATCH * (batches_already_done[i]);
        if (batches_already_done[i] < NB_MINIBATCH)
            average_percentage += batches_how_many[i];

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
    average_percentage /= (double)(NB_MINIBATCH * CHARSLEN * NB_TRAINING_PER_MINIBATCH);
    average_percentage *= 100;

    if (average_percentage > 100)
        average_percentage = 100;

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