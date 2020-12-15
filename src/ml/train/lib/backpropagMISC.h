#include <threads.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>


#include "../backpropagation.h"
#include "../../../math/analysis.h"

char **imageForLearningRate;
struct Networks *networksRef;
char ***all_images_inputs;

struct Folders *datset_folders;
size_t *batches_already_done;
size_t *batches_how_many;

mtx_t mutex;
int isStopped;

void PrintInput(double *input, size_t height, size_t with, char letter);

void PrintOuput(double *output, char letter, char network_character);

void configure_batch_io(struct Network *network, struct Folders *dataset, char **inputs, double **expected_output);

void CalculateScores(struct Networks *networks);

double CalculateScore(struct Network *network);

void MinibatchesStates(size_t batches_already_done[], size_t batches_how_many[]);

void loadDATASET(struct Folders *folders, char *dataset_path);

void freeDATASET(struct Folders *dataset);