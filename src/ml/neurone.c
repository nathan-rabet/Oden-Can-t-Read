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
    if (x <= 0) {
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
        double outputNeurone = 0;
        
        for (int i = 0; i < neurone.nb_inputs; i++)
        {
            double w = neurone.weights[i];
            double in = input[i];
            outputNeurone += w * in;
        }

        outputNeurone += neurone.bias;

        // Activation functions
        switch (neurone.activationFunction)
        {
        // Identity
        case 0:
            // Nothing to change
            break;
        
        // Threshold
        case 1:
            outputNeurone = threshold(outputNeurone);
            break;
        
        // Sigmoïd
        case 2:
            outputNeurone = sigmoid(outputNeurone);
            break;

        // ReLU
        case 3:
            outputNeurone = relu(outputNeurone);
            break;

        // Smooth ReLU
        case 4:
            outputNeurone = smooth_relu(outputNeurone);
            break;
        }

        return outputNeurone;
}