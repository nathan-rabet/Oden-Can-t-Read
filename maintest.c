#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>
#include <limits.h>
#include <string.h>

#include <math.h>


double * softmax1(double list[]) {

    double *softed = malloc(sizeof(double) * 7);
    double max = -INFINITY;
    for (size_t k = 0; k < 7; k++)
    {
        if (max < list[k])
            max = list[k];
    }


    double sum = 0;
    for (size_t i = 0; i < 7; i++)
    {
        sum += exp(list[i] - max);
    }

    double cst = max + log(sum);
    for (size_t j = 0; j < 7; j++)
    {
        softed[j] = exp(list[j]- cst);
    }
    
    return softed;

}

int main()
{
<<<<<<< HEAD
//  size_t npl[] = {NB_INPUTS, 3, 4, 1};
//  char afpl[] = {0, 2, 2, 2};
//  struct Networks *net = generateRandomNetworks(4, npl, afpl);

    struct Networks *net = LoadNetworksFromJSON("/home/maxou/Documents/gitrepos/noe.topeza/net.json");
    

    char cwd[PATH_MAX];
    char *datasetpath = strcat(getcwd(cwd, sizeof(cwd)), "/data/dataset/DatatSet");
     
    CalculateScores(net, datasetpath);
    return 0;
=======
    double z[7] = {1, 3, 2.5, 5, 4, 2};

    double *soft = softmax1(z);

    for (size_t i = 0; i < 7; i++)
    {
        printf("%lf, ",soft[i]);
    }
    printf("\n");

>>>>>>> trainMULTI
}