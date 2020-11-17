#ifndef BACKPROPAGATION
#define BACKPROPAGATION

#include <stdint.h>
#include <math.h>
#include "network.h"
#include "neurone.h"
#include "../matrix/matrix.h"
#include "../image/binarization.h"
#include "../math/analysis.h"

void trainingNetwork(struct Network network, double learningrate, char* databasepath, size_t imagesbyletters, size_t trainnumber);

void backpropagation(struct Network network, double learningrate, struct MatrixUCHAR imagematrice, size_t nb_outputTarget, double *outputTarget
, double *delta_bias, double delta_weight[][][]);

/**
 * @brief Gives the array of the inputs.
 * 
 * @param imgmat The matrix of the image to work with.
 * @param numberofneurones The number of neurones of the neural network we are working on.
 * @return Return a array of the inputs.
 */
double* loadmatrixasinputs(struct MatrixUCHAR imgmat, int numberofneurones);


struct MatrixUCHAR loadDataBase(char* databasepath, char letter, size_t imagenumber);

/**
 * @brief Gives the cost of a network with inputs and a target.
 * 
 * @param network The network to work with.
 * @param intput The inputs to work with.
 * @param nb_input The number of inputs.
 * @param outputTarget The ouput we want.
 * @param nb_outputTarget The number of outputTarget.
 * @return The cost.
 */
double cost(struct Network network, double *intput, size_t nb_input, double *outputTarget, size_t nb_outputTarget);

#endif