#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Déclaration d'une variable globale pour compter les signaux SIGINT.
// 'volatile sig_atomic_t' est utilisé pour garantir que la variable est modifiée
// atomiquement et correctement dans un contexte multithread ou de signal.
volatile sig_atomic_t sigint_count = 0;

// Définition de la fonction qui gère les signaux.
// Cette fonction est appelée automatiquement lorsqu'un signal SIGINT ou SIGTERM est reçu.
void signal_handler(int signal) {
    if (signal == SIGINT) {
        // Si le signal est SIGINT, incrémenter le compteur.
        ++sigint_count;
    } else if (signal == SIGTERM) {
        // Si le signal est SIGTERM, afficher le nombre de SIGINT reçus et terminer le programme.
        printf("Fin du programme. Nombre de SIGINT reçus : %d\n", sigint_count);
        exit(0);
    }
}

int main() {
    printf("Le PID de ce processus est %d\n", getpid());
    // Associer le gestionnaire de signaux 'signal_handler' aux signaux SIGINT et SIGTERM.
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // Boucle infinie : le programme reste dans cette boucle jusqu'à ce qu'il reçoive SIGTERM.
    while (1) {
        pause(); // Met le programme en pause jusqu'à ce qu'un signal soit reçu.
        // C'est plus efficace que d'utiliser une boucle active.
    }

    return 0;
}