#include "minishell_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h> // Pour l'utilisation de errno dans la gestion d'erreurs
#include <string.h> // Pour strerror pour convertir errno en message d'erreur

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
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Processus parent
        int status;
        waitpid(pid, &status, 0);
        return status;
    } else {
        // Échec de fork
        perror("fork");
        return -1;
    }
}

int main() {
    // Chemin vers le fichier d'historique des commandes
    const char *chemin_historique = "/home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/historique.txt";
    FILE *fichier_historique;

    // Boucle principale du shell
    while (1) {
        // Lire une ligne de commande
        char *commande = readline("mini-shell> ");

        // Sortir de la boucle si aucune commande n'est entrée (EOF ou Ctrl+D)
        if (!commande) break;

        // Enregistrer les commandes non vides dans l'historique
        if (strlen(commande) > 0) {
            add_history(commande);

            // Enregistrer la commande dans le fichier d'historique
            fichier_historique = fopen(chemin_historique, "a");
            if (!fichier_historique) {
                // Gestion d'erreur pour fopen
                fprintf(stderr, "fopen error: %s\n", strerror(errno));
            } else {
                fprintf(fichier_historique, "%s\n", commande);
                // Gestion d'erreur pour fclose
                if (fclose(fichier_historique) != 0) {
                    fprintf(stderr, "fclose error: %s\n", strerror(errno));
                }
            }
        }

        // Traitement des commandes intégrées
        if (strcmp(commande, "historique") == 0) {
            // Afficher l'historique des commandes
            char ligne[100];
            fichier_historique = fopen(chemin_historique, "r");
            if (!fichier_historique) {
                fprintf(stderr, "fopen error: %s\n", strerror(errno));
            } else {
                while (fgets(ligne, sizeof(ligne), fichier_historique)) {
                    printf("%s", ligne);
                }
                if (fclose(fichier_historique) != 0) {
                    fprintf(stderr, "fclose error: %s\n", strerror(errno));
                }
            }
        } else if (strcmp(commande, "exit") == 0) {
            // Quitter le shell
            printf("Fermeture de l'interpréteur.\n");
            break;
        } else if (strncmp(commande, "cd", 2) == 0) {
            // Changer de répertoire
            char* path = commande + 3;
            if (chdir(path) != 0) {
                fprintf(stderr, "cd error: %s\n", strerror(errno));
            }
        } else if (strcmp(commande, "pwd") == 0) {
            // Afficher le répertoire de travail actuel
            char cwd[1024];
            if (!getcwd(cwd, sizeof(cwd))) {
                fprintf(stderr, "getcwd error: %s\n", strerror(errno));
            } else {
                printf("%s\n", cwd);
            }
        } else if (strncmp(commande, "echo", 4) == 0) {
            // Afficher un message
            printf("%s\n", commande + 5);
        } else {
            // Exécuter des commandes externes
            if (strncmp(commande, "ls", 2) == 0) {
                executerLsPersonnalise(commande);
            } else if (strcmp(commande, "date") == 0) {
                system("/home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/date");
            } else if (strcmp(commande, "who") == 0) {
                system("/home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/who");
            } else if (strcmp(commande, "ps") == 0) {
                system("/home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/ps");
            }

            // Traitement de la commande saisie
            parse_and_execute(commande);
        }
<<<<<<< HEAD
            // Commandes externes
        if (strncmp(commande, "ls", 2) == 0) {
            executerLsPersonnalise(commande);
        }
        else if (strcmp(commande, "date") == 0) {
            system("/home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/date");
        }
        else if (strcmp(commande, "who") == 0) {
            system("/home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/who");
        }
        else if (strcmp(commande, "ps") == 0) {
            system("/home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/ps");
        }

        // Libérer la mémoire allouée pour la commande
        free(commande);
    }
    return 0;
}
