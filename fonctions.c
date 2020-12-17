#include "fonctions.h"

void seekDebutCasesCouleurCurseur(FILE* image) {
    // Va au début des cases couleurs
    fseek(image, 16 * sizeof(char), SEEK_SET);
}

   
int codageMessage() {
    if (copierImage() == ERREUR) {
        return ERREUR;
    }
    
    FILE *image;
    image = fopen("imageCodee.ppm", "rb+");
    if (image== NULL)
    {   
        printf("ERREUR : ouverture de l'image impossible\n");
    }
    seekDebutCasesCouleurCurseur(image);

    char message[200] = "";
    printf("Rentrez votre message secret\n > ");
    scanf("%s", message);
    int tailleMessage = strlen(message);

    int messageBinaire[200][7];
    for (int i = 0; i < tailleMessage; i++)
    {
        conversionBinaire(message[i], messageBinaire[i]);
    }
    
    // Ecriture message
    for (int i = 0; i < strlen(message); i++)
    {
        for (int j = 0; j < 7; j++)
        {
            int nombre = messageBinaire[i][j];
            ecrireCaseCouleur(image, nombre);
        }
    }

    // Ecriture caractère NULL
    for (int j = 0; j < 7; j++)
    {
        ecrireCaseCouleur(image, 0);
    }
     
    
    fclose(image);
    return 0;
}

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
        srand(time(NULL));
        if (rand() % 2) couleur += 1;
        else couleur -= 1;
        
        fseek(image, - SIZE_OF_COULEUR, SEEK_CUR);
        fwrite(&couleur, SIZE_OF_COULEUR, 1, image);
    }
}

int decodageMessage() {
    FILE *image;
    image = fopen("imageCodee.ppm", "rb");
    if (image == NULL)
    {
        printf("ERREUR : Ouverture de l'image codee");
        return ERREUR;
    }
    seekDebutCasesCouleurCurseur(image);

    char caractere;
    int caractereBinaire[7];
    do
    {
        for (int i = 0; i < 7; i++)
        {
            caractereBinaire[i] = lireCaseCouleur(image);
        }
        caractere = conversionCaractere(caractereBinaire);
        printf("%c", caractere);
        
    } while (caractere != '\0');
    
    return 0;

}

int lireCaseCouleur(FILE* image) {
    int bitFaible, valeurCouleur;
    fread(&valeurCouleur, SIZE_OF_COULEUR, 1, image);
    bitFaible = valeurCouleur % 2;
    return bitFaible;
}

char conversionCaractere(int binaire[]) {
    int puissance, decimal = 0;
    for (int i = 0; i < 7; i++)
    {
        decimal += pow(2, i) * binaire[i];
    }
    
    return (char) decimal;
}



