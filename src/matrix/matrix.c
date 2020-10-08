#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

struct MatrixINT createMatrixINT(int x, int y)
{
  struct MatrixINT matrix;
  matrix.columns = x;
  matrix.rows = y;

  matrix.pointer = malloc(sizeof(int)*x*y);

  return matrix;
}

struct MatrixFLOAT createMatrixFLOAT(int x, int y)
{
  struct MatrixFLOAT matrix;
  matrix.columns = x;
  matrix.rows = y;

  matrix.pointer = malloc(sizeof(float)*x*y);

  return matrix;
}

struct MatrixUCHAR createMatrixUCHAR(int x, int y)
{
  struct MatrixUCHAR matrix;
  matrix.columns = x;
  matrix.rows = y;

  matrix.pointer = malloc(sizeof(unsigned char)*x*y);

  return matrix;
}

int checkMatrixINTValidity(struct MatrixINT matrix) {

  return (matrix.pointer != NULL);

}

int checkMatrixFLOATValidity(struct MatrixFLOAT matrix) {

  return (matrix.pointer != NULL);

}

int checkMatrixUCHARValidity(struct MatrixUCHAR matrix) {

  return (matrix.pointer != NULL);

}

int checkMatrixINTCoord(struct MatrixINT matrix, int x, int y)
{
  return (x < matrix.columns &&  y < matrix.rows);
}

int checkMatrixFLOATCoord(struct MatrixFLOAT matrix, int x, int y)
{
  return (x < matrix.columns &&  y < matrix.rows); 
}

int checkMatrixUCHARCoord(struct MatrixUCHAR matrix, int x, int y)
{
  return (x < matrix.columns &&  y < matrix.rows);
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
    *(matrix.pointer + x * (matrix.rows - 1) + y) = value;
  }
}

void matrixSetFLOAT(struct MatrixFLOAT matrix, int x, int y, float value)
{
  if (!(checkMatrixFLOATValidity(matrix) && checkMatrixFLOATCoord(matrix, x, y)))
  {
    printMatrixERROR(400);
  } else {
    *(matrix.pointer + x * (matrix.rows - 1) + y) = value;
  }
}

void matrixSetINT(struct MatrixINT matrix, int x, int y, float value)
{
  if (!(checkMatrixINTValidity(matrix) && checkMatrixINTCoord(matrix, x, y)))
  {
    printMatrixERROR(400);
  } else {
    *(matrix.pointer + x * (matrix.rows - 1) + y) = value;
  }
}

unsigned char matrixGetUCHAR (struct MatrixUCHAR matrix, int x, int y) {
  if (!(checkMatrixUCHARValidity(matrix) && checkMatrixUCHARCoord(matrix, x, y)))
  {
    printMatrixERROR(400);
    return '\0';
  } else {
    return *(matrix.pointer + x * (matrix.rows - 1) + y);
  }
}

float matrixGetFLOAT(struct MatrixFLOAT matrix, int x, int y) {
  if (!(checkMatrixFLOATValidity(matrix) && checkMatrixFLOATCoord(matrix, x, y)))
  {
    printMatrixERROR(400);
    return '\0';
  } else {
    return *(matrix.pointer + x * (matrix.rows - 1) + y);
  }
}

int matrixGetINT(struct MatrixINT matrix, int x, int y) {
  if (!(checkMatrixINTValidity(matrix) && checkMatrixINTCoord(matrix, x, y)))
  {
    printMatrixERROR(400);
    return '\0';
  } else {
    return *(matrix.pointer + x * (matrix.rows - 1) + y);
  }
}

void printMatrixUCHAR(struct MatrixUCHAR matrix) {
  for (int i = 0; i < matrix.rows; i++)
  {
    for (int j = 0; j < matrix.columns; j++)
    {
      printf("%d\t", matrixGetUCHAR(matrix,j,i));
    }
    printf("\n");
  }
}

void printMatrixFLOAT(struct MatrixFLOAT matrix) {
  for (int i = 0; i < matrix.rows; i++)
  {
    for (int j = 0; j < matrix.columns; j++)
    {
      printf("%f\t", matrixGetFLOAT(matrix,j,i));
    }
    printf("\n");
  }
}

void printMatrixINT(struct MatrixINT matrix) {
  for (int i = 0; i < matrix.rows; i++)
  {
    for (int j = 0; j < matrix.columns; j++)
    {
      printf("%d\t", matrixGetINT(matrix,j,i));
    }
    printf("\n");
  }
}