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

<<<<<<< HEAD
   //size_t nrpl[] = {NB_INPUTS, 15, 15, 1};
   //char afpl[] = {0, 2, 2, 2};
   //struct Networks *networks = generateRandomNetworks(4, nrpl, afpl);
=======
   size_t nrpl[] = {NB_INPUTS, 30, 30};
   char afpl[] = {0, 5, 5, 2};
   struct Networks *networks = generateRandomNetworks(4, nrpl, afpl);
>>>>>>> f9d00715cfb7b1306e7277791b05f4c01bbd4ea9
   
   struct Networks *networks = LoadNetworksFromJSON("data/networks/~training/network_1608004356.json");
   //PrintNetwork(net);

   char cwd[PATH_MAX];
   char * datasetpath = strcat(getcwd(cwd, sizeof(cwd)),"/data/dataset");
   printf("Loading all dataset...");
   trainNetworks(networks,datasetpath);
   SaveNetworksToJSON(networks, "net.json");
   printf("Done!\n");
   FreeNetworks(networks);

   return 0;
}
