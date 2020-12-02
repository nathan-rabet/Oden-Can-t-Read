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
   char afpl[] = {0, 4, 2};
   struct Network *net = generateRandomNetwork(3, npl, afpl);
   PrintNetwork(net);
   char *databasepath = "/home/maxou/Documents/gitrepos/by_class";
   trainingNetwork(net, databasepath, 80, 1, 10000);

   FreeNetwork(net);

   char letter = 'a';

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

   double* inputs = loadDataBase(databasepath, letter, rand() % 1000);

   //Feedforward (run the network with input to set the z and activation values)
   double *output = calculateNetworkOutput(net, inputs);
   free(inputs);
   PrintOuput(output, letters, j-1);

   return 0;
}
