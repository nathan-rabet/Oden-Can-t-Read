#include <stdio.h>
#include <stdlib.h>
#include "segmentation.h"

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

struct Characters *Segmentation(char *imagepath)
{
    struct Image newImage;
    //Load image
    SDL_Surface *image = loadImage(imagepath);
    struct MatrixDOUBLE imagemat = binarization(image, 1);
    newImage.matrix = imagemat;

    int TotalNbCharacter = 0;
    struct MatrixDOUBLE *Matrixarray = calloc(MAX_TBLOCK_NUMBER * MAX_LINE_NUMBER * MAX_CHARACTER_NUMBER, sizeof(double) * STANDARD_CHARACTER_MATRIX_SIZE * STANDARD_CHARACTER_MATRIX_SIZE);
    char *AllCharacters = calloc(MAX_TBLOCK_NUMBER * MAX_LINE_NUMBER * MAX_CHARACTER_NUMBER, sizeof(char));

    struct TextBlock *textblocks = calloc(MAX_TBLOCK_NUMBER, sizeof(struct TextBlock));
    int nbTextblocs = GetTextBlock(newImage.matrix, textblocks);
    textblocks = realloc(textblocks, nbTextblocs * sizeof(struct TextBlock));

    for (int i = 0; i < nbTextblocs; i++)
    {
        /*
        printf("There is a total of %d Textblocks: \n\n",nbTextblocs);
        */

        struct TextBlock *T = &(textblocks[i]);
        struct Line *lines = calloc(MAX_LINE_NUMBER, sizeof(struct Line));
        int nbLines = GetLines(newImage.matrix, T, lines);
        T->nbLines = nbLines;
        lines = realloc(lines, nbLines * sizeof(struct Line));

        /*
        printf("There is a total of %d lines: \n",nbLines);
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- Lines -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        for(int il=0;il<nbLines;il++)
        {
            printf("Line %d: %d-%d\n",il+1,lines[il].FirstPoint,lines[il].LastPoint);
        }
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        */

        for (int j = 0; j < nbLines; j++)
        {
            struct Line *L = &(lines[j]);
            struct Character *characters = calloc(MAX_CHARACTER_NUMBER, sizeof(struct Character));
            int nbChara = GetCharacters(newImage.matrix, T, L, characters);
            characters = realloc(characters, nbChara * sizeof(struct Character));
            /*
           printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
           printf("There is a total of %d characters in Line %d.\n",nbChara,j+1);
           */
            for (int k = 0; k < nbChara; k++)
            {
                struct Character *C = &(characters[k]);
                /*
              if (k==0)
              {
                  printf("Firstpoint: %d -- ",C->FirstPoint);

              }
              if (k==nbChara-1)
              {
                  printf("Lastpoint: %d\n",C->LastPoint);

              }
              */

                if (k > 0 && j == 0)
                {
                    struct Character *D = &(characters[k - 1]);
                    if ((C->FirstPoint - D->LastPoint) > L->average_space)
                    {
                        AllCharacters[TotalNbCharacter] = ' ';
                        TotalNbCharacter++;
                        /*
                   printf("There is a space at:\n-Line:%d\n-Character:%d\n----------------\n",j+1,k+1);
                   */
                    }
                }

                struct MatrixDOUBLE charMatrix = createMatrixDOUBLE(L->LastPoint - L->FirstPoint + 1, C->LastPoint - C->FirstPoint + 1);
                for (int i = L->FirstPoint; i <= L->LastPoint; i++)
                {
                    for (int j = C->FirstPoint; j <= C->LastPoint; j++)
                    {
                        double Value = matrixGetDOUBLE(newImage.matrix, i, j);
                        matrixSetDOUBLE(charMatrix, i - L->FirstPoint, j - C->FirstPoint, Value);
                    }
                }

                //Trim charMatrix?
                //Resize Matrix
                struct MatrixDOUBLE newcharMatrix = Resize(charMatrix);
                free(charMatrix.cells);
                //Add to MatrixArray
                Matrixarray[TotalNbCharacter] = newcharMatrix; //Resized
                AllCharacters[TotalNbCharacter] = '\0';
                TotalNbCharacter++;
            }
            //After Completing the Line, we add a space char
            AllCharacters[TotalNbCharacter] = ' ';
            TotalNbCharacter++;
            //free used data
            free(characters);
        }
        //After Completing the TextBlock, we add a \n char
        AllCharacters[TotalNbCharacter] = '\n';
        TotalNbCharacter++;
        AllCharacters[TotalNbCharacter] = '\0';
        //free used data
        free(lines);
    }
    //free used data
    free(textblocks);
    free(newImage.matrix.cells);
    //realloc list of matrix of chara and Allchara
    Matrixarray = realloc(Matrixarray, TotalNbCharacter * sizeof(double) * STANDARD_CHARACTER_MATRIX_SIZE * STANDARD_CHARACTER_MATRIX_SIZE);
    AllCharacters = realloc(AllCharacters, TotalNbCharacter * sizeof(char));

    //Convert Mat
    char **Character_Binarized_Matrix = malloc(sizeof(char *) * TotalNbCharacter);
    for (size_t i = 0; i < (size_t)TotalNbCharacter; i++)
    {
        size_t col = Matrixarray[i].columns;
        size_t row = Matrixarray[i].rows;
        char *charactermat = malloc(col * row * sizeof(char));
        //Convert img
        for (size_t x = 0; x < col; x++)
        {
            for (size_t y = 0; y < row; y++)
            {
                charactermat[x * row + y] = matrixGetDOUBLE(Matrixarray[i], x, y);
            }
        }
        Character_Binarized_Matrix[i] = charactermat;
    }


    struct Characters * chars = malloc(sizeof(struct Characters));
    chars->AllCharacters = AllCharacters;
    chars->Character_Binarized_Matrix = Character_Binarized_Matrix;
    chars->Nb_Characters = (size_t)TotalNbCharacter;
    
    /*
    for (size_t i = 0; i < (size_t)TotalNbCharacter; i++)
    {
      show_matrix_to_img(Character_Binarized_Matrix[i], STANDARD_CHARACTER_MATRIX_SIZE, STANDARD_CHARACTER_MATRIX_SIZE);
    }
    */
    

    return chars;
}