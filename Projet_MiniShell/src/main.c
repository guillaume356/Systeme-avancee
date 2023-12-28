#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    FILE *fichier_historique;
    const char *chemin_historique = "/home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/historique.txt";
    char *commande;

    while (1) {
        commande = readline("mini-shell> ");
        if (!commande) break; // Sortie si commande est NULL (Ctrl+D)

        // Ajouter la commande à l'historique de readline
        if (strlen(commande) > 0) {
            add_history(commande);

            // Enregistrer la commande dans le fichier d'historique
            fichier_historique = fopen(chemin_historique, "a");
            if (fichier_historique != NULL) {
                fprintf(fichier_historique, "%s\n", commande);
                fclose(fichier_historique);
            }
        }

        // Commande 'historique' pour afficher l'historique des commandes
        if (strcmp(commande, "historique") == 0) {
            char ligne[100];
            FILE *fichier = fopen(chemin_historique, "r");
            if (fichier) {
                while (fgets(ligne, sizeof(ligne), fichier)) {
                    printf("%s", ligne);
                }
                fclose(fichier);
            } else {
                perror("Erreur en lisant l'historique");
            }
        }
            // Commande 'exit'
        else if (strcmp(commande, "exit") == 0) {
            printf("Fermeture de l'interpréteur.\n");
            break;
        }
            // Commande 'cd'
        else if (strncmp(commande, "cd", 2) == 0) {
            char* path = commande + 3;
            if (chdir(path) != 0) {
                perror("cd");
            }
        }
            // Commande 'pwd'
        else if (strcmp(commande, "pwd") == 0) {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                perror("pwd");
            }
        }
            // Commande 'echo'
        else if (strncmp(commande, "echo", 4) == 0) {
            printf("%s\n", commande + 5);
        }
            // Commandes externes
        else if (strcmp(commande, "ls") == 0) {
            system("/home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/ls");
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
        else {
            printf("%s: command not found\n", commande);
        }
    }

    return 0;
}
