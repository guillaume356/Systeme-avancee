#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <time.h>
#include <pthread.h>

#define SIZE 100000000 // 1e8
int tab[SIZE];
int globalMin = INT_MAX;
int globalMax = INT_MIN;
pthread_mutex_t minMaxMutex;

typedef struct {
    int start;
    int end;
} ThreadData;

void initialize_array() {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        tab[i] = rand() % 1000000000;
    }
}

void* find_min_max(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int localMin = INT_MAX;
    int localMax = INT_MIN;

    for (int i = data->start; i < data->end; i++) {
        if (tab[i] < localMin) {
            localMin = tab[i];
        }
        if (tab[i] > localMax) {
            localMax = tab[i];
        }
    }

    pthread_mutex_lock(&minMaxMutex);
    if (localMin < globalMin) globalMin = localMin;
    if (localMax > globalMax) globalMax = localMax;
    pthread_mutex_unlock(&minMaxMutex);

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }

    int numThreads = atoi(argv[1]);
    pthread_t threads[numThreads];
    ThreadData threadData[numThreads];

    pthread_mutex_init(&minMaxMutex, NULL);

    // Initialisation du tableau
    initialize_array();

    int segmentSize = SIZE / numThreads;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Création des threads
    for (int i = 0; i < numThreads; i++) {
        threadData[i].start = i * segmentSize;
        threadData[i].end = (i + 1) * segmentSize;
        pthread_create(&threads[i], NULL, find_min_max, &threadData[i]);
    }

    // Attente de la fin des threads
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

    printf("Min: %d\n", globalMin);
    printf("Max: %d\n", globalMax);
    printf("Temps de recherche: %f secondes\n", time_taken);

    pthread_mutex_destroy(&minMaxMutex);

    return 0;
}
