#include "network.h"
#include "layer.h"
#include "neurone.h"

#include <json-c/json.h>
#include <stdlib.h>
#include <stdio.h>

struct Network CreateNetwork(struct Layer *layers,size_t nb_layers) {
    struct Network network;
    network.layers = layers;
    network.nb_layers = nb_layers;
    return network;
}

void FreeNetwork(struct Network *network) {
    FreeLayer(network->layers);
    //free(network);
}

struct Network LoadNetworkFromJSON(char jsonFilePath[]) {    
    struct Network network;

    char *fileData;
    FILE *f = fopen (jsonFilePath, "rb");

    if (f)
    {
        long length;

        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        fileData = malloc(length);
        if (fileData)
        {
            fread(fileData, 1, length, f);
        }
        fclose (f);
    }

    if (fileData)
    {
        struct json_object *parsed_json = json_tokener_parse(fileData);
        free(fileData);

        // Point the layers
        struct json_object *JSONnb_layers = NULL;
        struct json_object *JSONlayers = NULL;

        struct json_object *JSONnb_input = NULL;

        json_object_object_get_ex(parsed_json,"nb_layers",&JSONnb_layers);
        json_object_object_get_ex(parsed_json,"layers",&JSONlayers);

        json_object_object_get_ex(parsed_json,"nb_inputs",&JSONnb_input);

        int nb_inputs = json_object_get_int(JSONnb_input);

        network.nb_layers = json_object_get_int(JSONnb_layers);
        
        // ? Layers
		struct Layer *layers = NULL;
        layers = malloc(sizeof(struct Layer) * (network.nb_layers));


        struct Neurone *neurones = NULL;

        // ? First layer special parameters
        neurones = malloc(sizeof(struct Neurone) * nb_inputs);
        double *uniqueWeight = malloc(sizeof(double));
        *uniqueWeight = 1;
        for (int i = 0; i < nb_inputs; i++)
        {
            neurones[i] = CreateNeurone(uniqueWeight,0,0,1);
            neurones[i].nextNeuroneSameLayer = &neurones[i+1];
        }
        neurones[nb_inputs-1].nextNeuroneSameLayer = NULL;
        layers[0] = CreateLayer(neurones,nb_inputs);
        
        for (size_t l = 1; l < network.nb_layers; l++)
        {
            neurones = NULL;

            // Point to a layer l of the network
            struct json_object *JSONlayer = json_object_array_get_idx(JSONlayers,l-1);

            struct json_object *JSONnb_neurones;
            json_object_object_get_ex(JSONlayer,"nb_neurones",&JSONnb_neurones);

            size_t nb_neurones = (size_t) json_object_get_int(JSONnb_neurones);


            struct json_object *JSONneurones;
            json_object_object_get_ex(JSONlayer,"neurones",&JSONneurones);

            // ? Neurones
            neurones = malloc(sizeof(struct Neurone) * nb_neurones);
            for (size_t n = 0; n < nb_neurones; n++)
            {
                struct json_object *JSONbias = NULL;
                struct json_object *JSONactivationFunction = NULL;
                struct json_object *JSONnb_weights = NULL;
                struct json_object *JSONweights = NULL;
                struct json_object *JSONneurone = NULL;

                // Point to the neurone n of the layer l
                JSONneurone = json_object_array_get_idx(JSONneurones,n);

                json_object_object_get_ex(JSONneurone,"bias",&JSONbias);
                json_object_object_get_ex(JSONneurone,"activationFunction",&JSONactivationFunction);
                json_object_object_get_ex(JSONneurone,"nb_weights",&JSONnb_weights);
                json_object_object_get_ex(JSONneurone,"weights",&JSONweights);

                double bias = json_object_get_double(JSONbias);
                unsigned char activationFunction = (unsigned char) json_object_get_int(JSONactivationFunction);
                size_t nb_weights = (size_t) json_object_get_int(JSONnb_weights);

                double *weights = malloc(sizeof(double) * nb_weights);
                for (size_t w = 0; w < nb_weights; w++)
                {
                    struct json_object *JSONweight = json_object_array_get_idx(JSONweights,w);
                    weights[w] = json_object_get_double(JSONweight);
                }

                neurones[n] = CreateNeurone(weights,bias,activationFunction,nb_weights);
                
                // Neurones linking
                if (n >= 1) {
                    neurones[n-1].nextNeuroneSameLayer = &neurones[n];
                }
            }

            neurones[nb_neurones - 1].nextNeuroneSameLayer = NULL;

            layers[l] = CreateLayer(neurones,nb_neurones);
            
            // Layers linking
            layers[l-1].nextLayer = &layers[l];
        }
        layers[network.nb_layers - 1].nextLayer = NULL;

        network.layers = layers;
    }

    else {
        fprintf(stderr, "The file '%s' doesn't exist.", jsonFilePath);
    }
    
    return network;
}

size_t networkNbInput(struct Network *network) {
    return network->layers[0].nb_neurones;
}

size_t networkNbOutput(struct Network *network) {
    
    size_t nb_output = 0;

    struct Layer *workingLayer = network->layers;

    while (workingLayer != NULL) {
        nb_output = workingLayer->nb_neurones;
        workingLayer = workingLayer->nextLayer;
    }
    
    return nb_output;
}

size_t networkNbNeurones(struct Network *network) {
    
    size_t nb_neurones = 0;

    struct Layer *workingLayer = network->layers;

    while (workingLayer != NULL) {
        nb_neurones += workingLayer->nb_neurones;
        workingLayer = workingLayer->nextLayer;
    }
    
    return nb_neurones;
}

size_t networkNbWeights(struct Network *network) {
    
    size_t nb_weights = 0;

    struct Layer *workingLayer = network->layers;

    while (workingLayer != NULL) {
        size_t weights = workingLayer->nb_neurones;
        workingLayer = workingLayer->nextLayer;
        nb_weights += weights * workingLayer->nb_neurones;
    }
    
    return nb_weights;
}

double *calculateNetworkOutput(struct Network *network, double* input) {
    double *nextInput;
    double *outputNetwork;
    
    struct Layer *workingLayer = network->layers;

    // Entry
    outputNetwork = malloc(sizeof(double) * (workingLayer->nb_neurones));
    for (size_t i = 0; i < workingLayer->nb_neurones; i++)
    {
        double *entry = &input[i];
        outputNetwork[i] = calculateNeuroneOutput(workingLayer->neurones[i],entry);
    }
    workingLayer = workingLayer->nextLayer;
    nextInput = outputNetwork;

    // General case
    while(workingLayer != NULL) {
        outputNetwork = CalculateLayerOutput(*workingLayer, nextInput);
        free(nextInput);
        nextInput = outputNetwork;
        workingLayer = workingLayer->nextLayer;
    }
    return outputNetwork;
} 

void SaveNetworkToJson(struct Network *Network, char jsonFilePath[]) {
    FILE *f = fopen (jsonFilePath, "w");
    size_t nb_i = Network->layers[0].nb_neurones;
    size_t nb_l = Network->layers[0].nb_neurones;

    fprintf(f, "{\n    \"nb_inputs\":%lu,\n  \t\"nb_layers\":%lu,\n  \t\"layers"
    "\": [\n", nb_i, nb_l);

    for (size_t i = 1; i < nb_l - 1; i++) {
        size_t nb_n = Network->layers[i].nb_neurones; //On recup le nb de neurone du layers i
        fprintf(f, " \t\t{\n \t\t\t\"nb_neurone\":%lu\n  \t\t\t\""
        "neurones\": [\n", nb_n);
        for (size_t j = 0; j < nb_n; j++) {
            struct Neurone *Neur_j = Network->layers[i].neurones; //On recup les info du neurone j dans le layer i
            size_t b, aF, nb_w;
            b = Neur_j[j].bias;
            aF = Neur_j[j].activationFunction;
            nb_w = Network->layers[i - 1].nb_neurones;
            fprintf(f, " \t\t\t\t{\n \t\t\t\t\t\"bias\":%lu,\n"                     
            "\"activationFunction\":%lu,\t\t\t\t\t \"nb_weights\":%lu"
            ",\n\t\t\t\t\t \"weights\": [\n", b, aF, nb_w);
            for (size_t k = 0; k < nb_w; k++) {
                size_t W_k = Neur_j[j].weights[k];  //On recup les info du poid k du neurone j dans layer i
                fprintf(f, " \t\t\t\t\t\t  %lu", W_k);
                if (k < nb_w - 1)
                    fprintf(f,",");
                fprintf(f,"\n");
            }
            fprintf(f, " \t\t\t\t\t]\n\t\t\t\t\t}");
            if (j < nb_n - 1)
                fprintf(f, ",");
            fprintf(f, "\n");
        }
        fprintf(f, " \t\t\t]\n \t\t}");
        if (i < nb_l - 1)
            fprintf(f, ",");
        fprintf(f, "\n");
    }
    fprintf(f, " \t]\n}");

    fclose(f);
}


void PrintNetwork(struct Network* network)
{
    printf("Network:\n");
    for (size_t l = 1; l < network->nb_layers; l++)
    {
        printf("Layer n°%lu:\n", l);
        PrintLayer(&network->layers[l]);
    }
    

}
