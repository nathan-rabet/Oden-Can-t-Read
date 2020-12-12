#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "src/ml/struct/networks.h"
#include "src/ml/train/multithreading/multithreading.h"
#include "src/ml/train/backpropagation.h"

#include "src/segmentation/segmentation.h"
#include "src/miscellaneous/color.h"

int main()
{

    size_t npl[] = {2, 3, 4, 1};
    char afpl[] = {0, 2, 2, 2};
    struct Networks *net = generateRandomNetworks(4, npl, afpl);

    char cwd[PATH_MAX];
    char *datasetpath = strcat(getcwd(cwd, sizeof(cwd)), "/data/dataset/by_class");
 
    time_t timerC = time(NULL);
    
    trainNetworks(net, datasetpath);
    timerC = (time(NULL) - timerC);
    time_t timerT = time(NULL);
    trainNetworksMULTITHREAD(net, datasetpath);
    timerT = (time(NULL) - timerT);

    printf("%sTime for CLASSIC training : %lus\n%s",BLU,timerC,RST);
    printf("%sTime for MULTITHREADING training : %lus\n%s",BLU,timerT,RST);


    return 0;
}