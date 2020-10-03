#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "src/matrix/matrix.h"
#include "src/image/image.h"

void binarization(SDL_Surface image, struct MatrixUCHAR matrix) {
    for(int i = 0; i < matrix.rows;i++) {
        for(int j = 0; j < matrix.columns;j++) {
          Uint32 pixel = getPixel(&image,i,j);
          Uint8 r, g, b;

          SDL_GetRGB(pixel,(&image)->format,&r,&g,&b);
          Uint8 bin = (Uint8)(((uintptr_t)r + (uintptr_t)g + (uintptr_t)b) / 3 < 128 ? 0 : 255);
          matrixSetUCHAR(matrix,i,j,bin);
        }
    }
}

int main()
{
  SDL_Surface *image = loadImage("/home/nathan/Documents/EPITA/OCR/lib/testbmp/max.bmp");
  struct MatrixUCHAR imgMatrix = createMatrixUCHAR(image->w,image->h);

binarization(*image,imgMatrix);
}
