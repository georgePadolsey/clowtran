#include <stdio.h>
#include <emscripten/emscripten.h>
#include "lowtran7.1.cpp"
#include <emscripten/bind.h>

struct buffer
{
    unsigned int pointer;
    unsigned int size;
};

int main()
{
    printf("LOWTRAN 7 Loaded\n");
}

#ifdef __cplusplus
extern "C"
{
#endif

    buffer runLowtran(long model, long itype, float h1, float h2, float range)
    {

        printf("RUN LOWTRAN Called\n");

        LOWTRAN_Card1 card1 = {.model = model, .itype = itype, .im = 1};
        LOWTRAN_Card2 card2 = {};
        LOWTRAN_Card3 card3 = {.h1 = h1, .h2 = h2, .range = range};

        LOWTRAN_ResultBuffer buf;

        _runLowtran(&buf, &card1, nullptr, &card2, nullptr, &card3, nullptr);

        buffer returnBuffer;

        returnBuffer.pointer = (unsigned int)buf.data;
        returnBuffer.size = buf.length * sizeof(float);

        return returnBuffer;
    }

    EMSCRIPTEN_BINDINGS(my_module)
    {
        emscripten::value_array<buffer>("buffer")
            .element(&buffer::pointer)
            .element(&buffer::size);

        emscripten::function("runLowtran", &runLowtran);
    }

#ifdef __cplusplus
}
#endif