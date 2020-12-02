#include <stdio.h>
#include <stdlib.h>
#include "segmentation.h"
#include "../matrix/matrix.h"

int RLSACompleted(struct Image Image, struct MatrixDOUBLE m)
{
    return 1;
}
//To be remplaced/improved with RLSA once ready
int GetTextBlock(struct Image Image, struct MatrixDOUBLE m)
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
                    j = FirstValueY;
                }
                if (j > LastValueY)
                {
                    LastValueY = j;
                }
            }
        }
    }
    struct MatrixDOUBLE newMatrix = createMatrixDOUBLE(LastValueX - FirstValueX, LastValueY - FirstValueY);
    for (int i = FirstValueX; i < LastValueX; i++)
    {
        for (int j = FirstValueY; j < LastValueY; j++)
        {
            double K = matrixGetDOUBLE(m, i, j);
            matrixSetDOUBLE(newMatrix, i, j, K);
        }
    }
    struct TextBlock newTextBlock;
    newTextBlock.matrix = &newMatrix;
    Image.textblocks[0] = newTextBlock;
    return 1;
}

int GetLines(struct TextBlock *tblock, struct MatrixDOUBLE m)
{
    int nbLines = 0;
    int height = m.rows;
    int width = m.columns;
    int isInLine = 0;
    int FirstPoint = 0;
    for (int i = 0; i < height; i++)
    {
        int Blank_line = 0; //Boolen False if !=0;
        for (int j = 0; j < width; j++)
        {
            if (matrixGetDOUBLE(m, i, j) == 0)
            {
                Blank_line = 1;
            }
        }

        // In the case we have found a new line
        if (isInLine == 0 && Blank_line != 0)
        {
            FirstPoint = i;
            isInLine = 1; //True
        }

        // In the case we are at the end of a line
        // (precedent iteration was in a line AND no pixel found in this
        // iteration)
        if (isInLine && Blank_line == 0)
        {
            isInLine = 0;
            // We create a Line object, and fill the lines[] array
            struct Line newLine;
            newLine.FirstPoint = FirstPoint; //first y found
            newLine.LastPoint = i;           //current height y
            tblock->lines[nbLines] = newLine;
            nbLines++;
        }
    }
    //Last line
    if (isInLine)
    {
        struct Line newLine;
        newLine.FirstPoint = FirstPoint;
        newLine.LastPoint = height - 1;
        tblock->lines[nbLines] = newLine;
        nbLines++;
    }
    return nbLines;
}

int Find_Characters(struct Line *line, struct MatrixDOUBLE m)
{
    int upperBound = line->FirstPoint;
    int lowerBound = line->LastPoint;
    int nbCharacters = 0;
    int isInChar = 0;
    int FirstPoint = 0;
    int height = m.rows;
    int width = m.columns;

    // total space width between characters for computing averageSpace
    int totalSpace = 0;

    for (int x = 0; x < width; x++)
    {
        int Blank_Line = 0; //Boolen False if !=0;
        // Counting black pixels
        for (int y = upperBound; y <= lowerBound; y++)
        {
            if (matrixGetDOUBLE(m, x, y) == 0)
            {
                Blank_Line = 1;
            }
        }
        // In the case we have found a new character
        if (isInChar == 0 && Blank_Line != 0)
        {
            FirstPoint = x;
            isInChar = 1; // <=> True

            if (nbCharacters)
            {
                // computes the space width between this new character
                // and the previous one
                totalSpace += FirstPoint - line->characters[nbCharacters - 1].LastPoint;
            }
        }

        // In the case we are at the end of a character
        if (isInChar && Blank_Line == 0)
        {
            struct Character character;
            character.FirstPoint = FirstPoint;
            character.LastPoint = x;
            line->characters[nbCharacters] = character;
            nbCharacters++;
            isInChar = 0; // <=> False

            struct MatrixDOUBLE newMatrix = createMatrixDOUBLE(line->LastPoint - line->FirstPoint, character.FirstPoint - character.LastPoint);
            for (int i = line->FirstPoint; i < line->LastPoint; i++)
            {
                for (int j = character.FirstPoint; j < character.LastPoint; j++)
                {
                    double K = matrixGetDOUBLE(m, character.FirstPoint, line->FirstPoint);
                    matrixSetDOUBLE(newMatrix, i, j, K);
                }
            }
            character.matrix = &newMatrix;
        }
    }
    if (isInChar)
    {
        struct Character character;
        character.FirstPoint = FirstPoint;
        character.LastPoint = width;
        line->characters[nbCharacters] = character;
        nbCharacters++;
        struct MatrixDOUBLE newMatrix = createMatrixDOUBLE(line->LastPoint - line->FirstPoint, character.FirstPoint - character.LastPoint);
        for (int i = line->FirstPoint; i < line->LastPoint; i++)
        {
            for (int j = character.FirstPoint; j < character.LastPoint; j++)
            {
                double K = matrixGetDOUBLE(m, character.FirstPoint, line->FirstPoint);
                matrixSetDOUBLE(newMatrix, i, j, K);
            }
        }
    }
    line->nbCharacters = nbCharacters;

    // fills the avergeSpace field once this line is finished
    if (nbCharacters > 1)
    {
        line->average_space = totalSpace / (nbCharacters - 1);
    }
    return nbCharacters;
}
