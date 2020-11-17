#include <stdlib.h>
#include "layer.h"


struct Layer CreateLayer(struct Neurone neurones[], size_t nb_neurones) {
    struct Layer layer;

    layer.nb_neurones = nb_neurones;
    layer.neurones = neurones;
    return layer;
}

double * CalculateLayerOutput(struct Layer layer, double input[]) {
    double *outputLayer = NULL;
    outputLayer = malloc(sizeof(double) * layer.nb_neurones);
    struct Neurone *workingNeurone = layer.neurones;

    size_t n = 0;
    while (n < layer.nb_neurones) {
        outputLayer[n] = calculateNeuroneOutput(*workingNeurone,input);
        workingNeurone = workingNeurone->nextNeuroneSameLayer;
        n++;
    }
    return outputLayer;
}