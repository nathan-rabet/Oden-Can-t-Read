#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "src/ml/struct/network.h"
#include "src/ml/train/generate.h"
#include "src/ml/train/backpropagation.h"

void mustcall()
{
   srand(time(NULL));   // Initialization, should only be called once.
}

int main()
{

   mustcall();

   size_t npl[] = {5,2,3,4};
   char afpl[] = {0,1,2,3};
   struct Network *net = generateRandomNetwork(4,npl,afpl,10000);
   printf("nb_layers : %ld",net->nb_layers);
   char* databasepath = "/home/maxou/Documents/gitrepos/by_class";
   trainingNetwork(net, databasepath, 400, 10, 10);

   //FreeNetwork(&net);

   char letter = 'a';

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

   while (letter != 0)
   {
      printf("Enter a character: ");
      scanf("%c", &letter);
      
      struct MatrixDOUBLE minibatchinput = loadDataBase(databasepath, letter, rand() % 1000);

      //Feedforward (run the network with input to set the z and activation values)
      double *output = calculateNetworkOutput(net, minibatchinput.cells);
      freeMatrixDOUBLE(&minibatchinput);
      letter = 0;
      char w = 0;
      while (letter == 0)
      {
         if (*(output+w) == 1)
         {
            letter = *(letters+w);
         }
         w++;
      }
      
      printf("The AI thinks it's a: %c\n", letter);
   }
   

   return 0;
}