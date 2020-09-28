#include <stdio.h>
#include <stdlib.h>
#include "cbmp.h"

int main()
{
    char file_path[] = "Maxcamnico.bmp";
    BMP* image = bopen("max.bmp");

    // Gets image width in pixels
    int width = get_width(image);

    // Gets image height in pixels
    int height = get_height(image);
    printf("width: %d, height: %d", width, height);
    bclose(image);
    for (;;)
    {
        int c = 0;
    }
    
}