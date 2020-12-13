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

   struct Networks *networks = LoadNetworksFromJSON("newnet.json");
   //PrintNetwork(net);

   char cwd[PATH_MAX];
   char * datasetpath = strcat(getcwd(cwd, sizeof(cwd)),"/data/dataset/DatatSet");
   trainNetworks(networks,datasetpath);
   SaveNetworksToJSON(networks, "newnet2.json");
   printf("Done!\n");
   FreeNetworks(networks);

   return 0;
}
