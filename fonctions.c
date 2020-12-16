#include "fonctions.h"
   
int copierImage() {
    FILE *imageSource, *imageCodee;
    size_t n;
    int buffer[TAILLE_BUFFER];

    imageSource = fopen("image.ppm", "rb");
    imageCodee = fopen("imageCodee.ppm", "wb+");
    if (imageSource == NULL || imageCodee == NULL)
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

void conversionBinaire(char caractere, int messageBinaire[]) {
    int ascii = (int) caractere;
    for (int i = 0; i < 7; i++) messageBinaire[i] = 0;
    
    decimalToBinaire(ascii, messageBinaire, 0);
}

void decimalToBinaire(int decimal, int binaire[], int index) {
    if (decimal / 2 == 0)
    {
        binaire[index] = decimal;
    }
    else
    {
        binaire[index] = decimal % 2;
        decimalToBinaire(decimal / 2, binaire, index+1);
    }
}

void ecrireCaseCouleur(FILE* image, int bitFaible) {
    int couleur;
    fread(&couleur, SIZE_OF_COULEUR, 1, image);
    if (couleur%2 != bitFaible)
    {
        couleur +=1;
        fseek(image, - SIZE_OF_COULEUR, SEEK_CUR);
        fwrite(&couleur, SIZE_OF_COULEUR, 1, image);
    }
}