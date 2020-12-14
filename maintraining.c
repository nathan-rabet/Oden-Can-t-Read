#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>
#include <limits.h>
#include <string.h>


#include "src/ml/struct/networks.h"
#include "src/ml/train/backpropagation.h"

void mustcall()
{
   srand(time(NULL)); // Initialization, should only be called once.
}


int main()
{   
   mustcall();

   size_t nrpl[] = {4096, 20, 20, 1};
   char afpl[] = {0, 2, 2, 2};
   struct Networks *networks = generateRandomNetworks(4, nrpl, afpl);
   
   //struct Networks *networks = LoadNetworksFromJSON("newnet.json");
   //PrintNetwork(net);

   char cwd[PATH_MAX];
   char * datasetpath = strcat(getcwd(cwd, sizeof(cwd)),"/data/dataset/DatatSet");
   trainNetworks(networks,datasetpath);
   SaveNetworksToJSON(networks, "net.json");
   printf("Done!\n");
   FreeNetworks(networks);

   return 0;
}
