<h1 align="center">Holberton-School Projet : Simple Shell</h1>
</div>
<br><br><br><br>

## Tâche

Pour ce projet appelé "Simple Shell", nous avions deux semaines pour le réaliser.
L'objectif est de créer une commande `hsh`, nous permettant d'exécuter des scripts de différentes manières

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

<img src="https://github.com/Thomas3300000/holbertonschool-simple_shell/blob/Samuel/Annexes/Flowchart.png?raw=true">

## Authors

| [@Thomas Maillard](https://github.com/Thomas3300000)| [@Samuel VERSCHUEREN]https://github.com/Ezio-33) |
