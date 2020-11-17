#include <stdint.h>
#include "image.h"
#include "../matrix/matrix.h"

struct MatrixUCHAR binarization(SDL_Surface* image) {

    //Create binary matrix
    struct MatrixUCHAR matrix = createMatrixUCHAR(image->h,image->w);
    
    Uint32 pixel;
    SDL_Color color;
    for(int i = 0; i < matrix.rows;i++) {
        for(int j = 0; j < matrix.columns;j++) {
          pixel = getPixel(image, j, i);

          SDL_GetRGB(pixel,(image)->format,&color.r, &color.g, &color.b);
          Uint8 bin = (Uint8)((color.r + color.g + color.b) / 3 < 128 ? 0 : 1);
          matrixSetUCHAR(matrix, i, j,bin);
        }
    }

    return matrix;
}