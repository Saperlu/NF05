#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAILLE_BUFFER 8000
#define ERREUR -1
#define SUCCES 42
#define SIZE_OF_COULEUR 1

/**
 * @brief Duplique l'image pour sauvegarder l'originale.
 * 
 * @return int -1 si erreur
 *              42 si succès
 */
int copierImage();

void conversionBinaire(char caractere, int messageBinaire[]);
void decimalToBinaire(int decimal, int binaire[], int index);
void ecrireCaseCouleur(FILE* image, int bitFaible);
