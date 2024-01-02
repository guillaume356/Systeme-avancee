#include "ls.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void listerRepertoire(const char *repertoirePath, int all, int longListing) {
    DIR *repertoire = opendir(repertoirePath);
    if (repertoire == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return;
    }

    struct dirent *entree;
    while ((entree = readdir(repertoire)) != NULL) {
        if (!all && entree->d_name[0] == '.') {
            continue; // Ignorer les fichiers cachés pour l'option -A et -a
        }

        if (longListing) {
            // Ajouter ici des informations supplémentaires pour l'option -l
            struct stat fileInfo;
            char fullPath[1024];
            sprintf(fullPath, "%s/%s", repertoirePath, entree->d_name);
            if (stat(fullPath, &fileInfo) != 0) {
                perror("stat");
                continue;
            }

            printf("%10ld %s\n", fileInfo.st_size, entree->d_name); // Exemple simplifié
        } else {
            printf("%s\n", entree->d_name);
        }
    }

    closedir(repertoire);
}

int main(int argc, char *argv[]) {
    int all = 0;
    int longListing = 0;

    // Analyse des arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0 || strcmp(argv[i], "-A") == 0) {
            all = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            longListing = 1;
        }
        // Ajouter ici d'autres options
    }

    listerRepertoire(".", all, longListing);
    return 0;
}
