// date.c
#include "date.h"
#include <stdio.h>
#include <stdlib.h>

void print_current_date_and_time() {
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    printf("Date et heure actuelles : %s", asctime(tm_info));
}

int main() {
    print_current_date_and_time();
    return 0;
}
