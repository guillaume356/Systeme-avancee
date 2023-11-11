#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <time.h>

#define SIZE 100000000 // 1e8

// Déclaration du tableau global
int tab[SIZE];

// Fonction pour initialiser le tableau avec des valeurs aléatoires
void initialize_array() {

    srand( time(NULL));
    for (int i = 0; i < SIZE; i++) {
        tab[i] = rand() % 1000000000; // Génère un nombre aléatoire entre 0 et 999999999
    }
}

// Fonction pour trouver le minimum et le maximum dans le tableau
void find_min_max(int *min, int *max) {
    *min = INT_MAX;
    *max = INT_MIN;

    for (int i = 0; i < SIZE; i++) {
        if (tab[i] < *min) {
            *min = tab[i];
        }
        if (tab[i] > *max) {
            *max = tab[i];
        }
    }
}

int main() {
    struct timeval start, end;
    int min, max;

    // Initialisation du tableau
    initialize_array();

    // Début du chronomètre
    gettimeofday(&start, NULL);

    // Recherche du min et du max
    find_min_max(&min, &max);

    // Fin du chronomètre
    gettimeofday(&end, NULL);

    // Calcul et affichage du temps écoulé
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

    printf("Min: %d\n", min);
    printf("Max: %d\n", max);
    printf("Temps de recherche: %f secondes\n", time_taken);

    return 0;
}
