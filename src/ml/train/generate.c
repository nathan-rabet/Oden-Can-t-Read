#ifndef GEN_NET
#define GEN_NET

#include <time.h>
#include <stdlib.h>
#include <float.h>

#include "../struct/network.h"
#include "../struct/layer.h"
#include "../struct/neurone.h"

#include "../../math/random.h"

#define NB_LAYERS 2
#define NB_NEURONES_MID_LAYER 20
#define NB_NEURONES_LAST_LAYER 10
#define FUNCTION_MID_LAYER 3
#define FUNCTION_LAST_LAYER 2

struct Network generateRandomNetwork(size_t nb_layers,size_t nb_neurone_per_layer[],char activation_functions_per_layer[]) {
    
    struct Layer *layers = malloc(sizeof(struct Layer) * nb_layers);
    for (size_t i = 1; i < nb_layers; i++) // start at "real" layer, not the input one!
    {
        struct Neurone *neurones = malloc(sizeof(struct Neurone) * nb_neurone_per_layer[i]);

        for (size_t j = 1; j < nb_neurone_per_layer[i]; j++) // same than the last comment
        {
            // Weights
            size_t nb_weights = nb_neurone_per_layer[j - 1];
            double *weights = NULL;
            weights = malloc(sizeof(double) * nb_weights);
            for (size_t k = 0; k < nb_weights; k++)
            {
                weights[k] = doubleRand(DBL_MIN,DBL_MAX);
            }

            neurones[j] = CreateNeurone(weights,doubleRand(DBL_MIN,DBL_MAX),activation_functions_per_layer[i],nb_neurone_per_layer[i]);
        }
        
    layers[i] = CreateLayer(neurones,nb_neurone_per_layer[i]);
    }

    struct Network network = CreateNetwork(layers,nb_layers);
    appendFirstLayerToNetwork(&network);
    return network;
    
}

#endif