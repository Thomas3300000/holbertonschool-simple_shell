#include "main.h"

/**
 * lire_ligne - Lit une ligne depuis le terminal
 * Retourne: la ligne lue depuis l'entrée standard
 */
char *lire_ligne(void)
{
	char *ligne = NULL;
	size_t taille_buffer = 0;

	if (getline(&ligne, &taille_buffer, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(ligne);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(ligne);
			printf("Erreur lors de la lecture de la ligne depuis l'entrée standard");
			exit(EXIT_FAILURE);
		}
	}
	return (ligne);
}

/**
 * diviser_ligne - Divise une ligne en utilisant des séparateurs communs
 * @ligne: La ligne à diviser
 * @séparateurs: Chaîne de caractères utilisée pour séparer
 * Retourne: Tableau de chaînes de caractères contenant un mot chacune
 */
char **diviser_ligne(char *ligne, char *séparateurs)
{
	int taille_buffer = 64;
	int i = 0;
	char **mots = malloc(taille_buffer * sizeof(char *));
	char *mot;

	if (!mots)
	{
		fprintf(stderr, "erreur d'allocation : mots\n");
		exit(EXIT_FAILURE);
	}
	mot = strtok(ligne, séparateurs);
	while (mot != NULL)
	{
		if (mot[0] == '#')
			break;
		mots[i] = mot;
		i++;
		if (i >= taille_buffer)
		{
			taille_buffer += taille_buffer;
			mots = realloc(mots, taille_buffer * sizeof(char *));
			if (!mots)
			{
				fprintf(stderr, "erreur de réallocation : mots");
				exit(EXIT_FAILURE);
			}
		}
		mot = strtok(NULL, séparateurs);
	}
	mots[i] = NULL;
	return (mots);
}
