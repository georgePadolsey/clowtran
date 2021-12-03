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

    /**
     * @brief Run LOWTRAN7 rawest input possible (literally inputting card valeus)
     *
     *
     * @param card1
     * @param card1a
     * @param card2
     * @param card2a
     * @param card2d
     * @param card3
     * @param card4
     * @return buffer
     */
    buffer runLowtran(LOWTRAN_Card1 card1,
                      LOWTRAN_Card1a card1a,
                      LOWTRAN_Card1b card1b,
                      LOWTRAN_Card2 card2,
                      LOWTRAN_Card2a card2a,
                      LOWTRAN_Card2b card2b,
                      LOWTRAN_Card2c card2c,
                      LOWTRAN_Card2d card2d,
                      LOWTRAN_Card3 card3,
                      LOWTRAN_Card3a1 card3a1,
                      LOWTRAN_Card3a2 card3a2,
                      LOWTRAN_Card4 card4)
    {

        printf("RUN LOWTRAN Called\n");

        LOWTRAN_ResultBuffer buf;

        _runLowtran(&buf, &card1, &card1a, &card1b, &card2, &card2a, &card2b, &card2c, &card2d, &card3, &card3a1, &card3a2, &card4);

        buffer returnBuffer;

        returnBuffer.pointer = (unsigned int)buf.data;
        returnBuffer.size = buf.length * sizeof(float);

        return returnBuffer;
    }

    EMSCRIPTEN_BINDINGS(my_module)
    {

        // emscripten bindings
        // @see
        // https://developers.google.com/web/updates/2018/08/embind

        emscripten::value_array<buffer>("buffer")
            .element(&buffer::pointer)
            .element(&buffer::size);

        emscripten::value_object<LOWTRAN_Card1>("LOWTRAN_Card1")
            .field("model", &LOWTRAN_Card1::model)
            .field("itype", &LOWTRAN_Card1::itype)
            .field("iemsct", &LOWTRAN_Card1::iemsct)
            .field("m1", &LOWTRAN_Card1::m1)
            .field("m2", &LOWTRAN_Card1::m2)
            .field("m3", &LOWTRAN_Card1::m3)
            .field("im", &LOWTRAN_Card1::im)
            .field("noprt", &LOWTRAN_Card1::noprt)
            .field("tbound", &LOWTRAN_Card1::tbound)
            .field("salb", &LOWTRAN_Card1::salb);

        emscripten::value_object<LOWTRAN_Card1a>("LOWTRAN_Card1a")
            .field("m4", &LOWTRAN_Card1a::m4)
            .field("m5", &LOWTRAN_Card1a::m5)
            .field("m6", &LOWTRAN_Card1a::m6)
            .field("mdef", &LOWTRAN_Card1a::mdef)
            .field("ird1", &LOWTRAN_Card1a::ird1)
            .field("ird2", &LOWTRAN_Card1a::ird2);

        emscripten::value_object<LOWTRAN_Card1b>("LOWTRAN_Card1b")
            // .field("junit", &LOWTRAN_Card1b::junit) @todo
            // .field("wmol", &LOWTRAN_Card1b::wmol) @todo
            .field("wair1", &LOWTRAN_Card1b::wair1)
            .field("jlow", &LOWTRAN_Card1b::jlow);

        emscripten::value_object<LOWTRAN_Card2>("LOWTRAN_Card2")
            .field("ihaze", &LOWTRAN_Card2::ihaze)
            .field("iseasn", &LOWTRAN_Card2::iseasn)
            .field("ivulcn", &LOWTRAN_Card2::ivulcn)
            .field("icstl", &LOWTRAN_Card2::icstl)
            .field("icld", &LOWTRAN_Card2::icld)
            .field("ivsa", &LOWTRAN_Card2::ivsa)
            .field("vis", &LOWTRAN_Card2::vis)
            .field("wss", &LOWTRAN_Card2::wss)
            .field("whh", &LOWTRAN_Card2::whh)
            .field("rainrt", &LOWTRAN_Card2::rainrt);

        emscripten::value_object<LOWTRAN_Card2a>("LOWTRAN_Card2a")
            .field("cthik", &LOWTRAN_Card2a::cthik)
            .field("calt", &LOWTRAN_Card2a::calt)
            .field("cext", &LOWTRAN_Card2a::cext)
            .field("iseed", &LOWTRAN_Card2a::iseed);

        emscripten::value_object<LOWTRAN_Card2b>("LOWTRAN_Card2b")
            .field("zcvsa", &LOWTRAN_Card2b::zcvsa)
            .field("ztvsa", &LOWTRAN_Card2b::ztvsa)
            .field("zinvsa", &LOWTRAN_Card2b::zinvsa);

        emscripten::value_object<LOWTRAN_Card2c>("LOWTRAN_Card2c")
            .field("ml", &LOWTRAN_Card2c::ml)
            .field("title", &LOWTRAN_Card2c::title);

        emscripten::value_object<LOWTRAN_Card2d>("LOWTRAN_Card2d");
        // .field("ireg", &LOWTRAN_Card2d::ireg) @todo
        // .field("altb", &LOWTRAN_Card2d::altb) @todo
        // .field("iregc", &LOWTRAN_Card2d::iregc); @todo

        emscripten::value_object<LOWTRAN_Card3>("LOWTRAN_Card3")
            .field("h1", &LOWTRAN_Card3::h1)
            .field("h2", &LOWTRAN_Card3::h2)
            .field("angle", &LOWTRAN_Card3::angle)
            .field("range", &LOWTRAN_Card3::range)
            .field("beta", &LOWTRAN_Card3::beta)
            .field("re", &LOWTRAN_Card3::re)
            .field("len", &LOWTRAN_Card3::len);

        emscripten::value_object<LOWTRAN_Card3a1>("LOWTRAN_Card3a1")
            .field("iparm", &LOWTRAN_Card3a1::iparm)
            .field("iph", &LOWTRAN_Card3a1::iph)
            .field("iday", &LOWTRAN_Card3a1::iday)
            .field("isourc", &LOWTRAN_Card3a1::isourc);

        emscripten::value_object<LOWTRAN_Card3a2>("LOWTRAN_Card3a2")
            .field("parm1", &LOWTRAN_Card3a2::parm1)
            .field("parm2", &LOWTRAN_Card3a2::parm2)
            .field("parm3", &LOWTRAN_Card3a2::parm3)
            .field("parm4", &LOWTRAN_Card3a2::parm4)
            .field("time", &LOWTRAN_Card3a2::time)
            .field("psio", &LOWTRAN_Card3a2::psio)
            .field("anglem", &LOWTRAN_Card3a2::anglem)
            .field("g", &LOWTRAN_Card3a2::g);

        emscripten::value_object<LOWTRAN_Card4>("LOWTRAN_Card4")
            .field("v1", &LOWTRAN_Card4::v1)
            .field("v2", &LOWTRAN_Card4::v2)
            .field("dv", &LOWTRAN_Card4::dv);

        emscripten::function("runLowtran", &runLowtran);
    }

#ifdef __cplusplus
}
#endif