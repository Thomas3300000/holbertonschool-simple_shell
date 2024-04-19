#ifndef MAIN_H
#define MAIN_H

/* Variable globale */

#define SÉPARATEURS_ARG " \t\r\n\a\""
#define SÉPARATEUR_ENV "="
#define SÉPARATEUR_PATH ":"

/* Librairies */

#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/*Prototypes */
char *lire_ligne(void);
char **diviser_ligne(char *ligne, char *séparateurs);

#endif
