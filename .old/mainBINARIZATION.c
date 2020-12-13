#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/matrix/matrix.h"
#include "src/image/binarization.h"

int main(int agrc, char *argv[])
{
  if (agrc == 2)
  {
    char file_name[100] = "data/images/";
    strcat(file_name, argv[1]);
  

  //Load image
  SDL_Surface *image = loadImage(file_name);

  ShowImg(image);

  image = Grayscale(image);
  ShowImg(image);
  ShowImg(PowerLaw(image, 1, 1.05));
  ShowImg(PowerLaw(image, 1, 25));
  //Apply median filter
  //image = laplacien(image);

   struct MatrixUCHAR bin_mat = binarization(image);
  show_matrix_to_img(bin_mat);
  }
}