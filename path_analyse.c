#include "main.h"
#include <dirent.h>
#include <sys/stat.h>

/**
 * obtenirLongueurTableau - obtenir la longueur d'un
 * tableau de chaînes
 * @tableau: Tableau de chaînes
 * Return: Longueur du tableau
 */
int obtenirLongueurTableau(char **tableau)
{
	int i = 0;

	while (tableau[i])
		i++;
	return (i);
}

/**
 * cheminExiste - Vérifier si un chemin existe
 * @chemin: Chemin à vérifier
 * Return: 1 si trouvé, 0 sinon
 */
int cheminExiste(char *chemin)
{
	if (access(chemin, X_OK) == 0)
		return (1);
	return (0);
}

/**
 * obtenirDossiersChemin - Filtrer tous les dossiers
 * à partir de la variable d'environnement PATH
 * @envp: Variables d'environnement
 * Return: Tableau de chaînes contenant
 * tous les chemins
 */
char **obtenirDossiersChemin(char **envp)
{
	int i = 0;

	while (envp[i])
	{
		if (envp[i] != NULL)
		{
			char *ligne = strdup(envp[i]);
			char **args = diviser_chaine(ligne, ENV_SEPARATEUR);
			int longueurArgs = obtenirLongueurTableau(args);

			if (longueurArgs > 1 && strcmp(args[0], "PATH") == 0)
			{
				char **chemins = diviser_chaine(args[1], PATH_SEPARATEUR);
				int longueurChemins = obtenirLongueurTableau(chemins);

				free(args);
				if (longueurChemins > 0)
					return (chemins);
				return (NULL);
			}
		}
		i++;
	}
	return (NULL);
}

/**
 * obtenirCheminCommande - Vérifier si une commande existe
 * de manière récursive à partir d'un chemin
 * @cheminBase: Racine de la recherche
 * @nomCommande: Nom de la commande
 * Return: Chemin de la commande, ou NULL si non trouvé
 */
char *obtenirCheminCommande(char *cheminBase, char *nomCommande)
{
	char *chemin = malloc(sizeof(char) * 1024);
	struct dirent *dp;
	DIR *dir = opendir(cheminBase);

	if (!dir)
	{
		free(chemin);
		return (NULL);
	}
	while ((dp = readdir(dir)) != NULL)
	{
		if (strcmp(dp->d_name, ".") != 0 &&
			strcmp(dp->d_name, "..") != 0 &&
			strcmp(dp->d_name, "X11") != 0)
		{
			struct stat sb;

			strcpy(chemin, cheminBase);
			strcat(chemin, "/");
			strcat(chemin, dp->d_name);
			if (stat(chemin, &sb) == 0 && sb.st_mode & S_IXUSR)
			{
				if (strcmp(nomCommande, dp->d_name) == 0)
				{
					closedir(dir);
					return (chemin);
				}
			}
			obtenirCheminCommande(chemin, nomCommande);
		}
	}
	closedir(dir);
	free(chemin);
	return (NULL);
}

/**
 * obtenirCommandeTousChemins - Obtenir le chemin de la commande
 * en recherchant dans une liste de dossiers
 * @dossiers: Dossiers à rechercher
 * @nomCommande: nom de la commande
 * Return: Nom de la commande, ou NULL si non trouvé
 */
char *obtenirCommandeTousChemins(char **dossiers, char *nomCommande)
{
	int i = 0;

	while (dossiers[i])
	{
		char *chemin = obtenirCheminCommande(dossiers[i], nomCommande);

		if (chemin != NULL)
			return (chemin);
		i++;
	}
	return (NULL);
}
