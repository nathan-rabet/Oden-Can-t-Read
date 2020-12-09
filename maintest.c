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

   size_t npl[] = {784, 200, 62};
   char afpl[] = {0, 2, 2};
   struct Network *net = LoadNetworkFromJSON("/home/maxou/Documents/gitrepos/noe.topeza/network.1000minibatch0.json");
   //struct Network *net = generateRandomNetwork(3, npl, afpl);
   //PrintNetwork(net);
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

   printf("Calculating score...\n");
   int numberoftest = 1000;
   int sumoftest = 0;
   for (int i = 0; i < numberoftest; i++)
   {
      int letter = rand() % 62;
      double* inputs = loadDataBase(databasepath, letters[letter], rand() % 1000);

      //Feedforward (run the network with input to set the z and activation values)
      double *outputs = calculateNetworkOutput(net, inputs);
      free(inputs);
      //PrintLayerOutput(&net->layers[0]);
      PrintOuput(outputs, letters, 62);

      double max = 0;
      int maxindex = 0;
      for (size_t output = 0; output < 62; output++)
      {
         if (outputs[output] > max)
         {
            max = outputs[output];
            maxindex = output;
         }
      }
      if(letter == maxindex)
         sumoftest += 1;
      //printf("max = %lf\n\n", max);
      
      free(outputs);
   }
   

   printf("AI guess correctly %d%% letters. [%d/%d]\n", ((100*sumoftest)/numberoftest), sumoftest, numberoftest);

   return 0;
}
