#pragma once
// #include <complex.h> @todo change complex to this
#define f2h_disabled 1

#ifndef f2h_disabled
#include "f2c.h"
#endif

#ifdef f2h_disabled

#include "math.h"

typedef float real;
typedef double doublereal;

typedef long int flag;
typedef long int ftnlen;
typedef long int ftnint;

typedef struct
{
    float r, i;
} complex;
typedef struct
{
    double r, i;
} doublecomplex;

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

typedef struct
{
    flag cierr;
    ftnint ciunit;
    flag ciend;
    char *cifmt;
    ftnint cirec;
} cilist;

#define dabs(x) (double)abs(x)
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
#endif

extern int MAIN__(void);