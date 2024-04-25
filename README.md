<h1 align="center">Holberton-School Projet : Simple Shell</h1>
</div>
<br><br><br><br>

## Tâche

Pour ce projet appelé "Simple Shell", nous avions deux semaines pour réaliser un programme qui reproduit le fonctionnement d'un terminal shell.

### Exigences

- Éditeurs autorisés : vi, vim, emacs
- Tous vos fichiers seront compilés sur Ubuntu 20.04 LTS avec gcc, en utilisant les options -Wall -Werror -Wextra -pedantic -std=gnu89
- Tous vos fichiers doivent se terminer par une nouvelle ligne
- Un fichier README.md, à la racine du dossier du projet, est obligatoire.
- Votre code doit utiliser le style Betty. Il sera vérifié en utilisant betty-style.pl et betty-doc.pl
- Votre shell ne doit pas avoir de fuites de mémoire
- Pas plus de 5 fonctions par fichier
- Tous vos fichiers d'en-tête doivent être gardés par include
- N'utilisez les appels système que lorsque vous en avez besoin

### Liste des fonctions et des appels système autorisés

| Fonctions et appels système autorisés |
| ------------------------------------- |
| Toutes les fonctions de string.h      |
| access                                |
| chdir                                 |
| close                                 |
| closedir                              |
| execve                                |
| exit                                  |
| \_exit                                |
| fflush                                |
| fork                                  |
| free                                  |
| getcwd                                |
| getline                               |
| getpid                                |
| isatty                                |
| kill                                  |
| malloc                                |
| open                                  |
| opendir                               |
| perror                                |
| printf                                |
| fprintf                               |
| vfprintf                              |
| sprintf                               |
| putchar                               |
| read                                  |
| readdir                               |
| signal                                |
| stat                                  |
| lstat                                 |
| fstat                                 |
| strtok                                |
| wait                                  |
| waitpid                               |
| wait3                                 |
| wait4                                 |
| write                                 |

## Instructions d'installation et de compilation

### Installation

Pour ajouter le projet dans votre environnement de travail, vous pouvez utiliser la commande suivante dans votre terminal:

```
git clone https://github.com/Thomas3300000/holbertonschool-simple_shell.git
```

### Compilation

Pour compiler le programme, vous devez utiliser la commande suivante :

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

Le mode interactif :

```
./hsh
```

Le mode non interactif :

```
$ echo "/bin/ls" | ./hsh
```

### Examples

1. Interactive mode

```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$

```

2. Non-interactive mode

```

$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
```

## Flowchart

<img src="https://github.com/Thomas3300000/holbertonschool-simple_shell/blob/main/Annexes/Flowchart.png?raw=true">

## Authors

| [@Thomas Maillard](https://github.com/Thomas3300000)| [@Samuel VERSCHUEREN](https://github.com/Ezio-33) |
