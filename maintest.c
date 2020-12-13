#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "src/ml/struct/networks.h"
#include "src/ml/train/backpropagation.h"

#include "src/segmentation/segmentation.h"
#include "src/miscellaneous/color.h"

int main()
{
   
   mustcall();
   char cwd[PATH_MAX];
   char * datasetpath = strcat(getcwd(cwd, sizeof(cwd)),"/data/dataset/by_class");
   struct Networks *networks = LoadNetworksFromJSON("/home/maxou/Documents/gitrepos/noe.topeza/networks.json");

   
   for (size_t net = 0; net < networks->nb_networks; net++)
   {
      CalculateScore(networks->networks[net], datasetpath);
   }
   

   FreeNetworks(networks);
   
   return 0;
}
