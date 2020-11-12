#include "analysis.h"

double derive(double (*f)(double), double a)
{
    const double limh = 1.0e-6;
    return (f(a + limh) - f(a)) / limh;
}