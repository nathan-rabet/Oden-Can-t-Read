#include <stdlib.h>
#include "layer.h"


struct Layer CreateLayer(struct Neurone neurones[], int nb_neurones) {
    struct Layer layer;

    layer.nb_neurones = nb_neurones;
    layer.neurones = neurones;
    return layer;
}

double * CalculateLayerOutput(struct Layer layer, double input[]) {
    double *outputLayer = NULL;
    outputLayer = malloc(sizeof(double) * layer.nb_neurones);
    struct Neurone *workingNeurone = layer.neurones;

    int n = 0;
    while (n < layer.nb_neurones) {
        outputLayer[n] = CalculateNeuroneOutput(layer.neurones[n],input);
        workingNeurone = workingNeurone->nextNeuroneSameLayer;
        n++;
    }
    return outputLayer;
}