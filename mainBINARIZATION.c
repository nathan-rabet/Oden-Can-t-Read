#include <stdio.h>
#include <stdlib.h>

#include "src/matrix/matrix.h"
#include "src/image/binarization.h"

int main()
{
  char* file_name = "data/images/tigre.bmp";

  struct MatrixUCHAR bin_mat = binarization(file_name);
  show_matrix_to_img(bin_mat);
}