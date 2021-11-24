#include "lowtran7.1.cpp"
#include <time.h>
#include <stdio.h>

int main()
{
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    MAIN__();

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("%lf milliseconds", (end.tv_nsec - start.tv_nsec) / 1e6 + (end.tv_sec - start.tv_sec) * 1e3);
}