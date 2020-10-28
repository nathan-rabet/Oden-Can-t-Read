#ifndef LAYER
#define LAYER

#include "neurone.h"

/**
 * @brief ML Layer
 * 
 */
struct Layer {    
    /**
     * @brief Point the next direct layer.
     * 
     * @see l0 -> l1 -> l2 -> ... -> ln -> ∅
     * 
     */
    struct Layer *nextLayer; 

    struct Neurone *neurones; /* Point to the first neurone of the current layer */

    int nb_neurones; /* The number of neurones that the layer contains */

    /**
     * @brief The calculus output of the layer.
     * 
     * @deprecated This will MAYBE be deleted in the future.
     * 
     */
    double *output;
};

// Initiate a layer (which includes neurones)

/**
 * @brief Create a Layer object.
 * 
 * @param neurones The configured neurones.
 * you want to include in the layer.
 * @param nb_neurones The number of neurones your layer will have.
 * @return struct Layer 
 */
struct Layer CreateLayer(struct Neurone neurones[], int nb_neurones);

/**
 * @brief Calculate an output of a layer.
 * 
 * @param layer The layer to work with.
 * @param intput The input list you want to calculate output with.
 * @return A list of outputs.
 */
double * CalculateLayerOutput(struct Layer layer, double intput[]);

#endif