#pragma once

// #include <complex.h> @todo change complex to this

// #define DO_FIO_IN 1
// #define DO_FIO_OUT 1

#include "stdio.h"
#include "atmos_data.c"
#include "math.h"
#include "stdlib.h"
#include "dolio.c"
#include "f2c.h"
#include "fmt.c"
#include "err.c"
#include "c_div.c"
#include "sfe.c"
#include "wsle.c"
#include "wsfe.c"
#include "pow_ci.c"
#include "s_copy.c"
#include "lwrite.c"
#include "lread.c"
#include "util.c"
#include "fmtlib.c"
#include "open.c"
#include "close.c"
#include "pow_ri.c"
#include "pow_zi.c"
#include "z_div.c"
#include "r_imag.c"
#include "wrtfmt.c"
#include "wref.c"
#include "endfile.c"
#include "rsfe.c"
#include "rdfmt.c"
#include "sig_die.c"
extern int MAIN__(void);