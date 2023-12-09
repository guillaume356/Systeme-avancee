// date.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    printf("Date et heure actuelles : %s", asctime(tm_info));

    return 0;
}
