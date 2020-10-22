#include <stdio.h>
#include <stdlib.h>
#include "rotate.h"
#include <math.h>

int diagMatrixSizeINT(struct MatrixINT matrix) 
{
  return (int) sqrt(matrix.columns*matrix.rows);
}

int diagMatrixSizeUCHAR(struct MatrixUCHAR matrix) 
{
  return (int) sqrt(matrix.columns*matrix.rows);
}

MatrixINT rotateINT(struct MatrixINT m, int angle) 
{
  //Conversion of the angle to radians
  angle=angle%360;
  int angle_c=angle*M_PI/180;

  int width = m.columns;
  int height = m.rows;
  int diag = diagMatrixSizeINT(m);

  //Height and Width of the center of the new matrix
  int diag_O=diag/2;

  struct MatrixINT newMatrix = createMatrixINT(diag, diag);
  for (int i=0; i<diag; i++)
  {
    for (int j=0; j<diag;j++)
    {
     matrixSetINT(newMatrix,i,j,255); 
    }
  }

  for (int x=0; x<width; x++)
  {
    for (int y=0; y<height;y++)
    {
      int newX = (x-diag_O)*cos(angle_c) - (y-diag_O)*sin(angle_c)+diag_O;
      int newY = (y-diag_O)*cos(angle_c) + (x-diag_O)*sin(angle_c)+diag_O;
      int Value= *(m.pointer + x * m.columns + y);
      matrixSetINT(newMatrix,newX,newY,Value);
    }
  }
  free(m);
  return newMatrix;
}
MatrixUCHAR rotateU(struct MatrixUCHAR m, int angle) 
{
  //Conversion of the angle to radians
  angle=angle%360;
  int angle_c=angle*M_PI/180;

  int width = m.columns;
  int height = m.rows;
  int diag = diagMatrixSizeUCHAR(m);

  //Height and Width of the center of the new matrix
  int diag_O=diag/2;

  struct MatrixINT newMatrix = createMatrixUCHAR(diag, diag);
  for (int i=0; i<diag; i++)
  {
    for (int j=0; j<diag;j++)
    {
     matrixSetUCHAR(newMatrix,i,j,255); 
    }
  }

  for (int x=0; x<width; x++)
  {
    for (int y=0; y<height;y++)
    {
      int newX = (x-diag_O)*cos(angle_c) - (y-diag_O)*sin(angle_c)+diag_O;
      int newY = (y-diag_O)*cos(angle_c) + (x-diag_O)*sin(angle_c)+diag_O;
      int Value= *(m.pointer + x * m.columns + y);
      matrixSetUCHAR(newMatrix,newX,newY,Value);
    }
  }
  free(m);
  return newMatrix;
}