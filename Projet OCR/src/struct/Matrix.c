#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

// Matrix creation
struct Matrix CreateMatrix(int x, int y,int sizeof_type)
{
  struct Matrix matrix;
  matrix.rows = x;
  matrix.columns = y;

  matrix.pointer = malloc(sizeof_type*x*y);

  return matrix;
}

// Check if matrix pointer is not NULL
int CheckMatrixValidity(struct Matrix matrix) {

  return (matrix.pointer != NULL);

}

// Check if the coordinates x & y are in a matrix
int CheckMatrixCoord(struct Matrix matrix, int x, int y)
{
  return (x < matrix.rows &&  y < matrix.columns); 
}

void PrintMatrixERROR(int error) {
  switch(error) {
    case 400:
      printf("400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400\n");
      printf("400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400\n");
      printf("                          MATRIX 400 ERROR\n");
      printf(" Can't set a value to a matrix, because wrong coordinates are provided\n");
      printf("400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400\n");
      printf("400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400 400\n");
      break;
    default:
      printf("UNKNOWN ERROR : %d",error);
      break;
  }
}

void MatrixSetUCHAR(struct Matrix matrix, int x, int y, unsigned char value)
{
  if (!(CheckMatrixValidity(matrix) && CheckMatrixCoord(matrix, x, y)))
  {
    PrintMatrixERROR(400);
  } else {
    *(matrix.pointer + x * matrix.rows + y) = value;
  }
}

void MatrixSetFLOAT(struct Matrix matrix, int x, int y, float value)
{
  if (!(CheckMatrixValidity(matrix) && CheckMatrixCoord(matrix, x, y)))
  {
    PrintMatrixERROR(400);
  } else {
    *(matrix.pointer + x * matrix.rows + y) = value;
  }
}

unsigned char MatrixGetUCHAR (struct Matrix matrix, int x, int y) {
  if (!(CheckMatrixValidity(matrix) && CheckMatrixCoord(matrix, x, y)))
  {
    PrintMatrixERROR(400);
    return '\0';
  } else {
    return *(matrix.pointer + x * matrix.rows + y);
  }
}

float MatrixGetFLOAT (struct Matrix matrix, int x, int y) {
  if (!(CheckMatrixValidity(matrix) && CheckMatrixCoord(matrix, x, y)))
  {
    PrintMatrixERROR(400);
    return '\0';
  } else {
    return *(matrix.pointer + x * matrix.rows + y);
  }
}

void PrintMatrixUCHAR(struct Matrix matrix) {
  for (int i = 0; i < matrix.rows; i++)
  {
    for (int j = 0; j < matrix.columns; j++)
    {
      printf("%d\t", MatrixGetUCHAR(matrix,i,j));
    }
    printf("\n");
  }
}

void PrintMatrixFLOAT(struct Matrix matrix) {
  for (int i = 0; i < matrix.rows; i++)
  {
    for (int j = 0; j < matrix.columns; j++)
    {
      printf("%f\t", MatrixGetFLOAT(matrix,i,j));
    }
    printf("\n");
  }
}