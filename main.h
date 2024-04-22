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

int main(int argc, char **argv);
void gerer_non_interactif(char **chemin_fichier);
void gerer_interactif(char **chemin_fichier);


char *lire_ligne(void);
char **diviser_chaine(char *ligne, char *separateurs);

int analyser_args(char **args, char **envp);
int commande_existe(char *commande, char **envp);
int execute_commande(char *commande, char **args, char **envp);
int execute_process(char **args, char **envp);
char *obtenir_commande_chemin(char *cheminBase, char *nomCommande);
char **obtenir_dossiers_chemin(char **envp);

int chemin_existe(char *path);
int obtenir_longueur_tableau(char **tableau);
char *obtenir_commande_tous_chemins(char **dossiers, char *nomCommande);

#endif
