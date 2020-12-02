#include <stdio.h>
#include <stdlib.h>
#include "src/matrix/matrix.h"
#include "src/image/binarization.h"
#include "src/segmentation/segmentation.h"



struct Image main(struct MatrixDOUBLE Matrix)
{
    struct Image newImage;
    newImage.matrix=Matrix;

    if(RLSACompleted(newImage,newImage.matrix)==0)
    {
        newImage.nbTextblocs=GetTextBlock;
    }  


    //Formation segmentation(+Màj Espaces)
    for (size_t i=0;i<newImage.nbTextblocs;i++)
    {
        struct TextBlock *T=&(newImage.textblocks[i]);
        T->nbLines=GetLines(T,newImage.matrix);
        
        for(size_t j=0; j<T->nbLines;j++)
        {
            struct Line *L=&(T->lines[j]);
            L->nbCharacters=Find_Characters(L,newImage.matrix);
            for(size_t k=1; k<L->nbCharacters;k++)
            {
                struct Character *A=&(L->characters[k-1]);
                struct Character *B=&(L->characters[k]);
                struct Character space;
                space.character=' ';
                if((B->FirstPoint-A->FirstPoint)>=L->average_space)
                {
                    L->nbCharacters+=1;
                    struct Character *Temp=&(L->characters[k]);
                    *B=space;
                    for(size_t l=k+1; l<L->nbCharacters-1;l++)
                    {
                        struct Character *C=Temp;
                        struct Character *D=&(L->characters[l]);
                        *D=*C;
                    }
                }
            }
        }
    }

    //Parours Type
    /*
    for (size_t i=0;i<newImage.nbTextblocs;i++)
    {
        struct TextBlock *T=&(newImage.textblocks[i]);
        for(size_t j=0; j<T->nbLines;j++)
        {
            struct Line *L=&(T->lines[j]);
            for(size_t k=1; k<L->nbCharacters;k++)
            {
                //OCR
                Free Matrix of Char
            }
        }
    }
    
    */
    
    return newImage;
}


