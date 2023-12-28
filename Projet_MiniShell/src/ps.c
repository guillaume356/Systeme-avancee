#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main() {
    DIR *dir;
    struct dirent *ent;

    printf("Liste des processus :\n");

    // Ouvrir le répertoire /proc
    dir = opendir("/proc");
    if (dir != NULL) {
        // Lire les entrées du répertoire
        while ((ent = readdir(dir)) != NULL) {
            // Vérifier si le nom de l'entrée est un numéro (PID)
            if (ent->d_type == DT_DIR && atoi(ent->d_name) > 0) {
                printf("PID: %s\n", ent->d_name);
            }
        }
        closedir(dir);
    } else {
        perror("Erreur en ouvrant /proc");
    }

    return 0;
}
