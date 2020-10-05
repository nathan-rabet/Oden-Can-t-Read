#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "src/matrix/matrix.h"
#include "src/image/image.h"

void binarization(SDL_Surface image, struct MatrixUCHAR matrix) {
    Uint32 pixel;
    SDL_Color color;
    for(int i = 0; i < matrix.rows;i++) {
        for(int j = 0; j < matrix.columns;j++) {
          pixel = getPixel(&image, i, j);

          SDL_GetRGB(pixel,(&image)->format,&color.r, &color.g, &color.b);
          Uint8 bin = (Uint8)((color.r + color.g + color.b) / 3 < 128 ? 0 : 255);
          matrixSetUCHAR(matrix,i,j,bin);
        }
    }
}

int main()
{
  SDL_Surface *image;
  char* file_name = "lib/testbmp/10x10.bmp";

  image = loadImage(file_name);

  /* Create image pixel Matrix */
  struct MatrixUCHAR imgMatrix = createMatrixUCHAR(image->w,image->h);
  binarization(*image,imgMatrix);
  printMatrixUCHAR(imgMatrix);
}
