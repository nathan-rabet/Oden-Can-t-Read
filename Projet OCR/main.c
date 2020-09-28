#include <stdlib.h>
#include "lib/bmplib/cbmp.h"
#include <stdio.h>

int main()
{
    char file_path[] = "lib/testbmp/Maxcamnico.bmp";
    BMP* image = bopen(file_path);

    // Gets image width & height in pixels
    int width = get_width(image);
    int height = get_height(image);

    unsigned char matrix[width][height];

    for (int i = 0; i < width; i++) {
    
      for (int j = 0; j < height; j++) {
        unsigned char r, g, b;
        
        get_pixel_rgb(image,i,j, &r, &g, &b);
        matrix[i][j] = ((r + g + b) / 3) < 128 ? 0 : 255;
      }
    }

    bclose(image);

}
