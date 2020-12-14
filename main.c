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
   char *datasetpath = strcat(getcwd(cwd, sizeof(cwd)), "/data/dataset/DatatSet");
   char *networkpath = strcat(getcwd(cwd1, sizeof(cwd1)), "/newnet2.json");
   char *imagepath = strcat(getcwd(cwd2, sizeof(cwd2)), "/data/images/EPITA.png");

   struct Networks *networks = LoadNetworksFromJSON(networkpath);
   
   struct Characters *Letters_Matrix = Segmentation(imagepath);
   FindCharacters(networks, Letters_Matrix);

   printf("Debut:%s\nVoila\n", Letters_Matrix->AllCharacters);



   FreeNetworks(networks);

   return 0;
}
