#pragma once
/* f2c.h  --  Standard Fortran to C header file */

/**  barf  [ba:rf]  2.  "He suggested using FORTRAN, and everybody barfed."

	- From The Shogakukan DICTIONARY OF NEW ENGLISH (Second edition) */
#include "math.h"
#include "stdio.h"

typedef long int integer;
typedef unsigned long int uinteger;
typedef char *address;
typedef short int shortint;
typedef float real;
typedef double doublereal;
typedef struct
{
    real r, i;
} complex;
typedef struct
{
    doublereal r, i;
} doublecomplex;
typedef long int logical;
typedef short int shortlogical;
typedef char logical1;
typedef char integer1;
#ifdef INTEGER_STAR_8                /* Adjust for integer*8. */
typedef long long longint;           /* system-dependent */
typedef unsigned long long ulongint; /* system-dependent */
#define qbit_clear(a, b) ((a) & ~((ulongint)1 << (b)))
#define qbit_set(a, b) ((a) | ((ulongint)1 << (b)))
#endif

#define TRUE_ (1)
#define FALSE_ (0)

/* Extern is for use with -E */
#ifndef Extern
#define Extern extern
#endif

/* I/O stuff */

typedef long int flag;
typedef long int ftnlen;
typedef long int ftnint;

/*external read, write*/
typedef struct
{
    flag cierr;
    ftnint ciunit;
    flag ciend;
    char *cifmt;
    ftnint cirec;
} cilist;

/*internal read, write*/
typedef struct
{
    flag icierr;
    char *iciunit;
    flag iciend;
    char *icifmt;
    ftnint icirlen;
    ftnint icirnum;
} icilist;

/*open*/
typedef struct
{
    flag oerr;
    ftnint ounit;
    char *ofnm;
    ftnlen ofnmlen;
    char *osta;
    char *oacc;
    char *ofm;
    ftnint orl;
    char *oblnk;
} olist;

/*close*/
typedef struct
{
    flag cerr;
    ftnint cunit;
    char *csta;
} cllist;

/*rewind, backspace, endfile*/
typedef struct
{
    flag aerr;
    ftnint aunit;
} alist;

/* inquire */
typedef struct
{
    flag inerr;
    ftnint inunit;
    char *infile;
    ftnlen infilen;
    ftnint *inex; /*parameters in standard's order*/
    ftnint *inopen;
    ftnint *innum;
    ftnint *innamed;
    char *inname;
    ftnlen innamlen;
    char *inacc;
    ftnlen inacclen;
    char *inseq;
    ftnlen inseqlen;
    char *indir;
    ftnlen indirlen;
    char *infmt;
    ftnlen infmtlen;
    char *inform;
    ftnint informlen;
    char *inunf;
    ftnlen inunflen;
    ftnint *inrecl;
    ftnint *innrec;
    char *inblank;
    ftnlen inblanklen;
} inlist;

#define VOID void

union Multitype
{ /* for multiple entry points */
    integer1 g;
    shortint h;
    integer i;
    /* longint j; */
    real r;
    doublereal d;
    complex c;
    doublecomplex z;
};

typedef union Multitype Multitype;

/*typedef long int Long;*/ /* No longer used; formerly in Namelist */

struct Vardesc
{ /* for Namelist */
    char *name;
    char *addr;
    ftnlen *dims;
    int type;
};
typedef struct Vardesc Vardesc;

struct Namelist
{
    char *name;
    Vardesc **vars;
    int nvars;
};
typedef struct Namelist Namelist;

// removed by GP to not interfere with STDLIB #define abs(x) ((x) >= 0 ? (x) : -(x))

#define dabs(x) (double)fabs(x)
#define max(a, b)                   \
    (                               \
        {                           \
            __typeof__(a) _a = (a); \
            __typeof__(b) _b = (b); \
            _a > _b ? _a : _b;      \
        })

#define min(a, b)                   \
    (                               \
        {                           \
            __typeof__(a) _a = (a); \
            __typeof__(b) _b = (b); \
            _a < _b ? _a : _b;      \
        })
#define bit_test(a, b) ((a) >> (b)&1)
#define bit_clear(a, b) ((a) & ~((uinteger)1 << (b)))
#define bit_set(a, b) ((a) | ((uinteger)1 << (b)))

double pow_dd(double *ap, double *bp)
{
    return pow(*ap, *bp);
}

int s_stop(char *s, ftnlen n)
{
    int i;

    if (n > 0)
    {
        fprintf(stderr, "STOP ");
        for (i = 0; i < n; ++i)
            putc(*s++, stderr);
        fprintf(stderr, " statement executed\n");
    }

    exit(0);

    return 0; /* NOT REACHED */
}

// @todo update to use actual log from maths library
// haven't updated yet as want to make sure no numerical errors!
#define log10e 0.43429448190325182765
double r_lg10(real *x)
{
    return (log10e * log(*x));
}

double r_mod(real *x, real *y)
{
    double quotient;
    if ((quotient = (double)*x / *y) >= 0)
        quotient = floor(quotient);
    else
        quotient = -floor(-quotient);
    return (*x - (*y) * quotient);
}

/* procedure parameter types for -A and -C++ */

#define F2C_proc_par_types 1

/* E_fp is for real functions when -R is not specified */
typedef VOID C_f;       /* complex function */
typedef VOID H_f;       /* character function */
typedef VOID Z_f;       /* double complex function */
typedef doublereal E_f; /* real function with -R not specified */
