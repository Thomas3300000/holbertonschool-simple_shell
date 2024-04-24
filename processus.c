#include "main.h"

/**
 * commande_existe - Vérifie si une commande existe
 * @args: Arguments du script
 * @chemin_fichier: nom du chemin du fichier script
 * @num_ligne: Numéro de la ligne du script à executer
 * @envp: Variables d'environnement
 * Return: Chemin de la commande, ou NULL si elle n'existe pas
 */
char *commande_existe(
	char **args,
	char *chemin_fichier,
	int num_ligne,
	char **envp)
{
	char *chemin_commande;
	char **Chemin_dossiers = obtenir_chemin_dossier(envp);

	if (chemin_existe(args[0]) < 1)
	{
		chemin_commande = obtenir_tout_chemin_commande(Chemin_dossiers, args[0]);

		free(Chemin_dossiers);
		if (chemin_commande == NULL)
		{
			printf("%s: %d: Aucun fichier ou dossier de ce type\n", chemin_fichier,
				   num_ligne);
			free(chemin_commande);
			return (NULL);
		}
		else
			return (chemin_commande);
	}
	free(Chemin_dossiers);
	return (strdup(args[0]));
}

/**
 * executer_processus - Exécute un processus à partir des arguments
 * @args: Ligne de commande
 * @chemin_fichier: nom du chemin du fichier script
 * @num_ligne: Numéro de la ligne du script à executer
 * @envp: Variable d'environnement
 * Return: Statut du résultat du processus
 */
int executer_processus(char **args, char *chemin_fichier, int num_ligne,
					   char **envp)

{
	pid_t pid;
	int statut;
	char *message = malloc(64 * sizeof(char));
	char *chemin_commande = commande_existe(args, chemin_fichier,
											num_ligne, envp);

	if (chemin_commande == NULL)
	{
		free(message);
		return (-1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(chemin_commande, args, envp) == -1)
		{
			sprintf(message, "%s: %d", chemin_fichier, num_ligne);
			perror(message);
		}
		free(message);
		free(chemin_commande);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		sprintf(message, "%s: %d", chemin_fichier, num_ligne);
		perror(message);
	}
	else
	{
		do
		{
			waitpid(pid, &statut, WUNTRACED);
		} while (!WIFEXITED(statut) && !WIFSIGNALED(statut));
	}
	free(chemin_commande);
	free(message);
	return (-1);
}

/**
 * analyser_args - Analyse les arguments pour executer un processus
 * @args: Arguments
 * @chemin_fichier: Chemin de l'exécutable
 * @num_ligne: Numéro de la ligne du script
 * @envp: Variables d'environnement
 * Return: Statut de l'exécution du processus
 */
int analyser_args(char **args, char *chemin_fichier,
				  int num_ligne, char **envp)
{
	if (args[0] == NULL)
		return (-1);
	if (strcmp(args[0], "exit") == 0)
		return (0);
	return (executer_processus(args, chemin_fichier, num_ligne, envp));
}
