#include <stdint.h>
#include "image.h"
#include "../matrix/matrix.h"

struct MatrixUCHAR binarization(char path[]) {
    
    SDL_Surface *image = loadImage(path);

    MedianFilter(image,1);

    ShowImg(image);

    struct MatrixUCHAR matrix = createMatrixUCHAR(image->w,image->h);
    
    Uint32 pixel;
    SDL_Color color;
    for(int i = 0; i < matrix.columns;i++) {
        for(int j = 0; j < matrix.rows;j++) {
          pixel = getPixel(image, i, j);

          SDL_GetRGB(pixel,(image)->format,&color.r, &color.g, &color.b);
          Uint8 bin = (Uint8)((color.r + color.g + color.b) / 3 < 128 ? 0 : 255);
          matrixSetUCHAR(matrix,i,j,bin);
        }
    }

    return matrix;
}