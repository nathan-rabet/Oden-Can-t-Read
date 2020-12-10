#include "network.h"
#include "layer.h"
#include "neurone.h"

#include <json-c/json.h>
#include <stdlib.h>
#include <stdio.h>

struct Network* CreateNetwork(struct Layer **layers, size_t nb_layers,char expected_char)
{
    struct Network *network = malloc(sizeof(struct Network));
    network->layers = layers;
    network->nb_layers = nb_layers;
    network->character = expected_char;
    return network;
}

void FreeNetwork(struct Network *network)
{
    for (size_t i = 0; i < network->nb_layers; i++)
    {
        FreeLayer(network->layers[i]);
    }
    
    //free(network);
}

size_t networkNbInput(struct Network *network)
{
    return network->layers[0]->nb_neurones;
}

size_t networkNbOutput(struct Network *network)
{

    size_t nb_output = 0;

    for (size_t i = 0; i < network->nb_layers; i++)
    {
        nb_output = network->layers[i]->nb_neurones;
    }
    return nb_output;
}

size_t networkNbNeurones(struct Network *network)
{

    size_t nb_neurones = 0;

    for (size_t i = 0; i < network->nb_layers; i++)
    {
        nb_neurones += network->layers[i]->nb_neurones;
    }

    return nb_neurones;
}

size_t networkNbWeights(struct Network *network)
{

    size_t nb_weights = 0;

    for (size_t i = 1; i < network->nb_layers; i++)
    {
        size_t weights = network->layers[i-1]->nb_neurones;
        nb_weights += weights * network->layers[i]->nb_neurones;
    }

    return nb_weights;
}

double *calculateNetworkOutput(struct Network *network, double *input)
{
    double *nextInput;
    double *outputNetwork;

    // Entry
    outputNetwork = malloc(sizeof(double) * (network->layers[0]->nb_neurones));
    for (size_t i = 0; i < network->layers[0]->nb_neurones; i++)
    {
        double *entry = &input[i];
        outputNetwork[i] = calculateNeuroneOutput((network->layers[0]->neurones[i]), entry);
    }
    nextInput = outputNetwork;

    // General case
    for (size_t i = 1; i < network->nb_layers; i++)
    {
        outputNetwork = CalculateLayerOutput(network->layers[i], nextInput);
        free(nextInput);
        nextInput = outputNetwork;
    }
    return outputNetwork;
}

void PrintNetwork(struct Network *network)
{
    printf("Network:\n");
    for (size_t l = 1; l < network->nb_layers; l++)
    {
        printf("Layer n°%lu:\n", l);
        PrintLayer(network->layers[l]);
    }
}