#include "main.h"

/**
 * obtenirLongueurTableau - obtenir la longueur d'un tableau de chaines
 * @tableau: Tableau de chaines
 * Retourne: Longueur du tableau
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
 * Retourne: 1 si trouvé, 0 sinon
 */
int cheminExiste(char *chemin)
{
	if (access(chemin, X_OK) == 0)
		return (1);
	return (0);
}

/**
 * obtenirDossiersChemin - Filtrer tous les
 * dossiers de la variable d'environnement PATH
 * @envp: Variables d'environnement
 * Retourne: Tableau de chaines contenant tous les chemins
 */
char **obtenirDossiersChemin(char **envp)
{
	int i = 0;

	while (envp[i])
	{
		if (envp[i] != NULL)
		{
			char **arguments = diviser_ligne(ligne, ENV_SEPARATEUR);
			int longueurArguments = obtenirLongueurTableau(arguments);

			if (longueurArguments > 1 && strcmp(arguments[0], "PATH") == 0)
			{
				char **chemins = diviser_chaine(arguments[1], PATH_SEPARATEUR);
				int longueurChemins = obtenirLongueurTableau(chemins);

				free(arguments);
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
 * obtenirCheminCommande - Vérifier si une
 * commande existe récursivement à partir d'un chemin
 * @cheminBase: Racine de la recherche
 * @nomCommande: Nom de la commande
 * Retourne: Chemin de la commande, ou NULL si non trouvée
 */
char *obtenirCheminCommande(char *cheminBase, char *nomCommande)
{
	char *chemin = malloc(sizeof(char) * INPUT_MAX_LONGUEUR);
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
 * obtenirCommandeTousChemins - Obtenir le chemin de
 * la commande en cherchant dans une liste de dossiers
 * @dossiers: Dossiers à chercher
 * @nomCommande: Nom de la commande
 * Retourne: Nom de la commande, ou NULL si non trouvée
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
