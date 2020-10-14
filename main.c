#include <stdio.h>
#include <stdlib.h>

#include "src/matrix/matrix.h"
#include "src/math/sortalgo.h"
#include "src/math/sortalgo.c"
#include "src/image/binarization.h"

int main()
{
  char* file_name = "lib/testbmp/tigre.bmp";

  struct MatrixUCHAR mat = binarization(file_name);
  show_matrix_to_img(mat);

  SDL_Quit();
}
