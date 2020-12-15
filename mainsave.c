#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "src/ml/struct/network.h"
#include "src/ml/train/generate.h"
#include "src/ml/train/backpropagation.h"


int main()
{
    char* loadpath = "/home/scarefire/Gitwork/noe.topeza/"
    "data/networks/xor.json";
    struct Network net = LoadNetworkFromJSON(loadpath);
    printf("Network recup");
    char* savepath = "/home/scarefire/Gitwork/noe.topeza/tkt_çavabiensepasser.json";
    SaveNetworkToJson(&net, savepath);
    printf("Network saved");

   

   return 0;
}
