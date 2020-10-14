#include "neurone.h"
#include <math.h>

// If no activation function, set activationFunction to 0
struct Neurone CreateNeurone(double weights[],double bias, unsigned char activationFunction, int nb_input) {
    struct Neurone neurone;
    neurone.weights = weights;
    neurone.nb_inputs = nb_input;
    neurone.bias = bias;
    neurone.activationFunction = activationFunction;
    return neurone;
}

double threshold(double x) {
    if (x < 1) {
        return 0;
    }
    return 1;
}

double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double relu(double x) {
    return fmax(0,x);
}

double smooth_relu(double x) {
    return log(1 + exp(x));
}

double CalculateNeuroneOutput(struct Neurone *neurone,double input[]) {
    neurone->output = 0;
        for (int i = 0; i < neurone->nb_inputs; i++)
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
        }

        return neurone->output;
}