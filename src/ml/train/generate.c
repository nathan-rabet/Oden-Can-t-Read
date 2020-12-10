#ifndef GEN_NET
#define GEN_NET

#include "generate.h"
#include <time.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#include "../struct/network.h"
#include "../struct/layer.h"
#include "../struct/neurone.h"

#include "../../math/random.h"

struct Network* generateRandomNetwork(size_t nb_layers,size_t nb_neurone_per_layer[],char activation_functions_per_layer[]) {
    
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

    return CreateNetwork(layers,nb_layers);
    
}

double Gaussian()
{
    return (exp( (-0.5) * pow(doubleRand(-1,1), 2) ) )/sqrt(2*3.14);
}

#endif