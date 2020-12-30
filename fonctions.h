#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

/**
 * @brief taille des blocs de données lus pour copier l'image
 * 
 */
#define TAILLE_BUFFER 8000

/**
 * @brief Valeur de retour quand une erreur survient
 * 
 */
#define ERREUR -1

/**
 * @brief Valeur de retour quand tout se déroule sans accroc
 * 
 */
#define SUCCES 42

/**
 * @brief Le nombre d'octets qu'occupe une couleur dans le fichier ppm
 * 
 */
#define SIZE_OF_COULEUR 1

/**
 * @brief Le nombre de bits sur lesquels un caractère est codé
 * 
 */
#define BITS_PAR_CARACTERE 7

/**************************************************************
 * Les fonctions qui servent dans les deux parties du programme
 * ***********************************************************/

/**
 * @brief Déplace le curseur à la première couleur du fichier image
 * 
 * @param image Le pointeur du fichier
 */
void seekDebutCasesCouleurCurseur(FILE* image);

/**
 * @brief Déplace le curseur à la case souhaitée dans le fichier image
 * 
 * @param image Le pointeur du fichier
 * @param index L'index de la case couleur
 */
void seekCaseCouleur(FILE* image, int index);

/**
 * @brief Génère le tableau d'ordre
 * 
 * @param tableauOrdre Le tableau à remplir
 * @param tailleMessage La taille du message à transmettre
 */
void genererTableauOrdre(int **tableauOrdre, int tailleMessage);


/**********************************************************
 * Les fonctions qui servent dans la partie codage
 * ********************************************************/

/**
 * @brief Codage d'un message dans une image
 * 
 * @return int ERREUR si une erreur est survenue, SUCCES sinon
 */
int codageMessage();

/**
 * @brief Copie l'image donnée par l'utilisateur dans "imageCodee.ppm" 
 * 
 * @return int ERREUR si une erreur est survenue, SUCCES sinon
 */
int copierImage();

/**
 * @brief Calcule la taille maximale du message à insérer dans l'image
 * 
 * @return int La taille maximale du message
 */
int calculTailleMaxMessage();

/**
 * @brief Remplit messageBinaire avec les bits correspondant au caractère envoyé
 * 
 * @param caractere Le caractère à convertir
 * @param messageBinaire Le tableau de bits à remplir
 */
void charToTabBinaire(char caractere, int messageBinaire[]);

/**
 * @brief Remplit binaire avec les bits correspondant au nombre decimal envoyé
 * 
 * @param decimal Le nombre en base décimale à convertir
 * @param binaire Le tableau de bits à remplir
 * @param index Utiliser 0. Ce paramètre permet la récursivité de la fonction.
 */
void decimalToTabBinaire(int decimal, int binaire[], int index);

/**
 * @brief Insère un bit dans le bit de poids faible d'une couleur
 * 
 * @param image Le pointeur vers le fichier
 * @param bitFaible le bit à insérer
 */
void ecrireCaseCouleur(FILE* image, int bitFaible);



/**********************************************************
 * Les fonctions qui servent dans la partie décodage
 * ********************************************************/

/**
 * @brief Décode le message dissimulé dans une image
 * 
 * @return int ERREUR si une erreur est survenue, SUCCES sinon
 */
int decodageMessage();

/**
 * @brief Détermine la taille du message en analysant l'image
 * 
 * @param image Le pointeur vers le fichier image
 * @return int La taille du message
 */
int calculTailleMessage(FILE* image);

/**
 * @brief Convertit tableau de bits en un caractères
 * 
 * @param binaire Le tableau de bits
 * @return char Le caractère
 */
char TabBinaireToChar(int binaire[]);

/**
 * @brief Lit le bit de poids faible dans une case couleur
 * 
 * @param image Le pointeur vers le fichier image avec le curseur au début de la case couleur
 * @return int Le bit de poids faible
 */
int lireCaseCouleur(FILE* image);
