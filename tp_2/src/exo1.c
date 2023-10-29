#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid, child_pid;
    int status;

    pid = fork(); // création d'un processus fils

    if (pid < 0) {
        // erreur lors de la création du processus
        perror("Erreur de fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Nous sommes dans le processus fils
        printf("Je suis le processus fils avec PID %d et mon père a le PID %d\n", getpid(), getppid());
        exit(getpid() % 10); // retourne le dernier chiffre du PID
    } else {
        // Nous sommes dans le processus père
        child_pid = wait(&status); // attend la fin du processus fils

        printf("Je suis le processus père. Le PID de mon fils était %d\n", child_pid);

        if (WIFEXITED(status)) {
            printf("Mon fils s'est terminé avec le code de retour %d\n", WEXITSTATUS(status));
        } else {
            printf("Mon fils ne s'est pas terminé normalement\n");
        }
    }

    return 0;
}
