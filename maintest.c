#include "src/ml/struct/networks.h"

int main()
{
<<<<<<< HEAD
    size_t npl[] = {2, 3, 4, 1};
    char afpl[] = {0, 2, 2, 2};
    struct Networks *net = generateRandomNetworks(4, npl, afpl);
=======
   
   mustcall();
   char cwd[PATH_MAX];
   char * datasetpath = strcat(getcwd(cwd, sizeof(cwd)),"/data/dataset/by_class");
   struct Networks *networks = LoadNetworksFromJSON("/home/maxou/Documents/gitrepos/noe.topeza/networks.json");

   
   for (size_t net = 0; net < networks->nb_networks; net++)
   {
      CalculateScore(networks->networks[net], datasetpath);
   }
   
>>>>>>> master

    SaveNetworksToJSON(net,"ptin.json");

    struct Networks *net2 = LoadNetworksFromJSON("ptin.json");

    return 0;
}