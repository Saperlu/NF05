#include "fonctions.h"

void seekDebutCasesCouleurCurseur(FILE* image) {
    // Va au début des cases couleurs
    fseek(image, 16 * sizeof(char), SEEK_SET);
}

void seekCaseCouleur(FILE* image, int index) {
    seekDebutCasesCouleurCurseur(image);
    fseek(image, index * SIZE_OF_COULEUR, SEEK_CUR);
}

void genererTableauOrdre(int **tableauOrdre, int tailleMessage) {
    int inter, m=0;
    long clef;
    for (int i = 0; i < tailleMessage; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            tableauOrdre[i][j]= m;
            m++;
        }
    }

    printf("Rentrez votre clef\n");
    scanf("%ld", &clef);
    srand(clef);
    // Permutations successives afin de "mélanger" le tableau
    for (int w=0;w<1000; w++)
    {
        for (int i = 0; i < tailleMessage; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                int x=rand()%tailleMessage;
                int y=rand()%7;
                inter=tableauOrdre[i][j];
                tableauOrdre[i][j]= tableauOrdre[x][y];
                tableauOrdre[x][y]=inter;
        
            }
        }
    }
}


 
int codageMessage() {
    if (copierImage() == ERREUR) {
        return ERREUR;
    }
    
    FILE *image;
    image = fopen("imageCodee.ppm", "rb+");
    if (image== NULL)
    {   
        printf("ERREUR : ouverture de l'image impossible (flag 10)\n");
    }
    seekDebutCasesCouleurCurseur(image);

    // TailleMax
    int tailleMaxMessage = calculTailleMaxMessage(image);

    // input le message
    char *message;
    message = (char*) malloc(tailleMaxMessage * sizeof(char));
    printf("Rentrez votre message secret de longueur maximale : %d caracteres\n > ", tailleMaxMessage);
    fgets(message, tailleMaxMessage, stdin);
    
    int tailleMessage = strlen(message);

    // Remplit le tableau messagBinaire
    int messageBinaire[200][BITS_PAR_CARACTERE];
    for (int i = 0; i < tailleMessage; i++)
    {
        charToTabBinaire(message[i], messageBinaire[i]);
    }

    // Déclaration tableauOrdre
    int **tableauOrdre;
    tableauOrdre = (int **) malloc(tailleMessage * sizeof(int *));
    for (int i = 0; i < tailleMessage; i++)
    {
        tableauOrdre[i] = (int *) malloc(BITS_PAR_CARACTERE * sizeof(int));
    }
    genererTableauOrdre(tableauOrdre, tailleMessage);
    

    // Ecriture message
    for (int i = 0; i < strlen(message); i++)
    {
        for (int j = 0; j < BITS_PAR_CARACTERE; j++)
        {
            int nombre = messageBinaire[i][j];
            seekCaseCouleur(image, tableauOrdre[i][j]);
            ecrireCaseCouleur(image, nombre);
        }
    }

    // Ecriture caractère NULL à la fin du message
    seekCaseCouleur(image, tailleMessage * BITS_PAR_CARACTERE + 1);
    for (int j = 0; j < BITS_PAR_CARACTERE; j++)
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

    // input le nom de l'image
    char nomImage[500] = "";
    printf("Entrez le nom de l'image dans laquelle le message doit etre dissimule \n > ");
    fgets(nomImage, 500, stdin);
    nomImage[strlen(nomImage) - 1] = '\0';

    // fopen l'image
    imageSource = fopen(nomImage, "rb");
    imageCodee = fopen("imageCodee.ppm", "wb+");
    if (imageSource == NULL || imageCodee == NULL)
    {
        printf("ERREUR : ouverture des images impossible (flag 11)\n");
        return ERREUR;
    }

    // Copie blocs par blocs du fichier
    do
    {
        n = fread(buffer, sizeof(int), TAILLE_BUFFER, imageSource);
        fwrite(buffer, sizeof(int), TAILLE_BUFFER, imageCodee);
    } while (n>0);

    fclose(imageSource);
    fclose(imageCodee);
    return SUCCES;
} 

int calculTailleMaxMessage() {
    // Lit les métadonnées de l'image
    FILE* image;
    image = fopen("imageCodee.ppm", "r");
    if (image == NULL)
    {
        printf("ERREUR : Ouverture de l'image");
        return ERREUR;
    }
    int largeur, hauteur;
    char truc[100];
    fscanf(image, "%s %d %d", truc, &largeur, &hauteur);
    fclose(image);

    return (largeur * hauteur * 3) / BITS_PAR_CARACTERE;
}

void charToTabBinaire(char caractere, int messageBinaire[]) {
    int ascii = (int) caractere;
    for (int i = 0; i < 7; i++) messageBinaire[i] = 0;
    
    decimalToTabBinaire(ascii, messageBinaire, 0);
}

void decimalToTabBinaire(int decimal, int binaire[], int index) {
    if (decimal / 2 == 0)
    {
        binaire[index] = decimal;
    }
    else
    {
        binaire[index] = decimal % 2;
        // Fonction récursive
        decimalToTabBinaire(decimal / 2, binaire, index+1);
    }
}

void ecrireCaseCouleur(FILE* image, int bitFaible) {
    int couleur;
    fread(&couleur, SIZE_OF_COULEUR, 1, image);
    if (couleur%2 != bitFaible)
    {
        // Amélioration #1
        srand(time(NULL));
        if (rand() % 2) couleur += 1;
        else couleur -= 1;
        
        fseek(image, - SIZE_OF_COULEUR, SEEK_CUR);
        fwrite(&couleur, SIZE_OF_COULEUR, 1, image);
    }
}


int decodageMessage() {
    // input le nom de l'image
    char nomImage[500] = "";
    printf("Entrez le nom de l'image dans laquelle le message est dissimule \n > ");
    fgets(nomImage, 500, stdin);
    nomImage[strlen(nomImage) - 1] = '\0';

    // fopen l'image
    FILE *image;
    image = fopen(nomImage, "rb");
    if (image == NULL)
    {
        printf("ERREUR : Ouverture de l'image codee");
        return ERREUR;
    }
    seekDebutCasesCouleurCurseur(image);

    int tailleMessage = calculTailleMessage(image);    
    
    // Déclaration tableauOrdre
    int **tableauOrdre;
    tableauOrdre = (int **) malloc(tailleMessage * sizeof(int *));
    for (int i = 0; i < tailleMessage; i++)
    {
        tableauOrdre[i] = (int *) malloc(BITS_PAR_CARACTERE * sizeof(int));
    }
    genererTableauOrdre(tableauOrdre, tailleMessage);

    char caractere;
    int caractereBinaire[BITS_PAR_CARACTERE];

    printf("Votre message s'affiche sur la ligne ci-dessous : \n");
    for (int i = 0; i < tailleMessage; i++)
    {
        // Lecture d'un caractère
        for (int j = 0; j < BITS_PAR_CARACTERE; j++)
        {
            seekCaseCouleur(image, tableauOrdre[i][j]);
            caractereBinaire[j] = lireCaseCouleur(image);
        }
        caractere = TabBinaireToChar(caractereBinaire);
        printf("%c", caractere);
        
    }

    
    return 0;

}

int calculTailleMessage(FILE* image) {
    seekDebutCasesCouleurCurseur(image);
    int tailleMessage = -1;
    char caractere;
    int caractereBinaire[BITS_PAR_CARACTERE];
    // Cherche le caractère nul dans le fichier
    do
    {
        // Lit un caractere
        for (int i = 0; i < BITS_PAR_CARACTERE; i++)
        {
            caractereBinaire[i] = lireCaseCouleur(image);
        }
        caractere = TabBinaireToChar(caractereBinaire);
        tailleMessage++;
    } while (caractere != '\0');
    return tailleMessage;
}


int lireCaseCouleur(FILE* image) {
    int bitFaible, valeurCouleur;
    fread(&valeurCouleur, SIZE_OF_COULEUR, 1, image);
    bitFaible = valeurCouleur % 2;
    return bitFaible;
}

char TabBinaireToChar(int binaire[]) {
    int puissance, decimal = 0;
    for (int i = 0; i < 7; i++)
    {
        decimal += pow(2, i) * binaire[i];
    }
    
    return (char) decimal;
}



