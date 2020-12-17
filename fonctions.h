#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define TAILLE_BUFFER 8000
#define ERREUR -1
#define SUCCES 42
#define SIZE_OF_COULEUR 1

void seekDebutCasesCouleurCurseur(FILE* image);

int codageMessage();   
int copierImage();
void conversionBinaire(char caractere, int messageBinaire[]);
void decimalToBinaire(int decimal, int binaire[], int index);
void ecrireCaseCouleur(FILE* image, int bitFaible);


int decodageMessage();
char conversionCaractere(int binaire[]);
int lireCaseCouleur(FILE* image);
