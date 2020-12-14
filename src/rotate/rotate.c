#include <stdio.h>
#include <stdlib.h>
#include "rotate.h"
#include <math.h>

#define M_PI 3.14159265359

int diagMatrixSizeINT(struct MatrixINT matrix) 
{
  return (int) sqrt(pow(matrix.columns,2)+pow(matrix.rows,2));
}

int diagMatrixSizeDOUBLE(struct MatrixDOUBLE matrix) 
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
  double angle_c=angle*M_PI/180;

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

struct MatrixDOUBLE rotateDOUBLE(struct MatrixDOUBLE m, int angle) 
{
  //Conversion of the angle to radians
  angle=angle%360;
  double angle_c=angle*M_PI/180;

  int width = m.columns;
  int height = m.rows;
  int diag = diagMatrixSizeDOUBLE(m);

  //Height and Width of the center of the new matrix
  int diag_O=diag/2;

  struct MatrixDOUBLE newMatrix = createMatrixDOUBLE(diag, diag);
  for (int i=0; i<diag; i++)
  {
    for (int j=0; j<diag;j++)
    {
     matrixSetDOUBLE(newMatrix,i,j,255); 
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
        int Value= matrixGetDOUBLE(m,x,y);
        matrixSetDOUBLE(newMatrix,newX,newY,Value);
      }
    }
  }
  return newMatrix;
}

struct MatrixUCHAR rotateUCHAR(struct MatrixUCHAR m, int angle) 
{
  //Conversion of the angle to radians
  angle=angle%360;
  double angle_c=angle*M_PI/180;

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
  return newMatrix;
}

struct MatrixUCHAR TrimUCHAR(struct MatrixUCHAR m)
{
  int FirstValue=0; // 0 if NoneFound 1 otherwise
  int FirstValueX=0;
  int FirstValueY=0;
  int LastValueX=0;
  int LastValueY=0;
  for (int i=0; i<m.rows;i++)
  {
    for (int j=0; j<m.columns;j++)
    {
      if (matrixGetUCHAR(m,i,j)==0)
      {
        LastValueX=i;
        if (FirstValue==0)
        {
          FirstValueX=i;
          FirstValueY=j;
          FirstValue=1;
        }
        if(j<FirstValueY)
        {
          FirstValueY=j;
        }
        if(j>LastValueY)
        {
          LastValueY=j;
        }
      }
    }
  }

  struct MatrixUCHAR newMatrix=createMatrixUCHAR(LastValueX-FirstValueX+1,LastValueY-FirstValueY+1);
  for (int i=0; i<LastValueX-FirstValueX+1; i++)
  {
    for (int j=0; j<LastValueY-FirstValueY+1;j++)
    {
      unsigned char K=matrixGetUCHAR(m,i+FirstValueX,j+FirstValueY);
      matrixSetUCHAR(newMatrix,i,j,K);
    }
  }
  free(m.cells);
  return newMatrix;
}

struct MatrixDOUBLE TrimDOUBLE(struct MatrixDOUBLE m)
{
  int FirstValue=0; // 0 if NoneFound 1 otherwise
  int FirstValueX=0;
  int FirstValueY=0;
  int LastValueX=0;
  int LastValueY=0;
  for (int i=0; i<m.rows;i++)
  {
    for (int j=0; j<m.columns;j++)
    {
      if (matrixGetDOUBLE(m,i,j)==0)
      {
        LastValueX=i;
        if (FirstValue==0)
        {
          FirstValueX=i;
          FirstValueY=j;
          FirstValue=1;
        }
        if(j<FirstValueY)
        {
          FirstValueY=j;
        }
        if(j>LastValueY)
        {
          LastValueY=j;
        }
      }
    }
  }
  
  struct MatrixDOUBLE newMatrix=createMatrixDOUBLE(LastValueX-FirstValueX+1,LastValueY-FirstValueY+1);
  for (int i=0; i<LastValueX-FirstValueX+1; i++)
  {
    for (int j=0; j<LastValueY-FirstValueY+1;j++)
    {
      unsigned char K=matrixGetDOUBLE(m,i+FirstValueX,j+FirstValueY);
      matrixSetDOUBLE(newMatrix,i,j,K);
    }
  }
  free(m.cells);
  return newMatrix;
}