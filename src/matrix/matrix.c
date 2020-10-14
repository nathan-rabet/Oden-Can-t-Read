#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

struct MatrixINT createMatrixINT(int x, int y)
{
  struct MatrixINT matrix;
  matrix.rows = x;
  matrix.columns = y;

  matrix.pointer = malloc(sizeof(int)*x*y);

  return matrix;
}

struct MatrixDOUBLE createMatrixDOUBLE(int x, int y)
{
  struct MatrixDOUBLE matrix;
  matrix.rows = x;
  matrix.columns = y;

  matrix.pointer = malloc(sizeof(double)*x*y);

  return matrix;
}

struct MatrixUCHAR createMatrixUCHAR(int x, int y)
{
  struct MatrixUCHAR matrix;
  matrix.rows = x;
  matrix.columns = y;

  matrix.pointer = malloc(sizeof(unsigned char)*x*y);

  return matrix;
}

int checkMatrixINTValidity(struct MatrixINT matrix) {

  return (matrix.pointer != NULL);

}

int checkMatrixDOUBLEValidity(struct MatrixDOUBLE matrix) {

  return (matrix.pointer != NULL);

}

int checkMatrixUCHARValidity(struct MatrixUCHAR matrix) {

  return (matrix.pointer != NULL);

}

int checkMatrixINTCoord(struct MatrixINT matrix, int x, int y)
{
  return (x < matrix.rows &&  y < matrix.columns); 
}

int checkMatrixDOUBLECoord(struct MatrixDOUBLE matrix, int x, int y)
{
  return (x < matrix.rows &&  y < matrix.columns); 
}

int checkMatrixUCHARCoord(struct MatrixUCHAR matrix, int x, int y)
{
  return (x < matrix.rows &&  y < matrix.columns); 
}

void printMatrixERROR(int error) {
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

void matrixSetUCHAR(struct MatrixUCHAR matrix, int x, int y, unsigned char value)
{
  if (!(checkMatrixUCHARValidity(matrix) && checkMatrixUCHARCoord(matrix, x, y)))
  {
    printMatrixERROR(400);
  } else {
    *(matrix.pointer + x * (matrix.columns - 1) + y) = value;
  }
}

void matrixSetDOUBLE(struct MatrixDOUBLE matrix, int x, int y, double value)
{
  if (!(checkMatrixDOUBLEValidity(matrix) && checkMatrixDOUBLECoord(matrix, x, y)))
  {
    printMatrixERROR(400);
  } else {
    *(matrix.pointer + x * (matrix.columns - 1) + y) = value;
  }
}

unsigned char matrixGetUCHAR (struct MatrixUCHAR matrix, int x, int y) {
  if (!(checkMatrixUCHARValidity(matrix) && checkMatrixUCHARCoord(matrix, x, y)))
  {
    printMatrixERROR(400);
    return '\0';
  } else {
    return *(matrix.pointer + x * (matrix.columns - 1) + y);
  }
}

double matrixGetDOUBLE(struct MatrixDOUBLE matrix, int x, int y) {
  if (!(checkMatrixDOUBLEValidity(matrix) && checkMatrixDOUBLECoord(matrix, x, y)))
  {
    printMatrixERROR(400);
    return '\0';
  } else {
    return *(matrix.pointer + x * (matrix.columns - 1) + y);
  }
}

void printMatrixUCHAR(struct MatrixUCHAR matrix) {
  for (int i = 0; i < matrix.rows; i++)
  {
    for (int j = 0; j < matrix.columns; j++)
    {
      printf("%d\t", matrixGetUCHAR(matrix,i,j));
    }
    printf("\n");
  }
}

void printMatrixDOUBLE(struct MatrixDOUBLE matrix) {
  for (int i = 0; i < matrix.rows; i++)
  {
    for (int j = 0; j < matrix.columns; j++)
    {
      printf("%f\t", matrixGetDOUBLE(matrix,i,j));
    }
    printf("\n");
  }
}