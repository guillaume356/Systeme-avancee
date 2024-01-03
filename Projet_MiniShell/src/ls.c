#include "ls.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Fonction pour lister le contenu d'un répertoire.
// 'repertoirePath' est le chemin vers le répertoire à lister.
// 'all' est un booléen indiquant si tous les fichiers (y compris les fichiers cachés) doivent être listés.
// 'longListing' est un booléen indiquant si un format long (avec plus d'informations) doit être utilisé.
void listerRepertoire(const char *repertoirePath, int all, int longListing) {
    DIR *repertoire = opendir(repertoirePath); // Ouverture du répertoire.
    if (repertoire == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return;
    }

    struct dirent *entree;
    while ((entree = readdir(repertoire)) != NULL) {
        // Si 'all' est faux, les fichiers cachés sont ignorés.
        if (!all && entree->d_name[0] == '.') {
            continue;
        }

        if (longListing) {
            struct stat fileInfo; // Structure pour stocker les informations du fichier.
            char fullPath[1024]; // Chemin complet vers le fichier.
            sprintf(fullPath, "%s/%s", repertoirePath, entree->d_name);
            // Récupération des informations du fichier.
            if (stat(fullPath, &fileInfo) != 0) {
                perror("stat");
                continue;
            }

            // Affichage des informations du fichier (taille et nom).
            printf("%10ld %s\n", fileInfo.st_size, entree->d_name);
        } else {
            // Affichage du nom du fichier seulement.
            printf("%s\n", entree->d_name);
        }
    }

    closedir(repertoire); // Fermeture du répertoire.
}

int main(int argc, char *argv[]) {
    int all = 0;         // Indicateur pour lister tous les fichiers.
    int longListing = 0; // Indicateur pour le format long.

    // Analyse des arguments de la ligne de commande.
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0 || strcmp(argv[i], "-A") == 0) {
            all = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            longListing = 1;
        }
        // Ajouter d'autres options de ligne de commande ici si nécessaire.
    }

    // Appel de la fonction pour lister le répertoire avec les options choisies.
    listerRepertoire(".", all, longListing);
    return 0;
}
