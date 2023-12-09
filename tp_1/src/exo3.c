#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define STDOUT 1
#define STDERR 2

#define MAX_PATH_LENGTH 4096


#define USAGE_SYNTAX "[OPTIONS] -i INPUT -o OUTPUT"
#define USAGE_PARAMS "OPTIONS:\n\
  -i, --input  INPUT_FILE  : input file\n\
  -o, --output OUTPUT_FILE : output file\n\
***\n\
  -v, --verbose : enable *verbose* mode\n\
  -h, --help    : display this help\n\
"

/**
 * Procedure which displays binary usage
 * by printing on stdout all available options
 *
 * \return void
 */
void print_usage(char* bin_name)
{
    dprintf(1, "USAGE: %s %s\n\n%s\n", bin_name, USAGE_SYNTAX, USAGE_PARAMS);
}


/**
 * Procedure checks if variable must be free
 * (check: ptr != NULL)
 *
 * \param void* to_free pointer to an allocated mem
 * \see man 3 free
 * \return void
 */
void free_if_needed(void* to_free)
{
    if (to_free != NULL) free(to_free);
}


/**
 *
 * \see man 3 strndup
 * \see man 3 perror
 * \return
 */
char* dup_optarg_str()
{
    char* str = NULL;

    if (optarg != NULL)
    {
        str = strndup(optarg, MAX_PATH_LENGTH);

        // Checking if ERRNO is set
        if (str == NULL)
            perror(strerror(errno));
    }

    return str;
}


/**
 * Binary options declaration
 * (must end with {0,0,0,0})
 *
 * \see man 3 getopt_long or getopt
 * \see struct option definition
 */
static struct option binary_opts[] =
        {
                { "help",    no_argument,       0, 'h' },
                { "verbose", no_argument,       0, 'v' },
                { "input",   required_argument, 0, 'i' },
                { "output",  required_argument, 0, 'o' },
                { 0,         0,                 0,  0  }
        };

/**
 * Binary options string
 * (linked to optionn declaration)
 *
 * \see man 3 getopt_long or getopt
 */
const char* binary_optstr = "hvi:o:";



/**
 * Binary main loop
 *
 * \return 1 if it exit successfully
 */
int main(int argc, char** argv)
{
    /**
     * Binary variables
     * (could be defined in a structure)
     */
    short int is_verbose_mode = 0;
    char* bin_input_param = NULL;
    char* bin_output_param = NULL;

    // Parsing options
    int opt = -1;
    int opt_idx = -1;

    while ((opt = getopt_long(argc, argv, binary_optstr, binary_opts, &opt_idx)) != -1)
    {
        switch (opt)
        {
            case 'i':
                //input param
                if (optarg)
                {
                    bin_input_param = dup_optarg_str();
                }
                break;
            case 'o':
                //output param
                if (optarg)
                {
                    bin_output_param = dup_optarg_str();
                }
                break;
            case 'v':
                //verbose mode
                is_verbose_mode = 1;
                break;
            case 'h':
                print_usage(argv[0]);

                free_if_needed(bin_input_param);
                free_if_needed(bin_output_param);

                exit(EXIT_SUCCESS);
            default :
                break;
        }
    }

    /**
     * Checking binary requirements
     * (could defined in a separate function)
     */
    if (bin_input_param == NULL || bin_output_param == NULL)
    {
        dprintf(STDERR, "Bad usage! See HELP [--help|-h]\n");

        // Freeing allocated data
        free_if_needed(bin_input_param);
        free_if_needed(bin_output_param);
        // Exiting with a failure ERROR CODE (== 1)
        exit(EXIT_FAILURE);
    }


    // Printing params
    dprintf(1, "** PARAMS **\n%-8s: %s\n%-8s: %s\n%-8s: %d\n",
            "input",   bin_input_param,
            "output",  bin_output_param,
            "verbose", is_verbose_mode);

    // Business logic must be implemented at this point

    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    struct passwd *fileUser;
    struct group *fileGroup;
    char filepath[MAX_PATH_LENGTH];
    char dateStr[20];  // Pour stocker la date formatée

    // Ouvrir le répertoire
    dir = opendir(bin_input_param);
    if(dir == NULL) {
        perror("Erreur en ouvrant le répertoire");
        free_if_needed(bin_input_param);
        free_if_needed(bin_output_param);
        exit(EXIT_FAILURE);
    }

    // Lire chaque entrée du répertoire
    while ((entry = readdir(dir)) != NULL) {
        // Construire le chemin complet du fichier
        snprintf(filepath, sizeof(filepath), "%s/%s", bin_input_param, entry->d_name);

        // Obtenir les informations sur le fichier
        if(stat(filepath, &fileStat) == -1) {
            perror("Erreur lors de l'obtention des informations du fichier");
            continue;
        }

        // Obtenir le propriétaire et le groupe du fichier
        fileUser = getpwuid(fileStat.st_uid);
        fileGroup = getgrgid(fileStat.st_gid);

        // Formater la date de la dernière modification
        strftime(dateStr, sizeof(dateStr), "%d%m%y @ %Hh%M", localtime(&fileStat.st_mtime));

        // Afficher les informations
        printf("%s – %o %s : %s – %lld – %s\n",
               entry->d_name,
               fileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO),  // Afficher seulement les permissions
               fileUser ? fileUser->pw_name : "",
               fileGroup ? fileGroup->gr_name : "",
               (long long)fileStat.st_size,
               dateStr);
    }

    // Fermer le répertoire
    closedir(dir);


    // Freeing allocated data
    free_if_needed(bin_input_param);
    free_if_needed(bin_output_param);


    return EXIT_SUCCESS;
}
