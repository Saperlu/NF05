#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAILLE_BUFFER 8000
#define ERREUR -1
#define SUCCES 42

/**
 * @brief Duplique l'image pour sauvegarder l'originale.
 * 
 * @return int -1 si erreur
 *              42 si succès
 */
int copierImage();