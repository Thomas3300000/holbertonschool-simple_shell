#include "main.h"

/**
 * commande_existe - Fonction qui verifie si la commande existe 
 * @commande: pointeur chaine de caracteres commande a verifier
 *
 * Return: 1 si la commande existe sinon 0
 */
int commande_existe(char *commande)
{	 if (access(commande, X_OK) == 0)
		return (1);
	fprintf(stderr, "Commande non trouve©\n©");
	return (0);
}

/**
 * analyser_arguments - Fonction qui analyse chaque argument
 * @ligne: chaine de caracteres a analyser
 * @se√parateurs: chaine de caracteres contenant les separateurs  
 *
 * Return: mots
 */
char **analyser_arguments(char *ligne, char *se√parateurs)
{
	char **mots = diviser_ligne(ligne, se√parateurs);
	int i = 0;

	if (mots == NULL)
		exit(EXIT_FAILURE);

	while (mots[i] != NULL)
		i++;

	free(mots);

	return (mots);
}
