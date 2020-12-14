#ifndef NETWORKS
#define NETWORKS

#include <stdio.h>
#include "network.h"
#include "../../segmentation/segmentation.h"

#define CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?!"
#define CHARSLEN 66

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
 * @param networks The configured networks.
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
 * @brief Create a C99 struct Networks
 * by parsing a JSON file.
 * 
 * @param jsonFilePath The path of the JSON file.
 * @return struct Networks
 */
struct Networks* LoadNetworksFromJSON(char jsonFilePath[]);
/**
 * @brief Create a JSON file data based on C99 struct Networks
 * 
 * @param networks The networks to work with.
 * @param jsonFilePath The path of the JSON file.
 */
void SaveNetworksToJSON(struct Networks *networks, char jsonFilePath[]);

/**
 * @brief Calculate networks outputs.
 * 
 * @param network The networks to work with.
 * @param input The input of the networks.
 * will perform calculus on.
 * @return The list of outputs.
 */
double **calculateNetworksOutput(struct Networks *networks, char input[]);

/**
 * @brief Generate networks with a random configuration.
 * 
 * @param nb_layers The number of layer a single network will have 
 * (entry layer excluded).
 * @param nb_neurone_per_layer An array with the number of neurone per layer.
 * For example, for a network with 2 layers, if you want the layer 1 to
 * have 20 neurones and the layer 2 to have 10 neurones, then 
 * nb_neurone_per_layer = {20,10}.
 * @param activation_functions_per_layer An array containing 
 * the characters corresponding to an activation function. For example, if you want the layer 1 to
 * have a sigmoïd function and the layer 2 to have a ReLU function, then 
 * activation_functions_per_layer = {2,3}.
 * @return struct Networks
 */
struct Networks* generateRandomNetworks(size_t nb_layers,size_t nb_neurone_per_layer[],char activation_functions_per_layer[]);

void FreeNetworks(struct Networks *networks);

char FindCharacter(struct Networks *networks, char* letter_matrix);

void FindCharacters(struct Networks *networks, struct Characters *character);
#endif
