#include "loadmnist.h"

double train_image[NUM_TRAIN][SIZE];
double test_image[NUM_TEST][SIZE];


int  train_label[NUM_TRAIN];
int test_label[NUM_TEST];

double *LoasMNIST(char* databasepath)
{
    fopen(databasepath, "rb");
}