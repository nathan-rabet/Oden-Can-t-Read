#include "backpropagMISC.h"
#include "datasetFILES.h"
#include "src/miscellaneous/CHARS.h"

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

/*void PrintOuput(double *output, char letter, char network_character)
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
}*/

void loadDATASET(struct Folders *folders, char *dataset_path)
{
    folders = malloc(sizeof(struct Folders));
    folders->path = dataset_path;

    folders->folderLIST = malloc(sizeof(struct Folder) * CHARSLEN);
    for (size_t dir = 0; dir < CHARSLEN; dir++)
    {
        struct Folder *folder = &folders->folderLIST[dir];
        folder->char_id = CHARS[dir];

        int file_count = 0;
        DIR *dirp;
        struct dirent *entry;

        sprintf(folder->path, "%s/%03d", dataset_path, CHARS[dir]);

        dirp = opendir(dataset_path); /* There should be error handling after this */
        while ((entry = readdir(dirp)) != NULL)
        {
            if (entry->d_type == DT_REG)
            { /* If the entry is a regular file */
                file_count++;
            }
        }

        free(entry);
        closedir(dirp);

        folder->fileLIST = malloc(sizeof(char *) * file_count);
        for (size_t f = 0; f < file_count; f++)
        {
            struct File *file = &folder->fileLIST[f];

            file->file_index = f;

            sprintf(file->path, "%s/%03d", folder->path, f);

            file->data = loadDATASET_Image(folders->path, folder->char_id, file->file_index);
        }
    }
}

void freeDATASET(struct Folders *dataset)
{
    for (size_t folder = 0; folder < dataset->nb_folder; folder++)
    {
        for (size_t file = 0; file < dataset->folderLIST[folder].nb_files; file++)
        {
            free(dataset->folderLIST[folder].fileLIST[file].data);
            free(dataset->folderLIST[folder].fileLIST[file].path);
            free(&dataset->folderLIST[folder].fileLIST[file]);
        }

        free(dataset->folderLIST[folder].path);
        free(dataset->folderLIST[folder].fileLIST);
        free(&dataset->folderLIST[folder]);
    }

    free(dataset->path);
    free(dataset->folderLIST);
    free(dataset);
}



void configure_batch_io(struct Network *network, struct Folders *dataset, char **inputs, double **expected_output)
{
    for (size_t i = 0; i < MINIBATCH_SIZE; i++)
    {
        // Define one minibatch size to MINIBATCH_SIZE
        expected_output[i] = calloc(networkNbOutput(network), sizeof(double)); // expected_output[i] -> Target vector : (0 0 0 0 1 0 0 0 0 0)
        /* 
            /!\ 
           Implementation for charcters only
        */
        char letter_id_in_CHARS = rand() % CHARSLEN;
        if (rand() % 100 < 10)
        {
            letter_id_in_CHARS = find_char_id(network->characters[0], CHARS);
        }

        // Check if the random letter is one managed by the network
        if (letter_id_in_CHARS == network->characters[0])
            expected_output[i][find_char_id(CHARS[letter_id_in_CHARS],network->characters)] = 1;

        char folder_name = dataset->folderLIST[CHARS[letter_id_in_CHARS]].char_id;
        inputs[i] = dataset->folderLIST[folder_name].fileLIST[rand() % dataset->folderLIST[folder_name].nb_files].data;
    }
}

void CalculateScores(struct Networks *networks)
{
    double average_percentage = 0;
    for (size_t i = 0; i < networks->nb_networks; i++)
    {
        average_percentage += CalculateScore(networks->networks[i]);
    }

    average_percentage /= networks->nb_networks;

    printf("\n\nGlobal accuracy : %s%f%s\n", BLU, average_percentage, RST);
}

double CalculateScore(struct Network *network)
{
    printf("SCORE : network '%s'\n", network->characters);
    int number_of_test = 1000;
    int nb_success = 0;

    double cost_average = 0;
    for (int i = 0; i < number_of_test; i++)
    {
        char letter = CHARS[rand() % CHARSLEN];
        if (i < number_of_test / 2)
            letter = network->characters[rand() % networkNbOutput(network)];

        // Dataset loading
        char *inputs = loadDATASET_Image(datset_folders->path, letter, (rand() % 1000));

        // Feedforward
        double *outputs = calculateNetworkOutput(network, inputs);

        int isIn = 0;
        double maxOutput = 0;
        for (size_t c = 0; c < networkNbOutput(network); c++)
        {
            if (network->characters == c)
                isIn = 1;
            
            if ()
        }
        

        if (isIn)
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