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
    
    /* Find window size*/
    int coef = 1;
    if (matrix.rows < 780)
    {
        coef = floor(780/matrix.rows);
    }

    SDL_Window* window = NULL;
    window = SDL_CreateWindow
    (
        "Binarized Image", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        matrix.columns * coef,
        matrix.rows * coef,
        SDL_WINDOW_SHOWN
    );

    // Setup renderer
    SDL_Renderer* renderer = NULL;
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

    // Set render color to red ( background will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 0 );

    // Clear winow
    SDL_RenderClear( renderer );


    for(int i = 0; i < matrix.columns;i++) {
        for(int j = 0; j < matrix.rows;j++) {
            Uint32 grey = 0;
            SDL_Rect r = {i * coef, j * coef, coef, coef};

            grey = matrixGetUCHAR(matrix, i, j);
            SDL_SetRenderDrawColor( renderer, grey, grey, grey, 0 );

            SDL_RenderFillRect( renderer, &r );
        }
    }

    // Render the rect to the screen
    SDL_RenderPresent(renderer);


    SDL_Event event;
    int quit = 0;
    while (quit == 0)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        case SDL_QUIT:
            quit = 1;
            break;
        }
    }
    SDL_DestroyWindow(window);

    return EXIT_SUCCESS;
}

int ShowImg(SDL_Surface *image)
{
    
    /* Find window size*/
    int coef = 1;
    if (image->h < 780)
    {
        coef = floor(780/image->h);
    }

    SDL_Window* window = NULL;
    window = SDL_CreateWindow
    (
        "Image", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        image->w * coef,
        image->h * coef,
        SDL_WINDOW_SHOWN
    );

    SDL_BlitSurface( image, NULL, SDL_GetWindowSurface( window ), NULL );

    // Render the rect to the screen
    SDL_UpdateWindowSurface( window );


    SDL_Event event;
    int quit = 0;
    while (quit == 0)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        case SDL_QUIT:
            quit = 1;
            break;
        }
    }

    SDL_DestroyWindow(window);

    return EXIT_SUCCESS;
}

SDL_Surface* MedianFilter(SDL_Surface *image, int px)
{
    for (int i = 1; i < image->w - 1; i++)
    {
        for (int j = 1; j < image->h - 1; j++)
        {
            //Create neighbours pixels matrix
            struct MatrixINT neighboursR = createMatrixINT(8,1);
            struct MatrixINT neighboursG = createMatrixINT(8,1);
            struct MatrixINT neighboursB = createMatrixINT(8,1);

            //Set neighbours pixels
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    if (x!=1 && y!=1)
                    {
                        Uint32 pixel = getPixel(image, i - 1 + x, j - 1 + y);
                        SDL_Color color;
                        SDL_GetRGB(pixel, image->format, &color.r, &color.g, &color.b);
                        matrixSetINT(neighboursR, x*2 + y, 1, color.r);
                        matrixSetINT(neighboursG, x*2 + y, 1, color.g);
                        matrixSetINT(neighboursB, x*2 + y, 1, color.b);
                    }
                }
                
            }

            printf("|");
            printMatrixINT(neighboursR);
            printf("|");
            

            // Search Median value

            // Set pixel value
        }
        
    }
    


    SDL_Rect surface_rect = {0, 0, 100, 100};
    SDL_FillRect(image, &surface_rect, SDL_MapRGB(image->format, 255, 0, 0));

    return image;
}