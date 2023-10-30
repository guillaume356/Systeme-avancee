#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    // Créer un pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Premier fork pour exécuter "ps eaux"
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipefd[0]);   // Fermer l'entrée du pipe, pas nécessaire ici
        dup2(pipefd[1], STDOUT_FILENO); // Rediriger la sortie standard vers le pipe
        close(pipefd[1]);

        execlp("ps", "ps", "eaux", NULL);
        perror("execlp ps");
        exit(EXIT_FAILURE);
    }

    // Second fork pour exécuter "grep "^root " > /dev/null"
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipefd[1]); // Fermer la sortie du pipe, pas nécessaire ici
        dup2(pipefd[0], STDIN_FILENO); // Rediriger l'entrée standard depuis le pipe
        close(pipefd[0]);

        int dev_null = open("/dev/null", O_WRONLY);
        dup2(dev_null, STDOUT_FILENO); // Rediriger la sortie standard vers /dev/null
        close(dev_null);

        execlp("grep", "grep", "^root ", NULL);
        perror("execlp grep");
        exit(EXIT_FAILURE);
    }

    // Fermer les deux extrémités du pipe dans le processus parent
    close(pipefd[0]);
    close(pipefd[1]);

    // Attendre que "grep" se termine et vérifier son code de sortie
    waitpid(pid2, NULL, 0);
    int status;
    if (waitpid(pid1, &status, 0) != -1 && WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        write(STDOUT_FILENO, "root est connecté\n", 18);
    }

    return 0;
}