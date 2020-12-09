#include "network.h"
#include "layer.h"
#include "neurone.h"

#include <json-c/json.h>
#include <stdlib.h>
#include <stdio.h>

struct Network* CreateNetwork(struct Layer **layers, size_t nb_layers)
{
    struct Network *network = malloc(sizeof(struct Network));
    network->layers = layers;
    network->nb_layers = nb_layers;
    return network;
}

void FreeNetwork(struct Network *network)
{
    for (size_t i = 0; i < network->nb_layers; i++)
    {
        FreeLayer(network->layers[i]);
    }
    
    //free(network);
}

struct Network* LoadNetworkFromJSON(char jsonFilePath[])
{
    struct Network *network = malloc(sizeof(struct Network));

    char *fileData;
    FILE *f = fopen(jsonFilePath, "rb");

    if (f)
    {
        long length;

        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        fileData = malloc(length);
        if (fileData)
        {
            fread(fileData, 1, length, f);
        }
        fclose(f);
    }

    if (fileData)
    {
        struct json_object *parsed_json = json_tokener_parse(fileData);
        free(fileData);

        // Point the layers
        struct json_object *JSONnb_layers = NULL;
        struct json_object *JSONlayers = NULL;

        struct json_object *JSONnb_input = NULL;

        json_object_object_get_ex(parsed_json, "nb_layers", &JSONnb_layers);
        json_object_object_get_ex(parsed_json, "layers", &JSONlayers);

        json_object_object_get_ex(parsed_json, "nb_inputs", &JSONnb_input);

        int nb_inputs = json_object_get_int(JSONnb_input);

        network->nb_layers = json_object_get_int(JSONnb_layers);

        // ? Layers
        struct Layer **layers = NULL;
        layers = malloc(sizeof(struct Layer) * (network->nb_layers));

        struct Neurone **neurones = NULL;

        // ? First layer special parameters
        neurones = malloc(sizeof(struct Neurone *) * nb_inputs);
        double *uniqueWeight = malloc(sizeof(double));
        *uniqueWeight = 1;
        for (int i = 0; i < nb_inputs; i++)
        {
            neurones[i] = CreateNeurone(uniqueWeight, 0, 0, 1);
        }
        layers[0] = CreateLayer(neurones, nb_inputs);

        for (size_t l = 1; l < network->nb_layers; l++)
        {
            neurones = NULL;

            // Point to a layer l of the network
            struct json_object *JSONlayer = json_object_array_get_idx(JSONlayers, l - 1);

            struct json_object *JSONnb_neurones;
            json_object_object_get_ex(JSONlayer, "nb_neurones", &JSONnb_neurones);

            size_t nb_neurones = (size_t)json_object_get_int(JSONnb_neurones);

            struct json_object *JSONneurones;
            json_object_object_get_ex(JSONlayer, "neurones", &JSONneurones);

            // ? Neurones
            neurones = malloc(sizeof(struct Neurone *) * nb_neurones);
            for (size_t n = 0; n < nb_neurones; n++)
            {
                struct json_object *JSONbias = NULL;
                struct json_object *JSONactivationFunction = NULL;
                struct json_object *JSONnb_weights = NULL;
                struct json_object *JSONweights = NULL;
                struct json_object *JSONneurone = NULL;

                // Point to the neurone n of the layer l
                JSONneurone = json_object_array_get_idx(JSONneurones, n);

                json_object_object_get_ex(JSONneurone, "bias", &JSONbias);
                json_object_object_get_ex(JSONneurone, "activationFunction", &JSONactivationFunction);
                json_object_object_get_ex(JSONneurone, "nb_weights", &JSONnb_weights);
                json_object_object_get_ex(JSONneurone, "weights", &JSONweights);

                double bias = json_object_get_double(JSONbias);
                unsigned char activationFunction = (unsigned char)json_object_get_int(JSONactivationFunction);
                size_t nb_weights = (size_t)json_object_get_int(JSONnb_weights);

                double *weights = malloc(sizeof(double) * nb_weights);
                for (size_t w = 0; w < nb_weights; w++)
                {
                    struct json_object *JSONweight = json_object_array_get_idx(JSONweights, w);
                    weights[w] = json_object_get_double(JSONweight);
                }

                neurones[n] = CreateNeurone(weights, bias, activationFunction, nb_weights);
            }

            layers[l] = CreateLayer(neurones, nb_neurones);
        }

        network->layers = layers;
    }

    else
    {
        fprintf(stderr, "The file '%s' doesn't exist.", jsonFilePath);
    }

    return network;
}

size_t networkNbInput(struct Network *network)
{
    return network->layers[0]->nb_neurones;
}

size_t networkNbOutput(struct Network *network)
{

    size_t nb_output = 0;

    for (size_t i = 0; i < network->nb_layers; i++)
    {
        nb_output = network->layers[i]->nb_neurones;
    }
    return nb_output;
}

size_t networkNbNeurones(struct Network *network)
{

    size_t nb_neurones = 0;

    for (size_t i = 0; i < network->nb_layers; i++)
    {
        nb_neurones += network->layers[i]->nb_neurones;
    }

    return nb_neurones;
}

size_t networkNbWeights(struct Network *network)
{

    size_t nb_weights = 0;

    for (size_t i = 1; i < network->nb_layers; i++)
    {
        size_t weights = network->layers[i-1]->nb_neurones;
        nb_weights += weights * network->layers[i]->nb_neurones;
    }

    return nb_weights;
}

double *calculateNetworkOutput(struct Network *network, double *input)
{
    double *nextInput;
    double *outputNetwork;

    // Entry
    outputNetwork = malloc(sizeof(double) * (network->layers[0]->nb_neurones));
    for (size_t i = 0; i < network->layers[0]->nb_neurones; i++)
    {
        double *entry = &input[i];
        outputNetwork[i] = calculateNeuroneOutput((network->layers[0]->neurones[i]), entry);
    }
    nextInput = outputNetwork;

    // General case
    for (size_t i = 1; i < network->nb_layers; i++)
    {
        outputNetwork = CalculateLayerOutput(network->layers[i], nextInput);
        free(nextInput);
        nextInput = outputNetwork;
    }
    return outputNetwork;
}

void SaveNetworkToJson(struct Network *Network, char jsonFilePath[])
{
    FILE *f = fopen(jsonFilePath, "w");
    size_t nb_i = Network->layers[0]->nb_neurones;
    size_t nb_l = Network->nb_layers;

    fprintf(f, "{\"nb_inputs\":%lu,\n  \t\"nb_layers\":%lu,\n  \t\"layers"
               "\": [\n",
            nb_i, nb_l);

    for (size_t i = 1; i < nb_l; i++)
    {
        size_t nb_n = Network->layers[i]->nb_neurones; //On recup le nb de neurone du layers i
        fprintf(f, " \t\t{\n \t\t\t\"nb_neurones\":%lu,\n  \t\t\t\""
                   "neurones\": [\n",
                nb_n);
        for (size_t j = 0; j < nb_n; j++)
        {
            struct Neurone *Neur_j = (Network->layers[i]->neurones[j]); //On recup les info du neurone j dans le layer i
            size_t aF, nb_w;
            double b;
            b = Neur_j->bias;
            aF = Neur_j->activationFunction;
            nb_w = Network->layers[i - 1]->nb_neurones;
            fprintf(f, "{\n\"bias\":%lf,"
                       "\"activationFunction\":%lu,\"nb_weights\":%lu"
                       ",\n\"weights\":\n[",
                    b, aF, nb_w);
            for (size_t k = 0; k < nb_w; k++)
            {
                double W_k = Neur_j->weights[k]; //On recup les info du poid k du neurone j dans layer i
                fprintf(f, "%lf", W_k);
                if (k < nb_w - 1)
                    fprintf(f, ",");
            }
            fprintf(f, "]}");
            if (j < nb_n - 1)
                fprintf(f, ",");
            fprintf(f, "\n");
        }
        fprintf(f, "]}");
        if (i < nb_l - 1)
            fprintf(f, ",");
        fprintf(f, "\n");
    }
    fprintf(f, " \t]\n}");

    fclose(f);
}

void PrintNetwork(struct Network *network)
{
    printf("Network:\n");
    for (size_t l = 1; l < network->nb_layers; l++)
    {
        printf("Layer n°%lu:\n", l);
        PrintLayer(network->layers[l]);
    }
}