#ifndef BACKPROPAGATION
#define BACKPROPAGATION

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "loadmnist.h"
#include "../struct/network.h"
#include "../struct/networks.h"
#include "../struct/neurone.h"
#include "../../matrix/matrix.h"
#include "../../image/binarization.h"
#include "../../math/analysis.h"
#include "../../miscellaneous/color.h"


#define LEARNINGRATE 0.01
#define MINIBATCH_SIZE 30
#define NB_TRAINING_PER_MINIBATCH 10000
#define NB_MINIBATCH 4
#define NB_INPUTS 32*32

/**
 * @brief Train the network to reconize letters. Inputs are 128x128 images
 * 
 * @param network The network to work with.
 * @param databasepath The path to the data base.
 * @param minibatchsize The size of mini batch.
 * @param minibatchnumber The number of the batch.
 * @param minibatchtrain The number of train of batch.
 * @return Return a array of the inputs.
 */
void configure_batch_io(struct Network *network, char *datasetpath, char **inputs, double **expected_output);

void trainNetworks(struct Networks *networks, char *datasetpath);

void trainNetwork(struct Network *network, char *datasetpath);

/**
 * @brief Train the network to reconize letters. Inputs are 128x128 images
 * 
 * @param network The network to work with.
 * @param minibatchinputs The list of matrix of images.
 * @param targets The list of index of letters according to minibatchinputs.
 * @param nbimages The number of images of batch.
 * @return Return a array of the inputs.
 */
void minibatch(struct Network *network, char **inputs, double **expected_output);

/**
 * @brief Sets the delta_bias and delta_weights of eavery neurones
 * 
 * @param network The network to work with.
 * @param expected_output Vector containg expected output values
 * len(expected_output) = len(network.output)
 */
void backpropagation(struct Network *network, double *expected_output);

/**
 * @brief Gives the array of the inputs.
 * 
 * @param imgmat The matrix of the image to work with.
 * @param numberofneurones The number of neurones of the neural network we are working on.
 * @return Return a array of the inputs.
 */
double* loadmatrixasinputs(struct MatrixDOUBLE *imgmat, int numberofneurones);

void CalculateScore(struct Network *network, char *databasepath);

char *loadDataBase(char *databasepath, char letter, size_t imagenumber);

void PrintInput(double *input, size_t height, size_t with, char letter);

void PrintOuput(double *output, char letter, char network_character);

#endif