#ifndef NETWORK
#define NETWORK

#include "layer.h"

struct Network {
    struct Layer *layers;

    int nb_layers;
};

struct Network LoadNetworkFromJSON(char jsonFilePath[]);

int networkNbInput(struct Network network);
int networkNbOutput(struct Network network);

double * CalculateNetworkOutput(struct Network network, double intput[]);

#endif