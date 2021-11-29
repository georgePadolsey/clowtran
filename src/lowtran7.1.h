#pragma once

// #include <complex.h> @todo change complex to this

// #define DO_FIO_IN 1
// #define DO_FIO_OUT 1
#include "stdio.h"
#include "atmos_data.cpp"
#include "math.h"
#include "stdlib.h"
#include "dolio.cpp"
#include "f2c.h"
#include "fmt.cpp"
#include "err.cpp"
#include "c_div.cpp"
#include "sfe.cpp"
#include "wsle.cpp"
#include "wsfe.cpp"
#include "pow_ci.cpp"
#include "s_copy.cpp"
#include "lwrite.cpp"
#include "lread.cpp"
#include "util.cpp"
#include "fmtlib.cpp"
#include "open.cpp"
#include "close.cpp"
#include "pow_ri.cpp"
#include "pow_zi.cpp"
#include "z_div.cpp"
#include "r_imag.cpp"
#include "wrtfmt.cpp"
#include "wref.cpp"
#include "endfile.cpp"
#include "rsfe.cpp"
#include "rdfmt.cpp"
#include "sig_die.cpp"
#include "gmrain.cpp"
extern int MAIN__(void);