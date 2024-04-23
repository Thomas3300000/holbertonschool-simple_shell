#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>

/**
 * commande_existe - Vérifie si une commande existe
 * @args: Arguments du script
 * @chemin_fichier: nom du chemin du fichier script
 * @numLigne: Numéro de la ligne du script à executer
 * @envp: Variables d'environnement
 * Return: Chemin de la commande, ou NULL si elle n'existe pas
 */
char *commande_existe(
	char **args,
	char *chemin_fichier,
	int numLigne,
	char **envp)
{
	char *chemin_Commande;
	char **Chemin_dossiers = obtenir_chemin_dossier(envp);

	if (chemin_existe(args[0]) < 1)
	{
		chemin_Commande = obtenir_tout_chemin_commande(Chemin_dossiers, args[0]);

		free(Chemin_dossiers);
		if (chemin_Commande == NULL)
		{
			printf("%s: %d: Aucun fichier ou dossier de ce type\n", chemin_fichier,
				   numLigne);
			free(chemin_Commande);
			return (NULL);
		}
		else
			return (chemin_Commande);
	}
	free(Chemin_dossiers);
	return (strdup(args[0]));
}

/**
 * executer_processus - Exécute un processus à partir des arguments
 * @args: Ligne de commande
 * @chemin_fichier: nom du chemin du fichier script
 * @numLigne: Numéro de la ligne du script à executer
 * @envp: Variable d'environnement
 * Return: Statut du résultat du processus
 */
int executer_processus(char **args, char *chemin_fichier, int numLigne,
					   char **envp)
{

	pid_t pid;
	int statut;
	char *message = malloc(64 * sizeof(char));
	char *chemin_Commande = commande_existe(args, chemin_fichier, numLigne, envp);

	if (chemin_Commande == NULL)
	{
		free(message);
		return (-1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(chemin_Commande, args, envp) == -1)
		{
			sprintf(message, "%s: %d", chemin_fichier, numLigne);
			perror(message);
		}
		free(message);
		free(chemin_Commande);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		sprintf(message, "%s: %d", chemin_fichier, numLigne);
		perror(message);
	}
	else
	{
		do
		{
			waitpid(pid, &statut, WUNTRACED);
		} while (!WIFEXITED(statut) && !WIFSIGNALED(statut));
	}
	free(chemin_Commande);
	free(message);
	return (-1);
}

/**
 * analyser_args - Analyse les arguments pour executer un processus
 * @args: Arguments
 * @chemin_fichier: Chemin de l'exécutable
 * @numLigne: Numéro de la ligne du script
 * @envp: Variables d'environnement
 * Return: Statut de l'exécution du processus
 */
int analyser_args(char **args, char *chemin_fichier, int numLigne, char **envp)
{
	if (args[0] == NULL)
		return (-1);
	return (executer_processus(args, chemin_fichier, numLigne, envp));
}
