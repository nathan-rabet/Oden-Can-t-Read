#include <stdlib.h>
#include "layer.h"

#include <math.h>

struct Layer *CreateLayer(struct Neurone **neurones, size_t nb_neurones)
{
    struct Layer *layer = malloc(sizeof(struct Layer));

    layer->nb_neurones = nb_neurones;
    layer->neurones = neurones;
    return layer;
}

void FreeLayer(struct Layer *layer)
{
    for (size_t i = 0; i < layer->nb_neurones; i++)
    {
        FreeNeurone(layer->neurones[i]);
        free(layer->neurones[i]);
    }
    free(layer->neurones);
}

double *CalculateLayerOutput(struct Layer *layer, double input[])
{
    double *outputLayer = NULL;
    outputLayer = malloc(sizeof(double) * layer->nb_neurones);

    size_t n = 0;
    while (n < layer->nb_neurones)
    {
        outputLayer[n] = calculateNeuroneOutput(layer->neurones[n], input);
        n++;
    }

    return outputLayer;
}

void PrintLayer(struct Layer *layer)
{
    for (size_t n = 0; n < layer->nb_neurones; n++)
    {
        printf("%lf;", layer->neurones[n]->bias);
    }
    printf("\n");
}

void PrintLayerOutput(struct Layer *layer)
{
    double output = 0;
    for (size_t n = 0; n < layer->nb_neurones; n++)
    {
        output = layer->neurones[n]->outputWithoutActivation;
        printf("n°%ld: %f", n, output);
    }
    printf("\n");
}

double * softmax(struct Layer layer) {

    double *softed = malloc(sizeof(double) * layer.nb_neurones);
    double sum = 0;
    for (size_t k = 0; k < layer.nb_neurones; k++)
    {
        sum += exp(layer.neurones[k]->outputWithoutActivation);
    }
    


    for (size_t i = 0; i < layer.nb_neurones; i++)
    {
        softed[i] = exp(layer.neurones[i]->outputWithoutActivation) / sum;
    }
    
    return softed;

}