#include "image.h"


SDL_Surface* loadImage(char* path) {
    SDL_Surface *image = IMG_Load(path);

    if (!image) {
        errx(500, "The image at the path '%s'can't be loaded: %s", path, IMG_GetError());
    }

    return image;
}

Uint32 getPixel(SDL_Surface *image, int x, int y)
{
    // Pixel reference
    Uint8 *p = (Uint8*)image->pixels + y * image->pitch + x * image->format->BytesPerPixel;;

    switch (image->format->BytesPerPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
    }
    return *p/24;
}

int show_matrix_to_img(struct MatrixUCHAR matrix)
{
    int quit = 0;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
 

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    /* Create a new Image*/
    SDL_Surface * image = SDL_CreateRGBSurface(0, matrix.columns, matrix.rows, 8, 0, 0, 0, 0);
    SDL_LockSurface(image);
    SDL_FillRect(image, NULL, SDL_MapRGB(image->format, 255, 255, 255));

    
    
    for(int i = 0; i < matrix.columns;i++) {
        for(int j = 0; j < matrix.rows;j++) {
            Uint32 grey = 0;
            SDL_Rect pixel = {i, j, i, j};
            grey = matrixGetUCHAR(matrix, i, j);
            printf("%d : ", grey);
            SDL_FillRect(image, &pixel, SDL_MapRGB(image->format, grey, grey, grey));
        }
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    

    while (quit == 0)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        case SDL_QUIT:
            quit = 1;
            break;
        }
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
 
    SDL_Quit();
 
    return 0;
}