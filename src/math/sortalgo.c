#include "sortalgo.h"

int MedianValueINT(int mat[], int matLenght) //Buble sort
{
    for (int i = 0; i < matLenght; i++)
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
    return mat[matLenght/2];
}