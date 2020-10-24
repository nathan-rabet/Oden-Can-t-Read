#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
#include "src/matrix/matrix.h"
#include "src/segmentation/segmentation.h"
#include "src/image/binarization.h"
#include "src/ml/network.h"

/*int main()
{
	char* file_name = "data/networks/xor.json";

	struct Network net = LoadNetworkFromJSON(file_name);

	for (double i = 0; i <= 1; i++)
	{
		for (double j = 0; j <= 1; j++)
		{
			double dataInput[2] = {i,j};
			printf("XOR(%lf,%lf) => %lf\n",i,j,*CalculateNetworkOutput(net, dataInput));
		}		
	}
	
}
*/



int main()
{
	char* file_name = "test1.bmp";
	struct MatrixUCHAR mat = binarization(file_name);
   show_matrix_to_img(mat);
   SDL_Quit();

   //Segmentation//
   TextBlock *Tblock=calloc(MAX_TBLOCK_NUMBER,sizeof(Tblock));
   //Détection blocS de textes à réaliser
   //Dans ce cas lancer boucle for pour chaque bloc
   Line *lines = calloc(MAX_LINE_NUMBER, sizeof(Line));
   int nblines=GetLines(Tblock,mat);
   for (int i=0;i<nblines;i++)
   {
      Line *l=&lines[i];
      l->characters=calloc(MAX_CHARACTER_NUMBER,sizeof(Character));
      int nbChara=GetCharacters(l,mat);
      for (int j=0; j<nbChara;j++)
      {
         Character *c=&(l->characters[i]);
         c->matrix=MatrixOfChar(mat,l,c);
      }
   }

   //Ajouter boucle pour blocS texte
   for (int u=0;u<=nblines;u++)
   {
      for (int v=0; v<Tblock->lines[u].nbCharacters;v++)
      {
         //Analyse
      }
   }
}