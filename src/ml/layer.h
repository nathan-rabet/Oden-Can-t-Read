#include "neurone.h"

typedef struct Layer {
    struct Neurone **neurones;
    
    // If nextLayer == NULL, the current layer is the last layer
    struct Layer *nextLayer;
};