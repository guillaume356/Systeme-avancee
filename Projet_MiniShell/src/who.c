// who.c
#include "who.h"
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// Fonction pour lister les utilisateurs actuellement connectés
void listerUtilisateurs() {
    int fd; // Descripteur de fichier pour lire les informations utmp
    struct utmp entry; // Structure pour stocker les informations de chaque entrée

    // Ouvrir le fichier utmp pour lire les informations de connexion
    fd = open(_PATH_UTMP, O_RDONLY);
    if (fd < 0) {
        perror("Erreur lors de l'ouverture du fichier utmp");
        return;
    }

    // Lire chaque entrée du fichier utmp
    while (read(fd, &entry, sizeof(entry)) > 0) {
        // Vérifier si l'entrée correspond à un processus utilisateur
        if (entry.ut_type == USER_PROCESS) {
            char username[UT_NAMESIZE + 1]; // Tableau pour stocker le nom d'utilisateur
            snprintf(username, sizeof(username), "%s", entry.ut_user); // Copier le nom d'utilisateur dans username
            printf("%s\n", username); // Afficher le nom d'utilisateur
        }
    }

    close(fd); // Fermer le fichier une fois terminé
}

// Fonction principale : point d'entrée du programme
int main() {
    listerUtilisateurs();  // Appeler la fonction pour lister les utilisateurs
    return 0; // Terminer le programme avec un statut de sortie réussi
}
