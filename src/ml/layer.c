#include <stdlib.h>
#include "layer.h"


struct Layer CreateLayer(struct Neurone neurones[], int nb_neurones) {
    struct Layer layer;

    layer.nb_neurones = nb_neurones;
    layer.neurones = neurones;
    return layer;
}

double * CalculateLayerOutput(struct Layer layer, double input[]) {
    layer.output = malloc(sizeof(double) * layer.nb_neurones);
    struct Neurone workingNeurone = *layer.neurones;

    for (int n = 0; n < layer.nb_neurones; n++) {
        layer.output[n] = CalculateNeuroneOutput(layer.neurones[n],input);
        workingNeurone = *workingNeurone.nextNeuroneSameLayer;
    }

    return layer.output;
}