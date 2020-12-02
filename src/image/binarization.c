#include <stdint.h>
#include "image.h"
#include "../matrix/matrix.h"

struct MatrixDOUBLE binarization(SDL_Surface* image) 
{

    //Create binary matrix
    struct MatrixDOUBLE matrix = createMatrixDOUBLE(image->h,image->w);
    
    Uint32 pixel;
    SDL_Color color;
    for(int i = 0; i < matrix.rows;i++) {
        for(int j = 0; j < matrix.columns;j++) {
          pixel = getPixel(image, j, i);

          SDL_GetRGB(pixel,(image)->format,&color.r, &color.g, &color.b);
          Uint8 bin = (Uint8)((color.r + color.g + color.b) / 3 < 128 ? 0 : 1);
          matrixSetDOUBLE(matrix, i, j,bin);
        }
    }

    return matrix;
}

double* binarizationpointer(SDL_Surface* image)
{
    double* imagebin = malloc(sizeof(double) * image->h * image->w);
    Uint32 pixel;
    SDL_Color color;
    for(int i = 0; i < image->h;i++) {
        for(int j = 0; j < image->w;j++) {
          pixel = getPixel(image, j, i);

          SDL_GetRGB(pixel,(image)->format,&color.r, &color.g, &color.b);
          *(imagebin+ i*image->w +j) = (double)((color.r + color.g + color.b) / 3 < 128 ? 0 : 1);
        }
    }
    return imagebin;
}