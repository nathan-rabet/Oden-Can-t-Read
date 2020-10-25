#include <stdio.h>
#include <stdlib.h>
#include "segmentation.h"
#include "../matrix/matrix.h"

//To be remplaced/improved with RLSA once ready
TextBlock GetTextBlock(struct MatrixUCHAR m)
{
    int FirstValue=0; // 0 if NoneFound 1 otherwise
    int FirstValueX=0;
    int FirstValueY=0;
    int LastValueX=0;
    int LastValueY=0;
    for (int i=0; i<m.columns;i++)
    {
        
        for (int j=0; j<m.rows;j++)
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
                    j=FirstValueY;
                }
                if(j>LastValueY)
                {
                    LastValueY=j;
                }
            }
        }
    }
    struct MatrixUCHAR newMatrix=createMatrixUCHAR(LastValueX-FirstValueX,LastValueY-FirstValueY);
    for (int i=FirstValueX; i<LastValueX; i++)
    {
        for (int j=FirstValueY; j<LastValueY;j++)
        {
            unsigned char K=matrixGetUCHAR(m,i+FirstValueX,j+FirstValueY);
            matrixSetUCHAR(newMatrix,i,j,K);
        }
  }
    TextBlock newTextBlock;
    newTextBlock.matrix=&newMatrix;
}

int GetLines(TextBlock *tblock, struct MatrixUCHAR m)
{
    int nbLines=0;
    int height=m.rows;
    int width=m.columns;
    // boolean indicating the state of the last iteration
    int isInLine = 0;

    // indicating the index of the starting point of the current line
    int FirstPoint = 0;

    for (int y = 0; y < height; y++)
    {
        
        int Blank_line = 0; //Boolen False if !=0;
        for ( int x = 0; x < width; x++)
        {
            if(matrixGetUCHAR(m,y,x)==0)
            {
                Blank_line+=1;
            } 
        }

        // In the case we have found a new line
        if (isInLine!=0 && Blank_line!=0)
        {
            FirstPoint = y; // for creating Line object later
            isInLine = 1; // <=> True
        }

        // In the case we are at the end of a line
        // (precedent iteration was in a line AND no pixel found in this
        // iteration)
        if (isInLine && Blank_line)
        {
            // We create a Line object, and fill the lines[] array
            Line newLine;
            newLine.FirstPoint = FirstPoint; //first y found
            newLine.LastPoint = y; //current height y
            tblock->lines[nbLines] = newLine;
            nbLines++;
        }
    }

    // Last line
    if (isInLine)
    {
        Line newLine;
        newLine.FirstPoint = FirstPoint;
        newLine.LastPoint = height - 1;
        tblock->lines[nbLines] = newLine;
        nbLines++;
    }
    return nbLines;
}

int Find_Characters(Line *line, struct MatrixUCHAR m)
{
    int upperBound = line->FirstPoint;
    int lowerBound = line->LastPoint;
    int nbCharacters = 0;
    int isInChar = 0;
    int FirstPoint = 0; 
    int height=m.rows;
    int width=m.columns;

    // total space width between characters for computing averageSpace
    int totalSpace = 0;

    for (int x = 0; x < width; x++)
    {
        
        int Blank_Line = 0;//Boolen False if !=0;
        // Counting black pixels
        for (int y = upperBound; y <= lowerBound; y++)
        {
            if(matrixGetUCHAR(m,x,y)==0)
            {
                Blank_Line+=1;
            } 
        }

        // In the case we have found a new character
        if (isInChar==0 && Blank_Line!=0)
        {
            FirstPoint = x;
            isInChar = 1; // <=> True

            if (nbCharacters) // <=> nbCharacters > 0
            {
                // computes the space width between this new character
                // and the previous one
                totalSpace += FirstPoint - line->characters[nbCharacters - 1].LastPoint;
            }
        }

        // In the case we are at the end of a character
        if (isInChar && Blank_Line!=0)
        {
            Character character;
            character.FirstPoint = FirstPoint;
            character.LastPoint = x;
            line->characters[nbCharacters] = character;
            nbCharacters++;
            isInChar = 0; // <=> False

            struct MatrixUCHAR newMatrix=createMatrixUCHAR(character.FirstPoint-character.LastPoint,line->LastPoint-line->FirstPoint);
            for (int i=character.FirstPoint; i<character.LastPoint; i++)
            {
                for (int j=line->FirstPoint; j<line->LastPoint;j++)
                {
                    unsigned char K=matrixGetUCHAR(m,i+character.FirstPoint,j+line->FirstPoint);
                    matrixSetUCHAR(newMatrix,i,j,K);
                }
            }
            character.matrix=&newMatrix;
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


struct MatrixUCHAR *MatrixOfChar(struct MatrixUCHAR m, Line *l, Character *c)
{
    int CHeight=l->LastPoint-l->FirstPoint;//Character Height
    int CWidth=c->LastPoint-c->FirstPoint;//Character Width
    struct MatrixUCHAR newMatrix = createMatrixUCHAR(CHeight, CWidth);
    for (int i=0; i<CHeight;i++)
    {
        for (int j=0;i<CWidth;j++)
        {
            unsigned char Value=matrixGetUCHAR(m,l->FirstPoint+x,c->FirstPoint+y);
            matrixSetUCHAR(newMatrix,x,y,Value);
        }
    }
    return &newMatrix;
}


