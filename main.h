#ifndef MAIN_H
#define MAIN_H

/* Variable globale */

#define INPUT_MAX_LONGUEUR 1000
#define SÉPARATEURS_ARG " \t\r\n\a\""
#define ENV_SÉPARATEUR "="
#define PATH_SÉPARATEUR ":

/* Librairies */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/*Prototypes */

char *lire_ligne(void);
char **diviser_ligne(char *ligne, char *séparateurs);
int commande_existe(char *commande);
#endif
