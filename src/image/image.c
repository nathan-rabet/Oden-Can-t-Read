#include "image.h"
#include <math.h>


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

int show_matrix_to_img(char *matrix, size_t m_rows, size_t m_columns)
{
    
    /* Find window size*/
    int coef = 1;
    if (m_rows < 780)
    {
        coef = floor(780/m_rows);
    }

    SDL_Window* window = NULL;
    window = SDL_CreateWindow
    (
        "Binarized Image", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        m_columns * coef,
        m_rows * coef,
        SDL_WINDOW_SHOWN
    );

    // Setup renderer
    SDL_Renderer* renderer = NULL;
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

    // Set render color to red ( background will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 0 );

    // Clear winow
    SDL_RenderClear( renderer );


    for(size_t i = 0; i < m_rows;i++) {
        for(size_t j = 0; j < m_columns;j++) {
            Uint32 grey = 0;
            SDL_Rect r = {j * coef, i * coef, coef, coef};

            grey = matrix[i * m_columns + j] * 255;
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
        "Binarized Image", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        image->w * coef,
        image->h * coef,
        SDL_WINDOW_SHOWN
    );

    // Setup renderer
    SDL_Renderer* renderer = NULL;
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

    // Set render color to red ( background will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 0 );

    // Clear winow
    SDL_RenderClear( renderer );


    for(int i = 0; i < image->h;i++) {
        for(int j = 0; j < image->w;j++) {
            Uint32 pixel = 0;
            SDL_Rect r = {j * coef, i * coef, coef, coef};
            SDL_Color color;

            pixel = getPixel(image, j, i);
            SDL_GetRGB(pixel, image->format, &color.r, &color.g, &color.b);
            SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, 0 );

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

SDL_Surface* MedianFilter(SDL_Surface *image, int px)
{
    //Verify px parameter
    int border = 0;
    switch (px)
    {
    case 3:
        border = 1;
        break;
    case 5:
        border = 2;
        break;
    case 7:
        border = 3;
        break;
    
    default:
        return image;
    }


    SDL_Surface *outImage = SDL_CreateRGBSurface(image->flags,image->w,image->h,image->format->BitsPerPixel,image->format->Rmask,image->format->Gmask,image->format->Bmask,image->format->Amask);
    for (int i = 1; i < image->w - border; i++)
    {
        for (int j = 1; j < image->h - border; j++)
        {
            //Create neighbours pixels matrix
            int neighboursR[px*px];
            int neighboursG[px*px];
            int neighboursB[px*px];

            //Set neighbours pixels
            int index = 0;
            for (int x = 0; x < px; x++)
            {
                for (int y = 0; y < px; y++)
                {                                     
                    Uint32 pixel = getPixel(image, i - 1 + x, j - 1 + y);
                    SDL_Color color;
                    SDL_GetRGB(pixel, image->format, &color.r, &color.g, &color.b);
                    neighboursR[index] = color.r;
                    neighboursG[index] = color.g;
                    neighboursB[index] = color.b;
                    index += 1;
                }
                
            }

            

            // Search Median value
            int medianValueR = MedianValueINT(neighboursR, sizeof(neighboursR) / sizeof(neighboursR[0]));
            int medianValueG = MedianValueINT(neighboursG, sizeof(neighboursG) / sizeof(neighboursG[0]));
            int medianValueB = MedianValueINT(neighboursB, sizeof(neighboursB) / sizeof(neighboursB[0]));

            // Set pixel value
            SDL_Rect surface_rect = {i, j, 1, 1};
            SDL_FillRect(outImage, &surface_rect, SDL_MapRGB(image->format, medianValueR, medianValueG, medianValueB));
        }
        
    }
    SDL_FreeSurface(image);
    return outImage;
}

SDL_Surface* Grayscale(SDL_Surface *image)
{
    SDL_Surface *outImage = SDL_CreateRGBSurface(image->flags,image->w,image->h,image->format->BitsPerPixel,image->format->Rmask,image->format->Gmask,image->format->Bmask,image->format->Amask);
    for (int i = 1; i < image->w - 1; i++)
    {
        for (int j = 1; j < image->h - 1; j++)
        {
            SDL_Color color;
            Uint32 pixel = getPixel(image, i, j);
            SDL_GetRGB(pixel, image->format, &color.r, &color.g, &color.b);

            Uint8 newcolor = (0.2126*color.r) + (0.7152*color.g) + (0.0722*color.b);

            // Set pixel value
            SDL_Rect surface_rect = {i, j, 1, 1};
            SDL_FillRect(outImage, &surface_rect, SDL_MapRGB(image->format, newcolor, newcolor, newcolor));
        }
    }
    return outImage;
}

SDL_Surface* PowerLaw(SDL_Surface *image, double c, double y)
{
    SDL_Surface *outImage = SDL_CreateRGBSurface(image->flags,image->w,image->h,image->format->BitsPerPixel,image->format->Rmask,image->format->Gmask,image->format->Bmask,image->format->Amask);
    for (int i = 1; i < image->w - 1; i++)
    {
        for (int j = 1; j < image->h - 1; j++)
        {
            SDL_Color color;
            Uint32 pixel = getPixel(image, i, j);
            SDL_GetRGB(pixel, image->format, &color.r, &color.g, &color.b);

            Uint8 newcolor = 255;
            newcolor = c * pow(color.r, y);
            
            // Set pixel value
            SDL_Rect surface_rect = {i, j, 1, 1};
            SDL_FillRect(outImage, &surface_rect, SDL_MapRGB(image->format, newcolor, newcolor, newcolor));
        }
    }
    SDL_FreeSurface(image);
    return outImage;
}

void TraceRect(SDL_Surface *image, size_t x1, size_t y1, size_t x2, size_t y2)
{
    SDL_Rect surface_rect = {x1 - 2, y1 - 2, 4, y2-y1+4};
    SDL_Rect surface_rect1 = {x1 - 2, y1 - 2, x2-x1+8, 4};
    SDL_Rect surface_rect2 = {x1 - 2, y2 + 2, x2-x1+4, 4};
    SDL_Rect surface_rect3 = {x2 + 2, y1 - 2, 4, y2-y1+4};
    SDL_FillRect(image, &surface_rect, SDL_MapRGB(image->format, 0, 255, 0));
    SDL_FillRect(image, &surface_rect1, SDL_MapRGB(image->format, 0, 255, 0));
    SDL_FillRect(image, &surface_rect2, SDL_MapRGB(image->format, 0, 255, 0));
    SDL_FillRect(image, &surface_rect3, SDL_MapRGB(image->format, 0, 255, 0));
}