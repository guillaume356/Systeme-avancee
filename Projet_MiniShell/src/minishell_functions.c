#include "minishell_functions.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

// Vérifie si la commande doit être exécutée en arrière-plan
bool is_background_command(char **tokens, int token_count) {
    return token_count > 0 && strcmp(tokens[token_count - 1], "&") == 0;
}

// Exécute une commande en arrière-plan
void execute_command_in_background(char **argv) {
    pid_t pid = fork(); // Crée un processus enfant
    if (pid == 0) {
        // Processus enfant : exécute la commande
        if (execvp(argv[0], argv) == -1) {
            perror("execvp");
        }
        exit(EXIT_FAILURE); // Quitte si execvp échoue
    } else if (pid < 0) {
        // Gestion de l'échec du fork
        perror("fork");
    }
    // Le processus parent continue sans attendre
}

// Parse et exécute la commande saisie par l'utilisateur
void parse_and_execute(char *commande) {
    char *tokens[MAX_TOKENS];
    int token_count = 0;

    // Découpage de la commande en tokens
    char *token = strtok(commande, " ");
    while (token != NULL && token_count < MAX_TOKENS - 1) {
        tokens[token_count++] = token;
        token = strtok(NULL, " ");
    }
    tokens[token_count] = NULL;

    if (token_count == 0) {
        return; // Sort si aucune commande n'est saisie
    }

    int status = 0;
    bool execute_next = true;

    // Vérifie si la commande doit être exécutée en arrière-plan
    if (is_background_command(tokens, token_count)) {
        tokens[token_count - 1] = NULL; // Enlève '&' du tableau d'arguments
        execute_command_in_background(tokens);
    } else {
        // Exécute chaque token en tant que commande
        for (int i = 0; i < token_count; i++) {
            // Gère les opérateurs de contrôle && et ||
            if (strcmp(tokens[i], "&&") == 0) {
                execute_next = (WEXITSTATUS(status) == 0);
            } else if (strcmp(tokens[i], "||") == 0) {
                execute_next = (WEXITSTATUS(status) != 0);
            } else if (execute_next) {
                // Exécute les commandes intégrées et externes
                // ...
                // Réinitialise execute_next pour la prochaine commande
                execute_next = true;
            }
        }
    }
}

// Fonction pour exécuter une version personnalisée de la commande 'ls'
int executerLsPersonnalise(char *commande) {
    char *argv[64]; // Stocke les arguments de la commande
    int argc = 0;

    // Tokenisation de la commande
    char *token = strtok(commande, " ");
    while (token != NULL && argc < 63) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL; // Marque la fin du tableau d'arguments

    if (argc == 0) {
        return -1; // Quitte si aucune commande n'est fournie
    }

    // Exécution de la commande dans un processus enfant
    pid_t pid = fork();
    if (pid == 0) {
        // Processus enfant : exécute la commande 'ls'
        execvp("/home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/ls", argv);
        fprintf(stderr, "execvp error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Gestion de l'échec du fork
        fprintf(stderr, "fork error: %s\n", strerror(errno));
        return -1;
    } else {
        // Processus parent : attend la fin du processus enfant
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            fprintf(stderr, "waitpid error: %s\n", strerror(errno));
        }
        return status;
    }
}