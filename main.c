#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>
#include <limits.h>
#include <string.h>


#include "src/ml/struct/networks.h"
#include "src/ml/train/multithreading/multithreading.h"

int main()
{   
   srand(time(NULL)); // Initialization, should only be called once.

   size_t npl[] = {NB_INPUTS, 20, 20, 1};
   char afpl[] = {0, 2, 2, 2};
   struct Networks *net = generateRandomNetworks(4, npl, afpl);
   //PrintNetwork(net);

   char cwd[PATH_MAX];
   char * datasetpath = strcat(getcwd(cwd, sizeof(cwd)),"/data/dataset/by_class");
   trainNetworksMULTITHREAD(net,datasetpath);

   printf("Done!\n");
   FreeNetworks(net);

   return 0;
}
