#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../matrix/matrix.h"
#include "../math/sortalgo.h"

/**
 * @brief Load an image in the memory using the SDL library.
 * 
 * @param path The path of the image to load.
 * @return An SDL_Surface structure.
 */
SDL_Surface* loadImage(char* path);

/**
 * @brief Get the Pixel object of an image.
 * 
 * @param image The image (as an SDL_Surface) 
 * you want to extract a pixel from.
 * @param x The height coordinate (starting from the left-bottom corner).
 * @param y The width coordinate (starting from the left-bottom corner).
 * @return The pixel value as an Uint32.
 */
Uint32 getPixel(SDL_Surface *image, int x, int y);

/**
 * @brief Display an image corresponding to a matrix of 0 and 1.
 * 
 * @param matrix unsigned char based matrix that only 
 * contains 0 and 1.
 * @return 0 if no error, 1 if there is one.
 */
int show_matrix_to_img(struct MatrixUCHAR matrix);

/**
 * @brief Display an SDL_Surface image to the screen
 * 
 * @param image An SDL_Surface
 * @return 0 if no error, 1 if there is one. 
 */
int ShowImg(SDL_Surface *image);

/**
 * @brief Apply the median filter on the image
 * 
 * @param image SDL_Surface to work with
 * @param px number of neighbours 3, 5, 7
 * @return  
 */
SDL_Surface* MedianFilter(SDL_Surface *image, int px);