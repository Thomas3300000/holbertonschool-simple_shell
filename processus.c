#include "main.h"

/**
 * commande_existe - Fonction qui verifie si la commande existe
 * @commande: pointeur chaine de caracteres commande a verifier
 *
 * Return: 1 si la commande existe sinon 0
 */
int commande_existe(char *commande)
{
	if (access(commande, X_OK) == 0)
		return (1);
	fprintf(stderr, "Commande non trouvée\n");
	return (0);
}

/**
 * analyser_arguments - Fonction qui analyse chaque argument
 * @ligne: chaine de caracteres a analyser
 * @separateurs: chaine de caracteres contenant les separateurs
 *
 * Return: mots
 */
char **analyser_arguments(char *ligne, char *separateurs)
{
	char **mots = diviser_ligne(ligne, separateurs);
	int i = 0;

	if (mots == NULL)
		exit(EXIT_FAILURE);

	while (mots[i] != NULL)
		i++;

	return mots;
}
