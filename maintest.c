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
    double z[7] = {1, 3, 2.5, 5, 4, 2};

    double *soft = softmax1(z);

    for (size_t i = 0; i < 7; i++)
    {
        printf("%lf, ",soft[i]);
    }
    printf("\n");

}