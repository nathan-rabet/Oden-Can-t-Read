#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double doubleRand(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}