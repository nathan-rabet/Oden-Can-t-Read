#ifndef NETWORK
#define NETWORK

#include <stdio.h>
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
    size_t nb_layers;
};

/**
 * @brief Create a Network object
 * 
 * @param layers The configured layers.
 * @param nb_layers The number of layers.
 * @return struct Network 
 */
struct Network CreateNetwork(struct Layer *layers,size_t nb_layers);

/**
 * @brief Free a Network object
 * 
 * @param Network to free
 */
void FreeNetwork(struct Network *network);

/**
 * @brief Append an input layer to a nework.
 * 
 * @param network The network which need the input layer.
 */
void appendFirstLayerToNetwork(struct Network *network);

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
void SaveNetworkToJson(struct Network *network, char jsonFilePath[]);
/**
 *@brief Save a selected network to a selected json file.
 *
 *@param Network the network selected to be saved
 *       jsonFilePath the path of the file where the network is saved
 */
size_t networkNbInput(struct Network *network);

/**
 * @brief Give the number of output that a network has.
 * 
 * @param network The network to work with.
 * @return The number of outputs.
 */
size_t networkNbOutput(struct Network *network);

/**
 * @brief Give the number of neurones that a network has.
 * 
 * @param network The network to work with.
 * @return The number of neurones.
 */
size_t networkNbNeurones(struct Network *network);

/**
 * @brief Give the number of weights that a network has.
 * 
 * @param network The network to work with.
 * @return The number of weights.
 */
size_t networkNbWeights(struct Network *network);

/**
 * @brief Calculate a network output.
 * 
 * @param network The network to work with.
 * @param intput The inputs the network
 * @param nb_input The number of inputs (eq. len(input))
 * will perform calculus on.
 * @return The list of outputs.
 */
double * calculateNetworkOutput(struct Network *network, double* intput);

void PrintNetwork(struct Network* network);
#endif
