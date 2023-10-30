#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int status;

    // Vérifier si le nombre de paramètres est correct
    if (argc != 2)
    {
        // Afficher un message d'erreur et quitter le programme
        printf("Erreur : nombre de paramètres incorrect\n");
        return 1;
    }

    // Afficher le premier mot passé en paramètre
    printf("Le premier mot passé en paramètre est : %s\n", argv[1]);

    // Créer un processus fils
    pid = fork();

    // Vérifier si le processus fils a été créé
    if (pid < 0)
    {
        // Afficher un message d'erreur et quitter le programme
        perror("Erreur de fork");
        return 1;
    }

    // Vérifier si nous sommes dans le processus fils
    if (pid == 0)
    {
        // Nous sommes dans le processus fils
        printf("Je suis le processus fils avec PID %d\n", getpid());

        // Ouvrir un fichier temporaire pour écrire la sortie
        int fd = mkstemp("/tmp/proc-exercise");

        // TODO : Fix file access

        if (fd == -1)
        {
            perror("Erreur d'ouverture du fichier");
            return 1;
        }

        // Rediriger la sortie standard (STDOUT) vers le fichier
        if (dup2(fd, 1) == -1)
        {
            perror("Erreur de redirection de descripteur");
            return 1;
        }

        // Fermer le descripteur dupliqué
        close(fd);

        // Exécuter la commande passée en paramètre
        execlp(argv[1], argv[1], NULL);
        perror("Erreur d'exécution");
    }
    else
    {
        printf("PID du père : %d\n", getpid());

        // Attend la fin du fils
        wait(&status);

        // Affiche un message avant de terminer
        printf("That's All Folks!\n");
    }

    return 0;
}
