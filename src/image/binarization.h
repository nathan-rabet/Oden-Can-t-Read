#include <stdint.h>

#include "../matrix/matrix.h"
#include "image.h"


/**
 * @brief Transform a image composed of pixel 
 * (r,g,b) ∈ [0,255]³ to a matrix or unsigned characters
 * M(width,height) with only 1 and 0.
 * 
 * @see 1 correspond to a white pixel
 * and 0 to a black pixel.
 * 
 * @param image Image to binarize.
 * @return The binarized image as a unsigned char matrix.
 */
struct MatrixDOUBLE binarization(SDL_Surface* image, int scale);


char *binarizationpointer(SDL_Surface *image, int scale);