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

/* Prototypes */

char *lire_ligne(void);
char **diviser_chaine(char *ligne, char *separateurs);
int executer_processus(char **args, char *chemin_fichier, int num_ligne,
					   char **envp);
int analyser_args(char **args, char *chemin_fichier, int num_ligne,
				  char **envp);
char **obtenir_chemin_dossier(char **envp);
char *obtenir_tout_chemin_commande(char **dossiers, char *nom_commande);
int chemin_existe(char *chemin);

#endif
