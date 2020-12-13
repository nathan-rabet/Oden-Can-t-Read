#include <stdlib.h>
#include <math.h>

#include "../ml/struct/network.h"
#include "analysis.h"

double cost(struct Network *network, size_t expected_outputs_index)
{
    // cost = ½∑(a-y)²

    double sum = 0;
    for (size_t i = 0; i < networkNbOutput(network); i++)
    {
        double o = activationFunction(network->layers[network->nb_layers - 1]->neurones[i]);
        sum += pow(o - (i == expected_outputs_index), 2);
    }

    sum /= 2;
    return sum;
}

double cost_derivate(struct Network *network, double *expected_outputs)
{
    // cost' = ∑a-y

    double sum = 0;
    for (size_t i = 0; i < networkNbOutput(network); i++)
    {
        double o_i = activationFunction(network->layers[network->nb_layers - 1]->neurones[i]);
        sum += o_i - expected_outputs[i];
    }
    return sum;
}