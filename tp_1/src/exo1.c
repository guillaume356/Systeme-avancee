/**
 * \file skeleton.c
 * \brief Exemple basique de parsing d'options.
 * \author Pierre L. <pierre1.leroy@orange.com>
 * \version 0.1
 * \date 10 septembre 2016
 *
 * Exemple basique de parsing d'options avec un fichier C.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>

#define STDOUT 1
#define STDERR 2
#define MAX_PATH_LENGTH 4096
#define TAILLE_TAMPON 4096

#define USAGE_SYNTAX "[OPTIONS] -i INPUT -o OUTPUT"
#define USAGE_PARAMS "OPTIONS:\n\
  -i, --input  INPUT_FILE  : fichier source\n\
  -o, --output OUTPUT_FILE : fichier de destination\n\
***\n\
  -v, --verbose : activer le mode *verbose*\n\
  -h, --help    : afficher cette aide\n\
"

void print_usage(char* nom_binaire) {
    dprintf(1, "USAGE: %s %s\n\n%s\n", nom_binaire, USAGE_SYNTAX, USAGE_PARAMS);
}

void free_if_needed(void* a_liberer) {
    if (a_liberer != NULL) free(a_liberer);
}

char* dup_optarg_str() {
    char* str = NULL;
    if (optarg != NULL) {
        str = strndup(optarg, MAX_PATH_LENGTH);
        if (str == NULL)
            perror(strerror(errno));
    }
    return str;
}

static struct option options_binaire[] = {
        { "help",    no_argument,       0, 'h' },
        { "verbose", no_argument,       0, 'v' },
        { "input",   required_argument, 0, 'i' },
        { "output",  required_argument, 0, 'o' },
        { 0,         0,                 0,  0  }
};

const char* options_chaine = "hvi:o:";

int main(int argc, char** argv) {
    short int mode_verbose = 0;
    char* param_input = NULL;
    char* param_output = NULL;

    int opt = -1;
    int idx_option = -1;

    while ((opt = getopt_long(argc, argv, options_chaine, options_binaire, &idx_option)) != -1) {
        switch (opt) {
            case 'i':
                if (optarg) {
                    param_input = dup_optarg_str();
                }
                break;
            case 'o':
                if (optarg) {
                    param_output = dup_optarg_str();
                }
                break;
            case 'v':
                mode_verbose = 1;
                break;
            case 'h':
                print_usage(argv[0]);
                free_if_needed(param_input);
                free_if_needed(param_output);
                exit(EXIT_SUCCESS);
            default:
                break;
        }
    }

    if (param_input == NULL || param_output == NULL) {
        dprintf(STDERR, "Mauvaise utilisation ! Voir AIDE [--help|-h]\n");
        free_if_needed(param_input);
        free_if_needed(param_output);
        exit(EXIT_FAILURE);
    }

    dprintf(1, "** PARAMS **\n%-8s: %s\n%-8s: %s\n%-8s: %d\n", "input", param_input, "output", param_output, "verbose", mode_verbose);

    int fd_source, fd_destination;
    ssize_t octets_lus, octets_ecrits;
    char tampon[TAILLE_TAMPON];

    fd_source = open(param_input, O_RDONLY);
    if(fd_source == -1) {
        perror("Erreur à l'ouverture du fichier source");
        exit(EXIT_FAILURE);
    }

    fd_destination = open(param_output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd_destination == -1) {
        perror("Erreur à l'ouverture ou à la création du fichier de destination");
        close(fd_source);
        exit(EXIT_FAILURE);
    }

    while((octets_lus = read(fd_source, tampon, TAILLE_TAMPON)) > 0) {
        octets_ecrits = write(fd_destination, tampon, octets_lus);
        if(octets_ecrits != octets_lus) {
            perror("Erreur lors de l'écriture dans le fichier de destination");
            close(fd_source);
            close(fd_destination);
            exit(EXIT_FAILURE);
        }
    }

    if(octets_lus == -1) {
        perror("Erreur lors de la lecture du fichier source");
    }

    close(fd_source);
    close(fd_destination);

    free_if_needed(param_input);
    free_if_needed(param_output);
    return EXIT_SUCCESS;
}