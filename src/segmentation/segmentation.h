#ifndef SEGMENTATION_H
#define SEGMENTATION_H
#include "../matrix/matrix.h"


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





void GetTextBlock(struct MatrixUCHAR m);

void GetLines(TextBlock *tblock, struct MatrixUCHAR m);

void GetCharacters(Line *line,struct MatrixUCHAR m);






#endif