#include "lowtran7.1.cpp"
#include <time.h>
#include <stdio.h>
#include <iostream>

int main()
{

    for (int i = 0; i < 500; i++)
    {

        LOWTRAN_Card1 card1 = {.model = 1, .itype = 2, .im = 1};
        LOWTRAN_Card2 card2 = {};
        LOWTRAN_Card3 card3 = {.h1 = 5, .h2 = 10, .range = 10};

        LOWTRAN_ResultBuffer buf;

        _runLowtran(&buf, &card1, nullptr, nullptr, &card2, nullptr, nullptr, nullptr, nullptr, &card3, nullptr, nullptr, nullptr);
        printf("%f %f\n", buf.data[500], buf.data[501]);
    }

    return 0;
}
