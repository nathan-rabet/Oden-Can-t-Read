#ifndef NETWORK
#define NETWORK

#include "layer.h"

struct Network {
    struct Layer *layers;

    int nb_layers;

    // In case of multiples networks
    // this pointer point to another network
    struct Network *otherNetwork;
};

struct Network * LoadNetworkFromJSON(char jsonFilePath[]);

#endif