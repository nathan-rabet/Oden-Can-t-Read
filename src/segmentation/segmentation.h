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

/**
 * @brief Gets the Text Block object from the Matrix of the image.
 * 
 * @param m The the Matrix of the image.
 * @return TextBlock.
 */
TextBlock GetTextBlock(struct MatrixUCHAR m);

/**
 * @brief Get the Lines object from the Matrix of the TextBlock.
 * 
 * @param tblock TextBlock with lines needed to be found.
 * @param m The Matrix of the TextBlock.
 * @return Number of lines in the TextBlock.
 */
int GetLines(TextBlock *tblock, struct MatrixUCHAR m);

/**
 * @brief Get the Characters object from the Matrix of the TextBlock via the values of the Line.
 * 
 * @param line Line of the current character.
 * @param m The Matrix of the TextBlock.
 * @return The number of characters in the Line.
 */
int Find_Characters(Line *line,struct MatrixUCHAR m);

struct MatrixUCHAR *MatrixOfChar(struct MatrixUCHAR m, Line *l, Character *c);

#endif