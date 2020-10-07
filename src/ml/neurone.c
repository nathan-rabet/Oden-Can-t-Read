#include "neurone.h"
#include <math.h>

// If no activation function, set activationFunction to 0
struct Neurone CreateNeurone(float weights[],float bias, unsigned char activationFunction) {
    struct Neurone neurone;
    neurone.weights = weights;
    neurone.nb_weights = sizeof(weights) / sizeof(float);
    neurone.bias = bias;
    neurone.activationFunction = activationFunction;
    return neurone;
}

float threshold(float x) {
    if (x < 1) {
        return 0;
    }
    return 1;
}

float sigmoid(float x) {
    return 1 / (1 + exp(-x));
}

float relu(float x) {
    return max(0,x);
}

float smooth_relu(float x) {
    return log(1 + exp(x));
}

int CalculateNeuroneOutput(struct Neurone *neurone,float input[]) {
    if (sizeof(input) / sizeof(float) == neurone->nb_weights) { 
        neurone->output = 0;
        for (int i = 0; i < neurone->nb_weights; i++)
        {
            neurone->output += neurone->weights[i] * input[i];
        }

        neurone->output += neurone->bias;

        // Activation functions
        switch (neurone->activationFunction)
        {
        // Identity
        case 0:
            // Nothing to change
            break;
        
        // Threshold
        case 1:
            neurone->output = threshold(neurone->output);
            break;
        
        // Sigmoïd
        case 2:
            neurone->output = sigmoid(neurone->output);
            break;

        // ReLU
        case 3:
            neurone->output = relu(neurone->output);
            break;

        // Smooth ReLU
        case 4:
            neurone->output = smooth_relu(neurone->output);
            break;
        
        // If nothing match
        default:
            return 1;
        }

        return 0;
    }
    else {
        return 1;
    }
}

void NeuroneLinker(struct Neurone *curentNeurone,struct Neurone *nextNeurone) {
    curentNeurone->nextNeuroneSameLayer = nextNeurone;
}