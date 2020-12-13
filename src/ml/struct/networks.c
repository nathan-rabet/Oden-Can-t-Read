#include <stdlib.h>
#include <json-c/json.h>

#include "network.h"
#include "networks.h"

struct Networks *CreateNetworks(struct Network **networks, size_t nb_networks)
{
    struct Networks *nets = malloc(sizeof(struct Networks));

    nets->networks = networks;
    nets->nb_networks = nb_networks;
    return nets;
}

struct Networks *LoadNetworksFromJSON(char jsonFilePath[])
{
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
        struct Networks *nets = malloc(sizeof(struct Networks));

        struct json_object *parsed_json_networks = json_tokener_parse(fileData);
        free(fileData);

        struct json_object *JSONnb_networks = NULL;
        json_object_object_get_ex(parsed_json_networks, "nb_networks", &JSONnb_networks);
        json_object_object_get_ex(parsed_json_networks, "networks", &parsed_json_networks);

        nets->nb_networks = json_object_get_int(JSONnb_networks);
        nets->networks = malloc(sizeof(struct Network *) * nets->nb_networks);

        for (size_t net = 0; net < nets->nb_networks; net++)
        {
            nets->networks[net] = malloc(sizeof(struct Network));
            // Point the network[net]
            struct json_object *parsed_json_network = json_object_array_get_idx(parsed_json_networks, net);

            // Point the layers
            struct json_object *JSONnb_layers = NULL;
            struct json_object *JSONlayers = NULL;

            struct json_object *JSONnb_input = NULL;
            struct json_object *JSONcharacter = NULL;

            json_object_object_get_ex(parsed_json_network, "nb_layers", &JSONnb_layers);
            json_object_object_get_ex(parsed_json_network, "layers", &JSONlayers);

            json_object_object_get_ex(parsed_json_network, "nb_inputs", &JSONnb_input);
            json_object_object_get_ex(parsed_json_network, "character", &JSONcharacter);

            int nb_inputs = json_object_get_int(JSONnb_input);

            nets->networks[net]->nb_layers = json_object_get_int(JSONnb_layers);
            nets->networks[net]->character = json_object_get_int(JSONcharacter);

            // ? Layers
            nets->networks[net]->layers = malloc(sizeof(struct Layer *) * (nets->networks[net]->nb_layers));

            struct Neurone **neurones = NULL;

            // ? First layer special parameters
            neurones = malloc(sizeof(struct Neurone *) * nb_inputs);
            double *uniqueWeight = malloc(sizeof(double));
            *uniqueWeight = 1;
            for (int i = 0; i < nb_inputs; i++)
            {
                neurones[i] = CreateNeurone(uniqueWeight, 0, 0, 1);
            }
            nets->networks[net]->layers[0] = CreateLayer(neurones, nb_inputs);

            for (size_t l = 1; l < nets->networks[net]->nb_layers; l++)
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

                nets->networks[net]->layers[l] = CreateLayer(neurones, nb_neurones);
            }
        }

        return nets;
    }
    else
    {
        fprintf(stderr, "The file '%s' doesn't exist.", jsonFilePath);
        return NULL;
    }
}

void SaveNetworksToJSON(struct Networks *networks, char jsonFilePath[])
{
    FILE *f = fopen(jsonFilePath, "w");
    fprintf(f, "{\n"
               "\t\"nb_networks\":%lu,\n"
               "\t\"networks\": [\n",
            networks->nb_networks);

    for (size_t net = 0; net < networks->nb_networks; net++)
    {
        size_t nb_input = networks->networks[net]->layers[0]->nb_neurones;
        size_t nb_layers = networks->networks[net]->nb_layers;

        fprintf(f,
                "\t\t{\n"
                "\t\t\t\"character\":%d,\n"
                "\t\t\t\"nb_inputs\":%lu,\n"
                "\t\t\t\"nb_layers\":%lu,\n"
                "\t\t\t\"layers\": [\n",
                networks->networks[net]->character,
                nb_input, nb_layers);

        for (size_t l = 1; l < nb_layers; l++)
        {
            size_t nb_neurones = networks->networks[net]->layers[l]->nb_neurones; //On recup le nb de neurone du layers i
            fprintf(f, "\t\t\t\t{\n"
                       "\t\t\t\t\t\"nb_neurones\":%lu,\n"
                       "\t\t\t\t\t\"neurones\": [\n",
                    nb_neurones);
            for (size_t j = 0; j < nb_neurones; j++)
            {
                struct Neurone *Neur_j = (networks->networks[net]->layers[l]->neurones[j]); //On recup les info du neurone j dans le layer i
                size_t aF, nb_w;
                double b;
                b = Neur_j->bias;
                aF = Neur_j->activationFunction;
                nb_w = networks->networks[net]->layers[l - 1]->nb_neurones;
                fprintf(f, "\t\t\t\t\t\t{\n"
                           "\t\t\t\t\t\t\t\"bias\":%lf, "
                           "\"activationFunction\":%lu, "
                           "\"nb_weights\":%lu,\n"
                           "\t\t\t\t\t\t\t\"weights\": [",
                        b, aF, nb_w);
                for (size_t k = 0; k < nb_w; k++)
                {
                    double W_k = Neur_j->weights[k]; //On recup les info du poid k du neurone j dans layer i
                    fprintf(f, "%lf", W_k);
                    if (k < nb_w - 1)
                        fprintf(f, ", ");
                }
                fprintf(f,
                        "]\n"
                        "\t\t\t\t\t\t}");
                if (j < nb_neurones - 1)
                    fprintf(f, ",");
                fprintf(f, "\n");
            }
            fprintf(f,
                    "\t\t\t\t\t]\n"
                    "\t\t\t\t}");
            if (l < nb_layers - 1)
                fprintf(f, ",");
            fprintf(f, "\n");
        }
        fprintf(f, "\t\t\t]\n"
                   "\t\t}%s\n",
                net != networks->nb_networks - 1 ? "," : "");
    }
    fprintf(f, "\t]\n"
               "}");
    fclose(f);
}

double **calculateNetworksOutput(struct Networks *networks, char input[])
{
    double **output = malloc(sizeof(struct Network *) * networks->nb_networks);

    for (size_t net = 0; net < networks->nb_networks; net++)
    {
        output[net] = malloc(sizeof(double) * networkNbOutput(networks->networks[net]));
        output[net] = calculateNetworkOutput(networks->networks[net], input);
    }

    return output;
}

struct Networks *generateRandomNetworks(size_t nb_layers, size_t nb_neurone_per_layer[], char activation_functions_per_layer[])
{

    struct Networks *networks = CreateNetworks(malloc(sizeof(struct Network *) * CHARSLEN), CHARSLEN);
    for (size_t n = 0; n < networks->nb_networks; n++)
    {
        networks->networks[n] = generateRandomNetwork(nb_layers, nb_neurone_per_layer, activation_functions_per_layer, CHARS[n]);
    }

    return networks;
}

void FreeNetworks(struct Networks *networks)
{
    for (size_t i = 0; i < networks->nb_networks; i++)
    {
        FreeNetwork(networks->networks[i]);
        free(networks->networks[i]);
    }
    free(networks->networks);
    free(networks);
}

char FindCharacter(struct Networks *networks, char* letter_matrix)
{
    size_t index_char = 0;
    double max_sort = 0;
    double **outputs = calculateNetworksOutput(networks, letter_matrix);
    for (size_t i = 0; i < networks->nb_networks; i++)
    {
        printf("Net %c: %f|\n", networks->networks[i]->character, outputs[i][0]);
        if (max_sort < outputs[i][0])
        {
            index_char = i;
            max_sort = outputs[i][0];
        }
    }
    
    return CHARS[index_char];
}

void FindCharacters(struct Networks *networks, struct Characters *character)
{
    for (size_t i = 0; i < character->Nb_Characters - 1; i++)
    {
        if (character->AllCharacters[i] != ' ')
            character->AllCharacters[i] = FindCharacter(networks, character->Character_Binarized_Matrix[i]);
    }
}