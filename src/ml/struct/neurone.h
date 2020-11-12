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
 * @return struct Neurone
 */
struct Neurone CreateNeurone(double weights[],double bias, unsigned char activationFunction, int nb_input);

/**
 * @brief Calculate a neurone output.
 * 
 * @param neurone The neurone to work with.
 * @param input The input to give to the neurone.
 * @return The result of the calculus as a double. 
 */
double calculateNeuroneOutput(struct Neurone neurone,double input[]);

double threshold(double x);

double sigmoid(double x);

double relu(double x);

double smooth_relu(double x);
#endif