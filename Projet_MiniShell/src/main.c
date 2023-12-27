#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    while (1) {
        printf("mini-shell> ");

        char commande[100];
        fgets(commande, sizeof(commande), stdin);
        commande[strcspn(commande, "\n")] = '\0';

        // Commande 'exit'
        if (strcmp(commande, "exit") == 0) {
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
        else {
            printf("%s: command not found\n", commande);
        }
    }

    return 0;
}
