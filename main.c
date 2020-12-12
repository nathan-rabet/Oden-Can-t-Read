#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "src/ml/struct/networks.h"
#include "src/ml/train/backpropagation.h"
#include "src/segmentation/segmentation.h"

void mustcall()
{
   srand(time(NULL)); // Initialization, should only be called once.
}

int main()
{
   mustcall();

   char cwd[PATH_MAX];
   char *datasetpath = strcat(getcwd(cwd, sizeof(cwd)), "/data/dataset/by_class");
   char *networkpath = strcat(getcwd(cwd, sizeof(cwd)), "/networks.json");
   char *imagepath = strcat(getcwd(cwd, sizeof(cwd)), "/data/images/rota3.png");

   size_t npl[] = {NB_INPUTS, 20, 20, 1};
   char afpl[] = {0, 2, 2, 2};
   struct Networks *networks = generateRandomNetworks(4, npl, afpl);
   //struct Networks *networks = LoadNetworksFromJSON(networkpath);
   
   struct Characters *Letters_Matrix = Segmentation(imagepath);

   FindCharacters(networks, Letters_Matrix);

   printf("%s", Letters_Matrix->AllCharacters);



   FreeNetworks(networks);
   free(datasetpath);
   free(networkpath);

   return 0;
}
