#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    

    return 0;
}

