#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int fd = open(_PATH_UTMP, O_RDONLY);
    struct utmp entry;

    if (fd < 0) {
        perror("Erreur lors de l'ouverture du fichier utmp");
        return 1;
    }

    while (read(fd, &entry, sizeof(entry)) > 0) {
        if (entry.ut_type == USER_PROCESS) {
            char username[UT_NAMESIZE + 1]; // +1 pour le caractère nul
            snprintf(username, sizeof(username), "%s", entry.ut_user);
            printf("%s\n", username);
        }
    }

    close(fd);
    return 0;
}
