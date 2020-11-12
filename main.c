#include <stdio.h>
#include <stdlib.h>
#include "src/math/analysis.h"

int main()
{
   double a = 220;
   printf("f'(%lf) = %lf\n", a, derive(f, a));
}