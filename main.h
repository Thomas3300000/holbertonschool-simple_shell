#ifndef MAIN_H
#define MAIN_H

/* Variable globale */
#define INPUT_MAX_LONGUEUR 1024
#define SEPARATEURS_ARG " \t\r\n\a\""
#define ENV_SEPARATEUR "="
#define PATH_SEPARATEUR ":"

/* Librairies */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>

/*Prototypes */

char *lire_ligne(void);
char **diviser_ligne(char *ligne, char *separateurs);
int commande_existe(char *commande);
char **analyser_arguments(char *ligne, char *separateurs);
void gerer_non_interactif(char *chemin_fichier);
void gerer_interactif(char *chemin_fichier);
int main(int argc, char **argv);

#endif
