#include "neurone.h"
#include <math.h>
#include <stdlib.h>

// If no activation function, set activationFunction to 0
struct Neurone CreateNeurone(double weights[],double bias, unsigned char activationFunction, size_t nb_input) {
    struct Neurone neurone;
    //neurone.weights = malloc(sizeof(double) * nb_input);
    neurone.weights = weights;
    neurone.nb_inputs = nb_input;
    neurone.bias = bias;
    neurone.activationFunction = activationFunction;
    neurone.nextNeuroneSameLayer = NULL;
    neurone.outputWithoutActivation = 0;
    neurone.delta_error = 0;
    neurone.delta_bias = NULL;
    neurone.delta_weight = NULL;
    return neurone;
}

void FreshNeuroneForTraining(struct Neurone neurone, size_t nblastLayer ,size_t nbtrainimages)
{
    if (neurone.delta_bias != NULL)
    {
        free(neurone.delta_bias);
        free(neurone.delta_weight);
    }
    neurone.delta_bias = malloc(nbtrainimages * sizeof(double));
    neurone.delta_weight = malloc(nblastLayer * nbtrainimages * sizeof(double));
}

void FreeNeurone(struct Neurone *neurone)
{
    //free(neurone->weights);
    if ((neurone->delta_bias) != NULL && (neurone->delta_bias) != NULL)
    {
        free(neurone->delta_bias);
        free(neurone->delta_weight);
    }
    if (neurone->nextNeuroneSameLayer != NULL)
        FreeNeurone(neurone->nextNeuroneSameLayer);
    //free(neurone);
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

double smooth_relu_derivate(double x) {
    double ex = exp(x);
    return (ex)/(1+ex);
}

double calculateNeuroneOutput(struct Neurone* neurone, double input[]) {
        neurone->outputWithoutActivation = 0;

        for (size_t i = 0; i < neurone->nb_inputs; i++)
        {
            double w = neurone->weights[i];
            double in = input[i];
            neurone->outputWithoutActivation += w * in;
        }

        neurone->outputWithoutActivation += neurone->bias;

        return activationFunction(neurone);
}

double activationFunction(struct Neurone* neurone)
{
        // Activation functions
        switch (neurone->activationFunction)
        {
        // Identity
        case 0:
            return neurone->outputWithoutActivation;
            break;

        // Threshold
        case 1:
            return threshold(neurone->outputWithoutActivation);
            break;

        // Sigmoïd
        case 2:
            return sigmoid(neurone->outputWithoutActivation);
            break;

        // ReLU
        case 3:
            return relu(neurone->outputWithoutActivation);
            break;

        // Smooth ReLU
        case 4:
            return smooth_relu(neurone->outputWithoutActivation);
            break;
        }
        return neurone->outputWithoutActivation;
}

double actvation_fonction_derivate(struct Neurone* neurone)
{
    // Activation functions
        switch (neurone->activationFunction)
        {
        // Identity
        case 0:
            return 0;
            break;

        // Threshold
        case 1:
            return 0;
            break;

        // Sigmoïd
        case 2:
            return sigmoid_derivate(neurone->outputWithoutActivation);
            break;

        // ReLU
        case 3:
            return threshold(neurone->outputWithoutActivation);
            break;

        // Smooth ReLU
        case 4:
            return smooth_relu_derivate(neurone->outputWithoutActivation);
            break;
        }
        return neurone->outputWithoutActivation;
}

void PrintLayerOutput(struct Neurone* neurone)
{
    int i = 0;
    struct Neurone* nextn = neurone;
    double output = 0;
    while (nextn != NULL)
    {
        output = neurone->outputWithoutActivation;
        if (output != 0)
            printf("n°%d: %f",i,output);  

        nextn = nextn->nextNeuroneSameLayer;
        i++;
    }
    printf("\n");
}