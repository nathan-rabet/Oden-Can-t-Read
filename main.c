#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>
#include <limits.h>
#include <string.h>


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

   size_t npl[] = {2, 2, 1};
   char afpl[] = {0, 2, 2};
   struct Network *net = generateRandomNetwork(3, npl, afpl);
   //PrintNetwork(net);

   char cwd[PATH_MAX];
   char * datasetpath = strcat(getcwd(cwd, sizeof(cwd)),"/data/dataset/by_class");
   trainingNetwork(net, datasetpath , 4, 1, 100000);

   FreeNetwork(net);

   return 0;
}
