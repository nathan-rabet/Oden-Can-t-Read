#include <stdlib.h>
#include "lib/bmplib/cbmp.h"
#include <stdio.h>

#include <stdint.h>
#include "src/struct/Matrix.h"

unsigned char** binarization(BMP* image, struct Matrix matrix) {

    for(char i = 0; i < matrix.rows;i++) {
        for(char j = 0; j < matrix.columns;j++) {
        unsigned char *r, *g, *b;
          get_pixel_rgb(image,i,j, r, g, b);
          MatrixSetUCHAR(matrix,i,j,(unsigned char)(((uintptr_t)&r + (uintptr_t)&g + (uintptr_t)&b) / 3 < 128 ? 0 : 255));
        }
    }

    PrintMatrixUCHAR(matrix);
}

int main()
{

  BMP* image = bopen("lib/testbmp/max.bmp");
 
  // Gets image width & height in pixels
  int width = get_width(image);
  int height = get_height(image);

  struct Matrix imgMatrix = CreateMatrix(width,height,sizeof(char));


binarization(image,imgMatrix);
bclose(image);
}
