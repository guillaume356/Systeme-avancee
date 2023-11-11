#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <time.h>
#include <pthread.h>

#define SIZE 100000000 // 1e8
int tab[SIZE];

typedef struct {
    int start;
    int end;
    int threadIndex;
    int min;
    int max;
} ThreadData;

void initialize_array() {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        tab[i] = rand() % 1000000000;
    }
}

void* find_min_max(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->min = INT_MAX;
    data->max = INT_MIN;

    for (int i = data->start; i < data->end; i++) {
        if (tab[i] < data->min) {
            data->min = tab[i];
        }
        if (tab[i] > data->max) {
            data->max = tab[i];
        }
    }

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

    // Initialisation du tableau
    initialize_array();

    int segmentSize = SIZE / numThreads;
    struct timeval start, end;
    gettimeofday(&start, NULL);

    // Création des threads
    for (int i = 0; i < numThreads; i++) {
        threadData[i].start = i * segmentSize;
        threadData[i].end = (i + 1) * segmentSize;
        threadData[i].threadIndex = i;
        pthread_create(&threads[i], NULL, find_min_max, &threadData[i]);
    }

    // Attente de la fin des threads et collecte des résultats
    int globalMin = INT_MAX;
    int globalMax = INT_MIN;
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
        if (threadData[i].min < globalMin) globalMin = threadData[i].min;
        if (threadData[i].max > globalMax) globalMax = threadData[i].max;
    }

    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

    printf("Min: %d\n", globalMin);
    printf("Max: %d\n", globalMax);
    printf("Temps de recherche: %f secondes\n", time_taken);

    return 0;
}
