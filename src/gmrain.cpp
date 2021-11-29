

double gmrain_(float *freq, float *t, float *rate)
{
    /* Initialized data */

    static float wvntbl[35] = {0.f, .0667f, .1f, .1111f, .125f, .1429f, .1538f,
                               .1667f, .1818f, .2f, .25f, .3333f, .5f, 1.f, 1.25f, 2.f, 3.3333f, 4.f, 5.f,
                               6.6667f, 10.f, 13.3333f, 16.6667f, 20.f, 23.2558f, 26.6667f, 30.303f,
                               33.3333f, 50.f, 80.f, 120.f, 180.f, 250.f, 300.f, 350.f};
    static float rattab[9] = {.25f, 1.25f, 2.5f, 5.f, 12.5f, 25.f, 50.f, 100.f, 150.f};
    static float tfreq[8] = {0.f, .1f, .3125f, .8f, 2.f, 10.f, 33.3333f, 350.f};
    static float tmptab[5] = {273.15f, 283.15f, 293.15f, 303.15f, 313.15f};
    static float ratlim = .05f;
    static long c__4 = 4;
    static struct
    {
        float e_1[315];
    } equiv_8 = {1.272f, 1.332f, 1.361f, 1.368f, 1.393f, 1.421f, 1.439f,
                 1.466f, 1.499f, 1.541f, 1.682f, 1.951f, 2.571f, 3.575f,
                 3.808f, 4.199f, 3.665f, 3.161f, 2.462f, 1.632f, .8203f,
                 .4747f, .3052f, .2113f, .1551f, .1168f, .08958f, .07338f,
                 .03174f, .01178f, .005016f, .002116f, .001123f, 8.113e-4f,
                 6.26e-4f, 4.915f, 5.257f, 5.518f, 5.632f, 5.807f, 6.069f,
                 6.224f, 6.452f, 6.756f, 7.132f, 8.453f, 11.32f, 16.85f,
                 21.77f, 22.46f, 21.56f, 14.7f, 11.67f, 8.333f, 5.089f, 2.356f,
                 1.32f, .8315f, .5705f, .4151f, .3119f, .2385f, .1955f,
                 .08373f, .03138f, .01351f, .005789f, .00309f, .002236f,
                 .001725f, 8.798f, 9.586f, 10.23f, 10.49f, 10.93f, 11.59f,
                 12.05f, 12.63f, 13.43f, 14.5f, 18.32f, 26.27f, 39.04f, 46.64f,
                 47.02f, 41.52f, 25.42f, 19.59f, 13.63f, 8.087f, 3.66f,
                 2.028f, 1.274f, .871f, .634f, .4757f, .3634f, .2971f, .1275f,
                 .04795f, .02072f, .008936f, .00478f, .00346f, .00267f, 15.75f,
                 17.5f, 19.14f, 19.91f, 21.08f, 22.76f, 23.99f, 25.61f,
                 27.85f, 30.97f, 42.04f, 63.34f, 89.71f, 98.53f, 96.09f,
                 77.18f, 42.9f, 32.2f, 21.88f, 12.71f, 5.641f, 3.11f, 1.947f,
                 1.327f, .9657f, .7242f, .5539f, .4528f, .1942f, .07335f,
                 .03181f, .0138f, .007394f, .005354f, .004132f, 34.f, 39.27f,
                 45.23f, 47.96f, 52.07f, 58.86f, 63.83f, 70.6f, 80.05f, 93.6f,
                 138.1f, 206.9f, 262.f, 253.4f, 236.6f, 167.3f, 82.85f, 60.59f,
                 40.13f, 22.8f, 9.939f, 5.439f, 3.4f, 2.315f, 1.685f, 1.263f,
                 .9664f, .7914f, .3397f, .1288f, .05611f, .0245f, .01316f,
                 .009536f, .00736f, 60.87f, 73.47f, 88.86f, 96.53f, 108.1f,
                 128.3f, 143.5f, 164.9f, 194.7f, 234.6f, 354.3f, 499.1f,
                 570.5f, 504.8f, 451.f, 290.f, 133.5f, 96.07f, 62.69f, 35.2f,
                 15.19f, 8.295f, 5.182f, 3.529f, 2.569f, 1.927f, 1.474f,
                 1.208f, .5191f, .1975f, .08627f, .03784f, .02037f, .01476f,
                 .01139f, 109.f, 139.6f, 181.1f, 202.9f, 239.6f, 303.9f,
                 353.6f, 418.9f, 508.1f, 621.7f, 903.8f, 1165.f, 1212.f,
                 973.1f, 833.f, 490.1f, 212.3f, 150.7f, 97.18f, 54.08f, 23.16f,
                 12.64f, 7.896f, 5.377f, 3.915f, 2.939f, 2.249f, 1.844f,
                 .794f, .3029f, .1327f, .05846f, .03151f, .02284f, .01763f,
                 195.f, 270.3f, 390.4f, 461.4f, 582.5f, 790.9f, 947.5f, 1142.f,
                 1380.f, 1656.f, 2237.f, 2610.f, 2500.f, 1820.f, 1491.f,
                 810.3f, 333.6f, 234.4f, 149.5f, 82.73f, 35.24f, 19.22f,
                 12.03f, 8.182f, 5.961f, 4.477f, 3.429f, 2.812f, 1.216f,
                 .4651f, .2043f, .09033f, .04874f, .03534f, .02728f, 274.2f,
                 401.2f, 635.3f, 782.9f, 1027.f, 1439.f, 1725.f, 2071.f,
                 2475.f, 2909.f, 3738.f, 4104.f, 3776.f, 2589.f, 2070.f,
                 1078.f, 432.6f, 302.3f, 191.8f, 105.9f, 44.99f, 24.54f,
                 15.39f, 10.45f, 7.615f, 5.722f, 4.384f, 3.596f, 1.561f,
                 .5978f, .263f, .1165f, .06292f, .04562f, .03522f};

    static struct
    {
        float e_1[200];
    } equiv_13 = {1.606f, 1.252f, 1.f, .816f, .68f, 1.603f, 1.246f, 1.f,
                  .817f, .684f, 1.444f, 1.207f, 1.f, .838f, .694f, 1.016f,
                  .985f, 1.f, 1.034f, 1.058f, .95f, .976f, 1.f, 1.034f, 1.068f,
                  .922f, .956f, 1.f, 1.044f, 1.09f, .932f, .966f, 1.f, 1.034f,
                  1.068f, .957f, .978f, 1.f, 1.022f, 1.044f, 1.606f, 1.252f,
                  1.f, .816f, .68f, 1.612f, 1.256f, 1.f, .817f, .684f, 1.193f,
                  1.101f, 1.f, .889f, .769f, .885f, .927f, 1.f, 1.086f, 1.175f,
                  .941f, .976f, 1.f, 1.024f, 1.047f, .932f, .966f, 1.f, 1.034f,
                  1.079f, .932f, .966f, 1.f, 1.034f, 1.068f, .957f, .978f, 1.f,
                  1.022f, 1.044f, 1.606f, 1.252f, 1.f, .816f, .68f, 1.621f,
                  1.256f, 1.f, .817f, .673f, .969f, .995f, 1.f, .982f, .94f,
                  .895f, .937f, 1.f, 1.075f, 1.143f, .95f, .976f, 1.f, 1.024f,
                  1.036f, .932f, .966f, 1.f, 1.034f, 1.079f, .932f, .966f, 1.f,
                  1.034f, 1.068f, .957f, .978f, 1.f, 1.022f, 1.044f, 1.606f,
                  1.252f, 1.f, .816f, .68f, 1.631f, 1.265f, 1.f, .807f, .662f,
                  .848f, .927f, 1.f, 1.044f, 1.079f, .922f, .956f, 1.f, 1.055f,
                  1.111f, .95f, .976f, 1.f, 1.013f, 1.036f, .932f, .966f, 1.f,
                  1.034f, 1.079f, .932f, .966f, 1.f, 1.034f, 1.068f, .957f,
                  .978f, 1.f, 1.022f, 1.044f, 1.606f, 1.252f, 1.f, .816f, .68f,
                  1.603f, 1.265f, 1.f, .807f, .662f, .82f, .918f, 1.f, 1.075f,
                  1.132f, .941f, .966f, 1.f, 1.034f, 1.079f, .96f, .976f, 1.f,
                  1.013f, 1.036f, .932f, .966f, 1.f, 1.034f, 1.079f, .932f,
                  .966f, 1.f, 1.034f, 1.068f, .957f, .978f, 1.f, 1.022f, 1.044f};

    /* System generated locals */
    long i__1;
    float ret_val;

    /* Builtin functions */
    double log(double), exp(double);

    /* Local variables */
    static long i__, j, k;
    static float x[4], y[4];
    static long ij, ji, kj;
    static float fac;
    extern double aitk_(float *, float *, float *, long *);
    static long kmin, jmax;
    static float attn[4];
    static long ilow, jlow;
    static float facit[5];
#define attab ((float *)&equiv_8)
    static float tfact[5], rates[4];
#define faceq1 ((float *)&equiv_13)
#define faceq2 ((float *)&equiv_13 + 40)
#define faceq3 ((float *)&equiv_13 + 80)
#define faceq4 ((float *)&equiv_13 + 120)
#define faceq5 ((float *)&equiv_13 + 160)
    static float wvlth;
#define attab1 ((float *)&equiv_8)
#define attab2 ((float *)&equiv_8 + 35)
#define attab3 ((float *)&equiv_8 + 70)
#define attab4 ((float *)&equiv_8 + 105)
#define attab5 ((float *)&equiv_8 + 140)
#define attab6 ((float *)&equiv_8 + 175)
#define attab7 ((float *)&equiv_8 + 210)
#define attab8 ((float *)&equiv_8 + 245)
#define attab9 ((float *)&equiv_8 + 280)
#define factor ((float *)&equiv_13)

    /*                                                                       GMR  110 */
    /*        COMPUTES ATTENUATION OF CONDENSED WATER IN FORM OF RAIN        GMR  120 */
    /*                                                                       GMR  130 */
    /*        FREQ = WAVENUMBER (CM-1)                                       GMR  140 */
    /*        T    = TEMPERATURE (DEGREES KELVIN)                            GMR  150 */
    /*        RATE = PRECIPITATION RATE (MM/HR)                              GMR  160 */
    /*       WVLTH = WAVELENGTH IN CM                                        GMR  170 */
    /*                                                                       GMR  180 */
    /*     TABLES ATTAB AND FACTOR CALCULATED FROM FULL MIE THEORY           GMR  190 */
    /*     UTILIZING MARSHALL-PALMER SIZE DISTRIBUTION WITH RAYS INDEX       GMR  200 */
    /*     OF REFRACTION                                                     GMR  210 */
    /*                                                                       GMR  220 */
    /*     ATTAB IS ATTENUATION DATA TABLE IN NEPERS FOR 20 DEG CELSIUS      GMR  230 */
    /*     WITH RADIATION FIELD REMOVED                                      GMR  240 */
    /*                                                                       GMR  250 */
    /*     WVNTBL IS WAVENUMBER TABLE FOR WAVENUMBERS USED IN TABLE ATTAB    GMR  260 */
    /*     TMPTAB IS INTERPOLATION DATA TABLE FOR TEMPERATURES IN DEG KELVIN GMR  270 */
    /*                                                                       GMR  280 */
    /*     TLMDA IS INTERPOLATION DATA TABLE FOR WAVELENGTH IN CM            GMR  290 */
    /*     TFREQ IS INTERPOLATION DATA TABLE FOR WAVENUMBER IN CM-1          GMR  300 */
    /*                                                                       GMR  310 */
    /*     RATTAB IS RAIN RATE TABLE IN MM/HR                                GMR  320 */
    /*                                                                       GMR  330 */
    /*     FACTOR IS TABLE OF TEMPERATURE CORRECTION FACTORS FOR             GMR  340 */
    /*     TABLE ATTAB FOR REPRESENTATIVE RAINS WITHOUT RADIATION FIELD      GMR  350 */
    /*                                                                       GMR  360 */
    /*                                                                       GMR  370 */
    /*     AITKEN INTERPOLATION SCHEME WRITTEN BY                            GMR  380 */
    /*           E.T. FLORANCE O.N.R. PASADENA CA.                           GMR  390 */
    /*                                                                       GMR  400 */
    /*                                                                       GMR  410 */
    /* CC   DIMENSION X(3),Y(3),ATTN(3),RATES(3)                              GMR  460 */
    /*         GIVE ZERO ATTN IF RATE FALLS BELOW LIMIT                      GMR 1620 */
    if (*rate > ratlim)
    {
        goto L12;
    }
    ret_val = 0.f;
    return ret_val;
L12:
    wvlth = 1.f / *freq;
    /* CC   JMAX=3                                                            GMR 1670 */
    jmax = 4;
    /* CC   IF(WVLTH.GT.WVLTAB(1)) GO TO      14                              GMR 1690 */
    /* CC   ILOW=0                                                            GMR 1700 */
    /* CC   JMAX=2                                                            GMR 1710 */
    /* CC   GO TO 18                                                          GMR 1720 */
    /* CC   THIS DO LOOP IS 2 LESS THAN NO. OF WVLTAB INPUT                   GMR 1730 */
    /* CC14 DO 15 I=2,25                                                      GMR 1740 */
    /* L14: */
    for (i__ = 3; i__ <= 33; ++i__)
    {
        /* CC   IF(WVLTH.LT.(.5*(WVLTAB(I)+WVLTAB(I+1)))) GO TO 16                GMR 1760 */
        if (*freq < wvntbl[i__ - 1])
        {
            goto L16;
        }
        /* L15: */
    }
    /* CC   SET ILOW EQUAL TO 1 LESS THAN DO MAX                              GMR 1790 */
    /* CC   ILOW=24                                                           GMR 1800 */
    i__ = 34;
/* CC   GO TO 18                                                          GMR 1820 */
/* CC16 ILOW = I-2                                                        GMR 1830 */
L16:
    ilow = i__ - 3;
    /* L18: */
    /* CC   DO 190 I=2,7                                                      GMR 1860 */
    for (k = 3; k <= 7; ++k)
    {
        /* CC   IF (RATE. LT.(.5*(RATTAB(I)+RATTAB(I+1))))GO TO 195               GMR 1880 */
        if (*rate < rattab[k - 1])
        {
            goto L195;
        }
        /* L190: */
    }
    /* CC   KMIN=6                                                            GMR 1910 */
    k = 8;
/* CC   GO TO 198                                                         GMR 1930 */
/* C195 KMIN=I-2                                                          GMR 1940 */
L195:
    kmin = k - 3;
    /* L198: */
    i__1 = jmax;
    for (j = 1; j <= i__1; ++j)
    {
        ij = ilow + j;
        x[j - 1] = wvntbl[ij - 1];
        /* L20: */
    }
    /*        INTERPOLATE                                                    GMR 2010 */
    /* CC   Z = -ALOG(FREQ)                                                   GMR 2020 */
    /* CC   DO 25 K=1,3                                                       GMR 2030 */
    for (k = 1; k <= 4; ++k)
    {
        kj = kmin + k;
        rates[k - 1] = rattab[kj - 1];
        i__1 = jmax;
        for (j = 1; j <= i__1; ++j)
        {
            ij = ilow + j;
            y[j - 1] = log(attab[ij + kj * 35 - 36]);
            /* L24: */
        }
        attn[k - 1] = exp(aitk_(x, y, freq, &jmax));
        /* L25: */
    }
    /*        APPLY TEMPERATURE CORRECTION                                   GMR 2130 */
    for (i__ = 2; i__ <= 5; ++i__)
    {
        if (*t < tmptab[i__ - 1])
        {
            goto L33;
        }
        /* L31: */
    }
    ilow = 4;
    goto L35;
L33:
    ilow = i__ - 1;
L35:
    for (j = 2; j <= 8; ++j)
    {
        if (*freq < tfreq[j - 1])
        {
            goto L43;
        }
        /* L41: */
    }
    /* CC   JLOW IS 2 LESS THAN DO MAX                                        GMR 2240 */
    jlow = 6;
    goto L45;
L43:
    jlow = j - 2;
L45:
    for (k = 1; k <= 2; ++k)
    {
        for (j = 1; j <= 2; ++j)
        {
            /*        INTERPOLATE IN TEMPERATURE                                     GMR 2310 */
            /* CC   KJ=(KMIN/2)+K                                                     GMR 2320 */
            kj = k + (kmin + 1) / 2;
            ji = jlow + j;
            fac = ((tmptab[ilow - 1] - *t) * factor[ilow + 1 + (ji + (kj << 3)) * 5 - 46] + (*t - tmptab[ilow]) * factor[ilow + (ji + (kj << 3)) * 5 - 46]) / (tmptab[ilow - 1] - tmptab[ilow]);
            ji = jlow + 3 - j;
            facit[j - 1] = (tfreq[ji - 1] - *freq) * fac;
            /* L49: */
        }
        tfact[k - 1] = (facit[1] - facit[0]) / (tfreq[jlow] - tfreq[jlow + 1]);
        /* L50: */
    }
    /*        COMPUTE ATTENUATION (DB/KM)                                    GMR 2420 */
    /* CC   KJ=2*KMIN/2+1                                                     GMR 2430 */
    kj = ((kmin + 1) / 2 << 1) + 1;
    /* CC   GMRAIN=AITK(RATES,ATTN,RATE,3)*                                   GMR 2450 */
    ret_val = aitk_(rates, attn, rate, &c__4) * ((*rate - rattab[kj - 1]) * tfact[1] + (rattab[kj + 1] - *rate) * tfact[0]) / (rattab[kj + 1] - rattab[kj - 1]);
    /* CC                                                                     GMR 2490 */
    /* CC    APPLY CONVERSION TO NEPERS                                       GMR 2500 */
    /* CC                                                                     GMR 2510 */
    return ret_val;
} /* gmrain_ */

#undef factor
#undef attab9
#undef attab8
#undef attab7
#undef attab6
#undef attab5
#undef attab4
#undef attab3
#undef attab2
#undef attab1
#undef faceq5
#undef faceq4
#undef faceq3
#undef faceq2
#undef faceq1
#undef attab