#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fonctions.c"


int main()
{
    int mode = 2;
    printf("\
    Quel mode ? \n\
       1. Codage\n\
       2. Decodage\n\n > ");
    scanf("%d", &mode);
    char c;
    while((c = getchar() != '\n') && c != EOF);
    switch (mode)
    {
    case 1:
        if (codageMessage() == ERREUR)
        {
            return ERREUR;
        }
        break;
    case 2:
        if (decodageMessage() == ERREUR)
        {
            return ERREUR;
        }
        break;
    default:
        printf("ERRRRREUR\n");
        break;
    }
    return 0;
}

