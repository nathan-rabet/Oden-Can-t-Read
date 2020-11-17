#include "analysis.h"

double derive(double (*f)(double), double a)
{
    const double dh = 1.0e-6;
    return (f(a + dh) - f(a)) / dh;
}

double * gradient(double vect[]) {
    //TODO : gradient function
    return vect;
}