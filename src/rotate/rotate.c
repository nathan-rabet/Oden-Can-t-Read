#include <stdio.h>
#include <stdlib.h>
#include "rotate.h"
#include <math.h>

int diagMatrixSizeINT(struct MatrixINT matrix) 
{
  return (int) sqrt(pow(matrix.columns,2)+pow(matrix.rows,2));
}

int diagMatrixSizeUCHAR(struct MatrixUCHAR matrix) 
{
  return (int) sqrt(pow(matrix.columns,2)+pow(matrix.rows,2));
}

struct MatrixINT rotateINT(struct MatrixINT m, int angle) 
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

  for (int x=0; x<height; x++)
  {
    for (int y=0; y<width;y++)
    {
      int newX = (x-diag_O)*cos(angle_c) - (y-diag_O)*sin(angle_c)+diag_O;
      int newY = (y-diag_O)*cos(angle_c) + (x-diag_O)*sin(angle_c)+diag_O;
      if (newX >= 0 && newY >= 0 && newX < diag && newY < diag)
      {
        int Value= matrixGetINT(m,x,y);
        matrixSetINT(newMatrix,newX,newY,Value);
      }
      
    }
  }
  free(m.cells);
  return newMatrix;
}

struct MatrixUCHAR rotateUCHAR(struct MatrixUCHAR m, int angle) 
{
  //Conversion of the angle to radians
  angle=angle%360;
  int angle_c=angle*M_PI/180;

  int width = m.columns;
  int height = m.rows;
  int diag = diagMatrixSizeUCHAR(m);

  //Height and Width of the center of the new matrix
  int diag_O=diag/2;

  struct MatrixUCHAR newMatrix = createMatrixUCHAR(diag, diag);
  for (int i=0; i<diag; i++)
  {
    for (int j=0; j<diag;j++)
    {
     matrixSetUCHAR(newMatrix,i,j,255); 
    }
  }

  for (int x=0; x<height; x++)
  {
    for (int y=0; y<width;y++)
    {
      int newX = (x-diag_O)*cos(angle_c) - (y-diag_O)*sin(angle_c)+diag_O;
      int newY = (y-diag_O)*cos(angle_c) + (x-diag_O)*sin(angle_c)+diag_O;
      if (newX >= 0 && newY >= 0 && newX < diag && newY < diag)
      {
        int Value= matrixGetUCHAR(m,x,y);
        matrixSetUCHAR(newMatrix,newX,newY,Value);
      }
    }
  }
  free(m.cells);
  return newMatrix;
}