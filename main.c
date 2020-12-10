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

   char cwd[PATH_MAX];
   char * path = strcat(getcwd(cwd, sizeof(cwd)),"/data/networks/xor.json");   
   struct Networks *net = LoadNetworksFromJSON(path);
   SaveNetworksToJSON(net,strcat(getcwd(cwd, sizeof(cwd)),"/data/networks/xorTEST.json"));


   return 0;


}
