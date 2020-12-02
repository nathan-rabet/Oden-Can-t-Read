#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "src/ml/struct/network.h"
#include "src/ml/train/generate.h"
#include "src/ml/train/backpropagation.h"
#include "src/ml/train/generate.h"

void mustcall()
{
   srand(time(NULL)); // Initialization, should only be called once.
}

int main()
{
   
   mustcall();

   size_t npl[] = {16384, 200, 62};
   char afpl[] = {0, 2, 2};
   struct Network network = LoadNetworkFromJSON("/home/maxou/Documents/gitrepos/noe.topeza/coucou.json");
   struct Network *net = &network;
   PrintNetwork(net);
   char *databasepath = "/home/maxou/Documents/gitrepos/by_class";

//Define letters
   char *letters = malloc(62 * sizeof(char));
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

   printf("Calculating for a\n");

   for (char i = 'a'; i < 'z'; i++)
   {
      double* inputs = loadDataBase(databasepath, i, rand() % 1000);

      //Feedforward (run the network with input to set the z and activation values)
      double *output = calculateNetworkOutput(net, inputs);
      free(inputs);
      //PrintLayerOutput(&net->layers[0].neurones[0]);
      //PrintOuput(output, letters, 62);
      for (size_t i = 1; i < 3; i++)
      {
         printf("Layer %lu:\n", i);
         for (size_t n = 0; n < net->layers[i].nb_neurones; n++)
         {
            printf("%f\n", net->layers[i].neurones[n].outputWithoutActivation);
         }
         
      }
      
      free(output);
   }
   

   

   return 0;
}
