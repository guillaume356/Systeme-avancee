// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    while (1) {
        // Afficher le prompt
        printf("mini-shell> ");

        // Lire la commande de l'utilisateur
        char commande[100]; // Déclarer un tableau pour stocker la commande
        fgets(commande, sizeof(commande), stdin);

        // Supprimer le saut de ligne à la fin de la commande lue
        commande[strcspn(commande, "\n")] = '\0';

        // Vérifier si la commande est "ls"
        if (strcmp(commande, "ls") == 0) {
            // Appeler la commande ls depuis le fichier ls.c
            system("./ls");
        } else if(strcmp(commande, "date") == 0) {
            system("./date");
        } else {
            // Si la commande n'est pas "ls", l'afficher
            printf("%s: command not found\n", commande);
        }
    }

    return 0;
}
