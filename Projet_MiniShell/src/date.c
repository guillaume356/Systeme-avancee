#include "date.h"
#include <stdio.h>
#include <stdlib.h>

// Fonction pour afficher la date et l'heure actuelles
void print_current_date_and_time() {
    time_t t;           // Déclarer une variable pour stocker le temps actuel
    struct tm *tm_info; // Pointeur vers une structure tm contenant les détails de la date et de l'heure

    time(&t);           // Obtenir le temps actuel et le stocker dans t
    tm_info = localtime(&t); // Convertir le temps en temps local et stocker le résultat dans tm_info

    // Afficher la date et l'heure actuelles en utilisant asctime pour convertir tm_info en chaîne lisible
    printf("Date et heure actuelles : %s", asctime(tm_info));
}

// Fonction principale : point d'entrée du programme
int main() {
    print_current_date_and_time(); // Appeler la fonction pour afficher la date et l'heure actuelles
    return 0; // Terminer le programme avec un statut de sortie réussi
}