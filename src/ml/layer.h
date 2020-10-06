#include "neurone.h"

typedef struct Layer {
    struct Neurone **neurones;
    
    // If nextLayer == NULL, the current layer is the last layer
    struct Layer *nextLayer;
};

// Initiate a layer (which includes neurones)
struct Layer CreateLayer(struct Neurone neurones[]);

void LayerLinker(struct Layer *currentLayer, struct Layer *nextLayer);