#include "sortalgo.h"

int MedianValueINT(int mat[], int matLength) //Buble sort
{
    for (int i = 0; i < matLength; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (mat[j+1] < mat[j])
            {
                int swap = mat[j+1];
                mat[j+1] = mat[j];
                mat[j] = swap;
            }
        }
    }
    return mat[matLength/2];
}