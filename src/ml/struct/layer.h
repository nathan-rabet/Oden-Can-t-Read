#ifndef LAYER
#define LAYER

#include <stdio.h>
#include "neurone.h"

/**
 * @brief ML layer
 * 
 */
struct Layer {

    struct Neurone **neurones; /* Point to the first neurone of the current layer */

    size_t nb_neurones; /* The number of neurones that the layer contains */
};

// Initiate a layer (which includes neurones)

/**
 * @brief Create a Layer object.
 * 
 * @param neurones The configured neurones
 * you want to include in the layer.
 * @param nb_neurones The number of neurones your layer will have.
 * @return struct Layer 
 */
struct Layer* CreateLayer(struct Neurone **neurones, size_t nb_neurones);

/**
 * @brief Free a Layer object.
 * 
 * @param layer The layer
 */
void FreeLayer(struct Layer* layer);

/**
 * @brief Calculate an output of a layer.
 * 
 * @param layer The layer to work with.
 * @param intput The input list you want to calculate output with.
 * @return The list of outputs.
 */
double * CalculateLayerOutput(struct Layer *layer, double intput[]);

void PrintLayer(struct Layer *layer);

void PrintLayerOutput(struct Layer* layer);
#endif