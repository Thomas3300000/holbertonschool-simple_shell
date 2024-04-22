#include "main.h"
/**
  * gerer_non_interactif - Gère le
  * processus non interactif de hsh
  * @chemin_fichier: Chemin du programme
  * @envp: Variables d'environnement
*/
void gerer_non_interactif(char *chemin_fichier)
{
	int fin_boucle = -1;
	int numero_ligne = 0;

	while (fin_boucle == -1)
	{
		char *ligne;
		char **arguments;

		ligne = lire_ligne();
		if (ligne == NULL)
		{
			fin_boucle = 1;
			break;
		}
		arguments = diviser_ligne(ligne, SEPARATEURS_ARG);
		fin_boucle = analyser_arguments(ligne, chemin_fichier);
		numero_ligne++;

		free(ligne);
		free(arguments);
		if (fin_boucle >= 0)
			exit(fin_boucle);
	}
}

/**
 * gerer_interactif - Gère le
 * processus interactif de hsh
 * @chemin_fichier: Chemin du programme
 * @envp: Variables d'environnement
 */
void gerer_interactif(char *chemin_fichier)
{
	char *ligne;
	char *arguments;
	int statut = -1;
	int numero_ligne = 0;

	do
	{
		printf("($) ");
		ligne = lire_ligne();
		char *arguments = diviser_ligne(ligne, SEPARATEURS_ARG);
		numero_ligne++;
		statut = analyser_arguments(arguments, chemin_fichier);

		free(ligne);
		free(arguments);
		if (statut >= 0)
			exit(statut);
	} while (statut == -1);
}

/**
 * main - Fonction principale de HSH
 * @argc: Nombre d'arguments
 * @argv: Valeurs des arguments
 * @envp: Variables d'environnement
 * Retourne: Toujours 0
 */
int main(int argc, char **argv, char **envp)

{
	if (argc < 1)
		return (1);
	if (isatty(STDIN_FILENO) == 1)
		gerer_interactif(argv[0]);
	else
		gerer_non_interactif(argv[0]);
	return (0);
}
