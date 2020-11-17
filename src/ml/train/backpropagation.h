#ifndef BACKPROPAGATION
#define BACKPROPAGATION

#include <stdint.h>
#include <math.h>
#include "network.h"
#include "neurone.h"
#include "../matrix/matrix.h"
#include "../image/binarization.h"
#include "../math/analysis.h"

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
void trainingNetwork(struct Network network, char* databasepath, size_t minibatchsize, size_t minibatchnumber, size_t minibatchtrain);

/**
 * @brief Train the network to reconize letters. Inputs are 128x128 images
 * 
 * @param network The network to work with.
 * @param minibatchinputs The list of matrix of images.
 * @param targets The list of index of letters according to minibatchinputs.
 * @param nbimages The number of images of batch.
 * @return Return a array of the inputs.
 */
void minibatch(struct Network network, struct MatrixUCHAR* minibatchinputs, size_t* targets, size_t nbimages);

/**
 * @brief Sets the delta_bias and delta_weights of eavery neurones
 * 
 * @param network The network to work with.
 */
void backpropagation(struct Network network);

/**
 * @brief Gives the array of the inputs.
 * 
 * @param imgmat The matrix of the image to work with.
 * @param numberofneurones The number of neurones of the neural network we are working on.
 * @return Return a array of the inputs.
 */
double* loadmatrixasinputs(struct MatrixUCHAR imgmat, int numberofneurones);

struct MatrixUCHAR loadDataBase(char* databasepath, char letter, size_t imagenumber);

#endif