#include <stdio.h>
#include <stdlib.h>
#include "segmentation.h"
#include "../matrix/matrix.h"
#include "../rotate/rotate.h"

int RLSACompleted()
{
  return 0;
}
//To be remplaced/improved with RLSA once ready
int GetTextBlock(struct MatrixDOUBLE m, struct TextBlock *textblocks)
{
  int FirstValue = 0; // 0 if NoneFound 1 otherwise
  int FirstValueX = 0;
  int FirstValueY = 0;
  int LastValueX = 0;
  int LastValueY = 0;
  for (int i = 0; i < m.rows; i++)
  {
    for (int j = 0; j < m.columns; j++)
    {
      if (matrixGetDOUBLE(m, i, j) == 0)
      {
        LastValueX = i;
        if (FirstValue == 0)
        {
          FirstValueX = i;
          FirstValueY = j;
          FirstValue = 1;
        }
        if (j < FirstValueY)
        {
          FirstValueY = j;
        }
        if (j > LastValueY)
        {
          LastValueY = j;
        }
      }
    }
  }
  struct TextBlock newTextBlock;
  newTextBlock.FirstX = FirstValueX;
  newTextBlock.LastX = LastValueX;
  newTextBlock.FirstY = FirstValueY;
  newTextBlock.LastY = LastValueY;

  textblocks[0] = newTextBlock;
  return 1;
}

int GetLines(struct MatrixDOUBLE m, struct TextBlock *T, struct Line *lines)
{
  int nbLines = 0;
  int isInLine = 0;
  int FirstPoint = T->FirstX;
  for (int i = T->FirstX; i <= T->LastX; i++)
  {
    int Blank_line = 0; //Boolen False if !=0;

    for (int j = T->FirstY; j <= T->LastY; j++)
    {
      if (matrixGetDOUBLE(m, i, j) == 0)
      {
        Blank_line = 1;
        break;
      }
    }
    //We weren't in a Line and the Line isn't Blank
    if (isInLine == 0 && Blank_line != 0)
    {
      FirstPoint = i;
      isInLine = 1;
    }

    if (isInLine != 0 && Blank_line == 0)
    {
      isInLine = 0;
      struct Line newLine;
      newLine.FirstPoint = FirstPoint;
      newLine.LastPoint = i;
      lines[nbLines] = newLine;
      nbLines++;
    }
  }

  if (isInLine)
  {
    struct Line newLine;
    newLine.FirstPoint = FirstPoint;
    newLine.LastPoint = T->LastX;
    lines[nbLines] = newLine;
    nbLines++;
  }
  return nbLines;
}

int GetCharacters(struct MatrixDOUBLE m, struct TextBlock *T, struct Line *L, struct Character *characters)
{
  int FirstX = L->FirstPoint;
  int LastX = L->LastPoint;
  int FirstY = T->FirstY;
  int LastY = T->LastY;
  int nbCharacters = 0;
  int isInChar = 0;
  int FirstPoint = 0;

  int totalspace = 0;

  for (int i = FirstY; i <= LastY; i++)
  {
    int Blankcolumn = 0;

    for (int j = FirstX; j <= LastX; j++)
    {
      if (matrixGetDOUBLE(m, j, i) == 0)
      {

        Blankcolumn = 1;
        break;
      }
    }

    if (isInChar == 0 && Blankcolumn != 0)
    {
      FirstPoint = i;
      isInChar = 1;
      if (nbCharacters != 0)
      {
        totalspace += FirstPoint - characters[nbCharacters - 1].LastPoint;
      }
    }

    if (isInChar != 0 && Blankcolumn == 0)
    {
      isInChar = 0;
      struct Character newcharacter;
      newcharacter.FirstPoint = FirstPoint;
      newcharacter.LastPoint = i;
      characters[nbCharacters] = newcharacter;
      nbCharacters++;
    }
  }
  L->nbCharacters = nbCharacters;
  if (nbCharacters > 1)
  {
    L->average_space = totalspace / nbCharacters;
  }
  return nbCharacters;
}

struct MatrixDOUBLE Resize(struct MatrixDOUBLE m)
{
  int FirstValue = 0; // 0 if NoneFound 1 otherwise
  int FirstValueX = 0;
  int FirstValueY = 0;
  int LastValueX = 0;
  int LastValueY = 0;
  for (int i = 0; i < m.rows; i++)
  {
    for (int j = 0; j < m.columns; j++)
    {
      if (matrixGetDOUBLE(m, i, j) == 0)
      {
        LastValueX = i;
        if (FirstValue == 0)
        {
          FirstValueX = i;
          FirstValueY = j;
          FirstValue = 1;
        }
        if (j < FirstValueY)
        {
          FirstValueY = j;
        }
        if (j > LastValueY)
        {
          LastValueY = j;
        }
      }
    }
  }

  int cwidth = LastValueY - FirstValueY;
  int cheight = LastValueX - FirstValueX;

  float width = m.columns;
  float height = m.rows;
  struct MatrixDOUBLE newcharMatrix = createMatrixDOUBLE(STANDARD_CHARACTER_MATRIX_SIZE, STANDARD_CHARACTER_MATRIX_SIZE);

  for (int x = 0; x < STANDARD_CHARACTER_MATRIX_SIZE; x++)
  {
    for (int y = 0; y < STANDARD_CHARACTER_MATRIX_SIZE; y++)
    {
      matrixSetDOUBLE(newcharMatrix, x, y, 1);
    }
  }

  if (height > width)
  {
    float Convert = STANDARD_CHARACTER_MATRIX_SIZE / height;
    for (int i = 0; i < STANDARD_CHARACTER_MATRIX_SIZE; i++)
    {
      for (int j = 0; j < width * Convert; j++)
      {
        if (i / Convert < height && j / Convert < width)
        {
          double Value = matrixGetDOUBLE(m, (int)i / Convert, (int)j / Convert);
          if (Value == 0)
          {
            int y = (STANDARD_CHARACTER_MATRIX_SIZE / 2) - (cwidth * Convert / 2) + j;
            matrixSetDOUBLE(newcharMatrix, i, y, Value);
          }
        }
      }
    }
  }

  else
  {
    float Convert = STANDARD_CHARACTER_MATRIX_SIZE / width;
    for (int i = 0; i < width * Convert; i++)
    {
      for (int j = 0; j < STANDARD_CHARACTER_MATRIX_SIZE; j++)
      {
        if (i / Convert < height && j / Convert < width)
        {
          double Value = matrixGetDOUBLE(m, (int)i / Convert, (int)j / Convert);
          if (Value == 0)
          {
            int x = (STANDARD_CHARACTER_MATRIX_SIZE / 2) - (cheight * Convert / 2) + i;
            matrixSetDOUBLE(newcharMatrix, x, j, Value);
          }
        }
      }
    }
  }

  return newcharMatrix;
}