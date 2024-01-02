// who.c
#include "who.h"
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void listerUtilisateurs() {
    int fd = open(_PATH_UTMP, O_RDONLY);
    struct utmp entry;

    if (fd < 0) {
        perror("Erreur lors de l'ouverture du fichier utmp");
        return;
    }

    while (read(fd, &entry, sizeof(entry)) > 0) {
        if (entry.ut_type == USER_PROCESS) {
            char username[UT_NAMESIZE + 1]; // +1 pour le caractère nul
            snprintf(username, sizeof(username), "%s", entry.ut_user);
            printf("%s\n", username);
        }
    }

    close(fd);
}

int main() {
    listerUtilisateurs();
    return 0;
}
