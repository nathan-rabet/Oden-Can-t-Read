#include "neurone.h"
#include <math.h>
#include <stdlib.h>

// If no activation function, set activationFunction to 0
struct Neurone CreateNeurone(double weights[],double bias, unsigned char activationFunction, size_t nb_input, size_t nbtrainimages) {
    struct Neurone neurone;
    neurone.weights = malloc(sizeof(double) * nb_input);
    neurone.weights = weights;
    neurone.nb_inputs = nb_input;
    neurone.bias = bias;
    neurone.activationFunction = activationFunction;
    neurone.nextNeuroneSameLayer = NULL;
    neurone.outputWithoutActivation = 0;
    neurone.delta_error = 0;
    if (nbtrainimages > 0)
    {
        neurone.delta_bias = malloc(nbtrainimages * sizeof(double));
        neurone.delta_weight = malloc(20000 * nbtrainimages * sizeof(double));
    }
    return neurone;
}

double threshold(double x) {
    if (x <= 0) {
        return 0;
    }
    return 1;
}

double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double sigmoid_derivate(double x) {
    return exp(-x)/pow((1+exp(-x)), 2);
}

double relu(double x) {
    return fmax(0,x);
}

double smooth_relu(double x) {
    return log(1 + exp(x));
}

double calculateNeuroneOutput(struct Neurone neurone, double input[]) {
        neurone.outputWithoutActivation = 0;

        for (size_t i = 0; i < neurone.nb_inputs; i++)
        {
            double w = neurone.weights[i];
            double in = input[i];
            neurone.outputWithoutActivation += w * in;
        }

        neurone.outputWithoutActivation += neurone.bias;

        return activationFunction(neurone);
}

double activationFunction(struct Neurone neurone)
{
        // Activation functions
        switch (neurone.activationFunction)
        {
        // Identity
        case 0:
            return neurone.outputWithoutActivation;
            break;

        // Threshold
        case 1:
            return threshold(neurone.outputWithoutActivation);
            break;

        // Sigmoïd
        case 2:
            return sigmoid(neurone.outputWithoutActivation);
            break;

        // ReLU
        case 3:
            return relu(neurone.outputWithoutActivation);
            break;

        // Smooth ReLU
        case 4:
            return smooth_relu(neurone.outputWithoutActivation);
            break;
        }
        return neurone.outputWithoutActivation;
}