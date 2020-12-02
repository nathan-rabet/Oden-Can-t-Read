#ifndef SEGMENTATION_H
#define SEGMENTATION_H
#include "../matrix/matrix.h"

#define MAX_TBLOCK_NUMBER 15 //for the calloc call
#define MAX_LINE_NUMBER 70 //for the calloc call
#define MAX_CHARACTER_NUMBER 100 //for the calloc call

/**
 * @brief Define a visual character in a matrix.
 * 
 */
struct Character
{
    int FirstPoint;
    int LastPoint;
    struct MatrixDOUBLE *matrix;
    char character;
};

/**
 * @brief Define a line in a textblock
 * 
 */
struct Line
{
    int FirstPoint;
    int LastPoint;
    int nbCharacters;
    int average_space; //average space between the characters
    struct Character *characters; //array of the characters in this line
};

/**
 * @brief Define a textblock in an image
 * 
 */
struct TextBlock
{
    struct MatrixDOUBLE *matrix; //matrix of the textblock
    struct Line *lines; //array of the lines of the textblock
    int nbLines;
};

/**
 * @brief Given image (turned into a matrix)
 * 
 */
struct Image
{
    struct MatrixDOUBLE matrix; //matrix of the textblock 
    struct TextBlock *textblocks; // array of the textblocks of the Image found by RLSA/the only tectblock
    int nbTextblocs;
};


int RLSACompleted(struct Image Image, struct MatrixDOUBLE m);


/**
 * @brief Gets the Text Block object from the Matrix of the image.
 * 
 * @param m The the Matrix of the image.
 * @return TextBlock.
 */
int GetTextBlock(struct Image Image, struct MatrixDOUBLE m);

/**
 * @brief Get the Lines object from the Matrix of the TextBlock.
 * 
 * @param tblock TextBlock with lines needed to be found.
 * @param m The Matrix of the TextBlock.
 * @return Number of lines in the TextBlock.
 */
int GetLines(struct TextBlock *tblock, struct MatrixDOUBLE m);

/**
 * @brief Get the Characters object from the Matrix of the TextBlock via the values of the Line.
 * 
 * @param line Line of the current character.
 * @param m The Matrix of the TextBlock.
 * @return The number of characters in the Line.
 */
int Find_Characters(struct Line *line,struct MatrixDOUBLE m);

#endif