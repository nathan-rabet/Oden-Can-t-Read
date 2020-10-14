#ifndef NEURONE
#define NEURONE

struct Neurone {
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
    
    int nb_inputs;

    // The bias of the neurone
    double bias;

    // List of weights of the neurone (=nb of entries)    
    // 
    // Pointer
    //     v
    //  | |w0|w1|w2|w3|...|wn| | 
    double *weights;

    // List of implemented functions :
    // 0 -> No activation function
    // 1 -> Threashold
    // 2 -> Sigmoïd
    // 3 -> ReLU
    // 4 -> Smooth ReLU
    unsigned char activationFunction;
    
    // activationFunction(Σxi×wi + bias) = output
    double output;
};

struct Neurone CreateNeurone(double weights[],double bias, unsigned char activationFunction, int nb_input);

double CalculateNeuroneOutput(struct Neurone *neurone,double input[]);

double threshold(double x);

double sigmoid(double x);

double relu(double x);

double smooth_relu(double x);
#endif