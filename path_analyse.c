#include "main.h"

/**
 * obtenir_longueur_tableau - obtenir la longueur d'un
 * tableau de chaînes
 * @tableau: Tableau de chaînes
 * Return: Longueur du tableau
 */
int obtenir_longueur_tableau(char **tableau)
{
	int i = 0;

	while (tableau[i])
		i++;
	return (i);
}

/**
 * chemin_existe - Vérifier si un chemin existe
 * @chemin: Chemin à vérifier
 * Return: 1 si trouvé, 0 sinon
 */
int chemin_existe(char *chemin)
{
	if (access(chemin, X_OK) == 0)
		return (1);
	return (0);
}

/**
 * obtenir_chemin_dossier - Filtrer tous les dossiers
 * à partir de la variable d'environnement PATH
 * @envp: Variables d'environnement
 * Return: Tableau de chaînes contenant
 * tous les chemins
 */
char **obtenir_chemin_dossier(char **envp)
{
	int i = 0;

	while (envp[i])
	{
		if (envp[i] != NULL)
		{
			char *ligne = strdup(envp[i]);
			char **args = diviser_chaine(ligne, ENV_SEPARATEUR);
			int longueurArgs = obtenir_longueur_tableau(args);

			if (longueurArgs > 1 && strcmp(args[0], "PATH") == 0)
			{
				char **chemins = diviser_chaine(args[1], PATH_SEPARATEUR);
				int longueurChemins = obtenir_longueur_tableau(chemins);

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
 * obtenir_chemin_commande - Vérifier si une commande existe
 * @chemin_base: Racine de la recherche
 * @nom_commande: Nom de la commande
 * Return: Chemin de la commande, ou NULL si non trouvé
 */
char *obtenir_chemin_commande(char *chemin_base, char *nom_commande)
{
	char *chemin = malloc(sizeof(char) * INPUT_MAX_LONGUEUR);
	struct dirent *dp;
	DIR *dir = opendir(chemin_base);

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

			strcpy(chemin, chemin_base);
			strcat(chemin, "/");
			strcat(chemin, dp->d_name);
			if (stat(chemin, &sb) == 0 && sb.st_mode & S_IXUSR)
			{
				if (strcmp(nom_commande, dp->d_name) == 0)
				{
					closedir(dir);
					return (chemin);
				}
			}
		}
	}
	closedir(dir);
	free(chemin);
	return (NULL);
}

/**
 * obtenir_tout_chemin_commande - Obtenir le chemin de la commande
 * en recherchant dans une liste de dossiers
 * @dossiers: Dossiers à rechercher
 * @nom_commande: nom de la commande
 * Return: Nom de la commande, ou NULL si non trouvé
 */
char *obtenir_tout_chemin_commande(char **dossiers, char *nom_commande)
{
	int i = 0;

	while (dossiers[i])
	{
		char *chemin = obtenir_chemin_commande(dossiers[i], nom_commande);

		if (chemin != NULL)
			return (chemin);
		i++;
	}
	return (NULL);
}
