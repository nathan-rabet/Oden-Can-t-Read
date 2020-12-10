#include "network.h"
#include "layer.h"
#include "neurone.h"

#include <json-c/json.h>
#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include <float.h>
#include <math.h>

#include "../../math/random.h"


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

struct Network* generateRandomNetwork(size_t nb_layers,size_t nb_neurone_per_layer[],char activation_functions_per_layer[],char expected_character) {
    
    struct Layer **layers = malloc(sizeof(struct Layer*) * nb_layers);

    struct Neurone **neurones = NULL;
    // ? First layer special parameters
    neurones = malloc(sizeof(struct Neurone*) * nb_neurone_per_layer[0]);
    double *uniqueWeight = malloc(sizeof(double));
    *uniqueWeight = 1;
    for (size_t i = 0; i < nb_neurone_per_layer[0]; i++)
    {
        neurones[i] = CreateNeurone(uniqueWeight,0,0,1);
    }
    layers[0] = CreateLayer(neurones,nb_neurone_per_layer[0]);

    for (size_t i = 1; i < nb_layers; i++) // start at "real" layer, not the input one!
    {
        neurones = NULL;
        neurones = malloc(sizeof(struct Neurone*) * nb_neurone_per_layer[i]);

        for (size_t j = 0; j < nb_neurone_per_layer[i]; j++) // same than the last comment
        {
            // Weights
            size_t nb_weights = nb_neurone_per_layer[i-1];
            double *weights = NULL;
            weights = malloc(sizeof(double) * nb_weights);
            for (size_t k = 0; k < nb_weights; k++)
            {
                //weights[k] = Gaussian();
                weights[k] = doubleRand(-0.5,0.5);
            }

            neurones[j] = CreateNeurone(weights,doubleRand(-1, 0),activation_functions_per_layer[i],nb_weights);
        }
        
        layers[i] = CreateLayer(neurones,nb_neurone_per_layer[i]);
    }

    return CreateNetwork(layers,nb_layers,expected_character);
    
}

double Gaussian()
{
    return (exp( (-0.5) * pow(doubleRand(-1,1), 2) ) )/sqrt(2*3.14);
}