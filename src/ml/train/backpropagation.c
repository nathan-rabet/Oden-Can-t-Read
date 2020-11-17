#include "backpropagation.h"

void trainingNetwork(struct Network network, char* databasepath, size_t minibatchsize, size_t minibatchnumber, size_t minibatchtrain)
{
    //Define letters
    char* letters = malloc(62*sizeof(char));
    size_t j = 0;
    for (char i = '0'; i <= '9'; i++) //Integers 0 to 9
    {
        letters[j] = i;
        j++;
    }
    for (char i = 'A'; i <= 'Z'; i++) //Uppercase letters
    {
        letters[j] = i;
        j++;
    }
    for (char i = 'a'; i <= 'z'; i++) //Lowercase letters
    {
        letters[j] = i;
        j++;
    }

    //Define minibatch
    struct MatrixDOUBLE* minibatchinputs = malloc(minibatchsize*sizeof(struct MatrixUCHAR));
    size_t* minibatchletters = malloc(minibatchsize*sizeof(size_t));
    
    for (size_t nb = 0; nb < minibatchnumber; nb++)
    {
        printf("minibatch num°%lu", nb);
        for (size_t i = 0; i < minibatchsize; i++)
        {
            minibatchletters[i] = rand() % 62;
            char letter = letters[minibatchletters[i]];
            minibatchinputs[i] = loadDataBase(databasepath, letter, rand() % 1000);
        }
        for (size_t j = 0; j < minibatchtrain; j++)
        {
            minibatch(network, minibatchinputs, minibatchletters, minibatchsize);
        }
    }
    
}

void minibatch(struct Network network, struct MatrixDOUBLE* minibatchinputs, size_t* targets, size_t nbimages)
{
    //Train
    for (size_t i = 0; i < nbimages; i++)
    {
        //Feedforward (run the network with input to set the z and activation values)
        double* output = calculateNetworkOutput(network, minibatchinputs[i].cells);

        //Output error (calculation delta of the last layer) delta = (activation - outputTarget) * sigmoid'(z)
        struct Layer* lastlayer = network.layers;
        for (size_t layer = 0; layer < network.nb_layers-1; layer++)
        {
            lastlayer = lastlayer->nextLayer;
        }
        for (size_t k = 0; k < networkNbOutput(network); k++)
        {
            struct Neurone n = lastlayer->neurones[k];
            
            n.delta_error = (output[k] - k == targets[i]);

            // TODO
            //Need impletation for other activation fonction than the sigmoid.
            n.delta_error *= sigmoid_derivate(n.outputWithoutActivation);
        }
        
        //Backpropagate the error
        backpropagation(network);

        //Set detla
        for (size_t l = 1; l < network.nb_layers; l++)
        {
            for (size_t n = 0; n < network.layers[l].nb_neurones; n++)
            {
                struct Neurone neurone = network.layers[l].neurones[n];
                neurone.delta_bias[i] = neurone.delta_error;

                for (size_t k = 0; k < network.layers[l-1].nb_neurones; k++)
                {
                    neurone.delta_weight[k + i*nbimages] = activationFunction(network.layers[l-1].neurones[k]) * neurone.delta_error;
                }
                
            }
            
        }
    }

    //Average bias and weight
    for (size_t l = 1; l < network.nb_layers; l++)
    {
        for (size_t n = 0; n < network.layers[l].nb_neurones; n++)
        {
            struct Neurone neurone = network.layers[l].neurones[n];
            double sumbias = 0;

            for (size_t k = 0; k < network.layers[l-1].nb_neurones; k++)
            {
                double sumweights = 0;

                for (size_t i = 0; i < nbimages; i++)
                {
                    sumbias += neurone.delta_bias[i];

                    sumweights += neurone.delta_weight[k + i*nbimages];
                }

                neurone.weights[k] = sumweights/nbimages;
            }
            neurone.bias -= sumbias/nbimages;
        }
    }
}

void backpropagation(struct Network network)
{
    //For each l=L−1,L−2,…,2 compute deltal = (45)
    //struct Layer* layer = network.layers;
    for (size_t l = network.nb_layers-2; l > 0; l++)
    {
        for (size_t j = 0; j < network.layers[l].nb_neurones; j++)
        {
            double sum = 0;
            for (size_t k = 0; k < network.layers[l+1].nb_neurones; k++)
            {
                sum += network.layers[l+1].neurones[k].weights[j] * network.layers[l+1].neurones[k].delta_error;
            }
        }
    }
}

struct MatrixDOUBLE loadDataBase(char* databasepath, char letter, size_t imagenumber)
{
    //Convert a imagenumber to a "12345" string
    char *imagename = malloc(6*sizeof(char));
    imagename[5] = 0;
    for (size_t i = 5; i > 0; i--)
    {
        imagename[i-1] = '0' + imagenumber%10;
        imagenumber /= 10;
    }
    
    //Build the image path string
    char* imagepath = malloc(150*sizeof(char));
    sprintf(imagepath, "%s/%02x/train_%02x/train_%02x_%s.png", databasepath, letter, letter, letter, imagename);

    //Load image
    SDL_Surface *image = loadImage(imagepath);

    free(imagepath);
    free(imagename);
    struct MatrixDOUBLE img = binarization(image);
    return img;
}