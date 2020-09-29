#include <stdlib.h>
#include "lib/bmplib/cbmp.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    
  void binarization(BMP image,unsigned char *imgMatrix,int width,int height) {
    for (int i = 0; i < width; i++) {
      
      for (int j = 0; j < height; j++) {
        unsigned char *r, *g, *b;
        
        get_pixel_rgb(image,i,j, r, g, b);
        imgMatrix[i][j] = ((r + g + b) / 3) < 128 ? 0 : 255;
        printf("%d",imgMatrix[i][j]); 
      }
     
    }
  }



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
