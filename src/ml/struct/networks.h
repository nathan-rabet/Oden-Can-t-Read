#ifndef NETWORKS
#define NETWORKS

#include <stdio.h>
#include "network.h"

/**
 * @brief ML binary networks
 * 
 */
struct Networks {
    /**
     * @brief The binary networks
     * 
     */
    struct Network **networks;

    /**
     * @brief The number of binary networks.
     * 
     */
    size_t nb_networks;
};

/**
 * @brief Create a Network object
 * 
 * @param network The configured network.
 * @param nb_networks The number of networks.
 * @return struct Network 
 */
struct Networks* CreateNetworks(struct Network **networks, size_t nb_networks);

/**
 * @brief Free a Network object
 * 
 * @param Network to free
 */
void FreeNetworks(struct Networks *networks);

/**
 * @brief Create a C99 struct Network
 * by parsing a JSON file.
 * 
 * @param jsonFilePath The path of the JSON file.
 * @return struct Network 
 */
struct Networks* LoadNetworksFromJSON(char jsonFilePath[]);
/**
 * @brief Give the number of input that a network has.
 * 
 * @param network The network to work with.
 * @return The number of inputs.
 */
void SaveNetworksToJSON(struct Networks *networks, char jsonFilePath[]);

/**
 * @brief Calculate a networks outputs.
 * 
 * @param network The network to work with.
 * @param intput The inputs the network
 * @param nb_input The number of inputs (eq. len(input))
 * will perform calculus on.
 * @return The list of outputs.
 */
double ** calculateNetworksOutput(struct Networks *networks, double intput[]);

#endif
