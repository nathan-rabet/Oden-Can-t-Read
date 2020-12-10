#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>
#include <limits.h>
#include <string.h>


#include "src/ml/struct/networks.h"

void mustcall()
{
   srand(time(NULL)); // Initialization, should only be called once.
}


int main()
{   
   mustcall();

   size_t npl[] = {2, 2, 1};
   char afpl[] = {0, 2, 2};
   struct Networks *net = generateRandomNetworks(3, npl, afpl);
   //PrintNetwork(net);

   char cwd[PATH_MAX];
   char * datasetpath = strcat(getcwd(cwd, sizeof(cwd)),"/data/dataset/by_class");
   //trainingNetwork(net, datasetpath , 4, 1, 100000);

   printf("Done!\n");
   FreeNetworks(net);

   return 0;
}
