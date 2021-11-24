#include "lowtran7.1.c"
#include <time.h>
#include <stdio.h>

int main()
{

    MAIN__();

    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    char buff[100];
    strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
    printf("\nCurrent time: %s.%09ld UTC\n", buff, ts.tv_nsec);
}