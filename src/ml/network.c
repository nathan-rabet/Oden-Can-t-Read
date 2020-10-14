#include "network.h"
#include "layer.h"
#include "neurone.h"

#include <json.h>
#include <stdlib.h>
#include <stdio.h>

struct Network * LoadNetworkFromJSON(char jsonFilePath[]) {    
    struct Network *network = malloc(sizeof(struct Network));

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

        // Point the layers
        struct json_object *JSONnb_layers;
        struct json_object *JSONlayers;

        json_object_object_get_ex(parsed_json,"nb_layers",&JSONnb_layers);
        json_object_object_get_ex(parsed_json,"layers",&JSONlayers);

        int nb_layers = json_object_get_int(JSONnb_layers);
        network->nb_layers = nb_layers;
        // ? Layers
		struct Layer layers[network->nb_layers];
        for (int l = 0; l < network->nb_layers; l++)
        {
            // Point to a layer l of the network
            struct json_object *JSONlayer = json_object_array_get_idx(JSONlayers,l);

            struct json_object *JSONnb_neurones;
            json_object_object_get_ex(JSONlayer,"nb_neurones",&JSONnb_neurones);

            int nb_neurones = json_object_get_int(JSONnb_neurones);


            struct json_object *JSONneurones;
            json_object_object_get_ex(JSONlayer,"neurones",&JSONneurones);

            // ? Neurones
            struct Neurone neurones[nb_neurones];
            for (int n = 0; n < nb_neurones; n++)
            {
                // Point to the neurone n of the layer l
                struct json_object *JSONneurone = json_object_array_get_idx(JSONneurones,n);
                
                struct json_object *JSONbias;
                struct json_object *JSONactivationFunction;
                struct json_object *JSONnb_weights;
                struct json_object *JSONweights;

                json_object_object_get_ex(JSONneurone,"bias",&JSONbias);
                json_object_object_get_ex(JSONneurone,"activationFunction",&JSONactivationFunction);
                json_object_object_get_ex(JSONneurone,"nb_weights",&JSONnb_weights);
                json_object_object_get_ex(JSONneurone,"weights",&JSONweights);

                double bias = json_object_get_double(JSONbias);
                unsigned char activationFunction = (unsigned char) json_object_get_int(JSONactivationFunction);
                int nb_weights = json_object_get_int(JSONnb_weights);

                double weights[nb_weights];
                for (int w = 0; w < nb_weights; w++)
                {
                    struct json_object *JSONweight = json_object_array_get_idx(JSONweights,w);
                    weights[w] = json_object_get_double(JSONweight);
                }

                neurones[n] = CreateNeurone(weights,bias,activationFunction,nb_weights);
            }

            layers[l] = CreateLayer(neurones,nb_neurones);
        }

        network->layers = layers;
        return network;
    }

    else {
        fprintf(stderr, "The file '%s' doesn't exist.", jsonFilePath);
        return network;
    }
}