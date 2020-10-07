#include <stdlib.h>
#include <stdio.h>

typedef struct Neurone {
    //  ◯
    //  ↓ nextLayer
    //  ◯
    //  ↓ nextLayer
    //  ◯
    //  ↓ nextLayer
    //  ◯ 
    //  ↓ NULL
    //  ∅
    struct Neurone *nextNeuroneSameLayer;
    
    // The bias of the neurone
    float bias;

    int nb_weights;

    // List of weights of the neurone (=nb of entries)    
    // 
    // Pointer
    //     v
    //  | |w0|w1|w2|w3|...|wn| | 
    float *weights;

    // List of implemented functions :
    // 0 -> No function
    // 1 -> Threashold
    // 2 -> Sigmoïd
    // 3 -> ReLU
    // 4 -> Smooth ReLU
    unsigned char activationFunction;
    
    // activationFunction(Σxi×wi + bias) = output
    float output;
};

struct Neurone CreateNeurone(float weights[],float bias, unsigned char activationFunction);

// if return int = 1 => ERROR !
int CalculateNeuroneOutput(struct Neurone *neurone,float input[]);

float threshold(float x);

float sigmoid(float x);

float relu(float x);

float smooth_relu(float x);

// nextNeurone <=> next layer into the current layer
void NeuroneLinker(struct Neurone *curentNeurone,struct Neurone *nextNeurone);