#include "binarization.h"

struct MatrixDOUBLE binarization(SDL_Surface *image, int scale)
{

  //Create binary matrix
  struct MatrixDOUBLE matrix = createMatrixDOUBLE((image->h/scale), (image->w/scale));

  Uint32 pixel;
  SDL_Color color;
  for (int i = 0; i < matrix.rows; i += scale)
  {
    for (int j = 0; j < matrix.columns; j += scale)
    {
      int moy = 0;
      for (int k = 0; k < scale; k++)
      {
        for (int w = 0; w < scale; w++)
        {      
          pixel = getPixel(image, j+k, i+w);

          SDL_GetRGB(pixel, (image)->format, &color.r, &color.g, &color.b);
          moy += color.r + color.g + color.b;
        }
      }
      Uint8 bin = (Uint8)(moy / (3 * scale * scale) < 128 ? 0 : 1);
      matrixSetDOUBLE(matrix, i/scale, j/scale, bin);
    }
  }

  return matrix;
}

double *binarizationpointer(SDL_Surface *image, int scale)
{
  double *imagebin = malloc(sizeof(double) * ((image->h)/scale) * ((image->w)/scale));
  Uint32 pixel;
  SDL_Color color;
  for (int i = 0; i < (image->h); i += scale)
  {
    for (int j = 0; j < (image->w); j += scale)
    {
      int moy = 0;
      for (int k = 0; k < scale; k++)
      {
        for (int w = 0; w < scale; w++)
        {      
          pixel = getPixel(image, j+k, i+w);

          SDL_GetRGB(pixel, (image)->format, &color.r, &color.g, &color.b);
          moy += (int)(color.r + color.g + color.b);
        }
      }
      if ((moy / (3 * scale * scale)) < 128)
        *(imagebin + (i/scale) * ((image->w)/scale) + (j/scale)) = 0;
      else
        *(imagebin + (i/scale) * ((image->w)/scale) + (j/scale)) = 1;
        
    }
  }
  return imagebin;
}