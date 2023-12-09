#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Déclaration d'une variable globale pour compter les signaux SIGINT.
// 'volatile sig_atomic_t' est utilisé pour garantir que la variable est modifiée
// atomiquement et correctement dans un contexte multithread ou de signal.
volatile sig_atomic_t sigint_count = 0;

void handle_sigint() {
    sigint_count++;
    printf("SIGINT reçu. Nombre de fois: %d\n", sigint_count);
}

void handle_sigterm() {
    printf("SIGTERM reçu. Terminaison du programme.\n");
    _exit(0);
}

int main() {
    printf("Le PID de ce processus est %d\n", getpid());
    // Associer le gestionnaire de signaux 'signal_handler' aux signaux SIGINT et SIGTERM.
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigterm);

    // Boucle infinie : le programme reste dans cette boucle jusqu'à ce qu'il reçoive SIGTERM.
    while (1) {
        pause(); // Met le programme en pause jusqu'à ce qu'un signal soit reçu.
        // C'est plus efficace que d'utiliser une boucle active.
    }

    return 0;
}