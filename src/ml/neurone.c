#include "neurone.h"
#include <math.h>
#include <stdlib.h>

// If no activation function, set activationFunction to 0
struct Neurone CreateNeurone(double weights[],double bias, unsigned char activationFunction, int nb_input) {
    struct Neurone neurone;
    neurone.weights = malloc(sizeof(double) * nb_input);
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

double CalculateNeuroneOutput(struct Neurone neurone,double input[]) {
        double output;
        
        for (int i = 0; i < neurone.nb_inputs; i++)
        {
            output += neurone.weights[i] * input[i];
        }

        output += neurone.bias;

        // Activation functions
        switch (neurone.activationFunction)
        {
        // Identity
        case 0:
            // Nothing to change
            break;
        
        // Threshold
        case 1:
            output = threshold(output);
            break;
        
        // Sigmoïd
        case 2:
            output = sigmoid(output);
            break;

        // ReLU
        case 3:
            output = relu(output);
            break;

        // Smooth ReLU
        case 4:
            output = smooth_relu(output);
            break;
        }

        return output;
}