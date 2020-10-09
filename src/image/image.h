#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../matrix/matrix.h"
#include "../math/sortalgo.h"

// Load an image in the memory using the SDL library
SDL_Surface* loadImage(char* path);

// Get the color of the pixel (x,y) on an image
Uint32 getPixel(SDL_Surface *image, int x, int y);

int show_matrix_to_img(struct MatrixUCHAR matrix);

int ShowImg(SDL_Surface *image);

SDL_Surface* MedianFilter(SDL_Surface *image, int px);