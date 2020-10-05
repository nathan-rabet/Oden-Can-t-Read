#include "neurone.h"
#include <math.h>

struct Neurone CreatePerceptron(float weights[],float bias, unsigned char activationFunction) {
    struct Neurone neurone;
    neurone.weights = weights;
    neurone.nb_weights = sizeof(weights) / sizeof(float);
    neurone.bias = bias;
    neurone.activationFunction = activationFunction;
    return neurone;
}

float threshold(float x, float threshold) {
    if (x < threshold) {
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

int CalculateNeuroneOutput(struct Neurone *neurone,float input[],float threashold) {
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
            neurone->output = threshold(neurone->output, threashold);
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