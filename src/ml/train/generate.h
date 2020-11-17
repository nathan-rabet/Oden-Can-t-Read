#include <stdlib.h>

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
 * @return struct Network 
 */
struct Network generateRandomNetwork(size_t nb_layers,size_t nb_neurone_per_layer[],char activation_functions_per_layer[]);