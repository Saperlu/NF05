#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fonctions.c"


int main()
{
    if (copierImage() == ERREUR) {
        return ERREUR;
    }
    
    FILE *image;
    image = fopen("imageCodee.ppm", "rb+");
    if (image== NULL)
    {   
        printf("ERREUR : ouverture de l'image impossible\n");
    }
    // Va au début des cases couleurs
    fseek(image, 16 * sizeof(char), SEEK_SET);

    char message[200] = "";
    printf("Rentrez votre message secret\n > ");
    scanf("%s", message);

    int messageBinaire[200][7];
    for (int i = 0; i < strlen(message); i++)
    {
        conversionBinaire(message[i], messageBinaire[i]);
    }


    for (int i = 0; i < strlen(message); i++)
    {
        for (int j = 0; j < 7; j++)
        {
            int nombre = messageBinaire[i][j];
            ecrireCaseCouleur(image, nombre);
        }
        
    }
    
    fclose(image);

    
    

    return 0;
}

