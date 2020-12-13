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
   char cwd1[PATH_MAX];
   char cwd2[PATH_MAX];
   char *datasetpath = strcat(getcwd(cwd, sizeof(cwd)), "/data/dataset/by_class");
   char *networkpath = strcat(getcwd(cwd1, sizeof(cwd1)), "/networks.json");
   char *imagepath = strcat(getcwd(cwd2, sizeof(cwd2)), "/data/images/epita.png");

   struct Networks *networks = LoadNetworksFromJSON(networkpath);
   
   struct Characters *Letters_Matrix = Segmentation(imagepath);

   FindCharacters(networks, Letters_Matrix);

   printf("%s\n", Letters_Matrix->AllCharacters);



   FreeNetworks(networks);

   return 0;
}
