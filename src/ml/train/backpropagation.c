#include "backpropagation.h"

void trainingNetwork(struct Network network, double learningrate, char* databasepath, size_t imagesbyletters, size_t trainnumber)
{
    //Define letters
    char* letters = malloc(62*sizeof(char));
    size_t j = 0;
    for (size_t i = 48; i < 58; i++) //Odd 0 to 9
    {
        letters[j] = i;
        j++;
    }
    for (size_t i = 65; i < 91; i++) //Uppercase letter
    {
        letters[j] = i;
        j++;
    }
    for (size_t i = 97; i < 123; i++) //Lowercase letter
    {
        letters[j] = i;
        j++;
    }


        
    //Define output Target
    size_t nb_outputTarget = 62;
    double *outputTarget = malloc(62 * sizeof(double));
    for (size_t i = 0; i < 62; i++)
    {
        outputTarget[i] = 0;
    }
    

    //For each letter
    for (size_t letter = 0; letter < 62; letter++)
    {
        printf("Training the %c '%02x' letter...\n", letters[letter], letters[letter]);

        //Set ouput Target
        outputTarget[letter] = 1;
        if (letter>0)
            outputTarget[letter-1] = 0;

        //Train on different images of the same letter
        for (size_t imagenumber = 0; imagenumber < imagesbyletters; imagenumber++)
        {
            //Get the binarized image matrix
            struct MatrixUCHAR imagemat = loadDataBase(databasepath, letters[letter], imagesbyletters);

            //Define delta weight and bias
            size_t nb_neurones = networkNbNeurones(network);
            double **delta_bias = malloc(nb_neurones * sizeof(double));
            double ***delta_weight = malloc(sizeof(delta_bias)*nb_neurones);
            

            //Train the network for this image
            for (size_t train = 0; train < trainnumber; train++)
            {
                //Clear delta_bias
                for (size_t i = 0; i < nb_neurones; i++)
                {
                    delta_bias[i][j] = 0;
                }

                backpropagation(network, learningrate, imagemat, nb_outputTarget, outputTarget, delta_bias, delta_weight);
            }
        }
    }
    
    free(outputTarget);
}

struct MatrixUCHAR loadDataBase(char* databasepath, char letter, size_t imagenumber)
{
    //Convert a size_t to a "00000" string
    char *imagename = malloc(6*sizeof(char));
    imagename[5] = 0;
    for (size_t i = 5; i > 0; i--)
    {
        imagename[i-1] = 48 + imagenumber%10;
        imagenumber /= 10;
    }
    
    //Build the image path string
    char* imagepath = malloc(150*sizeof(char));
    sprintf(imagepath, "%s/%02x/train_%02x/train_%02x_%s%s", databasepath, letter, letter, letter, imagename,".png");

    //Load image
    SDL_Surface *image = loadImage(imagepath);

    free(imagepath);
    free(imagename);

    return binarization(image);
}

void backpropagation(struct Network network, double learningrate, struct MatrixUCHAR imagematrice, size_t nb_outputTarget, double *outputTarget
, double **delta_bias, double ***delta_weight)
{
    //Feedforward
    double *zs = malloc(50000 * sizeof(double));
    double *activations = realloc(imagematrice.cells, 50000 * sizeof(double)); //Matrix of neurones activations
    double *layercount = malloc(network.nb_layers * sizeof(double)); //List of numbers of neurones for each layer
    size_t matPos = 0; //pos of the pointer on the matrix

    for (size_t l = 1; l < network.nb_layers; l++)
    {
        matPos += network.layers[l].nb_neurones;
        for (size_t i = 0; i < network.layers[l].nb_neurones; i++)
        {
            double weight = network.layers[l].neurones->weights[i];
            double bias = network.layers[l].neurones[i].bias;
            zs[matPos + i] = weight * activations[matPos-network.layers[l].nb_neurones + i] + bias;

            activations[matPos + i] = calculateNeuroneOutput(network.layers[l].neurones[i], activations+matPos-network.layers[l].nb_neurones);
        }
    }

    //Ouput error
    double* layerdelta = malloc(nb_outputTarget * sizeof(double)); //define delta for the last layer
    
    size_t layer = network.nb_layers-2//layer - 1
    for (size_t i = 0; i < nb_outputTarget; i++) //Update last layer
    {
        //Calculating delta of a layer
        layerdelta[i] = (activations[matPos + i] - outputTarget[i])*derive(sigmoid,zs[matPos + i]);
        
        //Change bias
        delta_bias[matPos][i] = layerdelta[i];
        //Change delta weight for
        for (size_t j = 0; j < network.layers[network.nb_layers-2].nb_neurones; j++)
        {
            delta_weight[network.nb_layers-1][i][j] = activations[matPos - network.layers[network.nb_layers-2].nb_neurones + i] * layerdelta[i];
        }
            

        //matPos is on the last layer
    }
    
    //Update layers from the -2 to the first one
    for (int l = network.nb_layers-2; l >= 0; l--)
    {
        //Set matPos
        matPos -= network.layers[l].nb_neurones;

        double z = 0;
        double sp = 0;
        //For each neurones
        for (size_t n = 0; n < network.layers[l].nb_neurones; n++)
        {
            z = zs[matPos + n];
            double sp = derive(sigmoid, z);
            layerdelta = sp * network.layers[l+1].neurones[n].weights[]
        }
        
    }
    
    
    free(zs);
    free(activations);
}

void Hadamardproduct(double* mat1, double* mat2, double* r, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        r[i] = mat1[i] * mat2[i];
    }
    
}

double* loadmatrixasinputs(struct MatrixUCHAR imgmat, int numberofneurones)
{
    //Convert matrix to inputs list
    double *intput = malloc(numberofneurones*sizeof(double));
    for (size_t x = 0; x < imgmat.columns; x++)
    {
        for (size_t y = 0; y < imgmat.rows; y++)
        {
            intput[x+y] = matrixGetUCHAR(imgmat, x, y);
        }        
    }
    return intput;
}

double cost(struct Network network, double* intput, size_t nb_input, double *outputTarget, size_t nb_outputTarget)
{
    double cost = 0;
    double* outputs = calculateNetworkOutput(network, intput, nb_input);
    for (size_t i = 0; i < nb_outputTarget; i++)
    {
        cost += (pow((outputs[i] - outputTarget[i]), 2))/2;
    }
    return cost;
}