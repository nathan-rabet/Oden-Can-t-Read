#include <stdlib.h>
#include "lib/bmplib/cbmp.h"
#include <stdio.h>

#include <stdint.h>


unsigned char** binarization(char img_path[]) {
   
  printf("Img gen");
  
   BMP* image = bopen(img_path);
 
   // Gets image width & height in pixels
   int width = get_width(image);
   int height = get_height(image);

    unsigned char** matrix;
    matrix = calloc(width, 1+sizeof(unsigned char*)); // alloc one extra ptr
    for(char i = 0;i < width; i++) {
        matrix[i] = calloc(height, sizeof(unsigned char));
    }
    matrix[width] = NULL;
    for(char i = 0; i < width;i++) {
        for(char j = 0; j < height;j++) {
        unsigned char *r, *g, *b;
 
          get_pixel_rgb(image,i,j, r, g, b);
          matrix[i][j] = (unsigned char)(((uintptr_t)&r + (uintptr_t)&g + (uintptr_t)&b) / 3 < 128 ? 0 : 255);
          printf("%d",matrix[i][j]);
        
        }
    }

    return matrix;
}






int main()
{

printf("test");  
binarization("lib/testbmp/max.bmp");
printf("Ok");
return 0;


if (argc < 2) {
  printf("You must provide an image path as an argument!\n");
  return 1;
}

// Image initialization
BMP *image = bopen(argv[1]);
int width = get_width(image);
int height = get_height(image);

// Initializing binarized matrix
unsigned char *imgMatrix[width][height];

binarization(&image,imgMatrix,width,height);
bclose(image);
}
