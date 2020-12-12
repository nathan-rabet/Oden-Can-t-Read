#ifndef NETWORK
#define NETWORK

#include <stdio.h>
#include "layer.h"

#define NB_INPUTS 32*32

/**
 * @brief ML network for one single character
 * 
 */
struct Network {
    /**
     * @brief Point to the first layer of the network
     * 
     */
    struct Layer **layers;

    /**
     * @brief The number of layers that the network has.
     * 
     */
    size_t nb_layers;

    /**
     * @brief The character the network will be able to confirm.
     * 
     */
    char character;
};

/**
 * @brief Create a Network object
 * 
 * @param layers The configured layers.
 * @param nb_layers The number of layers.
 * @return struct Network 
 */
struct Network* CreateNetwork(struct Layer **layers, size_t nb_layers,char expected_char);

/**
 * @brief Free a Network object
 * 
 * @param Network to free
 */
void FreeNetwork(struct Network *network);

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

/**
 * @brief Generate a network with a random configuration.
 * 
 * @param nb_layers The number of layer the network will have 
 * (entry layer excluded).
 * @param nb_neurone_per_layer An array with the number of neurone per layer.
 * For example, for a network with 2 layers, if you want the layer 1 to
 * have 20 neurones and the layer 2 to have 10 neurones, then 
 * nb_neurone_per_layer = {20,10}.
 * @param activation_functions_per_layer An array containing 
 * the characters corresponding to an activation function. For example, if you want the layer 1 to
 * have a sigmoïd function and the layer 2 to have a ReLU function, then 
 * activation_functions_per_layer = {2,3}.
 * @param nbtrainimages Number of images.
 * @param expected_character The character the network should recognize.
 * @return struct Network 
 */
struct Network* generateRandomNetwork(size_t nb_layers,size_t nb_neurone_per_layer[],char activation_functions_per_layer[],char expected_character);
#endif
