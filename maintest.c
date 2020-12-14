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

    size_t npl[] = {NB_INPUTS, 3, 4, 1};
    char afpl[] = {0, 2, 2, 2};
    struct Networks *net = generateRandomNetworks(4, npl, afpl);

    char cwd[PATH_MAX];
    char *datasetpath = strcat(getcwd(cwd, sizeof(cwd)), "/data/dataset/by_class");
     
    trainNetworks(net, datasetpath);
    return 0;
}