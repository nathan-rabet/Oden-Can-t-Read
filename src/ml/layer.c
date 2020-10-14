#include "layer.h"

struct Layer CreateLayer(struct Neurone neurones[], int nb_neurones) {
    struct Layer layer;

    layer.nb_neurones = nb_neurones;
    layer.neurones = neurones;
    return layer;
}