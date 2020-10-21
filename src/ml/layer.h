#ifndef LAYER
#define LAYER

#include "neurone.h"

struct Layer {
    struct Neurone *neurones;

    int nb_neurones;
    
    // If nextLayer == NULL, the current layer is the last layer
    struct Layer *nextLayer;

    double *output;
};

// Initiate a layer (which includes neurones)
struct Layer CreateLayer(struct Neurone neurones[], int nb_neurones);

double * CalculateLayerOutput(struct Layer layer, double intput[]);

#endif