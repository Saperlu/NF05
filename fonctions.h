#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define TAILLE_BUFFER 8000
#define ERREUR -1
#define SUCCES 42
#define SIZE_OF_COULEUR 1
#define BITS_PAR_CARACTERE 7

void seekDebutCasesCouleurCurseur(FILE* image);
void seekCaseCouleur(FILE* image, int index);
void genererTableauOrdre(int **tableauOrdre, int tailleMessage);

int codageMessage();
int copierImage();
int calculTailleMaxMessage();
void conversionBinaire(char caractere, int messageBinaire[]);
void decimalToBinaire(int decimal, int binaire[], int index);
void ecrireCaseCouleur(FILE* image, int bitFaible);


int decodageMessage();
int calculTailleMessage(FILE* image);
char conversionCaractere(int binaire[]);
int lireCaseCouleur(FILE* image);

// int trouverKIdeal(int tailleMessage, int tailleMax);
// int trouverN(int k);
// Perdu dans le néant distordu
