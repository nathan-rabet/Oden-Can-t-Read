#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include "src/matrix/matrix.h"
#include "src/rotate/rotate.h"
#include "src/image/binarization.h"
#include "src/ml/network.h"

int main(int argc,char *argv[])
{
   char* file_name = "data/images/tigre.bmp";
 	struct MatrixUCHAR mat = binarization(file_name);
   if(argc != 0)
   {
      int angle = strtoul(argv[1],NULL,10);
      if (angle<0)
      {
         angle=(-1)*angle;
      }
      mat=rotateUCHAR(mat,angle);
      mat=TrimUCHAR(mat);
   }
   show_matrix_to_img(mat);
   SDL_Quit();
   return 0;
} 