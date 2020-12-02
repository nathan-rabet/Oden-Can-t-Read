#include <stdio.h>
#include <stdlib.h>
#include "src/matrix/matrix.h"
#include "src/image/binarization.h"
#include "src/segmentation/segmentation.h"

int main()
{
    struct Image newImage;

    //Build the image path string
    char *imagepath = "/home/maxou/Documents/gitrepos/noe.topeza/data/images/rota3.png";

    //Load image
    SDL_Surface *image = loadImage(imagepath);
    struct MatrixDOUBLE imagemat = binarization(image);
    SDL_FreeSurface(image);
    show_matrix_to_img(imagemat);
    newImage.matrix = imagemat;

    if (RLSACompleted(newImage, newImage.matrix) != 0)
    {
        newImage.nbTextblocs = GetTextBlock(newImage, newImage.matrix);
    }

    newImage.textblocks = malloc(sizeof(int) * newImage.nbTextblocs);
    //Formation segmentation(+Màj Espaces)
    for (int i = 0; i < newImage.nbTextblocs; i++)
    {
        struct TextBlock *T = &(newImage.textblocks[i]);
        T->nbLines = GetLines(T, newImage.matrix);

        for (int j = 0; j < T->nbLines; j++)
        {
            struct Line *L = &(T->lines[j]);
            L->nbCharacters = Find_Characters(L, newImage.matrix);
            for (int k = 1; k < L->nbCharacters; k++)
            {
                struct Character *A = &(L->characters[k - 1]);
                struct Character *B = &(L->characters[k]);
                struct Character space;
                space.character = ' ';
                if ((B->FirstPoint - A->FirstPoint) >= L->average_space)
                {
                    L->nbCharacters += 1;
                    struct Character *Temp = &(L->characters[k]);
                    *B = space;
                    for (int l = k + 1; l < L->nbCharacters - 1; l++)
                    {
                        struct Character *C = Temp;
                        struct Character *D = &(L->characters[l]);
                        *D = *C;
                    }
                }
            }
        }
    }

    //Parours Type

    for (size_t i = 0; i < newImage.nbTextblocs; i++)
    {
        struct TextBlock *T = &(newImage.textblocks[i]);
        for (size_t j = 0; j < T->nbLines; j++)
        {
            struct Line *L = &(T->lines[j]);
            for (size_t k = 0; k < L->nbCharacters; k++)
            {
                //OCR
                show_matrix_to_img(*(L->characters[k].matrix));
            }
        }
    }

    return 0;
}
