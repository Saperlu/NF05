#include "fonctions.h"
   
int copierImage() {
    FILE *imageSource, *imageCodee;
    size_t n;
    int buffer[TAILLE_BUFFER];

    imageSource = fopen("image.ppm", "rb");
    imageCodee = fopen("imageCodee.ppm", "wb+");
    if (imageSource == NULL || imageCodee ==)
    {
        printf("ERREUR : ouverture des images impossible\n");
        return ERREUR;
    }

    do
    {
        n = fread(buffer, sizeof(int), TAILLE_BUFFER, imageSource);
        fwrite(buffer, sizeof(int), TAILLE_BUFFER, imageCodee);
    } while (n>0);

    fclose(imageSource);
    fclose(imageCodee);
    return SUCCES;
} 
