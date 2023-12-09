// ls.c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    // Ouvrir le répertoire courant
    DIR *repertoire = opendir(".");
    if (repertoire == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return 1;
    }

    // Lire le contenu du répertoire
    struct dirent *entree;
    while ((entree = readdir(repertoire)) != NULL) {
        printf("%s\n", entree->d_name);
    }

    // Fermer le répertoire
    closedir(repertoire);

    return 0;
}
