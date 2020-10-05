#include <stdlib.h>
#include <stdio.h>


struct Neurone {
    // The bias of the neurone
    float bias;

    int nb_weights;

    // List of weights of the neurone (=nb of entries)    
    // 
    // Pointer
    //     v
    //  | |w0|w1|w2|w3|...|wn| | 
    float *weights;

    unsigned char activationFunction;
    
    // activationFunction(Σxi×wi + bias = output
    float output;
};

// The parameter 'threashold' is useless when neurone->activationFunction ≠ 1
// if return int = 1 => ERROR !
int CalculateNeuroneOutput(struct Neurone *neurone,float input[],float threashold);

float threshold(float x, float threshold);

float sigmoid(float x);

float relu(float x);

float smooth_relu(float x);