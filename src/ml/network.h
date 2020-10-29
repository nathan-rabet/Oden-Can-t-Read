#ifndef NETWORK
#define NETWORK

#include "layer.h"

/**
 * @brief ML network
 * 
 */
struct Network {
    /**
     * @brief Point to the first layer of the network
     * 
     */
    struct Layer *layers;

    /**
     * @brief The number of layers that the network has.
     * 
     */
    int nb_layers;
};

/**
 * @brief Create a C99 struct Network
 * by parsing a JSON file.
 * 
 * @param jsonFilePath The path of the JSON file.
 * @return struct Network 
 */
struct Network LoadNetworkFromJSON(char jsonFilePath[]);
/**
 * @brief Give the number of input that a network has.
 * 
 * @param network The network to work with.
 * @return The number of inputs.
 */
int networkNbInput(struct Network network);

/**
 * @brief Give the number of output that a network has.
 * 
 * @param network The network to work with.
 * @return The number of outputs.
 */
int networkNbOutput(struct Network network);

/**
 * @brief Calculate a network output.
 * 
 * @param network The network to work with.
 * @param intput The inputs the network
 * will perform calculus on.
 * @return The list of outputs.
 */
double * CalculateNetworkOutput(struct Network network, double intput[]);

#endif