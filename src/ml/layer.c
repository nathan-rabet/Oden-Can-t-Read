#include "layer.h"

struct Layer CreateLayer(struct Neurone neurones[]) {
    struct Layer layer;

    int n = sizeof(neurones) / sizeof(struct Neurone);
    layer.neurones = neurones;
    return layer;
}

void LayerLinker(struct Layer *currentLayer, struct Layer *nextLayer) {
    currentLayer->nextLayer = nextLayer;
}