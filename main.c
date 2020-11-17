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
   struct Network net = generateRandomNetwork(4,npl,afpl);
   printf("nb_layers : %ld",net.nb_layers);

   trainingNetwork(net, "/home/maxou/Documents/gitrepos/by_class", 200, 50, 10000);

   return 0;
}