#ifndef SEGMENTATION_H
#define SEGMENTATION_H
#include "../matrix/matrix.h"

#define MAX_TBLOCK_NUMBER 15 //for the calloc call
#define MAX_LINE_NUMBER 70 //for the calloc call
#define MAX_CHARACTER_NUMBER 100 //for the calloc call


typedef struct Character
{
    int FirstPoint;
    int LastPoint;
    struct MatrixUCHAR *matrix;
    char character; //empty for now
}Character;

typedef struct Line
{
    int FirstPoint;
    int LastPoint;
    int nbCharacters;
    int average_space; //average space between the characters
    Character *characters; //array of the characters in this line
}Line;

typedef struct TextBlock
{
    struct MatrixUCHAR *matrix; //matrix of the textblock
    Line *lines; //array of the lines of the textblock
} TextBlock;


TextBlock GetTextBlock(struct MatrixUCHAR m);

int GetLines(TextBlock *tblock, struct MatrixUCHAR m);

int GetCharacters(Line *line,struct MatrixUCHAR m);

int *MatrixOfChar(struct MatrixUCHAR m, Line l, Character c);

#endif