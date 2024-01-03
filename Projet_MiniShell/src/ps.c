// ps.c
#include "ps.h"
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

// Fonction pour lister les processus en cours d'exécution
void listerProcessus() {
    DIR *dir;             // Pointeur vers le répertoire
    struct dirent *ent;   // Structure pour lire les informations de l'entrée du répertoire

    printf("Liste des processus :\n");

    // Tenter d'ouvrir le répertoire /proc contenant des informations sur les processus
    dir = opendir("/proc");
    if (dir != NULL) {
        // Lire chaque entrée dans le répertoire
        while ((ent = readdir(dir)) != NULL) {
            // Les dossiers dans /proc avec des noms numériques représentent des processus, vérifier et afficher le PID
            if (ent->d_type == DT_DIR && atoi(ent->d_name) > 0) {
                printf("PID: %s\n", ent->d_name);
            }
        }
        closedir(dir); // Fermer le répertoire une fois terminé
    } else {
        perror("Erreur en ouvrant /proc"); // Afficher l'erreur si /proc ne peut pas être ouvert
    }
}

// Fonction principale : point d'entrée du programme
int main() {
    listerProcessus();  // Appeler la fonction pour lister les processus
    return 0; // Terminer le programme avec un statut de sortie réussi
}
