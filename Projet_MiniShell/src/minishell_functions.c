#include "minishell_functions.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

bool is_background_command(char **tokens, int token_count) {
    return token_count > 0 && strcmp(tokens[token_count - 1], "&") == 0;
}

void execute_command_in_background(char **argv) {
    pid_t pid = fork();
    if (pid == 0) {
        // Processus enfant
        if (execvp(argv[0], argv) == -1) {
            perror("execvp");
        }
        exit(EXIT_FAILURE); // Si execvp échoue
    } else if (pid < 0) {
        // Échec du fork
        perror("fork");
    }
    // Le processus parent continue sans attendre le processus enfant
}

void parse_and_execute(char *commande) {
    char *tokens[MAX_TOKENS];
    int token_count = 0;

    // Découpage initial par espaces
    char *token = strtok(commande, " ");
    while (token != NULL && token_count < MAX_TOKENS - 1) {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }
    tokens[token_count] = NULL;

    if (token_count == 0) {
        return; // Pas de commande à exécuter
    }

    int status = 0;
    bool execute_next = true;


    if (is_background_command(tokens, token_count)) {
        tokens[token_count - 1] = NULL; // Enlever '&' du tableau d'arguments
        execute_command_in_background(tokens);
    } else {
        for (int i = 0; i < token_count; i++) {
            if (strcmp(tokens[i], "&&") == 0) {
                execute_next = (WEXITSTATUS(status) == 0);
            } else if (strcmp(tokens[i], "||") == 0) {
                execute_next = (WEXITSTATUS(status) != 0);
            } else if (execute_next) {
                // Exécution de la commande
                if (strcmp(tokens[i], "ls") == 0) {
                    status = executerLsPersonnalise(tokens[i]);
                } else if (strcmp(tokens[i], "pwd") == 0) {
                    char cwd[1024];
                    if (getcwd(cwd, sizeof(cwd)) != NULL) {
                        printf("%s\n", cwd);
                        status = 0;
                    } else {
                        perror("pwd");
                        status = -1;
                    }
                } else if (strcmp(tokens[i], "exit") == 0) {
                    exit(EXIT_SUCCESS);
                } else if (strcmp(tokens[i], "cd") == 0) {
                    status = chdir(tokens[i + 1]) == 0 ? 0 : -1;
                    i++; // Pour sauter l'argument de 'cd'
                } else if (strcmp(tokens[i], "echo") == 0) {
                    if (tokens[i + 1] != NULL) {
                        printf("%s\n", tokens[i + 1]);
                    }
                    status = 0;
                    i++; // Pour sauter l'argument de 'echo'
                } else if (strcmp(tokens[i], "date") == 0) {
                    status = system("/bin/date");
                } else if (strcmp(tokens[i], "who") == 0) {
                    status = system("/usr/bin/who");
                } else if (strcmp(tokens[i], "ps") == 0) {
                    status = system("/bin/ps");
                }
                // Réinitialiser execute_next pour la prochaine commande
                execute_next = true;
            }
        }
    }
}

int executerLsPersonnalise(char *commande) {
    char *argv[64]; // Tableau pour stocker les arguments de la commande
    int argc = 0;

    // Tokenisation de la commande
    char *token = strtok(commande, " ");
    while (token != NULL && argc < 63) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL; // Dernier élément doit être NULL pour execvp

    if (argc == 0) {
        return -1; // Pas de commande à exécuter
    }

    // Exécution de la commande
    pid_t pid = fork();
    if (pid == 0) {
        // Processus enfant
        execvp("/home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/ls", argv);
        fprintf(stderr, "execvp error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Échec de fork
        fprintf(stderr, "fork error: %s\n", strerror(errno));
        return -1;
    } else {
        // Processus parent
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            fprintf(stderr, "waitpid error: %s\n", strerror(errno));
        }
        return status;
    }
}