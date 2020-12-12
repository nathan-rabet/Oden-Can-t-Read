#include <stdio.h>
#include <stdlib.h>
#include "src/matrix/matrix.h"
#include "src/image/binarization.h"
#include "src/segmentation/segmentation.h"
#include "src/rotate/rotate.h"

int main()
{
    struct Image newImage;
    //Build the image path string
    char *imagepath = "/Users/lucasaingier/Desktop/noe.topeza/data/images/rota3.png";
    //Load image
    SDL_Surface *image = loadImage(imagepath);
    struct MatrixDOUBLE imagemat = binarization(image);
    newImage.matrix = imagemat;


    int TotalNbCharacter=0;
    struct MatrixDOUBLE *Matrixarray=calloc(MAX_TBLOCK_NUMBER*MAX_LINE_NUMBER*MAX_CHARACTER_NUMBER,sizeof(double)*STANDARD_CHARACTER_MATRIX_SIZE*STANDARD_CHARACTER_MATRIX_SIZE);
    char *AllCharacters=calloc(MAX_TBLOCK_NUMBER*MAX_LINE_NUMBER*MAX_CHARACTER_NUMBER,sizeof(char));


    struct TextBlock *textblocks=calloc(MAX_TBLOCK_NUMBER,sizeof(struct TextBlock));
    int nbTextblocs=GetTextBlock(newImage.matrix,textblocks);
    textblocks=realloc(textblocks,nbTextblocs*sizeof(struct TextBlock));

    for(int i=0; i<nbTextblocs;i++)
    {
        /*
        printf("There is a total of %d Textblocks: \n\n",nbTextblocs);
        */

        struct TextBlock *T=&(textblocks[i]);
        struct Line *lines=calloc(MAX_LINE_NUMBER, sizeof(struct Line));
        int nbLines=GetLines(newImage.matrix,T,lines);
        T->nbLines=nbLines;
        lines=realloc(lines,nbLines*sizeof(struct Line));

        /*
        printf("There is a total of %d lines: \n",nbLines);
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- Lines -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        for(int il=0;il<nbLines;il++)
        {
            printf("Line %d: %d-%d\n",il+1,lines[il].FirstPoint,lines[il].LastPoint);
        }
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        */
       

       for(int j=0; j<nbLines;j++)
       {
           struct Line *L=&(lines[j]);
           struct Character *characters=calloc(MAX_CHARACTER_NUMBER, sizeof(struct Character));
           int nbChara=GetCharacters(newImage.matrix,T,L,characters);
           characters=realloc(characters,nbChara*sizeof(struct Character));
           /*
           printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
           printf("There is a total of %d characters in Line %d.\n",nbChara,j+1);
           */
          for(int k=0; k<nbChara;k++)
          {
              struct Character *C=&(characters[k]);
              /*
              if (k==0)
              {
                  printf("Firstpoint: %d -- ",C->FirstPoint);

              }
              if (k==nbChara-1)
              {
                  printf("Lastpoint: %d\n",C->LastPoint);

              }
              */

             if(k>0 && j==0)
             {
                 struct Character *D=&(characters[k-1]);
                 if((C->FirstPoint-D->LastPoint)>L->average_space)
                 {
                     AllCharacters[TotalNbCharacter]=' ';
                     TotalNbCharacter++;
                   /*
                   printf("There is a space at:\n-Line:%d\n-Character:%d\n----------------\n",j+1,k+1);
                   */
                 }
             }
             
             struct MatrixDOUBLE charMatrix=createMatrixDOUBLE(L->LastPoint-L->FirstPoint+1,C->LastPoint-C->FirstPoint+1);
             for(int i=L->FirstPoint;i<=L->LastPoint;i++)
             {
                 for(int j=C->FirstPoint;j<=C->LastPoint;j++)
                 {
                     double Value=matrixGetDOUBLE(newImage.matrix,i,j);
                     matrixSetDOUBLE(charMatrix,i-L->FirstPoint,j-C->FirstPoint,Value);
                 }
             }

             //Trim charMatrix?
             //Resize Matrix
             struct MatrixDOUBLE newcharMatrix=Resize(charMatrix);
             free(charMatrix.cells);
             //Add to MatrixArray
             Matrixarray[TotalNbCharacter]=newcharMatrix; //Resized
             AllCharacters[TotalNbCharacter]='\0';
             TotalNbCharacter++;
          }
          //After Completing the Line, we add a space char
          AllCharacters[TotalNbCharacter]=' ';
          TotalNbCharacter++;
          //free used data
          free(characters);
       }
       //After Completing the TextBlock, we add a \n char
       AllCharacters[TotalNbCharacter]='\n';
       TotalNbCharacter++;
       //free used data
       free(lines);
    }
    //free used data
    free(textblocks);
    free(newImage.matrix.cells);
    //realloc list of matrix of chara and Allchara
    Matrixarray=realloc(Matrixarray,TotalNbCharacter*sizeof(double)*STANDARD_CHARACTER_MATRIX_SIZE*STANDARD_CHARACTER_MATRIX_SIZE);
    AllCharacters=realloc(AllCharacters,TotalNbCharacter*sizeof(char));

    for(int i=0; i<TotalNbCharacter;i++)
    {
        if(AllCharacters[i]=='\0')
        {
            show_matrix_to_img(Matrixarray[i]);
            printf("Lettre:%d\n",i);
        }
        if(AllCharacters[i]==' ')
        {
            printf("Espace!(%d)\n",i);   
        }
    }

    return 0;
}
