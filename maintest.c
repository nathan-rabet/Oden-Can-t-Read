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
   char cwd[PATH_MAX];
   char * datasetpath = strcat(getcwd(cwd, sizeof(cwd)),"/data/dataset/by_class");
   //struct Networks *networks = LoadNetworksFromJSON("/home/maxou/Documents/gitrepos/noe.topeza/networks.json");
   
   
   size_t npl[] = {NB_INPUTS, 20, 20, 1};
   char afpl[] = {0, 2, 2, 2};
   struct Networks *networks = generateRandomNetworks(4, npl, afpl);

   /*
   for (size_t net = 0; net < networks->nb_networks; net++)
   {
      CalculateScore(networks->networks[net], datasetpath);
   }
   */

   FreeNetworks(networks);
   

   

   return 0;
}
