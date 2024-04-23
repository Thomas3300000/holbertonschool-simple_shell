#include "main.h"
/**
 * commande_existe - verifie si la commande exite dans le PATH
 * @commande: commande a verifier
 * @envp: variables d'environnement
 *
 * Return: 1 si la commande existe sinon 0
 */
int commande_existe(char *commande, char **envp)
{
	char **chemins = obtenir_dossiers_chemin(envp);
	char *chemin_commande = obtenir_commande_tous_chemins(chemins, commande);

	if (chemins == NULL)
	{
		return (0);
	}

	if (chemin_commande != NULL)
	{
		free(chemin_commande);
		free(chemins);
		return (1);
	}

	free(chemins);
	return (0);
}

/**
 * execute_commande - execute la commande
 * @commande: commande a executer
 * @args: arguments de la commande
 * @envp: variables d'environnement
 *
 * Return: statut execution commande
 */
int execute_commande(char *commande, char **args, char **envp)
{
	if (commande_existe(commande, envp) == 0)
	{
		fprintf(stderr, "%s: Commande non trouvee\n", commande);
		return (-1);
	}
	return (execute_process(args, envp));
}

/**
  * analyser_args - analyse arguments pour executer commande
  * @args: arguments a analyser
  * @envp: variables d'environnement
  *
  * Return: status execution commande ou -1 si pas d'argument
  */
int analyser_args(char **args, char **envp)
{
	if (args[0] == NULL)
	{
		return (-1);
	}
	return (execute_commande(args[0], args, envp));
}

/**
   * execute_process - execute processus avec arguments et environemment
   * @args: argument processus
   * @envp: variable environnement
   *
   * Return: statut execution processus
   */
int execute_process(char **args, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid < 0)
	{
		perror(".hsh");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, envp) == -1)
		{
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return (status);
}
