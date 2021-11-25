#include "lowtran7.1.cpp"
#include <time.h>
#include <stdio.h>
#include <iostream>

int main()
{
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    MAIN__();
    clock_gettime(CLOCK_MONOTONIC, &end);

    int rows = sizeof BIG_BUF / sizeof BIG_BUF[0];
    int cols = sizeof BIG_BUF[0] / sizeof(float);

    for (int i = 0; i < rows; i++)
    {

        bool printingRow = BIG_BUF[i][0] != 0 && BIG_BUF[i][1] != NULL;

        if (printingRow)
        {
            printingRow = true;
            std::cout << BIG_BUF[i][0] << '\t' << BIG_BUF[i][1] << std::endl;
        }
    }

    // printf("%lf milliseconds", (end.tv_nsec - start.tv_nsec) / 1e6 + (end.tv_sec - start.tv_sec) * 1e3);
}