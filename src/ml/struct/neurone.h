#ifndef NEURONE
#define NEURONE

#include <stdio.h>

/**
 * @brief ML neurone
 * 
 */
struct Neurone {
    //  ◯
    //  | nextNeuroneSameLayer
    //  ◯
    //  | nextNeuroneSameLayer
    //  ◯
    //  | nextNeuroneSameLayer
    //  ◯ 
    //  |
    // NULL
    //  

    /**
     * @brief Point to the next 
     * bottom neurone of a same layer.
     */
    struct Neurone *nextNeuroneSameLayer;
    
    /**
     * @brief The number of input the neurone can handle.
     * 
     */
    size_t nb_inputs;

    /**
     * @brief The bias of the neurone
     * 
     */
    double bias;

    // Pointer
    //     v
    //  | |w0|w1|w2|w3|...|wn| | 
    /**
     * @brief List of weights of the neurone (=nb of entries)
     * 
     */
    double *weights;

    // List of implemented functions :
    // 0 -> No activation function
    // 1 -> Threashold
    // 2 -> Sigmoïd
    // 3 -> ReLU
    // 4 -> Smooth ReLU

    /**
     * @brief The activation function
     * 
     * 0 -> No activation function,
     * 1 -> Threashold,
     * 2 -> Sigmoïd,
     * 3 -> ReLU,
     * 4 -> Smooth ReLU
     */
    unsigned char activationFunction;

    /**
     * @brief ouput = activationFunction(outputWithoutActivation)
     * (Just for training)
     */
    double outputWithoutActivation;

    /**
     * @brief Delta error of the neurone to reach the target value.
     * (Just for training)
     */
    double delta_error;

    /**
     * @brief Delta error of the bias to reach the target value.
     * (Just for training)
     */
    double* delta_bias;

    /**
     * @brief Delta error of the weights to reach the target value.
     * (Just for training)
     */
    double* delta_weight;
};

/**
 * @brief Create a Neurone object.
 * 
 * @param weights Configured weights.
 * @param bias Configured bias.
 * @param activationFunction An activation function.
 *  0 -> No activation function,
    1 -> Threashold,
    2 -> Sigmoïd,
    3 -> ReLU,
    4 -> Smooth ReLU
 * @param nb_input The number of input
 *  the neurone can handle.
 * @param nbtrainimages The number of images to train. Default 0 if not training
 * @return struct Neurone
 */
struct Neurone CreateNeurone(double weights[],double bias, unsigned char activationFunction, size_t nb_input);


void FreshNeuroneForTraining(struct Neurone *neurone, size_t nblastLayer ,size_t nbtrainimages);

/**
 * @brief Free the neurone.
 * 
 * @param neurone The neurone to work with.
 */
void FreeNeurone(struct Neurone *neurone);

/**
 * @brief Calculate a neurone output.
 * 
 * @param neurone The neurone to work with.
 * @param input The input to give to the neurone.
 * @return The result of the calculus as a double. 
 */
double calculateNeuroneOutput(struct Neurone *neurone,double input[]);

/**
 * @brief Apply the activation function with the last output without activation. 
 * (Use calculateNeuroneOutput to get with a custom value)
 * 
 * @param neurone The neurone to work with.
 * @return The neurone activation. 
 */
double activationFunction(struct Neurone *neurone);

double threshold(double x);

double sigmoid(double x);

double sigmoid_derivate(double x);

double relu(double x);

double smooth_relu_derivate(double x);

double smooth_relu(double x);

double actvation_fonction_derivate(struct Neurone* neurone);

void PrintLayerOutput(struct Neurone *neurone);
#endif