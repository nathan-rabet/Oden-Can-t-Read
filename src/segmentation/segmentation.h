#ifndef SEGMENTATION_H
#define SEGMENTATION_H
#include "../matrix/matrix.h"
#include "../rotate/rotate.h"
#include "../image/binarization.h"

#define MAX_TBLOCK_NUMBER 15              //for the memory allocation
#define MAX_LINE_NUMBER 70                //for the memory allocation
#define MAX_CHARACTER_NUMBER 200          //for the memory allocation
#define STANDARD_CHARACTER_MATRIX_SIZE 64 //for the memory allocation
#define SPACE_SENSIBILITY 1.2             //for searching spaces

/**
 * @brief Define a visual character in a matrix.
 * 
 */
struct Character
{
    int FirstPoint;
    int LastPoint;
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
};

/**
 * @brief Define a textblock in an image
 * 
 */
struct TextBlock
{
    int FirstX;
    int LastX;
    int FirstY;
    int LastY;
    int nbLines;
};

/**
 * @brief Given image (turned into a matrix)
 * 
 */
struct Image
{
    struct MatrixDOUBLE matrix; //matrix of the textblock
    int nbTextblocs;
};

/**
 * @brief Matrix of characters
 * 
 */
struct Characters
{
    char **Character_Binarized_Matrix;
    char *AllCharacters;
    size_t Nb_Characters;
};

int RLSACompleted();

/**
 * @brief Gets the Text Block object from the Matrix of the image.
 * 
 * @param m The the Matrix of the image.
 * @return TextBlock.
 */
int GetTextBlock(struct MatrixDOUBLE m, struct TextBlock *textblocks);

int GetLines(struct MatrixDOUBLE m, struct TextBlock *T, struct Line *lines);

int GetCharacters(struct MatrixDOUBLE m, struct TextBlock *T, struct Line *L, struct Character *characters);

struct MatrixDOUBLE Resize(struct MatrixDOUBLE m);

struct Characters *Segmentation(char *imagepath);

#endif