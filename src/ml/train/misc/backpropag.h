#include <threads.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../backpropagation.h"
#include "../../../math/analysis.h"

void PrintInput(double *input, size_t height, size_t with, char letter);

void PrintOuput(double *output, char letter, char network_character);

char **imageForLearningRate;
struct Networks *networksRef;

char *dataset_path;
size_t *batches_already_done;
size_t *batches_how_many;

mtx_t mutex;
int isStopped;

void configure_batch_io(struct Network *network, char *datasetpath, char **inputs, double **expected_output);

void CalculateScores(struct Networks *networks, char *databasepath);

double CalculateScore(struct Network *network, char *databasepath);

void MinibatchesStates(size_t batches_already_done[], size_t batches_how_many[]);