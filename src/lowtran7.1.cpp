/* lowtran7.1.f -- translated by f2c (version 20191129).

   No need to link with libf2c anymore!
   Copied all files locally so can work through and remove ones not needed!
*/

// clang++ -g lowtran7.1.cpp -I../includes/libf2c -L../includes/libf2c -lf2c -lm -v -o test && ./test
#include "lowtran7.1.h"

// added by GP

#define STRINGIZING(x) #x
#define STR(x) STRINGIZING(x)
#define FILE_LINE __FILE__ ":" STR(__LINE__)

#ifdef PRINT_READS
#define PRINT_LINE_READ()               \
	printf("\nLINE with READ, CHECK:"); \
	printf(FILE_LINE);                  \
	printf("\n");
#else
#define PRINT_LINE_READ()
#endif

#define debug 1
// #define DO_FIO_IN 1
// end added by GP

/* Common Block Declarations */

struct LOWTRAN_ResultBuffer
{
	float *data;
	long length;
};

union
{
	struct
	{
		float relhum[34], hstor[34];
		long ich[4];
		float vh[17], tx[63], w[63], wpath[4284] /* was [68][63] */, tbby[68],
			absc[235] /* was [5][47] */, extc[235] /* was [5][47]
													*/
			,
			asym[235] /* was [5][47] */, vx2[47], awccon[5];
	} _1;
	struct
	{
		float relhum[34], whno3[34];
		long ich[4];
		float vh[17], tx[63], w[63], wpath[4284] /* was [68][63] */, tbby[68],
			absc[235] /* was [5][47] */, extc[235] /* was [5][47]
													*/
			,
			asym[235] /* was [5][47] */, vx2[47], awccon[5];
	} _2;
	struct
	{
		float relhum[34], hstor[34];
		long ich[4];
		float vh[17], tx[63], w[63], wpath[4284] /* was [68][63] */, tbby[68];
	} _3;
	struct
	{
		float relhum[34], hstor[34];
		long ich[4];
		float vh[17], tx[63], w[63], wpath[4284] /* was [68][63] */, tbby[68],
			absc[235] /* was [5][47] */, extc[235] /* was [5][47]
													*/
			,
			asyc[235] /* was [5][47] */, vx2[47], awccon[5];
	} _4;
	struct
	{
		float relhum[34], hstor[34];
		long ich[4];
		float vh[17], tx[63], w[63], wpath[4284] /* was [68][63] */, tbby[68],
			absc[235] /* was [5][47] */, extc[235] /* was [5][47]
													*/
			,
			asym[235] /* was [5][47] */, vx0[47], awccon[5];
	} _5;
} _BLNK__;

#define _BLNK__1 (_BLNK__._1)
#define _BLNK__2 (_BLNK__._2)
#define _BLNK__3 (_BLNK__._3)
#define _BLNK__4 (_BLNK__._4)
#define _BLNK__5 (_BLNK__._5)

struct
{
	long ird, ipr, ipu, npr, ipr1;
} ifil_;

#define ifil_1 (ifil_)

struct LOWTRAN_Card1
{
	//
	// m4, m5, m6, mdef not inclduded as on the 1a card below
	// this card is not listed on the documentation
	// however seems to be an additional card for card 1
	//
	/**
	 * @brief MODEL selects one of the six geographical-seasonal model
	 * atmospheres or specifies that user defined meteorological data
	 * are to be used.<br>
	 * MODEL = 0 if meterological data are specified (horizontal path only)
	 * 		 = 1 Tropical Atmopshere
	 * 		 = 2 Midlatitude Summer
	 * 		 = 3 Midlatitude Winter
	 * 		 = 4 Subartic Summer
	 *  	 = 5 Subartic Winter
	 * 		 = 6 1976 US Standard
	 * 		 = 7 If a new model atmopshere (e.g. radiosonde data) is to be read in
	 *
	 */
	long model;

	/**
	 * @brief ITYPE indicates the type of atmospheric path
	 * ITYPE = 1 For a horizontal (constant-pressure) path
	 * 		 = 2 Vertical or slant path between two altitudes
	 * 		 = 3 For a vertical or slant path to space.
	 *
	 */
	long itype;

	/**
	 * @brief IEMSCT Determines the mode of execution of the program
	 * IEMSCT = 0 Program execution in transmittance mode
	 * 		  = 1 Program execution in thermal radiance mode
	 * 		  = 2 Program execution in radiance mode with solar/lunar single scattered radiance included
	 * 		  = 3 Program calculates directly transmitted solar irradiance
	 */
	long iemsct;
	/**
	 * @brief IMULT Determines the execution with multiple scattering
	 * IMULT = 0 Program executed without multiple scattering
	 * 		 = 1 Program executed with multiple scattering
	 *
	 */
	long imult;
	long m1, m2, m3, /* m4, m5, m6, mdef,*/ im, noprt;
	float tbound, salb;
} card1_;

#define card1_1 (card1_)

struct LOWTRAN_Card1a
{
	long m4, m5, m6, mdef, ird1, ird2;
} card1a_;

#define card1a_1 card1a_

struct LOWTRAN_Card2
{
	long ihaze, iseasn, ivulcn, icstl, icld, ivsa;
	float vis, wss, whh, rainrt, gndalt;
} card2_;

#define card2_1 (card2_)

/**
 * @brief Optional card
 * only needed if CLD=18, 19, 20 See Page 19
 */
struct LOWTRAN_Card2a
{
	float cthik, calt, cext;
	long iseed;
} card2a_;

#define card2a_1 card2a_

/**
 * @brief Optional card
 * only needed if Card2.IVSA=1
 *
 */
struct LOWTRAN_Card2b
{
	float zcvsa, ztvsa, zinvsa;
} card2b_;

#define card2b_1 card2b_

/**
 * @brief Optional card
 * only needed if Card1.MODEL=0 or 7 and Card1.IM=1
 */
struct LOWTRAN_Card2c
{
	long ml /*,  ird1, ird2 included in non-standard card1a  */;
	/**
	 * @deprecated
	 */
	std::string title;
} card2c_;

#define card2c_1 card2c_

// @todo card 2c1 -> 2c3

struct LOWTRAN_Card2d
{
	long ireg[4];
	float altb[4]; // not in the original definition?
	long iregc[4]; // not in the original definition?
} card2d_;

#define card2d_1 card2d_

/** @todo Can be different card 3 if imesct = 3 perhaps need union or alternative def? */
struct LOWTRAN_Card3
{
	float h1, h2, angle, range, beta, re;
	long len;
} card3_;

#define card3_1 (card3_)

/**
 * @brief
 *
 */
struct LOWTRAN_Card3a1
{
	long iparm, iph, iday, isourc;
} card3a1_;

#define card3a1_1 card3a1_1;

/**
 * @brief Optional card if IEMSCT = 2
 *
 */
struct LOWTRAN_Card3a2
{
	float parm1, parm2, parm3, parm4, time, psio, anglem, g;
} card3a2_;

#define card3a2_1 card3a2_1;

// @todo card 3a1 -> 3b2 proeprly

struct LOWTRAN_Card4
{
	float v1, v2, dv;
} card4_;

#define card4_1 card4_

struct LOWTRAN_Card5
{
	long irpt;
} card5_;
#define card5_1 card5_;

struct
{
	float pi, ca, deg, gcair, bignum, bigexp;
} cnstns_;

#define cnstns_1 cnstns_

struct
{
	long kmax, m, ikmax, nl, ml, iklo, issgeo, imult;
} cntrl_;

#define cntrl_1 (cntrl_)

union
{
	struct
	{
		float zm[34], pm[34], tm[34], rfndx[34], densty[2142] /* was [63][
		34] */
			,
			cldamt[34], rramt[34], eqlwc[34], hazec[34];
	} _1;
	struct
	{
		float zmdl[34], pm[34], tm[34], rfndx[34], densty[2142] /* was [63][
		34] */
			,
			cldamt[34], rramt[34], eqlwc[34], hazec[34];
	} _2;
	struct
	{
		float z__[34], pm[34], tm[34], rfndx[34], densty[2142] /* was [63][
		34] */
			,
			cldamt[34], rramt[34], eqlwc[34], hazec[34];
	} _3;
	struct
	{
		float z__[34], p[34], t[34], rfndx[34], densty[2142] /* was [63][
		34] */
			,
			cldamt[34], rramt[34], eqlwc[34], hazec[34];
	} _4;
	struct
	{
		float zm[34], pm[34], tm[34], dum[34], densty[2142] /* was [63][
		34] */
			,
			cldamt[34], rramt[34], eqlwc[34], hazec[34];
	} _5;
} model_;

#define model_1 (model_._1)
#define model_2 (model_._2)
#define model_3 (model_._3)
#define model_4 (model_._4)
#define model_5 (model_._5)

struct
{
	float ah1[68], arh[68], wpaths[4284] /* was [68][63] */, pa[68], pr[68],
		atheta[35], adbeta[35];
	long lj[69], jturn;
	float angsun, cszen[68];
} sols_;

#define sols_1 sols_

struct
{
	float rhh;
} mart_;

#define mart_1 mart_

struct
{
	long nangls;
	float angf[50], f[200] /* was [4][50] */;
} usrdta_;

#define usrdta_1 usrdta_

struct
{
	float hmdlz[8];
} mdlz_;

#define mdlz_1 mdlz_

struct
{
	float zvsa[10], rhvsa[10], ahvsa[10];
	long ihvsa[10];
} zvsaly_;

#define zvsaly_1 zvsaly_

struct titl_1_
{
	char hhaze[320] /* was [5][16] */, hseasn[40] /* was [5][2] */,
		hvulcn[160] /* was [5][8] */, blank[4], hmet[40] /* was [5][2]
														  */
		,
		hmodel[160] /* was [5][8] */, htrrad[96] /* was [6][4]
												  */
		;
};
struct titl_2_
{
	char hz[320] /* was [5][16] */, seasn[40] /* was [5][2] */,
		vulcn[160] /* was [5][8] */, blank[4], hmet[40] /* was [5][2]
														 */
		,
		hmodel[160] /* was [5][8] */, htrrad[96] /* was [6][4]
												  */
		;
};

#define titl_1 (*(struct titl_1_ *)&titl_)
#define titl_2 (*(struct titl_2_ *)&titl_)

struct vsbd_1_
{
	float vsb[10];
};

#define vsbd_1 (*(struct vsbd_1_ *)&vsbd_)

struct
{
	float tbbss[68], tbbms[34], wpms[2142] /* was [34][63] */;
	long imsmx;
	float wpmss[2142] /* was [34][63] */;
} mnlt_;

#define mnlt_1 mnlt_

struct
{

	float pl[68], qtheta[68];
	long itest;
	float hi, hf, aht[68];

} path_;

#define path_1 (path_)

union
{
	struct
	{
		float tae7, tae12, tae13, tae14, tae16;
	} _1;
	struct
	{
		float taer[5];
	} _2;
} aertm_;

#define aertm_1 (aertm_._1)
#define aertm_2 (aertm_._2)

struct LOWTRAN_Card1b
{
	long junit[15];
	float wmol[12], wair1;
	long jlow;
};

union
{
	LOWTRAN_Card1b _1;
	struct
	{
		long junitp, junitt, junit1[13];
		float wmol1[12], wair1;
		long jlow;
	} _2;
	struct
	{
		long junitp, junitt, junit1[13];
		float wmol1[12], wair;
		long jlow;
	} _3;
	struct
	{
		long junit[15];
		float wmoli[12], wair1;
		long jlow;
	} _4;
	struct
	{
		long junitp, junitt, junit[13];
		float wmol[12], wair;
		long jlow;
	} _5;
} card1b_;

#define card1b_1 (card1b_._1)
#define card1b_2 (card1b_._2)
#define card1b_3 (card1b_._3)
#define card1b_4 (card1b_._4)
#define card1b_5 (card1b_._5)

struct mdata_1_
{
	float z__[50], p[50], t[50], wh[50], wco2[50], wo[50], wn2o[50], wco[50],
		wch4[50], wo2[50], cld[350] /* was [50][7] */, rr[350] /*
		was [50][7] */
		;
};
struct mdata_2_
{
	float zz[50], p[50], t[50], wh[50], wco2[50], wo[50], wn2o[50], wco[50],
		wch4[50], wo2[50], cld[350] /* was [50][7] */, rr[350] /*
		was [50][7] */
		;
};
struct mdata_3_
{
	float z__[50], p[50], t[50], wh[50], wco2[50], wo[50], wn2o[50], wco[50],
		wch4[50], wo2[50], cld1[50], cld2[50], cld3[50], cld4[50], cld5[50], cld6[50], cld7[50], rr1[50], rr2[50], rr3[50], rr4[50], rr5[50], rr6[50], rr7[50];
};

#define mdata_1 (*(struct mdata_1_ *)&mdata_)
#define mdata_2 (*(struct mdata_2_ *)&mdata_)
#define mdata_3 (*(struct mdata_3_ *)&mdata_)

struct
{
	float wno[50], wso2[50], wno2[50], wnh3[50], wair[50];
} mdata1_;

#define mdata1_1 mdata1_

struct trac_1_
{
	float ano[50], aso2[50], ano2[50], anh3[50], ano3[50], oh[50], hf[50], hcl[50], hbr[50], hi[50], clo[50], ocs[50], h2co[50], hocl[50], an2[50], hcn[50], ch3cl[50], h2o2[50], c2h2[50], c2h6[50], ph3[50];
};
struct trac_2_
{
	float trac[1050] /* was [50][21] */;
};
struct trac_3_
{
	float ano[50], so2[50], ano2[50], anh3[50], hno3[50], oh[50], hf[50], hcl[50], hbr[50], hi[50], clo[50], ocs[50], h2co[50], hocl[50], an2[50], hcn[50], ch3cl[50], h2o2[50], c2h2[50], c2h6[50], ph3[50];
};

#define trac_1 (*(struct trac_1_ *)&trac_)
#define trac_2 (*(struct trac_2_ *)&trac_)
#define trac_3 (*(struct trac_3_ *)&trac_)

struct desaer_1_
{
	float ext[188] /* was [47][4] */, abs__[188] /* was [47][4] */, g[188] /* was [47][4] */;
};
struct desaer_2_
{
	float desex1[47], desex2[47], desex3[47], desex4[47], desab1[47], desab2[47], desab3[47], desab4[47], desg1[47], desg2[47], desg3[47],
		desg4[47];
};

#define desaer_1 (*(struct desaer_1_ *)&desaer_)
#define desaer_2 (*(struct desaer_2_ *)&desaer_)

struct constn_1_
{
	float pzero, tzero, avogad, alosmt, gascon, plank, boltz, clight, adcon,
		alzero, avmwt, airmwt, amwt[35];
};

#define constn_1 (*(struct constn_1_ *)&constn_)

union
{
	struct
	{
		float zmdl[40], pm[40], tm[40], wmdl[520] /* was [40][13] */;
	} _1;
	struct
	{
		float zmdl[40], p[40], t[40], wmdl[520] /* was [40][13] */;
	} _2;
} nsinp_;

#define nsinp_1 (nsinp_._1)
#define nsinp_2 (nsinp_._2)

struct mlatm_1_
{
	float alt[50], pmatm[300] /* was [50][6] */, tmatm[300] /* was [50][6]
															 */
		,
		amol[2400] /* was [50][8][6] */;
};
struct mlatm_2_
{
	float alt[50], p1[50], p2[50], p3[50], p4[50], p5[50], p6[50], t1[50], t2[50], t3[50], t4[50], t5[50], t6[50], amol11[50], amol12[50],
		amol13[50], amol14[50], amol15[50], amol16[50], amol17[50],
		amol18[50], amol21[50], amol22[50], amol23[50], amol24[50],
		amol25[50], amol26[50], amol27[50], amol28[50], amol31[50],
		amol32[50], amol33[50], amol34[50], amol35[50], amol36[50],
		amol37[50], amol38[50], amol41[50], amol42[50], amol43[50],
		amol44[50], amol45[50], amol46[50], amol47[50], amol48[50],
		amol51[50], amol52[50], amol53[50], amol54[50], amol55[50],
		amol56[50], amol57[50], amol58[50], amol61[50], amol62[50],
		amol63[50], amol64[50], amol65[50], amol66[50], amol67[50],
		amol68[50];
};

#define mlatm_1 (*(struct mlatm_1_ *)&mlatm_)
#define mlatm_2 (*(struct mlatm_2_ *)&mlatm_)

struct prfd_1_
{
	float zht[34], hz2k[170] /* was [34][5] */, fawi50[34], fawi23[34],
		spsu50[34], spsu23[34], bastfw[34], vumofw[34], hivufw[34],
		exvufw[34], bastss[34], vumoss[34], hivuss[34], exvuss[34],
		upnatm[34], vutono[34], vutoex[34], exupat[34];
};

#define prfd_1 (*(struct prfd_1_ *)&prfd_)

struct
{
	float re, deltas, zmax;
	long imax, imod, ibmax, ipath;
} parmtr_;

#define parmtr_1 parmtr_

struct
{
	float zp[35], pp[35], tp[35], rfndxp[35], sp[35], ppsum[35], tpsum[35],
		rhopsm[35], denp[2205] /* was [63][35] */, amtp[2205] /*
		was [63][35] */
		;
} rfrpth_;

#define rfrpth_1 rfrpth_

struct
{
	float rnpath[68], rramtk[68];
} rain_;

#define rain_1 rain_

union
{
	struct
	{
		float xx1, xx2, xx3, xx4, xx5, yy1, yy2, yy3, yy4, yy5, zz1, zz2, zz3,
			zz4, zz5;
	} _1;
	struct
	{
		float extv[5], absv[5], asyv[5];
	} _2;
} aer_;

#define aer_1 (aer_._1)
#define aer_2 (aer_._2)

struct
{
	float teb1, teb2, tasp1, tasp2, tmsp1, tmsp2, teb2sv;
} srad_;

#define srad_1 srad_

struct
{
	float abb[19], btop[50], bmid[34], tmd[34], tmols[34], taers[34], tcont[34], dcont[34];
} tran_;

#define tran_1 tran_

struct
{
	float tle[34], cosbar[34], omega0[34], upf[340] /* was [10][34] */,
		dnf[340] /* was [10][34] */, taer[50], dtx7[34], daers[34], asyik[34], asydm[34], strn[35], dmols[34], dstrn[35],
		fdnsrf, fdnsrt;
	long ikdm;
	float fdntrf, fdntrt;
} msrd_;

#define msrd_1 (msrd_)

struct
{
	long icall;
	float fphs, falb, forbit;
} icll_;

#define icll_1 icll_

struct h2o_1_
{
	float cph2o[3515];
};
struct h2o_2_
{
	float c11h2o[70], c21h2o[126], c22h2o[5], c31h2o[126], c32h2o[2], c41h2o[126], c42h2o[52], c51h2o[126], c52h2o[52], c61h2o[126], c62h2o[52], c71h2o[126], c72h2o[126], c73h2o[116], c81h2o[126], c82h2o[126],
		c83h2o[118], c91h2o[126], c92h2o[126], c93h2o[71], ca1h2o[126],
		ca2h2o[126], ca3h2o[126], ca4h2o[7], cb1h2o[126], cb2h2o[126],
		cb3h2o[54], cc1h2o[126], cc2h2o[126], cc3h2o[106], cd1h2o[126],
		cd2h2o[111], ce1h2o[126], ce2h2o[126], ce3h2o[53];
};

#define h2o_1 (*(struct h2o_1_ *)&h2o_)
#define h2o_2 (*(struct h2o_2_ *)&h2o_)

struct o3_1_
{
	float cpo3[447];
};
struct o3_2_
{
	float c11o3[41], c21o3[126], c22o3[27], c31o3[126], c32o3[8], c41o3[36],
		c51o3[83];
};

#define o3_1 (*(struct o3_1_ *)&o3_)
#define o3_2 (*(struct o3_2_ *)&o3_)

struct ufmix1_1_
{
	float cpco2[1219];
};
struct ufmix1_2_
{
	float c11co2[83], c21co2[121], c31co2[126], c32co2[85], c41co2[126],
		c42co2[12], c51co2[62], c61co2[126], c62co2[45], c71co2[126],
		c72co2[99], c81co2[126], c82co2[82];
};

#define ufmix1_1 (*(struct ufmix1_1_ *)&ufmix1_)
#define ufmix1_2 (*(struct ufmix1_2_ *)&ufmix1_)

struct ufmix2_1_
{
	float cpco[173], cpch4[493], cpn2o[704], cpo2[382];
};
struct ufmix2_2_
{
	float c11co[36], c21co[126], c22co[11], c11ch4[126], c12ch4[126], c13ch4[126], c14ch4[115], c11n2o[25], c21n2o[126], c22n2o[126], c23n2o[112], c31n2o[126], c32n2o[126], c33n2o[63], c11o2[54], c21o2[126],
		c22o2[126], c23o2[76];
};

#define ufmix2_1 (*(struct ufmix2_1_ *)&ufmix2_)
#define ufmix2_2 (*(struct ufmix2_2_ *)&ufmix2_)

struct traceg_1_
{
	float cpnh3[431], cpno[62], cpno2[142], cpso2[226];
};
struct traceg_2_
{
	float c11nh3[78], c21nh3[126], c22nh3[126], c23nh3[101], c11no[62], c11no2[126], c12no2[16], c11so2[38], c21so2[126], c22so2[62];
};

#define traceg_1 (*(struct traceg_1_ *)&traceg_)
#define traceg_2 (*(struct traceg_2_ *)&traceg_)

struct wnlohi_1_
{
	long iwlh2o[15], iwlo3[6], iwlco2[11], iwlco[4], iwlch4[5], iwln2o[12],
		iwlo2[7], iwlnh3[3], iwlno[2], iwlno2[4], iwlso2[5], iwhh2o[15],
		iwho3[6], iwhco2[11], iwhco[4], iwhch4[5], iwhn2o[12], iwho2[7],
		iwhnh3[3], iwhno[2], iwhno2[4], iwhso2[5];
};

#define wnlohi_1 (*(struct wnlohi_1_ *)&wnlohi_)

union
{
	struct
	{
		float a1[11], b1[11], c1[11];
		long ibnd[11];
		float a[11], cps[11];
	} _1;
	struct
	{
		float aa[11], bb[11], cc[11];
		long ibnd[11];
		float a[11], cps[11];
	} _2;
} aabbcc_;

#define aabbcc_1 (aabbcc_._1)
#define aabbcc_2 (aabbcc_._2)

struct
{
	float sun, umb[34], dmb[34], umbs[34], dmbs[34];
} dirst_;

#define dirst_1 dirst_

struct abc_1_
{
	float factor[3], anh3[2], aco2[10], aco[3], ach4[4], ano2[3], an2o[11],
		ao2[6], ao3[5], aso2[4], ah2o[14], ano, aanh3[2], bbnh3[2], ccnh3[2], aaco2[10], bbco2[10], ccco2[10], aaco[3], bbco[3], ccco[3],
		aach4[4], bbch4[4], ccch4[4], aano2[3], bbno2[3], ccno2[3], aan2o[11], bbn2o[11], ccn2o[11], aao2[6], bbo2[6], cco2[6], aao3[5],
		bbo3[5], cco3[5], aaso2[4], bbso2[4], ccso2[4], aah2o[14], bbh2o[14], cch2o[14], aano, bbno, ccno;
};

#define abc_1 (*(struct abc_1_ *)&abc_)

struct c4c8_1_
{
	float c4[133], c8[102];
};
struct c4c8_2_
{
	float c401[114], c4115[19], c8[102];
};

#define c4c8_1 (*(struct c4c8_1_ *)&c4c8_)
#define c4c8_2 (*(struct c4c8_2_ *)&c4c8_)

struct sh2o_1_
{
	float v1, v2, dv;
	long npt;
	float s296[2003];
};
struct sh2o_2_
{
	float v1, v2, dv;
	long npt;
	float s0000[2], s0001[50], s0051[50], s0101[50], s0151[50], s0201[50],
		s0251[50], s0301[50], s0351[50], s0401[50], s0451[50], s0501[50],
		s0551[50], s0601[50], s0651[50], s0701[50], s0751[50], s0801[50],
		s0851[50], s0901[50], s0951[50], s1001[50], s1051[50], s1101[50],
		s1151[50], s1201[50], s1251[50], s1301[50], s1351[50], s1401[50],
		s1451[50], s1501[50], s1551[50], s1601[50], s1651[50], s1701[50],
		s1751[50], s1801[50], s1851[50], s1901[50], s1951[50], s2001[1];
};

#define sh2o_1 (*(struct sh2o_1_ *)&sh2o_)
#define sh2o_2 (*(struct sh2o_2_ *)&sh2o_)

struct s260_1_
{
	float v1, v2, dv;
	long npt;
	float s260[2003];
};
struct s260_2_
{
	float v1, v2, dv;
	long npt;
	float s0000[2], s0001[50], s0051[50], s0101[50], s0151[50], s0201[50],
		s0251[50], s0301[50], s0351[50], s0401[50], s0451[50], s0501[50],
		s0551[50], s0601[50], s0651[50], s0701[50], s0751[50], s0801[50],
		s0851[50], s0901[50], s0951[50], s1001[50], s1051[50], s1101[50],
		s1151[50], s1201[50], s1251[50], s1301[50], s1351[50], s1401[50],
		s1451[50], s1501[50], s1551[50], s1601[50], s1651[50], s1701[50],
		s1751[50], s1801[50], s1851[50], s1901[50], s1951[50], s2001[1];
};

#define s260_1 (*(struct s260_1_ *)&s260_)
#define s260_2 (*(struct s260_2_ *)&s260_)

struct fh2o_1_
{
	float v1, v2, dv;
	long npt;
	float f296[2003];
};
struct fh2o_2_
{
	float v1, v2, dv;
	long npt;
	float f0000[2], f0001[50], f0051[50], f0101[50], f0151[50], f0201[50],
		f0251[50], f0301[50], f0351[50], f0401[50], f0451[50], f0501[50],
		f0551[50], f0601[50], f0651[50], f0701[50], f0751[50], f0801[50],
		f0851[50], f0901[50], f0951[50], f1001[50], f1051[50], f1101[50],
		f1151[50], f1201[50], f1251[50], f1301[50], f1351[50], f1401[50],
		f1451[50], f1501[50], f1551[50], f1601[50], f1651[50], f1701[50],
		f1751[50], f1801[50], f1851[50], f1901[50], f1951[50], f2001[1];
};

#define fh2o_1 (*(struct fh2o_1_ *)&fh2o_)
#define fh2o_2 (*(struct fh2o_2_ *)&fh2o_)

struct o3hh0_1_
{
	float v1s, v2s, dvs;
	long npts;
	float s[2687];
};
struct o3hh0_2_
{
	float v1c, v2c, dvc;
	long nc;
	float o30001[80], o30081[80], o30161[80], o30241[80], o30321[80], o30401[7], c00001[80], c00081[80], c00161[80], c00241[80], c00321[80],
		c00401[80], c00481[80], c00561[80], c00641[80], c00721[80],
		c00801[80], c00881[80], c00961[80], c01041[80], c01121[80],
		c01201[80], c01281[80], c01361[80], c01441[80], c01521[80],
		c01601[80], c01681[80], c01761[80], c01841[80], c01921[80],
		c02001[80], c02081[80], c02161[80], c02241[40];
};

#define o3hh0_1 (*(struct o3hh0_1_ *)&o3hh0_)
#define o3hh0_2 (*(struct o3hh0_2_ *)&o3hh0_)

struct o3hh1_1_
{
	float v1s, v2s, dvs;
	long npts;
	float s[2690];
};
struct o3hh1_2_
{
	float v1c, v2c, dvc;
	long nc;
	float o31001[88], c10086[80], c10166[80], c10246[65], c10311[16], c10327[80], c10407[1], c10001[80], c10081[80], c10161[80], c10241[80],
		c10321[80], c10401[80], c10481[80], c10561[80], c10641[80],
		c10721[80], c10801[80], c10881[80], c10961[80], c11041[80],
		c11121[80], c11201[80], c11281[80], c11361[80], c11441[80],
		c11521[80], c11601[80], c11681[80], c11761[80], c11841[80],
		c11921[80], c12001[80], c12081[80], c12161[80], c12241[40];
};

#define o3hh1_1 (*(struct o3hh1_1_ *)&o3hh1_)
#define o3hh1_2 (*(struct o3hh1_2_ *)&o3hh1_)

struct o3hh2_1_
{
	float v1s, v2s, dvs;
	long npts;
	float s[2690];
};
struct o3hh2_2_
{
	float v1c, v2c, dvc;
	long nc;
	float o32001[88], c20086[80], c20166[80], c20246[65], c20311[16], c20327[80], c20407[1], c20001[80], c20081[80], c20161[80], c20241[80],
		c20321[80], c20401[80], c20481[80], c20561[80], c20641[80],
		c20721[80], c20801[80], c20881[80], c20961[80], c21041[80],
		c21121[80], c21201[80], c21281[80], c21361[80], c21441[80],
		c21521[80], c21601[80], c21681[80], c21761[80], c21841[80],
		c21921[80], c22001[80], c22081[80], c22161[80], c22241[40];
};

#define o3hh2_1 (*(struct o3hh2_1_ *)&o3hh2_)
#define o3hh2_2 (*(struct o3hh2_2_ *)&o3hh2_)

struct o3uvf_1_
{
	float v1, v2, dv;
	long npt;
	float s[133];
};
struct o3uvf_2_
{
	float v1o1, v2o1, dvo1;
	long npt1;
	float c02281[80], c02361[53];
};

#define o3uvf_1 (*(struct o3uvf_1_ *)&o3uvf_)
#define o3uvf_2 (*(struct o3uvf_2_ *)&o3uvf_)

struct o2c_1_
{
	float o2dray[74], o2c001[74], o2s0[74], o2a[74], o2b[74], v1o2, v2o2, dvo2;
	long npto2;
};

#define o2c_1 (*(struct o2c_1_ *)&o2c_)

struct extd_1_
{
	float vx2[47], rurext[188] /* was [47][4] */, rurabs[188] /* was [47][4]
															   */
		,
		rursym[188] /* was [47][4] */, urbext[188] /* was [47][4]
													*/
		,
		urbabs[188] /* was [47][4] */, urbsym[188] /* was [47][4]
													*/
		,
		ocnext[188] /* was [47][4] */, ocnabs[188] /* was [47][4]
													*/
		,
		ocnsym[188] /* was [47][4] */, troext[188] /* was [47][4]
													*/
		,
		troabs[188] /* was [47][4] */, trosym[188] /* was [47][4]
													*/
		,
		fg1ext[47], fg1abs[47], fg1sym[47], fg2ext[47], fg2abs[47],
		fg2sym[47], bstext[47], bstabs[47], bstsym[47], avoext[47],
		avoabs[47], avosym[47], fvoext[47], fvoabs[47], fvosym[47],
		dmeext[47], dmeabs[47], dmesym[47], ccuext[47], ccuabs[47],
		ccusym[47], calext[47], calabs[47], calsym[47], cstext[47],
		cstabs[47], cstsym[47], cscext[47], cscabs[47], cscsym[47],
		cniext[47], cniabs[47], cnisym[47];
};
struct extd_2_
{
	float vx2[47], rure1[47], rure2[47], rure3[47], rure4[47], rura1[47],
		rura2[47], rura3[47], rura4[47], rurg1[47], rurg2[47], rurg3[47],
		rurg4[47], urbe1[47], urbe2[47], urbe3[47], urbe4[47], urba1[47],
		urba2[47], urba3[47], urba4[47], urbg1[47], urbg2[47], urbg3[47],
		urbg4[47], ocne1[47], ocne2[47], ocne3[47], ocne4[47], ocna1[47],
		ocna2[47], ocna3[47], ocna4[47], ocng1[47], ocng2[47], ocng3[47],
		ocng4[47], troe1[47], troe2[47], troe3[47], troe4[47], troa1[47],
		troa2[47], troa3[47], troa4[47], trog1[47], trog2[47], trog3[47],
		trog4[47], fg1ext[47], fg1abs[47], fg1sym[47], fg2ext[47], fg2abs[47], fg2sym[47], bstext[47], bstabs[47], bstsym[47], avoext[47],
		avoabs[47], avosym[47], fvoext[47], fvoabs[47], fvosym[47],
		dmeext[47], dmeabs[47], dmesym[47], ccuext[47], ccuabs[47],
		ccusym[47], calext[47], calabs[47], calsym[47], cstext[47],
		cstabs[47], cstsym[47], cscext[47], cscabs[47], cscsym[47],
		cniext[47], cniabs[47], cnisym[47];
};

#define extd_1 (*(struct extd_1_ *)&extd_)
#define extd_2 (*(struct extd_2_ *)&extd_)

struct cirr_1_
{
	float ci32xt[47], ci32ab[47], ci32g[47], cir2xt[47], cir2ab[47], cir2g[47];
};
struct cirr_2_
{
	float ci64xt[47], ci64ab[47], ci64g[47], cir4xt[47], cir4ab[47], cir4g[47];
};

#define cirr_1 (*(struct cirr_1_ *)&cirr_)
#define cirr_2 (*(struct cirr_2_ *)&cirr_)

struct a_1_
{
	float t1qext[160] /* was [40][4] */, t2qext[160] /* was [40][4] */,
		t3qext[160] /* was [40][4] */, t1qabs[160] /* was [40][4] */,
		t2qabs[160] /* was [40][4] */, t3qabs[160] /* was [40][4] */,
		alam[40], arel[4];
};

#define a_1 (*(struct a_1_ *)&a_)

struct
{
	float pmol1, pmol2, paer1, paer2;
} srads_;

#define srads_1 srads_

struct sundat_1_
{
	float solara[1440], solarb[2910];
};
struct sundat_2_
{
	float suna01[41], suna02[144], suna03[144], suna04[144], suna05[144],
		suna06[144], suna07[144], suna08[144], suna09[144], suna10[144],
		suna11[103], sunb01[144], sunb02[144], sunb03[144], sunb04[144],
		sunb05[144], sunb06[144], sunb07[144], sunb08[144], sunb09[144],
		sunb10[144], sunb11[144], sunb12[144], sunb13[144], sunb14[144],
		sunb15[144], sunb16[144], sunb17[144], sunb18[144], sunb19[144],
		sunb20[144], sunb21[30];
};

#define sundat_1 (*(struct sundat_1_ *)&sundat_)
#define sundat_2 (*(struct sundat_2_ *)&sundat_)

struct mnmphs_1_
{
	long mnum[702] /* was [27][26] */;
	float phsfnc[2380] /* was [34][70] */;
};
struct mnmphs_2_
{
	long mum1[27], mum2[27], mum3[27], mum4[27], mum5[27], mum6[27], mum7[27], mum8[27], mum9[27], mum10[27], mum11[27], mum12[27], mum13[27], mum14[27], mum15[27], mum16[27], mum17[27], mum18[27], mum19[27], mum20[27], mum21[27], mum22[27], mum23[27], mum24[27], mum25[27], mum26[27];
	float phsf1[34], phsf2[34], phsf3[34], phsf4[34], phsf5[34], phsf6[34],
		phsf7[34], phsf8[34], phsf9[34], phsf10[34], phsf11[34], phsf12[34], phsf13[34], phsf14[34], phsf15[34], phsf16[34], phsf17[34],
		phsf18[34], phsf19[34], phsf20[34], phsf21[34], phsf22[34],
		phsf23[34], phsf24[34], phsf25[34], phsf26[34], phsf27[34],
		phsf28[34], phsf29[34], phsf30[34], phsf31[34], phsf32[34],
		phsf33[34], phsf34[34], phsf35[34], phsf36[34], phsf37[34],
		phsf38[34], phsf39[34], phsf40[34], phsf41[34], phsf42[34],
		phsf43[34], phsf44[34], phsf45[34], phsf46[34], phsf47[34],
		phsf48[34], phsf49[34], phsf50[34], phsf51[34], phsf52[34],
		phsf53[34], phsf54[34], phsf55[34], phsf56[34], phsf57[34],
		phsf58[34], phsf59[34], phsf60[34], phsf61[34], phsf62[34],
		phsf63[34], phsf64[34], phsf65[34], phsf66[34], phsf67[34],
		phsf68[34], phsf69[34], phsf70[34];
};

#define mnmphs_1 (*(struct mnmphs_1_ *)&mnmphs_)
#define mnmphs_2 (*(struct mnmphs_2_ *)&mnmphs_)

struct shur_1_
{
	float shn[430];
};
struct shur_2_
{
	float shn001[70], shn076[75], shn151[75], shn226[75], shn301[75], shn376[54], shdum[6];
};

#define shur_1 (*(struct shur_1_ *)&shur_)
#define shur_2 (*(struct shur_2_ *)&shur_)

struct
{
	float e_1[37];
	long fill_2[31];
	float e_3[3];
	long fill_4[31];
	float e_5[3];
	long fill_6[31];
	float e_7[3];
	long fill_8[31];
	float e_9[3];
	long fill_10[31];
	float e_11[544];
} prfd_ = {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f, 24.f, 25.f, 30.f, 35.f, 40.f, 45.f, 50.f, 70.f, 100.f, 99999.f, .0662f, .0415f, .026f, {0}, .158f, .0991f, .0621f, {0}, .379f, .379f, .0621f, {0}, .77f, .77f, .0621f, {0}, 1.94f, 1.94f, .0621f, {0}, 0.f, 0.f, 0.f, .0114f, .00643f, .00485f, .00354f, .00231f, .00141f, 9.8e-4f, 7.87e-4f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, .0272f, .012f, .00485f, .00354f, .00231f, .00141f, 9.8e-4f, 7.87e-4f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, .0146f, .0102f, .00931f, .00771f, .00623f, .00337f, .00182f, .00114f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, .0346f, .0185f, .00931f, .00771f, .00623f, .00337f, .00182f, .00114f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 7.14e-4f, 6.64e-4f, 6.23e-4f, 6.45e-4f, 6.43e-4f, 6.41e-4f, 6e-4f, 5.62e-4f, 4.91e-4f, 4.23e-4f, 3.52e-4f, 2.95e-4f, 2.42e-4f, 1.9e-4f, 1.5e-4f, 3.32e-5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, .00179f, .00221f, .00275f, .00289f, .00292f, .00273f, .00246f, .0021f, .00171f, .00135f, .00109f, 8.6e-4f, 6.6e-4f, 5.15e-4f, 4.09e-4f, 7.6e-5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, .00231f, .00325f, .00452f, .0064f, .00781f, .00942f, .0107f, .011f, .0086f, .0051f, .0027f, .00146f, 8.9e-4f, 5.8e-4f, 4.09e-4f, 7.6e-5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, .00231f, .00325f, .00452f, .0064f, .0101f, .0235f, .061f, .1f, .04f, .00915f, .00313f, .00146f, 8.9e-4f, 5.8e-4f, 4.09e-4f, 7.6e-5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 7.99e-4f, 6.41e-4f, 5.17e-4f, 4.42e-4f, 3.95e-4f, 3.82e-4f, 4.25e-4f, 5.2e-4f, 5.81e-4f, 5.89e-4f, 5.02e-4f, 4.2e-4f, 3e-4f, 1.98e-4f, 1.31e-4f, 3.32e-5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, .00212f, .00245f, .0028f, .00289f, .00292f, .00273f, .00246f, .0021f, .00171f, .00135f, .00109f, 8.6e-4f, 6.6e-4f, 5.15e-4f, 4.09e-4f, 7.6e-5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, .00212f, .00245f, .0028f, .0036f, .00523f, .00811f, .012f, .0152f, .0153f, .0117f, .00709f, .0045f, .0024f, .00128f, 7.76e-4f, 7.6e-5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, .00212f, .00245f, .0028f, .0036f, .00523f, .00811f, .0127f, .0232f, .0485f, .1f, .055f, .0061f, .0024f, .00128f, 7.76e-4f, 7.6e-5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 3.32e-5f, 1.64e-5f, 7.99e-6f, 4.01e-6f, 2.1e-6f, 1.6e-7f, 9.31e-10f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 7.6e-5f, 2.45e-5f, 7.99e-6f, 4.01e-6f, 2.1e-6f, 1.6e-7f, 9.31e-10f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 7.6e-5f, 7.2e-5f, 6.95e-5f, 6.6e-5f, 5.04e-5f, 1.03e-5f, 4.5e-7f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 3.32e-5f, 4.25e-5f, 5.59e-5f, 6.6e-5f, 5.04e-5f, 1.03e-5f, 4.5e-7f, 0.f};

/* Table of constant values */

static long c__1 = 1;
static long c__9 = 9;
static long c__2 = 2;
static long c__5 = 5;
static long c__18 = 18;
static double c_b749 = .63;
static double c_b750 = .981;
static double c_b751 = .3324;
static double c_b752 = 1.1406;
static double c_b753 = -2.6343;
static double c_b754 = .9834;
static double c_b755 = -2.5294;
static double c_b756 = 1.0443;
static double c_b757 = -2.4359;
static double c_b758 = .9681;
static double c_b759 = -1.9537;
static double c_b760 = .9555;
static double c_b761 = -1.5378;
static double c_b762 = .9362;
static double c_b763 = -1.6338;
static double c_b764 = .9233;
static double c_b765 = -.9398;
static double c_b766 = .8658;
static double c_b767 = -.1034;
static double c_b768 = .8874;
static double c_b769 = -.2576;
static double c_b770 = .7982;
static double c_b771 = .0588;
static double c_b772 = .8088;
static double c_b773 = .2816;
static double c_b774 = .6642;
static double c_b775 = .2764;
static double c_b776 = .6656;
static double c_b777 = .5061;
static double c_b778 = .42;
static double c_b779 = 1.3909;
static double c_b780 = .4221;
static double c_b781 = .7678;
static double c_b782 = .3739;
static double c_b783 = .1225;
static double c_b784 = .177;
static double c_b785 = .9827;
static double c_b786 = .3921;
static double c_b787 = .1942;
static double c_b788 = .6705;
static double c_b789 = -2.256;
static double c_b790 = .7038;
static double c_b791 = -5.0768;
static double c_b792 = .7258;
static double c_b793 = -1.674;
static double c_b794 = .6982;
static double c_b795 = -1.8107;
static double c_b796 = .8867;
static double c_b797 = -.5327;
static double c_b798 = .7883;
static double c_b799 = -1.3244;
static double c_b800 = .6899;
static double c_b801 = -.8152;
static double c_b802 = .6035;
static double c_b803 = .6026;
static double c_b804 = .7589;
static double c_b805 = .6911;
static double c_b806 = .9267;
static double c_b807 = .1716;
static double c_b808 = .7139;
static double c_b809 = -.4185;
static double c_b810 = .3783;
static double c_b811 = .9399;
static double c_b812 = .7203;
static double c_b813 = -.1836;
static double c_b814 = .7764;
static double c_b815 = 1.1931;
static double c_b816 = 1.1879;
static double c_b817 = 2.9738;
static double c_b818 = .9353;
static double c_b819 = .1936;
static double c_b820 = .8023;
static double c_b821 = -.9111;
static double c_b822 = .6968;
static double c_b823 = .3377;
static double c_b824 = .5265;
static double c_b825 = -.4702;
static double c_b826 = .3956;
static double c_b827 = -.0545;
static double c_b828 = .2943;
static double c_b829 = 1.2316;
static double c_b830 = .2135;
static double c_b831 = .0733;
static float c_b1128 = 90.f;
static float c_b1257 = 0.f;
static double c_b1423 = 1.5873015873015872;
static float c_b1471 = 1.f;
static double c_b1631 = .21;
static double c_b1641 = .84;
static double c_b1642 = .846;
static double c_b1661 = 10.;
static double c_b1716 = 2.;
static float c_b1750 = 10.f;
static float c_b1804 = 33.333f;
static double c_b1830 = .33333;
static double c_b1937 = 1.5;
static float c_b2008 = 20.f;
static float c_b2088 = 1.83899f;
static float c_b2089 = 1639.f;
static float c_b2090 = 52340.4f;
static float c_b2091 = 10399.2f;
static float c_b2092 = 588.24f;
static float c_b2093 = 345005.f;
static float c_b2094 = 259913.f;
static float c_b2095 = 161.29f;
static float c_b2096 = 43319.7f;
static float c_b2097 = 27661.2f;
static double c_b2098 = .25;
static float c_b2113 = 1.79907f;
static float c_b2114 = 3352.27f;
static float c_b2115 = 999140.f;
static float c_b2116 = 151963.f;
static float c_b2118 = 50483.5f;
static float c_b2119 = 9246.27f;
static float c_b2121 = 844697.f;
static float c_b2122 = 1076150.f;
static float c_b2138 = .25f;
static float c_b2139 = 300.f;
static float c_b2140 = .47f;
static float c_b2141 = 3.f;
static float c_b2142 = .39f;
static float c_b2143 = 17.f;
static float c_b2144 = .45f;
static float c_b2145 = 1.3f;
static float c_b2146 = .41f;
static float c_b2147 = 62.f;
static float c_b2148 = .35f;
static float c_b2149 = 1.7f;
static float c_b2162 = .4f;
static float c_b2163 = 2.f;
static float c_b2172 = .22f;
static float c_b2173 = 1.8f;
static float c_b2180 = .12f;
static float c_b2181 = 6.1f;
static float c_b2182 = .042f;
static float c_b2183 = .6f;
static float c_b2186 = .165f;
static float c_b2187 = 2.4f;
static float c_b2194 = .01f;
static float c_b2195 = 4.95f;
static float c_b2196 = .05f;
static float c_b2200 = .009f;
static float c_b2204 = .27f;
static float c_b2205 = 2.97f;
static float c_b2206 = .04f;
static float c_b2210 = .06f;
static float c_b2214 = .025f;
static long c__4 = 4;
static long c__3 = 3;

/* Main program */ int _runLowtran(LOWTRAN_ResultBuffer *resultBuffer,
								   const LOWTRAN_Card1 *lowtran_card1,
								   const LOWTRAN_Card1a *lowtran_card1a,
								   const LOWTRAN_Card1b *lowtran_card1b,
								   const LOWTRAN_Card2 *lowtran_card2,
								   const LOWTRAN_Card2a *lowtran_card2a,
								   const LOWTRAN_Card2b *lowtran_card2b,
								   const LOWTRAN_Card2c *lowtran_card2c,
								   const LOWTRAN_Card2d *lowtran_card2d,
								   const LOWTRAN_Card3 *lowtran_card3,
								   const LOWTRAN_Card3a1 *lowtran_card3a1,
								   const LOWTRAN_Card3a2 *lowtran_card3a2,
								   const LOWTRAN_Card4 *lowtran_card4)
{

	/* Initialized data */
	static long irpt = 0;
	static long maxgeo = 68;

	/* Format strings */
	static char fmt_1000[] = "(\0021\002,20x,\002***** LOWTRAN 7 *****\002)";
	static char fmt_1110[] = "(13i5,f8.3,f7.2)";
	static char fmt_1111[] = "(\0020 CARD 1  *****\002,13i5,f8.3,f7.2)";
	static char fmt_1200[] = "(6i5,5f10.3)";
	static char fmt_1201[] = "(\0020 CARD 2  *****\002,6i5,5f10.3)";
	static char fmt_1199[] = "(\0020\002,\002  GNDALT =\002,f10.2)";
	static char fmt_1202[] = "(\0020 GNDALT GT 6.0 RESET TO ZERO, GNDALT WA"
							 "S\002,f10.3)";
	static char fmt_1205[] = "(\0020 RAIN MODEL CALLED, RAIN RATE = \002,f9."
							 "2,\002 MM/HR\002)";
	static char fmt_1210[] = "(3f10.3,i10)";
	static char fmt_1211[] = "(\0020 CARD 2A *****\002,3f10.3,i10)";
	static char fmt_1230[] = "(3f10.3)";
	static char fmt_1231[] = "(\0020 CARD 2B *****\002,3f10.3)";
	static char fmt_1250[] = "(3i5,18a4)";
	static char fmt_1251[] = "(\0020 CARD 2C *****\002,3i5,18a4)";
	static char fmt_1220[] = "(15x,\002CIRRUS ATTENUATION INCLUDED (N O A A "
							 "CIRRUS) \002)";
	static char fmt_1221[] = "(15x,\002CIRRUS ATTENUTION STATISTICALLY DETER"
							 "MENED TO BE\002,f10.3,\002KM\002)";
	static char fmt_1222[] = "(15x,\002CIRRUS THICKNESS USER DETERMINED TO"
							 " BE\002,f10.3,\002KM\002)";
	static char fmt_1223[] = "(15x,\002CIRRUS THICKNESS DEFAULTED TO MEAN VA"
							 "LUE OF    \002,f10.3,\002KM\002)";
	static char fmt_1224[] = "(15x,\002CIRRUS BASE ALTITUDE STATISCALLY DETE"
							 "RMINED TO BE\002,f10.3,\002 KM\002)";
	static char fmt_1225[] = "(15x,\002CIRRUS BASE ALTITUDE USER DETERMINED "
							 "TO BE\002,f10.3,\002 KM\002)";
	static char fmt_1226[] = "(15x,\002CIRRUS BASE ALTITUDE DEFAULTED TO MEA"
							 "N VALUE OF\002,f10.3,\002KM\002)";
	static char fmt_1227[] = "(15x,\002PROBABILTY OF CLOUD OCCURRING IS\002,"
							 "f7.1,\002 PERCENT\002)";
	static char fmt_1312[] = "(6f10.3,i5)";
	static char fmt_1313[] = "(\0020 CARD 3  *****\002,6f10.3,i5)";
	static char fmt_1316[] = "(3f10.3,i5,5x,f10.3,i5,f10.3)";
	static char fmt_1317[] = "(\0020 CARD 3   *****\002,3f10.3,i5,5x,f10.3,i"
							 "5,f10.3)";
	static char fmt_905[] = "(\002  H1 LESS THAN FIRST ALT RESET \002,/\002 "
							"H1 WAS \002,f10.2,\002 1ST ALT = \002,f10.2)";
	static char fmt_1320[] = "(4i5)";
	static char fmt_1321[] = "(\0020 CARD 3A1*****\002,4i5)";
	static char fmt_1322[] = "(8f10.3)";
	static char fmt_1323[] = "(\0020 CARD 3A2*****\002,8f10.3)";
	static char fmt_1326[] = "(i5)";
	static char fmt_1327[] = "(\002 CARD 3B1*****\002,i5)";
	static char fmt_1328[] = "(5e10.3)";
	static char fmt_1329[] = "(\0020 CARD 3B2*****\002,5e10.3)";
	static char fmt_1400[] = "(3f10.3)";
	static char fmt_1401[] = "(\0020 CARD 4  *****\002,3f10.3)";
	static char fmt_1203[] = "(\0020**WARNING** NAVY MODEL IS NOT USEABLE BE"
							 "LOW 250CM-1\002/10x,\002 PROGRAM WILL SWITCH TO IHAZE=4 LOWTRAN "
							 "5 MARITIME\002//)";
	static char fmt_1410[] = "(\0020 PROGRAM WILL COMPUTE \002,6a4)";
	static char fmt_1204[] = "(\002   LUNAR SOURCE ONLY  \002)";
	static char fmt_1411[] = "(\0020 MULTIPLE SCATTERING HAS BEEN TURNED O"
							 "FF \002)";
	static char fmt_1412[] = "(\0020 CALCULATIONS WILL BE DONE USING MULTIPL"
							 "E SCATTERING \002)";
	static char fmt_1500[] = "(\0020 ATMOSPHERIC MODEL\002,/,10x,\002TEMPERA"
							 "TURE = \002,i4,5x,5a4,/,10x,\002WATER VAPOR = \002,i4,5x,5a4,/,1"
							 "0x,\002OZONE       = \002,i4,5x,5a4)";
	static char fmt_1501[] = "(20x,\002  M4 = \002,i5,\002 M5 = \002,i5,\002"
							 " M6 = \002,i5,\002 MDEF = \002,i5)";
	static char fmt_1510[] = "(\0020 AEROSOL MODEL\002,/,10x,\002REGIME\002,"
							 "t35,\002AEROSOL TYPE\002,t60,\002PROFILE\002,t85,\002SEASON\002,"
							 "/,/,10x,\002BOUNDARY LAYER (0-2 KM)\002,t35,5a4,t60,f5.1,\002 KM"
							 " VIS AT SEA LEVEL\002,/,10x,\002TROPOSPHERE  (2-10KM)\002,t35,5a"
							 "4,t60,5a4,t85,5a4,/,10x,\002STRATOSPHERE (10-30KM)\002,t35,5a4,t"
							 "60,5a4,t85,5a4,/,10x,\002UPPER ATMOS (30-100KM)\002,t35,5a4,t60,"
							 "5a4)";
	static char fmt_1515[] = "(\0020 HORIZONTAL PATH\002,/,10x,\002ALTITUDE "
							 "= \002,f10.3,\002 KM\002,/,10x,\002RANGE    = \002,f10.3,\002 K"
							 "M\002)";
	static char fmt_1516[] = "(\0020 SLANT PATH, H1 TO H2\002,/,10x,\002H1  "
							 "  = \002,f10.3,\002 KM\002,/,10x,\002H2    = \002,f10.3,\002 K"
							 "M\002,/,10x,\002ANGLE = \002,f10.3,\002 DEG\002,/,10x,\002RANGE "
							 "= \002,f10.3,\002 KM\002,/,10x,\002BETA  = \002,f10.3,\002 DE"
							 "G\002,/,10x,\002LEN   = \002,i6)";
	static char fmt_1517[] = "(\0020 SLANT PATH TO SPACE\002,/,10x,\002H1   "
							 " = \002,f10.3,\002 KM\002,/,10x,\002HMIN  = \002,f10.3,\002 K"
							 "M\002,/,10x,\002ANGLE = \002,f10.3,\002 DEG\002)";
	static char fmt_1530[] = "(\0020 SINGLE SCATTERING CONTROL PARAMETERS SU"
							 "MMARY \002/)";
	static char fmt_1532[] = "(10x,\002OBSERVER LATITUDE =\002,t35,f10.2,"
							 "\002 DEG NORTH OF EQUATOR\002,/,10x,\002OBSERVER LONGITUDE=\002,"
							 "t35,f10.2,\002 DEG WEST OF GREENWICH\002,/,10x,\002SUBSOLAR LATI"
							 "TUDE =\002,t35,f10.2,\002 NORTH OF EQUATOR\002,/,10x,\002SUBSOLA"
							 "R LONGITUDE =\002,t35,f10.2,\002 WEST OF GREENWICH\002,/,10x,"
							 "\002TIME (<0 IS UNDEF)=\002,t35,f10.3,\002 GREENWICH TIME\002,/,"
							 "10x,\002PATH AZIMUTH =\002,t35,f10.3,\002 DEG EAST OF NORTH\002,"
							 "/,10x,\002DAY OF YEAR =\002,t35,i10)";
	static char fmt_1534[] = "(10x,\002RELATIVE AZIMUTH =\002,t35,f10.3,\002"
							 " DEG EAST OF NORTH\002,/,10x,\002SOLAR ZENITH =\002,t35,f10.3"
							 ",\002 DEG \002,/,10x,\002TIME (<0 UNDEF) =\002,t35,f10.3,\002 GR"
							 "EENWICH TIME\002,/,10x,\002PATH AZIMUTH =\002,t35,f10.3,\002 DEG"
							 " EAST OF NORTH\002,/,10x,\002DAY OF THE YEAR =\002,t35,i6)";
	static char fmt_1535[] = "(\0020 EXTRATERRESTIAL SOURCE IS THE SUN\002)";
	static char fmt_1536[] = "(\0020 EXTRATERRESTIAL SOURCE IS THE MOON, MOO"
							 "N PHASE ANGLE =\002,f10.2,\002 DEG\002)";
	static char fmt_1538[] = "(\002O H-G PHASE FUNCTION ,G=\002,f10.3)";
	static char fmt_1540[] = "(\0020 USER SUPPLIED PHASE FUNCTION\002)";
	static char fmt_1542[] = "(\0020 PHASE FUNCTION FROM MIE DATA BASE\002)";
	static char fmt_1555[] = "(\0020 FREQUENCY RANGE \002/,10x,\002 V1 = "
							 "\002,f12.1,\002 CM-1  (\002,f10.2,\002 MICROMETERS)\002,/,10x"
							 ",\002 V2 = \002,f12.1,\002 CM-1  (\002,f10.2,\002 MICROMETERS"
							 ")\002,/10x,\002 DV = \002,f12.1,\002 CM-1\002)";
	static char fmt_1557[] = "(\0020 DIRECT PATH TO SUN INTERSECTS THE EARTH"
							 ": SKIP TO \002,\002NEXT CASE\002)";
	static char fmt_1255[] = "(i5,18a4)";
	static char fmt_1560[] = "(3f10.3,5e10.3)";
	static char fmt_1600[] = "(i5)";
	static char fmt_1620[] = "(\002 -9999.\002)";
	static char fmt_1630[] = "(\0020 CARD 5 *****\002,i5)";

	/* System generated locals */
	long i__1, i__2;
	float r__1;
	olist o__1;

	/* Builtin functions */
	long f_open(olist *);
	double asin(double);
	long s_wsfe(cilist *), e_wsfe(void), s_rsfe(cilist *), do_fio(long *, char *, long), e_rsfe(void);
	/* Subroutine */ void s_copy(char *, char *, long, long);
	// GP: have changed int -> void return type as return type not used anywhere
	// otherwise it messes with f2c and overloads with different return type
	long s_wsle(cilist *), do_lio(long *, long *, char *, long),
		e_wsle(void);
	/* Subroutine */ int s_stop(char *, long);

	/* Local variables */
	static float g;
	static long i__, j, k, n, i1, i2, i3, i4, i5, ia, ib, ic, ii, ik;
	static float ro;
	static long mm1;
	static float h1s, h2s;
	static long mm2, mm3;
	extern /* Subroutine */ int geo_(long *, float *, long *);
	static long iph;
	extern /* Subroutine */ int vsa_(long *, float *, float *, float *, float *, float *, float *, float *, long *);
	static long iday, mdel;
	static float time;
	static long lens, jprt;
	static float plst[68], w15sv, alam1, alam2, parm1, parm2, parm3, parm4;
	static long iflga;
	static float betas;
	static long mdels, iflgt;
	static float cprob;
	extern /* Subroutine */ int rdexa_(void);
	static long iparm;
	static float rangs;
	extern /* Subroutine */ int rdnsm_(void);
	static long ihvul;
	static float psipo;
	static long ihmet, issgs;
	extern /* Subroutine */ int ssgeo_(long *, long *, long *, float *, float *, float *, float *, float *, float *, long *);
	static long irain;
	extern /* Subroutine */ int trans_(LOWTRAN_ResultBuffer *, long *, long *, long *, float *);
	static float bendng, anglem;
	extern /* Subroutine */ int exabin_(void);

	extern /* Subroutine */ int marine_(float *, long *, float *, float *,
										long *, float *, float *, long *);
	static float angles;
	extern /* Subroutine */ int aernsm_(long *, float *), stdmdl_(void),
		aertmp_(void);
	static float csensv[68];
	static long ierror, isourc;
	extern /* Subroutine */ int equlwc_(void);
	static float qthets[68];
	extern /* Subroutine */ int cirrus_(float *, float *, long *, float *,
										float *);
	extern /* Subroutine */ int subsol_(float *, float *, float *, long *);
	static long itypes;

	/* Fortran I/O blocks */
	static cilist io___4 = {0, 0, 0, fmt_1000, 0};
	static cilist io___8 = {0, 0, 0, fmt_1110, 0};
	static cilist io___9 = {0, 0, 0, fmt_1111, 0};
	static cilist io___10 = {0, 0, 0, fmt_1200, 0};
	static cilist io___12 = {0, 0, 0, fmt_1201, 0};
	static cilist io___13 = {0, 0, 0, fmt_1199, 0};
	static cilist io___14 = {0, 0, 0, fmt_1202, 0};
	static cilist io___15 = {0, 0, 0, fmt_1205, 0};
	static cilist io___19 = {0, 0, 0, fmt_1210, 0};
	static cilist io___20 = {0, 0, 0, fmt_1211, 0};
	static cilist io___24 = {0, 0, 0, fmt_1230, 0};
	static cilist io___25 = {0, 0, 0, fmt_1231, 0};
	static cilist io___27 = {0, 0, 0, fmt_1250, 0};
	static cilist io___28 = {0, 0, 0, fmt_1251, 0};
	static cilist io___30 = {0, 0, 0, fmt_1220, 0};
	static cilist io___31 = {0, 0, 0, fmt_1221, 0};
	static cilist io___32 = {0, 0, 0, fmt_1222, 0};
	static cilist io___33 = {0, 0, 0, fmt_1223, 0};
	static cilist io___34 = {0, 0, 0, fmt_1224, 0};
	static cilist io___35 = {0, 0, 0, fmt_1225, 0};
	static cilist io___36 = {0, 0, 0, fmt_1226, 0};
	static cilist io___37 = {0, 0, 0, fmt_1227, 0};
	static cilist io___50 = {0, 0, 0, fmt_1312, 0};
	static cilist io___52 = {0, 0, 0, fmt_1313, 0};
	static cilist io___53 = {0, 0, 0, fmt_1316, 0};
	static cilist io___54 = {0, 0, 0, fmt_1317, 0};
	static cilist io___55 = {0, 0, 0, fmt_905, 0};
	static cilist io___63 = {0, 0, 0, fmt_1320, 0};
	static cilist io___64 = {0, 0, 0, fmt_1321, 0};
	static cilist io___65 = {0, 0, 0, fmt_1322, 0};
	static cilist io___66 = {0, 0, 0, fmt_1323, 0};
	static cilist io___67 = {0, 0, 0, fmt_1326, 0};
	static cilist io___68 = {0, 0, 0, fmt_1327, 0};
	static cilist io___69 = {0, 0, 0, fmt_1328, 0};
	static cilist io___70 = {0, 0, 0, fmt_1329, 0};
	static cilist io___71 = {0, 0, 0, fmt_1400, 0};
	static cilist io___72 = {0, 0, 0, fmt_1401, 0};
	static cilist io___73 = {0, 0, 0, fmt_1203, 0};
	static cilist io___74 = {0, 0, 0, fmt_1410, 0};
	static cilist io___76 = {0, 0, 0, fmt_1204, 0};
	static cilist io___77 = {0, 0, 0, fmt_1411, 0};
	static cilist io___78 = {0, 0, 0, fmt_1412, 0};
	static cilist io___83 = {0, 0, 0, fmt_1500, 0};
	static cilist io___86 = {0, 0, 0, fmt_1501, 0};
	static cilist io___89 = {0, 0, 0, fmt_1510, 0};
	static cilist io___95 = {0, 0, 0, fmt_1515, 0};
	static cilist io___96 = {0, 0, 0, fmt_1516, 0};
	static cilist io___97 = {0, 0, 0, fmt_1517, 0};
	static cilist io___98 = {0, 0, 0, fmt_1530, 0};
	static cilist io___99 = {0, 0, 0, fmt_1532, 0};
	static cilist io___100 = {0, 0, 0, fmt_1534, 0};
	static cilist io___101 = {0, 0, 0, fmt_1535, 0};
	static cilist io___102 = {0, 0, 0, fmt_1536, 0};
	static cilist io___103 = {0, 0, 0, fmt_1538, 0};
	static cilist io___104 = {0, 0, 0, fmt_1540, 0};
	static cilist io___105 = {0, 0, 0, fmt_1542, 0};
	static cilist io___108 = {0, 0, 0, fmt_1555, 0};
	static cilist io___118 = {0, 0, 0, fmt_1557, 0};
	static cilist io___120 = {0, 0, 0, fmt_1110, 0};
	static cilist io___121 = {0, 0, 0, fmt_1110, 0};
	static cilist io___122 = {0, 0, 0, fmt_1200, 0};
	static cilist io___123 = {0, 0, 0, fmt_1200, 0};
	static cilist io___124 = {0, 0, 0, fmt_1210, 0};
	static cilist io___125 = {0, 0, 0, fmt_1210, 0};
	static cilist io___126 = {0, 0, 0, fmt_1230, 0};
	static cilist io___127 = {0, 0, 0, fmt_1230, 0};
	static cilist io___128 = {0, 0, 0, fmt_1255, 0};
	static cilist io___129 = {0, 0, 0, fmt_1255, 0};
	static cilist io___130 = {0, 0, 0, fmt_1312, 0};
	static cilist io___131 = {0, 0, 0, fmt_1312, 0};
	static cilist io___132 = {0, 0, 0, fmt_1560, 0};
	static cilist io___133 = {0, 0, 0, fmt_1560, 0};
	static cilist io___134 = {0, 0, 0, fmt_1320, 0};
	static cilist io___135 = {0, 0, 0, fmt_1320, 0};
	static cilist io___136 = {0, 0, 0, fmt_1322, 0};
	static cilist io___137 = {0, 0, 0, fmt_1322, 0};
	static cilist io___138 = {0, 0, 0, fmt_1400, 0};
	static cilist io___139 = {0, 0, 0, fmt_1400, 0};
	static cilist io___140 = {0, 0, 0, fmt_1600, 0};
	static cilist io___141 = {0, 0, 0, fmt_1600, 0};
	static cilist io___142 = {0, 0, 0, fmt_1600, 0};
	static cilist io___144 = {0, 0, 0, fmt_1600, 0};
	static cilist io___145 = {0, 0, 0, fmt_1600, 0};
	static cilist io___146 = {0, 0, 0, fmt_1600, 0};
	static cilist io___147 = {0, 0, 0, fmt_1620, 0};
	static cilist io___148 = {0, 0, 0, fmt_1620, 0};
	static cilist io___149 = {0, 0, 0, fmt_1630, 0};
	static cilist io___150 = {0, 6, 0, 0, 0};

	/* ***********************************************************************LWT  110 */
	/*     LOWTRAN7  (LAST REVISED FEB 1 1992)   REVISION 4.2                LWT* 120 */
	/*                                                                       LWT  130 */
	/*               AUTHORS                                                 LWT  140 */
	/*                                                                       LWT  150 */
	/*               F.X.KNEIZYS                                             LWT  160 */
	/*               E. P. SHETTLE                                           LWT  170 */
	/*               G.P. ANDERSON                                           LWT  180 */
	/*               L. W. ABREU                                             LWT  190 */
	/*               J. H. CHETWYND                                          LWT  200 */
	/*               J. E. A. SELBY    (GRUMMAN AEROSPACE)                   LWT  210 */
	/*               S. A. CLOUGH      (AER INC)                             LWT  220 */
	/*               W. O. GALLERY     (OPTIMETRICS)                         LWT  230 */
	/*                                                                       LWT  240 */
	/*   PROGRAM LOWTRAN  CALCULATES THE TRANSMITTANCE AND/OR RADIANCE       LWT  250 */
	/*   OF THE ATMOSPHERE  FROM   0 CM-1 TO 50000 CM-1 (0.20 TO INFINITY    LWT  260 */
	/*   MICRONS) AT 20 CM-1 SPECTRAL RESOLUTION ON A LINEAR                 LWT  270 */
	/*   WAVENUMBER SCALE WITH 5CM-1 SAMPLING                                LWT  280 */
	/*                                                                       LWT  290 */
	/*   LOWTRAN 7 IS A LOW-RESOLUTION PROPAGATION MODEL FOR CALCULATING     LWT  300 */
	/*   ATMOSPHERIC TRANSMITTANCE AND BACKGROUND RADIANCE FROM 0 TO         LWT  310 */
	/*   50,000 CM-1 AT A RESOLUTION OF 20 CM-1 WITH A MINIMUM OF 5 CM-1     LWT  320 */
	/*   SAMPLING.  THE MODEL IS BASED ON THE LOWTRAN 6 (1983) MODEL.        LWT  330 */
	/*   THE PROGRAM CALCULATES SINGLE SCATTERED SOLAR (OR LUNAR)            LWT  340 */
	/*   RADIATION.  MULTIPLE SCATTERED RADIATION HAS BEEN ADDED TO THE      LWT  350 */
	/*   MODEL AS WELL AS NEW MOLECULAR BAND MODEL PARAMETERS AND NEW OR     LWT  360 */
	/*   UPDATED OZONE AND MOLECULAR OXYGEN ABSORPTION PARAMETERS FOR THE    LWT  370 */
	/*   UV.  OTHER MODIFICATIONS INCLUDE A WIND-DEPENDENT DESERT MODEL, NEW LWT  380 */
	/*   CIRRUS CLOUD MODELS, AND NEW CLOUD AND RAIN MODELS.  THE MODEL ALSO LWT  390 */
	/*   INCLUDES NEW REPRESENTATIVE (GEOGRAPHICAL AND SEASONAL) ATMOSPHERIC LWT  400 */
	/*   MODELS AND UPDATED AEROSOL MODELS WITH OPTIONS TO REPLACE THEM WITH LWT  410 */
	/*   USER-DERIVED VALUES.  SIX MODES OF PROGRAM EXECUTION ARE ALLOWED    LWT  420 */
	/*   WITH THE NEW MODEL AND COMPUTER CODE FOR A GIVEN SLANT PATH         LWT  430 */
	/*   UTILIZING SPHERICAL-REFRACTIVE GEOMETRY.  THE ARMY VERTICAL         LWT  440 */
	/*   STRUCTURE ALGORITHM HAS BEEN MODIFIED TO INCLUDE THE NEW PEDESTAL   LWT  450 */
	/*   MODEL BELOW THE CLOUD BASE.  A NEW OPTION HAS BEEN  ADDED TO        LWT  460 */
	/*   MODIFY THE AEROSOL PROFILE, IF THE GROUND IS NOT AT SEA LEVEL.      LWT  470 */
	/*                                                                       LWT  480 */
	/* ***********************************************************************LWT  490 */
	/*                                                                       LWT  500 */
	/*     THE FOLLOWING INFORMATION SHOULD BE PROVIDED BY THE USER          LWT  510 */
	/*     AND MAILED TO   L.W ABREU  ,AFGL/OPE,HANSCOM AFB,MASS 01731       LWT* 520 */
	/*     THIS WILL BE USED TO UPDATE THE AFGL MAILING LIST                 LWT  530 */
	/*     AND FOR NOTIFICATION TO THE USER OF ERRORS IN THE CODE            LWT  540 */
	/*                                                                       LWT  550 */
	/*                                                                       LWT  560 */
	/*           MY NAME IS                                                  LWT  570 */
	/*           COMPANY                                                     LWT  580 */
	/*           ADDRESS                                                     LWT  590 */
	/*           MY COMPUTER IS                                              LWT  600 */
	/*                                                                       LWT  610 */
	/*                                                                       LWT  620 */
	/* ***********************************************************************LWT  630 */
	/*   THE USE OF THE WORD 'CARD' IS EQUIVALENT TO EDITING WITH 80 COLUMNS LWT  640 */
	/*                                                                       LWT  650 */
	/*     PROGRAM ACTIVATED BY SUBMISSION OF A FIVE  (OR MORE)              LWT  660 */
	/*      CARD SEQUENCE AS FOLLOWS                                         LWT  670 */
	/*                                                                       LWT  680 */
	/*     CARD 1    MODEL,ITYPE,IEMSCT,IMULT,M1,M2,M3,                      LWT  690 */
	/*               M4,M5,M6,MDEF,IM,NOPRT,TBOUND,SALB                      LWT  700 */
	/*                          FORMAT(13I5,F8.3,F7.2)                       LWT  710 */
	/*                                                                       LWT  720 */
	/*     CARD 2    IHAZE,ISEASN,IVULCN,ICSTL,ICLD,IVSA,VIS,WSS,WHH,RAINRT, LWT  730 */
	/*               GNDALT                                                  LWT  740 */
	/*                          FORMAT(6I5,5F10.3)                           LWT  750 */
	/*                                                                       LWT  760 */
	/*               CARD 2A    CTHIK,CALT,CEXT,ISEED       (ICLD=18,19,20)  LWT  770 */
	/*                          FORMAT(3F10.3,I10)                           LWT  780 */
	/*                                                                       LWT  790 */
	/*               CARD 2B    ZCVSA,ZTVSA,ZINVSA    (IVSA=1)               LWT  800 */
	/*                          FORMAT(3F10.3)                               LWT  810 */
	/*                                                                       LWT  820 */
	/*               CARD 2C    ML,IRD1,IRD2,TITLE (MODEL=0 / 7,IM=1)        LWT  830 */
	/*                          FORMAT(3I5,18A4)                             LWT  840 */
	/*                                                                       LWT  850 */
	/* C------------------------ BEGIN ML LOOP                                LWT  860 */
	/* C-                                                                     LWT  870 */
	/* C-             CARD 2C1   ZMDL,P,T,WMOL(1),WMOL(2),WMOL(3),JCHAR       LWT  880 */
	/* C-                        FORMAT(F10.3,5E10.3,15A1)                    LWT  890 */
	/* C-                                                                     LWT  900 */
	/* C-             CARD 2C2   (WMOL(J),J=4,11)                             LWT  910 */
	/* C-                        FORMAT(8E10.3)                               LWT  920 */
	/* C-                                                                     LWT  930 */
	/* C-             CARD 2C2   WMOL(12)                                     LWT  940 */
	/* C-                        FORMAT(8E10.3)                               LWT  950 */
	/* C-                                                                     LWT  960 */
	/* C-             CARD 2C3   AHAZE,EQLWCZ,RRATZ,IHA1,ICLD1,               LWT  970 */
	/* C-                        IVUL1,ISEA1,ICHR                             LWT  980 */
	/* C-                        FORMAT(10X,3F10.3,5I5)                       LWT  990 */
	/* C-                                                                     LWT 1000 */
	/* C------------------------ END ML LOOP                                  LWT 1010 */
	/*                                                                       LWT 1020 */
	/*               CARD 2D    IREG(1 TO 4) (IHAZE=7 OR ICLD = 11)          LWT 1030 */
	/*                          FORMAT(4I5)                                  LWT 1040 */
	/*                                                                       LWT 1050 */
	/*               CARD 2D1   AWCCON,TITLE                                 LWT 1060 */
	/*                          FORMAT(E10.3,18A4)                           LWT 1070 */
	/*                                                                       LWT 1080 */
	/*               CARD 2D2   (VX(I),EXTC(N,I),ABSC(N,I),ASYM(N,I),I=1,47) LWT 1090 */
	/*                          (IHAZE=7 OR ICLD=11)                         LWT 1100 */
	/*                          FORMAT(3(F6.2,2F7.5,F6.4))                   LWT 1110 */
	/*                                                                       LWT 1120 */
	/*     CARD 3    H1,H2,ANGLE,RANGE,BETA,RO,LEN                           LWT 1130 */
	/*                          FORMAT(6F10.3,I5)                            LWT 1140 */
	/*                                                                       LWT 1150 */
	/*               ALTERNATE  CARD 3 (IEMSCT=3)                            LWT 1160 */
	/*                          H1,H2,ANGLE,IDAY,RO,ISOURC,ANGLEM            LWT 1170 */
	/*                          FORMAT(3F10.3,I5,5X,F10.3,I5,F10.3)          LWT 1180 */
	/*                                                                       LWT 1190 */
	/*               CARD 3A1   IPARM,IPH,IDAY,ISOURC           (IEMSCT=2)   LWT 1200 */
	/*                          FORMAT(4I5)                                  LWT 1210 */
	/*                                                                       LWT 1220 */
	/*               CARD 3A2    PARM1,PARM2,PARM3,PARM4,TIME,PSIPO,ANGLEM,G LWT 1230 */
	/*                           FORMAT(8F10.3)               (IEMSCT=2)     LWT 1240 */
	/*                                                                       LWT 1250 */
	/*               CARD 3B1    NANGLS       (IPH=1)                        LWT 1260 */
	/*                           FORMAT(I5)                                  LWT 1270 */
	/*                                                                       LWT 1280 */
	/*               CARD 3B2(1 TO NANGLS)    (IPH=1)                        LWT 1290 */
	/*                      (ANGF(I),F(1,I),F(2,I),F(3,I),F(4,I),I=1,NANGLS) LWT 1300 */
	/*                           FORMAT(5E10.3)                              LWT 1310 */
	/*                                                                       LWT 1320 */
	/*     CARD 4    V1, V2, DV                                              LWT 1330 */
	/*                           FORMAT(3F10.3)                              LWT 1340 */
	/*                                                                       LWT 1350 */
	/*     CARD 5    IRPT                                                    LWT 1360 */
	/*                           FORMAT(I5)                                  LWT 1370 */
	/*                                                                       LWT 1380 */
	/* ***********************************************************************LWT 1390 */
	/*   ** FOLLOWING IS A FULL DESCRIPTION OF EACH CARD                     LWT 1400 */
	/*                                                                       LWT 1410 */
	/*     CARD 1    MODEL,ITYPE,IEMSCT,IMULT,M1,M2,M3,                      LWT 1420 */
	/*               M4,M5,M6,MDEF,IM,NOPRT,TBOUND,SALB                      LWT 1430 */
	/*                         FORMAT(13I5,F8.3,F7.2)                        LWT 1440 */
	/*                                                                       LWT 1450 */
	/*             'MODEL' SELECTS ONE OF SIX GEOGRAPHICAL MODEL ATMOSPHERES LWT 1460 */
	/*              OR SPECIFIES THAT USER-DEFINED METEOROLOGICAL            LWT 1470 */
	/*              DATA ARE TO BE USED.                                     LWT 1480 */
	/*                                                                       LWT 1490 */
	/*                                                                       LWT 1500 */
	/*     MODEL=0 IF METEOROLOGICAL DATA ARE SPECIFIED(HORIZONTAL PATH ONLY)LWT 1510 */
	/*           1 TROPICAL ATMOSPHERE                                       LWT 1520 */
	/*           2 MIDLATITUDE SUMMER                                        LWT 1530 */
	/*           3 MIDLATITUDE WINTER                                        LWT 1540 */
	/*           4 SUBARCTIC   SUMMER                                        LWT 1550 */
	/*           5 SUBARCTIC   WINTER                                        LWT 1560 */
	/*           6 1976 U.S. STANDARD ATMOSPHERE                             LWT 1570 */
	/*           7 IF A NEW MODEL ATMOSPHERE( OR RADIOSONDE DATA) IS TO BE   LWT 1580 */
	/*             READ IN.                                                  LWT 1590 */
	/*                                                                       LWT 1600 */
	/*     [NOTE: MODEL=0  USED FOR HORIZONTAL PATH ONLY]                    LWT 1610 */
	/*                                                                       LWT 1620 */
	/*                                                                       LWT 1630 */
	/*           'ITYPE' INDICATES THE TYPE OF ATMOSPHERIC PATH              LWT 1640 */
	/*                                                                       LWT 1650 */
	/*     ITYPE=1 FOR A HORIZONTAL (CONSTANT-PRESSURE) PATH                 LWT 1660 */
	/*           2 VERTICAL OR SLANT PATH BETWEEN TWO ALTITUDES              LWT 1670 */
	/*           3 FOR A VERTICAL OR SLANT PATH TO SPACE                     LWT 1680 */
	/*                                                                       LWT 1690 */
	/*                                                                       LWT 1700 */
	/*           'IEMSCT' DETERMINES THE MODE OF EXECUTION OF THE PROGRAM    LWT 1710 */
	/*                                                                       LWT 1720 */
	/*     IEMSCT=0    PROGRAM EXECUTION IN TRANSMITTANCE MODE.              LWT 1730 */
	/*            1    PROGRAM EXECUTION IN RADIANCE MODE.                   LWT 1740 */
	/*            2    PROGRAM EXECUTION IN RADIANCE MODE WITH SOLAR/LUNAR   LWT 1750 */
	/*                  SCATTERED RADIANCE INCLUDED.                         LWT 1760 */
	/*            3    DIRECT SOLAR IRRADIANCE                               LWT 1770 */
	/*                                                                       LWT 1780 */
	/*           'IMULT' DETERMINES EXECUTION WITH MULTIPLE SCATTERING       LWT 1790 */
	/*                                                                       LWT 1800 */
	/*     IMULT = 0 PROGRAM EXECUTED WITHOUT MULTIPLE SCATTERING            LWT 1810 */
	/*             1 PROGRAM EXECUTED WITH MULTIPLE SCATTERING               LWT 1820 */
	/*              [NOTE: IEMSCT MUST EQUAL 1 OR 2 FOR MULTIPLE SCATTERING] LWT 1830 */
	/*                                                                       LWT 1840 */
	/*                                                                       LWT 1850 */
	/*           'M1,M2,M3' ARE USED TO MODIFY OR SUPPLEMENT THE ALTITUDE    LWT 1860 */
	/*            PROFILES OF TEMPERATURE AND PRESSURE,WATER VAPOR,AND OZONE LWT 1870 */
	/*                                                                       LWT 1880 */
	/*           'M4,M5,M6'  SEASONAL DEPENDENCE CH4,N2O,CO                  LWT 1890 */
	/*           'MDEF'       USE DEFAULT FOR OTHER GASES                    LWT 1900 */
	/*                                                                       LWT 1910 */
	/*     FOR NORMAL OPERATION OF PROGRAM   (MODEL 1 TO 6)                  LWT 1920 */
	/*     SET M1=M2=M3=0 , M4=M5=M6=MDEF = 0                                LWT 1930 */
	/*                                                                       LWT 1940 */
	/*     THESE PARAMETERS ARE RESET TO DEFAULT VALUES BY MODEL             LWT 1950 */
	/*     WHEN THEY ARE EQUAL TO ZERO                                       LWT 1960 */
	/*                                                                       LWT 1970 */
	/*      EXCEPT FOR MODEL 0 AND 7                                         LWT 1980 */
	/*      WHEN M1 = 0 M1 RESET TO 'MODEL'                                  LWT 1990 */
	/*      WHEN M2 = 0 M2 RESET TO 'MODEL'                                  LWT 2000 */
	/*      WHEN M3 = 0 M3 RESET TO 'MODEL'                                  LWT 2010 */
	/*      WHEN M4 = 0 M4 RESET TO 'MODEL'                                  LWT 2020 */
	/*      WHEN M5 = 0 M5 RESET TO 'MODEL'                                  LWT 2030 */
	/*      WHEN M6 = 0 M6 RESET TO 'MODEL'                                  LWT 2040 */
	/*      WHEN MDEF=0 MDEF RESET TO 1  FOR ALL REMAINING                   LWT 2050 */
	/*                                                                       LWT 2060 */
	/*     M1=1-6 DEFAULT TEMP. AND PRESSURE TO SPECIFIED MODEL ATM.         LWT 2070 */
	/*                                                                       LWT 2080 */
	/*     M2=1-6 DEFAULT H2O   TO SPECIFIED MODEL ATM.                      LWT 2090 */
	/*                                                                       LWT 2100 */
	/*     M3=1-6 DEFAULT OZONE TO SPECIFIED MODEL ATM.                      LWT 2110 */
	/*                                                                       LWT 2120 */
	/*     M4=1-6 DEFAULT CH4   TO SPECIFIED MODEL ATM.                      LWT 2130 */
	/*                                                                       LWT 2140 */
	/*     M5=1-6 DEFAULT N2O   TO SPECIFIED MODEL ATM.                      LWT 2150 */
	/*                                                                       LWT 2160 */
	/*     M6=1-6 DEFAULT CO    TO SPECIFIED MODEL ATM.                      LWT 2170 */
	/*                                                                       LWT 2180 */
	/*     MDEF=1     USE DEFAULT   PROFILE  FOR CO2,O2,NO,SO2,NO2,NH3,HNO3  LWT 2190 */
	/*                NOT NEEDED WITH MODEL 1 TO 6                           LWT 2200 */
	/*                                                                       LWT 2210 */
	/*                                                                       LWT 2220 */
	/*     IF 'MODEL' 0 OR 'MODEL' 7  THE PROGRAM EXPECTS TO READ            LWT 2230 */
	/*     "USER SUPPLIED" ATMOSPHERIC PROFILES. SET:'IM' = 1 FOR            LWT 2240 */
	/*      FIRST RUN. TO RERUN THE SAME "USER-ATMOSPHERE" FOR A SERIES      LWT 2250 */
	/*      OF CASES SET:'IM' = 0 TO REUSE THE PREVIOUSLY READ DATA.         LWT 2260 */
	/*                                                                       LWT 2270 */
	/*     IM=0    FOR  NORMAL OPERATION OF PROGRAM OR WHEN SUBSEQUENT       LWT 2280 */
	/*                  CALCULATIONS ARE TO BE RUN WITH MODEL =7             LWT 2290 */
	/*        1    WHEN RADIOSONDE DATA ARE TO BE READ INITIALLY.            LWT 2300 */
	/*                                                                       LWT 2310 */
	/*     NOPRT=0 FOR NORMAL OPERATION OF PROGRAM.                          LWT 2320 */
	/*                                                                       LWT 2330 */
	/*           1 TO MINIMIZE PRINTING OF TRANSMITTANCE /OR RADIANCE TABLE  LWT 2340 */
	/*                   AND ATMOSPHERIC PROFILES                            LWT 2350 */
	/*                                                                       LWT 2360 */
	/*                                                                       LWT 2370 */
	/*     TBOUND =BOUNDARY TEMPERATURE ( K),USED IN THE RADIATION MODE      LWT 2380 */
	/*             (IEMSCT = 1 OR 2) FOR SLANT PATHS THAT INTERSECT THE      LWT 2390 */
	/*             EARTH OR TERMINATE AT A GREY BOUNDARY (FOR EXAMPLE        LWT 2400 */
	/*             CLOUD,TARGET).  IF TBOUND IS LEFT BLANK AND THE PATH      LWT 2410 */
	/*             INTERSECTS THE EARTH, THE PROGRAM WILL USE THE            LWT 2420 */
	/*             TEMPERATURE OF THE FIRST ATMOSPHERIC LEVEL AS THE         LWT 2430 */
	/*             BOUNDARY TEMPERATURE.                                     LWT 2440 */
	/*                                                                       LWT 2450 */
	/*      SALB = SURFACE ALBEDO OF THE EARTH AT THE LOCATION               LWT 2460 */
	/*             AND AVERAGE FREQUENCY OF THE CALCULATION (0 TO 1.)        LWT 2470 */
	/*             IF SALB IS LEFT BLANK THE PROGRAM ASSUMES                 LWT 2480 */
	/*             THE SURFACE IS A BLACKBODY.                               LWT 2490 */
	/* ***********************************************************************LWT 2500 */
	/*                                                                       LWT 2510 */
	/*     CARD 2   IHAZE,ISEASN,IVULCN,ICSTL,ICLD,IVSA,VIS,WSS,WHH,RAINRT,  LWT 2520 */
	/*              GNDALT                                                   LWT 2530 */
	/*                          FORMAT(6I5,5F10.3)                           LWT 2540 */
	/*                                                                       LWT 2550 */
	/*     'IHAZE' SELECTS THE TYPE OF EXTINCTION AND A DEFAULT              LWT 2560 */
	/*     METEOROLOGICAL RANGE FOR THE BOUNDARY-LAYER AEROSOL MODEL         LWT 2570 */
	/*     (0 TO 2KM ALTITUDE)                                               LWT 2580 */
	/*     IF 'VIS' IS ALSO SPECIFIED ON CARD 2 IT WILL OVERRIDE THE         LWT 2590 */
	/*     DEFAULT 'IHAZE' VALUE  FOR METEOROLOGICAL RANGE                   LWT 2600 */
	/*                                                                       LWT 2610 */
	/*     IHAZE=0  NO AEROSOL ATTENUATION INCLUDED IN CALCULATION.          LWT 2620 */
	/*          =1  RURAL EXTINCTION, 23-KM VIS.                             LWT 2630 */
	/*          =2  RURAL EXTINCTION, 5-KM VIS.                              LWT 2640 */
	/*          =3  NAVY MARITIME EXTINCTION,SETS OWN VIS.                   LWT 2650 */
	/*          =4  MARITIME EXTINCTION, 23-KM VIS.    (LOWTRAN 5 MODEL)     LWT 2660 */
	/*          =5  URBAN EXTINCTION, 5-KM VIS.                              LWT 2670 */
	/*          =6  TROPOSPHERIC EXTINCTION, 50-KM VIS.                      LWT 2680 */
	/*          =7  USER DEFINED  AEROSOL EXTINCTION COEFFICIENTS            LWT 2690 */
	/*              TRIGGERS READING IREG FOR UP TO 4 REGIONS OF             LWT 2700 */
	/*              USER DEFINED EXTINCTION ABSORPTION AND ASYMMETRY         LWT 2710 */
	/*          =8  FOG1 (ADVECTIVE FOG) EXTINCTION, 0.2-KM VIS.             LWT 2720 */
	/*          =9  FOG2 (RADIATIVE FOG) EXTINCTION, 0.5-KM VIS.             LWT 2730 */
	/*          =10 DESERT EXTINCTION  SETS OWN VISIBILITY FROM WIND SPEED   LWT 2740 */
	/*                                                                       LWT 2750 */
	/*     'ISEASN' SELECTS THE SEASONAL DEPENDENCE OF THE PROFILES          LWT 2760 */
	/*     FOR BOTH THE TROPOSPHERIC (2 TO 10 KM) AND                        LWT 2770 */
	/*     STRATOSPHERIC(10 TO 30 KM) AEROSOLS.                              LWT 2780 */
	/*                                                                       LWT 2790 */
	/*     ISEASN=0 DEFAULTS TO SEASON OF 'MODEL'                            LWT 2800 */
	/*              (MODEL 0,1,2,4,6,7) SUMMER                               LWT 2810 */
	/*              (MODEL 3,5)         WINTER                               LWT 2820 */
	/*           =1 SPRING-SUMMER                                            LWT 2830 */
	/*           =2 FALL - WINTER                                            LWT 2840 */
	/*                                                                       LWT 2850 */
	/*     'IVULCN' SELECTS BOTH THE PROFILE AND EXTINCTION TYPE             LWT 2860 */
	/*     FOR THE STRATOSPHERIC AEROSOLS AND DETERMINES TRANSITION          LWT 2870 */
	/*     PROFILES ABOVE THE STRATOSPHERE TO 100 KM.                        LWT 2880 */
	/*                                                                       LWT 2890 */
	/*     IVULCN=0 DEFAULT TO STRATOSPHERIC BACKGROUND                      LWT 2900 */
	/*           =1 STRATOSPHERIC BACKGROUND                                 LWT 2910 */
	/*           =2 AGED VOLCANIC TYPE/MODERATE VOLCANIC PROFILE             LWT 2920 */
	/*           =3 FRESH VOLCANIC TYPE/HIGH VOLCANIC PROFILE                LWT 2930 */
	/*           =4 AGED VOLCANIC TYPE/HIGH VOLCANIC PROFILE                 LWT 2940 */
	/*           =5 FRESH VOLCANIC TYPE/MODERATE VOLCANIC PROFILE            LWT 2950 */
	/*           =6 BACKGROUND STRATOSPHERIC TYPE/MODERATE VOLCANIC PROFILE  LWT 2960 */
	/*           =7 BACKGROUND STRATOSPHERIC TYPE/HIGH VOLCANIC PROFILE      LWT 2970 */
	/*           =8 FRESH VOLCANIC TYPE/EXTREME VOLCANIC PROFILE             LWT 2980 */
	/*                                                                       LWT 2990 */
	/*     'ICSTL' IS THE AIR MASS CHARACTER(1 TO 10) ONLY USED WITH         LWT 3000 */
	/*     NAVY MARITIME MODEL(IHAZE=3)                                      LWT 3010 */
	/*                                                                       LWT 3020 */
	/*     ICSTL = 1 OPEN OCEAN                                              LWT 3030 */
	/*            .                                                          LWT 3040 */
	/*            .                                                          LWT 3050 */
	/*            .                                                          LWT 3060 */
	/*           10 STRONG CONTINENTAL INFLUENCE                             LWT 3070 */
	/*                                                                       LWT 3080 */
	/*                                                                       LWT 3090 */
	/*     'ICLD' SPECIFIES WHICH OF THE CLOUD MODELS AND THE RAIN RATES     LWT 3100 */
	/*     ARE USED                                                          LWT 3110 */
	/*                                                                       LWT 3120 */
	/*     ICLD  FOR CLOUD AND OR RAIN                                       LWT 3130 */
	/*     ICLD = 0   NO CLOUDS OR RAIN                                      LWT 3140 */
	/*          = 1  CUMULUS CLOUD BASE .66KM TOP 2.7KM                      LWT 3150 */
	/*          = 2  ALTOSTRATUS CLOUD BASE 2.4KM TOP 3.0KM                  LWT 3160 */
	/*          = 3  STRATUS CLOUD BASE .33KM TOP 1.0KM                      LWT 3170 */
	/*          = 4  STRATUS/STRATO CU BASE .66KM TOP 2.0KM                  LWT 3180 */
	/*          = 5  NIMBOSTRATUS CLOUD BASE .16KM TOP .66KM                 LWT 3190 */
	/*          = 6  2.0MM/HR DRIZZLE (MODELED WITH CLOUD  3)                LWT 3200 */
	/*               RAIN  2. MM HR AT 0KM TO .22 MM HR AT 1.5KM             LWT 3210 */
	/*          = 7  5.0MM/HR LIGHT RAIN (MODELED WITH CLOUD  5)             LWT 3220 */
	/*               RAIN  5. MM HR AT 0KM TO .2  MM HR AT 1.5KM             LWT 3230 */
	/*          = 8  12.5MM/HR MODERATE RAIN (MODELED WITH CLOUD  5)         LWT 3240 */
	/*               RAIN 12.5MM HR AT 0KM TO .2  MM HR AT 2.0KM             LWT 3250 */
	/*          = 9  25.0MM/HR HEAVY RAIN (MODELED WITH CLOUD  1)            LWT 3260 */
	/*               RAIN 25. MM HR AT 0KM TO .2  MM HR AT 3.0KM             LWT 3270 */
	/*          =10  75.0MM/HR EXTREME RAIN (MODELED WITH CLOUD  1)          LWT 3280 */
	/*               RAIN 75. MM HR AT 0KM TO .2  MM HR AT 3.5KM             LWT 3290 */
	/*          =11  READ IN USER DEFINED CLOUD EXTINCTION AND ABSORPTION    LWT 3300 */
	/*              USER DEFINED  AEROSOL EXTINCTION COEFFICIENTS            LWT 3310 */
	/*              TRIGGERS READING IREG FOR UP TO 4 REGIONS OF             LWT 3320 */
	/*              USER DEFINED EXTINCTION ABSORPTION AND ASYMMETRY         LWT 3330 */
	/*          =18  STANDARD   CIRRUS MODEL                                 LWT 3340 */
	/*          =19  SUB VISUAL CIRRUS MODEL                                 LWT 3350 */
	/*          =20  NOAA       CIRRUS MODEL  (LOWTRAN 6 MODEL)              LWT 3360 */
	/*                                                                       LWT 3370 */
	/*                                                                       LWT 3380 */
	/*     IVSA DETERMINES THE USE OF THE ARMY VERTICAL STRUCTURE            LWT 3390 */
	/*     ALGORITHM FOR AEROSOLS IN THE BOUNDARY LAYER.                     LWT 3400 */
	/*                                                                       LWT 3410 */
	/*     IVSA=0   NOT USED                                                 LWT 3420 */
	/*         =1   VERTICAL STRUCTURE ALGORITHM                             LWT 3430 */
	/*                                                                       LWT 3440 */
	/*     'VIS'   SPECIFIES THE METEOROLIGICAL RANGE                        LWT 3450 */
	/*     VIS =    METEOROLOGICAL RANGE (KM) (WHEN SPECIFIED,SUPERSEDES     LWT 3460 */
	/*              DEFAULT VALUE SET BY IHAZE)                              LWT 3470 */
	/*                                                                       LWT 3480 */
	/*     'WSS'     SPECIFIES THE CURRENT WIND SPEED                        LWT 3490 */
	/*     WSS =    CURRENT WIND SPEED (M/S).    WITH (IHAZE=3/IHAZE=10)     LWT 3500 */
	/*                                                                       LWT 3510 */
	/*     'WHH'    SPECIFIES THE 24 HOUR AVERAGE WIND SPEED                 LWT 3520 */
	/*     WHH =    24 HOUR AVERAGE WIND SPEED (M/S).  ONLY WITH (IHAZE=3)   LWT 3530 */
	/*                                                                       LWT 3540 */
	/*     'RAINRT' SPECIFIES THE RAIN RATE                                  LWT 3550 */
	/*     RAINRT = RAIN RATE (MM/HR).             DEFAULT VALUE IS ZERO.    LWT 3560 */
	/*     USED  TO TOP OF CLOUD WHEN CLOUD IS PRESENT                       LWT 3570 */
	/*     WHEN NO CLOUDS RAIN RATE USED TO 6KM                              LWT 3580 */
	/*                                                                       LWT 3590 */
	/*     'GNDALT' SPECIFIES THE ALTITUDE OF SURFACE RELATIVE TO SEA LEVEL  LWT 3600 */
	/*     GNDALT = ALTITUDE OF SURFACE RELATIVE TO SEA LEVEL (KM)           LWT 3610 */
	/*              USED TO MODIFY  AEROSOL PROFILES BELOW 6 KM ALTITUDE     LWT 3620 */
	/*                                                                       LWT 3630 */
	/* ***********************************************************************LWT 3640 */
	/*                                                                       LWT 3650 */
	/*     OPTIONAL INPUT CARDS AFTER CARD 2                                 LWT 3660 */
	/*     SELECTED BY PARAMETERS ICLD,IVSA,MODEL,AND IHAZE ON CARDS 2       LWT 3670 */
	/*                                                                       LWT 3680 */
	/*                                                                       LWT 3690 */
	/*     CARD 2A   CTHIK,CALT,CEXT,ISEED     (ICLD=18,19,20)               LWT 3700 */
	/*                          FORMAT(3F10.3,I10)                           LWT 3710 */
	/*                   INPUT CARD FOR CIRRUS ALTITUDE PROFILE              LWT 3720 */
	/*                   SUBROUTINE WHEN ICLD = 18,19,20                     LWT 3730 */
	/*                                                                       LWT 3740 */
	/*     CHTIK    = CIRRUS THICKNESS (KM)                                  LWT 3750 */
	/*                0  USE THICKNESS STATISTICS                            LWT 3760 */
	/*                                                                       LWT 3770 */
	/*     CALT     = CIRRUS BASE ALTITUDE(KM)                               LWT 3780 */
	/*                0 USE DEFAULT DETERMINED BY 'MODEL'                    LWT 3790 */
	/*                                                                       LWT 3800 */
	/*     CEXT     = EXTINCTION COEFFIENT(KM-1) AT 0.55                     LWT 3810 */
	/*                0 USE 0.14 * CTHIK                                     LWT 3820 */
	/*                                                                       LWT 3830 */
	/*     ISEED    = RANDOM NUMBER INITIALIZATION FLAG.                     LWT 3840 */
	/*                0 USE DEFAULT MEAN VALUES FOR CIRRUS                   LWT 3850 */
	/*                .NE. 0 INITIAL VALUE OF SEED FOR                       LWT 3860 */
	/*                RANDOM NUMBER GENERATOR FUNCTION                       LWT 3870 */
	/*                CHANGE SEED VALUE EACH RUN FOR DIFFERENT               LWT 3880 */
	/*                RANDOM NUMBER SEQUENCES.  THIS PROVIDES FOR            LWT 3890 */
	/*                STATISTICAL DETERMINATION OF CIRRUS BASE               LWT 3900 */
	/*                ALTITUDE AND THICKNESS.                                LWT 3910 */
	/*                                                                       LWT 3920 */
	/*   NOTE: RANDOM NUMBERS GENERATION IS SYSTEM DEPENDENT                 LWT 3930 */
	/*                                                                       LWT 3940 */
	/* ***********************************************************************LWT 3950 */
	/*                                                                       LWT 3960 */
	/*     CARD 2B             ZCVSA,ZTVSA,ZINVSA     (IVSA=1)               LWT 3970 */
	/*                          FORMAT(3F10.3)                               LWT 3980 */
	/*               INPUT CARD FOR ARMY VERTICAL STRUCTURE                  LWT 3990 */
	/*               ALGORITHM SUBROUTINE WHEN IVSA=1.                       LWT 4000 */
	/*                                                                       LWT 4010 */
	/*     ZCVSA = CLOUD CEILING HEIGHT (KM)                                 LWT 4020 */
	/*             LT 0 NO CLOUD CEILING                                     LWT 4030 */
	/*             GT 0 KNOWN CLOUD CEILING                                  LWT 4040 */
	/*                0 UNKNOWN CLOUD CEILING HEIGHT                         LWT 4050 */
	/*                  PROGRAM CALCULATES CLOUD HEIGHT                      LWT 4060 */
	/*                                                                       LWT 4070 */
	/*     ZTVSA = THICKNESS OF CLOUD OR FOG (KM),                           LWT 4080 */
	/*               0 DEFAULTS TO 200 METERS                                LWT 4090 */
	/*                                                                       LWT 4100 */
	/*     ZINVSA= HEIGHT OF THE INVERSION (KM)                              LWT 4110 */
	/*                 0 DEFAULTS TO 100 METERS                              LWT 4120 */
	/*             LT  0 NO INVERSION LAYER                                  LWT 4130 */
	/*                                                                       LWT 4140 */
	/* ***********************************************************************LWT 4150 */
	/*                                                                       LWT 4160 */
	/*     CARD 2C  ML,IRD1,IRD2,TITLE   (MODEL=0 / 7,IM=1)                  LWT 4170 */
	/*                          FORMAT(3I5,18A4)                             LWT 4180 */
	/*              ADDITIONAL ATMOSPHERIC MODEL       (MODEL=7)             LWT 4190 */
	/*              NEW MODEL ATMOSPHERE CAN BE INSERTED PROVIDED THE        LWT 4200 */
	/*              PARAMETERS 'MODEL' AND 'IM' ARE SET EQUAL TO 7 AND 1     LWT 4210 */
	/*              RESPECTIVELY ON CARD 1.                                  LWT 4220 */
	/*                                                                       LWT 4230 */
	/*     ML=      NUMBER OF ATMOSPHERIC LEVELS TO BE INSERTED              LWT 4240 */
	/*                   (MAXIMUM OF 34)                                     LWT 4250 */
	/*                                                                       LWT 4260 */
	/*     CARD 2C1 IS READ AUTOMATICALLY FOR MODEL 0 AND 7                  LWT 4270 */
	/*                                                                       LWT 4280 */
	/*     IRD1 CONTROL READING WN2O,WCO ... AND WNH3,WHNO3      CARD        LWT 4290 */
	/*                                                                       LWT 4300 */
	/*     IRD1 = 0     NO READ  (MOLECULAR DENSITIES BY LAYER)              LWT 4310 */
	/*     IRD1 = 1     READ                                                 LWT 4320 */
	/*                                                                       LWT 4330 */
	/*     IRD2  CONTROL READING AHAZE,EQLWCZ,... CARD                       LWT 4340 */
	/*                                                                       LWT 4350 */
	/*     IRD2 = 0     NO READ  (AEROSOL CONTROL BY LAYER)                  LWT 4360 */
	/*     IRD2 = 1     READ                                                 LWT 4370 */
	/*                                                                       LWT 4380 */
	/*     JCHAR  ON CARD 2C1 IS USUALLY USED TO DEFINE MOLECULES 4 TO 12    LWT 4390 */
	/*     IHAZE  ON CARD 2   IS USUALLY USED TO DEFINE AEROSOL PROFILES     LWT 4400 */
	/*     IRD1 = 1 OR IRD2 = 1   SELDOM USED                                LWT 4410 */
	/*                                                                       LWT 4420 */
	/*     TITLE=   IDENTIFICATION OF NEW MODEL ATMOSPHERE                   LWT 4430 */
	/*                                                                       LWT 4440 */
	/*                                                                       LWT 4450 */
	/*     THE FOLLOWING CARDS ARE READ IN SUBROUTINE AERNSM                 LWT 4460 */
	/*                                                                       LWT 4470 */
	/* C------------------------ BEGIN ML LOOP                                LWT 4480 */
	/* C-                                                                     LWT 4490 */
	/* C-   CARD 2C1 ZMDL,P,T,WMOL(1),WMOL(2),WMOL(3),JCHAR                   LWT 4500 */
	/* C-   LAYER VARIABLES        WH,   WCO2,     WO,JCHAR (1 TO 13)         LWT 4510 */
	/* C-                        FORMAT(F10.3,5E10.3,15A1)                    LWT 4520 */
	/* C-                                                                     LWT 4530 */
	/* C-   ZMDL     ALTITUDE OF LAYER (KM)                                   LWT 4540 */
	/* C-   P        PRESSURE AT LAYER                                        LWT 4550 */
	/* C-   T        TEMPERATURE                                              LWT 4560 */
	/* C-   WMOL     READ, INTERPRETED AND MOVED INTO LAYER VARIABLES         LWT 4570 */
	/* C-   WH =     WATER VAPOR                                              LWT 4580 */
	/* C-   WCO2 =   CO2                                                      LWT 4590 */
	/* C-   WO =     OZONE                                                    LWT 4600 */
	/* C-                                                                     LWT 4610 */
	/* C-   JCHAR    FLAGS TO SPECIFY UNITS OR DEFAULTS FOR                   LWT 4620 */
	/* C-   P,T,WH,WCO2,WO,WN2O,WCO,.. AND WNH3,WHNO3                         LWT 4630 */
	/* C-   JCHAR BLANK DEFAULT TO M1,M2,M3,M4,M5,M6,MDEF WHEN AMOUNT ZERO    LWT 4640 */
	/* C-                                                                     LWT 4650 */
	/* C-      PARAMETERS - JCHAR = INPUT KEY                                 LWT 4660 */
	/* C-                                                                     LWT 4670 */
	/* C-   **  ACCEPTS VARIABLE UNITS ON PRESS AND TEMP                      LWT 4680 */
	/* C-                                                                     LWT 4690 */
	/* C-     JCHAR(1)                                                        LWT 4700 */
	/* C-                                                                     LWT 4710 */
	/* C-    " ",A           PRESSURE IN (MB)    OR BLANK                     LWT 4720 */
	/* C-        B              "     "  (ATM)                                LWT 4730 */
	/* C-        C              "     "  (TORR)                               LWT 4740 */
	/* C-       1-6          DEFAULT TO SPECIFIED MODEL ATMOSPHERE            LWT 4750 */
	/* C-                                                                     LWT 4760 */
	/* C-     JCHAR(2)                                                        LWT 4770 */
	/* C-    " ",A           AMBIENT TEMPERATURE IN DEG(K)  OR BLANK          LWT 4780 */
	/* C-        B              "         "       "  " (C)                    LWT 4790 */
	/* C-       1-6          DEFAULT TO SPECIFIED MODEL ATMOSPHERE            LWT 4800 */
	/* C-                                                                     LWT 4810 */
	/* C-   ****************************************************************  LWT 4820 */
	/* C-   FOR MOLECULAR SPECIES ONLY                                        LWT 4830 */
	/* C-                                                                     LWT 4840 */
	/* C-     JCHAR             JCHAR(3-13)                                   LWT 4850 */
	/* C-                                                                     LWT 4860 */
	/* C-   " ",A            VOLUME MIXING RATIO (PPMV)                       LWT 4870 */
	/* C-       B            NUMBER DENSITY (CM-3)                            LWT 4880 */
	/* C-       C            MASS MIXING RATIO (GM(K)/KG(AIR))                LWT 4890 */
	/* C-       D            MASS DENSITY (GM M-3)                            LWT 4900 */
	/* C-       E            PARTIAL PRESSURE (MB)                            LWT 4910 */
	/* C-       F            DEW POINT TEMP (TD IN T(K)) - H2O ONLY           LWT 4920 */
	/* C-       G             "    "     "  (TD IN T(C)) - H2O ONLY           LWT 4930 */
	/* C-       H            RELATIVE HUMIDITY (RH IN PERCENT) - H2O ONLY (3) LWT 4940 */
	/* C-       I            AVAILABLE FOR USER DEFINITION                    LWT 4950 */
	/* C-      1-6           DEFAULT TO SPECIFIED MODEL ATMOSPHERE            LWT 4960 */
	/* C-                                                                     LWT 4970 */
	/* C-   ****************************************************************  LWT 4980 */
	/* C-                                                                     LWT 4990 */
	/* C-   CARD 2C2   (WMOL(J),J=4,11)                                       LWT 5000 */
	/* C-   VARIABLES  WN2O,WCO,WCH4,WO2,WNO,WSO2,WNO2,WNH3                   LWT 5010 */
	/* C-                        FORMAT(8E10.3)                               LWT 5020 */
	/* C-                                                                     LWT 5030 */
	/* C-   CARD 2C2   WMOL(12)             (CONT)                            LWT 5040 */
	/* C-   VARIABLE   WHNO3                                                  LWT 5050 */
	/* C-                        FORMAT(8E10.3)                               LWT 5060 */
	/* C-                                                                     LWT 5070 */
	/* C-                                                                     LWT 5080 */
	/* C-   WMOL     READ, INTERPRETED AND MOVED INTO LAYER VARIABLES         LWT 5090 */
	/* C-   WN2O =   N2O                                                      LWT 5100 */
	/* C-   WCO  =   CO                                                       LWT 5110 */
	/* C-   WCH4 =   CH4                                                      LWT 5120 */
	/* C-   WO2  =   O2                                                       LWT 5130 */
	/* C-   WNO  =   NO                                                       LWT 5140 */
	/* C-   WSO2 =   SO2                                                      LWT 5150 */
	/* C-   WNO2 =   NO2                                                      LWT 5160 */
	/* C-   WNH3 =   NH3                                                      LWT 5170 */
	/* C-   WHNO3 =  HNO3                                                     LWT 5180 */
	/* C-                                                                     LWT 5190 */
	/* C-   ****************************************************************  LWT 5200 */
	/* C-                                                                     LWT 5210 */
	/* C- CARD 2C3     AHAZE,EQLWCZ,RRATZ,IHA1,ICLD1,IVUL1,ISEA1,ICHR         LWT 5220 */
	/* C-                        FORMAT(10X,3F10.3,5I5)                       LWT 5230 */
	/* C-                                                                     LWT 5240 */
	/* C-  'AHAZE' AEROSOL SCALING FACTOR (EQUAL TO THE VISIBLE [0.55UM]      LWT 5250 */
	/* C-          EXTINCTION COEFFICIENT AT ALTZ)                            LWT 5260 */
	/* C-                                                                     LWT 5270 */
	/* C-          [NOTE ** ONE OF AHAZE OR EQLWCZ IS ALLOWED ]               LWT 5280 */
	/* C-                                                                     LWT 5290 */
	/* C-  'EQLWCZ' EQUIVALENT LIQUID WATER CONTENT ( GM/M3) AT ALT Z         LWT 5300 */
	/* C-           FOR THE AEROSOL, CLOUD OR FOG MODELS                      LWT 5310 */
	/* C-                                                                     LWT 5320 */
	/* C-   RRATZ=RAIN RATE (MM/HR) AT ALT Z                                  LWT 5330 */
	/* C-                                                                     LWT 5340 */
	/* C-   'IHA1' AEROSOL EXTINCTION AND METEOROLOGICAL RANGE CONTROL FOR    LWT 5350 */
	/* C-          THE ALTITUDE, Z                                            LWT 5360 */
	/* C-                                                                     LWT 5370 */
	/* C-   'ICLD1' CLOUD EXTINCTION CONTROL FOR THE ALTITUDE, Z              LWT 5380 */
	/* C-                                                                     LWT 5390 */
	/* C-   WHEN USING 'ICLD1' IT IS NECESSARY TO SET 'ICLD' (NON ZERO)       LWT 5400 */
	/* C-                                                                     LWT 5410 */
	/* C-   'IVUL1' STRATOSPHERIC AEROSOL PROFILE AND EXTINCTION CONTROL FOR  LWT 5420 */
	/* C-   THE ALTITUDE Z                                                    LWT 5430 */
	/* C-                                                                     LWT 5440 */
	/* C-   ONLY ONE OF 'IHA1','ICLD1' OR 'IVUL1' IS ALLOWED                  LWT 5450 */
	/* C-   IF 'IHA1' NE 0  THEN OTHERS IGNORED                               LWT 5460 */
	/* C-   IF 'IHA1' EQ 0 AND 'ICLD1' NE 0 THEN USE 'ICLD1'                  LWT 5470 */
	/* C-                                                                     LWT 5480 */
	/* C-   IF 'AHAZE' AND 'EQLWCZ' ARE BOTH ZERO  DEFAULT PROFILE LOADED     LWT 5490 */
	/* C-      FROM 'IHAZ1','ICLD1','IVUL1'                                   LWT 5500 */
	/* C-                                                                     LWT 5510 */
	/* C-   'ISEA1'  AEROSOL SEASON CONTROL FOR THE ALTITUDE,Z                LWT 5520 */
	/* C-                                                                     LWT 5530 */
	/* C-   'ICHR '  CHANGE PROFILE REGION  AT ALTITUDE Z                     LWT 5540 */
	/* C-            USED WHEN IHA1 IS 7 IN TWO ADJACENT ALTITUDE REGIMES     LWT 5550 */
	/* C-                                                                     LWT 5560 */
	/* C------------- END ML LOOP                                             LWT 5570 */
	/* ***********************************************************************LWT 5580 */
	/*                                                                       LWT 5590 */
	/*   IHAZE = 7 OR ICLD = 11 INPUT                                        LWT 5600 */
	/*                                                                       LWT 5610 */
	/*   CARD 2D  (IREG(II),II=1,4)                                          LWT 5620 */
	/*                        FORMAT(4I5)                                    LWT 5630 */
	/*                                                                       LWT 5640 */
	/*             'IREG' SPECIFIES WHICH OF THE FOUR AEROSOL REGIONS        LWT 5650 */
	/*              A USER DEFINED AEROSOL MODEL IS USED (IHAZE=7/ICLD=11)   LWT 5660 */
	/*                                                                       LWT 5670 */
	/*             [NOTE   REGIONS DEFAULT TO                                LWT 5680 */
	/*             0-2 ,3-10,11-30,35-100 KM                                 LWT 5690 */
	/*             AND CAN BE OVERRIDDEN WITH 'IHA1' SETTINGS IN MODEL 7]    LWT 5700 */
	/*                                                                       LWT 5710 */
	/*             IREG = 0  USE DEFAULT VALUES FOR THIS REGION              LWT 5720 */
	/*                                                                       LWT 5730 */
	/*             IREG = 1  READ EXTINCTION ABSORPTION ASYMMETRY            LWT 5740 */
	/*             FOR A REGION                                              LWT 5750 */
	/*                                                                       LWT 5760 */
	/*   CARD 2D1 AWCCON,TITLE                                               LWT 5770 */
	/*                        FORMAT(E10.3,18A4)                             LWT 5780 */
	/*                                                                       LWT 5790 */
	/*            'AWWCON' EQUIVALENT LIQUID WATER CONTENT(GM/M3)            LWT 5800 */
	/*             FOR A REGION                                              LWT 5810 */
	/*                                                                       LWT 5820 */
	/*             'TITLE' FOR A AEROSOL REGION                              LWT 5830 */
	/*                                                                       LWT 5840 */
	/*    CARD 2D2 (VX(I),EXTC(N,I),ABSC(N,I),ASYM(N,I),I=1,47)              LWT 5850 */
	/*                   FORMAT(4(F6.2,2F7.5,F6.4))                          LWT 5860 */
	/*                                                                       LWT 5870 */
	/*             WHERE  N = IREG(II)   FOR UP TO 4 ALTITUDE REGIONS        LWT 5880 */
	/*             USER DEFINED AEROSOL  OR CLOUD EXTINCTION AND ABSORPTION  LWT 5890 */
	/*              COEFFICIENTS WHEN IHAZE = 7 OR ICLD = 11                 LWT 5900 */
	/*                                                                       LWT 5910 */
	/*     VX(I)    = WAVELENGTH OF AEROSOL COEFFICIENT                      LWT 5920 */
	/*                   (NOT USED BY PROGRAM BUT CORRESPONDING TO           LWT 5930 */
	/*                   WAVELENGTHS DEFINED IN ARRAY VX2                    LWT 5940 */
	/*                   IN SUBROUTINE EXTDTA)                               LWT 5950 */
	/*                                                                       LWT 5960 */
	/*     EXTC(N,I) = AEROSOL EXTINCTION COEFFICIENT                        LWT 5970 */
	/*     ABSC(N,I) = AEROSOL ABSORPTION COEFFICIENT                        LWT 5980 */
	/*     ASYM(N,I) = AEROSOL ASYMMETRY PARAMETER                           LWT 5990 */
	/*     WHERE  N = IREG(II)   FOR UP TO 4 ALTITUDE REGIONS                LWT 6000 */
	/*                                                                       LWT 6010 */
	/* ***********************************************************************LWT 6020 */
	/*                                                                       LWT 6030 */
	/*     CARD 3    H1,H2,ANGLE,RANGE,BETA,RO,LEN    FORMAT(6F10.3,I5)      LWT 6040 */
	/*            USED TO DEFINE THE GEOMETRICAL PATH PARAMETERS FOR A GIVEN LWT 6050 */
	/*            PROBLEM.                                                   LWT 6060 */
	/*                                                                       LWT 6070 */
	/*     OR IF IEMSCT=3 ; CARD 3 H1,H2,ANGLE,IDAY,RO,ISOURC,ANGLEM         LWT 6080 */
	/*                                                                       LWT 6090 */
	/*     H1  =  INITIAL ALTITUDE(KM)                                       LWT 6100 */
	/*     H2  =  FINAL ALTITUDE(KM)                                         LWT 6110 */
	/*                                                                       LWT 6120 */
	/*                   IN THE RADIANCE MODE OF THE PROGRAM EXECUTION       LWT 6130 */
	/*            H1, THE INITIAL ALTITUDE,ALWAYS DEFINES THE POSITION OF    LWT 6140 */
	/*            THE OBSERVER (OR SENSOR).                                  LWT 6150 */
	/*                                                                       LWT 6160 */
	/*     ANGLE =INITIAL ZENITH ANGLE (DEGREES) AS MEASURED FROM H1         LWT 6170 */
	/*     [NOTE: ANGLE = 0 LOOKS STRAIGHT UP.                               LWT 6180 */
	/*            ANGLE IS DEFINED  FROM 0 TO 180 DEGREES ]                  LWT 6190 */
	/*                                                                       LWT 6200 */
	/*     RANGE =PATH LENGTH (KM)                                           LWT 6210 */
	/*     BETA  =EARTH CENTER ANGLE SUBTENDED BY H1 AND H2 (DEGREES)        LWT 6220 */
	/*                                                                       LWT 6230 */
	/*     RO =   RADIUS OF THE EARTH (KM) AT THE PARTICULAR GEOGRAPHICAL    LWT 6240 */
	/*            LOCATION AT WHICH THE CALCULATION IS TO BE PERFORMED.      LWT 6250 */
	/*              IF RO BLANK PROGRAM USES RADIUS FOR APPROPRIATE MODEL    LWT 6260 */
	/*              ATMOSPHERE. (MODEL 0 OR 7 DEFAULT = 6371.23 KM)          LWT 6270 */
	/*                                                                       LWT 6280 */
	/*     LEN =0 FOR NORMAL OPERATION OF PROGRAM                            LWT 6290 */
	/*         =1 LONG PATH THROUGH THE TANGENT HEIGHT                       LWT 6300 */
	/*                                                                       LWT 6310 */
	/*            IT IS NOT NECESSARY TO SPECIFY EVERY QUANTITY GIVEN ABOVE  LWT 6320 */
	/*            ONLY THOSE THAT ADEQUATELY DESCRIBE THE PROBLEM ACCORDING  LWT 6330 */
	/*            TO THE PARAMETER ITYPE                                     LWT 6340 */
	/*                                                                       LWT 6350 */
	/*            ITYPE=1 READ H1,RANGE                                      LWT 6360 */
	/*                 =2 READ H1,H2,ANGLE   OR H1,H2,RANGE   OR H1,H2,BETA  LWT 6370 */
	/*                    OR H1,ANGLE,RANGE                                  LWT 6380 */
	/*                 =3 READ H1,ANGLE OR H1,H2                             LWT 6390 */
	/*                    [NOTE: H2 IS INTERPRETED AS HMIN FOR THIS CASE]    LWT 6400 */
	/*                                                                       LWT 6410 */
	/* --------------                                                         LWT 6420 */
	/*     CARD 3    OPTION  IEMSCT = 3                                      LWT 6430 */
	/*    'IDAY'     DAY OF THE YEAR, I.E. FROM 1 TO 365  (IEMSCT = 3)       LWT 6440 */
	/*                                                                       LWT 6450 */
	/*     ISOURC=0  EXTRATERRESTRIAL SOURCE IS THE SUN                      LWT 6460 */
	/*           =1  EXTRATERRESTRIAL SOURCE IS THE MOON                     LWT 6470 */
	/*                                                                       LWT 6480 */
	/*     ANGLEM=PHASE ANGLE OF THE MOON, I.E. THE ANGLE FORMED             LWT 6490 */
	/*            BY THE SUN, MOON AND EARTH (REQUIRED IF ISOURC=1)          LWT 6500 */
	/*                                                                       LWT 6510 */
	/* ***********************************************************************LWT 6520 */
	/*                                                                       LWT 6530 */
	/*     CARD 3A1   IPARM,IPH,IDAY,ISOURC           (IEMSCT=2)             LWT 6540 */
	/*                          FORMAT(4I5)                                  LWT 6550 */
	/*              INPUT CARD FOR SOLAR/LUNAR SCATTERED RADIATION WHEN      LWT 6560 */
	/*              IEMSCT = 2                                               LWT 6570 */
	/*                                                                       LWT 6580 */
	/*              IPARM =0,1,2 AND CONTROLS THE METHOD OF SPECIFYING THE   LWT 6590 */
	/*              SOLAR/LUNAR GEOMETRY ON CARD 3A2.                        LWT 6600 */
	/*                     (SEE DEFINITION BELOW FOR CARD 3A2)               LWT 6610 */
	/*                                                                       LWT 6620 */
	/*              IPH DETERMINES THE TYPE OF PHASE FUNCTION USED IN THE    LWT 6630 */
	/*               CALCULATION                                             LWT 6640 */
	/*                                                                       LWT 6650 */
	/*     IPH=0     HENYEY-GREENSTEIN AEROSOL PHASE FUNCTION                LWT 6660 */
	/*        =1     USER SUPPLIED AEROSOL PHASE FUNCTION (SEE CARD 3B)      LWT 6670 */
	/*        =2     MIE GENERATED DATA BASE OF AEROSOL PHASE FUNCTIONS FOR  LWT 6680 */
	/*               THE LOWTRAN MODELS.                                     LWT 6690 */
	/*                                                                       LWT 6700 */
	/*     IDAY=     DAY OF THE YEAR, I.E. FROM 1 TO 365   (REQUIRED)        LWT 6710 */
	/*                                                                       LWT 6720 */
	/*     ISOURC=0  EXTRATERRESTRIAL SOURCE IS THE SUN                      LWT 6730 */
	/*           =1  EXTRATERRESTRIAL SOURCE IS THE MOON                     LWT 6740 */
	/*                                                                       LWT 6750 */
	/* ***********************************************************************LWT 6760 */
	/*                                                                       LWT 6770 */
	/*     CARD 3A2  PARM1,PARM2,PARM3,PARM4,TIME,PSIPO,ANGLEM,G             LWT 6780 */
	/*                          FORMAT(8F10.3)                (IEMSCT=2)     LWT 6790 */
	/*              INPUT CARD FOR SOLAR/LUNAR SCATTERED RADIATION WHEN      LWT 6800 */
	/*              IEMSCT = 2                                               LWT 6810 */
	/*              DEFINITIONS OF PARM1,PARM2,PARM3,PARM4 DETERMINED BY     LWT 6820 */
	/*              VALUE OF IPARM ON CARD 3A1.                              LWT 6830 */
	/*                                                                       LWT 6840 */
	/*                       FOR IPARM=0                                     LWT 6850 */
	/*                                                                       LWT 6860 */
	/*     PARM1= OBSERVER LATITUDE (-90 TO +90)                             LWT 6870 */
	/*          NOTE- IF ABS(PARM1) IS GREATER THAN 89.5 THE OBSERVER IS     LWT 6880 */
	/*          ASSUMED TO BE AT EITHER THE NORTH OR THE SOUTH POLE.  IN     LWT 6890 */
	/*          THAT CASE THE PATH AZIMUTH IS UNDEFINED.  THE DIRECTION OF   LWT 6900 */
	/*          LINE OF SIGHT MUST BE SPECIFIED AS THE LONGITUDE ALONG WHICH LWT 6910 */
	/*          THE PATH LIES. THIS QUANTITY RATHER THAN THE USUAL AZIMUTH   LWT 6920 */
	/*          IS READ IN                                                   LWT 6930 */
	/*     PARM2= OBSERVER LONGITUDE (0 TO 360)                              LWT 6940 */
	/*     PARM3= SOURCE (SUN OR MOON) LATITUDE                              LWT 6950 */
	/*     PARM4= SOURCE (SUN OR MOON) LONGITUDE                             LWT 6960 */
	/*                                                                       LWT 6970 */
	/*                       FOR IPARM=1                                     LWT 6980 */
	/*        (IDAY AND TIME MUST BE SPECIFIED,CANNOT BE USED WITH ISOURC=1) LWT 6990 */
	/*                                                                       LWT 7000 */
	/*                                                                       LWT 7010 */
	/*     PARM1= OBSERVER LATITUDE (-90 TO +90)                             LWT 7020 */
	/*     PARM2= OBSERVER LONGITUDE (0 TO 360)                              LWT 7030 */
	/*             PARM3,PARM4 ARE NOT REQUIRED                              LWT 7040 */
	/*                                                                       LWT 7050 */
	/*     [NOTE: THAT THE CALCULATED APPARENT SOLAR ZENITH                  LWT 7060 */
	/*            ANGLE IS THE ZENITH ANGLE AT H1 OF THE REFRACTED           LWT 7070 */
	/*            PATH TO THE SUN AND IS LESS THAN THE ASTRONOMICAL          LWT 7080 */
	/*            SOLAR ZENITH ANGLE.  THE DIFFERENCE BETWEEN THE            LWT 7090 */
	/*            TWO ANGLES IS NEGLIGIBLE FOR ANGLES LESS THAN 80           LWT 7100 */
	/*            DEGREES.]                                                  LWT 7110 */
	/*                                                                       LWT 7120 */
	/*                        FOR IPARM=2                                    LWT 7130 */
	/*                                                                       LWT 7140 */
	/*     PARM1= AZIMUTHAL ANGLE BETWEEN THE OBSERVER'S LINE OF SIGHT       LWT 7150 */
	/*            AND THE OBSERVER-TO-SUN PATH, MEASURED FROM THE LINE       LWT 7160 */
	/*            OF SIGHT, POSITIVE EAST OF NORTH, BETWEEN -180 AND 180     LWT 7170 */
	/*     PARM2= THE SUN'S ZENITH ANGLE                                     LWT 7180 */
	/*                                                                       LWT 7190 */
	/*              PARM3,PARM4 ARE NOT REQUIRED                             LWT 7200 */
	/*                                                                       LWT 7210 */
	/*                                                                       LWT 7220 */
	/*              REMAINING CONTROL PARAMETERS                             LWT 7230 */
	/*                                                                       LWT 7240 */
	/*     TIME=  GREENWICH TIME IN DECIMAL HOURS, I.E. 8:45 AM IS 8.75,     LWT 7250 */
	/*            5:20 PM IS 17.33 ETC. (USED WITH IPARM = 1)                LWT 7260 */
	/*                                                                       LWT 7270 */
	/*     PSIPO= PATH AZIMUTH (DEGREES EAST OF NORTH, I.E. DUE NORTH IS 0.0 LWT 7280 */
	/*            DUE EAST IS 90.0 ETC.  (USED WITH IPARM = 0 OR 1)          LWT 7290 */
	/*                                                                       LWT 7300 */
	/*     ANGLEM=PHASE ANGLE OF THE MOON, I.E. THE ANGLE FORMED             LWT 7310 */
	/*            BY THE SUN, MOON AND EARTH (REQUIRED IF ISOURC=1)          LWT 7320 */
	/*                                                                       LWT 7330 */
	/*     G=     ASYMMETRY FACTOR FOR USE WITH HENYEY-GREENSTEIN            LWT 7340 */
	/*            PHASE FUNCTION (USED WITH IPH = 0)                         LWT 7350 */
	/*                                                                       LWT 7360 */
	/* ***********************************************************************LWT 7370 */
	/*     CARD 3B1 NANGLS          (IPH=1)                                  LWT 7380 */
	/*                   FORMAT(I5)                                          LWT 7390 */
	/*                                                                       LWT 7400 */
	/*              INPUT CARD FOR USER DEFINED PHASE FUNCTIONS WHEN IPH=1.  LWT 7410 */
	/*                                                                       LWT 7420 */
	/*     NANGLS=  NUMBER OF ANGLES FOR THE USER DEFINED PHASE              LWT 7430 */
	/*              FUNCTIONS(MAXIMUM OF 50)                                 LWT 7440 */
	/*                                                                       LWT 7450 */
	/* ***********************************************************************LWT 7460 */
	/*                                                                       LWT 7470 */
	/*     CARD 3B2(1 TO NANGLS)    (IPH=1)                                  LWT 7480 */
	/*             (ANGF(I),F(1,I),F(2,I),F(3,I),F(4,I),I=1,NANGLS)          LWT 7490 */
	/*                   FORMAT(5E10.3)                                      LWT 7500 */
	/*              INPUT CARD FOR USER DEFINED PHASE FUNCTION WHEN IPH=1.   LWT 7510 */
	/*              FOR AVERAGE FREQUENCY OF CALCULATION                     LWT 7520 */
	/*                                                                       LWT 7530 */
	/*     ANGF(I)= PHASE ANGLE IN DECIMAL DEGREES                           LWT 7540 */
	/*                   (0.0 TO 180.0)                                      LWT 7550 */
	/*                                                                       LWT 7560 */
	/*     F(1,I)=  USER DEFINED PHASE FUNCTION AT ANGF(I)                   LWT 7570 */
	/*              BOUNDARY LAYER DEFAULTS TO (0 TO 2KM))                   LWT 7580 */
	/*                                                                       LWT 7590 */
	/*     F(2,I)=  USER DEFINED PHASE FUNCTION AT ANGF(I)                   LWT 7600 */
	/*              TROPOSPHERE DEFAULTS TO (2 TO 10 KM)                     LWT 7610 */
	/*                                                                       LWT 7620 */
	/*     F(3,I)=  USER DEFINED PHASE FUNCTION AT ANGF(I)                   LWT 7630 */
	/*              STRATOSPHERE DEFAULTS TO (10 TO 30 KM)                   LWT 7640 */
	/*                                                                       LWT 7650 */
	/*     F(4,I)=  USER DEFINED PHASE FUNCTION AT ANGF(I)                   LWT 7660 */
	/*              MESOSPHERE DEFAULTS TO (30 TO 100 KM)                    LWT 7670 */
	/*                                                                       LWT 7680 */
	/* ***********************************************************************LWT 7690 */
	/*                                                                       LWT 7700 */
	/*     CARD 4    V1, V2, DV                       FORMAT(3F10.3)         LWT 7710 */
	/*                                                                       LWT 7720 */
	/*              THE SPECTRAL RANGE OVER WHICH DATA ARE REQUIRED AND      LWT 7730 */
	/*              THE SPECTRAL INCREMENTS AT WHICH THE DATA ARE TO BE      LWT 7740 */
	/*              CALCULATED  IS DETERMINED BY CARD 4.                     LWT 7750 */
	/*                                                                       LWT 7760 */
	/*     V1 =     INITIAL FREQUENCY (WAVENUMBER CM-1 )                     LWT 7770 */
	/*     V2 =     FINAL FREQUENCY(WAVENUMBER CM-1 )                        LWT 7780 */
	/*     DV =     FREQUENCY INCREMENT (OR STEP SIZE) (CM-1)                LWT 7790 */
	/*              NOTE: DV MUST BE A MULTIPLE OF 5 CM-1                    LWT 7800 */
	/*              ANY STEP SIZE .GT. 5 CM-1 WILL UNDERSAMPLE THE RESULTS   LWT 7810 */
	/*                                                                       LWT 7820 */
	/*              SCANNING FUNCTION IS AVAILABLE TO PROPERLY HANDLE DATA   LWT 7830 */
	/*              WITH LOWER RESOLUTION THAN 20CM-1 LOWTRAN 7              LWT 7840 */
	/*                                                                       LWT 7850 */
	/* ***********************************************************************LWT 7860 */
	/*                                                                       LWT 7870 */
	/*     CARD 5    IRPT                             FORMAT(I5)             LWT 7880 */
	/*     IRPT=0  TO END PROGRAM                                            LWT 7890 */
	/*         =1  READ ALL DATA CARDS (1,2,3,4,5)                           LWT 7900 */
	/*         =2  NOT USED  (WILL STOP PROGRAM)                             LWT 7910 */
	/*         =3  READ CARD 3   THE GEOMETRY CARD AND CARD 5                LWT 7920 */
	/*         =4  READ CARD 4 TO CHANGE FREQUENCY AND CARD 5                LWT 7930 */
	/*     GT 4 OR IRPT=2 WILL CAUSE PROGRAM TO STOP                         LWT 7940 */
	/*                                                                       LWT 7950 */
	/*     IRPT GE 1 USED FOR MULTIPLE RUNS OF LOWTRAN                       LWT 7960 */
	/*     WARNING IRPT 3 CANNOT BE USED WHEN RUNNING MULTIPLE SCATTERING    LWT 7970 */
	/*     CASES WITH SOLAR SCATTERING                                       LWT 7980 */
	/*                                                                       LWT 7990 */
	/*     REFERENCES                                                        LWT 8000 */
	/*                                                                       LWT 8010 */
	/*       (1980) ATMOSPHERIC TRANSMITTANCE/RADIANCE- COMPUTER CODE        LWT 8020 */
	/*       LOWTRAN 5 AFGL-TR-80-0067                                       LWT 8030 */
	/*       KNEIZYS, F. X.,SHETTLE, E. P. ,GALLERY, W. O.,CHETWYND, J. H.,  LWT 8040 */
	/*       ABREU, L. W., SELBY, J. E. A., FENN, R. W. ,MCCLATCHEY R. A.    LWT 8050 */
	/*                                                                       LWT 8060 */
	/*       (1983) ATMOSPHERIC TRANSMITTANCE/RADIANCE- COMPUTER CODE        LWT 8070 */
	/*       LOWTRAN 6  AFGL TR 83 0187                                      LWT 8080 */
	/*       KNEIZYS, F. X.,SHETTLE, E. P. ,GALLERY, W. O.,CHETWYND, J. H.,  LWT 8090 */
	/*       ABREU, L. W., SELBY, J. E. A., CLOUGH, S. A., FENN, R. W.       LWT 8100 */
	/*                                                                       LWT 8110 */
	/*       (1988) ATMOSPHERIC TRANSMITTANCE/RADIANCE- COMPUTER CODE        LWT 8120 */
	/*       LOWTRAN 7 AFGL-TR-88-XXXX                                       LWT 8130 */
	/*       KNEIZYS, F. X.,SHETTLE, E. P. ,ANDERSON G. P.,ABREU ,L. W.      LWT 8140 */
	/*       CHETWYND, J H,SELBY, J. E. A. ,CLOUGH, S. A.,GALLERY, W. O      LWT 8150 */
	/*                                                                       LWT 8160 */
	/*       (1988) LOWTRAN 7 COMPUTER CODE : USER'S MANUAL AFGL-TR-88-XXXX  LWT 8170 */
	/*       KNEIZYS, F. X.,SHETTLE, E. P. ,ANDERSON G. P.,ABREU ,L. W.      LWT 8180 */
	/*       CHETWYND, J H,SELBY, J. E. A. ,CLOUGH, S. A.,GALLERY, W. O      LWT 8190 */
	/*                                                                       LWT 8200 */
	/*       MOLECULAR TRANSMISSION BAND MODELS FOR LOWTRAN AFGL-TR-86-0272  LWT 8210 */
	/*       PIERLUISSI, J. H., MARAGOUDAKIS, C. E.                          LWT 8220 */
	/*                                                                       LWT 8230 */
	/*       MULTIPLE SCATTERING TREATMENT FOR USE IN                        LWT 8240 */
	/*       THE LOWTRAN AND FASCODE MODELS  AFGL-TR-86-0073                 LWT 8250 */
	/*       ISAACS, R. G., WANG, W. C., WORSHAM, R. D.,GOLDENBERG S.        LWT 8260 */
	/*                                                                       LWT 8270 */
	/*       AFGL ATMOSPHERIC CONSTITUENT PROFILES (0 TO 120KM)              LWT 8280 */
	/*                                              AFGL-TR-86-0110          LWT 8290 */
	/*       ANDERSON, G. P., CLOUGH, S. A., KNEIZYS, F. X.,                 LWT 8300 */
	/*       CHETWYND, J. H., SHETTLE, E. P.                                 LWT 8310 */
	/*                                                                       LWT 8320 */
	/*       PROGRAM FOR ATMOSPHERIC TRANSMITTANCE RADIANCE/CALCULATIONS     LWT 8330 */
	/*       FSCATM                                  AFGL-TR-83-0065         LWT 8340 */
	/*       GALLERY, W. O., KNEIZYS, F. X., AND CLOUGH, S. A.               LWT 8350 */
	/*                                                                       LWT 8360 */
	/*       AFGL HANDBOOK OF GEOPHYSICS AND THE SPACE ENVIRONMENT           LWT 8370 */
	/*       EDITOR, A. S. JURSA  CHAPTER 18 1985                            LWT 8380 */
	/*                                                                       LWT 8390 */
	/*       MODELS OF THE AEROSOLS OF THE LOWER ATMOSPHERE AND THE EFFECTS  LWT 8400 */
	/*       OF HUMIDITY VARIATIONS ON THEIR OPTICAL PROPERTIES              LWT 8410 */
	/*       SHETTLE, E.P. AND FENN, R. W.            AFGL-TR-79-0214        LWT 8420 */
	/*                                                                       LWT 8430 */
	/*       OPTICAL PROPAGATION IN THE ATMOSPHERE    AGARD-CP-183  1975     LWT 8440 */
	/*       SHETTLE, E. P., AND FENN, R. W.          NTIS (NO AD-A028-615)  LWT 8450 */
	/*                                                                       LWT 8460 */
	/*                                                                       LWT 8470 */
	/*       ATMOSPHERIC ATTENUATION OF MILLIMETER AND SUBMILLIMETER         LWT 8480 */
	/*       WAVES:  MODEL AND COMPUTER CODE          AFGL-TR-79-0253        LWT 8490 */
	/*       FALCONE,V. J. JR.,ABREU,L. W. AND SHETTLE, E. P.                LWT 8500 */
	/*                                                                       LWT 8510 */
	/*       LOWTRAN  PLUS ULTRAVIOLET O2 ABSORPTION                         LWT 8520 */
	/*                                                                       LWT 8530 */
	/*       REFERENCES- JOHNSTON, ET AL, J GEOPHYS RES, 89,11661-11665,1984.LWT 8540 */
	/*                                                                       LWT 8550 */
	/*       FREQUENCY RANGE: 50000-36000CM-1 FOR HERZBERG CALCULATION       LWT 8560 */
	/*                                                                       LWT 8570 */
	/*       THE SCHUMANN-RUNGE BANDS (PARTICULARLY THE 1,0 AND 0,0) ARE NOT LWT 8580 */
	/*       INCLUDED IN THE CALCULATIONS (50000 AND 49400 CM-1).            LWT 8590 */
	/*       THE HERZBERG BANDS ARE APPROXIMATED BY AN EXTRAPOLATION OF THE  LWT 8600 */
	/*       HERZBERG CONTINUUM (41322-36000 CM-1).                          LWT 8610 */
	/*                                                                       LWT 8620 */
	/* ***********************************************************************LWT 8630 */
	/* *****HDATE AND HTIME CARRY THE DATA AND TIME AND MUST BE DOUBLE        LWT 8920 */
	/* *****PRECISION ON A 32 BIT WORD COMPUTER                               LWT 8930 */
	/* @    DOUBLE PRECISION HDATE,HTIME                                      LWT 8940 */
	/* *****IRD, IPR, AND IPU ARE UNIT NUMBERS FOR INPUT, OUTPUT, AND         LWT 8970 */
	/* *****  IPR1 = OUTPUT OF MOLECULAR TRANSMITTANCE                        LWT 8980 */

	ifil_1.ird = 5;	  // 5
	ifil_1.ipr = 6;	  // 6
	ifil_1.ipu = 7;	  // 7
	ifil_1.ipr1 = 18; // 8

	// GP remove card read
	// o__1.oerr = 0;
	// o__1.ounit = ifil_1.ird;
	// o__1.ofnmlen = 5;
	// o__1.ofnm = "TAPE5";
	// o__1.orl = 0;
	// o__1.osta = "OLD";
	// o__1.oacc = 0;
	// o__1.ofm = 0;
	// o__1.oblnk = 0;
	// o__1.oerr = 0;
	// o__1.ounit = ifil_1.ipr;
	// o__1.ofnmlen = 5;
	// o__1.ofnm = "TAPE6";
	// o__1.orl = 0;
	// o__1.osta = "UNKNOWN";
	// o__1.oacc = 0;
	// o__1.ofm = 0;
	// o__1.oblnk = 0;
	// f_open(&o__1);
	// o__1.oerr = 0;
	// o__1.ounit = ifil_1.ipu;
	// o__1.ofnmlen = 5;
	// o__1.ofnm = "TAPE7";
	// o__1.orl = 0;
	// o__1.osta = "UNKNOWN";
	// o__1.oacc = 0;
	// o__1.ofm = 0;
	// o__1.oblnk = 0;
	// f_open(&o__1);
	// o__1.oerr = 0;
	// o__1.ounit = ifil_1.ipr1;
	// o__1.ofnmlen = 5;
	// o__1.ofnm = "TAPE8";
	// o__1.orl = 0;
	// o__1.osta = "UNKNOWN";
	// o__1.oacc = 0;
	// o__1.ofm = 0;
	// o__1.oblnk = 0;
	// f_open(&o__1);

	/*                                                                       LWT 9080 */
	/*     ALTITUDE PARAMETERS                                               LWT 9090 */
	/*                                                                       LWT 9100 */
	/*     ZMDL  COMMON/MODEL/  THE ALTITUDES USED IN LOWTRAN                LWT 9110 */
	/*     ZCVSA,ZTVSA,ZIVSA  CARD 3.3 LOWTRAN FOR VSA INPUT                 LWT 9120 */
	/*     ZVSA  NINE ALTITUDES GEN BY VSA ROUTINE                           LWT 9130 */
	/*                                                                       LWT 9140 */
	cnstns_1.pi = asin(1.f) * 2.f;
	cnstns_1.ca = cnstns_1.pi / 180.f;
	cnstns_1.deg = 1.f / cnstns_1.ca;
	card3_1.range = 0.f;
	/* *****GCAIR IS THE GAS CONSTANT FOR AIR IN UNITS OF MB/(GM CM-3 K)      LWT 9190 */
	cnstns_1.gcair = 2870.53f;
	/* *****BIGNUM AND BIGEXP ARE THE LARGEST NUMBER AND THE LARGEST ARGUMENT LWT 9210 */
	/* *****EXP ALLOWED AND ARE MACHINE DEPENDENT. THE NUMBERS USED HERE ARE FLWT 9220 */
	/* *****A TYPICAL 32 BIT-WORD COMPUTER.                                   LWT 9230 */
	cnstns_1.bignum = 1e38f;
	cnstns_1.bigexp = 87.f;
	/*     THE VALUES FOR BIGNUM AND BIGEXP FOLLOW THE                       LWT 9260 */
	/*     DESCRIPTION UNDER EXP FUNCTION IN "IBM SYSTEM 360/                LWT 9270 */
	/*     AND SYSTEM 370 FORTRAN IV LANGUAGE"                               LWT 9280 */
	/*     BIGNUM = 4.3E68                                                   LWT 9290 */
	/*     BIGEXP = 174.6                                                    LWT 9300 */
	cntrl_1.kmax = 63;
	/* *****NL IS THE NUMBER OF BOUNDARIES IN THE STANDARD MODELS 1 TO 6      LWT 9320 */
	/* *****BOUNDARY 34 (AT 99999 KM) IS NO LONGER USED                       LWT 9330 */
	cntrl_1.nl = 33;
	/* *****CALL TIME AND DATE:                                               LWT 9350 */
	/* *****THE USER MAY WISH TO INCLUDE SUBROUTINES FDATE AND FCLOCK WHICH   LWT 9360 */
	/* *****RETURN THE DATE AND TIME IN MM/DD/YY AND HH.MM.SS FORMATS         LWT 9370 */
	/* *****RESPECTIVELY. THE REQUIRED ROUTINES FOR A CDC 6600 ARE INCLUDED ATLWT 9380 */
	/* *****THE MAIN PROGRAM IN COMMENT CARDS.                                LWT 9390 */
	/* @    CALL FDATE(HDATE)                                                 LWT 9400 */
	/* @    CALL FCLOCK(HTIME)                                                LWT 9410 */
	/*                                                                       LWT 9420 */
	/* *****START CALCULATION                                                 LWT 9430 */
	/*                                                                       LWT 9440 */
	/*                                                                       LWT 9450 */

L100:
	for (ii = 1; ii <= 4; ++ii)
	{
		/* L10: */
		card2d_1.ireg[ii - 1] = 0;
	}
	io___4.ciunit = ifil_1.ipr;
	s_wsfe(&io___4);
	e_wsfe();
	/* @    WRITE(IPR,1010) HDATE,HTIME                                       LWT 9500 */
	/* L1010: */
	for (i__ = 1; i__ <= 4; ++i__)
	{
		for (j = 1; j <= 40; ++j)
		{
			_BLNK__1.absc[i__ + j * 5 - 6] = 0.f;
			_BLNK__1.extc[i__ + j * 5 - 6] = 0.f;
			/* L80: */
			_BLNK__1.asym[i__ + j * 5 - 6] = 0.f;
		}
	}
	jprt = 0;
	cntrl_1.iklo = 1;
	/*                                                                       LWT 9590 */
	/* *****CARD 1                                                            LWT 9600 */
	/*                                                                       LWT 9610 */

#ifdef debug

	// card1b_3.wmol1 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	float newArr[] = {93.96, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// card1_ newcard{
	// 	_1{
	// 		1, 2, 3}};

	// card1_1 = *lowtran_card1;

	if (lowtran_card1 == nullptr)
	{
		printf("No Card1");
		return -1;
	}

	memcpy(&card1_, lowtran_card1, sizeof(LOWTRAN_Card1));

	// card not mandatory
	if (lowtran_card1a != nullptr)
	{
		memcpy(&card1a_, lowtran_card1a, sizeof(LOWTRAN_Card1a));
	}

	if (lowtran_card2 == nullptr)
	{
		printf("No Card 2");
		return -1;
	}

	memcpy(&card2_, lowtran_card2, sizeof(LOWTRAN_Card2));

	if (lowtran_card3 == nullptr)
	{
		printf("No Card3");
		return -1;
	}

	if (lowtran_card2a != nullptr)
	{
		memcpy(&card2a_, lowtran_card2a, sizeof(LOWTRAN_Card2a));
	}
	if (lowtran_card2b != nullptr)
	{
		memcpy(&card2b_, lowtran_card2b, sizeof(LOWTRAN_Card2b));
	}
	if (lowtran_card2c != nullptr)
	{
		memcpy(&card2c_, lowtran_card2c, sizeof(LOWTRAN_Card2c));
	}
	if (lowtran_card2d != nullptr)
	{
		memcpy(&card2d_, lowtran_card2d, sizeof(LOWTRAN_Card2d));
	}

	if (lowtran_card3 == nullptr)
	{
		printf("No Card3");
		return -1;
	}

	memcpy(&card3_, lowtran_card3, sizeof(LOWTRAN_Card3));

	// printf("Model: %i from %i\n", card1_1.model, lowtran_card1->model);
	// printf("h1: %f from %f\n", card3_1.h1, lowtran_card3->h1);
	// printf("h2: %f from %f\n", card3_1.h2, lowtran_card3->h2);
	// printf("range: %f from %f\n", card3_1.range, lowtran_card3->range);

	//
	// @gp SPECIAL CASE set IMULT = card1, why is it like this?
	// I honestly don't know
	//
	cntrl_1.imult = lowtran_card1->imult;

	cntrl_1.imult = 0;
	card1_1.tbound = 0;
	card1_1.salb = 0;
	card1_1.noprt = 0;
	cntrl_1.ml = 0;

	if (card1_1.im == 1 && (card1_1.model == 7 || card1_1.model == 0))
	{
		printf("TODO NOT IMPLEMENTED\n");
		card1b_1.junit[0] = 10;
		card1b_1.junit[1] = 10;
		card1b_1.junit[2] = 17;

		for (int i = 3; i < 14; i++)
		{
			card1b_1.junit[i] = 14;
		}

		for (int i = 0; i < 11; i++)
		{
			card1b_1.wmol[i] = 0; // todo wmol py
		}
	}

	// @todo cntrl_1
	// ro = 0;

	card4_1.v1 = 2000;
	card4_1.v2 = 50000.0;
	card4_1.dv = 5;

	irpt = 0;

	ro = 0;

	// Use internal MIE-generated database of aerosol phase functions
	// for lowtran models
	iph = 2;

#endif
	PRINT_LINE_READ()
#ifdef DO_FIO_IN
	io___8.ciunit = ifil_1.ird;

	s_rsfe(&io___8);

	do_fio(&c__1, (char *)&card1_1.model, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.itype, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.iemsct, (long)sizeof(long));

	do_fio(&c__1, (char *)&cntrl_1.imult, (long)sizeof(long));

	do_fio(&c__1, (char *)&card1_1.m1, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.m2, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.m3, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m4, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m5, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m6, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.mdef, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.im, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.noprt, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.tbound, (long)sizeof(float));
	do_fio(&c__1, (char *)&card1_1.salb, (long)sizeof(float));
	e_rsfe();
#endif
	io___9.ciunit = ifil_1.ipr;
	s_wsfe(&io___9);
	do_fio(&c__1, (char *)&card1_1.model, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.itype, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.iemsct, (long)sizeof(long));
	do_fio(&c__1, (char *)&cntrl_1.imult, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.m1, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.m2, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.m3, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m4, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m5, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m6, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.mdef, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.im, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.noprt, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.tbound, (long)sizeof(float));
	do_fio(&c__1, (char *)&card1_1.salb, (long)sizeof(float));
	e_wsfe();
	if (cntrl_1.imult == 1 && card1_1.noprt == 1)
	{
		card1_1.noprt = 0;
	}
	/*                                                                       LWT 9680 */
	card1a_1.ird1 = 0;
	card1a_1.ird2 = 0;
	if (card1_1.model == 0)
	{
		card3_1.len = 0;
	}
	if (card1_1.model == 0 || card1_1.model == 7)
	{
		goto L110;
	}
	if (card1_1.m1 == 0)
	{
		card1_1.m1 = card1_1.model;
	}
	if (card1_1.m2 == 0)
	{
		card1_1.m2 = card1_1.model;
	}
	if (card1_1.m3 == 0)
	{
		card1_1.m3 = card1_1.model;
	}
	if (card1a_1.m4 == 0)
	{
		card1a_1.m4 = card1_1.model;
	}
	if (card1a_1.m5 == 0)
	{
		card1a_1.m5 = card1_1.model;
	}
	if (card1a_1.m6 == 0)
	{
		card1a_1.m6 = card1_1.model;
	}
	if (card1a_1.mdef == 0)
	{
		card1a_1.mdef = 1;
	}
L110:
	cntrl_1.m = card1_1.model;
	ifil_1.npr = card1_1.noprt;
	/* *****CARD 2 AEROSOL MODEL                                              LWT 9830 */
	PRINT_LINE_READ()
#ifdef DO_FIO_IN
	io___10.ciunit = ifil_1.ird;
	s_rsfe(&io___10);

	do_fio(&c__1, (char *)&card2_1.ihaze, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.iseasn, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.ivulcn, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.icstl, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.icld, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.ivsa, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.vis, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.wss, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.whh, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.rainrt, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.gndalt, (long)sizeof(float));
	e_rsfe();
#endif
	io___12.ciunit = ifil_1.ipr;
	s_wsfe(&io___12);
	do_fio(&c__1, (char *)&card2_1.ihaze, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.iseasn, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.ivulcn, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.icstl, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.icld, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.ivsa, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.vis, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.wss, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.whh, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.rainrt, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.gndalt, (long)sizeof(float));
	e_wsfe();

	if (card2_1.gndalt > 0.f)
	{
		io___13.ciunit = ifil_1.ipr;
		s_wsfe(&io___13);
		do_fio(&c__1, (char *)&card2_1.gndalt, (long)sizeof(float));
		e_wsfe();
	}
	if (card2_1.gndalt >= 6.f)
	{
		io___14.ciunit = ifil_1.ipr;
		s_wsfe(&io___14);
		do_fio(&c__1, (char *)&card2_1.gndalt, (long)sizeof(float));
		e_wsfe();
		card2_1.gndalt = 0.f;
	}
	/*                                                                       LWT 9970 */
	if (card2_1.vis <= 0.f && card2_1.ihaze > 0)
	{
		card2_1.vis = vsbd_1.vsb[card2_1.ihaze - 1];
	}
	mart_1.rhh = 0.f;
	if (card1_1.model == 0 || card1_1.model == 7)
	{
		goto L205;
	}
	if ((card1_1.model == 3 || card1_1.model == 5) && card2_1.iseasn == 0)
	{
		card2_1.iseasn = 2;
	}
	/*                                                                       LWT10020 */
	if (card2_1.ivsa == 1)
	{
		if (card2_1.ihaze == 3)
		{
			marine_(&card2_1.vis, &card1_1.model, &card2_1.wss, &card2_1.whh,
					&card2_1.icstl, _BLNK__1.extc, _BLNK__1.absc, &c__1);
		}
	}
	_BLNK__1.ich[0] = card2_1.ihaze;
	_BLNK__1.ich[1] = 6;
	_BLNK__1.ich[2] = card2_1.ivulcn + 9;
L205:
	if (card2_1.rainrt == 0.f)
	{
		goto L210;
	}
	io___15.ciunit = ifil_1.ipr;
	s_wsfe(&io___15);
	do_fio(&c__1, (char *)&card2_1.rainrt, (long)sizeof(float));
	e_wsfe();
L210:
	_BLNK__1.ich[3] = 18;
	if (_BLNK__1.ich[0] <= 0)
	{
		_BLNK__1.ich[0] = 1;
	}
	if (_BLNK__1.ich[2] <= 9)
	{
		_BLNK__1.ich[2] = 10;
	}
	if (card2_1.icld >= 1 && card2_1.icld <= 11)
	{
		_BLNK__1.ich[3] = _BLNK__1.ich[2];
		_BLNK__1.ich[2] = _BLNK__1.ich[1];
		_BLNK__1.ich[1] = card2_1.icld;
	}
	iflga = 0;
	iflgt = 0;
	card2a_1.cthik = -99.f;
	card2a_1.calt = -99.f;
	card2a_1.cext = -99.f;
	card2a_1.iseed = -99;
	if (card2_1.icld < 18)
	{
		goto L230;
	}
	/* *****CARD 2A CIRRUS CLOUDS                                             LWT10270 */
	PRINT_LINE_READ()
#ifdef DO_FIO_IN
	io___19.ciunit = ifil_1.ird;
	s_rsfe(&io___19);

	do_fio(&c__1, (char *)&card2a_1.cthik, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2a_1.calt, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2a_1.cext, (long)sizeof(float));

	do_fio(&c__1, (char *)&card2a_1.iseed, (long)sizeof(long));

	e_rsfe();
#endif
	io___20.ciunit = ifil_1.ipr;
	s_wsfe(&io___20);

	do_fio(&c__1, (char *)&card2a_1.cthik, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2a_1.calt, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2a_1.cext, (long)sizeof(float));

	do_fio(&c__1, (char *)&card2a_1.iseed, (long)sizeof(long));

	e_wsfe();

L230:
	/* *****CARD 2B VERTICAL STRUCTURE ALGORITHM                              LWT10330 */
	card2b_1.zcvsa = -99.f;
	card2b_1.ztvsa = -99.f;
	card2b_1.zinvsa = -99.f;
	/*                                                                       LWT10370 */
	if (card2_1.ivsa == 0)
	{
		goto L240;
	}
	PRINT_LINE_READ()
#ifdef DO_FIO_IN
	io___24.ciunit = ifil_1.ird;

	s_rsfe(&io___24);
	do_fio(&c__1, (char *)&card2b_1.zcvsa, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2b_1.ztvsa, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2b_1.zinvsa, (long)sizeof(float));
	e_rsfe();
#endif
	io___25.ciunit = ifil_1.ipr;
	s_wsfe(&io___25);
	do_fio(&c__1, (char *)&card2b_1.zcvsa, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2b_1.ztvsa, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2b_1.zinvsa, (long)sizeof(float));
	e_wsfe();

	/*                                                                       LWT10430 */
	vsa_(&card2_1.ihaze, &card2_1.vis, &card2b_1.zcvsa, &card2b_1.ztvsa, &card2b_1.zinvsa, zvsaly_1.zvsa,
		 zvsaly_1.rhvsa, zvsaly_1.ahvsa, zvsaly_1.ihvsa);
/*                                                                       LWT10450 */
/*     END OF VSA MODEL SET-UP                                           LWT10460 */
/*                                                                       LWT10470 */
L240:
	if (card1_1.model != 0 && card1_1.model != 7)
	{
		cntrl_1.ml = cntrl_1.nl;
	}
	mdels = card1_1.model;
	for (i__ = 1; i__ <= 5; ++i__)
	{
		if (mdels != 0)
		{
			s_copy(titl_1.hmodel + ((i__ + 29) << 2), titl_1.hmodel + ((i__ + mdels * 5 - 6) << 2), (long)4, (long)4);
		}
		/* L250: */
		if (mdels == 0)
		{
			s_copy(titl_1.hmodel + ((i__ + 29) << 2), titl_1.hmodel + ((i__ + 34) << 2), (long)4, (long)4);
		}
	}
	/*                                                                       LWT10530 */
	/*                                                                       LWT10540 */
	if (card1_1.im == 1)
	{
		if (card1_1.model == 7 && card1_1.im == 1 || card1_1.model == 0)
		{
			/*                                                                       LWT10570 */
			/* *****CARD 2C  USER SUPPLIED ATMOSPHERIC PROFILE                        LWT10580 */
			/*                                                                       LWT10590 */
			PRINT_LINE_READ();
#ifdef DO_FIO_IN
			io___27.ciunit = ifil_1.ird;

			s_rsfe(&io___27);

			do_fio(&c__1, (char *)&cntrl_1.ml, (long)sizeof(long));

			do_fio(&c__1, (char *)&card1a_1.ird1, (long)sizeof(long));
			do_fio(&c__1, (char *)&card1a_1.ird2, (long)sizeof(long));

			for (i__ = 1; i__ <= 5; ++i__)
			{
				do_fio(&c__1, titl_1.hmodel + (i__ + 29 << 2), (long)4);
			}
			e_rsfe();
#endif
			io___28.ciunit = ifil_1.ipr;
			s_wsfe(&io___28);

			do_fio(&c__1, (char *)&cntrl_1.ml, (long)sizeof(long));

			do_fio(&c__1, (char *)&card1a_1.ird1, (long)sizeof(long));
			do_fio(&c__1, (char *)&card1a_1.ird2, (long)sizeof(long));

			for (i__ = 1; i__ <= 5; ++i__)
			{
				do_fio(&c__1, titl_1.hmodel + ((i__ + 29) << 2), (long)4);
			}
			e_wsfe();
			if (card2_1.ivsa == 1)
			{
				rdnsm_();
			}
		}
	}
	cntrl_1.m = 7;
	aernsm_(&jprt, &card2_1.gndalt);
	if (card2_1.icld < 20)
	{
		goto L260;
	}
	/*                                                                       LWT10700 */
	/*     SET UP CIRRUS MODEL                                               LWT10710 */
	/*                                                                       LWT10720 */
	if (card2a_1.cthik != 0.f)
	{
		iflgt = 1;
	}
	if (card2a_1.calt != 0.f)
	{
		iflga = 1;
	}
	if (card2a_1.iseed == 0)
	{
		iflgt = 2;
		iflga = 2;
	}
	cirrus_(&card2a_1.cthik, &card2a_1.calt, &card2a_1.iseed, &cprob, &card2a_1.cext);
	io___30.ciunit = ifil_1.ipr;
	s_wsfe(&io___30);
	e_wsfe();
	if (iflgt == 0)
	{
		io___31.ciunit = ifil_1.ipr;
		s_wsfe(&io___31);
		do_fio(&c__1, (char *)&card2a_1.cthik, (long)sizeof(float));
		e_wsfe();
	}
	if (iflgt == 1)
	{
		io___32.ciunit = ifil_1.ipr;
		s_wsfe(&io___32);
		do_fio(&c__1, (char *)&card2a_1.cthik, (long)sizeof(float));
		e_wsfe();
	}
	if (iflgt == 2)
	{
		io___33.ciunit = ifil_1.ipr;
		s_wsfe(&io___33);
		do_fio(&c__1, (char *)&card2a_1.cthik, (long)sizeof(float));
		e_wsfe();
	}
	if (iflga == 0)
	{
		io___34.ciunit = ifil_1.ipr;
		s_wsfe(&io___34);
		do_fio(&c__1, (char *)&card2a_1.calt, (long)sizeof(float));
		e_wsfe();
	}
	if (iflga == 1)
	{
		io___35.ciunit = ifil_1.ipr;
		s_wsfe(&io___35);
		do_fio(&c__1, (char *)&card2a_1.calt, (long)sizeof(float));
		e_wsfe();
	}
	if (iflga == 2)
	{
		io___36.ciunit = ifil_1.ipr;
		s_wsfe(&io___36);
		do_fio(&c__1, (char *)&card2a_1.calt, (long)sizeof(float));
		e_wsfe();
	}
	io___37.ciunit = ifil_1.ipr;
	s_wsfe(&io___37);
	do_fio(&c__1, (char *)&cprob, (long)sizeof(float));
	e_wsfe();
/*                                                                       LWT11000 */
/*       END OF CIRRUS MODEL SET UP                                      LWT11010 */
/*                                                                       LWT11020 */
/*                                                                       LWT11030 */
L260:
	/*                                                                       LWT11050 */
	/*                                                                       LWT11060 */
	/* *****CARD 2E                                                           LWT11070 */
	/*                                                                       LWT11080 */
	if (card2_1.ihaze == 7 || card2_1.icld == 11)
	{
		/*                                                                       LWT11100 */
		/* *****CARD 2E USER SUPPLIED AEROSOL EXTINCTION,ABSORPTION,AND ASYMMETRY LWT11110 */
		rdexa_();
		/*                                                                       LWT11130 */
	}
L300:
	/*                                                                       LWT11160 */
	/*                                                                       LWT11170 */
	iparm = -99;
	iph = -99;
	iday = -99;
	isourc = -99;
	/*                                                                       LWT11220 */
	parm1 = -99.f;
	parm2 = -99.f;
	parm3 = -99.f;
	parm4 = -99.f;
	time = -99.f;
	psipo = -99.f;
	anglem = -99.f;
	g = -99.f;
	/*                                                                       LWT11310 */
	/* *****CARD 3 GEOMETERY PARAMETERS                                       LWT11320 */
	/*                                                                       LWT11330 */
	if (card1_1.iemsct == 3)
	{
		goto L315;
	}
	PRINT_LINE_READ()
#ifdef DO_FIO_IN
	io___50.ciunit = ifil_1.ird;
	s_rsfe(&io___50);

	do_fio(&c__1, (char *)&card3_1.h1, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.h2, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.angle, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.range, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.beta, (long)sizeof(float));
	do_fio(&c__1, (char *)&ro, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.len, (long)sizeof(long));
	e_rsfe();
#endif
	io___52.ciunit = ifil_1.ipr;
	s_wsfe(&io___52);
	do_fio(&c__1, (char *)&card3_1.h1, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.h2, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.angle, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.range, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.beta, (long)sizeof(float));
	do_fio(&c__1, (char *)&ro, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.len, (long)sizeof(long));
	e_wsfe();

	goto L320;
/* *****CARD 3 FOR DIRECTLY TRANSMITTED SOLAR RADIANCE (IEMSCT = 3)       LWT11400 */
L315:
	PRINT_LINE_READ()
#ifdef DO_FIO_IN
	io___53.ciunit = ifil_1.ird;
	s_rsfe(&io___53);

	do_fio(&c__1, (char *)&card3_1.h1, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.h2, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.angle, (long)sizeof(float));

	do_fio(&c__1, (char *)&iday, (long)sizeof(long));
	do_fio(&c__1, (char *)&ro, (long)sizeof(float));
	do_fio(&c__1, (char *)&isourc, (long)sizeof(long));
	do_fio(&c__1, (char *)&anglem, (long)sizeof(float));
	e_rsfe();
#endif
	io___54.ciunit = ifil_1.ipr;
	s_wsfe(&io___54);

	do_fio(&c__1, (char *)&card3_1.h1, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.h2, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.angle, (long)sizeof(float));

	do_fio(&c__1, (char *)&iday, (long)sizeof(long));
	do_fio(&c__1, (char *)&ro, (long)sizeof(float));
	do_fio(&c__1, (char *)&isourc, (long)sizeof(long));
	do_fio(&c__1, (char *)&anglem, (long)sizeof(float));
	e_wsfe();

	card1_1.itype = 3;
	card3_1.range = 0.f;
	card3_1.beta = 0.f;
	card3_1.len = 0;
/* *****RO IS THE RADIUS OF THE EARTH                                     LWT11500 */
L320:
	card3_1.re = 6371.23f;
	if (card3_1.h1 < model_1.zm[0])
	{
		io___55.ciunit = ifil_1.ipr;
		s_wsfe(&io___55);
		do_fio(&c__1, (char *)&card3_1.h1, (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.zm[0], (long)sizeof(float));
		e_wsfe();
		card3_1.h1 = model_1.zm[0];
	}
	h1s = card3_1.h1;
	h2s = card3_1.h2;
	angles = card3_1.angle;
	rangs = card3_1.range;
	betas = card3_1.beta;
	itypes = card1_1.itype;
	lens = card3_1.len;
	if (card1_1.model == 0)
	{
		ro = card3_1.re;
	}
	if (card1_1.model == 1)
	{
		card3_1.re = 6378.39f;
	}
	if (card1_1.model == 4)
	{
		card3_1.re = 6356.91f;
	}
	if (card1_1.model == 5)
	{
		card3_1.re = 6356.91f;
	}
	if (ro > 0.f)
	{
		card3_1.re = ro;
	}
	/*                                                                       LWT11640 */
	if (card1_1.iemsct != 2)
	{
		goto L330;
	}
	/*                                                                       LWT11660 */
	/* *****CARD 3A1                                                          LWT11670 */
	/*                                                                       LWT11680 */
	PRINT_LINE_READ()
#ifdef DO_FIO_IN
	io___63.ciunit = ifil_1.ird;
	s_rsfe(&io___63);
	do_fio(&c__1, (char *)&iparm, (long)sizeof(long));
	do_fio(&c__1, (char *)&iph, (long)sizeof(long));
	do_fio(&c__1, (char *)&iday, (long)sizeof(long));
	do_fio(&c__1, (char *)&isourc, (long)sizeof(long));
	e_rsfe();
#endif
	io___64.ciunit = ifil_1.ipr;
	s_wsfe(&io___64);
	do_fio(&c__1, (char *)&iparm, (long)sizeof(long));
	do_fio(&c__1, (char *)&iph, (long)sizeof(long));
	do_fio(&c__1, (char *)&iday, (long)sizeof(long));
	do_fio(&c__1, (char *)&isourc, (long)sizeof(long));
	e_wsfe();
	/*                                                                       LWT11730 */
	/* *****CARD 3A2                                                          LWT11740 */
	/*                                                                       LWT11750 */
	PRINT_LINE_READ()
#ifdef DO_FIO_IN
	io___65.ciunit = ifil_1.ird;
	s_rsfe(&io___65);
	do_fio(&c__1, (char *)&parm1, (long)sizeof(float));
	do_fio(&c__1, (char *)&parm2, (long)sizeof(float));
	do_fio(&c__1, (char *)&parm3, (long)sizeof(float));
	do_fio(&c__1, (char *)&parm4, (long)sizeof(float));
	do_fio(&c__1, (char *)&time, (long)sizeof(float));
	do_fio(&c__1, (char *)&psipo, (long)sizeof(float));
	do_fio(&c__1, (char *)&anglem, (long)sizeof(float));
	do_fio(&c__1, (char *)&g, (long)sizeof(float));
	e_rsfe();
#endif
	io___66.ciunit = ifil_1.ipr;
	s_wsfe(&io___66);
	do_fio(&c__1, (char *)&parm1, (long)sizeof(float));
	do_fio(&c__1, (char *)&parm2, (long)sizeof(float));
	do_fio(&c__1, (char *)&parm3, (long)sizeof(float));
	do_fio(&c__1, (char *)&parm4, (long)sizeof(float));
	do_fio(&c__1, (char *)&time, (long)sizeof(float));
	do_fio(&c__1, (char *)&psipo, (long)sizeof(float));
	do_fio(&c__1, (char *)&anglem, (long)sizeof(float));
	do_fio(&c__1, (char *)&g, (long)sizeof(float));
	e_wsfe();
	/*                                                                       LWT11800 */
	if (iph == 0)
	{
		if (g >= 1.f)
		{
			g = .9999f;
		}
		if (g <= -1.f)
		{
			g = -.9999f;
		}
	}
	if (iph != 1)
	{
		goto L330;
	}
	/*                                                                       LWT11820 */
	/* *****CARD 3B1 USER DEFINED PHASE FUNCTION                              LWT11830 */
	/*                                                                       LWT11840 */
	/* *****READ USER DEFINED PHASE FUNCTION                                  LWT11850 */
	/*                                                                       LWT11860 */
	PRINT_LINE_READ()
#ifdef DO_FIO_IN
	io___67.ciunit = ifil_1.ird;
	s_rsfe(&io___67);
	do_fio(&c__1, (char *)&usrdta_1.nangls, (long)sizeof(long));
	e_rsfe();
#endif
	io___68.ciunit = ifil_1.ipr;
	s_wsfe(&io___68);
	do_fio(&c__1, (char *)&usrdta_1.nangls, (long)sizeof(long));
	e_wsfe();
	/*                                                                       LWT11910 */
	/* *****CARD 3B2                                                          LWT11920 */
	/*                                                                       LWT11930 */
	PRINT_LINE_READ()
#ifdef DO_FIO_IN
	io___69.ciunit = ifil_1.ird;
	s_rsfe(&io___69);
	i__1 = usrdta_1.nangls;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		do_fio(&c__1, (char *)&usrdta_1.angf[i__ - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&usrdta_1.f[(i__ << 2) - 4], (long)sizeof(float));
		do_fio(&c__1, (char *)&usrdta_1.f[(i__ << 2) - 3], (long)sizeof(float));
		do_fio(&c__1, (char *)&usrdta_1.f[(i__ << 2) - 2], (long)sizeof(float));
		do_fio(&c__1, (char *)&usrdta_1.f[(i__ << 2) - 1], (long)sizeof(float));
	}
	e_rsfe();
#endif
	io___70.ciunit = ifil_1.ipr;
	s_wsfe(&io___70);
	i__1 = usrdta_1.nangls;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		do_fio(&c__1, (char *)&usrdta_1.angf[i__ - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&usrdta_1.f[(i__ << 2) - 4], (long)sizeof(float));
		do_fio(&c__1, (char *)&usrdta_1.f[(i__ << 2) - 3], (long)sizeof(float));
		do_fio(&c__1, (char *)&usrdta_1.f[(i__ << 2) - 2], (long)sizeof(float));
		do_fio(&c__1, (char *)&usrdta_1.f[(i__ << 2) - 1], (long)sizeof(float));
	}
	e_wsfe();
/*                                                                       LWT11980 */
L330:
	/*                                                                       LWT12000 */
	if (irpt == 3)
	{
		goto L500;
	}
/*                                                                       LWT12020 */
/* *****CARD 4 WAVENUMBER                                                 LWT12030 */
/*                                                                       LWT12040 */
L400:
	PRINT_LINE_READ()
#ifdef DO_FIO_IN
	io___71.ciunit = ifil_1.ird;
	s_rsfe(&io___71);

	do_fio(&c__1, (char *)&card4_1.v1, (long)sizeof(float));
	do_fio(&c__1, (char *)&card4_1.v2, (long)sizeof(float));
	do_fio(&c__1, (char *)&card4_1.dv, (long)sizeof(float));

	e_rsfe();
#endif
	io___72.ciunit = ifil_1.ipr;
	s_wsfe(&io___72);
	do_fio(&c__1, (char *)&card4_1.v1, (long)sizeof(float));
	do_fio(&c__1, (char *)&card4_1.v2, (long)sizeof(float));
	do_fio(&c__1, (char *)&card4_1.dv, (long)sizeof(float));
	e_wsfe();
	if (card2_1.ihaze == 3)
	{
		if (card4_1.v1 < 250.f || card4_1.v2 < 250.f)
		{
			card2_1.ihaze = 4;
			io___73.ciunit = ifil_1.ipr;
			s_wsfe(&io___73);
			e_wsfe();
		}
	}
	if (irpt == 4)
	{
		goto L560;
	}
L500:
	if (irpt == 3)
	{
		goto L555;
	}

	io___74.ciunit = ifil_1.ipr;
	s_wsfe(&io___74);
	for (i1 = 1; i1 <= 6; ++i1)
	{
		do_fio(&c__1, titl_1.htrrad + ((i1 + (card1_1.iemsct + 1) * 6 - 7) << 2), (long)4);
	}
	e_wsfe();
	if (isourc == 1)
	{
		io___76.ciunit = ifil_1.ipr;
		s_wsfe(&io___76);
		e_wsfe();
	}
	if (cntrl_1.imult == 1)
	{
		if (card1_1.iemsct == 0 || card1_1.iemsct == 3)
		{
			io___77.ciunit = ifil_1.ipr;
			s_wsfe(&io___77);
			e_wsfe();
			cntrl_1.imult = 0;
		}
		else
		{
			io___78.ciunit = ifil_1.ipr;
			s_wsfe(&io___78);
			e_wsfe();
		}
	}
	mdel = card1_1.model;
	if (mdel == 0)
	{
		mdel = 8;
	}
	mm1 = mdel;
	mm2 = mdel;
	mm3 = mdel;
	if (card1_1.m1 != 0)
	{
		mm1 = card1_1.m1;
	}
	if (card1_1.m2 != 0)
	{
		mm2 = card1_1.m2;
	}
	if (card1_1.m3 != 0)
	{
		mm3 = card1_1.m3;
	}
	if (card1_1.model == 0)
	{
		goto L510;
	}
	io___83.ciunit = ifil_1.ipr;
	s_wsfe(&io___83);
	do_fio(&c__1, (char *)&mm1, (long)sizeof(long));
	for (i1 = 1; i1 <= 5; ++i1)
	{
		do_fio(&c__1, titl_1.hmodel + ((i1 + mm1 * 5 - 6) << 2), (long)4);
	}
	do_fio(&c__1, (char *)&mm2, (long)sizeof(long));
	for (i2 = 1; i2 <= 5; ++i2)
	{
		do_fio(&c__1, titl_1.hmodel + ((i2 + mm2 * 5 - 6) << 2), (long)4);
	}
	do_fio(&c__1, (char *)&mm3, (long)sizeof(long));
	for (i3 = 1; i3 <= 5; ++i3)
	{
		do_fio(&c__1, titl_1.hmodel + ((i3 + mm3 * 5 - 6) << 2), (long)4);
	}
	e_wsfe();
	io___86.ciunit = ifil_1.ipr;
	s_wsfe(&io___86);
	do_fio(&c__1, (char *)&card1a_1.m4, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m5, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m6, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.mdef, (long)sizeof(long));
	e_wsfe();
/*                                                                       LWT12520 */
L510:
	if (jprt == 0)
	{
		goto L520;
	}
	if (card2_1.iseasn == 0)
	{
		card2_1.iseasn = 1;
	}
	if (card2_1.ivulcn <= 0)
	{
		card2_1.ivulcn = 1;
	}
	ihvul = card2_1.ivulcn + 10;
	if (card2_1.ivulcn == 6)
	{
		ihvul = 11;
	}
	if (card2_1.ivulcn == 7)
	{
		ihvul = 11;
	}
	if (card2_1.ivulcn == 8)
	{
		ihvul = 13;
	}
	ihmet = 1;
	if (card2_1.ivulcn > 1)
	{
		ihmet = 2;
	}
	if (card2_1.ihaze == 0)
	{
		goto L520;
	}
	io___89.ciunit = ifil_1.ipr;
	s_wsfe(&io___89);
	for (i__ = 1; i__ <= 5; ++i__)
	{
		do_fio(&c__1, titl_1.hhaze + ((i__ + card2_1.ihaze * 5 - 6) << 2), (long)4);
	}
	do_fio(&c__1, (char *)&card2_1.vis, (long)sizeof(float));
	for (i2 = 1; i2 <= 5; ++i2)
	{
		do_fio(&c__1, titl_1.hhaze + ((i2 + 24) << 2), (long)4);
	}
	for (ii = 1; ii <= 5; ++ii)
	{
		do_fio(&c__1, titl_1.hhaze + ((ii + 24) << 2), (long)4);
	}
	for (ia = 1; ia <= 5; ++ia)
	{
		do_fio(&c__1, titl_1.hseasn + ((ia + card2_1.iseasn * 5 - 6) << 2), (long)4);
	}
	for (i3 = 1; i3 <= 5; ++i3)
	{
		do_fio(&c__1, titl_1.hhaze + ((i3 + ihvul * 5 - 6) << 2), (long)4);
	}
	for (ib = 1; ib <= 5; ++ib)
	{
		do_fio(&c__1, titl_1.hvulcn + ((ib + card2_1.ivulcn * 5 - 6) << 2), (long)4);
	}
	for (ic = 1; ic <= 5; ++ic)
	{
		do_fio(&c__1, titl_1.hseasn + ((ic + card2_1.iseasn * 5 - 6) << 2), (long)4);
	}
	for (i4 = 1; i4 <= 5; ++i4)
	{
		do_fio(&c__1, titl_1.hhaze + ((i4 + 74) << 2), (long)4);
	}
	for (i5 = 1; i5 <= 5; ++i5)
	{
		do_fio(&c__1, titl_1.hmet + ((i5 + ihmet * 5 - 6) << 2), (long)4);
	}
	e_wsfe();
L520:
	if (card1_1.itype == 1)
	{
		io___95.ciunit = ifil_1.ipr;
		s_wsfe(&io___95);
		do_fio(&c__1, (char *)&card3_1.h1, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.range, (long)sizeof(float));
		e_wsfe();
	}
	if (card1_1.itype == 2)
	{
		io___96.ciunit = ifil_1.ipr;
		s_wsfe(&io___96);
		do_fio(&c__1, (char *)&card3_1.h1, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.h2, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.angle, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.range, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.beta, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.len, (long)sizeof(long));
		e_wsfe();
	}
	if (card1_1.itype == 3)
	{
		io___97.ciunit = ifil_1.ipr;
		s_wsfe(&io___97);
		do_fio(&c__1, (char *)&card3_1.h1, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.h2, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.angle, (long)sizeof(float));
		e_wsfe();
	}
	if (card1_1.iemsct != 2)
	{
		goto L550;
	}
	/*                                                                       LWT12890 */
	/* *****INTREPRET SOLAR SCATTERING PARAMETERS                             LWT12900 */
	/*                                                                       LWT12910 */
	/*                                                                       LWT12920 */
	if (iparm == 1)
	{
		subsol_(&parm3, &parm4, &time, &iday);
	}
	/*                                                                       LWT12940 */
	io___98.ciunit = ifil_1.ipr;
	s_wsfe(&io___98);
	e_wsfe();
	if (iparm != 2)
	{
		io___99.ciunit = ifil_1.ipr;
		s_wsfe(&io___99);
		do_fio(&c__1, (char *)&parm1, (long)sizeof(float));
		do_fio(&c__1, (char *)&parm2, (long)sizeof(float));
		do_fio(&c__1, (char *)&parm3, (long)sizeof(float));
		do_fio(&c__1, (char *)&parm4, (long)sizeof(float));
		do_fio(&c__1, (char *)&time, (long)sizeof(float));
		do_fio(&c__1, (char *)&psipo, (long)sizeof(float));
		do_fio(&c__1, (char *)&iday, (long)sizeof(long));
		e_wsfe();
	}
	if (iparm == 2)
	{
		io___100.ciunit = ifil_1.ipr;
		s_wsfe(&io___100);
		do_fio(&c__1, (char *)&parm1, (long)sizeof(float));
		do_fio(&c__1, (char *)&parm2, (long)sizeof(float));
		do_fio(&c__1, (char *)&time, (long)sizeof(float));
		do_fio(&c__1, (char *)&psipo, (long)sizeof(float));
		do_fio(&c__1, (char *)&iday, (long)sizeof(long));
		e_wsfe();
	}
	if (isourc == 0)
	{
		io___101.ciunit = ifil_1.ipr;
		s_wsfe(&io___101);
		e_wsfe();
	}
	if (isourc == 1)
	{
		io___102.ciunit = ifil_1.ipr;
		s_wsfe(&io___102);
		do_fio(&c__1, (char *)&anglem, (long)sizeof(float));
		e_wsfe();
	}
	if (iph == 0)
	{
		io___103.ciunit = ifil_1.ipr;
		s_wsfe(&io___103);
		do_fio(&c__1, (char *)&g, (long)sizeof(float));
		e_wsfe();
	}
	if (iph == 1)
	{
		io___104.ciunit = ifil_1.ipr;
		s_wsfe(&io___104);
		e_wsfe();
	}
	if (iph == 2)
	{
		io___105.ciunit = ifil_1.ipr;
		s_wsfe(&io___105);
		e_wsfe();
	}
L550:

	card4_1.v1 = (float)((long)(card4_1.v1 / 5.f + .1f)) * 5.f;
	card4_1.v2 = (float)((long)(card4_1.v2 / 5.f + .1f)) * 5.f;
	/*     TO AVOID THE DIFFICULTY FOR V1=0                                  LWT13260 */
	alam1 = 99999.98f;
	if (card4_1.v1 > 0.f)
	{
		alam1 = 1e4f / card4_1.v1;
	}
	alam2 = 1e4f / card4_1.v2;
	if (card4_1.dv < 5.f)
	{
		card4_1.dv = 5.f;
	}
	card4_1.dv = (float)((long)(card4_1.dv / 5 + .1f)) * 5.f;
	io___108.ciunit = ifil_1.ipr;
	s_wsfe(&io___108);
	do_fio(&c__1, (char *)&card4_1.v1, (long)sizeof(float));
	do_fio(&c__1, (char *)&alam1, (long)sizeof(float));
	do_fio(&c__1, (char *)&card4_1.v2, (long)sizeof(float));
	do_fio(&c__1, (char *)&alam2, (long)sizeof(float));
	do_fio(&c__1, (char *)&card4_1.dv, (long)sizeof(float));
	e_wsfe();
	/*                                                                       LWT13360 */
	/*                                                                       LWT13370 */
	/* *****LOAD ATMOSPHERIC PROFILE INTO /MODEL/                             LWT13380 */
	/*                                                                       LWT13390 */
	stdmdl_();
/*                                                                       LWT13410 */
/*    DEFINE COUNTER ITEST TO PREVENT ZENITH ANGLE QTHETA AND LAYER      LWT13420 */
/*    PATH LENGTH PL FROM BEING CHANGED DURING SOLAR CALCULATIONS        LWT13430 */
L555:
	for (i__ = 1; i__ <= 68; ++i__)
	{
		i__1 = cntrl_1.kmax;
		for (j = 1; j <= i__1; ++j)
		{
			_BLNK__1.wpath[i__ + j * 68 - 69] = 0.f;
			sols_1.wpaths[i__ + j * 68 - 69] = 0.f;
			/* L14: */
		}
		/* L15: */
	}
	/*                                                                       LWT13500 */
	path_1.itest = 0;
	/*                                                                       LWT13520 */
	if (cntrl_1.imult == 1)
	{
		card3_1.h1 = model_1.zm[0];
		card3_1.h2 = model_1.zm[cntrl_1.ml - 1];
		card1_1.itype = 2;
		card3_1.angle = 0.f;
		card3_1.beta = 0.f;
		card3_1.range = 0.f;
		issgs = cntrl_1.issgeo;
		cntrl_1.issgeo = 0;
		geo_(&ierror, &bendng, &maxgeo);
		w15sv = _BLNK__1.w[14];
		/*                                                                       LWT13640 */
		/*      W15SV  IS THE REL HUM FROM 0 TO SPACE                            LWT13650 */
		/*      THIS REL HUM MAY BE DIFFERENT THAN THE PATH  REL HUM             LWT13660 */
		/*      WHEN REL HUM ARE DIFFERENT THE ANSWER CAN CHANGE                 LWT13670 */
		/*                                                                       LWT13680 */
		cntrl_1.issgeo = issgs;
		mnlt_1.imsmx = cntrl_1.ikmax;
		i__1 = mnlt_1.imsmx;
		for (n = 1; n <= i__1; ++n)
		{
			mnlt_1.tbbms[n - 1] = _BLNK__1.tbby[n - 1];
			plst[n - 1] = path_1.pl[n - 1];
			i__2 = cntrl_1.kmax;
			for (k = 1; k <= i__2; ++k)
			{
				/* L35: */
				mnlt_1.wpms[n + k * 34 - 35] = _BLNK__1.wpath[n + k * 68 - 69];
			}
		}
		/*                                                                       LWT13760 */
		if (card1_1.iemsct == 2)
		{
			ssgeo_(&ierror, &iph, &iparm, &parm1, &parm2, &parm3, &parm4, &psipo, &g, &maxgeo);
			i__2 = cntrl_1.ikmax;
			for (n = 1; n <= i__2; ++n)
			{
				csensv[n - 1] = (r__1 = sols_1.cszen[n - 1], dabs(r__1));
				if (csensv[n - 1] < .0174f)
				{
					csensv[n - 1] = .0174f;
				}
				/* L30: */
			}
			i__2 = cntrl_1.ml;
			for (n = 1; n <= i__2; ++n)
			{
				i__1 = cntrl_1.kmax;
				for (k = 1; k <= i__1; ++k)
				{
					mnlt_1.wpmss[n + k * 34 - 35] = sols_1.wpaths[n + k * 68 - 69];
					/* L45: */
				}
			}
		}
	}
	card3_1.h1 = h1s;
	card3_1.h2 = h2s;
	card3_1.angle = angles;
	card3_1.range = rangs;
	card3_1.beta = betas;
	card1_1.itype = itypes;
	card3_1.len = lens;
	/* *****TRACE PATH THROUGH THE ATMOSPHERE AND CALCULATE ABSORBER AMOUNTS  LWT13970 */
	/*                                                                       LWT13980 */
	cntrl_1.issgeo = 0;
	/*     RANGE=RN0                                                         LWT14000 */
	geo_(&ierror, &bendng, &maxgeo);
	aertmp_();
	if (cntrl_1.imult != 1)
	{
		w15sv = _BLNK__1.w[14];
	}
	/*                                                                       LWT14040 */
	/*   SAVE TEMPERATURE AND PATH INFO FOR LATER USE                        LWT14050 */
	/*                                                                       LWT14060 */
	if (cntrl_1.imult == 1)
	{
		/* L1900: */
		i__1 = cntrl_1.ikmax;
		for (n = 1; n <= i__1; ++n)
		{
			mnlt_1.tbbss[n - 1] = _BLNK__1.tbby[n - 1];
			qthets[n - 1] = path_1.qtheta[n - 1];
			/* L1910: */
			/* L25: */
		}
	}
	/*                                                                       LWT14150 */
	if (ierror > 0)
	{
		goto L630;
	}
	if (card1_1.iemsct == 3 && ierror == -5)
	{
		goto L557;
	}
	goto L558;
L557:
	io___118.ciunit = ifil_1.ipr;
	s_wsfe(&io___118);
	e_wsfe();
	goto L630;
L558:
	/*                                                                       LWT14250 */
	if (card1_1.iemsct == 2)
	{
		ssgeo_(&ierror, &iph, &iparm, &parm1, &parm2, &parm3, &parm4, &psipo,
			   &g, &maxgeo);
	}
	_BLNK__1.w[14] = w15sv;
	/*                                                                       LWT14300 */
	/*     W15SV IS THE REL HUM  (FOR MULT SCAT THIS MAY BE DIFFERENT        LWT14310 */
	/*     FROM PATH REL HUM)                                                LWT14320 */
	/*                                                                       LWT14330 */
	/*                                                                       LWT14340 */
	/*      THE SECOND CALL TO SSGEO IS TO GET THE CORRECT ANGLES FOR        LWT14350 */
	/*      PHASE FUNCTIONS                                                  LWT14360 */
	/*                                                                       LWT14370 */
	/*                                                                       LWT14380 */
	/*    SAVE SOLAR PATH INFORMATION                                        LWT14390 */
	/*                                                                       LWT14400 */
	if (ierror > 0)
	{
		goto L630;
	}
	/*                                                                       LWT14420 */
	if (cntrl_1.imult == 1)
	{
		i__1 = mnlt_1.imsmx;
		for (ik = 1; ik <= i__1; ++ik)
		{
			path_1.qtheta[ik - 1] = qthets[ik - 1];
			path_1.pl[ik - 1] = plst[ik - 1];
			if (card1_1.iemsct == 2)
			{
				sols_1.cszen[ik - 1] = csensv[ik - 1];
			}
			/* L60: */
		}
	}
	/*                                                                       LWT14500 */
	/*                                                                       LWT14510 */
	/* *****LOAD AEROSOL EXTINCTION, ABSORPTION, AND ASYMMETRY COEFFICIENTS   LWT14520 */
	/*                                                                       LWT14530 */
	exabin_();
/*                                                                       LWT14550 */
/* *****WRITE HEADER DATA TO TAPE 7                                       LWT14560 */
/*                                                                       LWT14570 */
L560:
	io___120.ciunit = ifil_1.ipu;
	s_wsfe(&io___120);
	do_fio(&c__1, (char *)&card1_1.model, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.itype, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.iemsct, (long)sizeof(long));
	do_fio(&c__1, (char *)&cntrl_1.imult, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.m1, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.m2, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.m3, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m4, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m5, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m6, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.mdef, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.im, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.noprt, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.tbound, (long)sizeof(float));
	do_fio(&c__1, (char *)&card1_1.salb, (long)sizeof(float));
	e_wsfe();
	io___121.ciunit = ifil_1.ipr1;
	s_wsfe(&io___121);
	do_fio(&c__1, (char *)&card1_1.model, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.itype, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.iemsct, (long)sizeof(long));
	do_fio(&c__1, (char *)&cntrl_1.imult, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.m1, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.m2, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.m3, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m4, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m5, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.m6, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1a_1.mdef, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.im, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.noprt, (long)sizeof(long));
	do_fio(&c__1, (char *)&card1_1.tbound, (long)sizeof(float));
	do_fio(&c__1, (char *)&card1_1.salb, (long)sizeof(float));
	e_wsfe();
	io___122.ciunit = ifil_1.ipu;
	s_wsfe(&io___122);
	do_fio(&c__1, (char *)&card2_1.ihaze, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.iseasn, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.ivulcn, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.icstl, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.icld, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.ivsa, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.vis, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.wss, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.whh, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.rainrt, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.gndalt, (long)sizeof(float));
	e_wsfe();
	io___123.ciunit = ifil_1.ipr1;
	s_wsfe(&io___123);
	do_fio(&c__1, (char *)&card2_1.ihaze, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.iseasn, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.ivulcn, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.icstl, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.icld, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.ivsa, (long)sizeof(long));
	do_fio(&c__1, (char *)&card2_1.vis, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.wss, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.whh, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.rainrt, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2_1.gndalt, (long)sizeof(float));
	e_wsfe();
	io___124.ciunit = ifil_1.ipu;
	s_wsfe(&io___124);
	do_fio(&c__1, (char *)&card2a_1.cthik, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2a_1.calt, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2a_1.cext, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2a_1.iseed, (long)sizeof(long));
	e_wsfe();
	io___125.ciunit = ifil_1.ipr1;
	s_wsfe(&io___125);
	do_fio(&c__1, (char *)&card2a_1.cthik, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2a_1.calt, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2a_1.cext, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2a_1.iseed, (long)sizeof(long));
	e_wsfe();
	io___126.ciunit = ifil_1.ipu;
	s_wsfe(&io___126);
	do_fio(&c__1, (char *)&card2b_1.zcvsa, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2b_1.ztvsa, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2b_1.zinvsa, (long)sizeof(float));
	e_wsfe();
	io___127.ciunit = ifil_1.ipr1;
	s_wsfe(&io___127);
	do_fio(&c__1, (char *)&card2b_1.zcvsa, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2b_1.ztvsa, (long)sizeof(float));
	do_fio(&c__1, (char *)&card2b_1.zinvsa, (long)sizeof(float));
	e_wsfe();
	io___128.ciunit = ifil_1.ipu;
	s_wsfe(&io___128);
	do_fio(&c__1, (char *)&cntrl_1.ml, (long)sizeof(long));
	for (i__ = 1; i__ <= 5; ++i__)
	{
		do_fio(&c__1, titl_1.hmodel + ((i__ + 29) << 2), (long)4);
	}
	e_wsfe();
	io___129.ciunit = ifil_1.ipr1;
	s_wsfe(&io___129);
	do_fio(&c__1, (char *)&cntrl_1.ml, (long)sizeof(long));
	for (i__ = 1; i__ <= 5; ++i__)
	{
		do_fio(&c__1, titl_1.hmodel + ((i__ + 29) << 2), (long)4);
	}
	e_wsfe();
	if (card1_1.model != 0)
	{
		io___130.ciunit = ifil_1.ipu;
		s_wsfe(&io___130);
		do_fio(&c__1, (char *)&card3_1.h1, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.h2, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.angle, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.range, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.beta, (long)sizeof(float));
		do_fio(&c__1, (char *)&ro, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.len, (long)sizeof(long));
		e_wsfe();
	}
	if (card1_1.model != 0)
	{
		io___131.ciunit = ifil_1.ipr1;
		s_wsfe(&io___131);
		do_fio(&c__1, (char *)&card3_1.h1, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.h2, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.angle, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.range, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.beta, (long)sizeof(float));
		do_fio(&c__1, (char *)&ro, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.len, (long)sizeof(long));
		e_wsfe();
	}
	mdlz_1.hmdlz[7] = card3_1.range;
	if (card1_1.model == 0)
	{
		io___132.ciunit = ifil_1.ipu;
		s_wsfe(&io___132);
		for (k = 1; k <= 8; ++k)
		{
			do_fio(&c__1, (char *)&mdlz_1.hmdlz[k - 1], (long)sizeof(float));
		}
		e_wsfe();
	}
	if (card1_1.model == 0)
	{
		io___133.ciunit = ifil_1.ipr1;
		s_wsfe(&io___133);
		for (k = 1; k <= 8; ++k)
		{
			do_fio(&c__1, (char *)&mdlz_1.hmdlz[k - 1], (long)sizeof(float));
		}
		e_wsfe();
	}
	io___134.ciunit = ifil_1.ipu;
	s_wsfe(&io___134);
	do_fio(&c__1, (char *)&iparm, (long)sizeof(long));
	do_fio(&c__1, (char *)&iph, (long)sizeof(long));
	do_fio(&c__1, (char *)&iday, (long)sizeof(long));
	do_fio(&c__1, (char *)&isourc, (long)sizeof(long));
	e_wsfe();
	io___135.ciunit = ifil_1.ipr1;
	s_wsfe(&io___135);
	do_fio(&c__1, (char *)&iparm, (long)sizeof(long));
	do_fio(&c__1, (char *)&iph, (long)sizeof(long));
	do_fio(&c__1, (char *)&iday, (long)sizeof(long));
	do_fio(&c__1, (char *)&isourc, (long)sizeof(long));
	e_wsfe();
	io___136.ciunit = ifil_1.ipu;
	s_wsfe(&io___136);
	do_fio(&c__1, (char *)&parm1, (long)sizeof(float));
	do_fio(&c__1, (char *)&parm2, (long)sizeof(float));
	do_fio(&c__1, (char *)&parm3, (long)sizeof(float));
	do_fio(&c__1, (char *)&parm4, (long)sizeof(float));
	do_fio(&c__1, (char *)&time, (long)sizeof(float));
	do_fio(&c__1, (char *)&psipo, (long)sizeof(float));
	do_fio(&c__1, (char *)&anglem, (long)sizeof(float));
	do_fio(&c__1, (char *)&g, (long)sizeof(float));
	e_wsfe();
	io___137.ciunit = ifil_1.ipr1;
	s_wsfe(&io___137);
	do_fio(&c__1, (char *)&parm1, (long)sizeof(float));
	do_fio(&c__1, (char *)&parm2, (long)sizeof(float));
	do_fio(&c__1, (char *)&parm3, (long)sizeof(float));
	do_fio(&c__1, (char *)&parm4, (long)sizeof(float));
	do_fio(&c__1, (char *)&time, (long)sizeof(float));
	do_fio(&c__1, (char *)&psipo, (long)sizeof(float));
	do_fio(&c__1, (char *)&anglem, (long)sizeof(float));
	do_fio(&c__1, (char *)&g, (long)sizeof(float));
	e_wsfe();
	io___138.ciunit = ifil_1.ipu;
	s_wsfe(&io___138);
	do_fio(&c__1, (char *)&card4_1.v1, (long)sizeof(float));
	do_fio(&c__1, (char *)&card4_1.v2, (long)sizeof(float));
	do_fio(&c__1, (char *)&card4_1.dv, (long)sizeof(float));
	e_wsfe();
	io___139.ciunit = ifil_1.ipr1;
	s_wsfe(&io___139);

	do_fio(&c__1, (char *)&card4_1.v1, (long)sizeof(float));
	do_fio(&c__1, (char *)&card4_1.v2, (long)sizeof(float));
	do_fio(&c__1, (char *)&card4_1.dv, (long)sizeof(float));
	e_wsfe();
	PRINT_LINE_READ()
#ifdef DO_FIO_IN
	io___140.ciunit = ifil_1.ird;
	s_rsfe(&io___140);
	do_fio(&c__1, (char *)&irpt, (long)sizeof(long));
	e_rsfe();
#endif
	io___141.ciunit = ifil_1.ipu;
	s_wsfe(&io___141);
	do_fio(&c__1, (char *)&irpt, (long)sizeof(long));
	e_wsfe();
	io___142.ciunit = ifil_1.ipr1;
	s_wsfe(&io___142);
	do_fio(&c__1, (char *)&irpt, (long)sizeof(long));
	e_wsfe();
	/*                                                                       LWT14890 */
	irain = 0;
	if (card2_1.rainrt > 0.f)
	{
		irain = 1;
	}
	/*                                                                       LWT14920 */
	/* CC                                                                     LWT14930 */
	/* CC    CALCULATE EQUIVALENT LIQUID WATER CONSTANTS                      LWT14940 */
	/* CC                                                                     LWT14950 */
	equlwc_();
	/*                                                                       LWT14970 */
	trans_(resultBuffer, &iph, &isourc, &iday, &anglem);
/*                                                                       LWT14990 */
/* *****WRITE END OF FILE ON TAPE 7                                       LWT15000 */
L630:
	if (ierror > 0)
	{
		PRINT_LINE_READ()
#ifdef DO_FIO_IN
		io___144.ciunit = ifil_1.ird;
		s_rsfe(&io___144);
		do_fio(&c__1, (char *)&irpt, (long)sizeof(long));
		e_rsfe();
#endif
		io___145.ciunit = ifil_1.ipu;
		s_wsfe(&io___145);
		do_fio(&c__1, (char *)&irpt, (long)sizeof(long));
		e_wsfe();
		io___146.ciunit = ifil_1.ipr1;
		s_wsfe(&io___146);
		do_fio(&c__1, (char *)&irpt, (long)sizeof(long));
		e_wsfe();
	}
	io___147.ciunit = ifil_1.ipu;
	s_wsfe(&io___147);
	e_wsfe();
	io___148.ciunit = ifil_1.ipr1;
	s_wsfe(&io___148);
	e_wsfe();
	/*                                                                       LWT15090 */
	io___149.ciunit = ifil_1.ipr;
	s_wsfe(&io___149);
	do_fio(&c__1, (char *)&irpt, (long)sizeof(long));
	e_wsfe();
	if (irpt == 0)
	{
		goto L900;
	}
	if (irpt == 4)
	{
		goto L400;
	}
	if (irpt > 1 && card1_1.iemsct >= 2)
	{
		s_wsle(&io___150);
		do_lio(&c__9, &c__1, (char *)"/!! ERROR IN INPUT IEMSCT GE 2 IRPT GT 1!", (long)41);
		e_wsle();
		s_stop((char *)"", (long)0);
	}
	if (irpt > 4)
	{
		goto L900;
	}
	switch (irpt)
	{
	case 1:
		goto L100;
	case 2:
		goto L900;
	case 3:
		goto L300;
	case 4:
		goto L400;
	}
L900:
	// remove stop
	// s_stop("", (long)0);
	/* @    END                                                               LWT15201 */
	/* @    THE FOLLOWING TIME AND DATE SUBROUTINES APPLY TO A CDC 6600       LWT15210 */
	/* @    SUBROUTINE FDATE(HDATE)                                           LWT15220 */
	/* @    CALL DATE(GDATE)                                                  LWT15230 */
	/* @    HDATE=SHIFT(GDATE,6)                                              LWT15240 */
	/* @    RETURN                                                            LWT15250 */
	/* @    END                                                               LWT15260 */
	/* @    SUBROUTINE FCLOCK(HTIME)                                          LWT15270 */
	/* @    CALL CLOCK(GTIME)                                                 LWT15280 */
	/* @    HTIME=SHIFT(GTIME,6)                                              LWT15290 */
	/* @    RETURN                                                            LWT15300 */
	return 0;
} /* MAIN__ */

/* Subroutine */ int aernsm_(long *jprt, float *gndalt)
{
	/* Initialized data */

	static char ahlvsa[4 * 5] = {'V', 'S', 'A', ' ', 'D', 'E', 'F', 'I', 'N', 'E', 'D', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	static char ahus[4 * 5] = {'U', 'S', 'E', 'R', ' ', 'D', 'E', 'F', 'I', 'N', 'E', 'D', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	static char ahahol[4 * 5 * 13] = {'C', 'U', 'M', 'U', 'L', 'U', 'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'A', 'L', 'T', 'O', 'S', 'T', 'R', 'A', 'T', 'U', 'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'S', 'T', 'R', 'A', 'T', 'U', 'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'S', 'T', 'R', 'A', 'T', 'U', 'S', ' ', 'S', 'T', 'R', 'A', 'T', 'O', ' ', 'C', 'U', 'M', ' ', ' ', 'N', 'I', 'M', 'B', 'O', 'S', 'T', 'R', 'A', 'T', 'U', 'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'D', 'R', 'I', 'Z', 'Z', 'L', 'E', ' ', '2', '.', '0', ' ', 'M', 'M', '/', 'H', 'R', ' ', ' ', ' ', 'L', 'T', ' ', 'R', 'A', 'I', 'N', ' ', '5', '.', '0', ' ', 'M', 'M', '/', 'H', 'R', ' ', ' ', ' ', 'M', 'O', 'D', ' ', 'R', 'A', 'I', 'N', ' ', '1', '2', '.', '5', ' ', 'M', 'M', '/', 'H', 'R', ' ', 'H', 'E', 'A', 'V', 'Y', ' ', 'R', 'A', 'I', 'N', ' ', '2', '5', ' ', 'M', 'M', '/', 'H', 'R', ' ', 'E', 'X', 'T', 'R', 'E', 'M', 'E', ' ', 'R', 'A', 'I', 'N', ' ', '7', '5', 'M', 'M', '/', 'H', 'R', 'U', 'S', 'E', 'R', ' ', 'A', 'T', 'M', 'O', 'S', 'P', 'H', 'E', 'R', 'E', ' ', ' ', ' ', ' ', ' ', 'U', 'S', 'E', 'R', ' ', 'R', 'A', 'I', 'N', ' ', 'N', 'O', ' ', 'C', 'L', 'O', 'U', 'D', ' ', ' ', 'C', 'I', 'R', 'R', 'U', 'S', ' ', 'C', 'L', 'O', 'U', 'D', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	static float cldtop[10] = {3.f, 3.f, 1.f, 2.f, .66f, 1.f, .66f, .66f, 3.f, 3.f};

	/* Format strings */
	static char fmt_910[] = "(\002  ERROR ML GT 24 AND ARMY MODEL TOP LAYER "
							"TRUNCATED\002)";
	static char fmt_900[] = "(\002   ERROR MODEL EQ 0 AND ARMY MODEL CANNOT "
							"MIX\002)";
	static char fmt_925[] = "(//,\002 MODEL ATMOSPHERE NO. \002,i5,\002 ICLD"
							" =\002,i5,//)";
	static char fmt_94[] = "(/,10x,\002 MODEL 0 / 7 USER INPUT DATA \002,//)";
	static char fmt_80[] = "(f10.3,5e10.3,15a1)";
	static char fmt_81[] = "(f10.3,1p5e10.3,10x,15a1)";
	static char fmt_83[] = "((8e10.3))";
	static char fmt_84[] = "((1p8e10.3))";
	static char fmt_82[] = "(10x,3f10.3,5i5)";
	static char fmt_930[] = "(\002 ***ERROR RELHUM \002,e15.4,\002  AT ALT "
							" \002,f12.3)";
	static char fmt_904[] = "(//\0020 CLOUD AND OR RAIN TYPE CHOSEN IS   "
							"\002,5a4)";
	static char fmt_905[] = "(//,t7,\002Z\002,t17,\002P\002,t26,\002T\002,t3"
							"2,\002REL H\002,t41,\002H2O\002,t49,\002CLD AMT\002,t59,\002RAIN"
							" RATE\002,t90,\002AEROSOL\002/,t6,\002(KM)\002,t16,\002(MB)\002,"
							"t25,\002(K)\002,t33,\002(%)\002,t39,\002(GM M-3)\002,t49,\002(GM"
							" M-3)\002,t59,\002(MM HR-1)\002,t69,\002TYPE\002,t90,\002PROFIL"
							"E\002)";
	static char fmt_915[] = "(2f10.3,2f8.2,1p3e10.3,1x,5a4,5a4,5a4)";

	/* System generated locals */
	long i__1;
	double d__1, d__2;

	/* Builtin functions */
	long s_wsfe(cilist *), e_wsfe(void);
	/* Subroutine */ int s_stop(char *, long);
	long do_fio(long *, char *, long), s_rsfe(cilist *), e_rsfe(void);
	double exp(double), pow_dd(double *, double *);
	/* Subroutine */ void s_copy(char *, char *, long, long);
	// GP: have changed int return type -> void to fix cpp error with overloading with f2c
	/* Local variables */
	static long i__, j, k, l, n;
	static float t0;
	static char bl[1];
	static long ii, ij;
	static float ta, rh;
	static long km, nn, kk;
	static float ts;
	static long ic1, ih1[34], is1[34];
	static float fac;
	static long icl;
	static float asc;
	static long ihh;
	static float con, zgn[34];
	extern long jou_(char *, long);
	static float zsc, cld0, cld1, cld2;
	static long iha1, ird0;
	static float haz1, haz2;
	static long ivl1[34];
	static float vis1;
	static long ity1[34];
	static float cldd;
	static long ichr;
	static float haze;
	static char hhol[4 * 5];
	static long idsr, icld1, isea1;
	static char ahol1[4 * 5], ahol2[4 * 5], ahol3[4 * 5];
	static long ivul1;
	extern /* Subroutine */ int check_(float *, long *, long *);
	static long icldc;
	static char jchar[1 * 15];
	static long icldl;
	static float ahaze;
	static long iclds;
	static float ahast[34];
	extern /* Subroutine */ int cirr18_(void);
	static long iconv;
	extern /* Subroutine */ int flayz_(long *, long *, long *, float *, float *, long *);
	static float wtemp, rratz;
	extern /* Subroutine */ int defalt_(float *, float *, float *), laycld_(long *, float *, float *, long *, float *, float *), marine_(float *, long *, float *, float *, long *, float *, float *, long *), cldprf_(long *, long *, long *, long *),
		aerprf_(long *, float *, float *, long *, long *, long *, long *), desatt_(float *, float *);
	static long ityaer;
	extern /* Subroutine */ int layvsa_(long *, float *, float *, long *,
										float *);
	static float eqlwcz;
	extern /* Subroutine */ int vsansm_(long *, float *, long *),
		convrt_(float *, float *);

	/* Fortran I/O blocks */
	static cilist io___166 = {0, 0, 0, fmt_910, 0};
	static cilist io___167 = {0, 0, 0, fmt_900, 0};
	static cilist io___179 = {0, 0, 0, fmt_925, 0};
	static cilist io___180 = {0, 0, 0, fmt_94, 0};
	static cilist io___194 = {0, 0, 0, fmt_80, 0};
	static cilist io___195 = {0, 0, 0, fmt_81, 0};
	static cilist io___196 = {0, 0, 0, fmt_83, 0};
	static cilist io___197 = {0, 0, 0, fmt_84, 0};
	static cilist io___198 = {0, 0, 0, fmt_82, 0};
	static cilist io___199 = {0, 0, 0, fmt_82, 0};
	static cilist io___212 = {0, 0, 0, fmt_930, 0};
	static cilist io___213 = {0, 0, 0, fmt_930, 0};
	static cilist io___227 = {0, 0, 0, fmt_904, 0};
	static cilist io___228 = {0, 0, 0, fmt_905, 0};
	static cilist io___234 = {0, 0, 0, fmt_915, 0};

	/* ********************************************************************** ANS  110 */
	/*     DEFINES ALTITUDE DEPENDENT VARIABLES Z,P,T,WH,WO AND HAZE         ANS  120 */
	/*     CLD RAIN  CLDTYPE                                                 ANS  130 */
	/*     IT ALSO DEFINES ALTITUDE DEPENDENT VARIABLES WAIR,WCO2,WCO,       ANS  140 */
	/*     WCH4,WN2O,WO2,WNH3,WNO,WNO2, AND WSO2                             ANS  150 */
	/*     LOADS HAZE INTO APPROPRATE LOCATION                               ANS  160 */
	/* ********************************************************************** ANS  170 */
	/*                                                                       ANS  820 */
	/*     F(A) IS SATURATED WATER WAPOR DENSITY AT TEMP T,A=TZERO/T         ANS  830 */
	/*                                                                       ANS  840 */
	/*                                                                       ANS  860 */
	/*                                                                       ANS  870 */
	/*     ZMDL COMMON /MODEL/ FINAL ALTITUDE FOR LOWTRAN                    ANS  880 */
	/*     Z   COMMON  /MDATA/ ALTITUDE OF THE PRESSURES,TEMP IN MDATA       ANS  890 */
	/*     ZK  ALTITUDE FOR CLOUD                                            ANS  900 */
	/*     ZSC ALTITUDE FOR AEROSOLS  GNDALT                                 ANS  910 */
	/*                                                                       ANS  920 */
	/*                                                                       ANS  930 */
	card2d_1.iregc[0] = 0;
	card2d_1.iregc[1] = 0;
	card2d_1.iregc[2] = 0;
	card2d_1.iregc[3] = 0;
	iconv = 1;
	ird0 = 1;
	icldl = card2_1.icld;
	if ((float)card1_1.model == 0.f || card1_1.model == 7)
	{
		if (card1_1.im != 1)
		{
			return 0;
		}
	}
	if ((float)card1_1.model > 0.f && card1_1.model < 7)
	{
		ird0 = 0;
	}
	if (ird0 == 1 && card2_1.ivsa == 1)
	{
		ird0 = 0;
		card1a_1.ird1 = 0;
		card1a_1.ird2 = 0;
		iconv = 0;
		cntrl_1.ml = cntrl_1.ml + 10 - card1b_1.jlow;
		if (cntrl_1.ml > 34)
		{
			io___166.ciunit = ifil_1.ipr;
			s_wsfe(&io___166);
			e_wsfe();
		}
		if (cntrl_1.ml > 34)
		{
			cntrl_1.ml = 34;
		}
		zvsaly_1.zvsa[9] = zvsaly_1.zvsa[8] + .01f;
		zvsaly_1.rhvsa[9] = 0.f;
		zvsaly_1.ahvsa[9] = 0.f;
		zvsaly_1.ihvsa[9] = 0;
		if (card1_1.model == 0)
		{
			io___167.ciunit = ifil_1.ipr;
			s_wsfe(&io___167);
			e_wsfe();
		}
		if (card1_1.model == 0)
		{
			s_stop((char *)"", (long)0);
		}
	}
	icl = 0;
	idsr = 0;
	if (card2_1.icld == 18 || card2_1.icld == 19)
	{
		cirr18_();
		cldd = card2a_1.cthik * .1f;
		cld0 = card2a_1.calt - cldd * .5f;
		if (cld0 <= 0.f)
		{
			cld0 = 0.f;
		}
		cld1 = cld0 + cldd;
		cld2 = cld1 + card2a_1.cthik - cldd;
		/*          CLD3 = CLD2 + CLDD                                           ANS 1310 */
		/*                                                                       ANS 1320 */
		/*          CLD1 1ST Z OF CIRRUS                                         ANS 1330 */
		/*          CLD2 LST Z OF CIRRUS                                         ANS 1340 */
		/*                                                                       ANS 1350 */
	}
	flayz_(&cntrl_1.ml, &card1_1.model, &card2_1.icld, model_2.zmdl, gndalt, &card2_1.ivsa);
	*jprt = 1;
	if (card1_1.model == 0 || card1_1.model == 7)
	{
		*jprt = 0;
	}
	if (card2_1.ivsa == 1)
	{
		*jprt = 0;
	}
	if (card2_1.icld >= 1 && card2_1.icld < 20)
	{
		*jprt = 0;
	}
	if (card2_1.rainrt > 0.f)
	{
		*jprt = 0;
	}
	if (*gndalt > 0.f)
	{
		*jprt = 0;
	}
	/*                                                                       ANS 1440 */
	i__1 = cntrl_1.ml;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		model_2.hazec[i__ - 1] = 0.f;
		/* L5: */
	}
	for (ii = 1; ii <= 4; ++ii)
	{
		/* L6: */
		card2d_1.altb[ii - 1] = 0.f;
	}
	t0 = 273.15f;
	ic1 = 1;
	n = 7;
	if (card2_1.ivulcn <= 0)
	{
		card2_1.ivulcn = 1;
	}
	if (card2_1.iseasn <= 0)
	{
		card2_1.iseasn = 1;
	}
	if (*jprt == 0)
	{
		io___179.ciunit = ifil_1.ipr;
		s_wsfe(&io___179);
		do_fio(&c__1, (char *)&card1_1.model, (long)sizeof(long));
		do_fio(&c__1, (char *)&card2_1.icld, (long)sizeof(long));
		e_wsfe();
		if (card1_1.model == 7)
		{
			io___180.ciunit = ifil_1.ipr;
			s_wsfe(&io___180);
			e_wsfe();
		}
		/*                                                                       ANS 1590 */
	}
	/*                                                                       ANS 1610 */
	/*                                                                       ANS 1620 */
	i__1 = cntrl_1.ml;
	for (k = 1; k <= i__1; ++k)
	{
		/*                                                                       ANS 1640 */
		/*    LOOP OVER LAYERS                                                   ANS 1650 */
		/*                                                                       ANS 1660 */
		rh = 0.f;
		mdata_1.wh[k - 1] = 0.f;
		mdata_1.wo[k - 1] = 0.f;
		/*                                                                       ANS 1700 */
		iha1 = 0;
		icld1 = 0;
		isea1 = 0;
		ivul1 = 0;
		vis1 = 0.f;
		ahaze = 0.f;
		eqlwcz = 0.f;
		rratz = 0.f;
		ichr = 0;
		/*     NEW                                                               ANS 1800 */
		/*                                                                       ANS 1810 */
		mdata1_1.wair[k - 1] = 0.f;
		mdata_1.wco2[k - 1] = 0.f;
		mdata_1.wco[k - 1] = 0.f;
		mdata_1.wch4[k - 1] = 0.f;
		mdata_1.wn2o[k - 1] = 0.f;
		mdata_1.wo2[k - 1] = 0.f;
		mdata1_1.wnh3[k - 1] = 0.f;
		mdata1_1.wno[k - 1] = 0.f;
		mdata1_1.wno2[k - 1] = 0.f;
		mdata1_1.wso2[k - 1] = 0.f;
		_BLNK__2.whno3[k - 1] = 0.f;
		for (km = 1; km <= 15; ++km)
		{
			*(unsigned char *)&jchar[km - 1] = ' ';
			if (km > 12)
			{
				goto L10;
			}
			// done in python
			// card1b_1.wmol[km - 1] = 0.f;
		L10:;
		}
		/*                                                                       ANS 1980 */
		/*                                                                       ANS 1990 */
		/*        PARAMETERS - JCHAR = INPUT KEY (SEE BELOW)                     ANS 2000 */
		/*                                                                       ANS 2010 */
		/*                                                                       ANS 2020 */
		/*     ***  ROUTINE ALSO ACCEPTS VARIABLE UNITS ON PRESS AND TEMP        ANS 2030 */
		/*                                                                       ANS 2040 */
		/*          SEE INPUT KEY BELOW                                          ANS 2050 */
		/*                                                                       ANS 2060 */
		/*                                                                       ANS 2070 */
		/*                                                                       ANS 2080 */
		/*     FOR MOLECULAR SPECIES ONLY                                        ANS 2090 */
		/*                                                                       ANS 2100 */
		/*       JCHAR   JUNIT                                                   ANS 2110 */
		/*                                                                       ANS 2120 */
		/*     " ",A      10    VOLUME MIXING RATIO (PPMV)                       ANS 2130 */
		/*         B      11    NUMBER DENSITY (CM-3)                            ANS 2140 */
		/*         C      12    MASS MIXING RATIO (GM(K)/KG(AIR))                ANS 2150 */
		/*         D      13    MASS DENSITY (GM M-3)                            ANS 2160 */
		/*         E      14    PARTIAL PRESSURE (MB)                            ANS 2170 */
		/*         F      15    DEW POINT TEMP (TD IN T(K)) - H2O ONLY           ANS 2180 */
		/*         G      16     "    "     "  (TD IN T(C)) - H2O ONLY           ANS 2190 */
		/*         H      17    RELATIVE HUMIDITY (RH IN PERCENT) - H2O ONLY     ANS 2200 */
		/*         I      18    AVAILABLE FOR USER DEFINITION                    ANS 2210 */
		/*        1-6    1-6    DEFAULT TO SPECIFIED MODEL ATMOSPHERE            ANS 2220 */
		/*                                                                       ANS 2230 */
		/*     ****************************************************************  ANS 2240 */
		/*     ****************************************************************  ANS 2250 */
		/*                                                                       ANS 2260 */
		/*     ***** OTHER 'JCHAR' SPECIFICATIONS -                              ANS 2270 */
		/*                                                                       ANS 2280 */
		/*       JCHAR   JUNIT                                                   ANS 2290 */
		/*                                                                       ANS 2300 */
		/*      " ",A     10    PRESSURE IN (MB)                                 ANS 2310 */
		/*          B     11       "     "  (ATM)                                ANS 2320 */
		/*          C     12       "     "  (TORR)                               ANS 2330 */
		/*         1-6   1-6    DEFAULT TO SPECIFIED MODEL ATMOSPHERE            ANS 2340 */
		/*                                                                       ANS 2350 */
		/*      " ",A     10    AMBIENT TEMPERATURE IN DEG(K)                    ANS 2360 */
		/*          B     11       "         "       "  " (C)                    ANS 2370 */
		/*          C     12       "         "       "  " (F)                    ANS 2380 */
		/*         1-6   1-6    DEFAULT TO SPECIFIED MODEL ATMOSPHERE            ANS 2390 */
		/*                                                                       ANS 2400 */
		/*     ***** DEFINITION OF "DEFAULT" CHOICES FOR PROFILE SELECTION ***** ANS 2410 */
		/*                                                                       ANS 2420 */
		/*      FOR THE USER WHO WISHES TO ENTER ONLY SELECTED ORIGINAL          ANS 2430 */
		/*      VERTICAL PROFILES AND WANTS STANDARD ATMOSPHERE SPECIFICATIONS   ANS 2440 */
		/*      FOR THE OTHERS, THE FOLLOWING OPTION IS AVAILABLE                ANS 2450 */
		/*                                                                       ANS 2460 */
		/*     *** JCHAR(P,T OR K) MUST = 1-6 (AS ABOVE)                         ANS 2470 */
		/*                                                                       ANS 2480 */
		/*      FOR MOLECULES 8-35, ONLY US STD PROFILES ARE AVIALABLE           ANS 2490 */
		/*      THEREFORE, WHEN  'JCHAR(K) = 1-5', JCHAR(K) WILL BE RESET TO 6   ANS 2500 */
		/*                                                                       ANS 2510 */
		/*                                                                       ANS 2520 */
		if (ird0 == 1)
		{
			PRINT_LINE_READ();
#ifdef DO_FIO_IN
			io___194.ciunit = ifil_1.ird;
			s_rsfe(&io___194);
			do_fio(&c__1, (char *)&model_2.zmdl[k - 1], (long)sizeof(float));
			do_fio(&c__1, (char *)&mdata_1.p[k - 1], (long)sizeof(float));
			do_fio(&c__1, (char *)&mdata_1.t[k - 1], (long)sizeof(float));

			do_fio(&c__1, (char *)&card1b_1.wmol[0], (long)sizeof(float));
			do_fio(&c__1, (char *)&card1b_1.wmol[1], (long)sizeof(float));
			do_fio(&c__1, (char *)&card1b_1.wmol[2], (long)sizeof(float));

			for (km = 1; km <= 14; ++km)
			{
				do_fio(&c__1, jchar + (km - 1), (long)1);
			}
			e_rsfe();
#endif
			io___195.ciunit = ifil_1.ipr;
			s_wsfe(&io___195);
			do_fio(&c__1, (char *)&model_2.zmdl[k - 1], (long)sizeof(float));
			do_fio(&c__1, (char *)&mdata_1.p[k - 1], (long)sizeof(float));
			do_fio(&c__1, (char *)&mdata_1.t[k - 1], (long)sizeof(float));
			do_fio(&c__1, (char *)&card1b_1.wmol[0], (long)sizeof(float));
			do_fio(&c__1, (char *)&card1b_1.wmol[1], (long)sizeof(float));
			do_fio(&c__1, (char *)&card1b_1.wmol[2], (long)sizeof(float));
			for (km = 1; km <= 14; ++km)
			{
				do_fio(&c__1, jchar + (km - 1), (long)1);
			}
			e_wsfe();
		}
		if (card1a_1.ird1 == 1)
		{
			PRINT_LINE_READ();
#ifdef DO_FIO_IN
			io___196.ciunit = ifil_1.ird;
			s_rsfe(&io___196);
			for (km = 4; km <= 12; ++km)
			{
				do_fio(&c__1, (char *)&card1b_1.wmol[km - 1], (long)sizeof(float));
			}
			e_rsfe();
#endif
			io___197.ciunit = ifil_1.ipr;
			s_wsfe(&io___197);
			for (km = 4; km <= 12; ++km)
			{
				do_fio(&c__1, (char *)&card1b_1.wmol[km - 1], (long)sizeof(float));
			}
			e_wsfe();
		}
		/*                                                                       ANS 2670 */
		/*                                                                       ANS 2680 */
		/*     AHAZE =  AEROSOL VISIBLE EXTINCTION COFF (KM-1)                   ANS 2690 */
		/*     AT A WAVELENGTH OF 0.55 MICROMETERS                               ANS 2700 */
		/*                                                                       ANS 2710 */
		/*     EQLWCZ=LIQUID WATER CONTENT (PPMV) AT ALT Z                       ANS 2720 */
		/*            FOR AEROSOL, CLOUD OR FOG MODELS                           ANS 2730 */
		/*                                                                       ANS 2740 */
		/*     RRATZ=RAIN RATE (MM/HR) AT ALT Z                                  ANS 2750 */
		/*                                                                       ANS 2760 */
		/*     IHA1 AEROSOL MODEL USED FOR SPECTRAL DEPENDENCE OF EXTINCTION     ANS 2770 */
		/*                                                                       ANS 2780 */
		/*     IVUL1 STRATOSPHERIC AERSOL MODEL USED FOR SPECTRAL DEPENDENCE     ANS 2790 */
		/*     OF EXT AT Z                                                       ANS 2800 */
		/*                                                                       ANS 2810 */
		/*     ICLD1 CLOUD MODEL USED FOR SPECTRAL DEPENDENCE OF EXT AT Z        ANS 2820 */
		/*                                                                       ANS 2830 */
		/*     ONLY ONE OF IHA1,ICLD1  OR IVUL1 IS ALLOWED                       ANS 2840 */
		/*     IHA1 NE 0 OTHERS IGNORED                                          ANS 2850 */
		/*     IHA1 EQ 0 AND ICLD1 NE 0 USE ICLD1                                ANS 2860 */
		/*                                                                       ANS 2870 */
		/*     IF AHAZE AND EQLWCZ ARE BOUTH ZERO                                ANS 2880 */
		/*        DEFAULT PROFILE ARE LOADED FROM IHA1,ICLD1,IVUL1               ANS 2890 */
		/*     ISEA1 = AERSOL SEASON CONTROL FOR ALTITUDE Z                      ANS 2900 */
		/*                                                                       ANS 2910 */
		/*     ICHR  CHANGE AERSOL PROFILE REGION FOR IHA1 = 7                   ANS 2920 */
		/*                                                                       ANS 2930 */
		if (card1a_1.ird2 == 1)
		{
			PRINT_LINE_READ();
#ifdef DO_FIO_IN
			io___198.ciunit = ifil_1.ird;
			s_rsfe(&io___198);
			do_fio(&c__1, (char *)&ahaze, (long)sizeof(float));
			do_fio(&c__1, (char *)&eqlwcz, (long)sizeof(float));
			do_fio(&c__1, (char *)&rratz, (long)sizeof(float));
			do_fio(&c__1, (char *)&iha1, (long)sizeof(long));
			do_fio(&c__1, (char *)&icld1, (long)sizeof(long));
			do_fio(&c__1, (char *)&ivul1, (long)sizeof(long));
			do_fio(&c__1, (char *)&isea1, (long)sizeof(long));
			do_fio(&c__1, (char *)&ichr, (long)sizeof(long));
			e_rsfe();
#endif
			io___199.ciunit = ifil_1.ipr;
			s_wsfe(&io___199);
			do_fio(&c__1, (char *)&ahaze, (long)sizeof(float));
			do_fio(&c__1, (char *)&eqlwcz, (long)sizeof(float));
			do_fio(&c__1, (char *)&rratz, (long)sizeof(float));
			do_fio(&c__1, (char *)&iha1, (long)sizeof(long));
			do_fio(&c__1, (char *)&icld1, (long)sizeof(long));
			do_fio(&c__1, (char *)&ivul1, (long)sizeof(long));
			do_fio(&c__1, (char *)&isea1, (long)sizeof(long));
			do_fio(&c__1, (char *)&ichr, (long)sizeof(long));
			e_wsfe();
		}
		else
		{
			rratz = card2_1.rainrt;
			if (model_2.zmdl[k - 1] > 6.f)
			{
				rratz = 0.f;
			}
		}
		iclds = icld1;
		if (ichr == 1)
		{
			if (iha1 == 0)
			{
				if (icld1 != 11)
				{
					ichr = 0;
				}
			}
			else
			{
				if (iha1 != 7)
				{
					ichr = 0;
				}
			}
		}
		if (card1_1.model == 0)
		{
			mdlz_1.hmdlz[0] = model_2.zmdl[k - 1];
			mdlz_1.hmdlz[1] = mdata_1.p[k - 1];
			mdlz_1.hmdlz[2] = mdata_1.t[k - 1];
			mdlz_1.hmdlz[3] = card1b_1.wmol[0];
			mdlz_1.hmdlz[4] = card1b_1.wmol[1];
			mdlz_1.hmdlz[5] = card1b_1.wmol[2];
			mdlz_1.hmdlz[6] = ahaze;
		}
		for (km = 1; km <= 15; ++km)
		{
			/* L12: */
			// ignore?
			// card1b_1.junit[km - 1] = jou_(jchar + (km - 1), (long)1);
		}
		if (ird0 == 0)
		{
			card1b_1.junit[0] = card1_1.m1;
			card1b_1.junit[1] = card1_1.m1;
			card1b_1.junit[2] = card1_1.m2;
			card1b_1.junit[3] = 6;
			card1b_1.junit[4] = card1_1.m3;
			card1b_1.junit[5] = card1a_1.m5;
			card1b_1.junit[6] = card1a_1.m6;
			card1b_1.junit[7] = card1a_1.m4;
			card1b_1.junit[8] = 6;
			card1b_1.junit[9] = 6;
			card1b_1.junit[10] = 6;
			card1b_1.junit[11] = 6;
			card1b_1.junit[12] = 6;
			card1b_1.junit[13] = 6;
			card1b_1.junit[14] = 6;
		}
		else
		{
			*(unsigned char *)bl = ' ';
			if (card1_1.m1 > 0 && *(unsigned char *)&jchar[0] == *(unsigned char *)bl)
			{
				card1b_1.junit[0] = card1_1.m1;
			}
			if (card1_1.m1 > 0 && *(unsigned char *)&jchar[1] == *(unsigned char *)bl)
			{
				card1b_1.junit[1] = card1_1.m1;
			}
			if (card1_1.m2 > 0 && *(unsigned char *)&jchar[2] == *(unsigned char *)bl)
			{
				card1b_1.junit[2] = card1_1.m2;
			}
			if (card1a_1.mdef > 0 && *(unsigned char *)&jchar[3] == *(
																		unsigned char *)bl)
			{
				card1b_1.junit[3] = 6;
			}
			if (card1_1.m3 > 0 && *(unsigned char *)&jchar[4] == *(unsigned char *)bl)
			{
				card1b_1.junit[4] = card1_1.m3;
			}
			if (card1a_1.m5 > 0 && *(unsigned char *)&jchar[5] == *(unsigned char *)bl)
			{
				card1b_1.junit[5] = card1a_1.m5;
			}
			if (card1a_1.m6 > 0 && *(unsigned char *)&jchar[6] == *(unsigned char *)bl)
			{
				card1b_1.junit[6] = card1a_1.m6;
			}
			if (card1a_1.m4 > 0 && *(unsigned char *)&jchar[7] == *(unsigned char *)bl)
			{
				card1b_1.junit[7] = card1a_1.m4;
			}
			if (card1a_1.mdef > 0 && *(unsigned char *)&jchar[8] == *(
																		unsigned char *)bl)
			{
				card1b_1.junit[8] = 6;
			}
			if (card1a_1.mdef > 0 && *(unsigned char *)&jchar[9] == *(
																		unsigned char *)bl)
			{
				card1b_1.junit[9] = 6;
			}
			if (card1a_1.mdef > 0 && *(unsigned char *)&jchar[10] == *(
																		 unsigned char *)bl)
			{
				card1b_1.junit[10] = 6;
			}
			if (card1a_1.mdef > 0 && *(unsigned char *)&jchar[11] == *(
																		 unsigned char *)bl)
			{
				card1b_1.junit[11] = 6;
			}
			if (card1a_1.mdef > 0 && *(unsigned char *)&jchar[12] == *(
																		 unsigned char *)bl)
			{
				card1b_1.junit[12] = 6;
			}
			if (card1a_1.mdef > 0 && *(unsigned char *)&jchar[13] == *(
																		 unsigned char *)bl)
			{
				card1b_1.junit[13] = 6;
			}
		}
		if (iconv == 1)
		{
			check_(&mdata_1.p[k - 1], card1b_1.junit, &c__1);
			check_(&mdata_1.t[k - 1], &card1b_1.junit[1], &c__2);
			defalt_(&model_2.zmdl[k - 1], &mdata_1.p[k - 1], &mdata_1.t[k - 1]);
			convrt_(&mdata_1.p[k - 1], &mdata_1.t[k - 1]);
			mdata_1.wh[k - 1] = card1b_1.wmol[0];
			mdata_1.wco2[k - 1] = card1b_1.wmol[1];
			mdata_1.wo[k - 1] = card1b_1.wmol[2];
			mdata_1.wn2o[k - 1] = card1b_1.wmol[3];
			mdata_1.wco[k - 1] = card1b_1.wmol[4];
			mdata_1.wch4[k - 1] = card1b_1.wmol[5];
			mdata_1.wo2[k - 1] = card1b_1.wmol[6];
			mdata1_1.wno[k - 1] = card1b_1.wmol[7];
			mdata1_1.wso2[k - 1] = card1b_1.wmol[8];
			mdata1_1.wno2[k - 1] = card1b_1.wmol[9];
			mdata1_1.wnh3[k - 1] = card1b_1.wmol[10];
			_BLNK__2.whno3[k - 1] = card1b_1.wmol[11];
			mdata1_1.wair[k - 1] = card1b_1.wair1;
		}
		else
		{
			vsansm_(&k, &ahaze, &iha1);
			model_2.zmdl[k - 1] = mdata_1.z__[k - 1];
		}
		/*                                                                       ANS 3920 */
		/*                                                                       ANS 3930 */
		/*     GNDALT NOT ZERO                                                   ANS 3940 */
		/*                                                                       ANS 3950 */
		zsc = model_2.zmdl[k - 1];
		if (*gndalt > 0.f && model_2.zmdl[k - 1] < 6.f)
		{
			asc = 6.f / (6.f - *gndalt);
			con = -asc * *gndalt;
			zsc = asc * model_2.zmdl[k - 1] + con - 1e-4f;
			if (zsc < 0.f)
			{
				zsc = 0.f;
			}
		}
		zgn[k - 1] = zsc;
		/*                                                                       ANS 4040 */
		/*                                                                       ANS 4050 */
		if (icld1 == 0)
		{
			icld1 = card2_1.icld;
		}
		icldl = icld1;
		if (icld1 > 11)
		{
			icld1 = 0;
		}
		if (iha1 != 0)
		{
			ivul1 = 0;
		}
		if (iha1 != 0)
		{
			icld1 = 0;
		}
		if (icld1 != 0)
		{
			ivul1 = 0;
		}
		if (ahaze != 0.f || eqlwcz != 0.f)
		{
			goto L8;
		}
		/* CC   IF(RRATZ.NE.0.) GO TO 8                                           ANS*4130 */
		if (card2_1.ivsa == 1 && icld1 == 0)
		{
			if (card1_1.model != 7)
			{
				layvsa_(&k, &rh, &ahaze, &iha1, model_2.zmdl);
			}
		}
		else
		{
			laycld_(&k, &eqlwcz, &rratz, &icld1, gndalt, &card2_1.rainrt);
			if (card2_1.rainrt > 0.f && model_2.zmdl[k - 1] < 6.f)
			{
				rratz = card2_1.rainrt;
			}
			if (icld1 < 1)
			{
				goto L8;
			}
			if (icld1 > 10)
			{
				goto L8;
			}
			if (model_2.zmdl[k - 1] > cldtop[icld1 - 1] + *gndalt)
			{
				rratz = 0.f;
			}
		}
	L8:
		icldc = card2_1.icld;
		if (iclds != 0)
		{
			icldc = iclds;
		}
		/*                                                                       ANS 4270 */
		if (iclds == 18 || iclds == 19)
		{
			if (ahaze > 0.f)
			{
				model_2.densty[k * 63 - 48] = ahaze;
				ahaze = 0.f;
				goto L46;
			}
			if (eqlwcz > 0.f)
			{
				if (iclds == 18)
				{
					con = .003446f;
				}
				if (iclds == 19)
				{
					con = .05811f;
				}
				model_2.densty[k * 63 - 48] = eqlwcz / con;
				eqlwcz = 0.f;
				goto L46;
			}
		}
		if (icldc == 18 || icldc == 19)
		{
			model_2.densty[k * 63 - 48] = 0.f;
			if (model_2.zmdl[k - 1] >= cld1 && model_2.zmdl[k - 1] <= cld2)
			{
				model_2.densty[k * 63 - 48] = card2a_1.cext;
			}
		}
	L46:
		model_2.cldamt[k - 1] = eqlwcz;
		if (iclds == 0 && model_2.cldamt[k - 1] == 0.f)
		{
			icld1 = 0;
		}
		model_2.rramt[k - 1] = rratz;
		if (card1_1.model == 0 || card1_1.model == 7)
		{
			/*     DONT CHANGE RH                                                    ANS 4510 */
		}
		else
		{
			if (eqlwcz > 0.f)
			{
				rh = 100.f;
			}
			if (rratz > 0.f)
			{
				rh = 100.f;
			}
		}
		ahast[k - 1] = ahaze;
		/*     IHA1  IS IHAZE FOR THIS LAYER                                     ANS 4570 */
		/*     ISEA1 IS ISEASN FOR THIS LAYER                                    ANS 4580 */
		/*     IVUL1 IS IVULCN FOR THE LAYER                                     ANS 4590 */
		if (isea1 == 0)
		{
			isea1 = card2_1.iseasn;
		}
		ityaer = card2_1.ihaze;
		if (iha1 > 0)
		{
			ityaer = iha1;
		}
		if (ivul1 > 0)
		{
			card2_1.ivulcn = ivul1;
		}
		if (ivul1 <= 0)
		{
			ivul1 = card2_1.ivulcn;
		}
		/*                                                                       ANS 4650 */
		if (k == 1)
		{
			goto L23;
		}
		if (ichr == 1)
		{
			goto L20;
		}
		if (icld1 != card2d_1.iregc[ic1 - 1])
		{
			goto L19;
		}
		if (iha1 == 0 && icld1 == 0)
		{
			if (zsc > 2.f)
			{
				ityaer = 6;
			}
			if (zsc > 10.f)
			{
				ityaer = card2_1.ivulcn + 10;
			}
			if (zsc > 30.f)
			{
				ityaer = 19;
			}
			if (ityaer == _BLNK__2.ich[ic1 - 1])
			{
				goto L23;
			}
		}
		if (icld1 == 0 && iha1 == 0)
		{
			goto L20;
		}
		n = 7;
		if (ic1 > 1)
		{
			n = ic1 + 10;
		}
		if (iha1 == 0)
		{
			goto L23;
		}
		if (iha1 != _BLNK__2.ich[ic1 - 1])
		{
			goto L20;
		}
		goto L23;
	L19:
		if (icld1 != 0)
		{
			if (icld1 == card2d_1.iregc[0])
			{
				n = 7;
				card2d_1.altb[0] = model_2.zmdl[k - 1];
				goto L24;
			}
			if (ic1 == 1)
			{
				goto L20;
			}
			if (icld1 == card2d_1.iregc[1])
			{
				n = 12;
				card2d_1.altb[1] = model_2.zmdl[k - 1];
				goto L24;
			}
			if (ic1 == 2)
			{
				goto L20;
			}
			if (icld1 == card2d_1.iregc[2])
			{
				n = 13;
				card2d_1.altb[2] = model_2.zmdl[k - 1];
				goto L24;
			}
		}
		else
		{
			if (iha1 == 0 && icld1 == 0)
			{
				if (zsc > 2.f)
				{
					ityaer = 6;
				}
				if (zsc > 10.f)
				{
					ityaer = card2_1.ivulcn + 10;
				}
				if (zsc > 30.f)
				{
					ityaer = 19;
				}
			}
			if (ityaer == _BLNK__2.ich[0])
			{
				n = 7;
				card2d_1.altb[0] = model_2.zmdl[k - 1];
				goto L24;
			}
			if (ic1 == 1)
			{
				goto L20;
			}
			if (ityaer == _BLNK__2.ich[1])
			{
				n = 12;
				card2d_1.altb[1] = model_2.zmdl[k - 1];
				goto L24;
			}
			if (ic1 == 2)
			{
				goto L20;
			}
			if (ityaer == _BLNK__2.ich[2])
			{
				n = 13;
				card2d_1.altb[2] = model_2.zmdl[k - 1];
				goto L24;
			}
		}
	L20:
		++ic1;
		/*                                                                       ANS 5240 */
		/*                                                                       ANS 5250 */
		/*                                                                       ANS 5260 */
		n = ic1 + 10;
		if (rh > 0.f)
		{
			mart_1.rhh = rh;
		}
		if (ic1 <= 4)
		{
			goto L23;
		}
		ic1 = 4;
		n = 14;
		ityaer = _BLNK__2.ich[ic1 - 1];
	L23:
		_BLNK__2.ich[ic1 - 1] = ityaer;
		card2d_1.iregc[ic1 - 1] = icld1;
		card2d_1.altb[ic1 - 1] = model_2.zmdl[k - 1];
	/*                                                                       ANS 5360 */
	/*     FOR LVSA OR CLD OR RAIN ONLY                                      ANS 5370 */
	/*                                                                       ANS 5380 */
	L24:
		if (rh > 0.f)
		{
			ta = t0 / mdata_1.t[k - 1];
			mdata_1.wh[k - 1] = exp(18.9766f - 14.9595f * ta - 2.43882f * ta * ta) * ta * .01f * rh;
			/*                                                                       ANS 5420 */
		}
		/* L40: */
		model_2.densty[k * 63 - 57] = 0.f;
		model_2.densty[k * 63 - 52] = 0.f;
		model_2.densty[k * 63 - 51] = 0.f;
		model_2.densty[k * 63 - 50] = 0.f;
		model_2.densty[k * 63 - 49] = 0.f;
		ts = 273.15f / mdata_1.t[k - 1];
		wtemp = mdata_1.wh[k - 1];
		_BLNK__2.relhum[k - 1] = 0.f;
		if (wtemp <= 0.f)
		{
			goto L45;
		}
		_BLNK__2.relhum[k - 1] = wtemp * 100.f / (exp(18.9766f - 14.9595f * ts - 2.43882f * ts * ts) * ts);
		if (_BLNK__2.relhum[k - 1] > 100.f)
		{
			io___212.ciunit = ifil_1.ipr;
			s_wsfe(&io___212);
			do_fio(&c__1, (char *)&_BLNK__2.relhum[k - 1], (long)sizeof(float));
			do_fio(&c__1, (char *)&model_2.zmdl[k - 1], (long)sizeof(float));
			e_wsfe();
		}
		if (_BLNK__2.relhum[k - 1] > 100.f)
		{
			_BLNK__2.relhum[k - 1] = 100.f;
		}
		if (_BLNK__2.relhum[k - 1] < 0.f)
		{
			io___213.ciunit = ifil_1.ipr;
			s_wsfe(&io___213);
			do_fio(&c__1, (char *)&_BLNK__2.relhum[k - 1], (long)sizeof(float));
			do_fio(&c__1, (char *)&model_2.zmdl[k - 1], (long)sizeof(float));
			e_wsfe();
		}
		if (_BLNK__2.relhum[k - 1] < 0.f)
		{
			_BLNK__2.relhum[k - 1] = 0.f;
		}
	L45:
		mart_1.rhh = _BLNK__2.relhum[k - 1];
		rh = mart_1.rhh;
		if (vis1 <= 0.f)
		{
			vis1 = card2_1.vis;
		}
		if (ahaze == 0.f)
		{
			goto L47;
		}
		model_2.densty[n + k * 63 - 64] = ahaze;
		if (ityaer == 3)
		{
			goto L47;
		}
		if (ityaer == 10)
		{
			goto L47;
		}
		/*     AHAZE IS IN LOWTRAN NUMBER DENSTY UNITS                           ANS 5670 */
		goto L50;
	L47:
		/*                                                                       ANS 5700 */
		/*     AHAZE NOT INPUT OR NAVY MARITIME MODEL IS CALLED                  ANS 5710 */
		/*                                                                       ANS 5720 */
		/*     CHECK IF GNDALT NOT ZERO                                          ANS 5730 */
		/*                                                                       ANS 5740 */
		if (*gndalt > 0.f && model_2.zmdl[k - 1] < 6.f)
		{
			j = (long)(zsc + 1e-6f) + 1;
			fac = zsc - (float)(j - 1);
		}
		else
		{
			j = (long)(model_2.zmdl[k - 1] + 1e-6f) + 1;
			if (model_2.zmdl[k - 1] >= 25.f)
			{
				j = (model_2.zmdl[k - 1] - 25.f) / 5.f + 26.f;
			}
			if (model_2.zmdl[k - 1] >= 50.f)
			{
				j = (model_2.zmdl[k - 1] - 50.f) / 20.f + 31.f;
			}
			if (model_2.zmdl[k - 1] >= 70.f)
			{
				j = (model_2.zmdl[k - 1] - 70.f) / 30.f + 32.f;
			}
			if (j > 32)
			{
				j = 32;
			}
			fac = model_2.zmdl[k - 1] - (float)(j - 1);
			if (j < 26)
			{
				goto L125;
			}
			fac = (model_2.zmdl[k - 1] - (float)(j - 26) * 5.f - 25.f) / 5.f;
			if (j >= 31)
			{
				fac = (model_2.zmdl[k - 1] - 50.f) / 20.f;
			}
			if (j >= 32)
			{
				fac = (model_2.zmdl[k - 1] - 70.f) / 30.f;
			}
		}
	L125:
		l = j + 1;
		if (fac > 1.f)
		{
			fac = 1.f;
		}
		if (ityaer == 3 && icl == 0)
		{
			marine_(&vis1, &card1_1.model, &card2_1.wss, &card2_1.whh, &card2_1.icstl, _BLNK__2.extc, _BLNK__2.absc, &ic1);
			card2d_1.ireg[ic1 - 1] = 1;
			card2_1.vis = vis1;
			++icl;
		}
		if (ityaer == 10 && idsr == 0)
		{
			desatt_(&card2_1.wss, &vis1);
			card2d_1.ireg[ic1 - 1] = 1;
			card2_1.vis = vis1;
			++idsr;
		}
		if (ahaze > 0.f)
		{
			goto L50;
		}
		if (iha1 <= 0)
		{
			iha1 = card2_1.ihaze;
		}
		cldprf_(&k, &icld1, &iha1, &ic1);
		aerprf_(&j, &vis1, &haz1, &iha1, &isea1, &ivul1, &nn);
		aerprf_(&l, &vis1, &haz2, &iha1, &isea1, &ivul1, &nn);
		haze = 0.f;
		if (haz1 <= 0.f || haz2 <= 0.f)
		{
			goto L48;
		}
		d__1 = (double)(haz2 / haz1);
		d__2 = (double)fac;
		haze = haz1 * pow_dd(&d__1, &d__2);
	L48:
		if (model_2.cldamt[k - 1] > 0.f)
		{
			haze = model_2.hazec[k - 1];
		}
		model_2.densty[n + k * 63 - 64] = haze;
	L50:
		ity1[k - 1] = ityaer;
		ih1[k - 1] = iha1;
		if (ahaze != 0.f)
		{
			ih1[k - 1] = -99;
		}
		is1[k - 1] = isea1;
		ivl1[k - 1] = ivul1;
		/* L100: */
	}
	/*                                                                       ANS 6220 */
	/*     END OF LOOP                                                       ANS 6230 */
	/*                                                                       ANS 6240 */
	ihh = card2_1.icld;
	if (ihh <= 0)
	{
		ihh = 12;
	}
	if (ihh > 12)
	{
		ihh = 12;
	}
	if (card2_1.icld >= 18)
	{
		ihh = 13;
	}
	for (ii = 1; ii <= 5; ++ii)
	{
		s_copy(hhol + ((ii - 1) << 2), ahahol + ((ii + ihh * 5 - 6) << 2), (long)4, (long)4);
		if (card2_1.ivsa != 0)
		{
			s_copy(hhol + ((ii - 1) << 2), ahlvsa + ((ii - 1) << 2), (long)4, (long)4);
		}
		/* L105: */
	}
	if (card2_1.icld != 0)
	{
		if (*jprt == 0)
		{
			io___227.ciunit = ifil_1.ipr;
			s_wsfe(&io___227);
			do_fio(&c__5, hhol, (long)4);
			e_wsfe();
		}
	}
	if (*jprt == 0)
	{
		io___228.ciunit = ifil_1.ipr;
		s_wsfe(&io___228);
		e_wsfe();
	}
	/*                                                                       ANS 6380 */
	if (*jprt == 1)
	{
		return 0;
	}
	i__1 = cntrl_1.ml;
	for (kk = 1; kk <= i__1; ++kk)
	{
		for (ij = 1; ij <= 5; ++ij)
		{
			s_copy(ahol1 + ((ij - 1) << 2), titl_2.blank, (long)4, (long)4);
			s_copy(ahol2 + ((ij - 1) << 2), titl_2.blank, (long)4, (long)4);
			/* L52: */
			s_copy(ahol3 + ((ij - 1) << 2), titl_2.blank, (long)4, (long)4);
		}
		ityaer = ity1[kk - 1];
		if (ityaer <= 0)
		{
			ityaer = 1;
		}
		if (ityaer == 16)
		{
			ityaer = 11;
		}
		if (ityaer == 17)
		{
			ityaer = 11;
		}
		if (ityaer == 18)
		{
			ityaer = 13;
		}
		if (ityaer == 19)
		{
			ityaer = 11;
		}
		iha1 = ih1[kk - 1];
		isea1 = is1[kk - 1];
		ivul1 = ivl1[kk - 1];
		for (ij = 1; ij <= 5; ++ij)
		{
			s_copy(ahol1 + ((ij - 1) << 2), titl_2.hz + ((ij + ityaer * 5 - 6) << 2), (long)4, (long)4);
			if (card2_1.ivsa == 1)
			{
				s_copy(ahol1 + ((ij - 1) << 2), hhol + ((ij - 1) << 2), (long)4,
					   (long)4);
			}
			if (model_2.cldamt[kk - 1] > 0.f || model_2.rramt[kk - 1] > 0.f)
			{
				s_copy(ahol1 + ((ij - 1) << 2), hhol + ((ij - 1) << 2), (long)4,
					   (long)4);
			}
			if (card2_1.ihaze == 0)
			{
				s_copy(ahol1 + ((ij - 1) << 2), hhol + ((ij - 1) << 2), (long)4,
					   (long)4);
			}
			s_copy(ahol2 + ((ij - 1) << 2), ahus + ((ij - 1) << 2), (long)4, (long)4);
			if (ahast[kk - 1] == 0.f)
			{
				s_copy(ahol2 + ((ij - 1) << 2), ahol1 + ((ij - 1) << 2), (long)4, (long)4);
			}
			if (model_2.cldamt[kk - 1] > 0.f || model_2.rramt[kk - 1] > 0.f)
			{
				s_copy(ahol2 + ((ij - 1) << 2), hhol + ((ij - 1) << 2), (long)4,
					   (long)4);
			}
			/* L54: */
			if (zgn[kk - 1] > 2.f)
			{
				s_copy(ahol3 + ((ij - 1) << 2), titl_2.seasn + ((ij + isea1 * 5 - 6) << 2), (long)4, (long)4);
			}
		}
		/* L60: */
		io___234.ciunit = ifil_1.ipr;
		s_wsfe(&io___234);
		do_fio(&c__1, (char *)&model_2.zmdl[kk - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&mdata_1.p[kk - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&mdata_1.t[kk - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&_BLNK__2.relhum[kk - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&mdata_1.wh[kk - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_2.cldamt[kk - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_2.rramt[kk - 1], (long)sizeof(float));
		do_fio(&c__5, ahol1, (long)4);
		do_fio(&c__5, ahol2, (long)4);
		do_fio(&c__5, ahol3, (long)4);
		e_wsfe();
	}
	return 0;
	/*                                                                       ANS 6710 */
} /* aernsm_ */

/* Subroutine */ int rdexa_(void)
{
	/* Format strings */
	static char fmt_1200[] = "(4i5)";
	static char fmt_1210[] = "(\0020 CARD 2D *****\002,4i5)";
	static char fmt_1220[] = "(e10.3,18a4)";
	static char fmt_1230[] = "(\0020 CARD 2D1 **** EQUIVALENT WATER = \002,1"
							 "pe10.3,18a4)";
	static char fmt_1250[] = "(\0020 CARD 2D2 ****\002)";
	static char fmt_1260[] = "(3(f6.2,2f7.5,f6.4))";
	static char fmt_1270[] = "(2x,f6.2,2f7.5,f6.4,f6.2,2f7.5,f6.4,f6.2,2f7.5"
							 ",f6.4)";

	/* Builtin functions */
	long s_rsfe(cilist *), do_fio(long *, char *, long), e_rsfe(void),
		s_wsfe(cilist *), e_wsfe(void);

	/* Local variables */
	static long i__, ik;
	static float vx[47];
	static long ihc;
	static float title[18];

	/* Fortran I/O blocks */
	static cilist io___235 = {0, 0, 0, fmt_1200, 0};
	static cilist io___237 = {0, 0, 0, fmt_1210, 0};
	static cilist io___239 = {0, 0, 0, fmt_1220, 0};
	static cilist io___241 = {0, 0, 0, fmt_1230, 0};
	static cilist io___242 = {0, 0, 0, fmt_1250, 0};
	static cilist io___243 = {0, 0, 0, fmt_1260, 0};
	static cilist io___246 = {0, 0, 0, fmt_1270, 0};

	/*                                                                       RDE  110 */
	/*     READ IN USER DEFINED EXTINCTION ABSORPTION COEFFICIENTS AND       RDE  120 */
	/*     ASYMMETRY PARAMETERS                                              RDE  130 */
	/*                                                                       RDE  140 */
	/*                                                                       RDE  210 */
	PRINT_LINE_READ()
#ifdef DO_FIO_IN
	io___235.ciunit = ifil_1.ird;
	s_rsfe(&io___235);
	for (ik = 1; ik <= 4; ++ik)
	{
		do_fio(&c__1, (char *)&card2d_1.ireg[ik - 1], (long)sizeof(long));
	}
	e_rsfe();
#endif
	io___237.ciunit = ifil_1.ipr;
	s_wsfe(&io___237);
	for (ik = 1; ik <= 4; ++ik)
	{

		do_fio(&c__1, (char *)&card2d_1.ireg[ik - 1], (long)sizeof(long));
	}
	e_wsfe();

	/*                                                                       RDE  260 */
	for (ihc = 1; ihc <= 4; ++ihc)
	{
		/*                                                                       RDE  280 */
		if (card2d_1.ireg[ihc - 1] == 0)
		{
			goto L1300;
		}
		PRINT_LINE_READ()
#ifdef DO_FIO_IN
		io___239.ciunit = ifil_1.ird;

		s_rsfe(&io___239);
		do_fio(&c__1, (char *)&_BLNK__1.awccon[ihc - 1], (long)sizeof(float));
		do_fio(&c__18, (char *)&title[0], (long)sizeof(float));
		e_rsfe();
#endif
		io___241.ciunit = ifil_1.ipr;
		s_wsfe(&io___241);
		do_fio(&c__1, (char *)&_BLNK__1.awccon[ihc - 1], (long)sizeof(float));
		do_fio(&c__18, (char *)&title[0], (long)sizeof(float));
		e_wsfe();
		io___242.ciunit = ifil_1.ipr;
		s_wsfe(&io___242);
		e_wsfe();
		/*                                                                       RDE  360 */
		PRINT_LINE_READ()
#ifdef DO_FIO_IN
		io___243.ciunit = ifil_1.ird;

		s_rsfe(&io___243);
		for (i__ = 1; i__ <= 47; ++i__)
		{
			do_fio(&c__1, (char *)&vx[i__ - 1], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.extc[ihc + i__ * 5 - 6], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.absc[ihc + i__ * 5 - 6], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.asym[ihc + i__ * 5 - 6], (long)sizeof(float));
		}
		e_rsfe();
#endif
		io___246.ciunit = ifil_1.ipr;
		s_wsfe(&io___246);
		for (i__ = 1; i__ <= 47; ++i__)
		{
			do_fio(&c__1, (char *)&vx[i__ - 1], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.extc[ihc + i__ * 5 - 6], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.absc[ihc + i__ * 5 - 6], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.asym[ihc + i__ * 5 - 6], (long)sizeof(float));
		}
		e_wsfe();
	L1300:;
	}
	return 0;
} /* rdexa_ */

/* Subroutine */ int cirr18_(void)
{
	/* Initialized data */

	static float camean[5] = {11.f, 10.f, 8.f, 7.f, 5.f};
	static struct
	{
		float e_1[10];
	} equiv_1 = {7.5f, 7.3f, 4.5f, 4.5f, 2.5f, 16.5f, 13.5f, 14.f, 9.5f,
				 10.f};

	/* Format strings */
	static char fmt_1219[] = "(15x,\002CIRRUS ATTENUATION INCLUDED   (STANDA"
							 "RD CIRRUS)\002)";
	static char fmt_1220[] = "(15x,\002CIRRUS ATTENUATION INCLUDED   (THIN  "
							 "   CIRRUS)\002)";
	static char fmt_1221[] = "(15x,\002CIRRUS THICKNESS \002,f10.3,\002KM"
							 "\002)";
	static char fmt_1224[] = "(15x,\002CIRRUS BASE ALTITUDE \002,f10.3,\002 "
							 "KM\002)";
	static char fmt_1226[] = "(15x,\002CIRRUS PROFILE EXTINCT \002,f10.3)";

	/* Builtin functions */
	long s_wsfe(cilist *), e_wsfe(void), do_fio(long *, char *, long);

	/* Local variables */
	static long mdl;
	static float hmax;
#define cbase ((float *)&equiv_1)
#define cbase1 ((float *)&equiv_1)
#define cbase2 ((float *)&equiv_1 + 5)

	/* Fortran I/O blocks */
	static cilist io___255 = {0, 0, 0, fmt_1219, 0};
	static cilist io___256 = {0, 0, 0, fmt_1220, 0};
	static cilist io___257 = {0, 0, 0, fmt_1221, 0};
	static cilist io___258 = {0, 0, 0, fmt_1224, 0};
	static cilist io___259 = {0, 0, 0, fmt_1226, 0};

	/* *********************************************************************  C18  110 */
	/* *  ROUTINE TO SET CTHIK CALT CEXT  FOR  CIRRUS CLOUDS 18 19        **  C18  120 */
	/* *  INPUTS]                                                         **  C18  130 */
	/* *           CHTIK    -  CIRRUS THICKNESS (KM)                      **  C18  140 */
	/* *                       0 = USE THICKNESS STATISTICS               **  C18  150 */
	/* *                       .NE. 0 = USER DEFINES THICKNESS            **  C18  160 */
	/* *                                                                  **  C18  170 */
	/* *           CALT     -  CIRRUS BASE ALTITUDE (KM)                  **  C18  180 */
	/* *                       0 = USE CALCULATED VALUE                   **  C18  190 */
	/* *                       .NE. 0 = USER DEFINES BASE ALTITUDE        **  C18  200 */
	/* *                                                                  **  C18  210 */
	/* *           ICLD     -  CIRRUS PRESENCE FLAG                       **  C18  220 */
	/* *                       0 = NO CIRRUS                              **  C18  230 */
	/* *                       18  19 = USE CIRRUS PROFILE                **  C18  240 */
	/* *                                                                  **  C18  250 */
	/* *           MODEL    -  ATMOSPHERIC MODEL                          **  C18  260 */
	/* *                       1-5  AS IN MAIN PROGRAM                    **  C18  270 */
	/* *                       MODEL = 0,6,7 NOT USED SET TO 2            **  C18  280 */
	/* *                                                                  **  C18  290 */
	/* *  OUTPUTS]                                                        **  C18  300 */
	/* *         CTHIK        -  CIRRUS THICKNESS (KM)                    **  C18  310 */
	/* *         CALT         -  CIRRUS BASE ALTITUDE (KM)                **  C18  320 */
	/*          CEXT IS THE EXTINCTION COEFFIENT(KM-1) AT 0.55               C18  330 */
	/*               DEFAULT VALUE 0.14*CTHIK                                C18  340 */
	/* *                                                                  **  C18  350 */
	/* *********************************************************************  C18  360 */
	/*                                                                       C18  370 */
	/*                                                                       C18  520 */
	mdl = card1_1.model;
	/*                                                                       C18  600 */
	/*  CHECK IF USER WANTS TO USE A THICKNESS VALUE HE PROVIDES             C18  610 */
	/*  DEFAULTED MEAN CIRRUS THICKNESS IS 1.0KM  OR 0.2 KM.                 C18  620 */
	/*                                                                       C18  630 */
	if (card2a_1.cthik > 0.f)
	{
		goto L25;
	}
	if (card2_1.icld == 18)
	{
		card2a_1.cthik = 1.f;
	}
	if (card2_1.icld == 19)
	{
		card2a_1.cthik = .2f;
	}
L25:
	if (card2a_1.cext == 0.f)
	{
		card2a_1.cext = card2a_1.cthik * .14f;
	}
	/*                                                                       C18  680 */
	/*  BASE HEIGHT CALCULATIONS                                             C18  690 */
	/*                                                                       C18  700 */
	if (card1_1.model < 1 || card1_1.model > 5)
	{
		mdl = 2;
	}
	/*                                                                       C18  720 */
	hmax = cbase[mdl + 4] - card2a_1.cthik;
	/*     BRANGE = HMAX - CBASE(MDL,1)                                      C18  740 */
	if (card2a_1.calt > 0.f)
	{
		goto L27;
	}
	card2a_1.calt = camean[mdl - 1];
/*                                                                       C18  770 */
L27:
	if (card2_1.icld == 18)
	{
		io___255.ciunit = ifil_1.ipr;
		s_wsfe(&io___255);
		e_wsfe();
	}
	if (card2_1.icld == 19)
	{
		io___256.ciunit = ifil_1.ipr;
		s_wsfe(&io___256);
		e_wsfe();
	}
	io___257.ciunit = ifil_1.ipr;
	s_wsfe(&io___257);
	do_fio(&c__1, (char *)&card2a_1.cthik, (long)sizeof(float));
	e_wsfe();
	io___258.ciunit = ifil_1.ipr;
	s_wsfe(&io___258);
	do_fio(&c__1, (char *)&card2a_1.calt, (long)sizeof(float));
	e_wsfe();
	io___259.ciunit = ifil_1.ipr;
	s_wsfe(&io___259);
	do_fio(&c__1, (char *)&card2a_1.cext, (long)sizeof(float));
	e_wsfe();
	/*                                                                       C18  900 */
	/*       END OF CIRRUS MODEL SET UP                                      C18  910 */
	return 0;
} /* cirr18_ */

#undef cbase2
#undef cbase1
#undef cbase

/* Subroutine */ int desatt_(float *wspd, float *vis)
{
	/* Initialized data */

	static float wind[4] = {0.f, 10.f, 20.f, 30.f};
	static float raysct = .01159f;

	/* Format strings */
	static char fmt_999[] = "(\002 WARNING: WIND SPEED IS BEYOND 30 M/S; RAD"
							"IATIVE\002,\002PROPERTIES\002,/,\002OF THE DESERT AEROSOL HAVE B"
							"EEN EXTRAPOLATED\002)";
	static char fmt_900[] = "(//,\002  VIS = \002,f10.3,\002 WIND = \002,f10"
							".3)";

	/* Builtin functions */
	long s_wsfe(cilist *), e_wsfe(void);
	double log(double), exp(double);
	long do_fio(long *, char *, long);

	/* Local variables */
	static float b, desg[47], ext55;
	static long wavel;
	static float slope;
	static long nwspd;
	static float desabs[47], dessca[47], desext[47];

	/* Fortran I/O blocks */
	static cilist io___263 = {0, 6, 0, fmt_999, 0};
	static cilist io___272 = {0, 6, 0, fmt_900, 0};

	/* ********************************************************************** DES  110 */
	/* *                                                                    * DES  120 */
	/* *    THIS SUBROUTINE CALCULATES THE ATTENUATION COEFFICIENTS AND     * DES  130 */
	/* *    ASYMMETRY PARAMETER FOR THE DESERT AEROSOL BASED ON THE WIND    * DES  140 */
	/* *    SPEED AND METEOROLOGICAL RANGE                                  * DES  150 */
	/* *                                                                    * DES  160 */
	/* *                                                                    * DES  170 */
	/* *                                                                    * DES  180 */
	/* *    PROGRAMMED BY:  D. R. LONGTIN         OPTIMETRICS, INC.         * DES  190 */
	/* *                                          BURLINGTON, MASSACHUSETTS * DES  200 */
	/* *                                          JULY 1987                 * DES  210 */
	/* *                                                                    * DES  220 */
	/* *                                                                    * DES  230 */
	/* *    INPUTS:    WSPD    -  WIND SPEED (IN M/S) AT 10 M               * DES  240 */
	/* *               VIS     -  METEOROLOGICAL RANGE (KM)                 * DES  250 */
	/* *                                                                    * DES  260 */
	/* *    OUTPUTS:   DESEXT  -  EXTINCTION COEFFICIENT AT 47 WAVELENGTHS  * DES  270 */
	/* *               DESSCA  -  SCATTERING COEFFICIENT AT 47 WAVELENGTHS  * DES  280 */
	/* *    *****      DESABS  -  ABSORPTION COEFFICIENT AT 47 WAVELENGTHS  * DES  290 */
	/* *               DESG    -  ASYMMETRY PARAMETER AT 47 WAVELENGTHS     * DES  300 */
	/* *                                                                    * DES  310 */
	/* ********************************************************************** DES  320 */
	/*                                                                       DES  330 */
	if (*wspd < 0.f)
	{
		*wspd = 10.f;
	}
	/*                                                                       DES  440 */
	nwspd = (long)(*wspd / 10) + 1;
	if (nwspd >= 5)
	{
		s_wsfe(&io___263);
		e_wsfe();
	}
	if (nwspd >= 4)
	{
		nwspd = 3;
	}
	/*                                                                       DES  480 */
	/*     INTERPOLATE THE RADIATIVE PROPERTIES AT WIND SPEED WSPD           DES  490 */
	/*                                                                       DES  500 */
	for (wavel = 1; wavel <= 47; ++wavel)
	{
		/*                                                                       DES  520 */
		/*     EXTINCTION COEFFICIENT                                            DES  530 */
		/*                                                                       DES  540 */
		slope = log(desaer_1.ext[wavel + (nwspd + 1) * 47 - 48] /
					desaer_1.ext[wavel + nwspd * 47 - 48]) /
				(wind[nwspd] - wind[nwspd - 1]);
		b = log(desaer_1.ext[wavel + (nwspd + 1) * 47 - 48]) - slope * wind[nwspd];
		desext[wavel - 1] = exp(slope * *wspd + b);
		/*                                                                       DES  590 */
		/*     ABSORPTION COEFFICIENT                                            DES  600 */
		/*                                                                       DES  610 */
		slope = log(desaer_1.abs__[wavel + (nwspd + 1) * 47 - 48] /
					desaer_1.abs__[wavel + nwspd * 47 - 48]) /
				(wind[nwspd] -
				 wind[nwspd - 1]);
		b = log(desaer_1.abs__[wavel + (nwspd + 1) * 47 - 48]) - slope * wind[nwspd];
		desabs[wavel - 1] = exp(slope * *wspd + b);
		/*                                                                       DES  660 */
		/*     SCATTERING COEFFICIENT                                            DES  670 */
		/*                                                                       DES  680 */
		dessca[wavel - 1] = desext[wavel - 1] - desabs[wavel - 1];
		/*                                                                       DES  700 */
		/*     ASYMMETRY PARAMETER                                               DES  710 */
		/*                                                                       DES  720 */
		slope = (desaer_1.g[wavel + (nwspd + 1) * 47 - 48] - desaer_1.g[wavel + nwspd * 47 - 48]) / (wind[nwspd] - wind[nwspd - 1]);
		b = desaer_1.g[wavel + (nwspd + 1) * 47 - 48] - slope * wind[nwspd];
		desg[wavel - 1] = slope * *wspd + b;
		/* L100: */
	}
	/*                                                                       DES  780 */
	ext55 = desext[3];
	/*                                                                       DES  800 */
	/*         DETERMINE METEROLOGICAL RANGE FROM 0.55 EXTINCTION            DES  810 */
	/*          AND KOSCHMIEDER FORMULA                                      DES  820 */
	/*                                                                       DES  830 */
	if (*vis <= 0.f)
	{
		*vis = 3.912f / (desext[3] + raysct);
	}
	/*                                                                       DES  870 */
	/*        RENORMALIZE ATTENUATION COEFFICIENTS TO 1.0 KM-1 AT            DES  880 */
	/*        0.55 MICRONS FOR CAPABILTY WITH LOWTRAN                        DES  890 */
	/*                                                                       DES  900 */
	for (wavel = 1; wavel <= 47; ++wavel)
	{
		_BLNK__2.extc[wavel * 5 - 5] = desext[wavel - 1] / ext55;
		/* C          DESSCA(WAVEL) = DESSCA(WAVEL)       /EXT55                  DES  930 */
		_BLNK__2.absc[wavel * 5 - 5] = desabs[wavel - 1] / ext55;
		_BLNK__2.asym[wavel * 5 - 5] = desg[wavel - 1];
		/* L200: */
	}
	s_wsfe(&io___272);
	do_fio(&c__1, (char *)&(*vis), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*wspd), (long)sizeof(float));
	e_wsfe();
	return 0;
	/*                                                                       DES 1000 */
} /* desatt_ */

/* Subroutine */ int dstdta_(void)
{
	return 0;
} /* dstdta_ */

/* >    BLOCK DATA                                                        DST  105 */
/* ********************************************************************** DST  110 */
/* *                                                                    * DST  120 */
/* *    DESERT AEROSOL EXTINCTION COEFFICIENTS, ABSORPTION COEFFICIENTS * DST  130 */
/* *    AND ASYMMETRY PARAMETERS FOR FOUR WIND SPEEDS: 0 M/S, 10 M/S,   * DST  140 */
/* *    20 M/S AND 30 M/S                                               * DST  150 */
/* *                                                                    * DST  160 */
/* *    PROGRAMMED BY:  D. R. LONGTIN         OPTIMETRICS, INC.         * DST  170 */
/* *                                          BURLINGTON, MASSACHUSETTS * DST  180 */
/* *                                          FEB  1988                 * DST  190 */
/* *                                                                    * DST  200 */
/* ********************************************************************** DST  210 */
/*                                                                       DST  220 */
/*                                                                       DST  260 */
/*     EXTINCTION COEFFICIENTS                                           DST  270 */
/*                                                                       DST  280 */
/*                                                                       DST  650 */
/*     ABSORPTION COEFFICIENTS                                           DST  660 */
/*                                                                       DST  670 */
/*                                                                       DST 1040 */
/*     ASYMMETRY PARAMETER                                               DST 1050 */
/*                                                                       DST 1060 */

/* Subroutine */ int flayz_(long *ml, long *model, long *icld, float *zmdl, float *gndalt, long *ivsa)
{
	/* Initialized data */

	static float zcld[16] = {0.f, .16f, .33f, .66f, 1.f, 1.5f, 2.f, 2.4f, 2.7f, 3.f,
							 3.5f, 4.f, 4.5f, 5.f, 5.5f, 6.f};
	static float znewv[24] = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f,
							  12.f, 14.f, 16.f, 18.f, 20.f, 22.f, 25.f, 30.f, 35.f, 40.f, 50.f, 70.f, 100.f};
	static float znew[17] = {7.f, 8.f, 9.f, 10.f, 12.f, 14.f, 16.f, 18.f, 20.f, 22.f,
							 25.f, 30.f, 35.f, 40.f, 50.f, 70.f, 100.f};
	static float zaer[34] = {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f,
							 11.f, 12.f, 13.f, 14.f, 15.f, 16.f, 17.f, 18.f, 19.f, 20.f, 21.f, 22.f, 23.f,
							 24.f, 25.f, 30.f, 35.f, 40.f, 45.f, 50.f, 70.f, 100.f, 1e3f};

	/* System generated locals */
	long i__1;

	/* Local variables */
	static long i__, j, k, ii, ij, ik, il, ml1;
	static float zk1, zst[34], cld0, cld1, cld2, cld3, cldd;
	static long mdel;
	static float dalt;
	static long ijii;
	static float hmxvsa;

	/*                                                                       FLA  110 */
	/*     SUBROUTINE TO CREATE FINAL LOWTRAN BOUNDARIES                     FLA  120 */
	/*                                                                       FLA  130 */
	/*     ZMDL COMMON /MODEL/ FINAL ALTITUDE FOR LOWTRAN                    FLA  140 */
	/*     ZCLD CLOUD ALTITUDE                                               FLA  150 */
	/*     ZK1 USED WITH VSA                                                 FLA  160 */
	/*     ZNEW ALTITUDES ABOVE THE CLOUD                                    FLA  170 */
	/*     ZNEWV ALTITUDES ABOVE THE 1ST 9 VSA ALTITUDES                     FLA  180 */
	/*     ZTST  =ZCLD(J)                                                    FLA  190 */
	/*     ZVSA  VSA ALTITUDES                                               FLA  200 */
	/*                                                                       FLA  210 */
	/* Parameter adjustments */
	--zmdl;

	/* Function Body */
	if (*model == 7)
	{
		goto L600;
	}
	/*                                                                       FLA  380 */
	if (*model == 0)
	{
		goto L600;
	}
	if (*ivsa == 1)
	{
		for (i__ = 1; i__ <= 9; ++i__)
		{
			/* L2: */
			zmdl[i__] = zvsaly_1.zvsa[i__ - 1];
		}
		/*                                                                       FLA  430 */
		hmxvsa = zvsaly_1.zvsa[8];
		zk1 = hmxvsa + .01f;
		if (hmxvsa < 2.f)
		{
			*ml = 33;
		}
		if (hmxvsa < 1.f)
		{
			*ml = 34;
		}
		if (hmxvsa == 2.f)
		{
			*ml = 32;
		}
		mdel = 34 - *ml;
		i__1 = *ml;
		for (k = 1; k <= i__1; ++k)
		{
			ik = k - 10 + mdel;
			if (ik >= 1)
			{
				zmdl[k] = znewv[ik - 1];
			}
			if (k == 10)
			{
				zmdl[k] = zk1;
			}
			/* L4: */
		}
		/*                                                                       FLA  550 */
		return 0;
	}
	/*                                                                       FLA  580 */
	if (*icld >= 1 && *icld <= 11)
	{
		goto L18;
	}
	i__1 = *ml;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		if (zaer[i__ - 1] > 100.f)
		{
			goto L12;
		}
		il = i__;
		/* L10: */
		zmdl[i__] = zaer[i__ - 1];
	}
L12:
	*ml = il;
	/*     IF(IEMSCT.NE.0) ZMDL(ML)=100.                                     FLA  650 */
	/*                                                                       FLA  660 */
	if (*gndalt <= 0.f)
	{
		goto L90;
	}
	dalt = (6.f - *gndalt) / 6.f;
	if (dalt <= 0.f)
	{
		goto L90;
	}
	/*                                                                       FLA  700 */
	for (i__ = 1; i__ <= 6; ++i__)
	{
		/* L15: */
		zmdl[i__] = (float)(i__ - 1) * dalt + *gndalt;
	}
L90:
	if (*icld == 18 || *icld == 19)
	{
		cldd = card2a_1.cthik * .1f;
		cld0 = card2a_1.calt - cldd * .5f;
		if (cld0 <= 0.f)
		{
			cld0 = 0.f;
		}
		cld1 = cld0 + cldd;
		cld2 = cld1 + card2a_1.cthik - cldd;
		cld3 = cld2 + cldd;
		i__1 = *ml;
		for (i__ = 1; i__ <= i__1; ++i__)
		{
			ij = i__;
			if (zmdl[i__] < cld0)
			{
				goto L100;
			}
			goto L120;
		L100:;
		}
		goto L600;
	L120:
		ml1 = *ml - ij;
		i__1 = ml1;
		for (i__ = 1; i__ <= i__1; ++i__)
		{
			/* L130: */
			zst[i__ - 1] = zmdl[ij + i__ - 1];
		}
		zmdl[ij] = cld0;
		zmdl[ij + 1] = cld1;
		zmdl[ij + 2] = cld2;
		zmdl[ij + 3] = cld3;
		ii = 3;
		i__1 = ml1;
		for (i__ = 1; i__ <= i__1; ++i__)
		{
			if (zst[i__ - 1] < cld3)
			{
				goto L140;
			}
			++ii;
			if (ij + ii == *ml)
			{
				goto L145;
			}
			zmdl[ij + ii] = zst[i__ - 1];
			ijii = ij + ii;
		L140:;
		}
		*ml = ijii + 1;
	L145:
		zmdl[*ml] = 100.f;
	}
	goto L600;
/*                                                                       FLA 1020 */
/*     STAND CLOUD                                                       FLA 1030 */
/*                                                                       FLA 1040 */
L18:
	for (i__ = 1; i__ <= 16; ++i__)
	{
		/* L20: */
		zmdl[i__] = zcld[i__ - 1] + *gndalt;
	}
	i__ = 16;
	/*                                                                       FLA 1080 */
	i__1 = *ml;
	for (k = 17; k <= i__1; ++k)
	{
		j = k - 16;
		if (znew[j - 1] <= zmdl[16])
		{
			goto L30;
		}
		++i__;
		zmdl[i__] = znew[j - 1];
	L30:;
	}
	*ml = i__;
	goto L600;
/*                                                                       FLA 1170 */
/*     MODEL 7                                                           FLA 1180 */
L600:
	return 0;
} /* flayz_ */

/* Subroutine */ int convrt_(float *p, float *t)
{

	/* Format strings */
	static char fmt_951[] = "(/,\002   **** ERROR IN CONVERT ****, JUNIT ="
							" \002,i5)";

	/* Builtin functions */
	long s_wsfe(cilist *), do_fio(long *, char *, long), e_wsfe(void);
	/* Subroutine */ int s_stop(char *, long);

	/* Local variables */
	static float b;
	static long k;
	static float r__, wtem, wmol;
	static long junit;
	static float rhoair;
	extern /* Subroutine */ int watvap_(const float *, const float *);

	/* Fortran I/O blocks */
	static cilist io___307 = {0, 0, 0, fmt_951, 0};

	/* *************************************************************          COV  110 */
	/*                                                                       COV  120 */
	/*        WRITTEN APR, 1985 TO ACCOMMODATE 'JCHAR' DEFINITIONS FOR       COV  130 */
	/*        UNIFORM DATA INPUT -                                           COV  140 */
	/*                                                                       COV  150 */
	/*      JCHAR    JUNIT                                                   COV  160 */
	/*                                                                       COV  170 */
	/*    " ",A       10    VOLUME MIXING RATIO (PPMV)                       COV  180 */
	/*        B       11    NUMBER DENSITY (CM-3)                            COV  190 */
	/*        C       12    MASS MIXING RATIO (GM(K)/KG(AIR))                COV  200 */
	/*        D       13    MASS DENSITY (GM M-3)                            COV  210 */
	/*        E       14    PARTIAL PRESSURE (MB)                            COV  220 */
	/*        F       15    DEW POINT TEMP (TD IN T(K)) - H2O ONLY           COV  230 */
	/*        G       16     "    "     "  (TD IN T(C)) - H2O ONLY           COV  240 */
	/*        H       17    RELATIVE HUMIDITY (RH IN PERCENT) - H2O ONLY     COV  250 */
	/*        I       18    AVAILABLE FOR USER DEFINITION                    COV  260 */
	/*        J       19    REQUEST DEFAULT TO SPECIFIED MODEL ATMOSPHERE    COV  270 */
	/*                                                                       COV  280 */
	/* ***************************************************************        COV  290 */
	/*                                                                       COV  300 */
	/* *****                                                                  COV  370 */
	rhoair = constn_1.alosmt * (*p / constn_1.pzero) * (constn_1.tzero / *t);
	/*     NOPRT = 0                                                        COV  390 */
	/*     A = TZERO/T                                                       COV  400 */
	for (k = 1; k <= 12; ++k)
	{
		b = constn_1.avogad / constn_1.amwt[k - 1];
		r__ = constn_1.airmwt / constn_1.amwt[k - 1];
		junit = card1b_2.junit1[k - 1];
		wmol = card1b_2.wmol1[k - 1];
		if (k != 1)
		{
			goto L100;
		}
		watvap_(p, t);
		goto L200;
	L100:
		if (junit > 10)
		{
			goto L110;
		}
		/* *****GIVEN VOL. MIXING RATIO                                           COV  510 */
		/* C    WMOL1(K)=WMOL*RHOAIR*1.E-6                                        COV  520 */
		goto L200;
	L110:
		if (junit != 11)
		{
			goto L120;
		}
		/* *****GIVEN NUMBER DENSITY (CM-3)                                       COV  550 */
		/* C    WMOL1(K) = WMOL                                                   COV  560 */
		card1b_2.wmol1[k - 1] = wmol / (rhoair * 1e-6f);
		goto L200;
	L120:
		if (junit != 12)
		{
			goto L130;
		}
		/* *****GIVEN MASS MIXING RATIO (GM KG-1)                                 COV  610 */
		/* C    WMOL1(K)= R*WMOL*1.0E-3*RHOAIR                                    COV  620 */
		card1b_2.wmol1[k - 1] = r__ * wmol * 1e3f;
		goto L200;
	L130:
		if (junit != 13)
		{
			goto L140;
		}
		/* *****GIVEN MASS DENSITY (GM M-3)                                       COV  670 */
		/* C    WMOL1(K) = B*WMOL*1.0E-6                                          COV  680 */
		card1b_2.wmol1[k - 1] = b * wmol / rhoair;
		goto L200;
	L140:
		if (junit != 14)
		{
			goto L150;
		}
		/* *****GIVEN  PARTIAL PRESSURE (MB)                                      COV  730 */
		/* C    WMOL1(K)= ALOSMT*(WMOL/PZERO)*(TZERO/T)                           COV  740 */
		wtem = constn_1.alosmt * (wmol / constn_1.pzero) * (constn_1.tzero / *t);
		card1b_2.wmol1[k - 1] = wtem / (rhoair * 1e-6f);
		goto L200;
	L150:
		if (junit > 14)
		{
			goto L299;
		}
	L200:;
	}
	return 0;
L299:
	io___307.ciunit = ifil_1.ipr;
	s_wsfe(&io___307);
	do_fio(&c__1, (char *)&junit, (long)sizeof(long));
	e_wsfe();
	s_stop((char *)"", (long)0);
	return 0;
} /* convrt_ */

/* Subroutine */ int watvap_(const float *p, const float *t)
{
	/* Initialized data */

	static float c1 = 18.9766f;
	static float c2 = -14.9595f;
	static float c3 = -2.43882f;
	static float xlosch = 2.6868e19f;

	/* Format strings */
	static char fmt_951[] = "(/,\002  **** ERROR IN WATVAP ****, JUNIT = "
							"\002,i5)";
	static char fmt_10[] = "(/,\002 ********WARNING (FROM WATVAP) # RELATIVE"
						   " HUMIDTY = \002,g10.3,\002 IS GREATER THAN 100 PERCENT\002)";

	/* System generated locals */
	float r__1;

	/* Builtin functions */
	double exp(double);
	long s_wsfe(cilist *), do_fio(long *, char *, long), e_wsfe(void);
	/* Subroutine */ int s_stop(char *, long);

	/* Local variables */
	static float a, b, r__, atd, rhp, pss, wtem, wmol, denst;
	static long junit;
	static float rhoair, dennum;

	/* Fortran I/O blocks */
	static cilist io___321 = {0, 0, 0, fmt_951, 0};
	static cilist io___325 = {0, 0, 0, fmt_10, 0};

	/* *************************************************************          WAT  110 */
	/*                                                                       WAT  120 */
	/*        WRITTEN APR, 1985 TO ACCOMMODATE 'JCHAR' DEFINITIONS FOR       WAT  130 */
	/*        UNIFORM DATA INPUT -                                           WAT  140 */
	/*                                                                       WAT  150 */
	/*     JCHAR    JUNIT                                                    WAT  160 */
	/*                                                                       WAT  170 */
	/*    " ",A       10    VOLUME MIXING RATIO (PPMV)                       WAT  180 */
	/*        B       11    NUMBER DENSITY (CM-3)                            WAT  190 */
	/*        C       12    MASS MIXING RATIO (GM(K)/KG(AIR))                WAT  200 */
	/*        D       13    MASS DENSITY (GM M-3)                            WAT  210 */
	/*        E       14    PARTIAL PRESSURE (MB)                            WAT  220 */
	/*        F       15    DEW POINT TEMP (TD IN T(K)) - H2O ONLY           WAT  230 */
	/*        G       16     "    "     "  (TD IN T(C)) - H2O ONLY           WAT  240 */
	/*        H       17    RELATIVE HUMIDITY (RH IN PERCENT) - H2O ONLY     WAT  250 */
	/*        I       18    AVAILABLE FOR USER DEFINITION                    WAT  260 */
	/*        J       19    REQUEST DEFAULT TO SPECIFIED MODEL ATMOSPHERE    WAT  270 */
	/*                                                                       WAT  280 */
	/*     THIS SUBROUTINE COMPUTES THE WATERVAPOR NUMBER DENSITY (MOL CM-3) WAT  290 */
	/*     GIVE HUMIDITY  # TD = DEW POINT TEMP(K,C), RH = RELATIVE          WAT  300 */
	/*     (PERCENT), PPH2O = WATER VAPOR PARTIAL PRESSURE (MB), DENH2O =    WAT  310 */
	/*     WATER VAPOR MASS DENSITY (GM M-3),AMSMIX = MASS MIXING RATIO      WAT  320 */
	/*     (GM/KG).                                                          WAT  330 */
	/*                     THE FUNCTION DENSAT FOR THE SATURATION            WAT  340 */
	/*     WATER VAPOR DENSITY OVER WATER IS ACCURATE TO BETTER THAN 1       WAT  350 */
	/*     PERCENT FROM -50 TO +50 DEG C. (SEE THE LOWTRAN3 OR 5 REPORT)     WAT  360 */
	/*                                                                       WAT  370 */
	/*       'JUNIT' GOVERNS CHOICE OF UNITS -                               WAT  380 */
	/*                                                                       WAT  390 */
	/* ***********************************************************************WAT  400 */
	/* *****                                                                  WAT  480 */
	rhoair = constn_1.alosmt * (*p / constn_1.pzero) * (constn_1.tzero / *t);
	pss = *p / constn_1.pzero;
	a = constn_1.tzero / *t;
	card1b_3.wair = xlosch * pss * a;
	b = constn_1.avogad / constn_1.amwt[0];
	r__ = constn_1.airmwt / constn_1.amwt[0];
	junit = card1b_3.junit1[0];
	wmol = card1b_3.wmol1[0];

	if (junit != 10)
	{
		goto L110;
	}
	/* *****GIVEN VOL. MIXING RATIO                                           WAT  580 */
	/* C    WMOL1(1)=WMOL*RHOAIR*1.E-6                                        WAT  590 */
	wtem = wmol * rhoair * 1e-6f;
	goto L200;
L110:
	if (junit != 11)
	{
		goto L120;
	}
	/* *****GIVEN NUMBER DENSITY (CM-3)                                       WAT  620 */
	card1b_3.wmol1[0] = wmol / (rhoair * 1e-6f);
	wtem = wmol;
	goto L200;
L120:
	if (junit != 12)
	{
		goto L130;
	}
	/* *****GIVEN MASS MIXING RATIO (GM KG-1)                                 WAT  670 */
	/* C    WMOL1(1) = R*WMOL*1.0E-3*RHOAIR                                   WAT  680 */
	wtem = r__ * wmol * .001f * rhoair;
	card1b_3.wmol1[0] = r__ * wmol * 1e3f;
	goto L200;
L130:
	if (junit != 13)
	{
		goto L140;
	}
	/* *****GIVEN MASS DENSITY (GM M-3)                                       WAT  730 */
	/* C    WMOL1(1) = B*WMOL*1.0E-6                                          WAT  740 */
	wtem = b * wmol * 1e-6f;
	card1b_3.wmol1[0] = b * wmol / rhoair;
	goto L200;
L140:
	if (junit != 14)
	{
		goto L150;
	}
	/* *****GIVEN WATER VAPOR PARTIAL PRESSURE (MB)                           WAT  790 */
	/* C    WMOL1(1) = ALOSMT*(WMOL/PZERO)*(TZERO/T)                          WAT  800 */
	wtem = constn_1.alosmt * (wmol / constn_1.pzero) * (constn_1.tzero / *t);
	card1b_3.wmol1[0] = wtem / (rhoair * 1e-6f);
	goto L200;
L150:
	if (junit != 15)
	{
		goto L160;
	}
	/* *****GIVEN DEWPOINT (DEG K)                                            WAT  860 */
	atd = constn_1.tzero / wmol;
	/* C    WMOL1(1)= DENSAT(ATD)*(WMOL)/T                                    WAT  880 */
	/* Computing 2nd power */
	r__1 = atd;
	wtem = atd * b * exp(c1 + c2 * atd + c3 * (r__1 * r__1)) * 1e-6f * wmol /
		   *t;
	card1b_3.wmol1[0] = wtem / (rhoair * 1e-6f);
	goto L200;
L160:
	if (junit != 16)
	{
		goto L170;
	}
	/* *****GIVEN DEWPOINT (DEG C)                                            WAT  940 */
	atd = constn_1.tzero / (constn_1.tzero + wmol);
	/* C    WMOL1(1) = DENSAT(ATD)*(TZERO+WMOL)/T                             WAT  960 */
	/* Computing 2nd power */
	r__1 = atd;
	wtem = atd * b * exp(c1 + c2 * atd + c3 * (r__1 * r__1)) * 1e-6f * (constn_1.tzero + wmol) / *t;
	card1b_3.wmol1[0] = wtem / (rhoair * 1e-6f);
	goto L200;
L170:
	if (junit != 17)
	{
		goto L199;
	}
	/* *****GIVEN RELATIVE HUMIDITY (PERCENT)                                 WAT 1020 */
	/*     DENNUM = DENSAT(A)*(WMOL/100.0)/(1.0-(1.0-WMOL/100.0)*DENSAT(A)/  WAT 1030 */
	/*    1    RHOAIR)                                                       WAT 1040 */
	/* C    WMOL1(1) = DENSAT(A)*(WMOL/100.0)                                 WAT 1050 */
	/* Computing 2nd power */
	r__1 = a;
	wtem = a * b * exp(c1 + c2 * a + c3 * (r__1 * r__1)) * 1e-6f * (wmol / 100.f);
	card1b_3.wmol1[0] = wtem / (rhoair * 1e-6f);
	goto L200;
L199:
	io___321.ciunit = ifil_1.ipr;
	s_wsfe(&io___321);
	do_fio(&c__1, (char *)&junit, (long)sizeof(long));
	e_wsfe();
	s_stop((char *)"JUNIT", (long)5);
L200:
	card1b_3.wmol1[0] = card1b_3.wmol1[0] * 2.989e-23f * card1b_3.wair;
	/* Computing 2nd power */

	denst = a * b * exp(c1 + c2 * a + c3 * (a * a)) * 1e-6f;
	dennum = wtem;

	/*     RHP = 100.0*(DENNUM/DENST)*((RHOAIR-DENST)/(RHOAIR-DENNUM))       WAT 1160 */
	rhp = dennum / denst * 100.f;
	/* L12: */
	if (rhp <= 100.f)
	{
		goto L230;
	}
	io___325.ciunit = ifil_1.ipr;
	s_wsfe(&io___325);
	do_fio(&c__1, (char *)&rhp, (long)sizeof(float));
	e_wsfe();
L230:
	return 0;
} /* watvap_ */

/* Subroutine */ int atmcon_(void)
{
	return 0;
} /* atmcon_ */

/* >    BLOCK DATA                                                        BAT  105 */
/* ***********************************************************************BAT  110 */
/*     THIS SUBROUTINE INITIALIZES THE CONSTANTS  USED IN THE            BAT  120 */
/*     PROGRAM. CONSTANTS RELATING TO THE ATMOSPHERIC PROFILES ARE STOREDBAT  130 */
/*     IN BLOCK DATA MLATMB.                                             BAT  140 */
/* ***********************************************************************BAT  150 */
/* *****ALZERO IS THE MEAN LORENTZ HALFWIDTH AT PZERO AND 296.0 K.        BAT  220 */
/* *****AVMWT IS THE MEAN MOLECULAR WEIGHT USED TO AUTOMATICALLY          BAT  230 */
/* *****GENERATE THE FASCODE BOUNDARIES IN AUTLAY                         BAT  240 */

/* Subroutine */ int stdmdl_(void)
{
	/* Initialized data */

	static float pzero = 1013.25f;
	static float tzero = 273.15f;
	static float xlosch = 2.6868e24f;
	static float rv = .0046152f;
	static float con = 3.3429e21f;
	static float a0 = 83.42f;
	static float a1 = 185.08f;
	static float a2 = 4.11f;
	static float b1 = 1.14e5f;
	static float b2 = 62400.f;
	static float c0 = 43.49f;
	static float c1 = 1.7e4f;

	/* Format strings */
	static char fmt_910[] = "(\0021\002,/,\002  ATMOSPHERIC PROFILES\002,//,"
							"3x,\002I\002,t10,\002Z\002,t18,\002P\002,t26,\002T\002,t35,\002N2"
							"\002,t44,\002CNTMSLF\002,t52,\002MOL SCAT\002,t65,\002N-1\002,t7"
							"3,\002O3 (UV)\002,t82,\002O2 (UV)\002,/,t9,\002(KM)\002,t17,\002"
							"(MB)\002,t25,\002(K)\002,t40,\002(MOL/CM2 KM)\002,t55,\002(-)"
							"\002,t65,\002(-)\002,t70,\002(ATM CM/KM)\002,t82,\002(ATM CM/KM"
							")\002,/)";
	static char fmt_905[] = "(i4,0pf9.2,f9.3,f7.1,1x,1p9e10.3)";
	static char fmt_915[] = "(\0021\002,/,\002  ATMOSPHERIC PROFILES\002,//,"
							"3x,\002I\002,t10,\002Z\002,t18,\002P\002,t26,\002T\002,t33,\002C"
							"NTMFRN\002,t45,\002HNO3\002,t53,\002AEROSOL 1\002,t63,\002AEROSO"
							"L 2\002,t73,\002AEROSOL 3\002,t83,\002AEROSOL 4\002,t93,\002AER1"
							"*RH\002,t103,\002CIRRUS\002,t118,\002RH\002/,t9,\002(KM)\002,t17,"
							"\002(MB)\002,t25,\002(K)\002,t31,\002MOL/CM2 KM\002,t42,\002ATM "
							"CM/KM\002,t54,\002(-)\002,t64,\002(-)\002,t74,\002(-)\002,t84"
							",\002(-)\002,t94,\002(-)\002,t104,\002(-)\002,t113,\002(PERCNT"
							")\002,/)";
	static char fmt_920[] = "(\0021\002,/,\002  ATMOSPHERIC PROFILES\002,//"
							",\002  (IF A MOLECULE HAS MORE THAN ONE BAND, THEN THE DATA FOR "
							"THE\002,\002 FIRST BAND ARE SHOWN.)\002//\002   I      Z       P"
							"       T      H2O      O3       CO2\002,\002      CO       CH4  "
							"    N2O      O2       NH3      NO \002,\002      NO2      SO2"
							"\002/\002         (KM)    (MB)    (K) G/CM**2/KM  (           "
							" \002,\002          ATM CM/KM                                  "
							" \002,\002                  )\002)";
	static char fmt_906[] = "(i4,0pf9.2,f9.3,f7.1,1x,1p11e9.2)";

	/* System generated locals */
	long i__1;
	float r__1, r__2, r__3;
	double d__1, d__2;

	/* Builtin functions */
	double sqrt(double), log(double), pow_dd(double *, double *);
	long s_wsfe(cilist *), e_wsfe(void), do_fio(long *, char *, long);

	/* Local variables */
	static long i__, k;
	static float f1, f2, dt, pp, tt, ts, avw, pss, ppw, tss, wo2d, relh, cono2,
		cono3, conco, rhlog, conno, wtemp, conch4, conco2, conh2o,
		connh3, conn2o, conno2, rhoh2o, conso2, conjoe, rhoair, rhofrn,
		rhzero;

	/* Fortran I/O blocks */
	static cilist io___369 = {0, 0, 0, fmt_910, 0};
	static cilist io___370 = {0, 0, 0, fmt_905, 0};
	static cilist io___372 = {0, 0, 0, fmt_915, 0};
	static cilist io___373 = {0, 0, 0, fmt_905, 0};
	static cilist io___374 = {0, 0, 0, fmt_920, 0};
	static cilist io___375 = {0, 0, 0, fmt_906, 0};

	/* ***********************************************************************STD  110 */
	/*     THIS SUBROUTINE LOADS ONE OF THE 6 STANDARD ATMOSPHERIC PROFILES  STD  120 */
	/*     INTO COMMON/MODEL/ AND CALCULATES THE DENSITIES OF THE            STD  130 */
	/*     VARIOUS ABSORBING GASES AND AEROSOLS                              STD  140 */
	/* ***********************************************************************STD  150 */
	/*     XLOSCH = LOSCHMIDT'S NUMBER,MOLECULES CM-2,KM-1                   STD  330 */
	/*     RV GAS CONSTANT FOR WATER IN MB/(GM M-3 K)                        STD  350 */
	/*     CON CONVERTS WATER VAPOR FROM GM M-3 TO MOLECULES CM-2 KM-1       STD  360 */
	/*     CONSTANTS FOR INDEX OF REFRACTION, AFTER EDLEN, 1965              STD  380 */
	/*                                                                       STD  410 */
	/*     F(A) IS SATURATED WATER WAPOR DENSITY AT TEMP T,A=TZERO/T         STD  420 */
	/*                                                                       STD  440 */
	/*     CONJOE=(1/XLOSCH)*1.E5*1.E-6 WITH                                 STD  450 */
	/*        1.E5 ARISING FROM CM TO KM CONVERSION AND                      STD  460 */
	/*        1.E-6  "       "  PPMV                                         STD  470 */
	/*                                                                       STD  480 */
	conjoe = 3.7194e-21f;
	/*                                                                       STD  500 */
	/*     H20 CONTINUUM IS STORED AT 296 K RHZERO IS AIR DENSITY AT 296 K   STD  510 */
	/*     IN UNITS OF LOSCHMIDT'S                                           STD  520 */
	/*                                                                       STD  530 */
	rhzero = .92280405405405397f;
	/*                                                                       STD  550 */
	/*     LOAD ATMOSPHERE PROFILE INTO /MODEL/                              STD  560 */
	i__1 = cntrl_1.ml;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		model_1.pm[i__ - 1] = mdata_1.p[i__ - 1];
		model_1.tm[i__ - 1] = mdata_1.t[i__ - 1];
		pp = model_1.pm[i__ - 1];
		tt = model_1.tm[i__ - 1];
		pss = pp / pzero;
		tss = tzero / tt;
		f1 = pp / pzero / (tt / tzero);
		f2 = pp / pzero * sqrt(tzero / tt);
		wtemp = mdata_1.wh[i__ - 1];
		/*     SCALED H2O DENSITY                                                STD  670 */
		if (model_1.zm[i__ - 1] > 2.f)
		{
			goto L15;
		}
		ts = tzero / tt;
	L15:
		/*     UNIFORMALY MIXED GASES DENSITYS                                   STD  710 */
		/*     ORIGINAL TRANSMITTANCE MODEL FOR CO2+ HAS BEEN REPLACED.          STD  720 */
		/*     DENSTY(2,I)=F1*F2**0.75                                           STD  730 */
		/*     UV OZONE                                                          STD  740 */
		/*     THE UNIT FOR O3 HAS BEEN CHANGED FROM G/M**3 TO PPMV.             STD  750 */
		model_1.densty[i__ * 63 - 56] = conjoe * mdata1_1.wair[i__ - 1] *
										mdata_1.wo[i__ - 1];
		/*     IR OZONE                                                          STD  770 */
		/*     ORIGINAL TRANSMITTANCE MODEL HAS BEEN REPLACED.                   STD  780 */
		/*     DENSTY(3,I)= DENSTY(8,I)*F2**0.4                                  STD  790 */
		/*     N2 CONTINUUM                                                      STD  800 */
		model_1.densty[i__ * 63 - 60] = f1 * .781f * f2;
		/*     SELF BROADENED WATER                                              STD  820 */
		rhoair = f1;
		rhoh2o = con * wtemp / xlosch;
		rhofrn = rhoair - rhoh2o;
		/* Computing 2nd power */
		r__1 = rhoh2o;
		model_1.densty[i__ * 63 - 59] = xlosch * (r__1 * r__1) / rhzero;
		/*     FOREIGN BROADENED                                                 STD  870 */
		model_1.densty[i__ * 63 - 54] = xlosch * rhoh2o * rhofrn / rhzero;
		/*     MOLECULAR SCATTERING                                              STD  890 */
		model_1.densty[i__ * 63 - 58] = f1;
		/*     RELITIVE HUMIDITY WEIGHTED BY BOUNDRY LAYER AEROSOL (0 TO 2 KM)   STD  910 */
		/*                                                                       STD  920 */
		/*     LOG WEIGHTING OF REL HUMIDITY                                     STD  930 */
		/*                                                                       STD  940 */
		relh = _BLNK__1.relhum[i__ - 1];
		if (_BLNK__1.relhum[i__ - 1] > 99.f)
		{
			relh = 99.f;
		}
		rhlog = log(100.f - relh);
		/*     DENSTY(15,I)=RELHUM(I)*DENSTY(7,I)                                STD  980 */
		model_1.densty[i__ * 63 - 49] = rhlog * model_1.densty[i__ * 63 - 57];
		/*     DENSITY (9,I) TEMP DEP OF WATER SET IN GEO                        STD 1000 */
		model_1.densty[i__ * 63 - 55] = 0.f;
		/*     IF(ICH(1).GT.7) DENSTY(15,I)=RELHUM(I)*DENSTY(12,I)               STD 1020 */
		if (_BLNK__1.ich[0] > 7)
		{
			model_1.densty[i__ * 63 - 49] = rhlog * model_1.densty[i__ * 63 -
																   52];
		}
		/*     HNO3 IN ATM * CM /KM                                              STD 1040 */
		/*     NEW PROFILE IS IN UNIT OF PART PER 10**6 BY VOLUME                STD 1050 */
		/*     DENSTY(11,I)= F1* HMIX(I)*1.0E-4                                  STD 1060 */
		/*     IF(MODEL.EQ.7) DENSTY(11,I)=F1*HSTOR(I)*1.0E-4                    STD 1070 */
		model_1.densty[i__ * 63 - 53] = f1 * _BLNK__1.hstor[i__ - 1] * 1e-4f;
		/*                                                                       STD 1090 */
		/*      O2 TEMP DEP                                                      STD 1100 */
		/*                                                                       STD 1110 */
		dt = tt - 220.f;
		wo2d = conjoe * mdata1_1.wair[i__ - 1] * mdata_1.wo2[i__ - 1] * pss;
		/*                                                                       STD 1140 */
		/*     DT CAN BE NEGIVATIVE                                              STD 1150 */
		/*     EFFECTIVE DT CALCULATED IN TRANS                                  STD 1160 */
		/*                                                                       STD 1170 */
		model_1.densty[i__ * 63 - 63] = wo2d * tt;
		model_1.densty[i__ * 63 - 62] = wo2d * dt * dt;
		model_1.densty[i__ * 63 - 1] = wo2d;
		/*                                                                       STD 1210 */
		/*   NEW  MICROWAVE TEMP  RAIN                                           STD 1220 */
		/*                                                                       STD 1230 */
		model_1.densty[i__ * 63 - 61] = 0.f;
		model_1.densty[i__ * 63 - 3] = 0.f;
		model_1.densty[i__ * 63 - 2] = 0.f;
		if (model_1.rramt[i__ - 1] != 0.f)
		{
			d__1 = (double)model_1.rramt[i__ - 1];
			model_1.densty[i__ * 63 - 61] = pow_dd(&d__1, &c_b749);
			model_1.densty[i__ * 63 - 3] = model_1.densty[i__ * 63 - 61] *
										   mdata_1.t[i__ - 1];
			model_1.densty[i__ * 63 - 2] = 1.f;
		}
		/*                                                                       STD 1320 */
		/*       CIRRIUS CLOUD                                                   STD 1330 */
		if (card2_1.icld < 18)
		{
			model_1.densty[i__ * 63 - 48] = 0.f;
		}
		/*  --- FOR H2O -----                                                    STD 1350 */
		conh2o = mdata_1.wh[i__ - 1] * .1f;
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 47] = conh2o * pow_dd(&d__1, &c_b750) *
										pow_dd(&d__2, &c_b751);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 46] = conh2o * pow_dd(&d__1, &c_b752) *
										pow_dd(&d__2, &c_b753);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 45] = conh2o * pow_dd(&d__1, &c_b754) *
										pow_dd(&d__2, &c_b755);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 44] = conh2o * pow_dd(&d__1, &c_b756) *
										pow_dd(&d__2, &c_b757);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 43] = conh2o * pow_dd(&d__1, &c_b758) *
										pow_dd(&d__2, &c_b759);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 42] = conh2o * pow_dd(&d__1, &c_b760) *
										pow_dd(&d__2, &c_b761);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 41] = conh2o * pow_dd(&d__1, &c_b762) *
										pow_dd(&d__2, &c_b763);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 40] = conh2o * pow_dd(&d__1, &c_b764) *
										pow_dd(&d__2, &c_b765);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 39] = conh2o * pow_dd(&d__1, &c_b766) *
										pow_dd(&d__2, &c_b767);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 38] = conh2o * pow_dd(&d__1, &c_b768) *
										pow_dd(&d__2, &c_b769);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 37] = conh2o * pow_dd(&d__1, &c_b770) *
										pow_dd(&d__2, &c_b771);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 36] = conh2o * pow_dd(&d__1, &c_b772) *
										pow_dd(&d__2, &c_b773);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 35] = conh2o * pow_dd(&d__1, &c_b774) *
										pow_dd(&d__2, &c_b775);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 34] = conh2o * pow_dd(&d__1, &c_b776) *
										pow_dd(&d__2, &c_b777);
		/*  --- FOR O3                                                           STD 1510 */
		cono3 = conjoe * mdata1_1.wair[i__ - 1] * mdata_1.wo[i__ - 1];
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 33] = cono3 * pow_dd(&d__1, &c_b778) *
										pow_dd(&d__2, &c_b779);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 32] = cono3 * pow_dd(&d__1, &c_b780) *
										pow_dd(&d__2, &c_b781);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 31] = cono3 * pow_dd(&d__1, &c_b782) *
										pow_dd(&d__2, &c_b783);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 30] = cono3 * pow_dd(&d__1, &c_b784) *
										pow_dd(&d__2, &c_b785);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 29] = cono3 * pow_dd(&d__1, &c_b786) *
										pow_dd(&d__2, &c_b787);
		/*  --- FOR CO2                                                          STD 1580 */
		conco2 = conjoe * mdata1_1.wair[i__ - 1] * mdata_1.wco2[i__ - 1];
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 28] = conco2 * pow_dd(&d__1, &c_b788) *
										pow_dd(&d__2, &c_b789);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 27] = conco2 * pow_dd(&d__1, &c_b790) *
										pow_dd(&d__2, &c_b791);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 26] = conco2 * pow_dd(&d__1, &c_b792) *
										pow_dd(&d__2, &c_b793);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 25] = conco2 * pow_dd(&d__1, &c_b794) *
										pow_dd(&d__2, &c_b795);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 24] = conco2 * pow_dd(&d__1, &c_b796) *
										pow_dd(&d__2, &c_b797);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 23] = conco2 * pow_dd(&d__1, &c_b798) *
										pow_dd(&d__2, &c_b799);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 22] = conco2 * pow_dd(&d__1, &c_b800) *
										pow_dd(&d__2, &c_b801);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 21] = conco2 * pow_dd(&d__1, &c_b802) *
										pow_dd(&d__2, &c_b803);
		/*  --- FOR CO                                                           STD 1680 */
		conco = conjoe * mdata1_1.wair[i__ - 1] * mdata_1.wco[i__ - 1];
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 20] = conco * pow_dd(&d__1, &c_b804) *
										pow_dd(&d__2, &c_b805);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 19] = conco * pow_dd(&d__1, &c_b806) *
										pow_dd(&d__2, &c_b807);
		/*  --- FOR CH4                                                          STD 1720 */
		conch4 = conjoe * mdata1_1.wair[i__ - 1] * mdata_1.wch4[i__ - 1];
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 18] = conch4 * pow_dd(&d__1, &c_b808) *
										pow_dd(&d__2, &c_b809);
		/*  --- FOR N2O                                                          STD 1750 */
		conn2o = conjoe * mdata1_1.wair[i__ - 1] * mdata_1.wn2o[i__ - 1];
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 17] = conn2o * pow_dd(&d__1, &c_b810) *
										pow_dd(&d__2, &c_b811);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 16] = conn2o * pow_dd(&d__1, &c_b812) *
										pow_dd(&d__2, &c_b813);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 15] = conn2o * pow_dd(&d__1, &c_b814) *
										pow_dd(&d__2, &c_b815);
		/*  --- FOR O2                                                           STD 1800 */
		cono2 = conjoe * mdata1_1.wair[i__ - 1] * mdata_1.wo2[i__ - 1];
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 14] = cono2 * pow_dd(&d__1, &c_b816) *
										pow_dd(&d__2, &c_b817);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 13] = cono2 * pow_dd(&d__1, &c_b818) *
										pow_dd(&d__2, &c_b819);
		/*  --- FOR NH3                                                          STD 1840 */
		connh3 = conjoe * mdata1_1.wair[i__ - 1] * mdata1_1.wnh3[i__ - 1];
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 12] = connh3 * pow_dd(&d__1, &c_b820) *
										pow_dd(&d__2, &c_b821);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 11] = connh3 * pow_dd(&d__1, &c_b822) *
										pow_dd(&d__2, &c_b823);
		/*  --- FOR NO                                                           STD 1880 */
		conno = conjoe * mdata1_1.wair[i__ - 1] * mdata1_1.wno[i__ - 1];
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 10] = conno * pow_dd(&d__1, &c_b824) *
										pow_dd(&d__2, &c_b825);
		/*  --- FOR NO2                                                          STD 1910 */
		conno2 = conjoe * mdata1_1.wair[i__ - 1] * mdata1_1.wno2[i__ - 1];
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 9] = conno2 * pow_dd(&d__1, &c_b826) *
									   pow_dd(&d__2, &c_b827);
		/*  --- FOR SO2                                                          STD 1940 */
		conso2 = conjoe * mdata1_1.wair[i__ - 1] * mdata1_1.wso2[i__ - 1];
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 8] = conso2 * pow_dd(&d__1, &c_b828) *
									   pow_dd(&d__2, &c_b829);
		d__1 = (double)pss;
		d__2 = (double)tss;
		model_1.densty[i__ * 63 - 7] = conso2 * pow_dd(&d__1, &c_b830) *
									   pow_dd(&d__2, &c_b831);
		/* ***********************************************************************STD 1980 */
		/*   HERZBERG CONTINUUM PRESSURE DEPENDENCE CALCULATION, SHARDANAND 1977 STD 1990 */
		/*      AND   YOSHINO ET AL 1988                                         STD 2000 */
		/*                                                                       STD 2010 */
		/*     OXYGEN                                                            STD 2020 */
		/*                                                                       STD 2030 */
		model_1.densty[i__ * 63 - 6] = (f1 * .83f + 1.f) * cono2;
		model_1.densty[i__ * 63 - 5] = 0.f;
		model_1.densty[i__ * 63 - 4] = 0.f;
		/* ***********************************************************************STD 2070 */
		/*                                                                       STD 2080 */
		/*     RFNDX = REFRAXTIVITY 1-INDEX OF REFRACTION                        STD 2090 */
		/*     FROM EDLEN, 1966                                                  STD 2100 */
		ppw = rv * wtemp * tt;
		avw = (card4_1.v1 + card4_1.v2) * .5f;
		/* Computing 2nd power */
		r__1 = avw / b1;
		/* Computing 2nd power */
		r__2 = avw / b2;
		/* Computing 2nd power */
		r__3 = avw / c1;
		model_1.rfndx[i__ - 1] = ((a0 + a1 / (1.f - r__1 * r__1) + a2 / (1.f - r__2 * r__2)) * (pp / pzero) * (tzero + 15.f) / tt - (c0 -
																																	 r__3 * r__3) *
																																		ppw / pzero) *
								 1e-6f;
		/* L25: */
	}
	if (ifil_1.npr == 1)
	{
		goto L40;
	}
	io___369.ciunit = ifil_1.ipr;
	s_wsfe(&io___369);
	e_wsfe();
	i__1 = cntrl_1.ml;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		io___370.ciunit = ifil_1.ipr;
		s_wsfe(&io___370);
		do_fio(&c__1, (char *)&i__, (long)sizeof(long));
		do_fio(&c__1, (char *)&model_1.zm[i__ - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.pm[i__ - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.tm[i__ - 1], (long)sizeof(float));
		for (k = 4; k <= 6; ++k)
		{
			do_fio(&c__1, (char *)&model_1.densty[k + i__ * 63 - 64], (long)sizeof(float));
		}
		do_fio(&c__1, (char *)&model_1.rfndx[i__ - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 56], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 6], (long)sizeof(float));
		e_wsfe();
		/* L30: */
	}
	io___372.ciunit = ifil_1.ipr;
	s_wsfe(&io___372);
	e_wsfe();
	i__1 = cntrl_1.ml;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		io___373.ciunit = ifil_1.ipr;
		s_wsfe(&io___373);
		do_fio(&c__1, (char *)&i__, (long)sizeof(long));
		do_fio(&c__1, (char *)&model_1.zm[i__ - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.pm[i__ - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.tm[i__ - 1], (long)sizeof(float));
		for (k = 10; k <= 11; ++k)
		{
			do_fio(&c__1, (char *)&model_1.densty[k + i__ * 63 - 64], (long)sizeof(float));
		}
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 57], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 52], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 51], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 50], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 49], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 48], (long)sizeof(float));
		do_fio(&c__1, (char *)&_BLNK__1.relhum[i__ - 1], (long)sizeof(float));
		e_wsfe();
		/* L35: */
	}
	io___374.ciunit = ifil_1.ipr;
	s_wsfe(&io___374);
	e_wsfe();
	i__1 = cntrl_1.ml;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		io___375.ciunit = ifil_1.ipr;
		s_wsfe(&io___375);
		do_fio(&c__1, (char *)&i__, (long)sizeof(long));
		do_fio(&c__1, (char *)&model_1.zm[i__ - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.pm[i__ - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.tm[i__ - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 47], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 33], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 28], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 20], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 18], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 17], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 14], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 12], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 10], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 9], (long)sizeof(float));
		do_fio(&c__1, (char *)&model_1.densty[i__ * 63 - 8], (long)sizeof(float));
		e_wsfe();
		/* L39: */
	}
L40:
	return 0;
} /* stdmdl_ */

/* Subroutine */ int laycld_(long *k, float *cldatz, float *rratz, long *icld1, float *gndalt, float *rainrt)
{
	/* Initialized data */

	static float zcld[16] = {0.f, .16f, .33f, .66f, 1.f, 1.5f, 2.f, 2.4f, 2.7f, 3.f,
							 3.5f, 4.f, 4.5f, 5.f, 5.5f, 6.f};
	static float cldtp = 6.0001f;
	static float delz = .02f;

	/* System generated locals */
	float r__1;

	/* Local variables */
	static long mc, mk, mr;
	static float zk, fac;
	static long icld;
	static float zdif;

	/*                                                                       LAY  110 */
	/*      THIS SUBROUTINE RESTRUCTURES THE ATMOSPHERIC PROFILE             LAY  120 */
	/*      TO PROFIDE FINER LAYERING WITHIN THE FIRST 6 KM.                 LAY  130 */
	/*                                                                       LAY  140 */
	/*     ZMDL COMMON /MODEL/ FINAL ALTITUDE FOR LOWTRAN                    LAY  150 */
	/*     ZK  EFFECTIVE CLOUD ALTITUDES                                     LAY  160 */
	/*     ZCLD CLOUD ALTITUDE ARRAY                                         LAY  170 */
	/*     ZDIF  ALT DIFF OF 2 LAYERS                                        LAY  180 */
	/*     ZDA COMMON /MDATA/ CLD AND RAIN INFO IN THIS COMMON               LAY  190 */
	/*                                                                       LAY  200 */
	icld = *icld1;
	if (icld == 0)
	{
		return 0;
	}
	if (icld > 11)
	{
		return 0;
	}
	zk = model_2.zmdl[*k - 1] - *gndalt;
	if (zk < 0.f)
	{
		zk = 0.f;
	}
	if (model_2.zmdl[*k - 1] > 6.f)
	{
		zk = model_2.zmdl[*k - 1];
	}
	if (icld > 5)
	{
		goto L15;
	}
	/* CC                                                                     LAY  390 */
	/* CC    ICLD  IS  1- 5 ONE OF 5 SPECIFIC CLOUD MODELS IS CHOSEN          LAY  400 */
	/* CC                                                                     LAY  410 */
	mc = icld;
	mr = 6;
	goto L25;
L15:
	/* CC                                                                     LAY  460 */
	/* CC   ICLD  IS  6-10 ONE OF 5 SPECIFIC CLOUD/RAIN MODELS CHOSEN         LAY  470 */
	/* CC                                                                     LAY  480 */
	if (icld == 6)
	{
		mc = 3;
	}
	if (icld == 7 || icld == 8)
	{
		mc = 5;
	}
	if (icld > 8)
	{
		mc = 1;
	}
	mr = icld - 5;
L25:
	if (zk > cldtp)
	{
		goto L30;
	}
	*cldatz = 0.f;
	*rratz = 0.f;
	if (zk <= 10.f)
	{
		*rratz = *rainrt;
	}
	if (mc < 1)
	{
		goto L29;
	}
	for (mk = 1; mk <= 15; ++mk)
	{
		if (zk >= zcld[mk])
		{
			goto L26;
		}
		if (zk < zcld[mk - 1])
		{
			goto L26;
		}
		if ((r__1 = zk - zcld[mk - 1], dabs(r__1)) < delz)
		{
			goto L27;
		}
		goto L28;
	L27:
		*cldatz = mdata_1.cld[mk + mc * 50 - 51];
		*rratz = mdata_1.rr[mk + mr * 50 - 51];
		goto L29;
	L28:
		zdif = zcld[mk] - zcld[mk - 1];
		if (zdif < delz)
		{
			goto L27;
		}
		fac = (zcld[mk] - zk) / zdif;
		*cldatz = mdata_1.cld[mk + 1 + mc * 50 - 51] + fac * (mdata_1.cld[mk + mc * 50 - 51] - mdata_1.cld[mk + 1 + mc * 50 - 51]);
		*rratz = mdata_1.rr[mk + 1 + mr * 50 - 51] + fac * (mdata_1.rr[mk +
																	   mr * 50 - 51] -
															mdata_1.rr[mk + 1 + mr * 50 - 51]);
		goto L29;
	L26:;
	}
L29:
	model_2.cldamt[*k - 1] = *cldatz;
	mdata_1.cld[*k + 299] = *cldatz;
	mdata_1.rr[*k + 299] = *rratz;
	model_2.rramt[*k - 1] = *rratz;
	return 0;
L30:
	model_2.cldamt[*k - 1] = 0.f;
	model_2.rramt[*k - 1] = 0.f;
	*cldatz = 0.f;
	*rratz = 0.f;
	return 0;
	/* 100  CONTINUE                                                          LAY  840 */
	/*     RETURN                                                            LAY  850 */
} /* laycld_ */

/* Subroutine */ int layvsa_(long *k, float *rh, float *ahaze, long *iha1,
							 float *znew)
{
	/*                                                                       LVS  110 */
	/*     RETURNS HAZE FOR VSA OPTION                                       LVS  120 */
	/*                                                                       LVS  130 */
	/*                                                                       LVS  260 */
	/* Parameter adjustments */
	--znew;

	/* Function Body */
	*rh = 0.f;
	*ahaze = 0.f;
	*iha1 = 0;
	/*     HMXVSA=ZVSA(9)                                                    LVS  310 */
	if (card1_1.model == 0 || card1_1.model == 7)
	{
		return 0;
	}
	if (*k > 9)
	{
		return 0;
	}
	model_3.z__[*k - 1] = zvsaly_1.zvsa[*k - 1];
	*rh = zvsaly_1.rhvsa[*k - 1];
	*ahaze = zvsaly_1.ahvsa[*k - 1];
	*iha1 = zvsaly_1.ihvsa[*k - 1];
	return 0;
} /* layvsa_ */

long jou_(char *char__, long char_len)
{
	/* Initialized data */

	static char holvec[1 * 22] = {'1',
								  '2',
								  '3',
								  '4',
								  '5',
								  '6',
								  '0',
								  '0',
								  '0',
								  '0',
								  ' ',
								  'A',
								  'B',
								  'C',
								  'D',
								  'E',
								  'F',
								  'G',
								  'H',
								  'I',
								  'J',
								  'K'};
	static long indx1[22] = {1, 2, 3, 4, 5, 6, 0, 0, 0, 0, 10, 10, 11, 12, 13, 14, 15, 16,
							 17, 18, 19, 20};

	/* Format strings */
	static char fmt_910[] = "(\0020 INVALID PARAMETER :\002,2x,a1)";

	/* System generated locals */
	long ret_val;

	/* Builtin functions */
	long s_wsfe(cilist *), do_fio(long *, char *, long), e_wsfe(void);
	/* Subroutine */ int s_stop(char *, long);

	/* Local variables */
	static long i__, indx;

	/* Fortran I/O blocks */
	static cilist io___390 = {0, 0, 0, fmt_910, 0};

	/*                                                                       FJO  120 */
	/*                                                                       FJO  210 */
	indx = 0;
	for (i__ = 1; i__ <= 22; ++i__)
	{
		if (*(unsigned char *)&holvec[i__ - 1] != *(unsigned char *)char__)
		{
			goto L100;
		}
		indx = indx1[i__ - 1];
		goto L110;
	L100:;
	}
L110:
	if (indx == 0)
	{
		io___390.ciunit = ifil_1.ipr;
		s_wsfe(&io___390);
		do_fio(&c__1, char__, (long)1);
		e_wsfe();
		s_stop((char *)" JOU: BAD PARAM ", (long)16);
	}
	/* L920: */
	ret_val = indx;
	return ret_val;
} /* jou_ */

/* Subroutine */ int check_(float *v, long *iv, long *key)
{
	/* Initialized data */

	static float pmb = 1013.25f;
	static float ptorr = 760.f;
	static float degk = 273.15f;

	/* Builtin functions */
	/* Subroutine */ int s_stop(char *, long);

	/*                                                                       CHE  110 */
	/*      UNITS CONVERSION FOR P AND T                                     CHE  120 */
	/*                                                                       CHE  130 */
	/*     V = P OR T     AND  IV =JUNITP(I.E. MB,ATM,TORR)                  CHE  140 */
	/*                            =JUNITT(I.E. DEG K OR C)                   CHE  150 */
	/*                            =JUNITR(I.E. KM,M,OR CM)                   CHE  160 */
	/*                                                                       CHE  170 */
	if (*iv <= 10)
	{
		return 0;
	}
	switch (*key)
	{
	case 1:
		goto L100;
	case 2:
		goto L200;
	case 3:
		goto L300;
	}
/*                                                                       CHE  210 */
/*      PRESSURE CONVERSIONS                                             CHE  220 */
/*                                                                       CHE  230 */
L100:
	if (*iv == 11)
	{
		goto L110;
	}
	if (*iv == 12)
	{
		goto L120;
	}
	s_stop((char *)"CHECK(P)", (long)8);
L110:
	*v *= pmb;
	return 0;
L120:
	*v = *v * pmb / ptorr;
	return 0;
/*                                                                       CHE  310 */
/*      TEMPERATURE COMVERSIONS                                          CHE  320 */
/*                                                                       CHE  330 */
L200:
	if (*iv > 11)
	{
		s_stop((char *)"CHECK(T)", (long)8);
	}
	*v += degk;
	return 0;
/*                                                                       CHE  370 */
/*      RANGE CONVERSIONS                                                CHE  380 */
/*                                                                       CHE  390 */
L300:
	if (*iv == 11)
	{
		goto L310;
	}
	if (*iv == 12)
	{
		goto L320;
	}
	s_stop((char *)"CHECK(R)", (long)8);
L310:
	*v /= 1e3f;
	return 0;
L320:
	*v /= 1e5f;
	return 0;
} /* check_ */

/* Subroutine */ int vsansm_(long *k, float *ahaze, long *iha1)
{
	/* System generated locals */
	double d__1, d__2;

	/* Builtin functions */
	double pow_dd(double *, double *);

	/* Local variables */
	static long j, jl, km, kn, jp;
	static float dz, fac, dif;
	static long jml, jls;
	static float dlin, wmol[13];

	/*                                                                       VSA  220 */
	/*                                                                       VSA  280 */
	/*     OUTPUT COMMON MDATA AND MDATA1                                    VSA  290 */
	/*                                                                       VSA  300 */
	/*                                                                       VSA  310 */
	/*     MODEL 7 CODEING                                                   VSA  320 */
	/*     OLD LAYERS  AEROSOL RETURNED                                      VSA  330 */
	/*     NEW LAYERS P,T,DP,AEROSOL                                         VSA  340 */
	/*                                                                       VSA  350 */
	/*                                                                       VSA  360 */
	/*                                                                       VSA  370 */
	jml = cntrl_1.ml;
	j = 1;
	kn = *k;
L110:
	if (kn > 10)
	{
		goto L140;
	}
	jl = j - 1;
	if (jl < 1)
	{
		jl = 1;
	}
	jp = jl + 1;
	jls = jl;
	if (zvsaly_1.zvsa[kn - 1] == nsinp_1.zmdl[jl - 1])
	{
		goto L140;
	}
	jls = jp;
	if (zvsaly_1.zvsa[kn - 1] == nsinp_1.zmdl[jp - 1])
	{
		goto L140;
	}
	if (zvsaly_1.zvsa[kn - 1] > nsinp_1.zmdl[jl - 1] && zvsaly_1.zvsa[kn - 1] < nsinp_1.zmdl[jp - 1])
	{
		goto L115;
	}
	if (j >= jml)
	{
		goto L115;
	}
	++j;
	goto L110;
L115:
	mdata_1.z__[*k - 1] = zvsaly_1.zvsa[kn - 1];
	dif = nsinp_1.zmdl[jp - 1] - nsinp_1.zmdl[jl - 1];
	dz = zvsaly_1.zvsa[kn - 1] - nsinp_1.zmdl[jl - 1];
	dlin = dz / dif;
	mdata_1.p[*k - 1] = (nsinp_1.pm[jp - 1] - nsinp_1.pm[jl - 1]) * dlin +
						nsinp_1.pm[jl - 1];
	mdata_1.t[*k - 1] = (nsinp_1.tm[jp - 1] - nsinp_1.tm[jl - 1]) * dlin +
						nsinp_1.tm[jl - 1];
	for (km = 1; km <= 13; ++km)
	{
		wmol[km - 1] = (nsinp_1.wmdl[jp + km * 40 - 41] - nsinp_1.wmdl[jl +
																	   km * 40 - 41]) *
						   dlin +
					   nsinp_1.wmdl[jl + km * 40 - 41];
		/* L120: */
	}
	*iha1 = zvsaly_1.ihvsa[kn - 1];
	*ahaze = zvsaly_1.ahvsa[kn - 1];
	fac = (zvsaly_1.zvsa[kn - 1] - nsinp_1.zmdl[jl - 1]) / dif;
	if (nsinp_1.pm[jp - 1] > 0.f && nsinp_1.pm[jl - 1] > 0.f)
	{
		d__1 = (double)(nsinp_1.pm[jp - 1] / nsinp_1.pm[jl - 1]);
		d__2 = (double)fac;
		mdata_1.p[*k - 1] = nsinp_1.pm[jl - 1] * pow_dd(&d__1, &d__2);
	}
	if (nsinp_1.tm[jp - 1] > 0.f && nsinp_1.tm[jl - 1] > 0.f)
	{
		d__1 = (double)(nsinp_1.tm[jp - 1] / nsinp_1.tm[jl - 1]);
		d__2 = (double)fac;
		mdata_1.t[*k - 1] = nsinp_1.tm[jl - 1] * pow_dd(&d__1, &d__2);
	}
	for (km = 1; km <= 13; ++km)
	{
		if (nsinp_1.wmdl[jp + km * 40 - 41] > 0.f && nsinp_1.wmdl[jl + km * 40 - 41] > 0.f)
		{
			d__1 = (double)(nsinp_1.wmdl[jl + km * 40 - 41] *
							nsinp_1.wmdl[jp + km * 40 - 41] / nsinp_1.wmdl[jl + km * 40 - 41]);
			d__2 = (double)fac;
			wmol[km - 1] = pow_dd(&d__1, &d__2);
		}
		/* L130: */
	}
	mdata_1.wh[*k - 1] = wmol[0];
	mdata_1.wco2[*k - 1] = wmol[1];
	mdata_1.wo[*k - 1] = wmol[2];
	mdata_1.wn2o[*k - 1] = wmol[3];
	mdata_1.wco[*k - 1] = wmol[4];
	mdata_1.wch4[*k - 1] = wmol[5];
	mdata_1.wo2[*k - 1] = wmol[6];
	mdata1_1.wno[*k - 1] = wmol[7];
	mdata1_1.wso2[*k - 1] = wmol[8];
	mdata1_1.wno2[*k - 1] = wmol[9];
	mdata1_1.wnh3[*k - 1] = wmol[10];
	_BLNK__2.whno3[*k - 1] = wmol[11];
	mdata1_1.wair[*k - 1] = wmol[12];
	return 0;
L140:
	j = jls;
	if (*k > 10)
	{
		j = *k - 10 + card1b_4.jlow;
		*iha1 = 0;
		*ahaze = 0.f;
	}
	mdata_1.z__[*k - 1] = nsinp_1.zmdl[j - 1];
	mdata_1.p[*k - 1] = nsinp_1.pm[j - 1];
	mdata_1.t[*k - 1] = nsinp_1.tm[j - 1];
	for (km = 1; km <= 13; ++km)
	{
		wmol[km - 1] = nsinp_1.wmdl[j + km * 40 - 41];
		/* L135: */
	}
	mdata_1.wh[*k - 1] = wmol[0];
	mdata_1.wco2[*k - 1] = wmol[1];
	mdata_1.wo[*k - 1] = wmol[2];
	mdata_1.wn2o[*k - 1] = wmol[3];
	mdata_1.wco[*k - 1] = wmol[4];
	mdata_1.wch4[*k - 1] = wmol[5];
	mdata_1.wo2[*k - 1] = wmol[6];
	mdata1_1.wno[*k - 1] = wmol[7];
	mdata1_1.wso2[*k - 1] = wmol[8];
	mdata1_1.wno2[*k - 1] = wmol[9];
	mdata1_1.wnh3[*k - 1] = wmol[10];
	_BLNK__2.whno3[*k - 1] = wmol[11];
	mdata1_1.wair[*k - 1] = wmol[12];
	if (kn <= 9)
	{
		*iha1 = zvsaly_1.ihvsa[kn - 1];
	}
	if (kn <= 9)
	{
		*ahaze = zvsaly_1.ahvsa[kn - 1];
	}
	return 0;
} /* vsansm_ */

/* Subroutine */ int rdnsm_(void)
{
	/* Format strings */
	static char fmt_900[] = "(\002  ML = \002,i5,\002  GT 24 ML RESET TO 2"
							"4\002)";
	static char fmt_80[] = "(f10.3,5e10.3,15a1)";
	static char fmt_81[] = "(f10.3,1p5e10.3,10x,15a1)";
	static char fmt_83[] = "(8e10.3)";
	static char fmt_84[] = "(1p8e10.3)";
	static char fmt_82[] = "(10x,3f10.3,4i5)";

	/* System generated locals */
	long i__1;

	/* Builtin functions */
	long s_wsfe(cilist *), do_fio(long *, char *, long), e_wsfe(void),
		s_rsfe(cilist *), e_rsfe(void);

	/* Local variables */
	static long k, km;
	extern long jou_(char *, long);
	static long iha1, ird0, icld1, isea1, ivul1;
	extern /* Subroutine */ int check_(float *, long *, long *);
	static char jchar[1 * 15];
	static float ahaze;
	static long iconv;
	static float rratz;
	extern /* Subroutine */ int defalt_(float *, float *, float *);
	static float eqlwcz;
	extern /* Subroutine */ int convrt_(float *, float *);

	/* Fortran I/O blocks */
	static cilist io___406 = {0, 0, 0, fmt_900, 0};
	static cilist io___412 = {0, 0, 0, fmt_80, 0};
	static cilist io___413 = {0, 0, 0, fmt_81, 0};
	static cilist io___414 = {0, 0, 0, fmt_83, 0};
	static cilist io___415 = {0, 0, 0, fmt_84, 0};
	static cilist io___416 = {0, 0, 0, fmt_82, 0};
	static cilist io___424 = {0, 0, 0, fmt_82, 0};

	/*                                                                       RDN  110 */
	/*     THIS SUBROUTINE READS MODEL 7 DATA WHEN ISVA EQ 1                 RDN  120 */
	/*                                                                       RDN  130 */
	if (cntrl_1.ml > 24)
	{
		io___406.ciunit = ifil_1.ipr;
		s_wsfe(&io___406);
		do_fio(&c__1, (char *)&cntrl_1.ml, (long)sizeof(long));
		e_wsfe();
		cntrl_1.ml = 24;
	}
	card1b_1.jlow = 1;
	i__1 = cntrl_1.ml;
	for (k = 1; k <= i__1; ++k)
	{
		for (km = 1; km <= 15; ++km)
		{
			*(unsigned char *)&jchar[km - 1] = ' ';
			if (km > 12)
			{
				goto L10;
			}
			card1b_1.wmol[km - 1] = 0.f;
		L10:;
		}
		ird0 = 1;
		iconv = 1;
		if ((float)card1_1.model > 0.f && card1_1.model < 7)
		{
			ird0 = 0;
		}
		if (ird0 == 1 && card2_1.ivsa == 1)
		{
			ird0 = 0;
			iconv = 0;
		}
		/*                                                                       RDN  430 */
		/*        PARAMETERS - JCHAR = INPUT KEY (SEE BELOW)                     RDN  440 */
		/*                                                                       RDN  450 */
		/*                                                                       RDN  460 */
		/*     ***  ROUTINE ALSO ACCEPTS VARIABLE UNITS ON PRESS AND TEMP        RDN  470 */
		/*                                                                       RDN  480 */
		/*          SEE INPUT KEY BELOW                                          RDN  490 */
		/*                                                                       RDN  500 */
		/*                                                                       RDN  510 */
		/*                                                                       RDN  520 */
		/*     FOR MOLECULAR SPECIES ONLY                                        RDN  530 */
		/*                                                                       RDN  540 */
		/*       JCHAR   JUNIT                                                   RDN  550 */
		/*                                                                       RDN  560 */
		/*     " ",A      10    VOLUME MIXING RATIO (PPMV)                       RDN  570 */
		/*         B      11    NUMBER DENSITY (CM-3)                            RDN  580 */
		/*         C      12    MASS MIXING RATIO (GM(K)/KG(AIR))                RDN  590 */
		/*         D      13    MASS DENSITY (GM M-3)                            RDN  600 */
		/*         E      14    PARTIAL PRESSURE (MB)                            RDN  610 */
		/*         F      15    DEW POINT TEMP (TD IN T(K)) - H2O ONLY           RDN  620 */
		/*         G      16     "    "     "  (TD IN T(C)) - H2O ONLY           RDN  630 */
		/*         H      17    RELATIVE HUMIDITY (RH IN PERCENT) - H2O ONLY     RDN  640 */
		/*         I      18    AVAILABLE FOR USER DEFINITION                    RDN  650 */
		/*        1-6    1-6    DEFAULT TO SPECIFIED MODEL ATMOSPHERE            RDN  660 */
		/*                                                                       RDN  670 */
		/*     ****************************************************************  RDN  680 */
		/*     ****************************************************************  RDN  690 */
		/*                                                                       RDN  700 */
		/*     ***** OTHER 'JCHAR' SPECIFICATIONS -                              RDN  710 */
		/*                                                                       RDN  720 */
		/*       JCHAR   JUNIT                                                   RDN  730 */
		/*                                                                       RDN  740 */
		/*      " ",A     10    PRESSURE IN (MB)                                 RDN  750 */
		/*          B     11       "     "  (ATM)                                RDN  760 */
		/*          C     12       "     "  (TORR)                               RDN  770 */
		/*         1-6   1-6    DEFAULT TO SPECIFIED MODEL ATMOSPHERE            RDN  780 */
		/*                                                                       RDN  790 */
		/*      " ",A     10    AMBIENT TEMPERATURE IN DEG(K)                    RDN  800 */
		/*          B     11       "         "       "  " (C)                    RDN  810 */
		/*          C     12       "         "       "  " (F)                    RDN  820 */
		/*         1-6   1-6    DEFAULT TO SPECIFIED MODEL ATMOSPHERE            RDN  830 */
		/*                                                                       RDN  840 */
		/*     ***** DEFINITION OF "DEFAULT" CHOICES FOR PROFILE SELECTION ***** RDN  850 */
		/*                                                                       RDN  860 */
		/*      FOR THE USER WHO WISHES TO ENTER ONLY SELECTED ORIGINAL          RDN  870 */
		/*      VERTICAL PROFILES AND WANTS STANDARD ATMOSPHERE SPECIFICATIONS   RDN  880 */
		/*      FOR THE OTHERS, THE FOLLOWING OPTION IS AVAILABLE                RDN  890 */
		/*                                                                       RDN  900 */
		/*     *** JCHAR(P,T OR K) MUST = 1-6 (AS ABOVE)                         RDN  910 */
		/*                                                                       RDN  920 */
		/*      FOR MOLECULES 8-35, ONLY US STD PROFILES ARE AVIALABLE           RDN  930 */
		/*      THEREFORE, WHEN  'JCHAR(K) = 1-5', JCHAR(K) WILL BE RESET TO 6   RDN  940 */
		/*                                                                       RDN  950 */
		/*                                                                       RDN  960 */
		PRINT_LINE_READ()
#ifdef DO_FIO_IN
		io___412.ciunit = ifil_1.ird;
		s_rsfe(&io___412);
		do_fio(&c__1, (char *)&nsinp_2.zmdl[k - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&nsinp_2.p[k - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&nsinp_2.t[k - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&card1b_1.wmol[0], (long)sizeof(float));
		do_fio(&c__1, (char *)&card1b_1.wmol[1], (long)sizeof(float));
		do_fio(&c__1, (char *)&card1b_1.wmol[2], (long)sizeof(float));
		for (km = 1; km <= 15; ++km)
		{
			do_fio(&c__1, jchar + (km - 1), (long)1);
		}
		e_rsfe();
#endif
		io___413.ciunit = ifil_1.ipr;
		s_wsfe(&io___413);
		do_fio(&c__1, (char *)&nsinp_2.zmdl[k - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&nsinp_2.p[k - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&nsinp_2.t[k - 1], (long)sizeof(float));
		do_fio(&c__1, (char *)&card1b_1.wmol[0], (long)sizeof(float));
		do_fio(&c__1, (char *)&card1b_1.wmol[1], (long)sizeof(float));
		do_fio(&c__1, (char *)&card1b_1.wmol[2], (long)sizeof(float));

		for (km = 1; km <= 15; ++km)
		{
			do_fio(&c__1, jchar + (km - 1), (long)1);
		}
		e_wsfe();
		if (nsinp_2.zmdl[k - 1] <= 2.f)
		{
			card1b_1.jlow = k;
		}
		if (card1a_1.ird1 == 1)
		{
#if DO_FIO_IN
			io___414.ciunit = ifil_1.ird;
			s_rsfe(&io___414);
			for (km = 4; km <= 12; ++km)
			{

				do_fio(&c__1, (char *)&card1b_1.wmol[km - 1], (long)sizeof(float));
			}
			e_rsfe();
			io___415.ciunit = ifil_1.ipr;
			s_wsfe(&io___415);
			for (km = 4; km <= 12; ++km)
			{

				do_fio(&c__1, (char *)&card1b_1.wmol[km - 1], (long)sizeof(float));
			}
			e_wsfe();
#endif
		}
		/*                                                                       RDN 1100 */
		/*                                                                       RDN 1110 */
		/*     AHAZE =  AEROSOL VISIBLE EXTINCTION COFF (KM-1)                   RDN 1120 */
		/*     AT A WAVELENGTH OF 0.55 MICROMETERS                               RDN 1130 */
		/*                                                                       RDN 1140 */
		/*     EQLWCZ=LIQUID WATER CONTENT (PPMV) AT ALT Z                       RDN 1150 */
		/*            FOR AEROSOL, CLOUD OR FOG MODELS                           RDN 1160 */
		/*                                                                       RDN 1170 */
		/*     RRATZ=RAIN RATE (MM/HR) AT ALT Z                                  RDN 1180 */
		/*                                                                       RDN 1190 */
		/*     IHA1 AEROSOL MODEL USED FOR SPECTRAL DEPENDENCE OF EXTINCTION     RDN 1200 */
		/*                                                                       RDN 1210 */
		/*     IVUL1 STRATOSPHERIC AERSOL MODEL USED FOR SPECTRAL DEPENDENCE     RDN 1220 */
		/*     OF EXT AT Z                                                       RDN 1230 */
		/*                                                                       RDN 1240 */
		/*     ICLD1 CLOUD MODEL USED FOR SPECTRAL DEPENDENCE OF EXT AT Z        RDN 1250 */
		/*                                                                       RDN 1260 */
		/*     ONLY ONE OF IHA1,ICLD1  OR IVUL1 IS ALLOWED                       RDN 1270 */
		/*     IHA1 NE 0 OTHERS IGNORED                                          RDN 1280 */
		/*     IHA1 EQ 0 AND ICLD1 NE 0 USE ICLD1                                RDN 1290 */
		/*                                                                       RDN 1300 */
		/*     IF AHAZE AND EQLWCZ ARE BOUTH ZERO                                RDN 1310 */
		/*        DEFAULT PROFILE ARE LOADED FROM IHA1,ICLD1,IVUL1               RDN 1320 */
		/*     ISEA1 = AERSOL SEASON CONTROL FOR ALTITUDE Z                      RDN 1330 */
		/*                                                                       RDN 1340 */
		if (card1a_1.ird2 == 1)
		{
			PRINT_LINE_READ();
#ifdef DO_FIO_IN
			io___416.ciunit = ifil_1.ird;
			s_rsfe(&io___416);
			do_fio(&c__1, (char *)&ahaze, (long)sizeof(float));
			do_fio(&c__1, (char *)&eqlwcz, (long)sizeof(float));
			do_fio(&c__1, (char *)&rratz, (long)sizeof(float));
			do_fio(&c__1, (char *)&iha1, (long)sizeof(long));
			do_fio(&c__1, (char *)&icld1, (long)sizeof(long));
			do_fio(&c__1, (char *)&ivul1, (long)sizeof(long));
			do_fio(&c__1, (char *)&isea1, (long)sizeof(long));
			e_rsfe();
#endif
			io___424.ciunit = ifil_1.ipr;
			s_wsfe(&io___424);
			do_fio(&c__1, (char *)&ahaze, (long)sizeof(float));
			do_fio(&c__1, (char *)&eqlwcz, (long)sizeof(float));
			do_fio(&c__1, (char *)&rratz, (long)sizeof(float));
			do_fio(&c__1, (char *)&iha1, (long)sizeof(long));
			do_fio(&c__1, (char *)&icld1, (long)sizeof(long));
			do_fio(&c__1, (char *)&ivul1, (long)sizeof(long));
			do_fio(&c__1, (char *)&isea1, (long)sizeof(long));
			e_wsfe();
		}
		for (km = 1; km <= 15; ++km)
		{
			/* L12: */
			card1b_1.junit[km - 1] = jou_(jchar + (km - 1), (long)1);
		}
		if (card1_1.m1 != 0)
		{
			card1b_1.junit[0] = card1_1.m1;
		}
		if (card1_1.m1 != 0)
		{
			card1b_1.junit[1] = card1_1.m1;
		}
		check_(&nsinp_2.p[k - 1], card1b_1.junit, &c__1);
		check_(&nsinp_2.t[k - 1], &card1b_1.junit[1], &c__2);
		defalt_(&nsinp_2.zmdl[k - 1], &nsinp_2.p[k - 1], &nsinp_2.t[k - 1]);

		convrt_(&nsinp_2.p[k - 1], &nsinp_2.t[k - 1]);
		for (km = 1; km <= 12; ++km)
		{
			/* L20: */
			nsinp_2.wmdl[k + km * 40 - 41] = card1b_1.wmol[km - 1];
		}
		nsinp_2.wmdl[k + 479] = card1b_1.wair1;
		/* L200: */
	}
	return 0;
} /* rdnsm_ */

/* Subroutine */ int defalt_(float *z__, float *p, float *t)
{

	/* Format strings */
	static char fmt_80[] = "(/,\002   *** Z IS GREATER THAN 120 KM ***, Z ="
						   " \002,f10.3)";

	/* System generated locals */
	long i__1;

	/* Builtin functions */
	long s_wsfe(cilist *), do_fio(long *, char *, long), e_wsfe(void);
	/* Subroutine */ int s_stop(char *, long);
	double log(double), exp(double);

	/* Local variables */
	static long k;
	static float a1, a2, a3, a4;
	static long i0, i1, i2, i3;
	static float x1, x2, x3, x4, z0, z1, z2, z3;
	static long im, im50, itr;
	static float den1, den2, den3, den4;
	static long matm, nmol, ilower, iupper;

	/* Fortran I/O blocks */
	static cilist io___441 = {0, 0, 0, fmt_80, 0};

	/*                                                                       DEF  110 */
	/*     ******************************************************************DEF  120 */
	/*                                                                       DEF  130 */
	/*     THIS SUBROUTINE LOADS ONE OF THE 6 BUILT IN ATMOSPHERIC PROFILES  DEF  140 */
	/*     FROM WHICH IT WILL INTERPOLATE "DEFAULT" VALUES FOR ALTITUDE "Z"  DEF  150 */
	/*                                                                       DEF  160 */
	/*                                                                       DEF  170 */
	/*      ***  THIS SUBROUTINE IS CALLED BY "RDUNIT" WHICH                 DEF  180 */
	/*      ***  READS USER SUPPLIED INPUT PROFILES OR SINGLE VALUES         DEF  190 */
	/*      ***  UNDER "MODEL = 0     " SPECIFICATIONS                       DEF  200 */
	/*                                                                       DEF  210 */
	/*      *** SEE DOCUMENTATION FOR CLARIFICATION ***                      DEF  220 */
	/*                                                                       DEF  230 */
	/*     SUBROUTINE "DEFALT"IS TRIGGERRED WHENEVER ANY ONE OF              DEF  240 */
	/*     THE INPUT PARAMETERS JCHARP, JCART, (JCHAR(K),K=1,NMOL) IS = 1-6  DEF  250 */
	/*                                                                       DEF  260 */
	/*     FOR SIMPLICITY, ALL INTERPOLATIONS ARE DONE AT ONE TIME BECAUSE   DEF  270 */
	/*     THE LAGRANGE WEIGHTS (4PT), BASED ON (ALT-Z), REMAIN UNCHANGED    DEF  280 */
	/*                                                                       DEF  290 */
	/*                   JCHAR(K) FOR K<8 ALLOW MODEL-DEPENDENT CHOICES      DEF  300 */
	/*                                                                       DEF  310 */
	/*                   JCHAR=JUNIT                                         DEF  320 */
	/*                                                                       DEF  330 */
	/*                        1       CHOOSES TROPICAL                       DEF  340 */
	/*                        2         "     MID-LATITUDE SUMMER            DEF  350 */
	/*                        3         "     MID-LATITUDE WINTER            DEF  360 */
	/*                        4         "     HIGH-LAT SUMMER                DEF  370 */
	/*                        5         "     HIGH-LAT WINTER                DEF  380 */
	/*                        6         "     US STANDARD                    DEF  390 */
	/*                                                                       DEF  400 */
	/*                                                                       DEF  410 */
	/*    JUNIT(K) FOR K>7 CHOOSES FROM THE SINGLE TRACE CONSTITUENT         DEF  420 */
	/*        PROFILES, ALL APPRORIATE FOR THE US STD ATMOSPHERE             DEF  430 */
	/*                                                                       DEF  440 */
	/*     ***  NOTE ***  T<0 WILL ALSO PRINT OUT A MESSAGE INDICATING       DEF  450 */
	/*     ***  A POSSIBLE MISAPPLICATION OF TEMPERATURE UNITS, (K) VS (C)   DEF  460 */
	/*                                                                       DEF  470 */
	/*     ******************************************************************DEF  480 */
	/*                                                                       DEF  530 */
	/*                                                                       DEF  550 */
	/*     *** 4PT INTERPOLATION FUNCTION                                    DEF  560 */
	/*                                                                       DEF  570 */
	/*                                                                       DEF  590 */
	/*                                                                       DEF  600 */
	nmol = 12;
	ilower = 0;
	iupper = 0;
	im50 = 50;
	i__1 = im50;
	for (im = 2; im <= i__1; ++im)
	{
		i2 = im;
		if (mlatm_1.alt[im - 1] >= *z__)
		{
			goto L20;
		}
		/* L15: */
	}
	i2 = im50;
L20:
	i1 = i2 - 1;
	i0 = i2 - 2;
	i3 = i2 + 1;
	if (i0 < 1)
	{
		goto L25;
	}
	if (i3 > im50)
	{
		goto L26;
	}
	/*                                                                       DEF  750 */
	goto L28;
/*                                                                       DEF  770 */
/*     LOWER ENDPOINT CORRECTION                                         DEF  780 */
/*                                                                       DEF  790 */
L25:
	ilower = 1;
	i0 = i1;
	i1 = i2;
	i2 = i3;
	++i3;
	goto L28;
/*                                                                       DEF  870 */
/*     UPPER ENDPOINT CORRECTION                                         DEF  880 */
/*                                                                       DEF  890 */
L26:
	iupper = 1;
	if (*z__ > mlatm_1.alt[im50 - 1])
	{
		goto L29;
	}
	i3 = i2;
	i2 = i1;
	i1 = i0;
	i0 = i1 - 1;
	goto L28;
/*                                                                       DEF  980 */
/*      UPPER ENDPOINT EXTRAPOLATION                                     DEF  990 */
/*                                                                       DEF 1000 */
L29:
	z0 = mlatm_1.alt[i0 - 1];
	z1 = mlatm_1.alt[i1 - 1];
	z2 = mlatm_1.alt[i2 - 1];
	z3 = z2 + (*z__ - z2) * 2.f;
	iupper = 2;
	io___441.ciunit = ifil_1.ipr;
	s_wsfe(&io___441);
	do_fio(&c__1, (char *)&(*z__), (long)sizeof(float));
	e_wsfe();
	s_stop((char *)"DEFAULTZ", (long)8);
/*     I3=I2                                                             DEF 1100 */
/*     GO TO 31                                                          DEF 1110 */
/*                                                                       DEF 1120 */
/*     LAGRANGE CONTINUATION                                             DEF 1130 */
/*                                                                       DEF 1140 */
L28:
	/*                                                                       DEF 1160 */
	/*      LAGRANGE COEF DETERMINATION                                      DEF 1170 */
	/*                                                                       DEF 1180 */
	z1 = mlatm_1.alt[i1 - 1];
	z2 = mlatm_1.alt[i2 - 1];
	z0 = mlatm_1.alt[i0 - 1];
	z3 = mlatm_1.alt[i3 - 1];
	/* L31: */
	den1 = (z0 - z1) * (z0 - z2) * (z0 - z3);
	den2 = (z1 - z2) * (z1 - z3) * (z1 - z0);
	den3 = (z2 - z3) * (z2 - z0) * (z2 - z1);
	den4 = (z3 - z0) * (z3 - z1) * (z3 - z2);
	a1 = (*z__ - z1) * (*z__ - z2) * (*z__ - z3) / den1;
	a2 = (*z__ - z2) * (*z__ - z3) * (*z__ - z0) / den2;
	a3 = (*z__ - z3) * (*z__ - z0) * (*z__ - z1) / den3;
	a4 = (*z__ - z0) * (*z__ - z1) * (*z__ - z2) / den4;
	/*                                                                       DEF 1320 */
	/*                                                                       DEF 1330 */
	/*     TEST INPUT PARAMETERS (JUNIT'S) SEQUENTIALLY FOR TRIGGER          DEF 1340 */
	/*      I.E.  JUNIT(P,T,K) = 1-6                                         DEF 1350 */
	/*                                                                       DEF 1360 */
	if (card1b_5.junitp > 6)
	{
		goto L35;
	}
	matm = card1b_5.junitp;
	/*     WRITE (IPR,60) Z,MATM                                             DEF 1390 */
	x1 = log(mlatm_1.pmatm[i0 + matm * 50 - 51]);
	x2 = log(mlatm_1.pmatm[i1 + matm * 50 - 51]);
	x3 = log(mlatm_1.pmatm[i2 + matm * 50 - 51]);
	x4 = log(mlatm_1.pmatm[i3 + matm * 50 - 51]);
	if (iupper == 2)
	{
		x4 = x3 + (x3 - x2) * 2;
	}
	*p = a1 * x1 + a2 * x2 + a3 * x3 + a4 * x4;
	*p = exp(*p);
L35:
	if (card1b_5.junitt > 6)
	{
		goto L40;
	}
	matm = card1b_5.junitt;
	/*     WRITE (IPR,65) Z,MATM                                             DEF 1490 */
	x1 = mlatm_1.tmatm[i0 + matm * 50 - 51];
	x2 = mlatm_1.tmatm[i1 + matm * 50 - 51];
	x3 = mlatm_1.tmatm[i2 + matm * 50 - 51];
	x4 = mlatm_1.tmatm[i3 + matm * 50 - 51];
	*t = a1 * x1 + a2 * x2 + a3 * x3 + a4 * x4;
L40:
	i__1 = nmol;
	for (k = 1; k <= i__1; ++k)
	{
		if (card1b_5.junit[k - 1] > 6)
		{
			goto L55;
		}
		/*                                                                       DEF 1570 */
		if (k > 7)
		{
			goto L45;
		}
		matm = card1b_5.junit[k - 1];
		/*                                                                       DEF 1600 */
		x1 = mlatm_1.amol[i0 + (k + (matm << 3)) * 50 - 451];
		x2 = mlatm_1.amol[i1 + (k + (matm << 3)) * 50 - 451];
		x3 = mlatm_1.amol[i2 + (k + (matm << 3)) * 50 - 451];
		x4 = mlatm_1.amol[i3 + (k + (matm << 3)) * 50 - 451];
		goto L50;
	L45:
		itr = k - 7;
		matm = 6;
		/*                                                                       DEF 1680 */
		x1 = trac_2.trac[i0 + itr * 50 - 51];
		x2 = trac_2.trac[i1 + itr * 50 - 51];
		x3 = trac_2.trac[i2 + itr * 50 - 51];
		x4 = trac_2.trac[i3 + itr * 50 - 51];
	L50:
		card1b_5.wmol[k - 1] = a1 * x1 + a2 * x2 + a3 * x3 + a4 * x4;
		card1b_5.junit[k - 1] = 10;
		goto L55;
	/*  53 JUNIT(K)=10                                                       DEF 1760 */
	/*     WRITE(IPR,54)K                                                    DEF 1770 */
	/*  54 FORMAT('  **** INCONSISTENCY IN THE USER SPECIFICATION',          DEF 1780 */
	/*    A ' , JUNIT = 9 AND WMOL(K) = 0 , K =',I2,/,                       DEF 1790 */
	/*    B '  ****   DENNUM(K) HAS BEEN SET TO 0, NOT DEFAULT VALUE')       DEF 1800 */
	L55:;
	}
	card1b_5.wmol[11] *= 1e3f;
	/*     THE UNIT FOR NEW PROFILE IS PPMV.                                 DEF 1830 */
	return 0;
	/* 100  CONTINUE                                                          DEF 1850 */
	/* L110: */
	/*     STOP'DEFAULT'                                                     DEF 1900 */
	/*                                                                       DEF 1910 */
	/* L60: */
	/* L65: */
	/* L70: */
} /* defalt_ */

/* Subroutine */ int aerprf_(long *i__, float *vis, float *haze, long *ihaze, long *iseasn, long *ivulcn, long *n)
{
	/* Initialized data */

	static float vs[5] = {50.f, 23.f, 10.f, 5.f, 2.f};

	static long j;
	static float hazi, const__;

	/* ***********************************************************************AER  110 */
	/*     WILL COMPUTE DENSITY    PROFILES FOR AEROSOLS                     AER  120 */
	/* ***********************************************************************AER  130 */
	*haze = 0.f;
	*n = 7;
	if (*ihaze == 0)
	{
		return 0;
	}
	if (prfd_1.zht[*i__ - 1] > 2.f)
	{
		goto L15;
	}
	for (j = 2; j <= 5; ++j)
	{
		if (*vis >= vs[j - 1])
		{
			goto L10;
		}
		/* L5: */
	}
	j = 5;
L10:
	const__ = 1.f / (1.f / vs[j - 1] - 1.f / vs[j - 2]);
	*haze = const__ * ((prfd_1.hz2k[*i__ + j * 34 - 35] - prfd_1.hz2k[*i__ + (j - 1) * 34 - 35]) / *vis + prfd_1.hz2k[*i__ + (j - 1) * 34 - 35] / vs[j - 1] - prfd_1.hz2k[*i__ + j * 34 - 35] / vs[j - 2]);
	if (prfd_1.zht[*i__ - 1] > 2.f)
	{
		goto L15;
	}
	return 0;
L15:
	if (prfd_1.zht[*i__ - 1] > 10.f)
	{
		goto L35;
	}
	const__ = 42.592592592592595f;
	if (*iseasn > 1)
	{
		goto L25;
	}
	if (*vis <= 23.f)
	{
		hazi = prfd_1.spsu23[*i__ - 1];
	}
	if (*vis <= 23.f)
	{
		goto L200;
	}
	if (prfd_1.zht[*i__ - 1] > 4.f)
	{
		goto L20;
	}
	hazi = const__ * ((prfd_1.spsu23[*i__ - 1] - prfd_1.spsu50[*i__ - 1]) / *vis + prfd_1.spsu50[*i__ - 1] / 23.f - prfd_1.spsu23[*i__ - 1] / 50.f);
	goto L200;
L20:
	hazi = prfd_1.spsu50[*i__ - 1];
	goto L200;
L25:
	if (*vis <= 23.f)
	{
		hazi = prfd_1.fawi23[*i__ - 1];
	}
	if (*vis <= 23.f)
	{
		goto L200;
	}
	if (prfd_1.zht[*i__ - 1] > 4.f)
	{
		goto L30;
	}
	hazi = const__ * ((prfd_1.fawi23[*i__ - 1] - prfd_1.fawi50[*i__ - 1]) / *vis + prfd_1.fawi50[*i__ - 1] / 23.f - prfd_1.fawi23[*i__ - 1] / 50.f);
	goto L200;
L30:
	hazi = prfd_1.fawi50[*i__ - 1];
	goto L200;
L35:
	if (prfd_1.zht[*i__ - 1] > 30.f)
	{
		goto L75;
	}
	hazi = prfd_1.bastss[*i__ - 1];
	if (*iseasn > 1)
	{
		goto L55;
	}
	if (*ivulcn == 0)
	{
		hazi = prfd_1.bastss[*i__ - 1];
	}
	if (*ivulcn == 0)
	{
		goto L200;
	}
	switch (*ivulcn)
	{
	case 1:
		goto L40;
	case 2:
		goto L45;
	case 3:
		goto L50;
	case 4:
		goto L50;
	case 5:
		goto L45;
	case 6:
		goto L45;
	case 7:
		goto L50;
	case 8:
		goto L52;
	}
L40:
	hazi = prfd_1.bastss[*i__ - 1];
	goto L200;
L45:
	hazi = prfd_1.vumoss[*i__ - 1];
	goto L200;
L50:
	hazi = prfd_1.hivuss[*i__ - 1];
	goto L200;
L52:
	hazi = prfd_1.exvuss[*i__ - 1];
	goto L200;
L55:
	if (*ivulcn == 0)
	{
		hazi = prfd_1.bastfw[*i__ - 1];
	}
	if (*ivulcn == 0)
	{
		goto L200;
	}
	switch (*ivulcn)
	{
	case 1:
		goto L60;
	case 2:
		goto L65;
	case 3:
		goto L70;
	case 4:
		goto L70;
	case 5:
		goto L65;
	case 6:
		goto L65;
	case 7:
		goto L70;
	case 8:
		goto L72;
	}
L60:
	hazi = prfd_1.bastfw[*i__ - 1];
	goto L200;
L65:
	hazi = prfd_1.vumofw[*i__ - 1];
	goto L200;
L70:
	hazi = prfd_1.hivufw[*i__ - 1];
	goto L200;
L72:
	hazi = prfd_1.exvufw[*i__ - 1];
	goto L200;
L75:
	*n = 14;
	if (*ivulcn > 1)
	{
		goto L80;
	}
	hazi = prfd_1.upnatm[*i__ - 1];
	goto L200;
L80:
	hazi = prfd_1.vutono[*i__ - 1];
L200:
	if (hazi > 0.f)
	{
		*haze = hazi;
	}
	return 0;
} /* aerprf_ */

/* Subroutine */ int geo_(long *ierror, float *bendng, long *maxgeo)
{
	/* Initialized data */

	static long kmol[17] = {1, 2, 3, 11, 8, 5, 9, 10, 4, 6, 7, 12, 13, 14, 16, 15, 17};

	/* Format strings */
	static char fmt_36[] = "(\0020HORIZONTAL PATH AT ALTITUDE = \002,f10.3"
						   ",\002 KM WITH RANGE = \002,f10.3,\002 KM, MODEL = \002,i3)";
	static char fmt_38[] = "(\0020GEO:  IERROR NE 0: END THIS CALCULATION AN"
						   "D SKIP TO\002,\002 THE NEXT CASE\002)";
	static char fmt_42[] = "(////,\002 CUMULATIVE ABSORBER AMOUNTS FOR THE P"
						   "ATH FROM\002,\002 H1 TO Z\002,//,t3,\002J\002,t9,\002Z\002,t18"
						   ",\002TBAR\002,t27,\002HNO3\002,t39,\002O3 UV\002,t50,\002CNTMSLF"
						   "1 \002,t061,\002CNTMSLF2\002,t73,\002CNTMFRN\002,t86,\002O2\002,"
						   "/,t8,\002(KM)\002,t19,\002(K)\002,t25,\002(ATM CM)\002,t37,\002("
						   "ATM CM)\002,t49,\002(MOL CM-2)\002,t61,\002(MOL CM-2)\002,t73"
						   ",\002(MOL CM-2)\002,t83,\002(MOL CM-2)\002/)";
	static char fmt_44[] = "(i3,f9.3,f9.2,1p8e12.3)";
	static char fmt_46[] = "(///,t3,\002J\002,t09,\002Z\002,t17,\002N2 CON"
						   "T\002,t28,\002MOL SCAT\002,t43,\002AER 1\002,t55,\002AER 2\002,t"
						   "67,\002AER 3\002,t79,\002AER 4\002,t091,\002CIRRUS\002,/,t8,\002"
						   "(KM)\002,/)";
	static char fmt_48[] = "(i3,f9.3,1p7e12.3)";
	static char fmt_47[] = "(///\002   J    Z       H2O       O3        CO2 "
						   "      CO    \002,\002    CH4       N2O       O2        NH3      "
						   " NO        NO2   \002,\002    SO2\002/\002      (KM)   (G/CM**2)"
						   "  (                           \002,\002                 ATM CM  "
						   "                                   \002,\002        )\002/)";
	static char fmt_49[] = "(i4,f8.2,1p11e10.2)";
	static char fmt_40[] = "(//,\0020SUMMARY OF THE GEOMETRY CALCULATION\002"
						   ",//,10x,\002H1      = \002,f10.3,\002 KM\002,/,10x,\002H2      = "
						   "\002,f10.3,\002 KM\002,/,10x,\002ANGLE   = \002,f10.3,\002 DE"
						   "G\002,/,10x,\002RANGE   = \002,f10.3,\002 KM\002,/,10x,\002BETA "
						   "   = \002,f10.3,\002 DEG\002,/,10x,\002PHI     = \002,f10.3,\002"
						   " DEG\002,/,10x,\002HMIN    = \002,f10.3,\002 KM\002,/,10x,\002BE"
						   "NDING = \002,f10.3,\002 DEG\002,/,10x,\002LEN     = \002,i10)";
	static char fmt_50[] = "(////,\002 EQUIVALENT SEA LEVEL TOTAL ABSORBER A"
						   "MOUNTS\002,//,t18,\002HNO3\002,t28,\002O3 UV\002,t40,\002CNTMSLF1"
						   "\002,t52,\002CNTMSLF2\002,t63,\002CNTMFRN\002,/,t16,\002(ATM CM"
						   ")\002,t27,\002(ATM CM)\002,t40,\002(MOL CM-2)\002,t52,\002(MOL C"
						   "M-2)\002,t64,\002(MOL CM-2)\002,t76,\002(MOL CM-2)\002,//,10x,1p"
						   "5e12.3,///,t15,\002N2 CONT\002,t26,\002MOL SCAT\002,t41,\002AER 1"
						   "\002,t53,\002AER 2\002,t65,\002AER 3\002,t77,\002AER 4\002,t87"
						   ",\002CIRRUS\002,t99,\002MEAN RH\002/,t99,\002(PRCNT)\002,//,10x,"
						   "1p7e12.3,0pf12.2)";
	static char fmt_60[] = "(//t18,\002H2O\002,t29,\002O3\002,t41,\002CO2"
						   "\002,t53,\002CO\002,t65,\002CH4\002,t77,\002N2O\002,t90,\002O"
						   "2\002,/t15,\002(G/CM**2)\002,t29,\002(\002,t57,\002ATM CM\002,t9"
						   "1,\002)\002,//10x,1p7e12.3,//t18,\002NH3\002,t29,\002NO\002,t41"
						   ",\002NO2\002,t53,\002SO2\002,/t18,\002(\002,t34,\002ATM CM\002,t"
						   "55,\002)\002,//10x,1p4e12.3)";
	static char fmt_900[] = "(//\002  CURRENT GEOMETRY DIMENSION \002,i5,/"
							",\002 JMAXST = \002,i5,\002 RESET AVTRAT TDIFF1 TDIFF2 TO 2. 10."
							" 20.\002)";

	/* System generated locals */
	long i__1, i__2;
	float r__1;

	/* Builtin functions */
	long s_wsfe(cilist *), do_fio(long *, char *, long), e_wsfe(void);
	double exp(double);
	/* Subroutine */ int s_stop(char *, long);

	/* Local variables */
	static long i__, j, k, l, i2, i1, j1, ik, il, lp, lz;
	static float w15;
	static long ih1, ii1, ih2;
	static float fac, phi;
	static long ldel, iamt;
	static float hmin;
	static long jmax;
	static float wtem;
	static long immax, jmaxp1;
	extern /* Subroutine */ int geoinp_(float *, float *, float *, float *, float *, long *, long *, float *, float *, long *), rfpath_(float *, float *, float *, float *, long *, float *, long *, float *,
																																		float *, float *);
	static long jmaxst;
	extern /* Subroutine */ int expint_(float *, float *, float *, float *);
	static float amttot;

	/* Fortran I/O blocks */
	static cilist io___469 = {0, 0, 0, fmt_36, 0};
	static cilist io___474 = {0, 0, 0, fmt_38, 0};
	static cilist io___485 = {0, 0, 0, fmt_42, 0};
	static cilist io___488 = {0, 0, 0, fmt_44, 0};
	static cilist io___489 = {0, 0, 0, fmt_46, 0};
	static cilist io___490 = {0, 0, 0, fmt_48, 0};
	static cilist io___491 = {0, 0, 0, fmt_47, 0};
	static cilist io___492 = {0, 0, 0, fmt_49, 0};
	static cilist io___493 = {0, 0, 0, fmt_40, 0};
	static cilist io___495 = {0, 0, 0, fmt_50, 0};
	static cilist io___496 = {0, 0, 0, fmt_60, 0};
	static cilist io___497 = {0, 0, 0, fmt_900, 0};

	/* *********************************************************************  GEO  110 */
	/*     THIS SUBROUTINE SERVES AS AN INTERFACE BETWEEN THE MAIN           GEO  120 */
	/*     LOWTRAN7 PROGRAM 'LWTRN7' AND THE NEW SET OF SUBROUTINES,         GEO  130 */
	/*     INCLUDING 'GEOINP', 'REDUCE', 'FDBETA', 'EXPINT', 'FNDHMN',       GEO  140 */
	/*     'FINDSH', 'SCALHT', 'ANDEX', 'RADREF', 'RFPATH', 'FILL',          GEO  150 */
	/*     AND 'LAYER',  WHICH CALCULATE THE ABSORBER                        GEO  160 */
	/*     AMOUNTS FOR A REFRACTED PATH THROUGH THE ATMOSPHERE.              GEO  170 */
	/*     THE INPUT PARAMETERS ITYPE, H1, H2, ANGLE, RANGE, BETA, AND LEN   GEO  180 */
	/*     ALL FUNCTION IN THE SAME WAY IN THE NEW ROUTINES AS IN THE OLD.   GEO  190 */
	/* *********************************************************************  GEO  200 */
	/*     *** IN COLM 73-76 MARK IMPROVED 32 BIT CONVERGANCE OF BETA        GEO  201 */
	/*     SUGESTED BY TONY WARRIC             MCDONNELL DUGLAS              GEO  202 */
	/*     AND  MAJ ROBERT G. HUGES            AFWAL/WEA                     GEO  203 */
	/* ***********************************************************************GEO  204 */
	/* *****KMOL(K) IS A POINTER USED TO REORDER THE AMOUNTS WHEN PRINTING    GEO  430 */
	/* *****INITIALIZE CONSTANTS AND CLEAR CUMULATIVE VARIABLES               GEO  450 */
	/* *****DELTAS IS THE NOMINAL PATH LENGTH INCRENMENT USED IN THE RAY TRACEGEO  460 */
	parmtr_1.deltas = 5.f;
	jmaxst = 1;
	*ierror = 0;
	parmtr_1.re = card3_1.re;
	parmtr_1.imod = cntrl_1.ml;
	parmtr_1.imax = cntrl_1.ml;
	/* *****ZERO OUT CUMULATIVE VARIABLES                                     GEO  530 */
	for (i__ = 1; i__ <= 35; ++i__)
	{
		sols_1.lj[i__ - 1] = 0;
		rfrpth_1.sp[i__ - 1] = 0.f;
		rfrpth_1.ppsum[i__ - 1] = 0.f;
		rfrpth_1.tpsum[i__ - 1] = 0.f;
		rfrpth_1.rhopsm[i__ - 1] = 0.f;
		i__1 = cntrl_1.kmax;
		for (k = 1; k <= i__1; ++k)
		{
			rfrpth_1.amtp[k + i__ * 63 - 64] = 0.f;
			/* L100: */
		}
	}
	parmtr_1.zmax = model_1.zm[parmtr_1.imax - 1];
	if (cntrl_1.issgeo == 1)
	{
		goto L200;
	}
	if (card1_1.itype >= 2)
	{
		goto L200;
	}
	/* *****HORIZONTAL PATH, MODEL EQ 1 TO 7:  INTERPOLATE PROFILE TO H1      GEO  660 */
	rfrpth_1.zp[0] = card3_1.h1;
	if (cntrl_1.ml == 1)
	{
		rfrpth_1.pp[0] = model_1.pm[0];
		rfrpth_1.tp[0] = model_1.tm[0];
		sols_1.lj[0] = 1;
		rfrpth_1.sp[0] = card3_1.range;
		path_1.pl[0] = card3_1.range;
	}
	else
	{
		if (card1_1.model == 0)
		{
			goto L145;
		}
		i__1 = cntrl_1.ml;
		for (i__ = 2; i__ <= i__1; ++i__)
		{
			i2 = i__;
			if (card3_1.h1 < model_1.zm[i__ - 1])
			{
				goto L130;
			}
			/* L120: */
		}
	L130:
		i1 = i2 - 1;
		fac = (card3_1.h1 - model_1.zm[i1 - 1]) / (model_1.zm[i2 - 1] -
												   model_1.zm[i1 - 1]);
		expint_(rfrpth_1.pp, &model_1.pm[i1 - 1], &model_1.pm[i2 - 1], &fac);
		rfrpth_1.tp[0] = model_1.tm[i1 - 1] + (model_1.tm[i2 - 1] -
											   model_1.tm[i1 - 1]) *
												  fac;
		ii1 = i1;
		if (fac > .5f)
		{
			ii1 = i2;
		}
		sols_1.lj[0] = ii1;
		rfrpth_1.sp[ii1 - 1] = card3_1.range;
		i__1 = cntrl_1.kmax;
		for (k = 1; k <= i__1; ++k)
		{
			expint_(&rfrpth_1.denp[k - 1], &model_1.densty[k + i1 * 63 - 64],
					&model_1.densty[k + i2 * 63 - 64], &fac);
			/* L140: */
		}
	}
/* *****CALCULATE ABSORBER AMOUNTS FOR A HORIZONTAL PATH                  GEO  930 */
L145:
	io___469.ciunit = ifil_1.ipr;
	s_wsfe(&io___469);
	do_fio(&c__1, (char *)&card3_1.h1, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.range, (long)sizeof(float));
	do_fio(&c__1, (char *)&card1_1.model, (long)sizeof(long));
	e_wsfe();
	cntrl_1.ikmax = 1;
	immax = 1;
	if (card1_1.model == 0)
	{
		rfrpth_1.tp[0] = model_1.tm[0];
	}
	_BLNK__1.tbby[0] = rfrpth_1.tp[0];
	i__1 = cntrl_1.kmax;
	for (k = 1; k <= i__1; ++k)
	{
		if (cntrl_1.ml == 1)
		{
			rfrpth_1.denp[k - 1] = model_1.densty[k - 1];
		}
		_BLNK__1.w[k - 1] = rfrpth_1.denp[k - 1] * card3_1.range;
		_BLNK__1.wpath[k * 68 - 68] = _BLNK__1.w[k - 1];
		/* L160: */
	}
	wtem = (296.f - rfrpth_1.tp[0]) / 36.f;
	if (wtem < 0.f)
	{
		wtem = 0.f;
	}
	if (wtem > 1.f)
	{
		wtem = 1.f;
	}
	_BLNK__1.w[8] = _BLNK__1.w[4] * wtem;
	_BLNK__1.w[58] = _BLNK__1.w[7] * .269f * (rfrpth_1.tp[0] - 273.15f);
	/* Computing 2nd power */
	r__1 = rfrpth_1.tp[0] - 273.15f;
	_BLNK__1.w[59] = _BLNK__1.w[7] * .269f * (r__1 * r__1);
	_BLNK__1.wpath[544] = _BLNK__1.w[8];
	_BLNK__1.wpath[3944] = _BLNK__1.w[58];
	_BLNK__1.wpath[4012] = _BLNK__1.w[59];
	goto L320;
L200:
	/* *****SLANT PATH SELECTED                                               GEO 1170 */
	/* *****INTERPRET SLANT PATH PARAMETERS                                   GEO 1180 */
	geoinp_(&card3_1.h1, &card3_1.h2, &card3_1.angle, &card3_1.range, &card3_1.beta, &card1_1.itype, &card3_1.len, &hmin, &phi, ierror);
	if (*ierror == 0)
	{
		goto L210;
	}
	if (cntrl_1.issgeo != 1)
	{
		io___474.ciunit = ifil_1.ipr;
		s_wsfe(&io___474);
		e_wsfe();
	}
	return 0;
L210:
	/* *****CALCULATE THE PATH THROUGH THE ATMOSPHERE                         GEO 1260 */
	iamt = 1;
	rfpath_(&card3_1.h1, &card3_1.h2, &card3_1.angle, &phi, &card3_1.len, &hmin, &iamt, &card3_1.beta, &card3_1.range, bendng);
	/* *****UNFOLD LAYER AMOUNTS IN AMTP INTO THE CUMULATIVE                  GEO 1290 */
	/* *****AMOUNTS IN WPATH FROM H1 TO H2                                    GEO 1300 */
	i__1 = parmtr_1.ipath;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		if (card3_1.h1 == rfrpth_1.zp[i__ - 1])
		{
			ih1 = i__;
		}
		if (card3_1.h2 == rfrpth_1.zp[i__ - 1])
		{
			ih2 = i__;
		}
		/* L220: */
	}
	jmax = parmtr_1.ipath - 1 + card3_1.len * (min(ih1, ih2) - 1);
	cntrl_1.ikmax = jmax;
	/* *****DETERMINE LJ(J), WHICH IS THE NUMBER OF THE LAYER IN AMTP(K,L),   GEO 1370 */
	/* *****STARTING FROM HMIN, WHICH CORRESPONDS TO THE LAYER J IN           GEO 1380 */
	/* *****WPATH(J,K), STARTING FROM H1                                      GEO 1390 */
	/* *****INITIAL DIRECTION OF PATH IS DOWN                                 GEO 1400 */
	l = ih1;
	ldel = -1;
	if (card3_1.len == 1 || card3_1.h1 > card3_1.h2)
	{
		goto L230;
	}
	/* *****INITIAL DIRECTION OF PATH IS UP                                   GEO 1440 */
	l = 0;
	ldel = 1;
L230:
	sols_1.jturn = 0;
	jmaxp1 = jmax + 1;
	i__1 = jmaxp1;
	for (j = 1; j <= i__1; ++j)
	{
		/* *****TEST FOR REVERSING DIRECTION OF PATH FROM DOWN TO UP              GEO 1510 */
		if (l != 1 || ldel != -1)
		{
			goto L240;
		}
		sols_1.jturn = j;
		l = 0;
		ldel = 1;
	L240:
		l += ldel;
		sols_1.lj[j - 1] = l;
		/* L250: */
	}
	/* *****LOAD TBBY AND WPATH                                               GEO 1600 */
	/* *****TBBY IS DENSITY WEIGHTED MEAN TEMPERATURE                         GEO 1610 */
	amttot = 0.f;
	i__1 = cntrl_1.kmax;
	for (k = 1; k <= i__1; ++k)
	{
		/* L255: */
		_BLNK__1.wpath[k * 68 - 68] = 0.f;
	}
	parmtr_1.imax = 0;
	i__1 = jmax;
	for (j = 1; j <= i__1; ++j)
	{
		l = sols_1.lj[j - 1];
		if (l >= cntrl_1.ml)
		{
			l = cntrl_1.ml;
		}
		if (l >= parmtr_1.imax)
		{
			parmtr_1.imax = l;
		}
		_BLNK__1.tbby[j - 1] = rfrpth_1.tpsum[l - 1] / rfrpth_1.rhopsm[l - 1];
		amttot += rfrpth_1.rhopsm[l - 1];
		j1 = j - 1;
		if (j1 == 0)
		{
			j1 = 1;
		}
		i__2 = cntrl_1.kmax;
		for (k = 1; k <= i__2; ++k)
		{
			if (k == 9)
			{
				goto L260;
			}
			_BLNK__1.wpath[j + k * 68 - 69] = _BLNK__1.wpath[j1 + k * 68 - 69] + rfrpth_1.amtp[k + l * 63 - 64];
		L260:;
		}
		_BLNK__1.wpath[j + 3943] = _BLNK__1.wpath[j1 + 3943] + rfrpth_1.amtp[l * 63 - 56] * .269f * (_BLNK__1.tbby[j - 1] - 273.15f);
		/* Computing 2nd power */
		r__1 = _BLNK__1.tbby[j - 1] - 273.15f;
		_BLNK__1.wpath[j + 4011] = _BLNK__1.wpath[j1 + 4011] + rfrpth_1.amtp[l * 63 - 56] * .269f * (r__1 * r__1);
		wtem = (296.f - _BLNK__1.tbby[j - 1]) / 36.f;
		if (wtem < 0.f)
		{
			wtem = 0.f;
		}
		if (wtem > 1.f)
		{
			wtem = 1.f;
		}
		_BLNK__1.wpath[j + 543] = _BLNK__1.wpath[j1 + 543] + wtem *
																 rfrpth_1.amtp[l * 63 - 59];
		/* L265: */
	}
	i__1 = cntrl_1.kmax;
	for (k = 1; k <= i__1; ++k)
	{
		_BLNK__1.w[k - 1] = _BLNK__1.wpath[jmax + k * 68 - 69];
		/* L270: */
	}
	jmaxst = jmax;
	/* C    JMAX = IMAX                                                       GEO 1890 */
	immax = parmtr_1.imax;
	cntrl_1.ikmax = jmax;
	/* *****INCLUDE BOUNDARY EMISSION IF:                                     GEO 1920 */
	/* *****    1. NON ZERO TBOUND IS READ IN ON CARD 1                       GEO 1930 */
	/* *****    2. SLANT PATH INTERSECTS THE EARTH (TBOUND                    GEO 1940 */
	/* *****       SET TO TEMPERATURE OF LOWEST BOUNDARY)                     GEO 1950 */
	if (card1_1.tbound == 0.f && card3_1.h2 == model_1.zm[0])
	{
		card1_1.tbound = model_1.tm[0];
	}
	/* *****PRINT CUMULATIVE ABSORBER AMOUNTS                                 GEO 1970 */
	if (ifil_1.npr == 1)
	{
		goto L315;
	}
	io___485.ciunit = ifil_1.ipr;
	s_wsfe(&io___485);
	e_wsfe();
	/* *****GOING DOWN, LP = 0,    GOING UP, LP = 1                           GEO 2090 */
	lp = 1;
	if (card3_1.len == 1 || card3_1.h1 > card3_1.h2)
	{
		lp = 0;
	}
	path_1.aht[0] = card3_1.h1;
	i__1 = jmax;
	for (j = 1; j <= i__1; ++j)
	{
		l = sols_1.lj[j - 1];
		if (j == sols_1.jturn)
		{
			lp = 1;
		}
		lz = l + lp;
		path_1.aht[j] = rfrpth_1.zp[lz - 1];
		if (ifil_1.npr != 1)
		{
			io___488.ciunit = ifil_1.ipr;
			s_wsfe(&io___488);
			do_fio(&c__1, (char *)&j, (long)sizeof(long));
			do_fio(&c__1, (char *)&rfrpth_1.zp[lz - 1], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.tbby[j - 1], (long)sizeof(float));
			for (k = 4; k <= 8; ++k)
			{
				do_fio(&c__1, (char *)&_BLNK__1.wpath[j + kmol[k - 1] * 68 - 69], (long)sizeof(float));
			}
			do_fio(&c__1, (char *)&_BLNK__1.wpath[j + 3875], (long)sizeof(float));
			e_wsfe();
		}
		/* L300: */
	}
	if (ifil_1.npr != 1)
	{
		io___489.ciunit = ifil_1.ipr;
		s_wsfe(&io___489);
		e_wsfe();
	}
	lp = 1;
	if (card3_1.len == 1 || card3_1.h1 > card3_1.h2)
	{
		lp = 0;
	}
	i__1 = jmax;
	for (j = 1; j <= i__1; ++j)
	{
		l = sols_1.lj[j - 1];
		if (j == sols_1.jturn)
		{
			lp = 1;
		}
		lz = l + lp;
		if (ifil_1.npr != 1)
		{
			io___490.ciunit = ifil_1.ipr;
			s_wsfe(&io___490);
			do_fio(&c__1, (char *)&j, (long)sizeof(long));
			do_fio(&c__1, (char *)&rfrpth_1.zp[lz - 1], (long)sizeof(float));
			for (k = 9; k <= 15; ++k)
			{
				do_fio(&c__1, (char *)&_BLNK__1.wpath[j + kmol[k - 1] * 68 - 69], (long)sizeof(float));
			}
			e_wsfe();
		}
		/* L310: */
	}
/* *****PRINT PATH SUMMARY                                                GEO 2350 */
L315:
	if (cntrl_1.issgeo == 1)
	{
		goto L320;
	}
	if (ifil_1.npr != 1)
	{
		io___491.ciunit = ifil_1.ipr;
		s_wsfe(&io___491);
		e_wsfe();
	}
	lp = 1;
	if (card3_1.len == 1 || card3_1.h1 > card3_1.h2)
	{
		lp = 0;
	}
	i__1 = jmax;
	for (j = 1; j <= i__1; ++j)
	{
		l = sols_1.lj[j - 1];
		if (j == sols_1.jturn)
		{
			lp = 1;
		}
		lz = l + lp;
		if (ifil_1.npr != 1)
		{
			io___492.ciunit = ifil_1.ipr;
			s_wsfe(&io___492);
			do_fio(&c__1, (char *)&j, (long)sizeof(long));
			do_fio(&c__1, (char *)&rfrpth_1.zp[lz - 1], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.wpath[j + 1087], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.wpath[j + 2039], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.wpath[j + 2379], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.wpath[j + 2923], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.wpath[j + 3059], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.wpath[j + 3127], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.wpath[j + 3331], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.wpath[j + 3467], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.wpath[j + 3603], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.wpath[j + 3671], (long)sizeof(float));
			do_fio(&c__1, (char *)&_BLNK__1.wpath[j + 3739], (long)sizeof(float));
			e_wsfe();
		}
		/* L312: */
	}
	io___493.ciunit = ifil_1.ipr;
	s_wsfe(&io___493);

	do_fio(&c__1, (char *)&card3_1.h1, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.h2, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.angle, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.range, (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.beta, (long)sizeof(float));
	do_fio(&c__1, (char *)&phi, (long)sizeof(float));
	do_fio(&c__1, (char *)&hmin, (long)sizeof(float));
	do_fio(&c__1, (char *)&(*bendng), (long)sizeof(float));
	do_fio(&c__1, (char *)&card3_1.len, (long)sizeof(long));

	e_wsfe();
L320:
	/* *****CALCULATE THE AEROSOL WEIGHTED MEAN RH                            GEO 2620 */
	if (_BLNK__1.w[6] > 0.f && _BLNK__1.ich[0] <= 7)
	{
		w15 = _BLNK__1.w[14] / _BLNK__1.w[6];
	}
	if (_BLNK__1.w[11] > 0.f && _BLNK__1.ich[0] > 7)
	{
		w15 = _BLNK__1.w[14] / _BLNK__1.w[11];
	}
	/*                                                                       GEO 2650 */
	/*     INVERSE OF LOG REL HUM                                            GEO 2660 */
	/*                                                                       GEO 2670 */
	if (_BLNK__1.w[6] > 0.f && _BLNK__1.ich[0] <= 7)
	{
		_BLNK__1.w[14] = 100.f - exp(w15);
	}
	if (_BLNK__1.w[11] > 0.f && _BLNK__1.ich[0] > 7)
	{
		_BLNK__1.w[14] = 100.f - exp(w15);
	}
	if (_BLNK__1.w[6] <= 0.f && _BLNK__1.ich[0] <= 7)
	{
		_BLNK__1.w[14] = 0.f;
	}
	if (_BLNK__1.w[11] <= 0.f && _BLNK__1.ich[0] > 7)
	{
		_BLNK__1.w[14] = 0.f;
	}
	/*                                                                       GEO 2760 */
	/* *****PRINT TOTAL PATH AMOUNTS                                          GEO 2770 */
	if (cntrl_1.issgeo == 1)
	{
		return 0;
	}
	io___495.ciunit = ifil_1.ipr;
	s_wsfe(&io___495);
	for (k = 4; k <= 16; ++k)
	{
		do_fio(&c__1, (char *)&_BLNK__1.w[kmol[k - 1] - 1], (long)sizeof(float));
	}
	e_wsfe();
	/*                                                                       GEO 2900 */
	io___496.ciunit = ifil_1.ipr;
	s_wsfe(&io___496);
	do_fio(&c__1, (char *)&_BLNK__1.w[16], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__1.w[30], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__1.w[35], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__1.w[43], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__1.w[45], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__1.w[46], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__1.w[49], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__1.w[51], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__1.w[53], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__1.w[54], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__1.w[55], (long)sizeof(float));
	e_wsfe();
	if (jmaxst > *maxgeo)
	{
		io___497.ciunit = ifil_1.ipr;
		s_wsfe(&io___497);
		do_fio(&c__1, (char *)&(*maxgeo), (long)sizeof(long));
		do_fio(&c__1, (char *)&jmaxst, (long)sizeof(long));
		e_wsfe();
		s_stop((char *)"GEO :JMAXST .GT. MAXGEO", (long)23);
	}
	i__1 = jmaxst;
	for (ik = 1; ik <= i__1; ++ik)
	{
		il = sols_1.lj[ik - 1];
		rain_1.rnpath[ik - 1] = rfrpth_1.sp[il - 1];
		rain_1.rramtk[ik - 1] = model_1.rramt[il - 1];
		/* L350: */
	}
	/*                                                                       GEO 3110 */
	/* L500: */
	return 0;
} /* geo_ */

/* Subroutine */ int geoinp_(float *h1, float *h2, float *angle, float *range,
							 float *beta, long *itype, long *len, float *hmin, float *phi,
							 long *ierror)
{
	/* Format strings */
	static char fmt_10[] = "(//,\002 CASE 3A: GIVEN H1,H2=SPACE,ANGLE\002)";
	static char fmt_12[] = "(//,\002 CASE 3B: GIVEN H1, HMIN, H2=SPACE\002)";
	static char fmt_16[] = "(//,\002 CASE 2A: GIVEN H1, H2, ANGLE\002)";
	static char fmt_15[] = "(//,\002 EITHER A SHORT PATH (LEN=0) OR A LONG P"
						   "ATH \002,\002THROUGH A TANGENT HEIGHT (LEN=1) IS POSSIBLE: LEN = "
						   "\002,i3)";
	static char fmt_18[] = "(//,\002 CASE 2B:, GIVEN H1, ANGLE, RANGE\002,//"
						   "10x,\002NOTE: H2 IS COMPUTED FROM H1, ANGLE, AND RANGE \002,\002"
						   "ASSUMING NO REFRACTION\002)";
	static char fmt_17[] = "(//,10x,\002CALCULATED H2 IS LESS THAN ZERO:\002"
						   ",/,10x,\002RESET H2 = 0.0 AND RANGE = \002,f10.3)";
	static char fmt_19[] = "(//,\002 CASE 2C: GIVEN H1, H2, RANGE\002,//,1"
						   "0x,\002NOTE: ANGLE IS COMPUTED FROM H1, H2, AND RANGE \002,\002A"
						   "SSUMING NO REFRACTION\002)";
	static char fmt_20[] = "(///,\002 SLANT PATH PARAMETERS IN STANDARD FOR"
						   "M\002,//,10x,\002H1      = \002,f10.3,\002 KM\002,/,10x,\002H2  "
						   "    = \002,f10.3,\002 KM\002,/,10x,\002ANGLE   = \002,f10.3,\002"
						   " DEG\002,/,10x,\002PHI     = \002,f10.3,\002 DEG\002,/,10x,\002H"
						   "MIN    = \002,f10.3,\002 KM\002,/,10x,\002LEN     = \002,i10)";
	static char fmt_40[] = "(\0020GEOINP, CASE 3B (H1,HMIN,SPACE): ERROR IN "
						   "INPUT DATA\002,//,10x,\002H1 = \002,f12.6,\002    IS LESS THAN H"
						   "MIN = \002,f12.6)";
	static char fmt_42[] = "(\0020GEOINP: ERROR IN INPUT DATA, ITYPE NOT EQU"
						   "AL TO \002,\002 2, OR 3.   ITYPE = \002,i10,e23.14)";
	static char fmt_43[] = "(\0020GEOINP, CASE 2C (H1,H2,RANGE): ERROR IN IN"
						   "PUT DATA\002,//,10x,\002ABS(H1-H2) GT RANGE;  H1 = \002,f12.6"
						   ",\002    H2 = \002,f12.6,\002    RANGE = \002,f12.6)";
	static char fmt_44[] = "(\0020GEOINP, CASE 2A (H1,H2,ANGLE): ERROR IN IN"
						   "PUT DATA\002,//,10x,\002H1 = \002,f12.6,\002    IS GREATER THAN "
						   "OR EQUAL TO H2 = \002,f12.6,/,10x,\002AND ANGLE = \002,f12.6,"
						   "\002    IS LESS THAN OR \002,\002EQUAL TO 90.0\002)";
	static char fmt_48[] = "(\0020GEOINP, ITYPE = 2: SLANT PATH INTERSECTS T"
						   "HE EARTH\002,\002 AND CANNOT REACH H2\002)";
	static char fmt_50[] = "(\002 GEOINP-  THE ENTIRE PATH LIES ABOVE THE TO"
						   "P ZMAX \002,\002OF THE ATMOSPHERIC PROFILE\002,//,10x,\002ZMAX = "
						   "\002,g12.6,5x,\002  H1 = \002,g12.6,5x,\002  H2 = \002,g12.6,"
						   "\002  HMIN = \002,g12.6)";

	/* System generated locals */
	float r__1, r__2, r__3;

	/* Builtin functions */
	long s_wsfe(cilist *), e_wsfe(void), do_fio(long *, char *, long);
	double cos(double), sqrt(double), sin(double), acos(double);

	/* Local variables */
	static float r1, r2, h2st;
	static long iter;
	static float zarg1, zarg2, zarg3, erarg1, erarg2, erarg3;
	extern /* Subroutine */ int fdbeta_(float *, float *, float *, float *, float *, long *, float *, long *), reduce_(float *, float *, float *, float *, long *), fndhmn_(float *, float *, float *, long *, long *, float *, float *, long *);

	/* Fortran I/O blocks */
	static cilist io___501 = {0, 0, 0, fmt_10, 0};
	static cilist io___502 = {0, 0, 0, fmt_12, 0};
	static cilist io___503 = {0, 0, 0, fmt_16, 0};
	static cilist io___504 = {0, 0, 0, fmt_15, 0};
	static cilist io___506 = {0, 0, 0, fmt_18, 0};
	static cilist io___509 = {0, 0, 0, fmt_17, 0};
	static cilist io___512 = {0, 0, 0, fmt_19, 0};
	static cilist io___517 = {0, 0, 0, fmt_20, 0};
	static cilist io___518 = {0, 0, 0, fmt_40, 0};
	static cilist io___519 = {0, 0, 0, fmt_42, 0};
	static cilist io___520 = {0, 0, 0, fmt_43, 0};
	static cilist io___521 = {0, 0, 0, fmt_44, 0};
	static cilist io___522 = {0, 0, 0, fmt_48, 0};
	static cilist io___523 = {0, 0, 0, fmt_50, 0};

	/* ***********************************************************************GEI  120 */
	/*     GEOINP INTERPRETS THE ALLOWABLE COMBINATIONS OF INPUT PATH        GEI  130 */
	/*     PARAMETERS INTO THE STANDARD SET H1,H2,ANGLE,PHI,HMIN, AND LEN.   GEI  140 */
	/*     THE ALLOWABLE COMBINATIONS OF INPUT PARAMETERS ARE- FOR ITYPE = 2,GEI  150 */
	/*     (SLANT PATH H1 TO H2) A. H1, H2, AND ANGLE, B. H1, ANGLE, AND     GEI  160 */
	/*     RANGE, C. H1, H2, AND RANGE, D. H1, H2, AND BETA -                GEI  170 */
	/*     FOR ITYPE = 3 (SLANT PATH H1 TO SPACE H2 = 100 KM),               GEI  180 */
	/*     A. H1 AND ANGLE, B. H1 AND HMIN (INPUT AS H2).                    GEI  190 */
	/*     THE SUBROUTINE ALSO DETECTS BAD INPUT (IMPOSSIBLE GEOMETRY) AND   GEI  200 */
	/*     ITYPE = 2 CASES WHICH INTERSECT THE EARTH, AND RETURNS THESE      GEI  210 */
	/*     CASES WITH ERROR FLAGS.                                           GEI  220 */
	/*     THE SUBROUTINE FNDHMN IS CALLED TO CALCULATE HMIN, THE MINIMUM    GEI  230 */
	/*     HEIGHT ALONG THE PATH, AND PHI, THE ZENITH ANGLE AT H2, USING THE GEI  240 */
	/*     ATMOSPHERIC PROFILE STORED IN /MODEL/                             GEI  250 */
	/* ***********************************************************************GEI  260 */
	iter = 0;
	if (*itype != 3)
	{
		goto L120;
	}
	/* *****SLANT PATH TO SPACE                                               GEI  320 */
	/* *****NOTE: IF BOTH HMIN AND ANGLE ARE ZERO, THEN ANGLE IS              GEI  330 */
	/* *****ASSUMED SPECIFIED                                                 GEI  340 */
	if (*h2 != 0.f)
	{
		goto L110;
	}
	/* *****CASE 3A: H1,SPACE,ANGLE                                           GEI  360 */
	if (ifil_1.npr != 1)
	{
		io___501.ciunit = ifil_1.ipr;
		s_wsfe(&io___501);
		e_wsfe();
	}
	*h2 = parmtr_1.zmax;
	fndhmn_(h1, angle, h2, len, &iter, hmin, phi, ierror);
	if (*ierror == -5)
	{
		return 0;
	}
	goto L200;
L110:
	/* *****CASE 3B: H1,HMIN,SPACE                                            GEI  440 */
	if (ifil_1.npr != 1)
	{
		io___502.ciunit = ifil_1.ipr;
		s_wsfe(&io___502);
		e_wsfe();
	}
	*hmin = *h2;
	*h2 = parmtr_1.zmax;
	if (*h1 < *hmin)
	{
		goto L9001;
	}
	fndhmn_(hmin, &c_b1128, h1, len, &iter, hmin, angle, ierror);
	fndhmn_(hmin, &c_b1128, h2, len, &iter, hmin, phi, ierror);
	if (*hmin < *h1)
	{
		*len = 1;
	}
	goto L200;
L120:
	if (*itype != 2)
	{
		goto L9002;
	}
	if (*range != 0.f || *beta != 0.f)
	{
		goto L130;
	}
	/* *****CASE 2A: H1, H2, ANGLE                                            GEI  570 */
	if (ifil_1.npr != 1)
	{
		io___503.ciunit = ifil_1.ipr;
		s_wsfe(&io___503);
		e_wsfe();
	}
	if (*h1 >= *h2 && *angle <= 90.f)
	{
		goto L9004;
	}
	if (*h1 == 0.f && *angle > 90.f)
	{
		goto L9007;
	}
	if (*h2<*h1 && * angle> 90.f && ifil_1.npr != 1)
	{
		io___504.ciunit = ifil_1.ipr;
		s_wsfe(&io___504);
		do_fio(&c__1, (char *)&(*len), (long)sizeof(long));
		e_wsfe();
	}
	h2st = *h2;
	fndhmn_(h1, angle, h2, len, &iter, hmin, phi, ierror);
	if (*h2 != h2st)
	{
		goto L9007;
	}
	goto L200;
L130:
	if (*beta == 0.f)
	{
		goto L133;
	}
	fdbeta_(h1, h2, beta, angle, phi, len, hmin, ierror);
	goto L200;
L133:
	if (*angle == 0.f)
	{
		goto L140;
	}
	/* *****CASE 2B: H1, ANGLE, RANGE                                         GEI  760 */
	/* *****ASSUME NO REFRACTION                                              GEI  770 */
	if (ifil_1.npr != 1)
	{
		io___506.ciunit = ifil_1.ipr;
		s_wsfe(&io___506);
		e_wsfe();
	}
	r1 = parmtr_1.re + *h1;
	/* Computing 2nd power */
	r__1 = r1;
	/* Computing 2nd power */
	r__2 = *range;
	r2 = sqrt(r__1 * r__1 + r__2 * r__2 + r1 * 2.f * *range * cos(*angle / cnstns_1.deg));
	*h2 = r2 - parmtr_1.re;
	if (*h2 >= 0.f)
	{
		goto L135;
	}
	*h2 = 0.f;
	r2 = parmtr_1.re + *h2;
	/* Computing 2nd power */
	r__1 = r2;
	/* Computing 2nd power */
	r__2 = r1;
	/* Computing 2nd power */
	r__3 = sin(*angle / cnstns_1.deg);
	*range = -r1 * cos(*angle / cnstns_1.deg) - sqrt(r__1 * r__1 - r__2 *
																	   r__2 * (r__3 * r__3));
	if (ifil_1.npr != 1)
	{
		io___509.ciunit = ifil_1.ipr;
		s_wsfe(&io___509);
		do_fio(&c__1, (char *)&(*range), (long)sizeof(float));
		e_wsfe();
	}
L135:
	/* *****NOTE: GEOMETRIC PHI IS NEEDED TO DETERMINE LEN(0 OR 1).           GEI  930 */
	/* *****PHI IS THEN RECOMPUTED IN FNDHMN                                  GEI  940 */
	/* Computing 2nd power */
	r__1 = r2;
	/* Computing 2nd power */
	r__2 = *range;
	/* Computing 2nd power */
	r__3 = r1;
	zarg1 = (r__1 * r__1 + r__2 * r__2 - r__3 * r__3) / (r2 * 2.f * *range);
	erarg1 = dabs(zarg1) - 1.f;
	if (erarg1 > 1e-6f || erarg1 < 0.f)
	{
		goto L137;
	}
	if (zarg1 < 0.f)
	{
		goto L138;
	}
	zarg1 = 1.f;
	goto L137;
L138:
	zarg1 = -1.f;
L137:
	*phi = 180.f - acos(zarg1) * cnstns_1.deg;
	*len = 0;
	if (*angle > 90.f && *phi > 90.f)
	{
		*len = 1;
	}
	fndhmn_(h1, angle, h2, len, &iter, hmin, phi, ierror);
	goto L200;
L140:
	/* *****CASE 2C: H1, H2, RANGE                                            GEI 1080 */
	if (ifil_1.npr != 1)
	{
		io___512.ciunit = ifil_1.ipr;
		s_wsfe(&io___512);
		e_wsfe();
	}
	if ((r__1 = *h1 - *h2, dabs(r__1)) > *range)
	{
		goto L9003;
	}
	r1 = *h1 + parmtr_1.re;
	r2 = *h2 + parmtr_1.re;
	/* %    PHI = 180.0-ACOS((R2**2+RANGE**2-R1**2)/(2.0*R2*RANGE))*DEG       *** 1160 */
	/* Computing 2nd power */
	r__1 = r1;
	/* Computing 2nd power */
	r__2 = *range;
	/* Computing 2nd power */
	r__3 = r2;
	zarg2 = (r__1 * r__1 + r__2 * r__2 - r__3 * r__3) / (r1 * 2.f * *range);
	erarg2 = dabs(zarg2) - 1.f;
	if (erarg2 > 1e-6f || erarg2 < 0.f)
	{
		goto L187;
	}
	if (zarg2 < 0.f)
	{
		goto L188;
	}
	zarg2 = 1.f;
	goto L187;
L188:
	zarg2 = -1.f;
L187:
	*angle = 180.f - acos(zarg2) * cnstns_1.deg;
	/* Computing 2nd power */
	r__1 = r2;
	/* Computing 2nd power */
	r__2 = *range;
	/* Computing 2nd power */
	r__3 = r1;
	zarg3 = (r__1 * r__1 + r__2 * r__2 - r__3 * r__3) / (r2 * 2.f * *range);
	erarg3 = dabs(zarg3) - 1.f;
	if (erarg3 > 1e-6f || erarg3 < 0.f)
	{
		goto L197;
	}
	if (zarg3 < 0.f)
	{
		goto L198;
	}
	zarg3 = 1.f;
	goto L197;
L198:
	zarg3 = -1.f;
L197:
	*phi = 180.f - acos(zarg3) * cnstns_1.deg;
	*beta = *phi + *angle - 180.f;
	/* #    RANGE = 0.                                                        GEI 1340 */
	if (*range > 2.f && *beta > 0.f)
	{
		fdbeta_(h1, h2, beta, angle, phi, len, hmin, ierror);
	}
	else
	{
		/* J                                                                      GEI 1360 */
		*len = 0;
		if (*angle > 90.f && *phi > 90.f)
		{
			*len = 1;
		}
		fndhmn_(h1, angle, h2, len, &iter, hmin, phi, ierror);
	}
L200:
	/* *****TEST IERROR AND RECHECK LEN                                       GEI 1410 */
	if (*ierror != 0)
	{
		return 0;
	}
	*len = 0;
	if (*hmin < min(*h1, *h2))
	{
		*len = 1;
	}
	/* *****REDUCE PATH ENDPOINTS ABOVE ZMAX TO ZMAX                          GEI 1450 */
	if (*hmin >= parmtr_1.zmax)
	{
		goto L9008;
	}
	if (*h1 > parmtr_1.zmax || *h2 > parmtr_1.zmax)
	{
		reduce_(h1, h2, angle, phi, &iter);
	}
	/* *****AT THIS POINT THE FOLLOWING PARAMETERS ARE DEFINED:               GEI 1480 */
	/* *****    H1,H2,ANGLE,PHI,HMIN,LEN                                      GEI 1490 */
	if (ifil_1.npr != 1)
	{
		io___517.ciunit = ifil_1.ipr;
		s_wsfe(&io___517);
		do_fio(&c__1, (char *)&(*h1), (long)sizeof(float));
		do_fio(&c__1, (char *)&(*h2), (long)sizeof(float));
		do_fio(&c__1, (char *)&(*angle), (long)sizeof(float));
		do_fio(&c__1, (char *)&(*phi), (long)sizeof(float));
		do_fio(&c__1, (char *)&(*hmin), (long)sizeof(float));
		do_fio(&c__1, (char *)&(*len), (long)sizeof(long));
		e_wsfe();
	}
	return 0;
/* *****                                                                  GEI 1560 */
/* *****ERROR MESAGES                                                     GEI 1570 */
/* *****                                                                  GEI 1580 */
L9001:
	io___518.ciunit = ifil_1.ipr;
	s_wsfe(&io___518);
	do_fio(&c__1, (char *)&(*h1), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*hmin), (long)sizeof(float));
	e_wsfe();
	goto L9900;
L9002:
	io___519.ciunit = ifil_1.ipr;
	s_wsfe(&io___519);
	do_fio(&c__1, (char *)&(*itype), (long)sizeof(long));
	do_fio(&c__1, (char *)&(*itype), (long)sizeof(long));
	e_wsfe();
	goto L9900;
L9003:
	io___520.ciunit = ifil_1.ipr;
	s_wsfe(&io___520);
	do_fio(&c__1, (char *)&(*h1), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*h2), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*range), (long)sizeof(float));
	e_wsfe();
	goto L9900;
L9004:
	io___521.ciunit = ifil_1.ipr;
	s_wsfe(&io___521);
	do_fio(&c__1, (char *)&(*h1), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*h2), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*angle), (long)sizeof(float));
	e_wsfe();
	goto L9900;
L9007:
	io___522.ciunit = ifil_1.ipr;
	s_wsfe(&io___522);
	e_wsfe();
	goto L9900;
L9008:
	io___523.ciunit = ifil_1.ipr;
	s_wsfe(&io___523);
	do_fio(&c__1, (char *)&parmtr_1.zmax, (long)sizeof(float));
	do_fio(&c__1, (char *)&(*h1), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*h2), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*hmin), (long)sizeof(float));
	e_wsfe();
L9900:
	*ierror = 1;
	return 0;
} /* geoinp_ */

/* Subroutine */ int reduce_(float *h1, float *h2, float *angle, float *phi,
							 long *iter)
{
	/* Format strings */
	static char fmt_20[] = "(///,\002 FROM SUBROUTINE REDUCE: \002,/,4x,\002"
						   "ONE OR BOTH OF H1 AND H2 ARE ABOVE THE TOP OF THE \002,\002ATMOS"
						   "PHERIC PROFILE ZMAX = \002,f10.3,\002 AND HAVE BEEN RESET \002"
						   ",\002TO ZMAX\002,/,4x,\002ANGLE AND/OR PHI HAVE ALSO BEEN RESET "
						   "TO \002,\002THE ZENITH ANGLE AT ZMAX = \002,f10.3,\002 DEG\002)";

	/* Builtin functions */
	double sin(double), asin(double);
	long s_wsfe(cilist *), do_fio(long *, char *, long), e_wsfe(void);

	/* Local variables */
	static float sh, gamma, cpath;
	extern double andex_(float *, float *, float *);
	static float czmax;
	extern /* Subroutine */ int findsh_(float *, float *, float *);
	static float angmax;

	/* Fortran I/O blocks */
	static cilist io___529 = {0, 0, 0, fmt_20, 0};

	/* ***********************************************************************RED  110 */
	/*     ZMAX IS THE HIGHEST LEVEL IN THE ATMOSPHERIC PROFILE STORED IN    RED  120 */
	/*     COMMON /MODEL/.  IF H1 AND/OR H2 ARE GREATER THAN ZMAX, THIS      RED  130 */
	/*     SUBROUTINE REDUCES THEM TO ZMAX AND RESETS ANGLE AND/OR PHI       RED  140 */
	/*     AS NECESSARY. THIS REDUCTION IS NECESSARY,FOR EXAMPLE FOR         RED  150 */
	/*     SATELLITE ALTITUDES, BECAUSE (1) THE DENSITY PROFILES ARE         RED  160 */
	/*     POORLY DEFINED ABOVE ZMAX AND (2) THE CALCULATION TIME FOR        RED  170 */
	/*     PATHS ABOVE ZMAX CAN BE EXCESSIVE ( EG. FOR GEOSYNCHRONOUS        RED  180 */
	/*     ALTITUDES)                                                        RED  190 */
	/* ***********************************************************************RED  200 */
	if (*h1 <= parmtr_1.zmax && *h2 <= parmtr_1.zmax)
	{
		return 0;
	}
	findsh_(h1, &sh, &gamma);
	cpath = andex_(h1, &sh, &gamma) * (parmtr_1.re + *h1) * sin(*angle / cnstns_1.deg);
	findsh_(&parmtr_1.zmax, &sh, &gamma);
	czmax = andex_(&parmtr_1.zmax, &sh, &gamma) * (parmtr_1.re +
												   parmtr_1.zmax);
	angmax = 180.f - asin(cpath / czmax) * cnstns_1.deg;
	if (*h1 <= parmtr_1.zmax)
	{
		goto L120;
	}
	*h1 = parmtr_1.zmax;
	*angle = angmax;
L120:
	if (*h2 <= parmtr_1.zmax)
	{
		goto L130;
	}
	*h2 = parmtr_1.zmax;
	*phi = angmax;
L130:
	io___529.ciunit = ifil_1.ipr;
	s_wsfe(&io___529);
	do_fio(&c__1, (char *)&parmtr_1.zmax, (long)sizeof(float));
	do_fio(&c__1, (char *)&angmax, (long)sizeof(float));
	e_wsfe();
	/* L200: */
	return 0;
} /* reduce_ */

/* Subroutine */ int fdbeta_(float *h1, float *h2, float *betas, float *angle,
							 float *phi, long *len, float *hmin, long *ierror)
{
	/* Initialized data */

	static float tolrnc = .005f;
	static long itermx = 10;
	static float betd = .04f;
	static float zer = 0.f;

	/* Format strings */
	static char fmt_24[] = "(///,\002 CASE 2D: GIVEN H1, H2,  BETA:\002,//"
						   ",\002 ITERATE AROUND ANGLE UNTIL BETA CONVERGES\002,//,\002 ITER"
						   "    ANGLE\002,t21,\002BETA\002,t30,\002DBETA\002,t40,\002RANG"
						   "E\002,t51,\002HMIN\002,t61,\002PHI\002,t70,\002BENDING\002,/,t10,"
						   "\002(DEG)\002,t21,\002(DEG)\002,t30,\002(DEG)\002,t41,\002(KM"
						   ")\002,t51,\002(KM)\002,t60,\002(DEG)\002,t71,\002(DEG)\002,/)";
	static char fmt_26[] = "(i5,3f10.4,2f10.3,2f10.4)";
	static char fmt_45[] = "(\0020FDBETA, CASE 2D(H1,H2,BETA): REFRACTED TAN"
						   "GENT \002,\002HEIGHT IS LESS THAN ZERO-PATH INTERSECTS THE EART"
						   "H\002,//,10x,\002BETA IS TOO LARGE FOR THIS H1 AND H2\002)";
	static char fmt_46[] = "(\0020FDBETA, CASE 2D (H1,H2,BETA): SOLUTION DID"
						   " NOT \002,\002 CONVERGE\002,//,10x,\002H1 = \002,f12.6,\002    H"
						   "2 = \002,f12.6,\002    BETA = \002,f12.6,\002    ITERATIONS ="
						   " \002,i4,//,10x,\002LAST THREE ITERATIONS \002,//,(10x,\002ANGLE"
						   " = \002,f15.9,\002    BETA = \002,f15.9))";

	/* System generated locals */
	float r__1;
	double d__1, d__2, d__3;

	/* Builtin functions */
	long s_wsfe(cilist *), e_wsfe(void);
	double cos(double), sqrt(double), acos(double), sin(double);
	long do_fio(long *, char *, long);

	/* Local variables */
	static float dc, ha, hb;
	static double ra, rb, sg;
	static float dang;
	static double beta;
	static long iter;
	static float temp, beta1, beta2;
	static double dbeta;
	static long iflag;
	static float betap;
	static long iamtb;
	static float range, hming;
	static double angle1, angle2;
	static float angls1, angls2, bendng, anglep;
	extern /* Subroutine */ int fndhmn_(float *, float *, float *, long *,
										long *, float *, float *, long *);
	static long iorder;
	extern /* Subroutine */ int rfpath_(float *, float *, float *, float *,
										long *, float *, long *, float *, float *, float *);

	/* Fortran I/O blocks */
	static cilist io___540 = {0, 0, 0, fmt_24, 0};
	static cilist io___551 = {0, 0, 0, fmt_26, 0};
	static cilist io___555 = {0, 0, 0, fmt_26, 0};
	static cilist io___561 = {0, 0, 0, fmt_26, 0};
	static cilist io___563 = {0, 0, 0, fmt_45, 0};
	static cilist io___564 = {0, 0, 0, fmt_46, 0};

	/* ********************************************************************** FDB  110 */
	/*     GIVEN H1,H2,AND BETA (THE EARTH CENTERED ANGLE) THIS SUBROUTINE   FDB  120 */
	/*     CALCULATES THE INITIAL ZENITH ANGLE AT H1 THROUGH AN ITERATIVE    FDB  130 */
	/*     PROCEDURE                                                         FDB  140 */
	/* ********************************************************************** FDB  150 */
	/*     DATA TOLRNC/1.0E-4/,ITERMX/10/,BETD /0.02/                        FDB  190 */
	beta = *betas;
	iflag = 0;
	if (*h1 > *h2)
	{
		goto L100;
	}
	iorder = 1;
	ha = *h1;
	hb = *h2;
	goto L120;
L100:
	iorder = -1;
	ha = *h2;
	hb = *h1;
L120:
	/* *****SET PARAMETER TO SUPRESS CALCULATION OF AMOUNTS                   FDB  330 */
	iamtb = 2;
	/* *****GUESS AT ANGLE, INTEGRATE TO FIND BETA, TEST FOR                  FDB  350 */
	/* *****CONVERGENCE, AND ITERATE                                          FDB  360 */
	/* *****FIRST GUESS AT ANGLE: USE THE GEOMETRIC SOLUTION(NO REFRACTION)   FDB  370 */
	io___540.ciunit = ifil_1.ipr;
	s_wsfe(&io___540);
	e_wsfe();
	iter = 0;
	ra = parmtr_1.re + ha;
	rb = parmtr_1.re + hb;
	/* Computing 2nd power */
	d__1 = ra;
	/* Computing 2nd power */
	d__2 = rb;
	sg = sqrt(d__1 * d__1 + d__2 * d__2 - ra * 2.f * rb * cos(beta / cnstns_1.deg));
	/* Computing 2nd power */
	d__1 = ra;
	/* Computing 2nd power */
	d__2 = sg;
	/* Computing 2nd power */
	d__3 = rb;
	angle1 = 180.f - acos((d__1 * d__1 + d__2 * d__2 - d__3 * d__3) / (ra *
																	   2.f * sg)) *
						 cnstns_1.deg;
	*hmin = ha;
	if (angle1 > 90.f)
	{
		*hmin = ra * sin(angle1 / cnstns_1.deg) - parmtr_1.re;
	}
	hming = *hmin;
	angls1 = angle1;
	fndhmn_(&ha, &angls1, &hb, len, &iter, hmin, phi, ierror);
	*len = 0;
	if (*hmin < ha)
	{
		*len = 1;
	}
	rfpath_(&ha, &hb, &angls1, phi, len, hmin, &iamtb, &beta1, &range, &bendng);
	io___551.ciunit = ifil_1.ipr;
	s_wsfe(&io___551);
	do_fio(&c__1, (char *)&iter, (long)sizeof(long));
	do_fio(&c__1, (char *)&angle1, (long)sizeof(double));
	do_fio(&c__1, (char *)&beta, (long)sizeof(double));
	do_fio(&c__1, (char *)&zer, (long)sizeof(float));
	do_fio(&c__1, (char *)&sg, (long)sizeof(double));
	do_fio(&c__1, (char *)&hming, (long)sizeof(float));
	do_fio(&c__1, (char *)&zer, (long)sizeof(float));
	do_fio(&c__1, (char *)&zer, (long)sizeof(float));
	e_wsfe();
	/*                                                                       FDB  580 */
	/*     OBTAIN DERIVATIVE                                                 FDB  590 */
	/*                                                                       FDB  600 */
	/* Computing 2nd power */
	d__1 = ra;
	/* Computing 2nd power */
	d__2 = rb;
	sg = sqrt(d__1 * d__1 + d__2 * d__2 - ra * 2.f * rb * cos((beta + betd) / cnstns_1.deg));
	/* Computing 2nd power */
	d__1 = ra;
	/* Computing 2nd power */
	d__2 = sg;
	/* Computing 2nd power */
	d__3 = rb;
	anglep = 180.f - acos((d__1 * d__1 + d__2 * d__2 - d__3 * d__3) / (ra *
																	   2.f * sg)) *
						 cnstns_1.deg;
	dang = angle1 - anglep;
	if (*hmin >= 0.f)
	{
		goto L310;
	}
	iflag = 1;
	*hmin = 0.f;
	fndhmn_(hmin, &c_b1128, &ha, len, &iter, hmin, &angls1, ierror);
L310:
	iter = 1;
	*len = 0;
	if (angle1 > 90.f)
	{
		*len = 1;
	}
	fndhmn_(&ha, &angls1, &hb, len, &iter, hmin, phi, ierror);
	*len = 0;
	if (*hmin < ha)
	{
		*len = 1;
	}
	rfpath_(&ha, &hb, &angls1, phi, len, hmin, &iamtb, &beta1, &range, &bendng);
	dbeta = beta - beta1;
	io___555.ciunit = ifil_1.ipr;
	s_wsfe(&io___555);
	do_fio(&c__1, (char *)&iter, (long)sizeof(long));
	do_fio(&c__1, (char *)&angle1, (long)sizeof(double));
	do_fio(&c__1, (char *)&beta1, (long)sizeof(float));
	do_fio(&c__1, (char *)&dbeta, (long)sizeof(double));
	do_fio(&c__1, (char *)&range, (long)sizeof(float));
	do_fio(&c__1, (char *)&(*hmin), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*phi), (long)sizeof(float));
	do_fio(&c__1, (char *)&bendng, (long)sizeof(float));
	e_wsfe();
	if (iflag == 1 && beta1 < beta)
	{
		goto L9005;
	}
L320:
	anglep = angle1 - dang;
	*len = 0;
	if (anglep > 90.f)
	{
		*len = 1;
	}
	fndhmn_(&ha, &anglep, &hb, len, &iter, hmin, phi, ierror);
	*len = 0;
	if (*hmin < ha)
	{
		*len = 1;
	}
	rfpath_(&ha, &hb, &anglep, phi, len, hmin, &iamtb, &betap, &range, &bendng);
	if ((r__1 = beta1 - betap, dabs(r__1)) < tolrnc)
	{
		goto L330;
	}
	++iter;
	dc = betap - beta1;
	/*     DERIV = -DC/BETD                                                  FDB  910 */
	angle2 = angle1 + (angle1 - anglep) * (beta - beta1) / (beta1 - betap);
	*len = 0;
	if (angle2 > 90.f)
	{
		*len = 1;
	}
	angls2 = angle2;
	fndhmn_(&ha, &angls2, &hb, len, &iter, hmin, phi, ierror);
	*len = 0;
	if (*hmin < ha)
	{
		*len = 1;
	}
	rfpath_(&ha, &hb, &angls2, phi, len, hmin, &iamtb, &beta2, &range, &bendng);
	dbeta = beta - beta2;
	io___561.ciunit = ifil_1.ipr;
	s_wsfe(&io___561);
	do_fio(&c__1, (char *)&iter, (long)sizeof(long));
	do_fio(&c__1, (char *)&angle2, (long)sizeof(double));
	do_fio(&c__1, (char *)&beta2, (long)sizeof(float));
	do_fio(&c__1, (char *)&dbeta, (long)sizeof(double));
	do_fio(&c__1, (char *)&range, (long)sizeof(float));
	do_fio(&c__1, (char *)&(*hmin), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*phi), (long)sizeof(float));
	do_fio(&c__1, (char *)&bendng, (long)sizeof(float));
	e_wsfe();
	if (beta2 < beta && *hmin < 0.f)
	{
		goto L9005;
	}
	angle1 = angle2;
	angls1 = angle1;
	/*                                                                       FDB 1030 */
	beta1 = beta2;
	/*     BETA2 = BETA3                                                     FDB 1050 */
	if ((d__1 = beta - beta2, abs(d__1)) < tolrnc)
	{
		goto L340;
	}
	if (iter > itermx)
	{
		goto L9006;
	}
	goto L320;
L330:
	angle2 = anglep;
	angls2 = angle2;
	beta = betap;
L340:
	if (*hmin < 0.f)
	{
		goto L9005;
	}
	/* *****CONVERGED TO A SOLUTION                                           FDB 1130 */
	*angle = angle2;
	beta = beta2;
	/* *****ASSIGN ANGLE AND PHI TO PROPER H1 AND H2                          FDB 1160 */
	if (iorder == 1)
	{
		goto L350;
	}
	temp = *phi;
	*phi = *angle;
	*angle = temp;
L350:
	*betas = beta;
	return 0;
/* *****                                                                  FDB 1230 */
/* *****ERROR MESSAGES                                                    FDB 1240 */
/* *****                                                                  FDB 1250 */
L9005:
	io___563.ciunit = ifil_1.ipr;
	s_wsfe(&io___563);
	e_wsfe();
	goto L9900;
L9006:
	io___564.ciunit = ifil_1.ipr;
	s_wsfe(&io___564);
	do_fio(&c__1, (char *)&(*h1), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*h2), (long)sizeof(float));
	do_fio(&c__1, (char *)&beta, (long)sizeof(double));
	do_fio(&c__1, (char *)&iter, (long)sizeof(long));
	do_fio(&c__1, (char *)&angle1, (long)sizeof(double));
	do_fio(&c__1, (char *)&beta1, (long)sizeof(float));
	do_fio(&c__1, (char *)&angle2, (long)sizeof(double));
	do_fio(&c__1, (char *)&beta2, (long)sizeof(float));
	e_wsfe();
/*    1    ANGLE3,BETA3                                                  FDB 1340 */
L9900:
	*ierror = 1;
	return 0;
} /* fdbeta_ */

/* Subroutine */ int fndhmn_(float *h1, float *angle, float *h2, long *len,
							 long *iter, float *hmin, float *phi, long *ierror)
{
	/* Initialized data */

	static float dh = 1.f;
	static float eta = 5e-8f;

	/* Format strings */
	static char fmt_22[] = "(///,\002 TANGENT PATH WITH H1 = \002,f10.3,\002"
						   " AND ANGLE = \002,f10.3,\002 INTERSECTS THE EARTH\002,//,10x,"
						   "\002H2 HAS BEEN RESET \002,\002TO 0.0 AND LEN TO 0\002)";
	static char fmt_20[] = "(\0020H2 IS LESS THAN THE TANGENT HEIGHT FOR THI"
						   "S PATH \002,\002AND CANNOT BE REACHED\002)";
	static char fmt_24[] = "(///,\0020FROM SUBROUTINE FNDHMN :\002,//,10x"
						   ",\002THE PROCEEDURE TO FIND THE TANGENT HEIGHT DID NOT \002,\002"
						   "CONVERG AFTER \002,i3,\002  ITERATIONS\002,//,10x,\002CPATH   ="
						   " \002,f12.5,\002 KM\002,//,10x,\002CT3     = \002,f12.5,\002 K"
						   "M\002,//,10x,\002DC      = \002,e12.3,\002 KM\002,//,10x,\002HT3"
						   "     = \002,f12.5,\002 KM\002)";

	/* System generated locals */
	float r__1;

	/* Builtin functions */
	double sin(double);
	long s_wsfe(cilist *), do_fio(long *, char *, long), e_wsfe(void);
	double asin(double);
	/* Subroutine */ int s_stop(char *, long);

	/* Local variables */
	static long n;
	static float dc, sh, ht, ch2, ct1, ct2, ct3, ht1, ht2, ht3, cmin, gamma;
	extern double andex_(float *, float *, float *);
	static float cpath;
	extern /* Subroutine */ int findsh_(float *, float *, float *);

	/* Fortran I/O blocks */
	static cilist io___581 = {0, 0, 0, fmt_22, 0};
	static cilist io___582 = {0, 0, 0, fmt_20, 0};
	static cilist io___583 = {0, 0, 0, fmt_24, 0};

	/* ***********************************************************************FNH  110 */
	/*     THIS SUBROUTINE CALCULATES THE MINIMUM ALTITUDE HMIN ALONG        FNH  120 */
	/*     THE REFRACTED PATH AND THE FINAL ZENITH ANGLE PHI.                FNH  130 */
	/*     THE PARAMETER LEN INDICATES WHETHER THE PATH GOES THROUGH         FNH  140 */
	/*     A TANGENT HEIGHT (LEN=1) OR NOT (LEN=0).  IF ANGLE > 90 AND       FNH  150 */
	/*     H1 > H2, THEN LEN CAN EITHER BE 1 OR 0, AND THE CHOICE IS         FNH  160 */
	/*     LEFT TO THE USER.                                                 FNH  170 */
	/*     THE (INDEX OF REFRACTION - 1.0) IS MODELED AS AN EXPONENTIAL      FNH  180 */
	/*     BETWEEN THE LAYER BOUNDARIES, WITH A SCALE HEIGHT SH AND AN       FNH  190 */
	/*     AMOUNT AT THE GROUND GAMMA.                                       FNH  200 */
	/*     CPATH IS THE REFRACTIVE CONSTANT FOR THIS PATH AND                FNH  210 */
	/*     EQUALS  INDEX(H1)*(RE+H1)*SIN(ANGLE).                             FNH  220 */
	/* ***********************************************************************FNH  230 */
	/* *****ETA MAY BE TOO SMALL FOR SOME COMPUTERS. TRY 1.0E-7 FOR 32 BIT    FNH  290 */
	/* *****WORD MACHINES                                                     FNH  300 */
	/*     CRFRCT IS REFRACTIVE CONSTANT FOR THE PATH                        FNH  310 */
	/*                                                                       FNH  320 */
	n = 0;
	findsh_(h1, &sh, &gamma);
	cpath = (parmtr_1.re + *h1) * andex_(h1, &sh, &gamma) * sin(*angle / cnstns_1.deg);
	findsh_(h2, &sh, &gamma);
	ch2 = (parmtr_1.re + *h2) * andex_(h2, &sh, &gamma);
	if ((r__1 = cpath / ch2, dabs(r__1)) > 1.f)
	{
		goto L200;
	}
	if (*angle > 90.f)
	{
		goto L100;
	}
	*len = 0;
	*hmin = *h1;
	goto L160;
L100:
	if (*h1 <= *h2)
	{
		*len = 1;
	}
	if (*len == 1)
	{
		goto L110;
	}
	*len = 0;
	*hmin = *h2;
	goto L160;
L110:
	/* *****LONG PATH THROUGH A TANGENT HEIGHT.                               FNH  510 */
	/* *****SOLVE ITERATIVELY FOR THE TANGENT HEIGHT HT.                      FNH  520 */
	/* *****HT IS THE HEIGHT FOR WHICH  INDEX(HT)*(RE+HT) = CPATH.            FNH  530 */
	findsh_(&c_b1257, &sh, &gamma);
	cmin = (parmtr_1.re + c_b1257) * andex_(&c_b1257, &sh, &gamma);
	/* *****FOR BETA CASES (ITER>0), ALLOW FOR HT < 0.0                       FNH  560 */
	if (*iter == 0 && cpath < cmin)
	{
		goto L150;
	}
	ht1 = (parmtr_1.re + *h1) * sin(*angle / cnstns_1.deg) - parmtr_1.re;
	findsh_(&ht1, &sh, &gamma);
	ct1 = (parmtr_1.re + ht1) * andex_(&ht1, &sh, &gamma);
	ht2 = ht1 - dh;
	findsh_(&ht2, &sh, &gamma);
	ct2 = (parmtr_1.re + ht2) * andex_(&ht2, &sh, &gamma);
	/* *****ITERATE TO FIND HT                                                FNH  640 */
	n = 2;
L120:
	if (ct2 == ct1)
	{
		goto L125;
	}
	++n;
	ht3 = ht2 + (ht2 - ht1) * (cpath - ct2) / (ct2 - ct1);
	findsh_(&ht3, &sh, &gamma);
	ct3 = (parmtr_1.re + ht3) * andex_(&ht3, &sh, &gamma);
	dc = cpath - ct3;
	if ((r__1 = (cpath - ct3) / cpath, dabs(r__1)) < eta)
	{
		goto L130;
	}
	if (n > 15)
	{
		goto L210;
	}
	ht1 = ht2;
	ct1 = ct2;
	ht2 = ht3;
	ct2 = ct3;
	goto L120;
L125:
	ht3 = ht2;
L130:
	ht = ht3;
	*hmin = ht;
	goto L160;
L150:
	if (cntrl_1.issgeo == 0)
	{
		goto L155;
	}
	*ierror = -5.f;
	return 0;
L155:
	/* *****TANGENT PATH INTERSECTS EARTH                                     FNH  900 */
	*h2 = 0.f;
	*hmin = 0.f;
	*len = 0;
	ch2 = cmin;
	if (cntrl_1.issgeo != 1)
	{
		io___581.ciunit = ifil_1.ipr;
		s_wsfe(&io___581);
		do_fio(&c__1, (char *)&(*h1), (long)sizeof(float));
		do_fio(&c__1, (char *)&(*angle), (long)sizeof(float));
		e_wsfe();
	}
L160:
	/* *****CALCULATE THE ZENITH ANGLE PHI AT H2                              FNH 1000 */
	*phi = asin(cpath / ch2) * cnstns_1.deg;
	if (*angle <= 90.f || *len == 1)
	{
		*phi = 180.f - *phi;
	}
	return 0;
/* *****H2 LT TANGENT HEIGHT FOR THIS H1 AND ANGLE                        FNH 1040 */
L200:
	io___582.ciunit = ifil_1.ipr;
	s_wsfe(&io___582);
	e_wsfe();
	*ierror = 2;
	return 0;
L210:
	dc = cpath - ct3;
	io___583.ciunit = ifil_1.ipr;
	s_wsfe(&io___583);
	do_fio(&c__1, (char *)&n, (long)sizeof(long));
	do_fio(&c__1, (char *)&cpath, (long)sizeof(float));
	do_fio(&c__1, (char *)&ct3, (long)sizeof(float));
	do_fio(&c__1, (char *)&dc, (long)sizeof(float));
	do_fio(&c__1, (char *)&ht3, (long)sizeof(float));
	e_wsfe();
	s_stop((char *)"20", (long)2);
	return 0;
} /* fndhmn_ */

/* Subroutine */ int findsh_(float *h__, float *sh, float *gamma)
{
	/* System generated locals */
	long i__1;

	/* Local variables */
	static long i1, i2, im;
	extern /* Subroutine */ int scalht_(float *, float *, float *, float *, float *, float *);

	/* *****GIVEN AN ALTITUDE H, THIS SUBROUTINE FINDS THE LAYER BOUNDARIES   FIN  110 */
	/* *****ZM(I1) AND ZM(I2) WHICH CONTAIN H,  THEN CALCULATES THE SCALE     FIN  120 */
	/* *****HEIGHT (SH) AND THE VALUE AT THE GROUND (GAMMA+1) FOR THE         FIN  130 */
	/* *****INDEX OF REFRACTION                                               FIN  140 */
	i__1 = parmtr_1.imod;
	for (im = 2; im <= i__1; ++im)
	{
		i2 = im;
		if (model_4.z__[im - 1] >= *h__)
		{
			goto L110;
		}
		/* L100: */
	}
	i2 = parmtr_1.imod;
L110:
	i1 = i2 - 1;
	scalht_(&model_4.z__[i1 - 1], &model_4.z__[i2 - 1], &model_4.rfndx[i1 - 1], &model_4.rfndx[i2 - 1], sh, gamma);
	return 0;
} /* findsh_ */

/* Subroutine */ int scalht_(float *z1, float *z2, float *rfndx1, float *rfndx2,
							 float *sh, float *gamma)
{
	/* System generated locals */
	float r__1;
	double d__1, d__2;

	/* Builtin functions */
	double log(double), pow_dd(double *, double *);

	/* Local variables */
	static float rf1, rf2, ratio;

	/* ***********************************************************************SCA  110 */
	/*     THIS SUBROUTINE CALCULATES THE SCALE HEIGHT SH OF THE (INDEX OF   SCA  120 */
	/*     REFRACTION-1.0) FROM THE VALUES OF THE INDEX AT THE ALTITUDES Z1  SCA  130 */
	/*     AND Z2 ( Z1 < Z2). IT ALSO CALCULATES THE EXTRAPOLATED VALUE      SCA  140 */
	/*     GAMMA OF THE (INDEX-1.0) AT Z = 0.0                               SCA  150 */
	/* ***********************************************************************SCA  160 */
	rf1 = *rfndx1 + 1e-20f;
	rf2 = *rfndx2 + 1e-20f;
	ratio = rf1 / rf2;
	if ((r__1 = ratio - 1.f, dabs(r__1)) < 1e-5f)
	{
		goto L100;
	}
	*sh = (*z2 - *z1) / log(ratio);
	d__1 = (double)(rf2 / rf1);
	d__2 = (double)(-(*z1) / (*z2 - *z1));
	*gamma = rf1 * pow_dd(&d__1, &d__2);
	goto L110;
L100:
	/* *****THE VARIATION IN THE INDEX OF REFRACTION WITH HEIGHT IS           SCA  250 */
	/* *****INSIGNIFICANT OR ZERO                                             SCA  260 */
	*sh = 0.f;
	*gamma = *rfndx1;
L110:
	return 0;
} /* scalht_ */

double radref_(float *h__, float *sh, float *gamma)
{
	/* System generated locals */
	float ret_val;

	/* Builtin functions */
	double exp(double);

	/* Local variables */
	static float hsh;

	/* ***********************************************************************RDF  110 */
	/*     COMPUTES THE RADIUS OF CURVATURE OF THE REFRACTED RAY FOR         RDF  120 */
	/*     HORIZONTAL PATH:  RADREF = ANDEX/ D(ANDEX)/D(RADIUS)              RDF  130 */
	/* ***********************************************************************RDF  140 */
	if (*sh == 0.f)
	{
		goto L20;
	}
	hsh = *h__ / *sh;
	if (hsh > cnstns_1.bigexp)
	{
		goto L20;
	}
	ret_val = *sh * (exp(hsh) / *gamma + 1.f);
	return ret_val;
L20:
	ret_val = cnstns_1.bignum;
	return ret_val;
} /* radref_ */

/* Subroutine */ int rfpath_(float *h1, float *h2, float *angle, float *phi,
							 long *len, float *hmin, long *iamt, float *beta, float *range,
							 float *bendng)
{
	/* Initialized data */

	// changed from source to allow C++ (removes null-terminator)
	static char hlow[2 * 2] = {'H', '1',
							   'H', '2'};

	/* Format strings */
	static char fmt_20[] = "(\0021CALCULATION OF THE REFRACTED PATH THROUGH "
						   "THE \002,\002ATMOSPHERE\002,///,t3,\002I\002,t11,\002ALTITUDE"
						   "\002,t27,\002THETA\002,t34,\002DRANGE\002,t44,\002RANGE\002,t53"
						   ",\002DBETA\002,t63,\002BETA\002,t72,\002PHI\002,t80,\002DBEND"
						   "\002,t87,\002BENDING\002,t98,\002PBAR\002,t106,\002TBAR\002,t113,"
						   "\002RHOBAR\002,/,t07,\002FROM\002,t18,\002TO\002,/,t07,\002(KM"
						   ")\002,t17,\002(KM)\002,t27,\002(DEG)\002,t36,\002(KM)\002,t45"
						   ",\002(KM)\002,t53,\002(DEG)\002,t62,\002(DEG)\002,t71,\002(DEG"
						   ")\002,t80,\002(DEG)\002,t89,\002(DEG)\002,t098,\002(MB)\002,t106,"
						   "\002(K)\002,t111,\002(GM CM-3)\002,/)";
	static char fmt_24[] = "(\002 \002,t7,\002TANGENT\002,t17,a2,/,t7,\002HE"
						   "IGHT\002,/)";
	static char fmt_22[] = "(\002 \002,i2,2f9.3,9f9.3,f8.2,1pe9.2)";
	static char fmt_26[] = "(\0020\002,t10,\002DOUBLE RANGE, BETA, BENDIN"
						   "G\002,/,t10,\002FOR SYMMETRIC PART OF PATH\002,t40,f9.3,t58,f9.3"
						   ",t85,f9.3,/)";
	static char fmt_28[] = "(\002 \002,t11,a2,\002 TO \002,a2,/)";

	/* System generated locals */
	long i__1;

	/* Builtin functions */
	long s_wsfe(cilist *), e_wsfe(void);
	double sin(double);
	long do_fio(long *, char *, long);
	double asin(double), cos(double);

	/* Local variables */
	static long j;
	static float s;
	static long j1, j2;
	static float ha, hb;
	static long ja, ka, jd;
	static float sh, ds;
	static long jo, j2a, j2b, jha, max__;
	static float pbar;
	extern /* Subroutine */ int fill_(float *, float *, long *);
	static float tbar;
	static long jmax;
	static float dbend, dbeta, gamma;
	static long ihigh;
	static float cosai, cpath;
	extern double andex_(float *, float *, float *);
	static float sinai, theta;
	extern /* Subroutine */ int layer_(long *, float *, float *, float *,
									   float *, float *, long *, float *, float *);
	static long ihlow, jnext;
	static float anglea;
	extern /* Subroutine */ int findsh_(float *, float *, float *);
	static float rhobar;
	extern /* Subroutine */ int scalht_(float *, float *, float *, float *, float *, float *);
	static long iorder;

	/* Fortran I/O blocks */
	static cilist io___598 = {0, 0, 0, fmt_20, 0};
	static cilist io___606 = {0, 0, 0, fmt_24, 0};
	static cilist io___618 = {0, 0, 0, fmt_22, 0};
	static cilist io___621 = {0, 0, 0, fmt_26, 0};
	static cilist io___628 = {0, 0, 0, fmt_28, 0};
	static cilist io___629 = {0, 0, 0, fmt_22, 0};

	/* ***********************************************************************RFP  110 */
	/*     THIS SUBROUTINE  TRACES THE REFRACTED RAY FROM H1 WITH A          RFP  120 */
	/*     INITIAL ZENITH ANGLE ANGLE TO H2 WHERE THE ZENITH ANGLE IS PHI,   RFP  130 */
	/*     AND CALCULATES THE ABSORBER AMOUNTS (IF IAMT.EQ.1) ALONG          RFP  140 */
	/*     THE PATH.  IT STARTS FROM THE LOWEST POINT ALONG THE PATH         RFP  150 */
	/*     (THE TANGENT HEIGHT HMIN IF LEN = 1 OR HA = MIN(H1,H2) IF LEN = 0)RFP  160 */
	/*     AND PROCEEDS TO THE HIGHEST POINT.  BETA AND RANGE ARE THE        RFP  170 */
	/*     EARTH CENTERED ANGLE AND THE TOTAL DISTANCE RESPECTIVELY          RFP  180 */
	/*     FOR THE REFRACTED PATH FROM H1 TO H2                              RFP  190 */
	/* ***********************************************************************RFP  200 */
	max__ = 0;
	if (*h1 > *h2)
	{
		goto L90;
	}
	iorder = 1;
	ha = *h1;
	hb = *h2;
	anglea = *angle;
	goto L95;
L90:
	iorder = -1;
	ha = *h2;
	hb = *h1;
	anglea = *phi;
L95:
	jnext = 1;
	if (*iamt == 1 && ifil_1.npr != 1)
	{
		io___598.ciunit = ifil_1.ipr;
		s_wsfe(&io___598);
		e_wsfe();
	}
	if (*len == 0)
	{
		goto L100;
	}
	/* *****LONG PATH: FILL IN THE SYMETRIC PART FROM THE TANGENT HEIGHT      RFP  600 */
	/* *****TO HA                                                             RFP  610 */
	fill_(hmin, &ha, &jnext);
	jha = jnext;
L100:
	/* *****FILL IN THE REMAINING PATH FROM HA TO HB                          RFP  650 */
	if (ha == hb)
	{
		goto L110;
	}
	fill_(&ha, &hb, &jnext);
L110:
	jmax = jnext;
	parmtr_1.ipath = jmax;
	/* *****INTEGRATE EACH SEGMENT OF THE PATH                                RFP  710 */
	/* *****CALCULATE CPATH SEPERATELY FOR LEN = 0,1                          RFP  720 */
	if (*len == 1)
	{
		goto L115;
	}
	findsh_(&ha, &sh, &gamma);
	cpath = (parmtr_1.re + ha) * andex_(&ha, &sh, &gamma) * sin(anglea / cnstns_1.deg);
	goto L116;
L115:
	findsh_(hmin, &sh, &gamma);
	cpath = (parmtr_1.re + *hmin) * andex_(hmin, &sh, &gamma);
L116:
	*beta = 0.f;
	s = 0.f;
	*bendng = 0.f;
	if (*len == 0)
	{
		goto L140;
	}
	/* *****DO SYMETRIC PART, FROM TANGENT HEIGHT(HMIN) TO HA                 RFP  850 */
	ihlow = 1;
	if (iorder == -1)
	{
		ihlow = 2;
	}
	if (*iamt == 1 && ifil_1.npr != 1)
	{
		io___606.ciunit = ifil_1.ipr;
		s_wsfe(&io___606);
		do_fio(&c__1, hlow + ((ihlow - 1) << 1), (long)2);
		e_wsfe();
	}
	sinai = 1.f;
	cosai = 0.f;
	theta = 90.f;
	j2 = jha - 1;
	i__1 = j2;
	for (j = 1; j <= i__1; ++j)
	{
		scalht_(&rfrpth_1.zp[j - 1], &rfrpth_1.zp[j], &rfrpth_1.rfndxp[j - 1],
				&rfrpth_1.rfndxp[j], &sh, &gamma);
		layer_(&j, &sinai, &cosai, &cpath, &sh, &gamma, iamt, &ds, &dbend);
		dbend *= cnstns_1.deg;
		*phi = asin(sinai) * cnstns_1.deg;
		dbeta = theta - *phi + dbend;
		*phi = 180.f - *phi;
		s += ds;
		/*                                                                       RFP 1020 */
		/*   SAVE REFRACTED RAY PATH LENGTH FOR USE WITH MULTIPLE SCATTERING     RFP 1030 */
		/*                                                                       RFP 1040 */
		*bendng += dbend;
		*beta += dbeta;
		if (*iamt != 1)
		{
			goto L118;
		}
		pbar = rfrpth_1.ppsum[j - 1] / rfrpth_1.rhopsm[j - 1];
		tbar = rfrpth_1.tpsum[j - 1] / rfrpth_1.rhopsm[j - 1];
		rhobar = rfrpth_1.rhopsm[j - 1] / ds;
		if (*iamt == 1 && ifil_1.npr != 1)
		{
			io___618.ciunit = ifil_1.ipr;
			s_wsfe(&io___618);
			do_fio(&c__1, (char *)&j, (long)sizeof(long));
			do_fio(&c__1, (char *)&rfrpth_1.zp[j - 1], (long)sizeof(float));
			do_fio(&c__1, (char *)&rfrpth_1.zp[j], (long)sizeof(float));
			do_fio(&c__1, (char *)&theta, (long)sizeof(float));
			do_fio(&c__1, (char *)&ds, (long)sizeof(float));
			do_fio(&c__1, (char *)&s, (long)sizeof(float));
			do_fio(&c__1, (char *)&dbeta, (long)sizeof(float));
			do_fio(&c__1, (char *)&(*beta), (long)sizeof(float));
			do_fio(&c__1, (char *)&(*phi), (long)sizeof(float));
			do_fio(&c__1, (char *)&dbend, (long)sizeof(float));
			do_fio(&c__1, (char *)&(*bendng), (long)sizeof(float));
			do_fio(&c__1, (char *)&pbar, (long)sizeof(float));
			do_fio(&c__1, (char *)&tbar, (long)sizeof(float));
			do_fio(&c__1, (char *)&rhobar, (long)sizeof(float));
			e_wsfe();
		}
		j2a = j2 - j + 1;
		j2b = j2 + j;
		path_1.qtheta[j2a - 1] = *phi * cnstns_1.ca;
		path_1.qtheta[j2b - 1] = theta * cnstns_1.ca;
		max__ = j2b;
	L118:
		if (cntrl_1.issgeo == 1)
		{
			goto L119;
		}
		sols_1.atheta[j - 1] = theta;
		sols_1.adbeta[j - 1] = dbeta;
	L119:
		theta = 180.f - *phi;
		/* L120: */
	}
	/* *****DOUBLE PATH QUANTITIES FOR THE OTHER PART OF THE SYMETRIC PATH    RFP 1260 */
	*bendng *= 2.f;
	*beta *= 2.f;
	s *= 2.f;
	if (*iamt == 1 && ifil_1.npr != 1)
	{
		io___621.ciunit = ifil_1.ipr;
		s_wsfe(&io___621);
		do_fio(&c__1, (char *)&s, (long)sizeof(float));
		do_fio(&c__1, (char *)&(*beta), (long)sizeof(float));
		do_fio(&c__1, (char *)&(*bendng), (long)sizeof(float));
		e_wsfe();
	}
	jnext = jha;
	goto L150;
L140:
	/* *****SHORT PATH                                                        RFP 1370 */
	jnext = 1;
	/* *****ANGLEA IS THE ZENITH ANGLE AT HA IN DEG                           RFP 1390 */
	/* *****SINAI IS SIN OF THE INCIDENCE ANGLE                               RFP 1400 */
	/* *****COSAI IS CARRIED SEPERATELY TO AVOID A PRECISION PROBLEM          RFP 1410 */
	/* *****WHEN SINAI IS CLOSE TO 1.0                                        RFP 1420 */
	theta = anglea;
	if (anglea > 45.f)
	{
		goto L145;
	}
	sinai = sin(anglea / cnstns_1.deg);
	cosai = -cos(anglea / cnstns_1.deg);
	goto L150;
L145:
	sinai = cos((90.f - anglea) / cnstns_1.deg);
	cosai = -sin((90.f - anglea) / cnstns_1.deg);
L150:
	/* *****DO PATH FROM HA TO HB                                             RFP 1520 */
	if (ha == hb)
	{
		goto L170;
	}
	jo = max__ - jnext + 1;
	j1 = jnext;
	j2 = jmax - 1;
	/*                                                                       RFP 1570 */
	if (*h1 > *h2)
	{
		jd = j2 - j1 + 1;
		i__1 = max__;
		for (j = 1; j <= i__1; ++j)
		{
			ka = max__ - j + 1;
			ja = ka + jd;
			path_1.qtheta[ja - 1] = path_1.qtheta[ka - 1];
			/* L1158: */
		}
		max__ += jd;
		jo = 0;
	}
	/*                                                                       RFP 1680 */
	ihlow = 1;
	if (iorder == -1)
	{
		ihlow = 2;
	}
	ihigh = ihlow % 2 + 1;
	if (*iamt == 1 && ifil_1.npr != 1)
	{
		io___628.ciunit = ifil_1.ipr;
		s_wsfe(&io___628);
		do_fio(&c__1, hlow + ((ihlow - 1) << 1), (long)2);
		do_fio(&c__1, hlow + ((ihigh - 1) << 1), (long)2);
		e_wsfe();
	}
	i__1 = j2;
	for (j = j1; j <= i__1; ++j)
	{
		scalht_(&rfrpth_1.zp[j - 1], &rfrpth_1.zp[j], &rfrpth_1.rfndxp[j - 1],
				&rfrpth_1.rfndxp[j], &sh, &gamma);
		layer_(&j, &sinai, &cosai, &cpath, &sh, &gamma, iamt, &ds, &dbend);
		dbend *= cnstns_1.deg;
		*phi = asin(sinai) * cnstns_1.deg;
		dbeta = theta - *phi + dbend;
		*phi = 180.f - *phi;
		s += ds;
		/*                                                                       RFP 1830 */
		/*    SAVE LAYER REFRACTED PATH LENGTH FOR USE WITH MULTIPLE SCATTERING  RFP 1840 */
		/*                                                                       RFP 1850 */
		path_1.pl[j - 1] = ds;
		*bendng += dbend;
		*beta += dbeta;
		if (*iamt != 1)
		{
			goto L158;
		}
		pbar = rfrpth_1.ppsum[j - 1] / rfrpth_1.rhopsm[j - 1];
		tbar = rfrpth_1.tpsum[j - 1] / rfrpth_1.rhopsm[j - 1];
		rhobar = rfrpth_1.rhopsm[j - 1] / ds;
		if (*iamt == 1 && ifil_1.npr != 1)
		{
			io___629.ciunit = ifil_1.ipr;
			s_wsfe(&io___629);
			do_fio(&c__1, (char *)&j, (long)sizeof(long));
			do_fio(&c__1, (char *)&rfrpth_1.zp[j - 1], (long)sizeof(float));
			do_fio(&c__1, (char *)&rfrpth_1.zp[j], (long)sizeof(float));
			do_fio(&c__1, (char *)&theta, (long)sizeof(float));
			do_fio(&c__1, (char *)&ds, (long)sizeof(float));
			do_fio(&c__1, (char *)&s, (long)sizeof(float));
			do_fio(&c__1, (char *)&dbeta, (long)sizeof(float));
			do_fio(&c__1, (char *)&(*beta), (long)sizeof(float));
			do_fio(&c__1, (char *)&(*phi), (long)sizeof(float));
			do_fio(&c__1, (char *)&dbend, (long)sizeof(float));
			do_fio(&c__1, (char *)&(*bendng), (long)sizeof(float));
			do_fio(&c__1, (char *)&pbar, (long)sizeof(float));
			do_fio(&c__1, (char *)&tbar, (long)sizeof(float));
			do_fio(&c__1, (char *)&rhobar, (long)sizeof(float));
			e_wsfe();
		}
	L158:
		/*                                                                       RFP 1960 */
		/*   SAVE LAYER REFRACTED PATH ANGLE FOR USE WITH MULTIPLE SCATTERING    RFP 1970 */
		/*                                                                       RFP 1980 */
		/*                                                                       RFP 1990 */
		if (*h2 > *h1)
		{
			path_1.qtheta[j + jo - 1] = theta * cnstns_1.ca;
			max__ = j + jo;
		}
		else
		{
			j2b = j2 - j + 1;
			path_1.qtheta[j2b - 1] = *phi * cnstns_1.ca;
		}
		/*                                                                       RFP 2070 */
		if (cntrl_1.issgeo == 1)
		{
			goto L159;
		}
		sols_1.adbeta[j - 1] = dbeta;
		sols_1.atheta[j - 1] = theta;
	L159:
		theta = 180.f - *phi;
		/* L160: */
	}
L170:
	if (cntrl_1.issgeo == 0)
	{
		sols_1.atheta[jmax - 1] = theta;
	}
	if (iorder == -1)
	{
		*phi = anglea;
	}
	*range = s;
	return 0;
} /* rfpath_ */

/* Subroutine */ int fill_(float *ha, float *hb, long *jnext)
{
	/* Format strings */
	static char fmt_22[] = "(\0020SUBROUTINE FILL- ERROR, HA .GE. HB\002,//,"
						   "10x,\002HA, HB, JNEXT = \002,2e25.15,i6)";

	/* System generated locals */
	long i__1, i__2;

	/* Builtin functions */
	long s_wsfe(cilist *), do_fio(long *, char *, long), e_wsfe(void);
	/* Subroutine */ int s_stop(char *, long);

	/* Local variables */
	static float a;
	static long i__, k, i1, i2, ia, ib;
	extern /* Subroutine */ int expint_(float *, float *, float *, float *);

	/* Fortran I/O blocks */
	static cilist io___630 = {0, 0, 0, fmt_22, 0};

	/* ********************************************************************   FLL  110 */
	/*     THIS SUBROUTINE DEFINES THE ATMOSPHERIC BOUNDARIES OF THE PATH    FLL  120 */
	/*     FROM HA TO HB AND INTERPOLATES (EXTRAPOLATES) THE DENSITIES TO    FLL  130 */
	/*     THESE BOUNDARIES ASSUMING THE DENSITIES VARY EXPONENTIALLY        FLL  140 */
	/*     WITH HEIGHT                                                       FLL  150 */
	/* ********************************************************************   FLL  160 */
	if (*ha < *hb)
	{
		goto L90;
	}
	io___630.ciunit = ifil_1.ipr;
	s_wsfe(&io___630);
	do_fio(&c__1, (char *)&(*ha), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*hb), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*jnext), (long)sizeof(long));
	e_wsfe();
	s_stop((char *)"", (long)0);
L90:
	/* *****FIND Z(IA): THE SMALLEST Z(I).GT.HA                               FLL  310 */
	i__1 = parmtr_1.imax;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		if (*ha >= model_4.z__[i__ - 1])
		{
			goto L100;
		}
		ia = i__;
		goto L110;
	L100:;
	}
	ia = parmtr_1.imax + 1;
	ib = ia;
	goto L130;
/* *****FIND Z(IB): THE SMALLEST Z(I).GE.HB                               FLL  400 */
L110:
	i__1 = parmtr_1.imax;
	for (i__ = ia; i__ <= i__1; ++i__)
	{
		if (*hb - model_4.z__[i__ - 1] > 1e-4f)
		{
			goto L120;
		}
		ib = i__;
		goto L130;
	L120:;
	}
	ib = parmtr_1.imax + 1;
L130:
	/* *****INTERPOLATE DENSITIES TO HA, HB                                   FLL  490 */
	rfrpth_1.zp[*jnext - 1] = *ha;
	i2 = ia;
	if (i2 == 1)
	{
		i2 = 2;
	}
	if (i2 > parmtr_1.imax)
	{
		i2 = parmtr_1.imax;
	}
	i1 = i2 - 1;
	a = (*ha - model_4.z__[i1 - 1]) / (model_4.z__[i2 - 1] - model_4.z__[i1 -
																		 1]);
	expint_(&rfrpth_1.pp[*jnext - 1], &model_4.p[i1 - 1], &model_4.p[i2 - 1],
			&a);
	rfrpth_1.tp[*jnext - 1] = model_4.t[i1 - 1] + (model_4.t[i2 - 1] -
												   model_4.t[i1 - 1]) *
													  a;
	expint_(&rfrpth_1.rfndxp[*jnext - 1], &model_4.rfndx[i1 - 1], &model_4.rfndx[i2 - 1], &a);
	i__1 = cntrl_1.kmax;
	for (k = 1; k <= i__1; ++k)
	{
		expint_(&rfrpth_1.denp[k + *jnext * 63 - 64], &model_4.densty[k + i1 * 63 - 64], &model_4.densty[k + i2 * 63 - 64], &a);
		/* L140: */
	}
	if (ia == ib)
	{
		goto L160;
	}
	/* *****FILL IN DENSITIES BETWEEN HA AND HB                               FLL  630 */
	i1 = ia;
	i2 = ib - 1;
	i__1 = i2;
	for (i__ = i1; i__ <= i__1; ++i__)
	{
		++(*jnext);
		rfrpth_1.zp[*jnext - 1] = model_4.z__[i__ - 1];
		rfrpth_1.pp[*jnext - 1] = model_4.p[i__ - 1];
		rfrpth_1.tp[*jnext - 1] = model_4.t[i__ - 1];
		rfrpth_1.rfndxp[*jnext - 1] = model_4.rfndx[i__ - 1];
		i__2 = cntrl_1.kmax;
		for (k = 1; k <= i__2; ++k)
		{
			rfrpth_1.denp[k + *jnext * 63 - 64] = model_4.densty[k + i__ * 63 - 64];
			/* L150: */
		}
	}
L160:
	/* *****INTERPOLATE THE DENSITIES TO HB                                   FLL  760 */
	++(*jnext);
	rfrpth_1.zp[*jnext - 1] = *hb;
	i2 = ib;
	if (i2 == 1)
	{
		i2 = 2;
	}
	if (i2 > parmtr_1.imax)
	{
		i2 = parmtr_1.imax;
	}
	i1 = i2 - 1;
	a = (*hb - model_4.z__[i1 - 1]) / (model_4.z__[i2 - 1] - model_4.z__[i1 -
																		 1]);
	expint_(&rfrpth_1.pp[*jnext - 1], &model_4.p[i1 - 1], &model_4.p[i2 - 1],
			&a);
	rfrpth_1.tp[*jnext - 1] = model_4.t[i1 - 1] + (model_4.t[i2 - 1] -
												   model_4.t[i1 - 1]) *
													  a;
	expint_(&rfrpth_1.rfndxp[*jnext - 1], &model_4.rfndx[i1 - 1], &model_4.rfndx[i2 - 1], &a);
	i__2 = cntrl_1.kmax;
	for (k = 1; k <= i__2; ++k)
	{
		expint_(&rfrpth_1.denp[k + *jnext * 63 - 64], &model_4.densty[k + i1 * 63 - 64], &model_4.densty[k + i2 * 63 - 64], &a);
		/* L170: */
	}
	return 0;
} /* fill_ */

/* Subroutine */ int layer_(long *j, float *sinai, float *cosai, float *cpath,
							float *sh, float *gamma, long *iamt, float *s, float *bend)
{
	/* Initialized data */

	static float epsiln = 1e-5f;

	/* System generated locals */
	long i__1;
	float r__1, r__2, r__3;

	/* Builtin functions */
	double log(double), sqrt(double), exp(double);

	/* Local variables */
	static long k, n;
	static float h1, h2, h3, r1, r2, r3, w1, x1, y1, z1, z2, y3, x3, w2, w3,
		x2, d21, d31, d32, dh, pa, pb, ta, tb, hp, dx, dz, ds, h3z1, dena[63], denb[63], hden[63], dhhp, dhrh, rhoa, rhob, hrho, dsdz,
		dsdx1, dsdx2, dsdx3, dbend, dhmin;
	extern double andex_(float *, float *, float *);
	static float cosai1, dbndx1, cosai3, cosai2, dbndx2, sinai1, sinai2,
		sinai3, dbndx3, ratio1, ratio2, ratio3;
	extern double radref_(float *, float *, float *);

	/* *****************************************************************      LYR  110 */
	/*     THIS SUBROUTINE CALCULATES THE REFRACTED PATH FROM Z1 TO Z2       LYR  120 */
	/*     WITH THE SIN OF THE INITIAL INCIDENCE ANGLE SINAI                 LYR  130 */
	/* *****************************************************************      LYR  140 */
	/* *****INITIALIZE LOOP                                                   LYR  220 */
	n = 0;
	z1 = rfrpth_1.zp[*j - 1];
	z2 = rfrpth_1.zp[*j];
	h1 = z1;
	r1 = parmtr_1.re + h1;
	/* Computing 2nd power */
	r__1 = parmtr_1.deltas;
	dhmin = r__1 * r__1 / (r1 * 2.f);
	sinai1 = *sinai;
	cosai1 = *cosai;
	/* Computing 2nd power */
	r__1 = cosai1;
	/* Computing 4th power */
	r__2 = cosai1, r__2 *= r__2;
	/* Computing 6th power */
	r__3 = cosai1, r__3 *= r__3;
	y1 = r__1 * r__1 / 2.f + r__2 * r__2 / 8.f + r__3 * (r__3 * r__3) * 3.f / 48.f;
	y3 = 0.f;
	x1 = -r1 * cosai1;
	ratio1 = r1 / radref_(&h1, sh, gamma);
	/* Computing 2nd power */
	r__1 = sinai1;
	dsdx1 = 1.f / (1.f - ratio1 * (r__1 * r__1));
	dbndx1 = dsdx1 * sinai1 * ratio1 / r1;
	*s = 0.f;
	*bend = 0.f;
	if (*iamt == 2)
	{
		goto L110;
	}
	/* *****INITIALIZE THE VARIABLES FOR THE CALCULATION OF THE               LYR  400 */
	/* *****ABSORBER AMOUNTS                                                  LYR  410 */
	pa = rfrpth_1.pp[*j - 1];
	pb = rfrpth_1.pp[*j];
	ta = rfrpth_1.tp[*j - 1];
	tb = rfrpth_1.tp[*j];
	rhoa = pa / (cnstns_1.gcair * ta);
	rhob = pb / (cnstns_1.gcair * tb);
	dz = rfrpth_1.zp[*j] - rfrpth_1.zp[*j - 1];
	hp = -dz / log(pb / pa);
	if ((r__1 = rhob / rhoa - 1.f, dabs(r__1)) < epsiln)
	{
		goto L90;
	}
	hrho = -dz / log(rhob / rhoa);
	goto L95;
L90:
	hrho = 1e30f;
L95:
	i__1 = cntrl_1.kmax;
	for (k = 1; k <= i__1; ++k)
	{
		dena[k - 1] = rfrpth_1.denp[k + *j * 63 - 64];
		denb[k - 1] = rfrpth_1.denp[k + (*j + 1) * 63 - 64];
		if (dena[k - 1] <= 0.f || denb[k - 1] <= 0.f)
		{
			goto L100;
		}
		if ((r__1 = 1.f - dena[k - 1] / denb[k - 1], dabs(r__1)) <= epsiln)
		{
			goto L100;
		}
		/* *****USE EXPONENTIAL INTERPOLATION                                     LYR  600 */
		hden[k - 1] = -dz / log(denb[k - 1] / dena[k - 1]);
		goto L105;
	/* *****USE LINEAR INTERPOLATION                                          LYR  630 */
	L100:
		hden[k - 1] = 0.f;
	L105:;
	}
L110:
/* *****                                                                  LYR  670 */
/* *****LOOP THROUGH PATH                                                 LYR  680 */
/* *****INTEGRATE PATH QUANTITIES USING QUADRATIC INTEGRATION WITH        LYR  690 */
/* *****UNEQUALLY SPACED POINTS                                           LYR  700 */
/* *****                                                                  LYR  710 */
L115:
	++n;
	dh = -parmtr_1.deltas * cosai1;
	if (dh < dhmin)
	{
		dh = dhmin;
	}
	h3 = h1 + dh;
	if (h3 > z2)
	{
		h3 = z2;
	}
	dh = h3 - h1;
	r3 = parmtr_1.re + h3;
	h2 = h1 + dh / 2.f;
	r2 = parmtr_1.re + h2;
	sinai2 = *cpath / (andex_(&h2, sh, gamma) * r2);
	sinai3 = *cpath / (andex_(&h3, sh, gamma) * r3);
	ratio2 = r2 / radref_(&h2, sh, gamma);
	ratio3 = r3 / radref_(&h3, sh, gamma);
	if (1.f - sinai2 > epsiln)
	{
		goto L116;
	}
	/* *****NEAR A TANGENT HEIGHT, COSAI = -SQRT(1-SINAI**2) LOSES            LYR  870 */
	/* *****PRECISION. USE THE FOLLOWING ALGORITHM TO GET COSAI.              LYR  880 */
	y3 = y1 + (sinai1 * (1.f - ratio1) / r1 + sinai2 * 4.f * (1.f - ratio2) / r2 + sinai3 * (1.f - ratio3) / r3) * dh / 6.f;
	/* Computing 2nd power */
	r__1 = y3;
	cosai3 = -sqrt(y3 * 2.f - r__1 * r__1);
	x3 = -r3 * cosai3;
	dx = x3 - x1;
	w1 = dx * .5f;
	w2 = 0.f;
	w3 = dx * .5f;
	goto L118;
/* *****                                                                  LYR  980 */
L116:
	/* Computing 2nd power */
	r__1 = sinai2;
	cosai2 = -sqrt(1.f - r__1 * r__1);
	/* Computing 2nd power */
	r__1 = sinai3;
	cosai3 = -sqrt(1.f - r__1 * r__1);
	x2 = -r2 * cosai2;
	x3 = -r3 * cosai3;
	/* *****CALCULATE WEIGHTS                                                 LYR 1040 */
	d31 = x3 - x1;
	d32 = x3 - x2;
	d21 = x2 - x1;
	if (d32 == 0.f || d21 == 0.f)
	{
		goto L117;
	}
	w1 = (2 - d32 / d21) * d31 / 6.f;
	/* Computing 3rd power */
	r__1 = d31;
	w2 = r__1 * (r__1 * r__1) / (d32 * d21 * 6.f);
	w3 = (2.f - d21 / d32) * d31 / 6.f;
	goto L118;
L117:
	w1 = d31 * .5f;
	w2 = 0.f;
	w3 = d31 * .5f;
/* *****                                                                  LYR 1170 */
L118:
	/* Computing 2nd power */
	r__1 = sinai2;
	dsdx2 = 1.f / (1.f - ratio2 * (r__1 * r__1));
	/* Computing 2nd power */
	r__1 = sinai3;
	dsdx3 = 1.f / (1.f - ratio3 * (r__1 * r__1));
	dbndx2 = dsdx2 * sinai2 * ratio2 / r2;
	dbndx3 = dsdx3 * sinai3 * ratio3 / r3;
	/* *****INTEGRATE                                                         LYR 1230 */
	ds = w1 * dsdx1 + w2 * dsdx2 + w3 * dsdx3;
	*s += ds;
	dbend = w1 * dbndx1 + w2 * dbndx2 + w3 * dbndx3;
	*bend += dbend;
	if (*iamt == 2)
	{
		goto L150;
	}
	/* *****CALCULATE AMOUNTS                                                 LYR 1290 */
	dsdz = ds / dh;
	dhhp = dh / hp;
	if (dhhp <= cnstns_1.bigexp)
	{
		pb = pa * exp(-dhhp);
	}
	else
	{
		pb = 0.f;
	}
	dhrh = dh / hrho;
	if (dhrh <= cnstns_1.bigexp)
	{
		rhob = rhoa * exp(-dhrh);
	}
	else
	{
		rhob = 0.f;
	}
	if (dh / hrho < epsiln)
	{
		goto L120;
	}
	rfrpth_1.ppsum[*j - 1] += dsdz * (hp / (hp / hrho + 1.f)) * (pa * rhoa - pb * rhob);
	rfrpth_1.tpsum[*j - 1] += dsdz * hp * (pa - pb) / cnstns_1.gcair;
	rfrpth_1.rhopsm[*j - 1] += dsdz * hrho * (rhoa - rhob);
	goto L125;
L120:
	rfrpth_1.ppsum[*j - 1] += ds * .5f * (pa * rhoa + pb * rhob);
	rfrpth_1.tpsum[*j - 1] += ds * .5f * (pa + pb) / cnstns_1.gcair;
	rfrpth_1.rhopsm[*j - 1] += ds * .5f * (rhoa + rhob);
L125:
	i__1 = cntrl_1.kmax;
	for (k = 1; k <= i__1; ++k)
	{
		if ((r__1 = hden[k - 1], dabs(r__1)) == 0.f)
		{
			goto L130;
		}
		if (dh / hden[k - 1] < epsiln)
		{
			goto L130;
		}
		/* *****EXPONENTIAL INTERPOLATION                                         LYR 1560 */
		h3z1 = (h3 - z1) / hden[k - 1];
		if (h3z1 <= cnstns_1.bigexp)
		{
			denb[k - 1] = rfrpth_1.denp[k + *j * 63 - 64] * exp(-h3z1);
		}
		else
		{
			denb[k - 1] = 0.f;
		}
		rfrpth_1.amtp[k + *j * 63 - 64] += dsdz * hden[k - 1] * (dena[k - 1] - denb[k - 1]);
		goto L140;
	L130:
		/* *****LINEAR INTERPOLATION                                              LYR 1660 */
		denb[k - 1] = rfrpth_1.denp[k + *j * 63 - 64] + (rfrpth_1.denp[k + (*j + 1) * 63 - 64] - rfrpth_1.denp[k + *j * 63 - 64]) * (h3 - z1) / dz;
		rfrpth_1.amtp[k + *j * 63 - 64] += (dena[k - 1] + denb[k - 1]) * .5f *
										   ds;
	L140:;
	}
	pa = pb;
	rhoa = rhob;
	i__1 = cntrl_1.kmax;
	for (k = 1; k <= i__1; ++k)
	{
		/* L145: */
		dena[k - 1] = denb[k - 1];
	}
L150:
	if (h3 >= z2)
	{
		goto L160;
	}
	h1 = h3;
	r1 = r3;
	sinai1 = sinai3;
	ratio1 = ratio3;
	y1 = y3;
	cosai1 = cosai3;
	x1 = x3;
	dsdx1 = dsdx3;
	dbndx1 = dbndx3;
	goto L115;
L160:
	if (sinai3 > 1)
	{
		sinai3 = 1;
		printf("WARNING: Possible loss of accuracy. Clamping SINAI3 -> 1");
	}
	*sinai = sinai3;
	*cosai = cosai3;
	rfrpth_1.sp[*j - 1] = *s;
	return 0;
} /* layer_ */

/* Subroutine */ int trans_(LOWTRAN_ResultBuffer *resBuff, long *iph, long *isourc, long *iday,
							float *anglem)
{

	float *resultData = new float[static_cast<int>(2 * (card4_1.v2 - card4_1.v1) / card4_1.dv) + 2];

	long resultDataLen = 0;
	resBuff->data = resultData;
	resBuff->length = 2 * static_cast<int>((card4_1.v2 - card4_1.v1) / card4_1.dv) + 2;

	/* Format strings */
	static char fmt_931[] = "(\002  FREQ   TOTAL     H2O     CO2+ \002,\002O"
							"ZONE    TRACE  N2 CON  H2O CON MOL SCAT AER-HYD HNO3   \002,\002"
							"AER-HYD\002)";
	static char fmt_901[] = "(\002   FREQ  H2O     O3       CO2    CO    "
							"\002,\002   CH4     N2O    O2     NH3      NO     NO2      SO"
							"2\002,/\002   1/CM  TRANS   TRANS    TRANS  TRANS \002,\002   TR"
							"ANS   TRANS  TRANS  TRANS    TRANS  TRANS    TRANS\002)";
	static char fmt_932[] = "(\002  FREQ   TRANS     ATMOS   PATH     \002"
							",\002SINGLE   GROUND DIRECT   TOTAL RAD\002)";
	static char fmt_933[] = "(\002  FREQ   TRANS     SOL TR  SOLAR    \002)";
	static char fmt_1200[] = "(\002        V   ALT1    UFLX        UFLXS  "
							 "   \002,\002  DFLX        DFLXS       DIRS          TRANS \002)";
	static char fmt_1205[] = "(\002        V   ALT1   ALT2    B(V,T)     DTA"
							 "U \002,\002       TAU \002)";
	static char fmt_900[] = "(\0021\002,/1x,\002  FREQ WAVELENGTH  TOTAL    "
							" H2O     CO2+     \002,\002OZONE    TRACE  N2 CONT  H2O CONT MOL"
							" SCAT  AER-HYD  HNO3    \002,\002AER-HYD  INTEGRATED\002//1x,"
							"\002  1/CM  MICRONS    TRANS    TRANS    TRANS    \002,\002TRANS"
							"    TRANS   TRANS    TRANS    TRANS     TRANS   TRANS   \002,"
							"\002 ABS     ABSORPTION\002/)";
	static char fmt_910[] = "(\0021\002,20x,\002RADIANCE(WATTS/CM2-STER-XXX"
							")\002,/,\0020   FREQ\002,t10,\002WAVLEN\002,t19,\002ATMOS RADIAN"
							"CE\002,t39,\002 INTEGRAL\002,t049,\002TOTAL\002,/2x,\002(CM-1"
							")\002,t10,\002(MICRN)\002,t19,\002(CM-1)\002,t29,\002(MICRN)\002"
							",t39,\002(CM-1)\002,t49,\002TRANS\002,/)";
	static char fmt_920[] = "(\0021\002,45x,\002RADIANCE(WATTS/CM2-STER-XXX"
							")\002,/,\0020  FREQ\002,t11,\002WAVLEN\002,t21,\002ATMOS RADIANCE"
							"\002,t41,\002PATH SCATTERED\002,t61,\002GROUND REFLECTED\002,t85,"
							"\002TOTAL\002,t98,\002 INTEGRAL\002,t110,\002TOTAL\002,/2x,\002("
							"CM-1)\002,t10,\002(MICRN)\002,t20,\002(CM-1)\002,t30,\002(MICRN"
							")\002,t40,\002(CM-1)\002,t50,\002(MICRN)\002,t60,\002(CM-1)\002,"
							"t70,\002(MICRN)\002,t80,\002(CM-1)\002,t90,\002(MICRN)\002,t100"
							",\002(CM-1)\002,t110,\002TRANS\002,/)";
	static char fmt_921[] = "(\0021\002,45x,\002RADIANCE(WATTS/CM2-STER-XXX"
							")\002,/,/,\0020 FREQ\002,t10,\002WAVLEN\002,t20,\002ATMOS RADIAN"
							"CE\002,t40,\002PATH SCATTERED RADIANCE\002,t69,\002GROUND REFLEC"
							"TED RADIANCE\002,t100,\002TOTAL RADIANCE\002,t117,\002 INTEGRA"
							"L\002,t127,\002TOTAL\002,/,t45,\002TOTAL\002,t59,\002S SCAT\002,"
							"t75,\002TOTAL\002,t89,\002DIRECT\002,/,1x,\002(CM-1)\002,t9,\002"
							"(MICRN)\002,t19,\002(CM-1)\002,t29,\002(MICRN)\002,t39,\002(CM-1)"
							"\002,t49,\002(MICRN)\002,t59,\002(CM-1)\002,t69,\002(CM-1)\002,t"
							"79,\002(MICRN)\002,t89,\002(CM-1)\002,t99,\002(CM-1)\002,t109"
							",\002(MICRN)\002,t119,\002(CM-1)\002,t127,\002TRANS\002,/)";
	static char fmt_930[] = "(\0021\002,22x,\002IRRADIANCE (WATTS/CM2-XXXX"
							")\002,/\0020  FREQ\002,t11,\002WAVLEN\002,t23,\002TRANSMITTED"
							" \002,t45,\002SOLAR\002,t61,\002INTEGRATED\002,t80,\002TOTAL\002"
							",/,2x,\002(CM-1)\002,t10,\002(MICRN)\002,t20,\002(CM-1)\002,t30"
							",\002(MICRN)\002,t40,\002(CM-1)\002,t50,\002(MICRN)\002,t60,\002"
							"TRANS.\002,t70,\002SOLAR\002,t80,\002TRANS\002)";
	static char fmt_1210[] = "(f10.0,2f7.2,1p2e12.5,0pf12.9)";
	static char fmt_1220[] = "(\002     -999.\002,t63,\002  DTAU   EXIT LO"
							 "OP \002)";
	static char fmt_1230[] = "(f10.0,f7.2,1p5e12.5,0pf10.5)";
	static char fmt_906[] = "(1x,f7.0,f8.3,11f9.4,f12.3)";
	static char fmt_907[] = "(f7.0,11f8.4,1pe10.3)";
	static char fmt_916[] = "(1x,f7.0,f8.3,1p3e10.2,0pf9.4)";
	static char fmt_917[] = "(f7.0,f8.4,1pe9.2,t96,e10.3)";
	static char fmt_926[] = "(1x,f7.0,f8.3,1p9e10.2,0pf9.4)";
	static char fmt_928[] = "(1x,f6.0,f8.3,1p11e10.2,0pf7.4)";
	static char fmt_927[] = "(f7.0,f8.4,1p6e9.2,0p2f8.4,t96,1pe10.3)";
	static char fmt_936[] = "(1x,f7.0,f8.3,1p6e10.2,0pf9.4)";
	static char fmt_937[] = "(f7.0,f8.4,1p2e9.2,t96,e10.3)";
	static char fmt_740[] = "(\0020INTEGRATED ABSORPTION FROM\002,i5,\002 T"
							"O\002,i5,\002 CM-1 =\002,f10.2,\002 CM-1\002,/,\002 AVERAGE TRAN"
							"SMITTANCE =\002,f6.4,/)";
	static char fmt_755[] = "(\0020INTEGRATED IRRADIANCE = \002,1pe10.3,\002"
							" WATTS CM-2 \002,/,\002 MINIMUM IRRADIANCE    = \002,e10.3,\002 "
							"WATTS CM-2  (CM-1)-1 \002,\002AT \002,0pf10.1,\002 CM-1\002,/"
							",\002 MAXIMUM IRRADIANCE    = \002,1pe10.3,\002 WATTS CM-2  (CM-"
							"1)-1 \002,\002AT \002,0pf10.1,\002 CM-1\002)";
	static char fmt_750[] = "(\0020INTEGRATED RADIANCE = \002,1pe10.3,\002 W"
							"ATTS CM-2 STER-1\002,/,\002 MINIMUM RADIANCE    = \002,e10.3,"
							"\002 WATTS CM-2 STER-1 (CM-1)-1 \002,\002AT \002,0pf10.1,\002 CM"
							"-1\002,/,\002 MAXIMUM RADIANCE    = \002,1pe10.3,\002 WATTS CM-2"
							" STER-1 (CM-1)-1 \002,\002AT \002,0pf10.1,\002 CM-1\002)";
	static char fmt_760[] = "(\002 BOUNDARY TEMPERATURE = \002,f10.2,\002 "
							"K\002,/,\002 BOUNDARY EMISSIVITY = \002,f11.3)";

	/* System generated locals */
	long i__1, i__2;
	float r__1;
	double d__1;

	/* Builtin functions */
	double exp(double);
	long s_wsfe(cilist *), e_wsfe(void);
	double pow_dd(double *, double *);
	long do_fio(long *, char *, long);
	double cos(double), log(double);

	/* Local variables */
	static long k, n;
	static float v, c0;
	static long n1;
	static float t0, t1, ab;
	static long ib;
	static float cp;
	static long ik, jk, iv;
	static float xd, ss;
	static long ik1;
	static float ct1, ct2;
	static long ml1, iv1, iv2;
	static float w7d, wo3, wt2, fdg, bbg, dmf[34], abt, bet[68], w12d, w13d;
	static long idv;
	static float umf[34], w14d, w16d, ext;
	static long ikm;
	static float asy, sum, sct, rfd, w1o3, w2o3, sms, fh2o;
	static long ikp1;
	extern /* Subroutine */ int hno3_(float *, float *);
	static float xh2o;
	extern /* Subroutine */ int o3uv_(float *, float *);
	static float bbik;
	extern double bbfn_(float *, float *);
	static float alam;
	static long ioff, imap[68];
	static float dmfs[34], cssa;
	static long iiii;
	static float dtau;
	static long dist, ient;
	static float umfs[34];
	static long ikmx, imlt;
	static float suma, rfls;
	static long init;
	static float ssol;
	static long imol;
	static float temp, unif, smss, sums, sumt, sumv;
	extern /* Subroutine */ int c4dta_(float *, float *), c6dta_(float *, float *), c8dta_(float *, float *);
	static long indo3, indo2;
	extern /* Subroutine */ int slf260_(float *, float *), slf296_(float *, float *), frn296_(float *, float *);
	static float altx9;
	extern /* Subroutine */ int fudge_(float *, float *);
	static long indco;
	static float abbuv;
	static long phase;
	extern /* Subroutine */ int cxdta_(float *, float *, long *, long *,
									   float *, long *);
	static float sigo20;
	static long ipath, indno;
	extern /* Subroutine */ int mapms_(long *, long *, float *, float *,
									   long *);
	static float emiss, vrmin, alpha2, vrmax, stsol, train;
	static long indch4, indco2;
	static float tlold, sh2ot0, sh2ot1, vtemp;
	static long indh2o, indnh3;
	static float radfn0, radfn1, sigo2a;
	static long indn2o, indno2;
	static float sigo2b;
	static long indso2;
	extern /* Subroutine */ int o3hht0_(float *, float *), o3hht1_(float *, float *), o2cont_(float *, float *, float *, float *), o3hht2_(float *, float *), abcdta_(long *);
	static float total, summs, tmprn, rain63, asymr, denom;
	extern double dbltx_(float *, float *, float *);
	static float trace;
	extern /* Subroutine */ int ssrad_(long *, long *, long *,
									   long *, float *, float *);
	static float tlnew;
	extern /* Subroutine */ int msrad_(long *, float *, long *, long *, float *, float *, float *, float *, float *, float *);
	static long ikmax1;
	static float cozen, sumvv, sumtt;
	extern double betabs_(float *, float *);
	static float sumss, rflss, rflfac;
	extern /* Subroutine */ int hertda_(float *, float *);
	static float solil, radmin, radmax, soliv, factor, rainav;
	extern /* Subroutine */ int aerext_(float *);
	static long iemiss;
	static float radsum, rflsol;
	static long icount, iscttr;
	static float wcrris, tcrris;
	extern /* Subroutine */ int schrun_(float *, float *);
	static long itzero;
	extern double tnrain_(float *, float *, float *, float *);
	extern /* Subroutine */ int rnscat_(float *, float *, float *, long *,
										long *, long *, float *, float *, long *);
	static float rnexph, traipl;
	static long ikmaxp;
	static float surdtr;
	extern /* Subroutine */ int source_(float *, long *, long *, float *,
										float *);
	static float surdsr, rflsss, tsoliv, tsolil, sumssr, sumsss;

	/* Fortran I/O blocks */
	static cilist io___729 = {0, 0, 0, fmt_931, 0};
	static cilist io___730 = {0, 0, 0, fmt_901, 0};
	static cilist io___731 = {0, 0, 0, fmt_932, 0};
	static cilist io___732 = {0, 0, 0, fmt_932, 0};
	static cilist io___733 = {0, 0, 0, fmt_933, 0};
	static cilist io___734 = {0, 0, 0, fmt_1200, 0};
	static cilist io___735 = {0, 0, 0, fmt_1205, 0};
	static cilist io___753 = {0, 0, 0, fmt_900, 0};
	static cilist io___754 = {0, 0, 0, fmt_910, 0};
	static cilist io___755 = {0, 0, 0, fmt_920, 0};
	static cilist io___756 = {0, 0, 0, fmt_921, 0};
	static cilist io___757 = {0, 0, 0, fmt_930, 0};
	static cilist io___819 = {0, 0, 0, fmt_1210, 0};
	static cilist io___820 = {0, 0, 0, fmt_1220, 0};
	static cilist io___823 = {0, 0, 0, fmt_1230, 0};
	static cilist io___824 = {0, 0, 0, fmt_1220, 0};
	static cilist io___833 = {0, 0, 0, fmt_1230, 0};
	static cilist io___839 = {0, 0, 0, fmt_906, 0};
	static cilist io___840 = {0, 0, 0, fmt_907, 0};
	static cilist io___841 = {0, 0, 0, fmt_907, 0};
	static cilist io___845 = {0, 0, 0, fmt_916, 0};
	static cilist io___846 = {0, 0, 0, fmt_917, 0};
	static cilist io___855 = {0, 0, 0, fmt_926, 0};
	static cilist io___856 = {0, 0, 0, fmt_928, 0};
	static cilist io___857 = {0, 0, 0, fmt_927, 0};
	static cilist io___862 = {0, 0, 0, fmt_936, 0};
	static cilist io___863 = {0, 0, 0, fmt_937, 0};
	static cilist io___865 = {0, 0, 0, fmt_740, 0};
	static cilist io___866 = {0, 0, 0, fmt_755, 0};
	static cilist io___867 = {0, 0, 0, fmt_750, 0};
	static cilist io___868 = {0, 0, 0, fmt_760, 0};

	/* ***********************************************************************TRA  110 */
	/*     CALCULATES TRANSMITTANCE AND RADIANCE VALUES BETWEEN V1 AND V2    TRA  120 */
	/*        FOR A GIVEN ATMOSPHERIC SLANT PATH                             TRA  130 */
	/*                                                                       TRA  140 */
	/*     K                                                                 TRA  150 */
	/*     1-2  TEMP DEP O2  1395 TO 1760                                    TRA  160 */
	/*     3    RAIN                                                         TRA  170 */
	/*     4    N2 CONTINUUM                                                 TRA  180 */
	/*     5    H2O SELF BROADENED CONTINUUM AT 296                          TRA  190 */
	/*     6    MOLECULAR (RAYLIEGH) SCATTERING                              TRA  200 */
	/*     7    BOUNDRY LAYER AEROSOL (0 TO 2 KM)                            TRA  210 */
	/*          (TX(7) IS TOTAL AEROSOL TRANSMITTANCE)                       TRA  220 */
	/*     8    ULTRAVIOLET OZONE                                            TRA  230 */
	/*     9    H2O SELF CONTINUUM 296-260  (TX(9) TOTAL TRANS)              TRA  240 */
	/*    10    H2O FORIGN CONTINUUM                                         TRA  250 */
	/*          (TX(10) IS AEROSOL ABSORPTION)                               TRA  260 */
	/*    11    HNO3 (NITRIC ACID)                                           TRA  270 */
	/*    12    TROPOSPHERIC AEROSOL (2-10 KM)                               TRA  280 */
	/*    13    STRATOSPHERIC  AEROSOL (10-30)                               TRA  290 */
	/*    14    UPPER STRATOPHERIC (ABOVE 30KM)                              TRA  300 */
	/*    15    AEROSOL WEIGHTED RELATIVE HUMITY (0 TO 2 KM)                 TRA  310 */
	/*    16    CIRRUS CLOUDS                                                TRA  320 */
	/*    17-30 H2O (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                TRA  330 */
	/*    31-35 O3  (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                TRA  340 */
	/*    36-43 CO2 (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                TRA  350 */
	/*    44-45 CO  (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                TRA  360 */
	/*    46    CH4 (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                TRA  370 */
	/*    47    N2O (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                TRA  380 */
	/*    50-51 O2  (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                TRA  390 */
	/*    52-53 NH3 (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                TRA  400 */
	/*    54    NO  (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                TRA  410 */
	/*    55    NO2 (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                TRA  420 */
	/*    56-57 SO2 (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                TRA  430 */
	/*    58     O2  UV                                                      TRA  440 */
	/*    59-60  TEMP DEP O3                                                 TRA  450 */
	/*    61-62  TEMP DEP RAIN                                               TRA  460 */
	/*    63     O2  1395 TO 1760                                            TRA  470 */
	/* ***********************************************************************TRA  480 */
	/*                                                                       TRA  490 */
	/*      MODIFIED TO ACCOMODATE MULTIPLE SCATTERING CALCULATION           TRA  500 */
	/*      AS DESCRIBED IN ISAACS ET AL 1986,      A.E.R. INC.              TRA  510 */
	/*                                                                       TRA  520 */
	/* -----------------------------------------------------------------------TRA  530 */
	/*                                                                       TRA  540 */
	/*      MODIFICATIONS TO SET UP EVALUATION OF VERTICAL OPTICAL           TRA  550 */
	/*      QUANTITIES PROFILES (I.E. OPTICAL DEPTH, SINGLE SCATTERING       TRA  560 */
	/*      ALBEDO, ASYMMETRY FACTORS) FOR FLUX ADDING AND MULTIPLE          TRA  570 */
	/*      SCATTERING (MS) SOURCE FUNCTION.                                 TRA  580 */
	/*                                                                       TRA  590 */
	/*      SUBROUTINES MSRAD AND FLXADD ARE CALLED FOR MS.                  TRA  600 */
	/*                                                                       TRA  610 */
	/*                                                                       TRA  620 */
	/*                                                                       TRA  630 */
	/*      'K' LOOPS IN MSRAD AND FLXADD PERFORM K DISTRIBUTION             TRA  640 */
	/*      INTEGRAL OVER K VALUES AND PROBABILITES (SEE ISAACS,             TRA  650 */
	/*      ET AL 1986, P.    )                                              TRA  660 */
	/*                                                                       TRA  670 */
	/*      SUBROUTINE MSRAD:                                                TRA  680 */
	/*         (1) SETS UP OPTICAL PROPERTIES PROFILES FOR VERTICAL          TRA  690 */
	/*             PATH                                                      TRA  700 */
	/*         (2) CALLS FLXADD WHICH RETURNS MS SOURCE FUNCTION, J,         TRA  710 */
	/*             FOR PATH                                                  TRA  720 */
	/*         (3) EVALUATES PATH INTEGRAL OF SOURCE FUNCTION, I.E.          TRA  730 */
	/*             MS RADIANCE CONTRIBUTION                                  TRA  740 */
	/*                                                                       TRA  750 */
	/*      SUBROUTINE    FLXADD:                                            TRA  760 */
	/*         (1) CALCULATES UPWARD, F+ (UPF), AND DOWNWARD, F- (DNF),      TRA  770 */
	/*             FLUX PROFILES USING ADDING METHOD                         TRA  780 */
	/*         (2) MS SOURCE FUNCTION EVALUATED FROM LEVEL FLUXES VIA        TRA  790 */
	/*             STREAM APPROXIMATION (SEE EQN     , ISAACS ET AL, 1986)   TRA  800 */
	/*         (3) BACKSCATTER FOR SOURCE FUNCTION FOR GIVEN G FACTOR        TRA  810 */
	/*             AND ZENTIH ANGLE OBTAINED USING FUNCTION BETABS           TRA  820 */
	/*                                                                       TRA  830 */
	/* ***********************************************************************TRA  840 */
	/*                                                                       TRA  850 */
	/*                                                                       TRA 1060 */
	/*                                                                       TRA 1350 */
	alpha2 = 4e4f;
	if (cntrl_1.imult == 1)
	{
		mapms_(&cntrl_1.ml, &cntrl_1.ikmax, model_1.zm, path_1.aht, imap);
	}
	ioff = 0;
	if (card3_1.h1 >= card3_1.h2)
	{
		ioff = 1;
	}
	if (card3_1.angle > 90.f)
	{
		ioff = 1;
	}
	/*     IF(ITYPE. EQ. 3)IOFF = 1                                          TRA 1410 */
	/*                                                                       TRA 1420 */
	/*                                                                       TRA 1430 */
	/*  SET UP LAYER EDGE AND MIDPOINT TEMPERATURES FOR USE IN               TRA 1440 */
	/*  MS FLUX ADDING                                                       TRA 1450 */
	/*                                                                       TRA 1460 */
	if (cntrl_1.imult == 1)
	{
		i__1 = cntrl_1.ml;
		for (ik = 1; ik <= i__1; ++ik)
		{
			msrd_1.tle[ik - 1] = model_1.tm[cntrl_1.ml - ik];
			if (ik <= mnlt_1.imsmx)
			{
				tran_1.tmd[ik - 1] = mnlt_1.tbbms[ik - 1];
			}
			if (ik > mnlt_1.imsmx)
			{
				tran_1.tmd[ik - 1] = mnlt_1.tbbms[mnlt_1.imsmx - 1];
			}
			/* L50: */
		}
		tran_1.tmd[cntrl_1.ml] = tran_1.tmd[cntrl_1.ml - 1];
		msrd_1.tle[cntrl_1.ml] = msrd_1.tle[cntrl_1.ml - 1];
	}
	radmin = 1e30f;
	radmax = 0.f;
	ient = 0;
	emiss = 1.f - card1_1.salb;
	vrmin = 0.f;
	vrmax = 0.f;
	/*                                                                       TRA 1620 */
	/*  SAVE IKMAX AND IMULT                                                 TRA 1630 */
	/*                                                                       TRA 1640 */
	/*                                                                       TRA 1650 */
	ikmx = cntrl_1.ikmax;
	imlt = cntrl_1.imult;
	suma = 0.f;
	sums = -99.f;
	sumssr = -99.f;
	rfls = -99.f;
	rflsol = -99.f;
	radsum = 0.f;
	stsol = 0.f;
	ssol = 0.f;
	factor = .5f;
	iv1 = card4_1.v1 / 5.f;
	iv2 = card4_1.v2 / 5.f + .99f;
	iv1 *= 5;
	iv2 *= 5;
	if (iv2 > 50000)
	{
		iv2 = 50000;
	}
	if (card4_1.dv < 5.f)
	{
		card4_1.dv = 5.f;
	}
	idv = card4_1.dv;
	iv = iv1 - idv;
	cntrl_1.iklo = 1;
	icount = 0;
	icll_1.icall = 0;
	iemiss = 0;
	iscttr = 0;
	if (card1_1.iemsct == 1 || card1_1.iemsct == 2)
	{
		iemiss = 1;
	}
	if (card1_1.iemsct == 2)
	{
		iscttr = 1;
	}
	wcrris = _BLNK__4.wpath[cntrl_1.ikmax + 1019] * 2.f;
	tcrris = 1.f;
	if (card2_1.icld == 20)
	{
		if (wcrris <= cnstns_1.bigexp)
		{
			tcrris = exp(-wcrris);
		}
		else
		{
			tcrris = 0.f;
		}
	}
	train = 1.f;
	if (iemiss == 0)
	{
		cntrl_1.ikmax = cntrl_1.iklo;
	}
	if (card1_1.iemsct == 0)
	{
		io___729.ciunit = ifil_1.ipu;
		s_wsfe(&io___729);
		e_wsfe();
	}
	/*     IPR1 IS THE LOGICAL UNIT FOR THE MOLECULAR TRANSMITTANCE OUTPUTS  TRA 2090 */
	if (card1_1.iemsct == 0)
	{
		io___730.ciunit = ifil_1.ipr1;
		s_wsfe(&io___730);
		e_wsfe();
	}
	if (card1_1.iemsct == 1)
	{
		io___731.ciunit = ifil_1.ipu;
		s_wsfe(&io___731);
		e_wsfe();
	}
	if (card1_1.iemsct == 2)
	{
		io___732.ciunit = ifil_1.ipu;
		s_wsfe(&io___732);
		e_wsfe();
	}
	if (card1_1.iemsct == 3)
	{
		io___733.ciunit = ifil_1.ipu;
		s_wsfe(&io___733);
		e_wsfe();
	}
	/*                                                                       TRA 2170 */
	if (card1_1.noprt == -1)
	{
		if (cntrl_1.imult == 1)
		{
			io___734.ciunit = ifil_1.ipr1;
			s_wsfe(&io___734);
			e_wsfe();
		}
		else
		{
			if (card1_1.iemsct > 0)
			{
				io___735.ciunit = ifil_1.ipr1;
				s_wsfe(&io___735);
				e_wsfe();
			}
		}
	}
	indh2o = 1;
	indo3 = 1;
	indco2 = 1;
	indco = 1;
	indch4 = 1;
	indn2o = 1;
	indo2 = 1;
	indnh3 = 1;
	indno = 1;
	indno2 = 1;
	indso2 = 1;
/* ******BEGINNING OF FREQUENCY LOOP                                      TRA 2400 */
/*                                                                       TRA 2410 */
L5:
	iv += idv;
	/*                                                                       TRA 2430 */
	/*   INITIALIZE THERMAL AND SOLAR MULTIPLE SCATTERING CONTRIBUTIONS      TRA 2440 */
	/*                                                                       TRA 2450 */
	/*                                                                       TRA 2460 */
	/*   RESET TBBY, WPATH AND WPATHS FOR MULTIPLE SCATTERING                TRA 2470 */
	/*                                                                       TRA 2480 */
	ml1 = cntrl_1.ml - 1;
	init = 0;
	cntrl_1.iklo = 1;
	/*                                                                       TRA 2520 */
	/*  FOR MULTIPLE SCATTERING SET IKMAX=IKMAX+1 DUE TO GROUND LAYER        TRA 2530 */
	/*                                                                       TRA 2540 */
	if (cntrl_1.imult == 1)
	{
		cntrl_1.ikmax = mnlt_1.imsmx;
	}
	else
	{
		/*                                                                       TRA 2580 */
		/*  IF NOT MULTIPLE SCATTERING, RESET IKMAX TO ORIGINAL VALUE            TRA 2590 */
		/*                                                                       TRA 2600 */
		cntrl_1.ikmax = ikmx;
	}
	if (iemiss == 0)
	{
		cntrl_1.ikmax = cntrl_1.iklo;
	}
	/*                                                                       TRA 2660 */
	itzero = 0;
	ipath = 1;
	sumv = 0.f;
	tlold = 1.f;
	if (icount == 0)
	{
		goto L15;
	}
	if (icount == 50)
	{
		goto L15;
	}
	goto L20;
L15:
	icount = 0;
	if (card1_1.iemsct == 0)
	{
		io___753.ciunit = ifil_1.ipr;
		s_wsfe(&io___753);
		e_wsfe();
	}
	if (card1_1.iemsct == 1)
	{
		io___754.ciunit = ifil_1.ipr;
		s_wsfe(&io___754);
		e_wsfe();
	}
	if (card1_1.iemsct == 2 && imlt == 0)
	{
		io___755.ciunit = ifil_1.ipr;
		s_wsfe(&io___755);
		e_wsfe();
	}
	if (card1_1.iemsct == 2 && imlt == 1)
	{
		io___756.ciunit = ifil_1.ipr;
		s_wsfe(&io___756);
		e_wsfe();
	}
	if (card1_1.iemsct == 3)
	{
		io___757.ciunit = ifil_1.ipr;
		s_wsfe(&io___757);
		e_wsfe();
	}
L20:
	i__1 = cntrl_1.kmax;
	for (k = 1; k <= i__1; ++k)
	{
		_BLNK__4.tx[k - 1] = 0.f;
		if (k < 4)
		{
			_BLNK__4.tx[k - 1] = 1.f;
		}
		/* L25: */
	}
	++icount;
	/*                                                                       TRA 2850 */
	v = (float)iv;
	/*                                                                       TRA 2870 */
	/*      VALF,ALF2 AND FAC2 ARE USED TO MODIFY THE H2O CONTINUUM          TRA 2880 */
	/*      AFTER THE CALLS TO SLF296 AND SLF260                             TRA 2890 */
	/*                                                                       TRA 2900 */
	/*     THE ORIGINAL TRANSMITTANCE MODELS FOR H2O, CO2+, O3(IR)           TRA 2910 */
	/*     HAVE BEEN REPLACED.                                               TRA 2920 */
	/*                                                                       TRA 2930 */
	/*     CALL C1DTA (ABB(1),V)                                             TRA 2940 */
	/* *****   UNIFORMLY MIXED GASES                                          TRA 2950 */
	/*     CALL C2DTA (ABB(2),V)                                             TRA 2960 */
	/* *****   OZONE                                                          TRA 2970 */
	/*     CALL C3DTA (ABB(3),V)                                             TRA 2980 */
	/*  ===== STOP OF DELETION  =====                                        TRA 2990 */
	/* *****   N2 CONTINUUM                                                   TRA 3000 */
	/*                                                                       TRA 3010 */
	cxdta_(&cp, &v, wnlohi_1.iwlh2o, wnlohi_1.iwhh2o, h2o_1.cph2o, &indh2o);
	aabbcc_1.cps[0] = cp;
	cxdta_(&cp, &v, wnlohi_1.iwlco2, wnlohi_1.iwhco2, ufmix1_1.cpco2, &indco2);
	aabbcc_1.cps[1] = cp;
	cxdta_(&cp, &v, wnlohi_1.iwlo3, wnlohi_1.iwho3, o3_1.cpo3, &indo3);
	aabbcc_1.cps[2] = cp;
	cxdta_(&cp, &v, wnlohi_1.iwln2o, wnlohi_1.iwhn2o, ufmix2_1.cpn2o, &indn2o);
	aabbcc_1.cps[3] = cp;
	cxdta_(&cp, &v, wnlohi_1.iwlco, wnlohi_1.iwhco, ufmix2_1.cpco, &indco);
	aabbcc_1.cps[4] = cp;
	cxdta_(&cp, &v, wnlohi_1.iwlch4, wnlohi_1.iwhch4, ufmix2_1.cpch4, &indch4);
	aabbcc_1.cps[5] = cp;
	cxdta_(&cp, &v, wnlohi_1.iwlo2, wnlohi_1.iwho2, ufmix2_1.cpo2, &indo2);
	aabbcc_1.cps[6] = cp;
	cxdta_(&cp, &v, wnlohi_1.iwlno, wnlohi_1.iwhno, traceg_1.cpno, &indno);
	aabbcc_1.cps[7] = cp;
	cxdta_(&cp, &v, wnlohi_1.iwlso2, wnlohi_1.iwhso2, traceg_1.cpso2, &indso2);
	aabbcc_1.cps[8] = cp;
	cxdta_(&cp, &v, wnlohi_1.iwlno2, wnlohi_1.iwhno2, traceg_1.cpno2, &indno2);
	aabbcc_1.cps[9] = cp;
	cxdta_(&cp, &v, wnlohi_1.iwlnh3, wnlohi_1.iwhnh3, traceg_1.cpnh3, &indnh3);
	aabbcc_1.cps[10] = cp;
	/*                                                                       TRA 3240 */
	c4dta_(&tran_1.abb[3], &v);
	abcdta_(&iv);
	/*                                                                       TRA 3270 */
	/* *****   WATER CONTINUUM                                                TRA 3280 */
	slf296_(&v, &sh2ot0);
	slf260_(&v, &sh2ot1);
	frn296_(&v, &fh2o);
	t0 = 296.f;
	t1 = 260.f;
	if (sh2ot0 > 0.f)
	{
		/*                                                                       TRA 3350 */
		/*        CORRECTION TO SELF CONTINUUM (1 SEPT 85); FACTOR OF 0.78 @ 1000TRA 3360 */
		/* Computing 2nd power */
		r__1 = v - 1050.f;
		xh2o = 1.f - alpha2 / (r__1 * r__1 + alpha2) * .2333f;
		sh2ot0 *= xh2o;
		sh2ot1 *= xh2o;
	}
	/* *****PROTECT AGAINST EXPONENTIAL UNDERFLOW AT HIGH FREQUENCY           TRA 3410 */
	vtemp = v / .6952f;
	if (vtemp / t1 <= cnstns_1.bigexp)
	{
		xd = exp(-v / (t0 * .6952f));
		radfn0 = v * (1.f - xd) / (xd + 1.f);
		xd = exp(-v / (t1 * .6952f));
		radfn1 = v * (1.f - xd) / (xd + 1.f);
	}
	else
	{
		radfn0 = v;
		radfn1 = v;
	}
	fudge_(&v, &fdg);
	tran_1.abb[4] = sh2ot0 * radfn0;
	c6dta_(&tran_1.abb[5], &v);
	tran_1.abb[6] = 0.f;
	c8dta_(&tran_1.abb[7], &v);
	tran_1.abb[8] = sh2ot1 * radfn1 - sh2ot0 * radfn0;
	tran_1.abb[9] = (fh2o + fdg) * radfn0;
	/* *****HNO3 ABSORPTION CALCULATION                                       TRA 3600 */
	hno3_(&v, &tran_1.abb[10]);
	aerext_(&v);
	/*                                                                       TRA 3630 */
	hertda_(&tran_1.abb[16], &v);
	o2cont_(&v, &sigo20, &sigo2a, &sigo2b);
	if (v > 49600.f)
	{
		schrun_(&v, &aabbcc_1.cps[6]);
	}
	/*                                                                       TRA 3670 */
	/* ********    DIFFUSE OZONE  ********                                    TRA 3680 */
	/*                                                                       TRA 3690 */
	abbuv = 0.f;
	if (v > 24370.f && v < 40800.f)
	{
		tran_1.abb[7] = 0.f;
		o3hht0_(&v, &c0);
		o3hht1_(&v, &ct1);
		o3hht2_(&v, &ct2);
		/*                                                                       TRA 3760 */
	}
	if (v >= 40800.f)
	{
		o3uv_(&v, &c0);
		tran_1.abb[7] = 0.f;
	}
L109:
	srad_1.teb1 = -99.f;
	ipath = 1;
	srad_1.teb2sv = -99.f;
	/* *****                                                                  TRA 3850 */
	/* *****BEGINNING OF LAYER LOOP                                           TRA 3860 */
	total = 1.f;
	msrd_1.dstrn[0] = 1.f;
	/* C    DSTRN(IKMAX) = 1.                                                 TRA 3890 */
	sum = 0.f;
	summs = 0.f;
	i__1 = cntrl_1.ikmax;
	for (ik = cntrl_1.iklo; ik <= i__1; ++ik)
	{
		if (iemiss == 0)
		{
			goto L120;
		}
		if (iscttr == 0)
		{
			goto L116;
		}
	L111:
		/* *****LOAD APPROPRIATE ABSORBER AMOUNTS INTO W(K)                       TRA 3960 */
		if ((i__2 = ipath - 2) < 0)
		{
			goto L112;
		}
		else if (i__2 == 0)
		{
			goto L114;
		}
		else
		{
			goto L116;
		}
	L112:
		/* *****LOAD W(K) WITH WPATHS(1,K) TO OBTAIN THE FIRST                    TRA 3990 */
		/* *****SUN PATH TRANSMITTANCE                                            TRA 4000 */
		i__2 = cntrl_1.kmax;
		for (k = 1; k <= i__2; ++k)
		{
			if (cntrl_1.imult == 1 && init == 0)
			{
				_BLNK__4.w[k - 1] = mnlt_1.wpmss[k * 34 - 34];
			}
			else
			{
				_BLNK__4.w[k - 1] = sols_1.wpaths[k * 68 - 68];
			}
			/* L113: */
		}
		if (_BLNK__4.w[35] >= 0.f)
		{
			goto L120;
		}
		_BLNK__4.tx[5] = 0.f;
		_BLNK__4.tx[6] = 0.f;
		_BLNK__4.tx[8] = 0.f;
		_BLNK__4.tx[9] = 0.f;
		/*            SUN CAN NOT BE SEEN                                        TRA 4130 */
		if (cntrl_1.imult == 1 && init == 0)
		{
			if (ik > 1)
			{
				msrd_1.asyik[ik - 2] = 0.f;
				msrd_1.asydm[ik - 2] = 1.f;
			}
			msrd_1.asyik[cntrl_1.ikmax - 1] = msrd_1.asyik[0];
			msrd_1.asydm[cntrl_1.ikmax - 1] = msrd_1.asydm[0];
			tran_1.dcont[ik - 1] = 0.f;
			msrd_1.dtx7[ik - 1] = 0.f;
			msrd_1.daers[ik - 1] = 0.f;
			msrd_1.dmols[ik - 1] = 0.f;
			goto L1020;
		}
		goto L206;
	L114:
		/* *****LOAD W(K) WITH WPATH(IK,K)+WPATHS(IK+1,K)                         TRA 4290 */
		/* *****TO OBTAIN L PATH TRANSMITTANCES                                   TRA 4300 */
		ikp1 = ik + 1;
		i__2 = cntrl_1.kmax;
		for (k = 1; k <= i__2; ++k)
		{
			/*                                                                       TRA 4330 */
			/*   FOR MULTIPLE SCATTERING, CALCULATE SOLAR PATH ONLY TO FIND          TRA 4340 */
			/*   THE SOLAR PATH TRANSMITTANCE                                        TRA 4350 */
			/*                                                                       TRA 4360 */
			if (cntrl_1.imult == 1 && init == 0)
			{
				_BLNK__4.w[k - 1] = mnlt_1.wpmss[ikp1 + k * 34 - 35];
			}
			else
			{
				_BLNK__4.w[k - 1] = _BLNK__4.wpath[ik + k * 68 - 69] +
									sols_1.wpaths[ikp1 + k * 68 - 69];
			}
			/* L115: */
		}
		/*                                                                       TRA 4430 */
		/*   FOR MULTIPLE SCATTERING, CALCULATE SOLAR PATH ONLY TO FIND          TRA 4440 */
		/*   THE SOLAR PATH TRANSMITTANCE                                        TRA 4450 */
		/*                                                                       TRA 4460 */
		if (cntrl_1.imult == 1 && init == 0)
		{
			if (mnlt_1.wpmss[ikp1 + 1189] > 0.f)
			{
				goto L120;
			}
			_BLNK__4.tx[5] = 0.f;
			_BLNK__4.tx[6] = 0.f;
			_BLNK__4.tx[8] = 0.f;
			_BLNK__4.tx[9] = 0.f;
			if (ik > 1)
			{
				msrd_1.asyik[ik - 2] = 0.f;
				msrd_1.asydm[ik - 2] = 1.f;
			}
			msrd_1.asyik[cntrl_1.ikmax - 1] = msrd_1.asyik[0];
			msrd_1.asydm[cntrl_1.ikmax - 1] = msrd_1.asydm[0];
			tran_1.dcont[ik - 1] = 0.f;
			msrd_1.dtx7[ik - 1] = 0.f;
			msrd_1.daers[ik - 1] = 0.f;
			msrd_1.dmols[ik - 1] = 0.f;
			goto L1020;
		}
		if (sols_1.wpaths[ikp1 + 2379] >= 0.f)
		{
			goto L120;
		}
		_BLNK__4.tx[5] = 0.f;
		_BLNK__4.tx[6] = 0.f;
		_BLNK__4.tx[8] = 0.f;
		_BLNK__4.tx[9] = 0.f;
		/*            SUN CAN NOT BE SEEN                                        TRA 4700 */
		goto L206;
	L116:
		/* *****LOAD W(K) WITH WPATH(IK,K) TO OBTAIN THE OPTICAL                  TRA 4730 */
		/* *****PATH TRANSMITTANCES                                               TRA 4740 */
		i__2 = cntrl_1.kmax;
		for (k = 1; k <= i__2; ++k)
		{
			if (cntrl_1.imult == 1 && init == 0)
			{
				/*                                                                       TRA 4770 */
				/*     MPSM AMOUNTS FROM 0 TO SPACE A 0 DEG                              TRA 4780 */
				/*                                                                       TRA 4790 */
				_BLNK__4.w[k - 1] = mnlt_1.wpms[ik + k * 34 - 35];
				/*                                                                       TRA 4810 */
			}
			else
			{
				/*                                                                       TRA 4830 */
				/*          WPATHS IS VEW PATH                                           TRA 4840 */
				/*                                                                       TRA 4850 */
				_BLNK__4.w[k - 1] = _BLNK__4.wpath[ik + k * 68 - 69];
				/*                                                                       TRA 4870 */
			}
			/* L117: */
		}
	L120:
		for (k = 3; k <= 16; ++k)
		{
			/* L121: */
			_BLNK__4.tx[k - 1] = 0.f;
		}
		/*                                                                       TRA 4930 */
		ext = aer_1.xx1 * _BLNK__4.w[6] + aer_1.xx2 * _BLNK__4.w[11] +
			  aer_1.xx3 * _BLNK__4.w[12] + aer_1.xx4 * _BLNK__4.w[13] +
			  aer_1.xx5 * _BLNK__4.w[15];
		abt = aer_1.yy1 * _BLNK__4.w[6] + aer_1.yy2 * _BLNK__4.w[11] +
			  aer_1.yy3 * _BLNK__4.w[12] + aer_1.yy4 * _BLNK__4.w[13] +
			  aer_1.yy5 * _BLNK__4.w[15];
		if (cntrl_1.imult == 1 && init == 0)
		{
			if (ik == 1)
			{
				w7d = mnlt_1.wpms[ik + 203];
				w12d = mnlt_1.wpms[ik + 373];
				w13d = mnlt_1.wpms[ik + 407];
				w14d = mnlt_1.wpms[ik + 441];
				w16d = mnlt_1.wpms[ik + 509];
			}
			else
			{
				ikm = ik - 1;
				w7d = mnlt_1.wpms[ik + 203] - mnlt_1.wpms[ikm + 203];
				w12d = mnlt_1.wpms[ik + 373] - mnlt_1.wpms[ikm + 373];
				w13d = mnlt_1.wpms[ik + 407] - mnlt_1.wpms[ikm + 407];
				w14d = mnlt_1.wpms[ik + 441] - mnlt_1.wpms[ikm + 441];
				w16d = mnlt_1.wpms[ik + 509] - mnlt_1.wpms[ikm + 509];
			}
			/*                                                                       TRA 5110 */
			/*  ASYMMETRY FACTOR IS WEIGHTED AVERAGE                                 TRA 5120 */
			/*                                                                       TRA 5140 */
			asy = aer_1.zz1 * (aer_1.xx1 - aer_1.yy1) * w7d + aer_1.zz2 * (aer_1.xx2 - aer_1.yy2) * w12d + aer_1.zz3 * (aer_1.xx3 - aer_1.yy3) * w13d + aer_1.zz4 * (aer_1.xx4 - aer_1.yy4) * w14d + aer_1.zz5 * (aer_1.xx5 - aer_1.yy5) * w16d;
		}
		/*                                                                       TRA 5180 */
		sct = ext - abt;
		train = 1.f;
		/* CC                                                                     TRA 5210 */
		/* CC   ADD CONTRIBUTION OF CLOUDS AND RAIN                               TRA 5220 */
		/* CC                                                                     TRA 5230 */
		if (_BLNK__4.w[2] != 0.f)
		{
			tmprn = _BLNK__4.w[60] / _BLNK__4.w[2];
			xd = exp(-v / (tmprn * .6952f));
			rfd = v * (1.f - xd) / (xd + 1.f);
			rain63 = _BLNK__4.w[2] / _BLNK__4.w[61];
			d__1 = (double)rain63;
			rainav = pow_dd(&d__1, &c_b1423);
			train = tnrain_(&rainav, &v, &tmprn, &rfd);
			if (v < 250.f)
			{
				if (card2_1.icld <= 11)
				{
					phase = 1;
				}
				if (card2_1.icld > 11)
				{
					phase = 2;
				}
				dist = 1;
				/*                                                                       TRA 5350 */
				/*       CALL SCATTERING ROUTINE TO OBTAIN ASYMMTRY FACTOR AND RATIO     TRA 5360 */
				/*       OF ABSORPTION TO EXTINCTION DUE TO RAIN WITHIN RANGE OF         TRA 5370 */
				/*       19 TO 231 GHZ                                                   TRA 5380 */
				/*       EXTRAPOLATE ABOVE AND BELOW THAT FREQ RANGE                     TRA 5390 */
				/*                                                                       TRA 5400 */
				rnscat_(&v, &rainav, &tmprn, &phase, &dist, &ik1, &cssa, &asymr, &ient);
				++ient;
			}
			else
			{
				cssa = .5f;
				asymr = .85f;
			}
			rnexph = train * _BLNK__4.w[61];
			abt += rnexph * cssa;
			sct += rnexph * (1.f - cssa);
			if (cntrl_1.imult == 1 && init == 0)
			{
				traipl = rnexph;
				asy += asymr * (1.f - cssa) * traipl;
			}
		}
		/* L130: */
		/*                                                                       TRA 5570 */
		/*    SET EXT DUE TO RAIN FOR LAYER                                      TRA 5580 */
		/*                                                                       TRA 5590 */
		/*                                                                       TRA 5600 */
		/*                                                                       TRA 5610 */
		if (cntrl_1.imult == 1 && init == 0)
		{
			denom = (aer_1.xx1 - aer_1.yy1) * w7d + (aer_1.xx2 - aer_1.yy2) * w12d + (aer_1.xx3 - aer_1.yy3) * w13d + (aer_1.xx4 - aer_1.yy4) * w14d + (aer_1.xx5 - aer_1.yy5) * w16d;
			if (_BLNK__4.w[2] != 0.f)
			{
				denom += (1.f - cssa) * traipl;
			}
			/*                                                                       TRA 5650 */
			if (ik > 1)
			{
				msrd_1.asyik[ik - 2] = asy;
				msrd_1.asydm[ik - 2] = denom;
			}
			msrd_1.asyik[cntrl_1.ikmax - 1] = msrd_1.asyik[0];
			msrd_1.asydm[cntrl_1.ikmax - 1] = msrd_1.asydm[0];
		}
		/*                                                                       TRA 5730 */
		ext = sct + abt;
		/*                                                                       TRA 5750 */
		sum = 0.f;
		wo3 = _BLNK__4.w[7] * .269f;
		if (v > 24370.f && v < 40800.f)
		{
			w1o3 = _BLNK__4.w[58];
			w2o3 = _BLNK__4.w[59];
			/* CC        COZ   = C0  *(1.+ CT1  *TC+CT2   *TC*TC)                     TRA 5810 */
			abbuv = c0 * (wo3 + ct1 * w1o3 + ct2 * w2o3);
		}
		if (v >= 40800.f)
		{
			abbuv = c0 * wo3;
		}
		sum += abbuv;
		for (jk = 4; jk <= 11; ++jk)
		{
			_BLNK__4.tx[jk - 1] = tran_1.abb[jk - 1] * _BLNK__4.w[jk - 1];
			if (jk == 5)
			{
				_BLNK__4.tx[4] = tran_1.abb[4] * (_BLNK__4.w[4] * 1e-20f);
			}
			if (jk == 9)
			{
				_BLNK__4.tx[8] = tran_1.abb[8] * (_BLNK__4.w[8] * 1e-20f);
			}
			if (jk == 10)
			{
				_BLNK__4.tx[9] = tran_1.abb[9] * (_BLNK__4.w[9] * 1e-20f);
			}
			/* L125: */
			sum += _BLNK__4.tx[jk - 1];
		}
		/*                                                                       TRA 5940 */
		/*  CONTINUUM OPTICAL THICKNESS (CUMULATIVE)                             TRA 5950 */
		/*                                                                       TRA 5960 */
		_BLNK__4.tx[7] += abbuv;
		if (cntrl_1.imult == 1 && init == 0)
		{
			tran_1.dcont[ik - 1] = _BLNK__4.tx[3] + _BLNK__4.tx[4] +
								   _BLNK__4.tx[7] + _BLNK__4.tx[8] + _BLNK__4.tx[9] +
								   _BLNK__4.tx[10];
		}
		_BLNK__4.tx[4] = _BLNK__4.tx[4] + _BLNK__4.tx[9] + _BLNK__4.tx[8];
		/*                                                                       TRA 6000 */
		/*  STORE CUMULATIVE AEROSOL PARAMETERS FOR DIFFERENT VERTICAL REGIONS   TRA 6010 */
		/*                                                                       TRA 6020 */
		_BLNK__4.tx[9] = abt;
		_BLNK__4.tx[6] = ext;
		/*                                                                       TRA 6050 */
		/*  WATCH OUT FOR NUMBERING OF LAYERS--BOTTOM=LAYER 1 IN LOWTRAN         TRA 6060 */
		/*                                                                       TRA 6070 */
		/*   STORE CUMULATIVE AEROSOL EXTINCTION AND SCATTERING OPTICAL          TRA 6080 */
		/*   THICKNESS AND MOLECULAR SCATTERING OPTICAL THICKNESS                TRA 6090 */
		/*                                                                       TRA 6100 */
		if (cntrl_1.imult == 1 && init == 0)
		{
			msrd_1.dtx7[ik - 1] = _BLNK__4.tx[6];
			msrd_1.daers[ik - 1] = _BLNK__4.tx[6] - _BLNK__4.tx[9];
			msrd_1.dmols[ik - 1] = _BLNK__4.tx[5];
		}
		sum += _BLNK__4.tx[6];
		if (card2_1.icld == 20)
		{
			_BLNK__4.tx[15] = _BLNK__4.w[15] * 2.f;
			sum += _BLNK__4.tx[15];
		}
		/* ***********************************************************************TRA 6190 */
		/*                                                                       TRA 6200 */
		/*                                                                       TRA 6210 */
		/*     OXYGEN                                                            TRA 6220 */
		/*                                                                       TRA 6230 */
		wt2 = _BLNK__4.w[0] - _BLNK__4.w[62] * 220.f;
		_BLNK__4.tx[57] = sigo20 * (_BLNK__4.w[62] + sigo2a * wt2 + sigo2b * _BLNK__4.w[1]);
		/*                                                                       TRA 6260 */
		/*  UV O2 HERZBERG CONTINUUM ABSORPTION CALCULATION                      TRA 6270 */
		/*                                                                       TRA 6280 */
		_BLNK__4.tx[57] = _BLNK__4.w[57] * tran_1.abb[16] + _BLNK__4.tx[57];
		if (cntrl_1.imult == 1 && init == 0)
		{
			tran_1.dcont[ik - 1] += _BLNK__4.tx[57];
		}
		/* CC   SUM=SUM+TX(58)                                                    TRA*6310 */
		_BLNK__4.tx[2] = _BLNK__4.tx[57];
		/*                                                                       TRA 6330 */
		/* ***********************************************************************TRA 6340 */
		_BLNK__4.tx[8] = sum;
		for (k = 3; k <= 16; ++k)
		{
			/* C    IF (TX(K).GT.20.0  ) TX(K)=20.0                                   TRA 6370 */
			/* C    IF (TX(K).LT.-20.0 ) TX(K)=-20.0                                  TRA 6380 */
			if (_BLNK__4.tx[k - 1] > cnstns_1.bigexp)
			{
				goto L200;
			}
			_BLNK__4.tx[k - 1] = exp(-_BLNK__4.tx[k - 1]);
			goto L205;
		L200:
			_BLNK__4.tx[k - 1] = 1.f / cnstns_1.bignum;
		L205:;
		}
		_BLNK__4.tx[57] = _BLNK__4.tx[2];
		_BLNK__4.tx[2] = 1.f;
		/*  ---H2O                                                               TRA 6430 */
		/*                                                                       TRA 6440 */
		imol = 1;
		temp = 1.f;
		cp = aabbcc_1.cps[imol - 1];
		if (cp == -20.f)
		{
			goto L1001;
		}
		ib = aabbcc_1.ibnd[imol - 1];
		temp = dbltx_(&_BLNK__4.w[ib - 1], &cp, &aabbcc_1.a[imol - 1]);
	L1001:
		_BLNK__4.tx[16] = temp;
		/*  ---CO2                                                               TRA 6520 */
		/*                                                                       TRA 6530 */
		imol = 2;
		temp = 1.f;
		cp = aabbcc_1.cps[imol - 1];
		if (cp == -20.f)
		{
			goto L1002;
		}
		ib = aabbcc_1.ibnd[imol - 1];
		temp = dbltx_(&_BLNK__4.w[ib - 1], &cp, &aabbcc_1.a[imol - 1]);
	L1002:
		_BLNK__4.tx[35] = temp;
		/*  ---O3                                                                TRA 6610 */
		/*                                                                       TRA 6620 */
		imol = 3;
		temp = 1.f;
		cp = aabbcc_1.cps[imol - 1];
		if (cp == -20.f)
		{
			goto L1003;
		}
		ib = aabbcc_1.ibnd[imol - 1];
		temp = dbltx_(&_BLNK__4.w[ib - 1], &cp, &aabbcc_1.a[imol - 1]);
	L1003:
		_BLNK__4.tx[30] = temp;
		/*  ---N2O                                                               TRA 6700 */
		/*                                                                       TRA 6710 */
		imol = 4;
		temp = 1.f;
		cp = aabbcc_1.cps[imol - 1];
		if (cp == -20.f)
		{
			goto L1004;
		}
		ib = aabbcc_1.ibnd[imol - 1];
		temp = dbltx_(&_BLNK__4.w[ib - 1], &cp, &aabbcc_1.a[imol - 1]);
	L1004:
		_BLNK__4.tx[46] = temp;
		/*  ---CO                                                                TRA 6790 */
		/*                                                                       TRA 6800 */
		imol = 5;
		temp = 1.f;
		cp = aabbcc_1.cps[imol - 1];
		if (cp == -20.f)
		{
			goto L1005;
		}
		ib = aabbcc_1.ibnd[imol - 1];
		temp = dbltx_(&_BLNK__4.w[ib - 1], &cp, &aabbcc_1.a[imol - 1]);
	L1005:
		_BLNK__4.tx[43] = temp;
		/*  ---CH4                                                               TRA 6880 */
		/*                                                                       TRA 6890 */
		imol = 6;
		temp = 1.f;
		cp = aabbcc_1.cps[imol - 1];
		if (cp == -20.f)
		{
			goto L1006;
		}
		ib = aabbcc_1.ibnd[imol - 1];
		temp = dbltx_(&_BLNK__4.w[ib - 1], &cp, &aabbcc_1.a[imol - 1]);
	L1006:
		_BLNK__4.tx[45] = temp;
		/*  ---O2                                                                TRA 6970 */
		/*                                                                       TRA 6980 */
		imol = 7;
		temp = 1.f;
		cp = aabbcc_1.cps[imol - 1];
		if (cp == -20.f)
		{
			goto L1007;
		}
		ib = aabbcc_1.ibnd[imol - 1];
		temp = dbltx_(&_BLNK__4.w[ib - 1], &cp, &aabbcc_1.a[imol - 1]);
	L1007:
		_BLNK__4.tx[49] = temp;
		/*  ---NO                                                                TRA 7060 */
		/*                                                                       TRA 7070 */
		imol = 8;
		temp = 1.f;
		cp = aabbcc_1.cps[imol - 1];
		if (cp == -20.f)
		{
			goto L1008;
		}
		ib = aabbcc_1.ibnd[imol - 1];
		temp = dbltx_(&_BLNK__4.w[ib - 1], &cp, &aabbcc_1.a[imol - 1]);
	L1008:
		_BLNK__4.tx[53] = temp;
		/*  ---SO2                                                               TRA 7150 */
		/*                                                                       TRA 7160 */
		imol = 9;
		temp = 1.f;
		cp = aabbcc_1.cps[imol - 1];
		if (cp == -20.f)
		{
			goto L1009;
		}
		ib = aabbcc_1.ibnd[imol - 1];
		temp = dbltx_(&_BLNK__4.w[ib - 1], &cp, &aabbcc_1.a[imol - 1]);
	L1009:
		_BLNK__4.tx[55] = temp;
		/*  ---NO2                                                               TRA 7240 */
		/*                                                                       TRA 7250 */
		imol = 10;
		temp = 1.f;
		cp = aabbcc_1.cps[imol - 1];
		if (cp == -20.f)
		{
			goto L1010;
		}
		ib = aabbcc_1.ibnd[imol - 1];
		temp = dbltx_(&_BLNK__4.w[ib - 1], &cp, &aabbcc_1.a[imol - 1]);
	L1010:
		_BLNK__4.tx[54] = temp;
		/*  ---NH3                                                               TRA 7330 */
		/*                                                                       TRA 7340 */
		imol = 11;
		temp = 1.f;
		cp = aabbcc_1.cps[imol - 1];
		if (cp == -20.f)
		{
			goto L1011;
		}
		ib = aabbcc_1.ibnd[imol - 1];
		temp = dbltx_(&_BLNK__4.w[ib - 1], &cp, &aabbcc_1.a[imol - 1]);
	L1011:
		_BLNK__4.tx[51] = temp;
		/*     UNIF = UNIFORMLY MIXED GASES TRANSMITTANCE (DOUBLE EXPONENTIAL)   TRA 7420 */
		/*     TRACE = TRACE GASES TRANSMITTANCE (DOUBLE EXPONENTIAL MODELS)     TRA 7430 */
		unif = _BLNK__4.tx[35] * _BLNK__4.tx[43] * _BLNK__4.tx[45] *
			   _BLNK__4.tx[46] * _BLNK__4.tx[49] * _BLNK__4.tx[57];
		trace = _BLNK__4.tx[51] * _BLNK__4.tx[53] * _BLNK__4.tx[54] *
				_BLNK__4.tx[55];
		_BLNK__4.tx[8] = _BLNK__4.tx[16] * unif * _BLNK__4.tx[30] *
						 _BLNK__4.tx[8] * trace;
		if (iv >= 13000)
		{
			_BLNK__4.tx[30] = _BLNK__4.tx[7];
		}
	/*                                                                       TRA 7480 */
	/*  SAVE TX(9) FROM PREVIOUS PASS, WHICH IS TOTAL TRANSMITTANCE          TRA 7490 */
	/*  FOR ENTIRE ATMOSPHERIC PATH                                          TRA 7500 */
	/*                                                                       TRA 7510 */
	L1020:
		if (ipath == 1)
		{
			msrd_1.dstrn[0] = _BLNK__4.tx[8];
		}
		if (cntrl_1.imult == 1 && init == 0)
		{
			if (ipath == 2)
			{
				msrd_1.dstrn[ik] = _BLNK__4.tx[8];
			}
			if (card1_1.iemsct == 1)
			{
				msrd_1.dstrn[ik] = 1.f;
			}
		}
		/*                                                                       TRA 7550 */
		/*   DSTRN IS CUMULATIVE SOLAR TRANSMISSTION, USED IN CALCULATION        TRA 7560 */
		/*   OF SOLAR TRANSMISSION TO LAYER N                                    TRA 7570 */
		/*                                                                       TRA 7580 */
		/*                                                                       TRA 7590 */
		/*  IF THERMAL CASE ONLY, INITIALIZE STRN                                TRA 7600 */
		/*  STRN IS SOLAR TRANSMISSIVITY TO NTH LAYER FROM TOP OF ATM            TRA 7610 */
		/*                                                                       TRA 7620 */
		/*                                                                       TRA 7630 */
		/*   INITIALIZE OMEGA0 FOR NO MULTIPLE SCATTERING CASES                  TRA 7640 */
		/*                                                                       TRA 7650 */
		/* CC   IF(IMULT .EQ. 0) THEN                                             TRA*7660 */
		/* CC   IF(IK. LE. ML)OMEGA0(IK)=0.0                                      TRA*7670 */
		/* CC   ENDIF                                                             TRA*7680 */
		if (iscttr == 0)
		{
			goto L209;
		}
		if (cntrl_1.imult == 1 && init == 0)
		{
			goto L207;
		}
	L206:
		/*     TEST AGAINST ML1 INSERTED  FOR ERRATA TO WORK                     TRA 7720 */
		if (ik <= ml1 && cntrl_1.imult == 1)
		{
			ssrad_(iph, &ik, &itzero, &ipath, &v, &sumssr);
		}
		if (cntrl_1.imult == 0)
		{
			ssrad_(iph, &ik, &itzero, &ipath, &v, &sumssr);
		}
	L207:
		if (ipath == 3)
		{
			goto L208;
		}
		++ipath;
		goto L111;
	L208:
		ipath = 2;
	L209:
		if (iv >= 13000)
		{
			_BLNK__4.tx[2] = _BLNK__4.tx[7];
		}
		/*     TO AVOID THE DIFFICULTY FOR WAVENUMBER BEING ZERO                 TRA 7810 */
		alam = 9999.998f;
		if (v > 0.f)
		{
			alam = 1e4f / v;
		}
		if (card1_1.iemsct == 0 || card1_1.iemsct == 3)
		{
			goto L220;
		}
		/*                                                                       TRA 7850 */
		/*   FOR NO MULTIPLE SCATTERING, CALCULATE BLACK BODY FUNCTION,          TRA 7860 */
		/*   AS WELL AS RADIANCE ADDING FOR THERMAL                              TRA 7870 */
		/*                                                                       TRA 7880 */
		bbik = bbfn_(&_BLNK__4.tbby[ik - 1], &v);
		/*     TLNEW=(TX(9)*TX(10))/(TX(7)*TX(6))                                TRA 7900 */
		/*     TSNEW=(TX(7)*TX(6))/TX(10)                                        TRA 7910 */
		tlnew = _BLNK__4.tx[8];
		dtau = tlold - tlnew;
		if (cntrl_1.imult == 1)
		{
			dtau = total - _BLNK__4.tx[8];
		}
		total = _BLNK__4.tx[8];
		if (dtau <= 0.f)
		{
			dtau = 0.f;
		}
		if (cntrl_1.imult == 0)
		{
			if (card1_1.noprt == -1)
			{
				io___819.ciunit = ifil_1.ipr1;
				s_wsfe(&io___819);
				do_fio(&c__1, (char *)&v, (long)sizeof(float));
				do_fio(&c__1, (char *)&path_1.aht[ik - 1], (long)sizeof(float));
				do_fio(&c__1, (char *)&path_1.aht[ik], (long)sizeof(float));
				do_fio(&c__1, (char *)&bbik, (long)sizeof(float));
				do_fio(&c__1, (char *)&dtau, (long)sizeof(float));
				do_fio(&c__1, (char *)&tlnew, (long)sizeof(float));
				e_wsfe();
			}
			if (card1_1.iemsct < 2 && dtau < 1e-5f && tlnew < 1e-5f)
			{
				if (card1_1.noprt == -1)
				{
					io___820.ciunit = ifil_1.ipr1;
					s_wsfe(&io___820);
					e_wsfe();
				}
				goto L220;
			}
			sumv += bbik * dtau;
			/*     RADIANCE / CONSERVATIVE SCATTERING                                TRA 8080 */
		}
		else
		{
			if (init == 0)
			{
				goto L210;
			}
			n1 = cntrl_1.ml - imap[ik - 1] + ioff;
			if (n1 >= cntrl_1.ml)
			{
				n1 = cntrl_1.ml - 1;
			}
			if (card1_1.noprt == -1)
			{
				n = n1 + 1;
				io___823.ciunit = ifil_1.ipr1;
				s_wsfe(&io___823);
				do_fio(&c__1, (char *)&v, (long)sizeof(float));
				do_fio(&c__1, (char *)&path_1.aht[ik], (long)sizeof(float));
				do_fio(&c__1, (char *)&dirst_1.umb[n - 1], (long)sizeof(float));
				do_fio(&c__1, (char *)&dirst_1.umbs[n - 1], (long)sizeof(float));
				do_fio(&c__1, (char *)&dirst_1.dmb[n - 1], (long)sizeof(float));
				do_fio(&c__1, (char *)&dirst_1.dmbs[n - 1], (long)sizeof(float));
				r__1 = dirst_1.sun * _BLNK__4.tx[8];
				do_fio(&c__1, (char *)&r__1, (long)sizeof(float));
				do_fio(&c__1, (char *)&_BLNK__4.tx[8], (long)sizeof(float));
				e_wsfe();
			}
			if (dtau < 1e-5f && _BLNK__4.tx[8] < 1e-5f)
			{
				if (card1_1.noprt == -1)
				{
					io___824.ciunit = ifil_1.ipr1;
					s_wsfe(&io___824);
					e_wsfe();
				}
				goto L220;
			}
			if (path_1.qtheta[ik - 1] < cnstns_1.pi / 2.f)
			{
				/*     UP                                                                TRA 8230 */
				/*                                                                       TRA 8240 */
				/*   SU & SD ARE THERMAL UPWARD & DOWNWARD SOURCE FUNCTIONS              TRA 8250 */
				/*   SUS & SDS ARE SOLAR UPWARD & DOWNWARD SOURCE FUNCTIONS              TRA 8260 */
				/*                                                                       TRA 8270 */
				sms = bbik * (1.f - msrd_1.omega0[n1 - 1]) + msrd_1.omega0[n1 - 1] / cnstns_1.pi * (dmf[n1 - 1] * (1.f - bet[ik - 1]) + umf[n1 - 1] * bet[ik - 1]);
				smss = msrd_1.omega0[n1 - 1] / cnstns_1.pi * (dmfs[n1 - 1] * (1.f - bet[ik - 1]) + umfs[n1 - 1] * bet[ik - 1]);
			}
			else
			{
				/*     DOWN                                                              TRA 8330 */
				sms = bbik * (1.f - msrd_1.omega0[n1 - 1]) + msrd_1.omega0[n1 - 1] / cnstns_1.pi * (umf[n1 - 1] * (1.f - bet[ik - 1]) + dmf[n1 - 1] * bet[ik - 1]);
				smss = msrd_1.omega0[n1 - 1] / cnstns_1.pi * (umfs[n1 - 1] * (1.f - bet[ik - 1]) + dmfs[n1 - 1] * bet[ik - 1]);
			}
			sumv += sms * dtau;
			summs += smss * dtau;
		}
		tlold = tlnew;
	L210:;
	}
/* *****END OF LAYER LOOP                                                 TRA 8440 */
L220:
	/*                                                                       TRA 8460 */
	/*   THE FOLLOWING ROUTINE IS CALLED FOR MULTIPLE SCATTERING CASES ONLY  TRA 8470 */
	/*                                                                       TRA 8480 */
	/*   MSRAD RETURNS SOLAR AND THERMAL CONTRIBUTIONS TO RADIANCE           TRA 8490 */
	/*   AND THERMAL (FDNTRT) DIFFUSE FLUX FOR SURFACE REFLECTION.           TRA 8500 */
	/*   (THESE QUANTITIES IN COMMON /MSRD/)                                 TRA 8510 */
	/*                                                                       TRA 8520 */
	if (cntrl_1.imult == 0)
	{
		goto L266;
	}
	if (init != 0)
	{
		goto L266;
	}
	msrad_(&iv, &v, isourc, iday, anglem, &ss, dmf, dmfs, umf, umfs);
	/*                                                                       TRA 8570 */
	if (card1_1.noprt == -1)
	{
		io___833.ciunit = ifil_1.ipr1;
		s_wsfe(&io___833);
		do_fio(&c__1, (char *)&v, (long)sizeof(float));
		do_fio(&c__1, (char *)&path_1.aht[0], (long)sizeof(float));
		do_fio(&c__1, (char *)&dirst_1.umb[0], (long)sizeof(float));
		do_fio(&c__1, (char *)&dirst_1.umbs[0], (long)sizeof(float));
		do_fio(&c__1, (char *)&dirst_1.dmb[0], (long)sizeof(float));
		do_fio(&c__1, (char *)&dirst_1.dmbs[0], (long)sizeof(float));
		do_fio(&c__1, (char *)&dirst_1.sun, (long)sizeof(float));
		do_fio(&c__1, (char *)&c_b1471, (long)sizeof(float));
		e_wsfe();
	}
	/*                                                                       TRA 8630 */
	/*   GO BACK AND CALCULATE RADIANCE FOR NON-MULTIPLE SCATTERING CASE     TRA 8640 */
	/*                                                                       TRA 8650 */
	/*                                                                       TRA 8660 */
	/*     IKMAX AND IKMAXP NEED BE DEFINED FOR VEW TO SPACE                 TRA 8670 */
	/*                                                                       TRA 8680 */
	ikmax1 = cntrl_1.ikmax - 1;
	ikmaxp = cntrl_1.ikmax + 1;
	msrd_1.cosbar[cntrl_1.ikmax - 1] = msrd_1.cosbar[ikmax1 - 1];
	msrd_1.omega0[cntrl_1.ikmax - 1] = msrd_1.omega0[ikmax1 - 1];
	umf[cntrl_1.ikmax - 1] = umf[ikmax1 - 1];
	umfs[cntrl_1.ikmax - 1] = umfs[ikmax1 - 1];
	dmfs[cntrl_1.ikmax - 1] = dmfs[ikmax1 - 1];
	msrd_1.cosbar[ikmaxp - 1] = msrd_1.cosbar[ikmax1 - 1];
	msrd_1.omega0[ikmaxp - 1] = msrd_1.omega0[ikmax1 - 1];
	umf[ikmaxp - 1] = umf[ikmax1 - 1];
	umfs[ikmaxp - 1] = umfs[ikmax1 - 1];
	dmfs[ikmaxp - 1] = dmfs[ikmax1 - 1];
	/*                                                                       TRA 8810 */
	cntrl_1.ikmax = ikmx;
	++init;
	i__1 = cntrl_1.ikmax;
	for (ik = 1; ik <= i__1; ++ik)
	{
		n = cntrl_1.ml - imap[ik - 1] + ioff;
		/*                                                                       TRA 8860 */
		/*   BET(N)     - BACKSCATTER FRACTION ALONG OPTICAL PATH AT LAYER N     TRA 8870 */
		/*                                                                       TRA 8880 */
		cozen = (r__1 = cos(path_1.qtheta[ik - 1]), dabs(r__1));
		/*                                                                       TRA 8900 */
		/*    CALCULATE BACKSCATTER PARAMETERS                                   TRA 8910 */
		/*                                                                       TRA 8920 */
		if (msrd_1.cosbar[n - 1] == 0.f)
		{
			bet[ik - 1] = .5f;
		}
		else
		{
			bet[ik - 1] = betabs_(&cozen, &msrd_1.cosbar[n - 1]);
		}
		/* L60: */
	}
	bet[cntrl_1.ikmax] = .5f;
	/*                                                                       TRA 9000 */
	goto L109;
L266:
	if (iv > iv1)
	{
		factor = 1.f;
	}
	if (iv >= iv2)
	{
		factor = .5f;
	}
	suma += factor * card4_1.dv * (1.f - _BLNK__4.tx[8]);
	iiii = card1_1.iemsct + 1;
	altx9 = cnstns_1.bignum;
	if (_BLNK__4.tx[8] > 0.f)
	{
		altx9 = -log(_BLNK__4.tx[8]);
	}
	switch (iiii)
	{
	case 1:
		goto L300;
	case 2:
		goto L400;
	case 3:
		goto L400;
	case 4:
		goto L600;
	}
L300:
	/* *****TRANSMITTANCE ONLY                                                TRA 9110 */
	_BLNK__4.tx[9] = 1.f - _BLNK__4.tx[9];
	_BLNK__4.tx[6] *= _BLNK__4.tx[15];

	// interested in v and _BLNK__4.tx
	*(resultData + resultDataLen * 2) = alam;
	*(resultData + resultDataLen++ * 2 + 1) = _BLNK__4.tx[8];

	io___839.ciunit = ifil_1.ipr;
	s_wsfe(&io___839);
	do_fio(&c__1, (char *)&v, (long)sizeof(float));
	do_fio(&c__1, (char *)&alam, (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[8], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[16], (long)sizeof(float));
	do_fio(&c__1, (char *)&unif, (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[30], (long)sizeof(float));
	do_fio(&c__1, (char *)&trace, (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[3], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[4], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[5], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[6], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[10], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[9], (long)sizeof(float));
	do_fio(&c__1, (char *)&suma, (long)sizeof(float));
	e_wsfe();
	_BLNK__4.tx[49] *= _BLNK__4.tx[57];
	io___840.ciunit = ifil_1.ipr1;
	s_wsfe(&io___840);
	do_fio(&c__1, (char *)&v, (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[16], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[30], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[35], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[43], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[45], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[46], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[49], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[51], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[53], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[54], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[55], (long)sizeof(float));
	e_wsfe();
	io___841.ciunit = ifil_1.ipu;
	s_wsfe(&io___841);
	do_fio(&c__1, (char *)&v, (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[8], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[16], (long)sizeof(float));
	do_fio(&c__1, (char *)&unif, (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[30], (long)sizeof(float));
	do_fio(&c__1, (char *)&trace, (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[3], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[4], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[5], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[6], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[10], (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[9], (long)sizeof(float));
	do_fio(&c__1, (char *)&altx9, (long)sizeof(float));
	e_wsfe();
	goto L700;
L400:
	/* *****ATMOSPHERIC RADIANCE ONLY                                         TRA 9240 */
	/* *****INCLUDE EMISSION OF BOUNDARY ATTENUATED BY TOTAL TRANSMISSION     TRA 9250 */
	/*                                                                       TRA 9260 */
	/*    CALCULATE THERMAL RADIANCE CONTRIBUTION OF BOUNDARY                TRA 9270 */
	/*                                                                       TRA 9280 */
	/*    SURDTR IS THE SCATTERED CONTRIBUTION TO THE THERMAL RADIANCE       TRA 9290 */
	/*    BUT IS ONLY ADDED IF THE PATH INTERSECTS THE SURFACE               TRA 9300 */
	/*                                                                       TRA 9310 */
	/*                                                                       TRA 9320 */
	surdtr = 0.f;
	if (imlt == 1 && card3_1.h2 == 0.f)
	{
		surdtr = card1_1.salb * msrd_1.fdntrt * _BLNK__4.tx[8] / cnstns_1.pi;
	}
	if (card1_1.tbound <= 0.f)
	{
		bbg = 0.f;
	}
	else
	{
		bbg = bbfn_(&card1_1.tbound, &v) * _BLNK__4.tx[8] * emiss + surdtr;
	}
	/*                                                                       TRA 9420 */
	/*   ADD THERMAL BOUNDARY AND MULTIPLE SCATTERED RADIANCE                TRA 9430 */
	/*                                                                       TRA 9440 */
	sumv += bbg;
	sumvv = sumv;
	if (v > 0.f)
	{
		/* Computing 2nd power */
		r__1 = v;
		sumv = 1e4f / (r__1 * r__1) * sumv;
	}
	if (card1_1.iemsct == 2)
	{
		goto L500;
	}
	radsum += card4_1.dv * factor * sumv;
	io___845.ciunit = ifil_1.ipr;
	s_wsfe(&io___845);
	do_fio(&c__1, (char *)&v, (long)sizeof(float));
	do_fio(&c__1, (char *)&alam, (long)sizeof(float));
	do_fio(&c__1, (char *)&sumv, (long)sizeof(float));
	do_fio(&c__1, (char *)&sumvv, (long)sizeof(float));
	do_fio(&c__1, (char *)&radsum, (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[8], (long)sizeof(float));
	e_wsfe();
	io___846.ciunit = ifil_1.ipu;
	s_wsfe(&io___846);
	do_fio(&c__1, (char *)&v, (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[8], (long)sizeof(float));
	do_fio(&c__1, (char *)&sumv, (long)sizeof(float));
	do_fio(&c__1, (char *)&altx9, (long)sizeof(float));
	e_wsfe();
	sumt = sumv;
	sumtt = sumvv;
	goto L700;
L500:
	/* *****SOLAR SCATTERED RADIANCE                                          TRA 9570 */
	/* *****MULTIPLY SUMSSR BY THE EXTRATERRESTRIAL SOURCE STRENGTH SS        TRA 9580 */
	source_(&v, isourc, iday, anglem, &ss);
	/*                                                                       TRA 9600 */
	/*   CALCULATE TOTAL SINGLE SCATTERED + MULTIPLE SCATTERED SOLAR         TRA 9610 */
	/*   RADIANCE FOR EACH FREQUENCY                                         TRA 9620 */
	/*                                                                       TRA 9630 */
	sumsss = sumssr * ss;
	sumssr = sumsss + summs;
	/* *****SUMSSR IS THE SCATTERED RADIANCE IN (W/CM2-STER-MICROMETER)       TRA 9660 */
	sums = 0.f;
	sumss = 0.f;
	if (v > 0.f)
	{
		/* Computing 2nd power */
		r__1 = v;
		sums = 1e4f / (r__1 * r__1) * sumssr;
	}
	if (v > 0.f)
	{
		/* Computing 2nd power */
		r__1 = v;
		sumsss = 1e4f / (r__1 * r__1) * sumsss;
	}
	/* *****RFLSOL IS GROUND-REFLECTED DIRECT SOURCE RADIANCE                 TRA 9690 */
	rflsol = 0.f;
	rfls = 0.f;
	rflss = 0.f;
	/*                                                                       TRA 9730 */
	/*   SURDSR IS SURFACE REFLECTION OF DOWNWARD SCATTERED RADIANCE         TRA 9740 */
	/*                                                                       TRA 9750 */
	surdsr = 0.f;
	if (card3_1.h2 > model_1.zm[0])
	{
		goto L510;
	}
	if (srad_1.teb1 <= 0.f)
	{
		goto L510;
	}
	if (sols_1.angsun >= 0.f)
	{
		rflfac = card1_1.salb * cos(sols_1.angsun * cnstns_1.ca) /
				 cnstns_1.pi;
	}
	/*                                                                       TRA 9800 */
	/*     FOR MULTIPLE SCATTERING CASES:                                    TRA 9810 */
	/*                                                                       TRA 9820 */
	if (imlt == 1)
	{
		surdsr = card1_1.salb * msrd_1.fdnsrt * _BLNK__4.tx[8] / cnstns_1.pi;
	}
	rflsss = rflfac * srad_1.teb1 * ss;
	rflsol = rflsss + surdsr;
	rfls = 0.f;
	rflss = 0.f;
	if (v > 0.f)
	{
		/* Computing 2nd power */
		r__1 = v;
		rfls = 1e4f / (r__1 * r__1) * rflsol;
	}
	if (v > 0.f)
	{
		/* Computing 2nd power */
		r__1 = v;
		rflss = 1e4f / (r__1 * r__1) * rflsss;
	}
L510:
	sumt = sumv + sums + rfls;
	sumtt = sumvv + sumssr + rflsol;
	radsum += card4_1.dv * factor * sumt;
	if (imlt != 1)
	{
		io___855.ciunit = ifil_1.ipr;
		s_wsfe(&io___855);
		do_fio(&c__1, (char *)&v, (long)sizeof(float));
		do_fio(&c__1, (char *)&alam, (long)sizeof(float));
		do_fio(&c__1, (char *)&sumv, (long)sizeof(float));
		do_fio(&c__1, (char *)&sumvv, (long)sizeof(float));
		do_fio(&c__1, (char *)&sums, (long)sizeof(float));
		do_fio(&c__1, (char *)&sumssr, (long)sizeof(float));
		do_fio(&c__1, (char *)&rfls, (long)sizeof(float));
		do_fio(&c__1, (char *)&rflsol, (long)sizeof(float));
		do_fio(&c__1, (char *)&sumt, (long)sizeof(float));
		do_fio(&c__1, (char *)&sumtt, (long)sizeof(float));
		do_fio(&c__1, (char *)&radsum, (long)sizeof(float));
		do_fio(&c__1, (char *)&_BLNK__4.tx[8], (long)sizeof(float));
		e_wsfe();
	}
	else
	{
		io___856.ciunit = ifil_1.ipr;
		s_wsfe(&io___856);
		do_fio(&c__1, (char *)&v, (long)sizeof(float));
		do_fio(&c__1, (char *)&alam, (long)sizeof(float));
		do_fio(&c__1, (char *)&sumv, (long)sizeof(float));
		do_fio(&c__1, (char *)&sumvv, (long)sizeof(float));
		do_fio(&c__1, (char *)&sums, (long)sizeof(float));
		do_fio(&c__1, (char *)&sumssr, (long)sizeof(float));
		do_fio(&c__1, (char *)&sumsss, (long)sizeof(float));
		do_fio(&c__1, (char *)&rfls, (long)sizeof(float));
		do_fio(&c__1, (char *)&rflsol, (long)sizeof(float));
		do_fio(&c__1, (char *)&rflss, (long)sizeof(float));
		do_fio(&c__1, (char *)&sumt, (long)sizeof(float));
		do_fio(&c__1, (char *)&sumtt, (long)sizeof(float));
		do_fio(&c__1, (char *)&radsum, (long)sizeof(float));
		do_fio(&c__1, (char *)&_BLNK__4.tx[8], (long)sizeof(float));
		e_wsfe();
	}
	io___857.ciunit = ifil_1.ipu;
	s_wsfe(&io___857);
	do_fio(&c__1, (char *)&v, (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[8], (long)sizeof(float));
	do_fio(&c__1, (char *)&sumv, (long)sizeof(float));
	do_fio(&c__1, (char *)&sums, (long)sizeof(float));
	do_fio(&c__1, (char *)&sumsss, (long)sizeof(float));
	do_fio(&c__1, (char *)&rfls, (long)sizeof(float));
	do_fio(&c__1, (char *)&rflss, (long)sizeof(float));
	do_fio(&c__1, (char *)&sumt, (long)sizeof(float));
	do_fio(&c__1, (char *)&srad_1.teb1, (long)sizeof(float));
	do_fio(&c__1, (char *)&srad_1.teb2sv, (long)sizeof(float));
	do_fio(&c__1, (char *)&altx9, (long)sizeof(float));
	e_wsfe();
	goto L700;
L600:
	/* *****DIRECTLY TRANSMITTED SOLAR IRRADIANCE                             TRA10060 */
	/* *****SOLIL IS SOLAR IRRADIANCE IN WATTS/(CM2 MICROMETER)               TRA10070 */
	source_(&v, isourc, iday, anglem, &solil);
	soliv = 0.f;
	if (v > 0.f)
	{
		/* Computing 2nd power */
		r__1 = v;
		soliv = solil * 1e4f / (r__1 * r__1);
	}
	tsoliv = soliv * _BLNK__4.tx[8];
	tsolil = solil * _BLNK__4.tx[8];
	stsol += tsoliv * card4_1.dv * factor;
	ssol += soliv * card4_1.dv * factor;
	io___862.ciunit = ifil_1.ipr;
	s_wsfe(&io___862);
	do_fio(&c__1, (char *)&v, (long)sizeof(float));
	do_fio(&c__1, (char *)&alam, (long)sizeof(float));
	do_fio(&c__1, (char *)&tsoliv, (long)sizeof(float));
	do_fio(&c__1, (char *)&tsolil, (long)sizeof(float));
	do_fio(&c__1, (char *)&soliv, (long)sizeof(float));
	do_fio(&c__1, (char *)&solil, (long)sizeof(float));
	do_fio(&c__1, (char *)&stsol, (long)sizeof(float));
	do_fio(&c__1, (char *)&ssol, (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[8], (long)sizeof(float));
	e_wsfe();
	io___863.ciunit = ifil_1.ipu;
	s_wsfe(&io___863);
	do_fio(&c__1, (char *)&v, (long)sizeof(float));
	do_fio(&c__1, (char *)&_BLNK__4.tx[8], (long)sizeof(float));
	do_fio(&c__1, (char *)&tsoliv, (long)sizeof(float));
	do_fio(&c__1, (char *)&soliv, (long)sizeof(float));
	do_fio(&c__1, (char *)&altx9, (long)sizeof(float));
	e_wsfe();
	sumt = tsoliv;
	radsum = stsol;
/* *****                                                                  TRA10190 */
L700:
	if (card1_1.iemsct == 0)
	{
		goto L710;
	}
	if (sumt >= radmax)
	{
		vrmax = v;
	}
	if (sumt >= radmax)
	{
		radmax = sumt;
	}
	if (sumt <= radmin)
	{
		vrmin = v;
	}
	if (sumt <= radmin)
	{
		radmin = sumt;
	}
L710:
	cntrl_1.imult = imlt;
	if (iv < iv2)
	{
		goto L5;
	}
	/* *****END OF FREQUENCY LOOP                                             TRA10290 */
	ab = 1.f - suma / (float)(iv - iv1);
	io___865.ciunit = ifil_1.ipr;
	s_wsfe(&io___865);
	do_fio(&c__1, (char *)&iv1, (long)sizeof(long));
	do_fio(&c__1, (char *)&iv, (long)sizeof(long));
	do_fio(&c__1, (char *)&suma, (long)sizeof(float));
	do_fio(&c__1, (char *)&ab, (long)sizeof(float));
	e_wsfe();
	if (card1_1.iemsct == 0)
	{
		goto L770;
	}
	if (card1_1.iemsct == 3)
	{
		io___866.ciunit = ifil_1.ipr;
		s_wsfe(&io___866);
		do_fio(&c__1, (char *)&radsum, (long)sizeof(float));
		do_fio(&c__1, (char *)&radmin, (long)sizeof(float));
		do_fio(&c__1, (char *)&vrmin, (long)sizeof(float));
		do_fio(&c__1, (char *)&radmax, (long)sizeof(float));
		do_fio(&c__1, (char *)&vrmax, (long)sizeof(float));
		e_wsfe();
	}
	else
	{
		io___867.ciunit = ifil_1.ipr;
		s_wsfe(&io___867);
		do_fio(&c__1, (char *)&radsum, (long)sizeof(float));
		do_fio(&c__1, (char *)&radmin, (long)sizeof(float));
		do_fio(&c__1, (char *)&vrmin, (long)sizeof(float));
		do_fio(&c__1, (char *)&radmax, (long)sizeof(float));
		do_fio(&c__1, (char *)&vrmax, (long)sizeof(float));
		e_wsfe();
		io___868.ciunit = ifil_1.ipr;
		s_wsfe(&io___868);
		do_fio(&c__1, (char *)&card1_1.tbound, (long)sizeof(float));
		do_fio(&c__1, (char *)&emiss, (long)sizeof(float));
		e_wsfe();
	}
L770:

	return 0;
	/* *****                                                                  TRA10380 */
	/* *****FORMAT STATEMENTS FOR SPECTRAL DATA                               TRA10390 */
	/* *****PAGE HEADERS                                                      TRA10400 */
	/* *****SPECTRAL DATA TO UNIT=IPR (=6)                                    TRA10750 */
	/* *****SPECTRAL DATA TO UNIT=IPU (=7)                                    TRA10810 */
	/* *****SUMMARY VALUES                                                    TRA10820 */
	/* L720: */
} /* trans_ */

/* Subroutine */ int fudge_(float *v, float *sumy)
{
	/* Builtin functions */
	double log(double), exp(double);

	/* Local variables */
	static float ya, yb, yainv, ybinv;

	/*                                                                       FDG* 110 */
	/*     TO CALCULATE H2O FAR WING CONTINUUM USING THE SUMS OF EXPONENTIALSFDG* 120 */
	/*                                                                       FDG* 130 */
	/*     THIS FUNCTION IS WITHIN 5% OF THE ORIGINAL "FUDGE" BETWEEN 0 AND  FDG* 140 */
	/*     3000CM-1, PRESERVING THAT VALIDATION.                             FDG* 150 */
	/*     THE NEW FUNCTION IS 0.01 OF THE ORIGINAL NEAR 10000CM-1 (1.06NM), FDG* 160 */
	/*     IN ACCORDANCE WITH THE MEASUREMENTS OF JAYCOR, FUNDED BY SDIO.    FDG* 170 */
	/*                                                                       FDG* 180 */
	/*     Y0(V)=EXP(ALOG(3.159E-8)-(2.75E-4)*V)                             FDG* 190 */
	/*                                                                       FDG* 220 */
	/*     YO=Y0(V)                                                          FDG* 230 */
	ya = exp(log(3.2379749999999996e-8f) - 2.75e-4f * *v);
	yb = exp(log(8.97e-6f) - .0013f * *v);
	yainv = 1 / ya;
	ybinv = 1 / yb;
	*sumy = 1.f / (yainv * 1.f + ybinv * 1.f);
	return 0;
} /* fudge_ */

double andex_(float *h__, float *sh, float *gamma)
{
	/* System generated locals */
	float ret_val;

	/* Builtin functions */
	double exp(double);

	/* Local variables */
	static float hsh;

	/* ***********************************************************************FAN  110 */
	/*     COMPUTES THE INDEX OF REFRACTION AT HEIGHT H, SH IS THE           FAN  120 */
	/*     SCALE HEIGHT, GAMMA IS THE VALUE AT H=0 OF THE REFRACTIVITY =     FAN  130 */
	/*     INDEX-1                                                           FAN  140 */
	/* ***********************************************************************FAN  150 */
	if (*sh == 0.f)
	{
		goto L10;
	}
	if (*h__ <= 0.f)
	{
		goto L10;
	}
	hsh = *h__ / *sh;
	if (hsh > cnstns_1.bigexp)
	{
		goto L20;
	}
	ret_val = *gamma * exp(-hsh) + 1.f;
	return ret_val;
L10:
	ret_val = *gamma + 1.f;
	return ret_val;
L20:
	ret_val = 1.f;
	return ret_val;
} /* andex_ */

double tnrain_(float *rr, float *v, float *tm, float *radfld)
{
	/* Initialized data */

	static float nzero = 8e3f;

	/* System generated locals */
	float ret_val, r__1;
	double d__1;

	/* Builtin functions */
	double pow_dd(double *, double *);

	/* Local variables */
	static float a;
	extern double gmrain_(float *, float *, float *);

	/* CC                                                                     TNR  110 */
	/* CC   CALCULATES TRANSMISSION DUE TO RAIN AS A FUNCTION OF              TNR  140 */
	/* CC   RR=RAIN RATE IN MM/HR                                             TNR  150 */
	/* CC   OR WITHIN 350CM-1 USES THE MICROWAVE TABLE ROUTINE TO             TNR  160 */
	/* CC   OBTAIN THE EXTINCTION DUE TO RAIN                                 TNR  170 */
	/* CC   RANGE=SLANT RANGE KM                                              TNR  180 */
	/* CC                                                                     TNR  190 */
	/* CC   ASSUMES A MARSHALL-PALMER RAIN DROP SIZE DISTRIBUTION             TNR  200 */
	/* CC   N(D)=NZERO*EXP(-A*D)                                              TNR  210 */
	/* CC   NZERO=8.E3 (MM-1)  (M-3)                                          TNR  220 */
	/* CC   A=41.*RR**(-0.21)                                                 TNR  230 */
	/* CC   D=DROP DIAMETER (CM)                                              TNR  240 */
	/* CC                                                                     TNR  250 */
	/* CC                                                                     TNR  280 */
	d__1 = (double)(*rr);
	a = 41.f / pow_dd(&d__1, &c_b1631);
	/* CC                                                                     TNR  300 */
	if (*rr <= 0.f)
	{
		ret_val = 1.f;
	}
	if (*rr <= 0.f)
	{
		return ret_val;
	}
	/* CC                                                                     TNR  330 */
	if (*v >= 350.f)
	{
		/* Computing 3rd power */
		r__1 = a;
		ret_val = cnstns_1.pi * nzero / (r__1 * (r__1 * r__1));
	}
	else
	{
		ret_val = gmrain_(v, tm, rr);
		ret_val *= *radfld;
	}
	return ret_val;
} /* tnrain_ */

/* Subroutine */ int rnscat_(float *v, float *r__, float *tt, long *phase,
							 long *dist, long *ik, float *cssa, float *asymr, long *ient)
{
	/* Initialized data */

	static long nf = 9;
	static long nt = 3;
	static long nsc = 4;
	static long maxi = 3;
	static float tk = 273.15f;
	static float cmt0 = 1.f;
	static float c7500 = .5f;
	static float g0 = 0.f;
	static float g7500 = .85f;
	static float temp[3] = {-10.f, 0.f, 10.f};
	static float fr[9] = {19.35f, 37.f, 50.3f, 89.5f, 100.f, 118.f, 130.f, 183.f,
						  231.f};

	/* Format strings */
	static char fmt_801[] = "(2x,\002***  THE ASYMMETRY PARAMETER DUE TO RAI"
							"N IS BASED ON\002,\002DATA BETWEEN 19 AND 231 GHZ\002,/2x,\002**"
							"*  EXTRAPOLATION IS USED FOR FREQUENCIES LOWER AND\002,\002HIGHE"
							"R THAN THIS RANGE\002)";
	static char fmt_802[] = "(2x,\002***  TEMPERATURE RANGE OF DATA IS -10 T"
							"O +10 \002,\002DEGREES CELSIUS\002,/2x,\002***  BEYOND THESE VAL"
							"UES IT IS \002,\002TREATED AS IF AT THE EXTREMES\002)";
	static char fmt_803[] = "(2x,\002***  RAIN RATES BETWEEN 0 AND 50 MM/HR "
							"ARE\002,\002WITHIN THIS DATA RANGE\002,/2x,\002***  ABOVE THAT T"
							"HE ASYMMETRY\002,\002 PARAMETER IS CALCULATED FOR 50 MM/HR\002)";

	/* System generated locals */
	long i__1, i__2, i__3, i__4, i__5;
	double d__1;

	/* Builtin functions */
	long s_wsfe(cilist *), e_wsfe(void);
	double pow_dd(double *, double *);

	/* Local variables */
	static float f;
	static long i__, j, k;
	static float t, s1, s2, s3, s4, al, am, cl, cm, fl, fm, sc[12] /*
		was [3][4] */
		;
	static long ki;
	extern /* Subroutine */ int bs_(long *, float *, float *, long *,
									float *);
	static float sf, wc, st;
	extern double tab_(long *, long *, long *, float *);
	static long isc, int__;
	static float fdif, aamt, camt, fsav, atot, ctot, rsav, ftot, tsav;
	static long nopr;

	/* Fortran I/O blocks */
	static cilist io___898 = {0, 6, 0, fmt_801, 0};
	static cilist io___899 = {0, 6, 0, fmt_801, 0};
	static cilist io___900 = {0, 6, 0, fmt_802, 0};
	static cilist io___901 = {0, 6, 0, fmt_802, 0};
	static cilist io___902 = {0, 6, 0, fmt_803, 0};

	/* ********************************************************************** RNS  110 */
	/*                                                                       RNS  140 */
	/*          ARGUMENTS:                                                   RNS  150 */
	/*                                                                       RNS  160 */
	/*          F = FREQUENCY (GHZ)                                          RNS  170 */
	/*          R = RAINFALL RATE (MM/HR)                                    RNS  180 */
	/*          T = TEMPERATURE (DEGREES CELSIUS)                            RNS  190 */
	/*          PHASE = PHASE PARAMETER (1=WATER, 2=ICE)                     RNS  200 */
	/*          DIST = DROP SIZE DISTRIBUTION PARAMETER                      RNS  210 */
	/*                     (1=MARSHALL-PALMER, 2=BEST)                       RNS  220 */
	/*                                                                       RNS  230 */
	/*          RESULTS:                                                     RNS  240 */
	/*                                                                       RNS  250 */
	/*          SC(1) = ABSORPTION COEFFICIENT (1/KM)                        RNS  260 */
	/*          SC(2) = EXTINCTION COEFFICIENT (1/KM)                        RNS  270 */
	/*          SC(I),I=3,NSC = LEGENDRE COEFFICIENTS #I-3  (NSC=10)         RNS  280 */
	/*          ERR = ERROR RETURN CODE: 0=NO ERROR, 1=BAD FREQUENCY,        RNS  290 */
	/*                2=BAD RAINFALL RATE, 3=BAD TEMPERATURE,                RNS  300 */
	/*                4=BAD PHASE PARAMETER, 5=BAD DROP SIZE DISTRIBUTION    RNS  310 */
	/*                                                                       RNS  320 */
	/*          THE INTERNAL DATA:                                           RNS  330 */
	/*                                                                       RNS  340 */
	/*                                                                       RNS  360 */
	/*          FR(I),I=1,NF = TABULATED FREQUENCIES (GHZ)  (NF=9)           RNS  370 */
	/*          TEMP(I),I=1,NT = TABULATED TEMPERATURES  (NT=3)              RNS  380 */
	/*                                                                       RNS  390 */
	/*          THE BLOCK-DATA SECTION                                       RNS  400 */
	/*                                                                       RNS  410 */
	/*                                                                       RNS  460 */
	/*      THIS SUBROUTINE REQUIRES FREQUENCIES IN GHZ                      RNS  470 */
	nopr = 0;
	if (*ik == 1)
	{
		nopr = 1;
	}
	if (*ient > 1)
	{
		nopr = 0;
	}
	f = *v * 29.97925f;
	fsav = f;
	rsav = *r__;
	tsav = t;
	int__ = 0;
	/*      CONVERT TEMP TO DEGREES CELSIUS                                  RNS  560 */
	t = *tt - tk;
	/*      FREQ RANGE OF DATA 19.35-231 GHZ IF LESS THAN 19.35              RNS  580 */
	/*      SET UP PARAMETERS FOR INTERPOLATION                              RNS  590 */
	if (f < fr[0])
	{
		fl = 0.f;
		fm = fr[0];
		int__ = 1;
		if (nopr > 0)
		{
			s_wsfe(&io___898);
			e_wsfe();
		}
	}
	/*      IF MORE THAN 231 GHZ SET UP PARAMETERS FOR EXTRAPOLATION         RNS  660 */
	if (f > fr[nf - 1])
	{
		fl = fr[nf - 1];
		fm = 7500.f;
		int__ = 2;
		if (nopr > 0)
		{
			s_wsfe(&io___899);
			e_wsfe();
		}
	}
	/*      TEMP RANGE OF DATA IS -10 TO +10 DEGREES CELCIUS                 RNS  730 */
	/*      IF BELOW OR ABOVE EXTREME SET AND DO CALCULATIONS AT EXTREME     RNS  740 */
	if (t < temp[0])
	{
		t = temp[0];
		if (nopr > 0)
		{
			s_wsfe(&io___900);
			e_wsfe();
		}
	}
	/*                                                                       RNS  790 */
	if (t > temp[2])
	{
		t = temp[2];
		if (nopr > 0)
		{
			s_wsfe(&io___901);
			e_wsfe();
		}
	}
	/*                                                                       RNS  840 */
	/*      RAIN RATE OF DATA IS FOR 0-50 MM/HR                              RNS  850 */
	/*      IF GT 50 TREAT CALCULATIONS AS IF 50 MM/HR WAS INPUT             RNS  860 */
	if (*r__ > 50.f)
	{
		*r__ = 50.f;
		if (nopr > 0)
		{
			s_wsfe(&io___902);
			e_wsfe();
		}
	}
	/*                                                                       RNS  910 */
	ki = 1;
/*             FIGURE OUT THE SECOND INDEX                               RNS  930 */
L10:
	j = *phase + (*dist << 1);
	/*                                                                       RNS  950 */
	/*                                                                       RNS  960 */
	/*             GET THE TEMPERATURE INTERPOLATION PARAMETER ST            RNS  970 */
	/*             IF NEEDED AND AMEND THE SECOND INDEX                      RNS  980 */
	bs_(&j, &t, temp, &nt, &st);
	/*                                                                       RNS 1000 */
	/*             FIGURE OUT THE THIRD INDEX AND THE FREQUENCY INTERPOLATIONRNS 1010 */
	/*             PARAMETER SF                                              RNS 1020 */
	bs_(&k, &f, fr, &nf, &sf);
	/*                                                                       RNS 1040 */
	/*             INITIALIZE SC                                             RNS 1050 */
	i__1 = nsc;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		sc[ki + i__ * 3 - 4] = 0.f;
		/* L11: */
	}
	sc[ki + 5] = 1.f;
	/*                                                                       RNS 1100 */
	/*             NOW DO THE CALCULATIONS                                   RNS 1110 */
	/*                                                                       RNS 1120 */
	/*             THE WATER CONTENT IS                                      RNS 1130 */
	if (*dist == 1)
	{
		d__1 = (double)(*r__);
		wc = pow_dd(&d__1, &c_b1641) * .0889f;
	}
	else
	{
		d__1 = (double)(*r__);
		wc = pow_dd(&d__1, &c_b1642) * .067f;
	}
	/*                                                                       RNS 1190 */
	/*             FOR A TEMPERATURE DEPENDENT CASE, I.E.                    RNS 1200 */
	if (j < 3)
	{
		s1 = (1.f - sf) * (1.f - st);
		s2 = (1.f - sf) * st;
		s3 = sf * (1.f - st);
		s4 = sf * st;
		i__1 = maxi;
		for (i__ = 1; i__ <= i__1; ++i__)
		{
			if (i__ <= 2)
			{
				isc = i__;
			}
			else
			{
				isc = i__ + 1;
			}
			i__2 = j + 1;
			i__3 = k + 1;
			i__4 = j + 1;
			i__5 = k + 1;
			sc[ki + isc * 3 - 4] = s1 * tab_(&i__, &j, &k, &wc) + s2 * tab_(&i__, &i__2, &k, &wc) + s3 * tab_(&i__, &j, &i__3, &wc) +
								   s4 * tab_(&i__, &i__4, &i__5, &wc);
			/* L14: */
		}
		/*                                                                       RNS 1350 */
		/*             FOR A TEMPERATURE INDEPENDENT CASE                        RNS 1360 */
	}
	else
	{
		s1 = 1.f - sf;
		s2 = sf;
		i__1 = maxi;
		for (i__ = 1; i__ <= i__1; ++i__)
		{
			if (i__ <= 2)
			{
				isc = i__;
			}
			else
			{
				isc = i__ + 1;
			}
			i__2 = k + 1;
			sc[ki + isc * 3 - 4] = s1 * tab_(&i__, &j, &k, &wc) + s2 * tab_(&i__, &j, &i__2, &wc);
			/* L17: */
		}
	}
	f = fsav;
	if (int__ == 3)
	{
		goto L20;
	}
	if (int__ == 4)
	{
		goto L30;
	}
	if (int__ == 0)
	{
		*cssa = sc[ki - 1] / sc[ki + 2];
		if (*cssa > 1.f)
		{
			*cssa = 1.f;
		}
		*asymr = sc[ki + 8] / 3.f;
		f = fsav;
		*r__ = rsav;
		t = tsav;
		return 0;
	}
	if (int__ == 1)
	{
		int__ = 3;
		f = fm;
		ki = 2;
	}
	if (int__ == 2)
	{
		int__ = 4;
		f = fl;
		ki = 3;
	}
	goto L10;
L20:
	fdif = fm - f;
	ftot = fm - fl;
	cm = sc[ki - 1] / sc[ki + 2];
	if (cm > 1.f)
	{
		cm = 1.f;
	}
	cl = cmt0;
	am = sc[ki + 8] / 3.f;
	al = g0;
	goto L40;
L30:
	fdif = fm - f;
	ftot = fm - fl;
	cm = c7500;
	cl = sc[ki - 1] / sc[ki + 2];
	if (cl > 1.f)
	{
		cl = 1.f;
	}
	am = g7500;
	al = sc[ki + 8] / 3.f;
L40:
	ctot = cm - cl;
	camt = fdif * ctot / ftot;
	*cssa = cm - camt;
	atot = am - al;
	aamt = fdif * atot / ftot;
	*asymr = am - aamt;
	f = fsav;
	*r__ = rsav;
	t = tsav;
	return 0;
} /* rnscat_ */

/* Subroutine */ int bs_(long *i__, float *a, float *b, long *n, float *s)
{
	static long j, m;

	/* ********************************************************************** BS   110 */
	/*                                                                       BS   130 */
	/*             THIS SUBROUTINE DOES THE BINARY SEARCH FOR THE INDEX I    BS   140 */
	/*             SUCH THAT A IS IN BETWEEN B(I) AND B(I+1)                 BS   150 */
	/*             AND CALCULATES THE INTERPOLATION PARAMETER S              BS   160 */
	/*             SUCH THAT A=S*B(I+1)+(1.-S)*B(I)                          BS   170 */
	/*                                                                       BS   180 */
	/* Parameter adjustments */
	--b;

	/* Function Body */
	*i__ = 1;
	j = *n;
L10:
	m = (*i__ + j) / 2;
	if (*a <= b[m])
	{
		j = m;
	}
	else
	{
		*i__ = m;
	}
	if (j > *i__ + 1)
	{
		goto L10;
	}
	*s = (*a - b[*i__]) / (b[*i__ + 1] - b[*i__]);
	return 0;
} /* bs_ */

double tab_(long *i__, long *j, long *k, float *wc)
{
	/* Initialized data */

	static long maxi[54] /* was [6][9] */ = {6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7,
											 7, 7, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
											 9, 9, 9, 9, 9, 9, 9, 9, 9};
	static float a1[5] = {.611f, .655f, .958f, .538f, 1.58f};
	static float a2[5] = {-.807f, -.772f, -1.f, -.696f, -1.5f};
	static float alpha1[5] = {1.18f, 1.08f, .99f, 1.27f, 1.02f};
	static float a[486] /* was [9][6][9] */ = {.284f, .363f, 0.f, .4908f, .035f,
											   .002f, 0.f, 0.0, 0.0, .285f, .365f, 0.f, .487f, .035f, .00205f, 0.f, 0.0, 0.0,
											   .294f, .375f, 0.f, .482f, .035f, .00208f, 0.f, 0.0, 0.0, .001336f, .0148f,
											   .3147f, .528f, .047f, .00285f, 0.f, 0.0, 0.0, .36f, .528f, 0.f, .478f,
											   .0482f, .0037f, 2.1e-4f, 0.0, 0.0, .00146f, .0317f, .438f, .538f, .0647f,
											   .0048f, 1.6e-4f, 0.0, 0.0, .8f, 1.28f, .254f, .5f, .0965f, .0234f, .0037f,
											   0.0, 0.0, .77f, 1.27f, .172f, .486f, .0936f, .0228f, .0037f, 0.0, 0.0, .73f,
											   1.24f, 0.f, .4706f, .09f, .0221f, .0035f, 0.0, 0.0, .00344f, .162f, .93f,
											   .69f, .159f, .034f, .005f, 0.0, 0.0, .76f, 1.43f, .32f, .481f, .151f, .057f,
											   .011f, 0.0, 0.0, .0043f, .332f, 1.29f, .8f, .234f, .065f, .0106f, 0.0, 0.0,
											   1.11f, 1.88f, .512f, .561f, .175f, .066f, .0169f, 0.0, 0.0, 1.07f, 1.89f,
											   .425f, .534f, .165f, .064f, .0162f, 0.0, 0.0, 1.02f, 1.87f, .336f, .506f,
											   .156f, .061f, .0156f, 0.0, 0.0, .0059f, .43f, 1.25f, .867f, .3f, .105f,
											   .023f, 0.0, 0.0, .92f, 1.8f, .677f, .6f, .292f, .16f, .055f, 0.0, 0.0,
											   .00775f, .77f, 1.55f, 1.07f, .49f, .22f, .056f, 0.0, 0.0, 1.51f, 2.73f,
											   1.14f, .99f, .594f, .352f, .171f, .084f, .037f, 1.49f, 2.77f, 1.054f, .93f,
											   .557f, .334f, .163f, .081f, .036f, 1.44f, 2.79f, .961f, .87f, .516f, .315f,
											   .154f, .077f, .034f, .0163f, 1.61f, 1.57f, 1.31f, .77f, .43f, .18f, .106f,
											   .029f, 1.12f, 2.18f, 1.36f, 1.33f, 1.02f, .73f, .47f, .29f, .16f, .0194f,
											   1.9f, 1.66f, 1.63f, 1.16f, .8f, .43f, .32f, .11f, 1.55f, 2.82f, 1.266f,
											   1.13f, .74f, .465f, .248f, .132f, .065f, 1.53f, 2.87f, 1.184f, 1.07f, .698f,
											   .444f, .238f, .128f, .063f, 1.49f, 2.9f, 1.093f, 1.f, .649f, .418f, .225f,
											   .122f, .06f, .0194f, 1.91f, 1.6f, 1.4f, .87f, .52f, .24f, .15f, .045f, 1.14f,
											   2.22f, 1.48f, 1.51f, 1.24f, .94f, .65f, .43f, .26f, .0225f, 2.f, 1.65f,
											   1.69f, 1.23f, .91f, .53f, .47f, .16f, 1.58f, 2.94f, 1.447f, 1.37f, 1.f, .68f,
											   .41f, .25f, .136f, 1.58f, 2.97f, 1.374f, 1.31f, .96f, .66f, .4f, .24f, .133f,
											   1.54f, 3.f, 1.288f, 1.234f, .898f, .62f, .38f, .23f, .127f, .0248f, 2.34f,
											   1.62f, 1.52f, 1.01f, .66f, .33f, .23f, .081f, 1.15f, 2.25f, 1.64f, 1.8f,
											   1.6f, 1.31f, .99f, .71f, .49f, .0279f, 2.2f, 1.63f, 1.77f, 1.3f, 1.07f, .66f,
											   .56f, .26f, 1.6f, 2.98f, 1.546f, 1.52f, 1.18f, .84f, .54f, .34f, .2f, 1.59f,
											   3.02f, 1.481f, 1.464f, 1.13f, .82f, .53f, .33f, .2f, 1.56f, 3.05f, 1.4f,
											   1.388f, 1.07f, .78f, .5f, .32f, .19f, .0285f, 2.6f, 1.63f, 1.58f, 1.08f,
											   .75f, .4f, .3f, .112f, 1.16f, 2.26f, 1.72f, 1.97f, 1.82f, 1.55f, 1.22f, .93f,
											   .67f, .0314f, 2.3f, 1.62f, 1.8f, 1.33f, 1.16f, .74f, .67f, .33f, 1.6f, 3.08f,
											   1.849f, 2.07f, 1.89f, 1.58f, 1.22f, .91f, .65f, 1.6f, 3.09f, 1.81f, 2.04f,
											   1.86f, 1.56f, 1.21f, .91f, .65f, 1.58f, 3.1f, 1.75f, 1.98f, 1.81f, 1.52f,
											   1.18f, .89f, .64f, .045f, 3.3f, 1.628f, 1.78f, 1.3f, 1.11f, .68f, .61f,
											   .299f, 1.15f, 2.27f, 1.98f, 2.5f, 2.6f, 2.49f, 2.2f, 2.f, 1.6f, .0461f,
											   2.32f, 1.606f, 1.946f, 1.508f, 1.57f, 1.11f, 1.18f, .73f, 1.58f, 3.09f,
											   2.009f, 2.43f, 2.42f, 2.2f, 1.87f, 1.54f, 1.22f, 1.58f, 3.08f, 1.99f, 2.42f,
											   2.42f, 2.2f, 1.88f, 1.54f, 1.22f, 1.56f, 3.08f, 1.95f, 2.38f, 2.38f, 2.17f,
											   1.85f, 1.52f, 1.21f, .0587f, 3.39f, 1.624f, 1.902f, 1.454f, 1.4f, .94f,
											   .93f, .53f, 1.13f, 2.26f, 2.11f, 2.8f, 3.09f, 3.1f, 3.f, 2.8f, 2.5f, .0579f,
											   2.33f, 1.64f, 2.078f, 1.7f, 1.91f, 1.46f, 1.64f, 1.17f};
	static float alpha[486] /* was [9][6][9] */ = {1.214f, 1.291f, 3.1f,
												   -.009f, .398f, 1.06f, 0.f, 0.0, 0.0, 1.233f, 1.31f, 2.1f, -.013f, .399f,
												   .97f, 0.f, 0.0, 0.0, 1.25f, 1.323f, 1.1f, -.016f, .4f, 1.03f, 0.f, 0.0, 0.0,
												   1.035f, 1.63f, 5.005f, .028f, .473f, 1.03f, 0.f, 0.0, 0.0, 1.22f, 1.334f,
												   4.1f, -.019f, .461f, 1.18f, 1.3f, 0.0, 0.0, 1.076f, 1.74f, .555f, .031f,
												   .525f, 1.16f, 1.3f, 0.0, 0.0, 1.1f, 1.2f, .29f, 0.f, .386f, .92f, 1.32f, 0.0,
												   0.0, 1.1f, 1.2f, .42f, -.01f, .378f, .91f, 1.26f, 0.0, 0.0, 1.09f, 1.15f,
												   5.1f, -.0199f, .2f, .9f, 1.32f, 0.0, 0.0, 1.13f, 1.66f, .39f, .12f, .48f,
												   .97f, 1.41f, 0.0, 0.0, 1.02f, 1.14f, .66f, -.01f, .485f, 1.15f, 1.69f, 0.0,
												   0.0, 1.19f, 1.7f, .44f, .17f, .56f, 1.13f, 1.67f, 0.0, 0.0, 1.01f, 1.1f,
												   .264f, .048f, .429f, .83f, 1.22f, 0.0, 0.0, 1.01f, 1.1f, .32f, .033f, .417f,
												   .83f, 1.21f, 0.0, 0.0, 1.f, 1.1f, .445f, .018f, .402f, .82f, 1.2f, 0.0, 0.0,
												   1.18f, 1.58f, .27f, .168f, .501f, .9f, 1.23f, 0.0, 0.0, .92f, 1.f, .416f,
												   .09f, .528f, 1.01f, 1.51f, 0.0, 0.0, 1.23f, 1.57f, .27f, .224f, .62f, 1.11f,
												   1.53f, 0.0, 0.0, .87f, .93f, .188f, .2f, .461f, .66f, .94f, 1.22f, 1.58f,
												   .86f, .92f, .21f, .2f, .461f, .66f, .94f, 1.22f, 1.56f, .85f, .91f, .24f,
												   .19f, .459f, .65f, .93f, 1.22f, 1.54f, 1.181f, 1.3f, .09f, .175f, .39f, .58f,
												   .84f, 1.09f, 1.5f, .79f, .84f, .21f, .275f, .51f, .7f, 1.03f, 1.37f, 1.8f,
												   1.16f, 1.18f, .06f, .2f, .41f, .64f, 1.01f, 1.4f, 1.9f, .85f, .9f, .172f,
												   .222f, .452f, .63f, .89f, 1.14f, 1.44f, .84f, .89f, .191f, .221f, .454f,
												   .68f, .89f, 1.13f, 1.41f, .83f, .88f, .216f, .22f, .456f, .63f, .89f, 1.12f,
												   1.43f, 1.168f, 1.23f, .071f, .165f, .35f, .52f, .76f, .96f, 1.31f, .78f,
												   .82f, .181f, .274f, .48f, .66f, .94f, 1.24f, 1.6f, 1.15f, 1.11f, .04f, .17f,
												   .33f, .55f, .86f, 1.1f, 1.6f, .83f, .87f, .149f, .232f, .428f, .59f, .81f,
												   1.02f, 1.25f, .81f, .86f, .165f, .236f, .433f, .59f, .81f, 1.01f, 1.25f, .8f,
												   .85f, .184f, .238f, .438f, .59f, .81f, 1.01f, 1.24f, 1.145f, 1.14f, .046f,
												   .146f, .28f, .44f, .64f, .81f, 1.07f, .762f, .799f, .148f, .255f, .44f, .59f,
												   .83f, 1.06f, 1.36f, 1.12f, 1.f, .014f, .13f, .23f, .43f, .66f, .89f, 1.3f,
												   .81f, .85f, .136f, .232f, .411f, .56f, .77f, .95f, 1.17f, .8f, .84f, .153f,
												   .236f, .416f, .56f, .77f, .95f, 1.16f, .788f, .83f, .167f, .241f, .422f,
												   .56f, .76f, .95f, 1.16f, 1.132f, 1.09f, .033f, .133f, .25f, .4f, .58f, .74f,
												   .98f, .753f, .788f, .131f, .24f, .4f, .55f, .76f, .97f, 1.23f, 1.105f, .95f,
												   .004f, .11f, .19f, .38f, .56f, .78f, 1.11f, .777f, .796f, .1f, .207f, .34f,
												   .46f, .61f, .75f, .91f, .764f, .79f, .108f, .21f, .34f, .46f, .61f, .75f,
												   .91f, .752f, .784f, .117f, .215f, .35f, .46f, .61f, .75f, .9f, 1.092f, .96f,
												   .004f, .093f, .15f, .3f, .42f, .56f, .76f, .729f, .756f, .089f, .182f, .3f,
												   .41f, .55f, .7f, .87f, 1.057f, .81f, -.006f, .075f, .122f, .28f, .394f, .55f,
												   .79f, .757f, .766f, .084f, .183f, .29f, .4f, .52f, .63f, .76f, .746f, .764f,
												   .087f, .182f, .29f, .39f, .52f, .63f, .75f, .736f, .761f, .092f, .184f, .29f,
												   .39f, .51f, .62f, .75f, 1.06f, .86f, -.0018f, .078f, .128f, .264f, .367f,
												   .49f, .67f, .717f, .74f, .069f, .148f, .24f, .33f, .44f, .55f, .67f, 1.024f,
												   .763f, .007f, .075f, .13f, .256f, .36f, .47f, .66f};

	/* System generated locals */
	float ret_val, r__1;
	double d__1, d__2;

	/* Builtin functions */
	double pow_dd(double *, double *);

	/* Local variables */
	static long l;

	/* ********************************************************************** TAB  110 */
	/*                                                                       TAB  120 */
	/*          THE INTERNAL DATA:                                           TAB  130 */
	/*                                                                       TAB  140 */
	/*                                                                       TAB  170 */
	/*          A(1,J,K),J=1,3 = POWER LAW COEFFICIENT FOR THE ABSORPTION    TAB  180 */
	/*            COEFICIENT FOR THE MARSHALL-PALMER WATER DROP SIZE         TAB  190 */
	/*            DISTRIBUTION FOR TEMPERATURE=10.*(J-2) AND FREQUENCY=FR(K) TAB  200 */
	/*          A(2,J,K),J=1,3 = THE SAME FOR THE EXTINCTION COEFFICIENT     TAB  210 */
	/*          A(I,J,K),J=1,3,I=3,9 = THE SAME FOR THE LEGENDRE             TAB  220 */
	/*                                      COEFFICIENT #I-2                 TAB  230 */
	/*          A(I,4,K),I=1,9 = THE SAME AS A(I,2,K), BUT FOR ICE           TAB  240 */
	/*                             (NO TEMPERATURE DEPENDENCE)               TAB  250 */
	/*          A(I,5,K),I=1,9 = THE SAME AS A(I,2,K), BUT FOR THE BEST DROP TAB  260 */
	/*            SIZE DISTRIBUTION (NO TEMPRATURE DEPENDENCE)               TAB  270 */
	/*          A(I,6,K),I=1,9 = THE SAME AS A(I,5,K), BUT FOR ICE           TAB  280 */
	/*          ALPHA(I,J,K) = THE POWER EXPONENET CORRESPONDING TO A(I,J,K) TAB  290 */
	/*          MAXI(J,K): TAB(I,J,K,WC)=0. IF I.GT.MAXI(J,K)                TAB  300 */
	/*          A1, A2 AND ALPHA1 = THE POWER-LINEAR LAW COEFFICIENTS AND    TAB  310 */
	/*                 EXPONENT FOR THE EXCEPTIONAL CASES                    TAB  320 */
	/*                                                                       TAB  330 */
	/*          THE FORMULA:                                                 TAB  340 */
	/*                                                                       TAB  350 */
	/*          SC=A*WC**ALPHA IF ABS(A).GT.10.**-8,                         TAB  360 */
	/*          SC=A1*WC**ALPHA1+A2*WC IF ABS(A).LE.10.**-8,                 TAB  370 */
	/*                    A1, A2 AND ALPHA1 ARE INDEXED BY INT(ALPHA)        TAB  380 */
	/*                                                                       TAB  390 */
	/*          THE BLOCK-DATA SECTION                                       TAB  400 */
	/*                                                                       TAB  410 */
	/*                                                                       TAB 1300 */
	/*                                                                       TAB 1310 */
	if (*i__ > maxi[(0 + (0 + ((*j + *k * 6 - 7) << 2))) / 4])
	{
		ret_val = 0.f;
		return ret_val;
	}
	if ((r__1 = a[*i__ + (*j + *k * 6) * 9 - 64], dabs(r__1)) > 1e-8f)
	{
		d__1 = (double)(*wc);
		d__2 = (double)alpha[*i__ + (*j + *k * 6) * 9 - 64];
		ret_val = a[*i__ + (*j + *k * 6) * 9 - 64] * pow_dd(&d__1, &d__2);
	}
	else
	{
		l = alpha[*i__ + (*j + *k * 6) * 9 - 64];
		d__1 = (double)(*wc);
		d__2 = (double)alpha1[l - 1];
		ret_val = a1[l - 1] * pow_dd(&d__1, &d__2) + a2[l - 1] * *wc;
	}
	return ret_val;
} /* tab_ */

/* Subroutine */ int abcd_(void)
{
	return 0;
} /* abcd_ */

/* >    BLOCK DATA                                                        BAB  105 */

/* Subroutine */ int abcdta_(long *iv)
{

	static long iw, imol, iband;

	/*                                                                       ABC  120 */
	/*                                                                       ABC  270 */
	/*                                                                       ABC  310 */
	/*    MOL                                                                ABC  320 */
	/*     1    H2O (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                ABC  330 */
	/*     2    CO2 (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                ABC  340 */
	/*     3    O3  (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                ABC  350 */
	/*     4    N2O (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                ABC  360 */
	/*     5    CO  (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                ABC  370 */
	/*     6    CH4 (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                ABC  380 */
	/*     7    O2  (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                ABC  390 */
	/*     8    NO  (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                ABC  400 */
	/*     9    SO2 (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                ABC  410 */
	/*    10    NO2 (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                ABC  420 */
	/*    11    NH3 (ALL REGIONS) (DOUBLE EXPONENTIAL MODELS)                ABC  430 */
	/*                                                                       ABC  440 */
	/*  ---H2O                                                               ABC  450 */
	imol = 1;
	iw = -1;
	if (*iv >= 0 && *iv <= 345)
	{
		iw = 17;
	}
	if (*iv >= 350 && *iv <= 1000)
	{
		iw = 18;
	}
	if (*iv >= 1005 && *iv <= 1640)
	{
		iw = 19;
	}
	if (*iv >= 1645 && *iv <= 2530)
	{
		iw = 20;
	}
	if (*iv >= 2535 && *iv <= 3420)
	{
		iw = 21;
	}
	if (*iv >= 3425 && *iv <= 4310)
	{
		iw = 22;
	}
	if (*iv >= 4315 && *iv <= 6150)
	{
		iw = 23;
	}
	if (*iv >= 6155 && *iv <= 8000)
	{
		iw = 24;
	}
	if (*iv >= 8005 && *iv <= 9615)
	{
		iw = 25;
	}
	if (*iv >= 9620 && *iv <= 11540)
	{
		iw = 26;
	}
	if (*iv >= 11545 && *iv <= 13070)
	{
		iw = 27;
	}
	if (*iv >= 13075 && *iv <= 14860)
	{
		iw = 28;
	}
	if (*iv >= 14865 && *iv <= 16045)
	{
		iw = 29;
	}
	if (*iv >= 16340 && *iv <= 17860)
	{
		iw = 30;
	}
	iband = iw - 16;
	aabbcc_2.ibnd[imol - 1] = iw;
	if (iw > 0)
	{
		aabbcc_2.a[imol - 1] = abc_1.ah2o[iband - 1];
		aabbcc_2.aa[imol - 1] = abc_1.aah2o[iband - 1];
		aabbcc_2.bb[imol - 1] = abc_1.bbh2o[iband - 1];
		aabbcc_2.cc[imol - 1] = abc_1.cch2o[iband - 1];
	}
	/*  ---O3                                                                ABC  700 */
	imol = 3;
	iw = -1;
	if (*iv >= 0 && *iv <= 200)
	{
		iw = 31;
	}
	if (*iv >= 515 && *iv <= 1275)
	{
		iw = 32;
	}
	if (*iv >= 1630 && *iv <= 2295)
	{
		iw = 33;
	}
	if (*iv >= 2670 && *iv <= 2845)
	{
		iw = 34;
	}
	if (*iv >= 2850 && *iv <= 3260)
	{
		iw = 35;
	}
	iband = iw - 30;
	aabbcc_2.ibnd[imol - 1] = iw;
	if (iw > 0)
	{
		aabbcc_2.a[imol - 1] = abc_1.ao3[iband - 1];
		aabbcc_2.aa[imol - 1] = abc_1.aao3[iband - 1];
		aabbcc_2.bb[imol - 1] = abc_1.bbo3[iband - 1];
		aabbcc_2.cc[imol - 1] = abc_1.cco3[iband - 1];
	}
	/*  ---CO2                                                               ABC  860 */
	imol = 2;
	iw = -1;
	if (*iv >= 425 && *iv <= 835)
	{
		iw = 36;
	}
	if (*iv >= 840 && *iv <= 1440)
	{
		iw = 37;
	}
	if (*iv >= 1805 && *iv <= 2855)
	{
		iw = 38;
	}
	if (*iv >= 3070 && *iv <= 3755)
	{
		iw = 39;
	}
	if (*iv >= 3760 && *iv <= 4065)
	{
		iw = 40;
	}
	if (*iv >= 4530 && *iv <= 5380)
	{
		iw = 41;
	}
	if (*iv >= 5905 && *iv <= 7025)
	{
		iw = 42;
	}
	if (*iv >= 7395 && *iv <= 7785 || *iv >= 8030 && *iv <= 8335 || *iv >= 9340 && *iv <= 9670)
	{
		iw = 43;
	}
	iband = iw - 35;
	aabbcc_2.ibnd[imol - 1] = iw;
	if (iw > 0)
	{
		aabbcc_2.a[imol - 1] = abc_1.aco2[iband - 1];
		aabbcc_2.aa[imol - 1] = abc_1.aaco2[iband - 1];
		aabbcc_2.bb[imol - 1] = abc_1.bbco2[iband - 1];
		aabbcc_2.cc[imol - 1] = abc_1.ccco2[iband - 1];
	}
	/*  ---CO                                                                ABC 1070 */
	imol = 5;
	iw = -1;
	if (*iv >= 0 && *iv <= 175)
	{
		iw = 44;
	}
	if (*iv >= 1940 && *iv <= 2285 || *iv >= 4040 && *iv <= 4370)
	{
		iw = 45;
	}
	iband = iw - 43;
	aabbcc_2.ibnd[imol - 1] = iw;
	if (iw > 0)
	{
		aabbcc_2.a[imol - 1] = abc_1.aco[iband - 1];
		aabbcc_2.aa[imol - 1] = abc_1.aaco[iband - 1];
		aabbcc_2.bb[imol - 1] = abc_1.bbco[iband - 1];
		aabbcc_2.cc[imol - 1] = abc_1.ccco[iband - 1];
	}
	/*  ---CH4                                                               ABC 1210 */
	imol = 6;
	iw = -1;
	if (*iv >= 1065 && *iv <= 1775 || *iv >= 2345 && *iv <= 3230 || *iv >= 4110 && *iv <= 4690 || *iv >= 5865 && *iv <= 6135)
	{
		iw = 46;
	}
	iband = iw - 45;
	aabbcc_2.ibnd[imol - 1] = iw;
	if (iw > 0)
	{
		aabbcc_2.a[imol - 1] = abc_1.ach4[iband - 1];
		aabbcc_2.aa[imol - 1] = abc_1.aach4[iband - 1];
		aabbcc_2.bb[imol - 1] = abc_1.bbch4[iband - 1];
		aabbcc_2.cc[imol - 1] = abc_1.ccch4[iband - 1];
	}
	/*  ---N2O                                                               ABC 1360 */
	imol = 4;
	iw = -1;
	if (*iv >= 0 && *iv <= 120)
	{
		iw = 47;
	}
	if (*iv >= 490 && *iv <= 775 || *iv >= 865 && *iv <= 995 || *iv >= 1065 && *iv <= 1385 || *iv >= 1545 && *iv <= 2040 || *iv >= 2090 && *iv <= 2655)
	{
		iw = 48;
	}
	if (*iv >= 2705 && *iv <= 2865 || *iv >= 3245 && *iv <= 3925 || *iv >= 4260 && *iv <= 4470 || *iv >= 4540 && *iv <= 4785 || *iv >= 4910 && *iv <= 5165)
	{
		iw = 49;
	}
	iband = iw - 46;
	aabbcc_2.ibnd[imol - 1] = iw;
	if (iw > 0)
	{
		aabbcc_2.a[imol - 1] = abc_1.an2o[iband - 1];
		aabbcc_2.aa[imol - 1] = abc_1.aan2o[iband - 1];
		aabbcc_2.bb[imol - 1] = abc_1.bbn2o[iband - 1];
		aabbcc_2.cc[imol - 1] = abc_1.ccn2o[iband - 1];
	}
	/*  ---O2                                                                ABC 1580 */
	imol = 7;
	iw = -1;
	if (*iv >= 0 && *iv <= 265)
	{
		iw = 50;
	}
	if (*iv >= 7650 && *iv <= 8080 || *iv >= 9235 && *iv <= 9490 || *iv >= 12850 && *iv <= 13220 || *iv >= 14300 && *iv <= 14600 || *iv >= 15695 && *iv <= 15955)
	{
		iw = 51;
	}
	if (*iv >= 49600 && *iv <= 52710)
	{
		iw = 51;
	}
	iband = iw - 49;
	aabbcc_2.ibnd[imol - 1] = iw;
	if (iw > 0)
	{
		aabbcc_2.a[imol - 1] = abc_1.ao2[iband - 1];
		if (*iv >= 49600 && *iv <= 52710)
		{
			aabbcc_2.a[imol - 1] = .4704f;
		}
		aabbcc_2.aa[imol - 1] = abc_1.aao2[iband - 1];
		aabbcc_2.bb[imol - 1] = abc_1.bbo2[iband - 1];
		aabbcc_2.cc[imol - 1] = abc_1.cco2[iband - 1];
	}
	/*  ---NH3                                                               ABC 1770 */
	imol = 11;
	iw = -1;
	if (*iv >= 0 && *iv <= 385)
	{
		iw = 52;
	}
	if (*iv >= 390 && *iv <= 2150)
	{
		iw = 53;
	}
	iband = iw - 51;
	aabbcc_2.ibnd[imol - 1] = iw;
	if (iw > 0)
	{
		aabbcc_2.a[imol - 1] = abc_1.anh3[iband - 1];
		aabbcc_2.aa[imol - 1] = abc_1.aanh3[iband - 1];
		aabbcc_2.bb[imol - 1] = abc_1.bbnh3[iband - 1];
		aabbcc_2.cc[imol - 1] = abc_1.ccnh3[iband - 1];
	}
	/*  ---NO                                                                ABC 1900 */
	imol = 8;
	iw = -1;
	if (*iv >= 1700 && *iv <= 2005)
	{
		iw = 54;
	}
	iband = iw - 53;
	aabbcc_2.ibnd[imol - 1] = iw;
	if (iw > 0)
	{
		aabbcc_2.a[imol - 1] = abc_1.ano;
		aabbcc_2.aa[imol - 1] = abc_1.aano;
		aabbcc_2.bb[imol - 1] = abc_1.bbno;
		aabbcc_2.cc[imol - 1] = abc_1.ccno;
	}
	/*  ---NO2                                                               ABC 2020 */
	iw = -1;
	imol = 10;
	if (*iv >= 580 && *iv <= 925 || *iv >= 1515 && *iv <= 1695 || *iv >= 2800 && *iv <= 2970)
	{
		iw = 55;
	}
	iband = iw - 54;
	aabbcc_2.ibnd[imol - 1] = iw;
	if (iw > 0)
	{
		aabbcc_2.a[imol - 1] = abc_1.ano2[iband - 1];
		aabbcc_2.aa[imol - 1] = abc_1.aano2[iband - 1];
		aabbcc_2.bb[imol - 1] = abc_1.bbno2[iband - 1];
		aabbcc_2.cc[imol - 1] = abc_1.ccno2[iband - 1];
	}
	/*  ---SO2                                                               ABC 2160 */
	imol = 9;
	iw = -1;
	if (*iv >= 0 && *iv <= 185)
	{
		iw = 56;
	}
	if (*iv >= 400 && *iv <= 650 || *iv >= 950 && *iv <= 1460 || *iv >= 2415 && *iv <= 2580)
	{
		iw = 57;
	}
	iband = iw - 55;
	aabbcc_2.ibnd[imol - 1] = iw;
	if (iw > 0)
	{
		aabbcc_2.a[imol - 1] = abc_1.aso2[iband - 1];
		aabbcc_2.aa[imol - 1] = abc_1.aaso2[iband - 1];
		aabbcc_2.bb[imol - 1] = abc_1.bbso2[iband - 1];
		aabbcc_2.cc[imol - 1] = abc_1.ccso2[iband - 1];
	}
	return 0;
} /* abcdta_ */

/* Subroutine */ int cxdta_(float *cprime, float *v, long *iwl, long *iwh,
							float *cp, long *ind)
{
	/* System generated locals */
	long i__1;

	/* Local variables */
	static long i__, ic, iv, indm1;

	/*     THIS SUBROUTINE FINDS THE CPRIME FOR THE WAVENUMBER V.            CXD  110 */
	/*     INPUT:         V --- WAVENUMBER                                   CXD  120 */
	/*            (IWL,IWH) --- WAVENUMBER PAIR SPECIFIES THE ABSORPTION     CXD  130 */
	/*                          REGION. BOTH ARE ARRAYS AND TERMINATED       CXD  140 */
	/*                          WITH THE VALUE -999                          CXD  150 */
	/*                   CP --- ARRAY CONTAINS THE CPRIMES                   CXD  160 */
	/*     OUTPUT:   CPRIME --- THE CPRIME CORRESPONDING TO V                CXD  170 */
	/*     I/O:         IND --- INDICATOR INDICATES THE ABSORPTION REGION    CXD  180 */
	/*                          WHERE THE WAVENUMBER IS EXPECTED TO BE IN    CXD  190 */
	/*                          OR NEARBY (IT SERVES FOR THE PURPOSE         CXD  200 */
	/*                          TO SPEED UP THE SEARCHING PROCESS)           CXD  210 */
	/* Parameter adjustments */
	--cp;
	--iwh;
	--iwl;

	/* Function Body */
	iv = *v;
	*cprime = -20.f;
	if (iwl[*ind + 1] == -999 && iv > iwh[*ind])
	{
		return 0;
	}
	if (iv < iwl[1])
	{
		return 0;
	}
	ic = 0;
L100:
	if (iv >= iwl[*ind] && iv <= iwh[*ind])
	{
		goto L200;
	}
	if (iv > iwh[*ind] && iv < iwl[*ind + 1])
	{
		return 0;
	}
	++(*ind);
	if (iwl[*ind] != -999)
	{
		goto L100;
	}
	--(*ind);
	if (iv > iwh[*ind])
	{
		return 0;
	}
	*ind = 1;
	goto L100;
L200:
	if (*ind == 1)
	{
		goto L400;
	}
	indm1 = *ind - 1;
	i__1 = indm1;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		ic = ic + (iwh[i__] - iwl[i__]) / 5 + 1;
		/* L300: */
	}
L400:
	ic = ic + (iv - iwl[*ind]) / 5 + 1;
	*cprime = cp[ic];
	return 0;
} /* cxdta_ */

double dbltx_(float *w, float *cprime, float *qa)
{
	/* System generated locals */
	float ret_val;
	double d__1;

	/* Builtin functions */
	double r_lg10(float *), pow_dd(double *, double *), exp(double);

	/* Local variables */
	static float ws, qaws;

	ret_val = 1.f;
	if (*w < 1e-20f)
	{
		return ret_val;
	}
	if (*cprime < -20.f)
	{
		return ret_val;
	}
	ws = r_lg10(w) + *cprime;
	qaws = *qa * ws;
	if (qaws < 2.f)
	{
		goto L100;
	}
	ret_val = 0.f;
	return ret_val;
L100:
	if (qaws > -6.f)
	{
		goto L200;
	}
	ret_val = 1.f;
	return ret_val;
L200:
	d__1 = (double)qaws;
	ret_val = exp(-pow_dd(&c_b1661, &d__1));
	return ret_val;
} /* dbltx_ */

/* Subroutine */ int cldprf_(long *k, long *icld, long *iha1,
							 long *ic1)
{
	/* Initialized data */

	static float rhzone[4] = {0.f, 70.f, 80.f, 99.f};
	static float elwcr[4] = {3.517e-4f, 3.74e-4f, 4.439e-4f, 9.529e-4f};
	static float elwcm[4] = {4.675e-4f, 6.543e-4f, .001166f, .003154f};
	static float elwcu[4] = {3.102e-4f, 3.802e-4f, 4.463e-4f, 9.745e-4f};
	static float elwct[4] = {1.735e-4f, 1.82e-4f, 2.02e-4f, 2.408e-4f};
	static float aflwc = .01295f;
	static float rflwc = .001804f;
	static float culwc = .007683f;
	static float aslwc = .004509f;
	static float stlwc = .005272f;
	static float sclwc = .004177f;
	static float snlwc = .007518f;
	static float bslwc = 1.567e-4f;
	static float fvlwc = 5.922e-4f;
	static float avlwc = 1.675e-4f;
	static float mdlwc = 4.775e-4f;
	static float tnlwc = .003446f;
	static float tklwc = .05811f;

	/* Builtin functions */
	long s_wsle(cilist *), do_lio(long *, long *, char *, long),
		e_wsle(void);
	double log(double), exp(double);

	/* Local variables */
	static long i__, m, n;
	static float x, e1, e2, x1, x2, ec;
	static long ih, ii, ita;
	static float con;
	static long itc;
	static float wrh;

	/* Fortran I/O blocks */
	static cilist io___964 = {0, 6, 0, 0, 0};

	/* ***********************************************************************CLD  110 */
	/*     WILL COMPUTE DENSITY    PROFILES FOR CLOUDS                       CLD  120 */
	/* ***********************************************************************CLD  130 */
	if (model_2.cldamt[(9112 + (0 + ((*k - 1) << 2)) - 9112) / 4] <= 0.f)
	{
		goto L15;
	}
	ih = *icld;
	if (ih == 0)
	{
		goto L200;
	}
	if (*icld == 18)
	{
		model_2.hazec[*k - 1] = model_2.cldamt[*k - 1] / tnlwc;
		return 0;
	}
	if (*icld == 19)
	{
		model_2.hazec[*k - 1] = model_2.cldamt[*k - 1] / tklwc;
		return 0;
	}
	if (*icld == 20)
	{
		return 0;
	}
	switch (ih)
	{
	case 1:
		goto L114;
	case 2:
		goto L115;
	case 3:
		goto L116;
	case 4:
		goto L117;
	case 5:
		goto L118;
	case 6:
		goto L116;
	case 7:
		goto L118;
	case 8:
		goto L118;
	case 9:
		goto L114;
	case 10:
		goto L114;
	case 11:
		goto L114;
	}
L114:
	model_2.hazec[*k - 1] = model_2.cldamt[*k - 1] / culwc;
	return 0;
L115:
	model_2.hazec[*k - 1] = model_2.cldamt[*k - 1] / aslwc;
	return 0;
L116:
	model_2.hazec[*k - 1] = model_2.cldamt[*k - 1] / stlwc;
	return 0;
L117:
	model_2.hazec[*k - 1] = model_2.cldamt[*k - 1] / sclwc;
	return 0;
L118:
	model_2.hazec[*k - 1] = model_2.cldamt[*k - 1] / snlwc;
L15:
	return 0;
L200:
	if (*iha1 > 0)
	{
		goto L205;
	}
	s_wsle(&io___964);
	do_lio(&c__9, &c__1, (char *)" WARNING ICLD NOT SET ", (long)22);
	e_wsle();
	return 0;
L205:
	wrh = _BLNK__2.relhum[*k - 1];
	/*                                                                       CLD  620 */
	m = *ic1;
	if (_BLNK__2.ich[m - 1] == 6 && m != 1)
	{
		wrh = 70.f;
	}
	/*     THIS CODING  DOES NOT ALLOW TROP RH DEPENDENT  ABOVE EH(7,I)      CLD  650 */
	/*     DEFAULTS TO TROPOSPHERIC AT 70. PERCENT                           CLD  660 */
	for (i__ = 2; i__ <= 4; ++i__)
	{
		if (wrh < rhzone[i__ - 1])
		{
			goto L215;
		}
		/* L210: */
	}
	i__ = 4;
L215:
	ii = i__ - 1;
	if (wrh > 0.f && wrh < 99.f)
	{
		x = log(100.f - wrh);
	}
	x1 = log(100.f - rhzone[ii - 1]);
	x2 = log(100.f - rhzone[i__ - 1]);
	if (wrh >= 99.f)
	{
		x = x2;
	}
	if (wrh <= 0.f)
	{
		x = x1;
	}
	ita = _BLNK__2.ich[m - 1];
	if (ita == 3 && m == 1)
	{
		goto L218;
	}
	if (ita > 6)
	{
		goto L245;
	}
	/* C                                                                      CLD  800 */
	/* C    MICROWAVE                                                         CLD  810 */
	n = 41;
/* C                                                                      CLD  830 */
L218:
	if (n >= 41 && ita == 3)
	{
		ita = 4;
	}
	/*     RH DEPENDENT AEROSOLS                                             CLD  850 */
	switch (ita)
	{
	case 1:
		goto L220;
	case 2:
		goto L220;
	case 3:
		goto L222;
	case 4:
		goto L225;
	case 5:
		goto L230;
	case 6:
		goto L235;
	}
L220:
	e2 = log(elwcr[i__ - 1]);
	e1 = log(elwcr[ii - 1]);
	goto L240;
L222:
	if (m > 1)
	{
		goto L225;
	}
	e2 = log(elwcm[i__ - 1]);
	e1 = log(elwcm[ii - 1]);
	goto L240;
L225:
	e2 = log(elwcm[i__ - 1]);
	e1 = log(elwcm[ii - 1]);
	goto L240;
L230:
	e2 = log(elwcu[i__ - 1]);
	e1 = log(elwcu[ii - 1]);
	goto L240;
L235:
	e2 = log(elwct[i__ - 1]);
	e1 = log(elwct[ii - 1]);
L240:
	ec = e1 + (e2 - e1) * (x - x1) / (x2 - x1);
	con = exp(ec);
	model_2.hazec[*k - 1] = model_2.cldamt[*k - 1] / con;
	return 0;
L245:
	if (ita > 19)
	{
		goto L275;
	}
	itc = _BLNK__2.ich[m - 1] - 7;
	if (itc < 1)
	{
		return 0;
	}
	switch (itc)
	{
	case 1:
		goto L250;
	case 2:
		goto L255;
	case 3:
		goto L280;
	case 4:
		goto L260;
	case 5:
		goto L265;
	case 6:
		goto L270;
	case 7:
		goto L265;
	case 8:
		goto L270;
	case 9:
		goto L260;
	case 10:
		goto L260;
	case 11:
		goto L270;
	case 12:
		goto L275;
	}
L250:
	con = aflwc;
	goto L280;
L255:
	con = rflwc;
	goto L280;
L260:
	con = bslwc;
	goto L280;
L265:
	con = avlwc;
	goto L280;
L270:
	con = fvlwc;
	goto L280;
L275:
	con = mdlwc;
L280:
	model_2.hazec[*k - 1] = model_2.cldamt[*k - 1] / con;
	return 0;
} /* cldprf_ */

double bbfn_(float *t, float *v)
{
	/* System generated locals */
	float ret_val, r__1, r__2;

	/* Builtin functions */
	double exp(double);

	/* Local variables */
	static float x;

	/* ***********************************************************************BBF  110 */
	/*   PLANCK BLACK BODY FUNCTION IN UNITS OF WATTS/(CM2 STER MICROMETER)  BBF  120 */
	/* ***********************************************************************BBF  130 */
	ret_val = 0.f;
	if (*v <= 0.f)
	{
		return ret_val;
	}
	x = *v * 1.43879f / *t;
	/* *****PROTECT AGAINST EXPONENTIAL OVERLOW                               BBF  180 */
	if (x > cnstns_1.bigexp)
	{
		return ret_val;
	}
	/* Computing 5th power */
	r__1 = *v, r__2 = r__1, r__1 *= r__1;
	ret_val = r__2 * (r__1 * r__1) * 1.190956e-16f / (exp(x) - 1.f);
	return ret_val;
} /* bbfn_ */

/* Subroutine */ int msrad_(long *iv, float *v, long *isourc, long *iday, float *anglem, float *ss, float *dmf, float *dmfs, float *umf, float *umfs)
{
	/* System generated locals */
	long i__1;

	/* Local variables */
	static float s0;
	static long ik, ikm;
	static float denom;
	static long ikmik;
	extern /* Subroutine */ int flxadd_(float *, float *, float *, float *, float *, float *, long *, long *, float *, float *, float *, float *,
										float *, float *, float *, float *, float *),
		source_(float *, long *, long *, float *, float *);

	/*                                                                       MSR  120 */
	/*         (1) SETS UP OPTICAL PROPERTIES PROFILES FOR VERTICAL          MSR  130 */
	/*             PATH                                                      MSR  140 */
	/*         (2) CALLS FLXADD WHICH RETURNS MS SOURCE FUNCTION, J,         MSR  150 */
	/*             FOR PATH                                                  MSR  160 */
	/*         (3) EVALUATES PATH INTEGRAL OF SOURCE FUNCTION, I.E.          MSR  170 */
	/*             MS RADIANCE CONTRIBUTION                                  MSR  180 */
	/*                                                                       MSR  190 */
	/*                                 A.E.R. 1986                           MSR  200 */
	/*                                                                       MSR  210 */
	/*                                                                       MSR  340 */
	/*                                                                       MSR  450 */
	/* Parameter adjustments */
	--umfs;
	--umf;
	--dmfs;
	--dmf;

	/* Function Body */
	++cntrl_1.ikmax;
	ikm = cntrl_1.ikmax - 1;
	/*                                                                       MSR  480 */
	/*  FOR H1 < H2, CALCULATE DOWNWARD RADIANCE                             MSR  490 */
	/*                                                                       MSR  500 */
	/*                                                                       MSR  510 */
	i__1 = ikm - 1;
	for (ik = cntrl_1.iklo; ik <= i__1; ++ik)
	{
		/*                                                                       MSR  530 */
		/*  AEROSOL PATH FOR EACH LAYER (NOT CUMULATIVE)                         MSR  540 */
		/*                                                                       MSR  550 */
		/*                                                                       MSR  560 */
		/*  SOLAR TRANSMITTANCE FROM TOP OF ATMOSPHERE                           MSR  570 */
		/*                                                                       MSR  580 */
		msrd_1.strn[ik - 1] = msrd_1.dstrn[cntrl_1.ikmax - ik];
		if (card2_1.ihaze > 0)
		{
			/*                                                                       MSR  610 */
			/*  CALCULATE AEROSOL ASYMMETRY FACTOR FOR GIVEN LAYER                   MSR  620 */
			/*                                                                       MSR  630 */
			denom = msrd_1.asydm[ik - 1];
			if (denom <= 0.f)
			{
				msrd_1.cosbar[ikm - ik - 1] = 0.f;
			}
			else
			{
				msrd_1.cosbar[ikm - ik - 1] = msrd_1.asyik[ik - 1] / denom;
			}
		}
		/*                                                                       MSR  710 */
		/*  TAER,TAERS, AND TMOLS ARE TOTAL AEROSOL, AEROSOL SCATTERING, AND     MSR  720 */
		/*  MOLECULAR SCATTERING OPTICAL THICKNESS FOR GIVEN LAYER               MSR  730 */
		/*                                                                       MSR  740 */
		msrd_1.taer[ikm - ik - 1] = msrd_1.dtx7[ik] - msrd_1.dtx7[ik - 1];
		tran_1.taers[ikm - ik - 1] = msrd_1.daers[ik] - msrd_1.daers[ik - 1];
		tran_1.tmols[ikm - ik - 1] = msrd_1.dmols[ik] - msrd_1.dmols[ik - 1];
		ikmik = ikm - ik;
		if (msrd_1.taer[ikmik - 1] < 0.f)
		{
			msrd_1.taer[ikmik - 1] = 0.f;
		}
		if (tran_1.taers[ikmik - 1] < 0.f)
		{
			tran_1.taers[ikmik - 1] = 0.f;
		}
		if (tran_1.tmols[ikmik - 1] < 0.f)
		{
			tran_1.tmols[ikmik - 1] = 0.f;
		}
		/*                                                                       MSR  780 */
		/*  WEIGHT ASYMMETRY FACTOR                                              MSR  790 */
		/*                                                                       MSR  800 */
		if (tran_1.taers[ikm - ik - 1] <= 0.f)
		{
			msrd_1.cosbar[ikm - ik - 1] = 0.f;
		}
		else
		{
			msrd_1.cosbar[ikm - ik - 1] = msrd_1.cosbar[ikm - ik - 1] *
										  tran_1.taers[ikm - ik - 1] / (tran_1.taers[ikm - ik - 1] + tran_1.tmols[ikm - ik - 1]);
		}
		/*                                                                       MSR  870 */
		/*  TCONT IS MOLECULAR CONTINUUM OPTICAL THICKNESS FOR GIVEN LAYER       MSR  880 */
		/*                                                                       MSR  890 */
		/* L222: */
		tran_1.tcont[ikm - ik - 1] = tran_1.dcont[ik] - tran_1.dcont[ik - 1];
	}
	if (card2_1.ihaze > 0)
	{
		/*                                                                       MSR  920 */
		/*  CALCULATE ASYMMETRY FACTOR FOR BOTTOM OF ATMOSPHERE                  MSR  930 */
		/*                                                                       MSR  940 */
		denom = msrd_1.asydm[0];
		if (denom <= 0.f)
		{
			msrd_1.cosbar[ikm - 1] = 0.f;
		}
		else
		{
			msrd_1.cosbar[ikm - 1] = msrd_1.asyik[ik - 1] / denom;
		}
	}
	msrd_1.strn[ikm - 1] = msrd_1.dstrn[cntrl_1.ikmax - ikm];
	msrd_1.strn[ikm] = msrd_1.dstrn[0];
	msrd_1.taer[ikm - 1] = msrd_1.dtx7[0];
	tran_1.taers[ikm - 1] = msrd_1.daers[0];
	tran_1.tmols[ikm - 1] = msrd_1.dmols[0];
	/*                                                                       MSR 1070 */
	/*   WEIGHT ASYMMETRY FACTOR                                             MSR 1080 */
	/*                                                                       MSR 1090 */
	if (tran_1.taers[ikm - 1] <= 0.f)
	{
		msrd_1.cosbar[ikm - 1] = 0.f;
	}
	else
	{
		msrd_1.cosbar[ikm - 1] = msrd_1.cosbar[ikm - 1] * tran_1.taers[ikm - 1] / (tran_1.taers[ikm - 1] + tran_1.tmols[ikm - 1]);
	}
	tran_1.tcont[ikm - 1] = tran_1.dcont[0];
	/*                                                                       MSR 1160 */
	/*   FOR H1 > H2, CALCULATE UPWARD RADIANCE                              MSR 1170 */
	/*                                                                       MSR 1180 */
	/*                                                                       MSR 1190 */
	/*   CALCULATE SOLAR INTENSITY AT TOP OF ATMOSPHERE                      MSR 1200 */
	/*                                                                       MSR 1210 */
	s0 = 0.f;
	if (card1_1.iemsct == 2)
	{
		source_(v, isourc, iday, anglem, &s0);
	}
	/*                                                                       MSR 1240 */
	/*                                                                       MSR 1250 */
	/*   CALL FLUX ADDING SUBROUTINE                                         MSR 1260 */
	/*                                                                       MSR 1270 */
	flxadd_(msrd_1.tle, msrd_1.cosbar, msrd_1.taer, msrd_1.omega0, msrd_1.upf,
			msrd_1.dnf, iv, &cntrl_1.ikmax, sols_1.cszen, &s0, msrd_1.strn, &msrd_1.fdnsrt, &msrd_1.fdntrt, &dmf[1], &dmfs[1], &umf[1], &umfs[1]);
	return 0;
} /* msrad_ */

/* Subroutine */ int flxadd_(float *tle, float *cosbar, float *taer, float *omega0, float *upf, float *dnf, long *iwavn, long *ikmax, float *cszen, float *s0, float *strn, float *fdnsrf, float *fdntrf, float *dmf,
							 float *dmfs, float *umf, float *umfs)
{
	/* Initialized data */

	static float rupc[50] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
							 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
							 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
							 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	static float rupcs[34] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
							  0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
							  0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	static float eups[34] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
							 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
							 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	static float edns[34] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
							 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
							 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	static float refs[34] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
							 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
							 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	static float tdfs[34] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
							 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
							 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	static float upfs[510] /* was [15][34] */ = {0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	static float dnfs[510] /* was [15][34] */ = {0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
												 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	static float fac[3] = {1.f, .09f, .015f};

	/* System generated locals */
	long i__1;
	double d__1, d__2;

	/* Builtin functions */
	double pow_dd(double *, double *), sqrt(double), exp(double);

	/* Local variables */
	static float g;
	static long k, m, n;
	static float q, v, x, b0, fc;
	static long ib, mf, ng;
	static float cs, sk;
	static long iw;
	static float xp, ys, gm1;
	static long ng1;
	static float gm2;
	static double ex1, ex2;
	static float edn[50], dpc, tdf[50], ref[50], dpj[102] /* was [3][34]
														   */
		,
		eup[50];
	static long mol;
	static float ekt, smu;
	static double aer1, aer2, dnm1;
	static float ome0, ekt2, cp1s[11];
	extern double bbfn_(float *, float *);
	static double aera, aerc, deno, aeru, aerv, dnmo;
	static float eupc[50], taum[150] /* was [3][50] */, bets[34], taut[34],
		twgp[102] /* was [3][34] */, gkwj[33] /* was [3][11] */,
		dpwj[33] /* was [3][11] */, wavn, ektl, etmu, asxp, edncn,
		pefdn;
	static double aercx;
	static float denom, rdncn, denos, eupcn, smdpj, eupcs[34], gmmsk, gmpsk,
		etmul, rupcn, asnew, bsnew, pefup;
	extern double betabs_(float *, float *);
	static float omegak[34], edncns, pefdns, rdncns, eupcns, pefups, fupsrf,
		fuptrf;
	static long nlayrs;
	static float rupcns, xcszen;

	/*                                                                       FLX  130 */
	/*         (1) CALCULATES UPWARD, F+ (UPF), AND DOWNWARD, F- (DNF),      FLX  140 */
	/*             FLUX PROFILES USING ADDING METHOD                         FLX  150 */
	/*         (2) MS SOURCE FUNCTION EVALUATED FROM LEVEL FLUXES VIA        FLX  160 */
	/*             STREAM APPROXIMATION (SEE EQN     , ISAACS ET AL, 1986)   FLX  170 */
	/*         (3) BACKSCATTER FOR SOURCE FUNCTION FOR GIVEN G FACTOR        FLX  180 */
	/*             AND ZENTIH ANGLE OBTAINED USING FUNCTION BETABS           FLX  190 */
	/*                                                                       FLX  200 */
	/*                                          A.E.R. 1986                  FLX  210 */
	/*                                                                       FLX  220 */
	/*                                                                       FLX  250 */
	/* ***********************************************************************FLX  470 */
	/*                                                                       FLX  480 */
	/*   INPUT PARAMETERS:                                                   FLX  490 */
	/*   ----------------                                                    FLX  500 */
	/*   TLE(N)     - TEMPERATURE (KELVIN) OF UPPER EDGE OF LAYER N          FLX  510 */
	/*   COSBAR(N)  - ASYMMETRY FACTOR FOR LAYER N                           FLX  520 */
	/*   TAER(N)    - TOTAL AEROSOL OPTICAL THICKNESS OF LAYER N             FLX  530 */
	/*   TAERS(N)   - AEROSOL SCATTERING OPTICAL THICKNESS OF LAYER N        FLX  540 */
	/*   TCONT(N)   - MOLECULAR CONTINUUM OPTICAL THICKNESS FOR LAYER N      FLX  550 */
	/*   TMOLS(N)   - RAYLEIGH SCATTERING OPTICAL THICKNESS FOR LAYER N      FLX  560 */
	/*   CSZEN(N)   - COSINE OF SOLAR ZENITH ANGLE FOR LAYER N               FLX  570 */
	/*   IWAVN      - FREQUENCY (WAVENUMBER)                                 FLX  580 */
	/*   S0         - SOLAR INTENSITY AT TOP OF ATMOSPHERE                   FLX  590 */
	/*   H1         - ALTITUDE OF OBSERVER (KM)                              FLX  600 */
	/*   H2         - ALTITUDE OF TARGET (KM)                                FLX  610 */
	/*   STRN(N)    - SOLAR TRANSMISSION TO BOTTOM OF LAYER N                FLX  620 */
	/*                                                                       FLX  630 */
	/*   OUTPUT PARAMETERS:                                                  FLX  640 */
	/*   -----------------                                                   FLX  650 */
	/*   OMEGAK  (N)- SINGLE SCATTERING ALBEDO OF LAYER N FOR VALUE OF K     FLX  660 */
	/*   TAUM(K,N)  - MOLECULAR OPTICAL THICKNESS OF LAYER N FOR VALUE OF K  FLX  670 */
	/*   BTOP(N)    - BLACK BODY FLUX FOR UPPER EDGE TEMPERATURE OF LAYER N  FLX  680 */
	/*   BMID(N)    - BLACK BODY FLUX FOR AVERAGE TEMPERATURE OF LAYER N     FLX  690 */
	/*                                                                       FLX  700 */
	/*   INTERNAL PARAMETERS:                                                FLX  710 */
	/*   -------------------                                                 FLX  720 */
	/*   TWGP(K,N)  - SUM OF OPTICAL DEPTH * PROBABILITY BY MOLECULE         FLX  730 */
	/*                                                                       FLX  740 */
	/*   UPF(K,N)   - UPWARD THERMAL FLUX AT UPPER EDGE OF LAYER N FOR       FLX  750 */
	/*                VALUE OF K                                             FLX  760 */
	/*   UPFS(K,N)  - UPWARD SOLAR FLUX AT UPPER EDGE OF LAYER N FOR         FLX  770 */
	/*                VALUE OF K                                             FLX  780 */
	/*   DNF(K,N)   - DOWNWARD THERMAL FLUX AT UPPER EDGE OF LAYER N FOR     FLX  790 */
	/*                VALUE OF K                                             FLX  800 */
	/*   DNFS(K,N)  - DOWNWARD SOLAR FLUX AT UPPER EDGE OF LAYER N FOR       FLX  810 */
	/*                VALUE OF K                                             FLX  820 */
	/*   UMF(N)     - MEAN UPWARD THERMAL FLUX OF LAYER N FOR VALUE OF K     FLX  830 */
	/*   UMFS(N)    - MEAN UPWARD SOLAR FLUX OF LAYER N FOR VALUE OF K       FLX  840 */
	/*   DMF(N)     - MEAN DOWNWARD THERMAL FLUX OF LAYER N FOR VALUE OF K   FLX  850 */
	/*   DMFS(N)    - MEAN DOWNWARD SOLAR FLUX OF LAYER N FOR VALUE OF K     FLX  860 */
	/*   SU(K,N)    - UPWARD THERMAL RADIANCE SOURCE FUNCTION FOR N,K        FLX  870 */
	/*   SUS(K,N)   - UPWARD SOLAR RADIANCE SOURCE FUNCTION FOR N,K          FLX  880 */
	/*   SD(K,N)    - DOWNWARD THERMAL RADIANCE SOURCE FUNCTION FOR N,K      FLX  890 */
	/*   SDS(K,N)   - DOWNWARD SOLAR RADIANCE SOURCE FUNCTION FOR N,K        FLX  900 */
	/*   BETS(N)    - BACKSCATTER FRACTION ALONG SOLAR PATH AT LAYER N       FLX  910 */
	/*                                                                       FLX  920 */
	/* ***********************************************************************FLX  930 */
	/*                                                                       FLX  940 */
	/*   NEW VARABLES          11 MOLECULES  BY JOSEPH H PIERLUISSI          FLX  950 */
	/*   DPWJ  PROBABILITY FOR EACH MOLECULE  FIT DOUBLE EXPODENTIAL         FLX  960 */
	/*   GKWJ  BAND DEPENDENT  SCALING OF DENSITYS TO GET K  AMOUNT          FLX  970 */
	/*   CPS IS THE STORED VALUES OF PIERLUISSI BAND MODEL COEFFIECNTS       FLX  980 */
	/*   CP1S = 10**CPS                                                      FLX  990 */
	/*   IBND MAPS BANDS TO MOLECULES                                        FLX 1000 */
	/*   DPJ REPLACES DPO  IS THE  EFFECTIVE PROBILITY BY LAYER              FLX 1010 */
	/*   TAUM IS DEFINED AS THE SUM OF THE OPTICAL DEPTHS BY MOLECULE        FLX 1020 */
	/*                                                                       FLX 1030 */
	/* Parameter adjustments */
	--umfs;
	--umf;
	--dmfs;
	--dmf;
	--cszen;
	dnf -= 11;
	upf -= 11;
	--omega0;
	--taer;
	--cosbar;
	--tle;

	/* Function Body */
	/* L320: */
	/* L300: */
	/* L310: */
	dpc = .33333333333333331f;
	wavn = (float)(*iwavn);
	v = wavn;
	/* C    PRINT 1900                                                        FLX 1150 */
	/* L1900: */
	nlayrs = cntrl_1.ml - 1;
	ng = nlayrs + 1;
	ng1 = ng + 1;
	for (m = 1; m <= 11; ++m)
	{
		/* L1: */
		d__1 = (double)aabbcc_2.cps[m - 1];
		cp1s[m - 1] = pow_dd(&c_b1661, &d__1);
	}
	/*                                                                       FLX 1220 */
	for (mol = 1; mol <= 11; ++mol)
	{
		for (k = 1; k <= 3; ++k)
		{
			iw = aabbcc_2.ibnd[mol - 1];
			gkwj[k + mol * 3 - 4] = 0.f;
			dpwj[k + mol * 3 - 4] = 0.f;
			if (iw <= 0)
			{
				goto L5;
			}
			gkwj[k + mol * 3 - 4] = fac[k - 1] * aabbcc_2.cc[mol - 1];
			if (k == 1)
			{
				dpwj[k + mol * 3 - 4] = aabbcc_2.aa[mol - 1];
			}
			if (k == 2)
			{
				dpwj[k + mol * 3 - 4] = aabbcc_2.bb[mol - 1];
			}
			if (k == 3)
			{
				dpwj[k + mol * 3 - 4] = 1.f - aabbcc_2.aa[mol - 1] -
										aabbcc_2.bb[mol - 1];
			}
			if (k > 1)
			{
				goto L5;
			}
		L5:;
		}
		/* L4: */
	}
	tle[ng1] = tle[ng];
	i__1 = ng;
	for (n = 1; n <= i__1; ++n)
	{
		/*                                                                       FLX 1380 */
		/*   BLACK BODY FLUX FOR LAYER EDGE TEMPERATURE                          FLX 1390 */
		/*                                                                       FLX 1400 */
		tran_1.btop[n - 1] = bbfn_(&tle[n], &v) * cnstns_1.pi;
		/*                                                                       FLX 1420 */
		/*   BLACK BODY RADIANCE FOR LAYER MIDDLE TEMPERATURE                    FLX 1430 */
		/*                                                                       FLX 1440 */
		tran_1.bmid[n - 1] = bbfn_(&tran_1.tmd[n - 1], &v);
		if (n < ng)
		{
			/*                                                                       FLX 1470 */
			/*    CALCULATE COSINE OF VIEWING PATH ZENITH ANGLE                      FLX 1480 */
			/*                                                                       FLX 1490 */
			/*                                                                       FLX 1500 */
			/*    CALCULATE BACKSCATTER PARAMETERS                                   FLX 1510 */
			/*                                                                       FLX 1520 */
			if (cosbar[n] == 0.f)
			{
				bets[n - 1] = .5f;
			}
			else
			{
				if (card1_1.iemsct == 2 || card1_1.iemsct == 3)
				{
					bets[n - 1] = betabs_(&cszen[n], &cosbar[n]);
				}
			}
		}
		/* L98: */
	}
	/*                                                                       FLX 1620 */
	/*   ABSORPTION COEFFICIENTS FOR WATER VAPOR, UNIFORMLY MIXED GASES      FLX 1630 */
	/*   AND OZONE                                                           FLX 1640 */
	/*                                                                       FLX 1650 */
	/*                                                                       FLX 1660 */
	/*   EVALUATE THE WEIGHTED K DISTRIBUTION QUANTITIES FOR                 FLX 1670 */
	/*   WATER VAPOR AND THE UNIFORMLY MIXED GASES                           FLX 1680 */
	/*                                                                       FLX 1690 */
	for (k = 1; k <= 3; ++k)
	{
		i__1 = nlayrs;
		for (n = 1; n <= i__1; ++n)
		{
			/*                                                                       FLX 1720 */
			taum[k + n * 3 - 4] = 0.f;
			twgp[k + n * 3 - 4] = 0.f;
			for (mol = 1; mol <= 11; ++mol)
			{
				ib = aabbcc_2.ibnd[mol - 1];
				if (ib < 0)
				{
					goto L60;
				}
				_BLNK__1.w[ib - 1] = model_5.densty[ib + (*ikmax - n) * 63 -
													64] *
									 path_1.pl[*ikmax - n - 1] * gkwj[k + mol * 3 - 4];
				taum[k + n * 3 - 4] += _BLNK__1.w[ib - 1] * cp1s[mol - 1];
				twgp[k + n * 3 - 4] += _BLNK__1.w[ib - 1] * cp1s[mol - 1] *
									   dpwj[k + mol * 3 - 4];
			L60:;
			}
			dpj[k + n * 3 - 4] = dpc;
			if (taum[k + n * 3 - 4] != 0.f)
			{
				dpj[k + n * 3 - 4] = twgp[k + n * 3 - 4] / taum[k + n * 3 - 4];
			}
			/*                                                                       FLX 1860 */
			/*     EFFECTIVE PROBILITY BY LAYER DPJ IS BASED ON MOLECULAR            FLX 1870 */
			/*     PROBILITY WEIGHTED BY OPTICAL DEPTH                               FLX 1880 */
			/*                                                                       FLX 1890 */
			/* L70: */
		}
	}
	i__1 = nlayrs;
	for (n = 1; n <= i__1; ++n)
	{
		smdpj = dpj[n * 3 - 3] + dpj[n * 3 - 2] + dpj[n * 3 - 1];
		for (k = 1; k <= 3; ++k)
		{
			dpj[k + n * 3 - 4] /= smdpj;
			/* L80: */
		}
	}
	/*                                                                       FLX 1960 */
	/*     EFFECTIVE PROBILITY BY LAYER DPJ NORMALIZED                       FLX 1970 */
	/*     FOR CURRENT VALUES OF GKWJ  NORMALIZATION NOT REQUIRED            FLX 1980 */
	/*     PROTECTION FOR ARBITARY CHOICE OF GKWJ                            FLX 1990 */
	/*                                                                       FLX 2000 */
	/* ***********************************************************************FLX 2010 */
	/* *    PROBABILITY INTEGRATION LOOP                                     *FLX 2020 */
	/* ***********************************************************************FLX 2030 */
	for (k = 1; k <= 3; ++k)
	{
		/* **** COMPOSITE DOWNWARDS REFLECTION                                    FLX 2050 */
		rdncn = 0.f;
		rdncns = 0.f;
		/* ***********************************************************************FLX 2080 */
		/* *    ADDING GROUND LAYER                                              *FLX 2090 */
		/* ***********************************************************************FLX 2100 */
		/*                                                                       FLX 2110 */
		/*   DEFINE INITIAL UPWARD COMPOSITE SURFACE REFLECTANCE                 FLX 2120 */
		/*                                                                       FLX 2130 */
		rupcn = card1_1.salb;
		rupcns = card1_1.salb;
		/*                                                                       FLX 2160 */
		/*   SURFACE THERMAL EMISSION                                            FLX 2170 */
		/*                                                                       FLX 2180 */
		tran_1.btop[ng1 - 1] = bbfn_(&tle[ng1], &v) * cnstns_1.pi;
		/*                                                                       FLX 2200 */
		/*   SURFACE EMISSION                                                    FLX 2210 */
		/*                                                                       FLX 2220 */
		eupcn = (1.f - rupcn) * tran_1.btop[ng1 - 1];
		eup[ng - 1] = eupcn;
		eupc[ng - 1] = eupcn;
		if (card1_1.iemsct == 2)
		{
			mf = cntrl_1.ml - 1;
			eupcns = rupcns * cszen[mf] * strn[mf] * *s0;
		}
		else
		{
			eupcns = 0.f;
		}
		eups[ng - 1] = eupcns;
		eupcs[ng - 1] = eupcns;
		/*                                                                       FLX 2340 */
		/* ***********************************************************************FLX 2350 */
		/* *      UPWARD ADDING LOOP(1-N)                                        *FLX 2360 */
		/* ***********************************************************************FLX 2370 */
		for (n = nlayrs; n >= 1; --n)
		{
			m = n - 1;
			/*                                                                       FLX 2400 */
			/*    CALCULATE MOLECULAR OPTICAL THICKNESS OF EACH LAYER FOR EACH K     FLX 2410 */
			/*    NOTE: TOP LAYER IS LAYER 1                                         FLX 2420 */
			/*                                                                       FLX 2430 */
			/*                                                                       FLX 2440 */
			/*      EUP AND EDN ARE UPWARD AND DOWNWARD THERMAL FLUX                 FLX 2450 */
			/*      FOR AN ISOLATED LAYER                                            FLX 2460 */
			/*      TDF AND REF ARE THE THERMAL TRANSMISSION AND REFLECTANCE         FLX 2470 */
			/*      FOR AN ISOLATED LAYER                                            FLX 2480 */
			if (k == 1)
			{
				taut[n - 1] = taum[k + n * 3 - 4] * dpj[k + n * 3 - 4];
			}
			else
			{
				taut[n - 1] = taum[k + n * 3 - 4] * dpj[k + n * 3 - 4] + taut[n - 1];
				denom = taut[n - 1] + taer[n] + tran_1.tcont[n - 1] +
						tran_1.tmols[n - 1];
				if (denom <= 0.f)
				{
					denom = 1.f;
				}
				if (k == 3)
				{
					omega0[n] = (tran_1.taers[n - 1] + tran_1.tmols[n - 1]) /
								denom;
				}
			}
			/*                                                                       FLX 2580 */
			/*    XP IS THE PATH OPTICAL THICKNESS FOR A GIVEN LAYER OF PATH         FLX 2590 */
			/*    LENGTH PL                                                          FLX 2600 */
			/*                                                                       FLX 2610 */
			xp = taum[k + n * 3 - 4] + taer[n] + tran_1.tcont[n - 1] +
				 tran_1.tmols[n - 1];
			/*                                                                       FLX 2630 */
			/*    X IS THE NORMAL PATH OPTICAL THICKNESS FOR A GIVEN LAYER           FLX 2640 */
			/*                                                                       FLX 2650 */
			x = xp * (model_5.zm[*ikmax - n] - model_5.zm[*ikmax - n - 1]) /
				path_1.pl[*ikmax - n - 1];
			omegak[n - 1] = (tran_1.taers[n - 1] + tran_1.tmols[n - 1]) / xp;
			/*                                                                       FLX 2680 */
			/*   USE TWO STREAM APPROXIMATION FOR THERMAL                            FLX 2690 */
			/*                                                                       FLX 2700 */
			/* L160: */
			if (omegak[n - 1] > .99999f)
			{
				goto L115;
			}
			aer1 = 1.f - omegak[n - 1];
			aer2 = 1.f - omegak[n - 1] * cosbar[n];
			aera = sqrt(aer1 / aer2);
			aeru = (1.f - aera) / 2.f;
			aerv = (aera + 1.f) / 2.f;
			aerc = sqrt(aer1 * 3.f * aer2);
			aercx = aerc * x;
			if (aercx < cnstns_1.bigexp)
			{
				ex1 = exp(-aercx);
			}
			else
			{
				ex1 = 1.f / cnstns_1.bignum;
			}
			ex2 = ex1 * ex1;
			deno = aerv * aerv - aeru * aeru * ex2;
			dnmo = (tran_1.btop[n - 1] - tran_1.btop[n]) / x / aerc * (aerv - aeru * ex2 - aera * ex1);
			dnm1 = aerv + aeru * ex2;
			eup[n - 1] = (tran_1.btop[n - 1] * dnm1 - dnmo - tran_1.btop[n] * ex1) / deno * aera;
			edn[n - 1] = (tran_1.btop[n] * dnm1 + dnmo - tran_1.btop[n - 1] * ex1) / deno * aera;
			if (eup[n - 1] < 0.f)
			{
				eup[n - 1] = 0.f;
			}
			if (edn[n - 1] < 0.f)
			{
				edn[n - 1] = 0.f;
			}
			ref[n - 1] = aeru * aerv * (1.f - ex2) / deno;
			tdf[n - 1] = (aerv - aeru) / deno * ex1;
			goto L114;
		L115:
			tdf[n - 1] = 1.f / (sqrt(3.f) * (1.f - cosbar[n]) / 2.f * x + 1.f);
			ref[n - 1] = 1.f - tdf[n - 1];
			eup[n - 1] = 0.f;
			edn[n - 1] = 0.f;
		L114:
			if (card1_1.iemsct == 2)
			{
				/*                                                                       FLX 3000 */
				/*     CALCULATE PARAMETERS FOR SOLAR HYBRID MODIFIED                    FLX 3010 */
				/*     DELTA EDDINGTON 2-STREAM APPROXIMATION                            FLX 3020 */
				/*                                                                       FLX 3030 */
				smu = cszen[n];
				b0 = bets[n - 1];
				ome0 = omegak[n - 1];
				if (ome0 >= .999999f)
				{
					ome0 = .999999f;
				}
				/*                                                                       FLX 3080 */
				/*      OME0 TEST MAY BE MACHINE DEPENDENT                               FLX 3090 */
				/*                                                                       FLX 3100 */
				/*                                                                       FLX 3110 */
				/*      RECODED AS BS  FC AND AS*EXP(SK*X)  FOR IMPROVED                 FLX 3120 */
				/*      ACCURACY IN SOLAR FLUX CALCULATIONS FOR LARGE X                  FLX 3130 */
				/*      ( NON MACHINE DEPENDANT )                                        FLX 3140 */
				/*                                                                       FLX 3150 */
				g = cosbar[n];
				d__1 = (double)g;
				q = (1.f - pow_dd(&d__1, &c_b1716) * (1.f - smu)) * 4.f;
				d__1 = (double)g;
				d__2 = (double)g;
				gm1 = (7.f - pow_dd(&d__1, &c_b1716) * 3.f - ome0 * (g * 3.f + 4.f) + ome0 * pow_dd(&d__2, &c_b1716) * (b0 * 4.f + g * 3.f)) / q;
				d__1 = (double)g;
				d__2 = (double)g;
				gm2 = -(1.f - pow_dd(&d__1, &c_b1716) - ome0 * (4.f - g * 3.f) - ome0 * pow_dd(&d__2, &c_b1716) * (b0 * 4.f + g * 3.f - 4.f)) / q;
				if (gm2 == 0.f)
				{
					gm2 = 1e-10f;
				}
				sk = sqrt(gm1 * gm1 - gm2 * gm2);
				cs = ome0 * (bets[n - 1] / smu - gm1 * bets[n - 1] - gm2 * (1.f - bets[n - 1])) * (smu * smu / (1.f - sk * sk * smu * smu));
				ys = cs * (gm1 + 1.f / smu) - ome0 * bets[n - 1];
				/* C    E1=YS/(GM1-SK)                                                    FLX 3270 */
				/* C    E2=-CS                                                            FLX 3280 */
				/* C    E3=(GM1+SK)/(SK-GM1)                                              FLX 3290 */
				/* C    E4=1.                                                             FLX 3300 */
				/* CC   BS=(E1*EXP(SK*X)+E2*EXP(-X/SMU))/(E3*EXP(SK*X)+E4*EXP(-SK*X))     FLX 3310 */
				/* CC   AS=(BS*(GM1+SK)+YS)/(SK-GM1)                                      FLX 3320 */
				/*                                                                       FLX 3330 */
				/*    CALCULATE UPWARD & DOWNWARD FLUX, EACH LAYER ALONE                 FLX 3340 */
				/*                                                                       FLX 3350 */
				/* CC   EUPS(N)=AS+BS+CS                                                  FLX 3360 */
				/* CC   EDNS(N)=(AS*(GM1-SK)*EXP(SK*X)+BS*(GM1+SK)*EXP(-SK*X)+            FLX 3370 */
				/* CC  2 YS*EXP(-X/SMU))/GM2                                              FLX 3380 */
				/*                                                                       FLX 3390 */
				/*     NEW SECTION                                                       FLX 3400 */
				/*                                                                       FLX 3410 */
				ektl = sk * x;
				if (ektl < cnstns_1.bigexp)
				{
					ekt = exp(-ektl);
				}
				else
				{
					ekt = 1.f / cnstns_1.bignum;
				}
				ekt2 = ekt * ekt;
				etmul = x / smu;
				if (etmul < cnstns_1.bigexp)
				{
					etmu = exp(-etmul);
				}
				else
				{
					etmu = 1.f / cnstns_1.bignum;
				}
				/* C    ASXP =-1.* ((GM1+SK)*E2*ETMU+YS*E4*EKT)/(E3+E4*EKT2)              FLX 3550 */
				gmpsk = gm1 + sk;
				gmmsk = gm1 - sk;
				denom = ekt2 * gmmsk - gmpsk;
				asxp = -gmmsk * (ys * ekt - gmpsk * cs * etmu) / denom;
				/* C    ASNEW=-1.* ((GM1+SK)*E2*ETMU*EKT+YS*E4*EKT2)/(E3+E4*EKT2)         FLX 3600 */
				asnew = (-gmpsk * cs * etmu * ekt + ys * ekt2) * -1.f / denom;
				/* C    BSNEW = (E1 + E2 * ETMU * EKT)/(E3 + E4*EKT2)                     FLX 3620 */
				bsnew = (ys - cs * etmu * ekt * gmmsk) / denom;
				eups[n - 1] = asnew + bsnew + cs;
				/* C    EDNS(N)=(ASXP+BSNEW*(GM1+SK)*EXP(-SK*X)+                          FLX 3650 */
				/* C   2 YS*EXP(-X/SMU))/GM2                                              FLX 3660 */
				edns[n - 1] = (asxp + bsnew * gmpsk * ekt + ys * etmu) / gm2;
				fc = 1.f / cszen[n];
				/*                                                                       FLX 3690 */
				/*   REFS & TDFS ARE REFLECT & TRANSMITT FOR INDIVIDUAL LAYERS,SOLAR     FLX 3700 */
				/*                                                                       FLX 3710 */
				refs[n - 1] = eups[n - 1] * fc;
				xcszen = x / cszen[n];
				if (xcszen < cnstns_1.bigexp)
				{
					tdfs[n - 1] = edns[n - 1] * fc + exp(-xcszen);
				}
				else
				{
					tdfs[n - 1] = edns[n - 1] * fc;
				}
				eups[n - 1] = eups[n - 1] * *s0 * strn[m];
				edns[n - 1] = edns[n - 1] * *s0 * strn[m];
			}
			deno = 1.f - rupcn * ref[n - 1];
			denos = 1.f - rupcns * refs[n - 1];
			/*                                                                       FLX 3840 */
			/*    CALCULATE COMPOSITE FLUXES AND REFLECTANCES                        FLX 3850 */
			/*                                                                       FLX 3860 */
			/* L125: */
			eupcn = eup[n - 1] + (eupcn + edn[n - 1] * rupcn) * tdf[n - 1] /
									 deno;
			eupcns = eups[n - 1] + (eupcns + edns[n - 1] * rupcns) * tdfs[n - 1] / denos;
			rupcns = refs[n - 1] + tdfs[n - 1] * rupcns * tdfs[n - 1] / denos;
			/* L140: */
			rupcn = ref[n - 1] + tdf[n - 1] * rupcn * tdf[n - 1] / deno;
			eupc[n - 1] = eupcn;
			eupcs[n - 1] = eupcns;
			rupc[n - 1] = rupcn;
			rupcs[n - 1] = rupcns;
			/* L101: */
		}
		/* ***********************************************************************FLX 3960 */
		/* *    NOW ADD DOWNWARD FROM TOP LAYER (N=1)                            *FLX 3970 */
		/* ***********************************************************************FLX 3980 */
		edncn = 0.f;
		edncns = 0.f;
		dnf[k + 10] = edncn;
		upf[k + 10] = eupc[0];
		if (card1_1.iemsct == 2)
		{
			dnfs[k - 1] = edncns;
			upfs[k - 1] = eupcs[0];
		}
		rdncn = 0.f;
		rdncns = 0.f;
		i__1 = ng;
		for (n = 2; n <= i__1; ++n)
		{
			m = n - 1;
			deno = 1.f - rdncn * ref[m - 1];
			denos = 1.f - rdncns * refs[m - 1];
			/* L121: */
			edncn = edn[m - 1] + (edncn + eup[m - 1] * rdncn) * tdf[m - 1] /
									 deno;
			rdncn = ref[m - 1] + tdf[m - 1] * tdf[m - 1] * rdncn / deno;
			/* L132: */
			pefup = (eupc[n - 1] + edncn * rupc[n - 1]) / deno;
			pefdn = (edncn + eupc[n - 1] * rdncn) / deno;
			if (card1_1.iemsct == 2)
			{
				edncns = edns[m - 1] + (edncns + eups[m - 1] * rdncns) * tdfs[m - 1] / denos;
				rdncns = refs[m - 1] + tdfs[m - 1] * tdfs[m - 1] * rdncns /
										   denos;
				pefups = (eupcs[n - 1] + edncns * rupcs[n - 1]) / denos;
				pefdns = (edncns + eupcs[n - 1] * rdncns) / denos;
				upfs[k + n * 15 - 16] = pefups;
				dnfs[k + n * 15 - 16] = pefdns;
			}
			/* L120: */
			upf[k + n * 10] = pefup;
			dnf[k + n * 10] = pefdn;
			/* L130: */
		}
		dpj[k + ng * 3 - 4] = dpj[k + (ng - 1) * 3 - 4];
		i__1 = ng;
		for (n = 2; n <= i__1; ++n)
		{
			m = n - 1;
			if (k == 1)
			{
				umf[m] = (upf[k + m * 10] + upf[k + n * 10]) * .5f * dpj[k + m * 3 - 4];
				umfs[m] = (upfs[k + m * 15 - 16] + upfs[k + n * 15 - 16]) *
						  .5f * dpj[k + m * 3 - 4];
				dmf[m] = (dnf[k + m * 10] + dnf[k + n * 10]) * .5f * dpj[k + m * 3 - 4];
				dmfs[m] = (dnfs[k + m * 15 - 16] + dnfs[k + n * 15 - 16]) *
						  .5f * dpj[k + m * 3 - 4];
				dirst_1.umb[n - 1] = upf[k + n * 10] * dpj[k + n * 3 - 4];
				dirst_1.umbs[n - 1] = upfs[k + n * 15 - 16] * dpj[k + n * 3 -
																  4];
				dirst_1.dmb[m - 1] = dnf[k + m * 10] * dpj[k + m * 3 - 4];
				dirst_1.dmbs[m - 1] = dnfs[k + m * 15 - 16] * dpj[k + m * 3 -
																  4];
			}
			else
			{
				umf[m] += (upf[k + m * 10] + upf[k + n * 10]) * .5f * dpj[k + m * 3 - 4];
				umfs[m] += (upfs[k + m * 15 - 16] + upfs[k + n * 15 - 16]) *
						   .5f * dpj[k + m * 3 - 4];
				dmf[m] += (dnf[k + m * 10] + dnf[k + n * 10]) * .5f * dpj[k + m * 3 - 4];
				dmfs[m] += (dnfs[k + m * 15 - 16] + dnfs[k + n * 15 - 16]) *
						   .5f * dpj[k + m * 3 - 4];
				dirst_1.umb[n - 1] += upf[k + n * 10] * dpj[k + n * 3 - 4];
				dirst_1.umbs[n - 1] += upfs[k + n * 15 - 16] * dpj[k + n * 3 - 4];
				dirst_1.dmb[m - 1] += dnf[k + m * 10] * dpj[k + m * 3 - 4];
				dirst_1.dmbs[m - 1] += dnfs[k + m * 15 - 16] * dpj[k + m * 3 - 4];
			}
			/*                                                                       FLX 4520 */
			/*   TRNSD & TRNSU ARE CUMULATIVE DOWNWARD & UPWARD TRANSMISSION         FLX 4530 */
			/*                                                                       FLX 4540 */
			/* L117: */
		}
		/*                                                                       FLX 4560 */
		/*   FDNSRF IS THE DOWNWARD SOLAR FLUX AT THE SURFACE                    FLX 4570 */
		/*   FDNTRF IS THE DOWNWARD THERMAL FLUX AT THE SURFACE                  FLX 4580 */
		/*                                                                       FLX 4590 */
		if (k == 1)
		{
			*fdnsrf = dnfs[k + ng * 15 - 16] * dpj[k + nlayrs * 3 - 4];
			*fdntrf = dnf[k + ng * 10] * dpj[k + nlayrs * 3 - 4];
			fupsrf = upfs[k - 1] * dpj[k - 1];
			fuptrf = upf[k + 10] * dpj[k - 1];
		}
		else
		{
			*fdnsrf += dnfs[k + ng * 15 - 16] * dpj[k + nlayrs * 3 - 4];
			*fdntrf += dnf[k + ng * 10] * dpj[k + nlayrs * 3 - 4];
			fupsrf += upfs[k - 1] * dpj[k - 1];
			fuptrf += upf[k + 10] * dpj[k - 1];
		}
		/* C    IF(K.EQ.3)PRINT 1910,V,FDNSRF,FDNTRF,FUPSRF,FUPTRF                FLX 4710 */
		/* L1910: */
		/* CC   IF(K.EQ.3)WRITE(6,1920)FDNSRF,FDNTRF,FUPSRF,FUPTRF                FLX 4730 */
		/* L1920: */
		/* L100: */
	}
	dirst_1.umb[0] = fuptrf;
	dirst_1.umbs[0] = fupsrf;
	dirst_1.dmb[ng - 1] = *fdntrf;
	dirst_1.dmbs[ng - 1] = *fdnsrf;
	dirst_1.sun = *s0;
	return 0;
} /* flxadd_ */

/* Subroutine */ int mapms_(long *ml, long *ikmax, float *zm, float *aht,
							long *imap)
{
	/* System generated locals */
	long i__1, i__2;

	/* Local variables */
	static long i__, j;

	/*                                                                       MAP  110 */
	/*     ZM MODEL ALTITUDES                                                MAP  120 */
	/*     AHT LINE OF SIGHT ALTITUDES                                       MAP  130 */
	/*                                                                       MAP  140 */
	/*     MULTISCATERING SET UP LOOKING UP                                  MAP  150 */
	/*     GROUND TO SPACE AT 0 DEG                                          MAP  160 */
	/*                                                                       MAP  170 */
	/* Parameter adjustments */
	--imap;
	--aht;
	--zm;

	/* Function Body */
	i__1 = *ikmax;
	for (j = 1; j <= i__1; ++j)
	{
		i__2 = *ml;
		for (i__ = 1; i__ <= i__2; ++i__)
		{
			if (zm[i__] > aht[j])
			{
				goto L20;
			}
			imap[j] = i__;
			/* L10: */
		}
	L20:;
	}
	return 0;
} /* mapms_ */

double betabs_(float *u, float *g)
{
	/* Initialized data */

	static float u8[9] = {0.f, .1f, .2f, .3f, .4f, .5f, .6f, .8f, 1.f};
	static float a9[50] /* was [10][5] */ = {.5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f,
											 .5f, .5f, 0.f, .13979292889f, -.12019000482f, -.46017123188f,
											 -.406828796532f, -.3001541656f, -.553474414782f, -.626794663911f,
											 -.84678101f, -.406823676662f, 0.f, -1.5989873995f, -.2724219928f,
											 1.18747390274f, .49409050834f, -.35928947292f, .37397957743f,
											 .18057740986f, .50718036245f, .01406832224f, 0.f, 3.5184116963f,
											 .6385960123f, -2.081230849f, -1.0144699491f, .1589475781f,
											 -.74761782865f, -.37416958202f, -.374040109f, .1055607702f, 0.f,
											 -2.5592172257f, -.7459840146f, .85392041407f, .4272082373f,
											 4.9606046e-4f, .42711266606f, .32038683614f, .2136746594f,
											 -.2128054157f};

	/* Format strings */
	static char fmt_105[] = "(//,\002 THE VALUE FOR MU OF \002,f12.6,\002 IS"
							" > 1.0 ]]\002)";

	/* System generated locals */
	float ret_val;

	/* Builtin functions */
	long s_wsfe(cilist *), do_fio(long *, char *, long), e_wsfe(void);
	/* Subroutine */ int s_stop(char *, long);
	double pow_ri(float *, long *);

	/* Local variables */
	static long j;
	static float y3, y5, y6, y7, y8, y9;
	static long iq, jm1, iqp1;

	/* Fortran I/O blocks */
	static cilist io___1080 = {0, 16, 0, fmt_105, 0};

	/*                                                                       BET  110 */
	/*   FUNCTION BETABS SUPPLIES THE BACK SCATTER FRACTION FOR A GIVEN      BET  120 */
	/*   ASYMMETRY FACTOR AND COSINE OF ANGLE                                BET  130 */
	/*                                             A.E.R. 1986               BET  140 */
	/*                                                                       BET  150 */
	/*                                                                       BET  280 */
	/*     BACKSCATTERING INTERPOLATION                                      BET  290 */
	/*                                                                       BET  300 */
	iq = 0;
	if (*u < .1f)
	{
		iq = 1;
	}
	if (*u < .2f && *u >= .1f)
	{
		iq = 2;
	}
	if (*u < .3f && *u >= .2f)
	{
		iq = 3;
	}
	if (*u < .4f && *u >= .3f)
	{
		iq = 4;
	}
	if (*u < .5f && *u >= .4f)
	{
		iq = 5;
	}
	if (*u < .6f && *u >= .5f)
	{
		iq = 6;
	}
	if (*u < .8f && *u >= .6f)
	{
		iq = 7;
	}
	if (*u <= 1.f && *u >= .8f)
	{
		iq = 8;
	}
	if (iq == 0)
	{
		s_wsfe(&io___1080);
		do_fio(&c__1, (char *)&(*u), (long)sizeof(float));
		e_wsfe();
		s_stop((char *)" ERROR ***", (long)10);
	}
	/*                                                                       BET  450 */
	y5 = 0.f;
	y6 = 0.f;
	y7 = 0.f;
	iqp1 = iq + 1;
	/*                                                                       BET  500 */
	for (j = 1; j <= 5; ++j)
	{
		jm1 = j - 1;
		y9 = a9[iq + j * 10 - 11] * pow_ri(g, &jm1);
		y8 = a9[iqp1 + j * 10 - 11] * pow_ri(g, &jm1);
		y3 = a9[j * 10 - 1] * pow_ri(g, &jm1);
		y7 += y9;
		y6 += y8;
		y5 += y3;
		/* L30: */
	}
	ret_val = y7 + (y6 - y7) * (*u - u8[iq - 1]) / (u8[iqp1 - 1] - u8[iq - 1]);
	/*                                                                       BET  610 */
	return ret_val;
} /* betabs_ */

/* Subroutine */ int c4dta_(float *c4l, float *v)
{
	static long l, iv;

	/* **  N2 CONTINUUM                                                      C4D  110 */
	*c4l = 0.f;
	if (*v < 2080.f)
	{
		return 0;
	}
	if (*v > 2740.f)
	{
		return 0;
	}
	iv = *v;
	l = (iv - 2080) / 5 + 1;
	*c4l = c4c8_1.c4[l - 1];
	return 0;
} /* c4dta_ */

/* Subroutine */ int c6dta_(float *c6l, float *v)
{
	/* System generated locals */
	float r__1, r__2;

	/*     CALCULATES MOLECULAR RAYLEIGH SCATTERING COEFFICIENT              C6D* 110 */
	/*     USES APPROXIMATION OF SHETTLE ET AL., 1980 (APPL OPT,2873-4)      C6D* 120 */
	/*     WITH THE DEPOLARIZATION = 0.0279 INSTED OF 0.035                  CD6* 130 */
	/*     INPUT: V = FREQUENCY IN WAVENUMBERS (CM-1)                        C6D* 140 */
	/*     OUTPUT: C6L = MOLECULAR SCATTERING COEFFICIENT (KM-1)             C6D* 150 */
	/*                   FOR TEMPERATURE 273K & PRESSURE = 1 ATM.            C6D* 160 */
	/*                                                                       C6D* 170 */
	/* Computing 4th power */
	r__1 = *v, r__1 *= r__1;
	/* Computing 2nd power */
	r__2 = *v;
	*c6l = r__1 * r__1 / (9.38076e18f - r__2 * r__2 * 1.08426e9f);
	return 0;
} /* c6dta_ */

/* Subroutine */ int c8dta_(float *c8l, float *v)
{
	static long n;
	static float xd;
	static long iv;
	static float xi;

	/* **  OZONE U.V + VISIBLE                                               C8D  110 */
	*c8l = 0.f;
	if (*v < 1.3e4f)
	{
		return 0;
	}
	if (*v > 5e4f)
	{
		return 0;
	}
	iv = *v;
	if (iv > 24200 && iv < 27500)
	{
		return 0;
	}
	xi = (*v - 1.3e4f) / 200.f + 1.f;
	if (iv >= 27500)
	{
		xi = (*v - 27500.f) / 500.f + 57.f;
	}
	n = xi + 1.001f;
	xd = xi - (float)n;
	*c8l = c4c8_1.c8[n - 1] + xd * (c4c8_1.c8[n - 1] - c4c8_1.c8[n - 2]);
	return 0;
} /* c8dta_ */

/* Subroutine */ int hertda_(float *herz, float *v)
{
	/* System generated locals */
	float r__1;

	/* Builtin functions */
	double log(double), exp(double);

	/* Local variables */
	static float corr, rlosch, yratio;

	/*                                                                       HER  110 */
	/*     HERZBERG O2 ABSORPTION                                            HER  120 */
	/*     HALL,1987 PRIVATE COMMUNICATION, BASED ON:                        HER  130 */
	/*                                                                       HER  140 */
	/*     REF. JOHNSTON ET.AL, JGR,89,11661-11665,1984                      HER  150 */
	/*         NICOLET, 1987 (RECENT STUDIES IN ATOMIC & MOLECULAR PROCESSES,HER  160 */
	/*                        PLEMUN PUBLISHING CORP, NY 1987)               HER  170 */
	/*     AND YOSHINO, ET.AL., 1988 (PREPRINT OF "IMPROVED ABSORPTION       HER  180 */
	/*         CROSS SECTIONS OF OXYGEN IN THE WAVELENGTH REGION 205-240NM   HER  190 */
	/*         OF THE HERZBERG CONTINUUM")                                   HER  200 */
	/*                                                                       HER  210 */
	/*                                                                       HER  230 */
	*herz = 0.f;
	if (*v <= 3.6e4f)
	{
		return 0;
	}
	/*                                                                       HER  260 */
	/*     EXTRAPOLATE SMOOTHLY THROUGH THE HERZBERG BAND REGION             HER  270 */
	/*     NOTE: HERZBERG BANDS ARE NOT CORRECTLY INCLUDED                   HER  280 */
	/*                                                                       HER  290 */
	corr = 0.f;
	if (*v <= 4e4f)
	{
		corr = (4e4f - *v) / 4e3f * 7.917e-27f;
	}
	/*                                                                       HER  320 */
	/*     CONVERSION TO ATM-CM /KM                                          HER  330 */
	/*                                                                       HER  340 */
	rlosch = 2.6868e19f;
	/*                                                                       HER  360 */
	/*     HALL'S NEW HERZBERG  (LEAST SQRS FIT, LN(P))                      HER  370 */
	/*                                                                       HER  380 */
	/*     YRATIO=2048.7/WL(I)  ****IN ANGSTOMS****                          HER  390 */
	/*           =.20487/WN(I)     IN MICRONS                                HER  400 */
	/*           =WCM(I)/48811.0   IN CM-1                                   HER  410 */
	/*                                                                       HER  420 */
	yratio = *v / 48811.f;
	/* Computing 2nd power */
	r__1 = log(yratio);
	*herz = yratio * 6.884e-24f * exp(r__1 * r__1 * -69.738f) - corr;
	*herz *= rlosch;
	return 0;
} /* hertda_ */

/* Subroutine */ int slf296_(float *v1c, float *sh2ot0)
{
	extern /* Subroutine */ int sint_(float *, float *, float *, long *, float *, float *);

	/*     LOADS SELF CONTINUUM  296K                                        SLF  110 */
	sint_(&sh2o_1.v1, v1c, &sh2o_1.dv, &sh2o_1.npt, sh2o_1.s296, sh2ot0);
	return 0;
} /* slf296_ */

/* Subroutine */ int slf260_(float *v1c, float *sh2ot1)
{
	extern /* Subroutine */ int sint_(float *, float *, float *, long *, float *, float *);

	/*     LOADS SELF CONTINUUM  260K                                        S26  110 */
	sint_(&s260_1.v1, v1c, &s260_1.dv, &s260_1.npt, s260_1.s260, sh2ot1);
	return 0;
} /* slf260_ */

/* Subroutine */ int frn296_(float *v1c, float *fh2o)
{
	extern /* Subroutine */ int sint_(float *, float *, float *, long *, float *, float *);

	/*     LOADS FOREIGN CONTINUUM  296K                                     FRN  110 */
	sint_(&fh2o_1.v1, v1c, &fh2o_1.dv, &fh2o_1.npt, fh2o_1.f296, fh2o);
	return 0;
} /* frn296_ */

/* Subroutine */ int sint_(float *v1, float *v1c, float *dv, long *npt, float *conti, float *conto)
{
	/* Builtin functions */
	double r_mod(float *, float *);

	/* Local variables */
	static long i__, imod;

	/*                                                                       SIN  110 */
	/*     INTERPOLATION  FOR CONTINUUM WITH LOWTRAN                         SIN  120 */
	/*                                                                       SIN  130 */
	/* Parameter adjustments */
	--conti;

	/* Function Body */
	*conto = 0.f;
	i__ = (*v1c - *v1) / *dv + 1.00001f;
	if (i__ >= *npt)
	{
		goto L10;
	}
	*conto = conti[i__];
	imod = r_mod(v1c, &c_b1750);
	if (imod > 0)
	{
		*conto = (conti[i__] + conti[i__ + 1]) / 2.f;
	}
L10:
	return 0;
} /* sint_ */

/* Subroutine */ int o3int_(float *v1c, float *v1, float *dv, long *npt, float *conti, float *conto)
{
	static long i__;

	/*                                                                       O3I  110 */
	/*     INTERPOLATION  FOR  O3 CONTINUUM WITH LOWTRAN                     O3I  120 */
	/*                                                                       O3I  130 */
	/* Parameter adjustments */
	--conti;

	/* Function Body */
	*conto = 0.f;
	i__ = (*v1c - *v1) / *dv + 1.00001f;
	if (i__ < 1)
	{
		goto L10;
	}
	if (i__ > *npt)
	{
		goto L10;
	}
	*conto = conti[i__];
L10:
	return 0;
} /* o3int_ */

/* Subroutine */ int o3hht0_(float *v, float *c__)
{
	extern /* Subroutine */ int o3int_(float *, float *, float *, long *,
									   float *, float *);

	/*                                                                       O3H  120 */
	o3int_(v, &o3hh0_1.v1s, &o3hh0_1.dvs, &o3hh0_1.npts, o3hh0_1.s, c__);
	return 0;
} /* o3hht0_ */

/* Subroutine */ int bo3hh0_(void)
{
	return 0;
} /* bo3hh0_ */

/* >    BLOCK DATA                                                        O30  110 */
/*                                                                       O30  120 */
/*                                                                       O30  130 */
/*     O3HH0 CONTAINS O3 HARTLEY HUGGINS CROSS SECTIONS FOR 273K         O30  140 */
/*               UNITS OF (CM**2/MOL)*1.E-20                             O30  150 */
/*                                                                       O30  160 */
/*     NOW INCLUDES MOLINA & MOLINA AT 273K WITH THE TEMPERATURE         O30  170 */
/*     DEPENDENCE DETERMINED FROM THE 195K HARVARD MEASUREMENTS,         O30  180 */
/*     EMPLOYING THE BASS ALGORITHM (CO(1+C1*T+C2*T2); THIS IS           O30  190 */
/*     ONLY FOR THE WAVELENGTH RANGE FROM .34 TO .35 MICRONS;            O30  200 */
/*     OTHERWISE, THE BASS DATA ALONE HAVE BEEN EMPLOYED BETWEEN         O30  210 */
/*     .34 AND .245 MICRONS.                                             O30  220 */
/*                                                                       O30  230 */
/*     NEW T-DEPENDENT X-SECTIONS BETWEEN .345 AND .36 MICRONS           O30  240 */
/*     HAVE NOW BEEN ADDED, BASED ON WORK BY CACCIANI, DISARRA           O30  250 */
/*     AND FIOCCO, UNIVERSITY OF ROME, 1987.  QUADRATIC TEMP             O30  260 */
/*     HAS BEEN DERIVED, AS ABOVE.                                       O30  270 */
/*                                                                       O30  280 */
/*     MOLINA & MOLINA HAVE AGAIN BEEN USED BETWEEN .245 AND .185        O30  290 */
/*     MICRONS (NO TEMPERATURE DEPENDENCE)                               O30  300 */
/*                                                                       O30  310 */
/*     AGREEMENT AMONGST THE FOUR DATA SETS IS REASONABLE (<10%)         O30  320 */
/*     AND OFTEN EXCELLENT (0-3%)                                        O30  330 */
/*                                                                       O30  340 */
/*                                                                       O30  350 */
/*                                                                       O30  450 */
/*     DATA V1C  /27370./,V2C  /29400./,DVC  /5./,NC  /407/ INN & TANAKA O30  460 */
/*         DATA FROM INN & TANAKA, HANDBOOK OF GEOPHYSICS, 1957, P 16-24 O30  470 */
/*                LINEARLY INTERPOLATED BY SAC, JUNE 1985                O30  480 */
/*                CONVERSION: (I&T)/(LOSCHMIDT 1 1987*1.2)               O30  490 */
/*                                                                       O30  500 */
/*     DATA V1C /29405./, V2C /40800./ ,DVC /5./, NC /2280/  BASS        O30  510 */
/*         DATA FROM BASS, JUNE 1985                                     O30  520 */
/*                                                                       O30  530 */
/*                                                                       O30  550 */
/*    X 2.08858E-03, 1.98947E-03, 1.89037E-03, 1.79126E-03, 1.69215E-03, O30  570 */
/*     THIS LINE OF DATA HAS BEEN REPLACED BY MONTONICALLY DECREASING    O30  580 */
/*     VALUES                                                            O30  590 */
/*    X 1.64187E-01, 1.69368E-01, 1.74549E-01, 1.79731E-01, 1.84912E-01, O30 1450 */
/*      1.90094E-01, 1.95275E-01/                                        O30 1460 */
/*   THE VALUE AT 29400. HAS BEEN CHANGED TO PROVIDE A SMOOTH TRANSITION O30 1470 */
/*    X 1.90094E-01, 1.85275E-01/                                        O30 1480 */
/*                                                                       O30 1510 */
/*                                                                       O30 1520 */
/*    FOLLOWING DATA ARE FROM BASS JUNE 1985                             O30 1530 */
/*                                                                       O30 1540 */
/*                                                                       O30 6400 */

/* Subroutine */ int o3hht1_(float *v, float *c__)
{
	extern /* Subroutine */ int o3int_(float *, float *, float *, long *,
									   float *, float *);

	/*     SUBROUTINE O3HHT1(V1C,V2C,DVC,NPTC,C)                             OT1  110 */
	/*                                                                       OT1  130 */
	o3int_(v, &o3hh1_1.v1s, &o3hh1_1.dvs, &o3hh1_1.npts, o3hh1_1.s, c__);
	/*                                                                       OT1  150 */
	return 0;
} /* o3hht1_ */

/* Subroutine */ int bo3hh1_(void)
{
	return 0;
} /* bo3hh1_ */

/* >    BLOCK DATA                                                        O31  110 */
/*                                                                       O31  120 */
/*     RATIO (C1/C0)                                                     O31  130 */
/*     DATA FROM BASS 1985                                               O31  140 */
/*                                                                       O31  150 */
/*     NOW INCLUDES MOLINA & MOLINA AT 273K WITH THE TEMPERATURE         O31  160 */
/*     DEPENDENCE DETERMINED FROM THE 195K HARVARD MEASUREMENTS,         O31  170 */
/*     EMPLOYING THE BASS ALGORITHM (CO(1+C1*T+C2*T2); THIS IS           O31  180 */
/*     ONLY FOR THE WAVELENGTH RANGE FROM .34 TO .35 MICRONS;            O31  190 */
/*     OTHERWISE, THE BASS DATA ALONE HAVE BEEN EMPLOYED BETWEEN         O31  200 */
/*     .34 AND .245 MICRONS.                                             O31  210 */
/*                                                                       O31  220 */
/*     NEW T-DEPENDENT X-SECTIONS BETWEEN .345 AND .36 MICRONS           O31  230 */
/*     HAVE NOW BEEN ADDED, BASED ON WORK BY CACCIANI, DISARRA           O31  240 */
/*     AND FIOCCO, UNIVERSITY OF ROME, 1987.  QUADRATIC TEMP             O31  250 */
/*     HAS BEEN DERIVED, AS ABOVE.                                       O31  260 */
/*                                                                       O31  270 */
/*     AGREEMENT AMONGST THE FOUR DATA SETS IS REASONABLE (<10%)         O31  280 */
/*     AND OFTEN EXCELLENT (0-3%)                                        O31  290 */
/*                                                                       O31  300 */
/*                                                                       O31  310 */
/*                                                                       O31  410 */
/*     DATA V1C /29405./, V2C /40800./ ,DVC /5./, NC /2280/   BASS       O31  420 */
/*                                                                       O31  440 */

/* Subroutine */ int o3hht2_(float *v, float *c__)
{
	extern /* Subroutine */ int o3int_(float *, float *, float *, long *,
									   float *, float *);

	/*                                                                       OT2  120 */
	o3int_(v, &o3hh2_1.v1s, &o3hh2_1.dvs, &o3hh2_1.npts, o3hh2_1.s, c__);
	/*                                                                       OT2  140 */
	return 0;
} /* o3hht2_ */

/* Subroutine */ int bo3hh2_(void)
{
	return 0;
} /* bo3hh2_ */

/* >    BLOCK DATA                                                        O32  110 */
/*                                                                       O32  120 */
/*     RATIO (C2/C0)                                                     O32  130 */
/*     DATA FROM BASS 1985                                               O32  140 */
/*                                                                       O32  150 */
/*     NOW INCLUDES MOLINA & MOLINA AT 273K WITH THE TEMPERATURE         O32  160 */
/*     DEPENDENCE DETERMINED FROM THE 195K HARVARD MEASUREMENTS,         O32  170 */
/*     EMPLOYING THE BASS ALGORITHM (CO(1+C1*T+C2*T2); THIS IS           O32  180 */
/*     ONLY FOR THE WAVELENGTH RANGE FROM .34 TO .35 MICRONS;            O32  190 */
/*     OTHERWISE, THE BASS DATA ALONE HAVE BEEN EMPLOYED BETWEEN         O32  200 */
/*     .34 AND .245 MICRONS.                                             O32  210 */
/*                                                                       O32  220 */
/*     NEW T-DEPENDENT X-SECTIONS BETWEEN .345 AND .36 MICRONS           O32  230 */
/*     HAVE NOW BEEN ADDED, BASED ON WORK BY CACCIANI, DISARRA           O32  240 */
/*     AND FIOCCO, UNIVERSITY OF ROME, 1987.  QUADRATIC TEMP             O32  250 */
/*     HAS BEEN DERIVED, AS ABOVE.                                       O32  260 */
/*                                                                       O32  270 */
/*     AGREEMENT AMONGST THE FOUR DATA SETS IS REASONABLE (<10%)         O32  280 */
/*     AND OFTEN EXCELLENT (0-3%)                                        O32  290 */
/*                                                                       O32  300 */
/*                                                                       O32  310 */
/*                                                                       O32  410 */
/*     DATA V1C /29405./, V2C /40800./ ,DVC /5./, NC /2280/   BASS       O32  420 */
/*                                                                       O32  440 */

/* Subroutine */ int o3uv_(float *v, float *c__)
{
	static long i__;
	static float c0, am, vr;

	/*                                                                       O3V  120 */
	/*     INTERPOLATION  FOR  O3 CONTINUUM WITH LOWTRAN                     O3V  130 */
	/*                                                                       O3V  140 */
	*c__ = 0.f;
	i__ = (*v - o3uvf_1.v1) / o3uvf_1.dv + 1.00001f;
	if (i__ < 1)
	{
		goto L10;
	}
	if (i__ > o3uvf_1.npt)
	{
		goto L10;
	}
	vr = i__ * o3uvf_1.dv + o3uvf_1.v1;
	if (vr <= *v + .1f && vr >= *v - .1f)
	{
		goto L5;
	}
	if (i__ == o3uvf_1.npt)
	{
		i__ = o3uvf_1.npt - 1;
	}
	am = (o3uvf_1.s[i__] - o3uvf_1.s[i__ - 1]) / o3uvf_1.dv;
	c0 = o3uvf_1.s[i__ - 1] - am * vr;
	*c__ = am * *v + c0;
	goto L10;
L5:
	*c__ = o3uvf_1.s[i__ - 1];
L10:
	/*                                                                       O3V  280 */
	return 0;
} /* o3uv_ */

/* Subroutine */ int o3uvfd_(void)
{
	return 0;
} /* o3uvfd_ */

/* >    BLOCK DATA                                                        O3F  110 */
/*                                                                       O3F  130 */
/*        OZONE UV  VISIBLE ABSORPTION COEFFICIENTS                      O3F  140 */
/*                     (CM-ATM)-1                                        O3F  150 */
/*     DATA DERIVED FROM MOLINA & MOLINA, JGR,91,14501-14508,1986.       O3F  160 */
/*     VALUES BETWEEN 245 AND 185NM (40800 AND 54054CM-1) USED AS        O3F  170 */
/*     DIRECT AVERAGE WITH NO TEMPERATURE DEPENDENCE.                    O3F  180 */
/*                                                                       O3F  190 */
/*     O3 LOCATION  1    V =  40800  CM-1                                O3F  200 */
/*     O3 LOCATION  133  V =  54054  CM-1                                O3F  210 */
/*        DV = 100  CM-1                                                 O3F  220 */
/*                                                                       O3F  230 */

/* Subroutine */ int o2cont_(float *v, float *sigma, float *alpha, float *beta)
{
	/* System generated locals */
	float r__1;

	/* Local variables */
	static float a, b, c__;
	extern /* Subroutine */ int o2int_(float *, float *, float *, long *,
									   float *, float *, float *, float *, float *, float *);

	/*                                                                       O2C  110 */
	/*     THIS ROUTINE IS DRIVEN BY FREQUENCY, RETURNING ONLY THE           O2C  120 */
	/*     O2 COEFFICIENTS, INDEPENDENT OF TEMPERATURE.                      O2C  130 */
	/*                                                                       O2C  140 */
	/*  *******************************************************************  O2C  150 */
	/*  *  THESE COMMENTS APPLY TO THE COLUME ARRAYS FOR:                 *  O2C  160 */
	/*  *       PBAR*UBAR(O2)                                             *  O2C  170 */
	/*  *       PBAR*UBAR(O2)*DT                                          *  O2C  180 */
	/*  *   AND PBAR*UBAR(O2)*DT*DT    WHERE:  DT=TBAR-220.               *  O2C  190 */
	/*  *  THAT HAVE BEEN COMPILED IN OTHER PARTS OF THE LOWTRAN CODE     *  O2C  200 */
	/*  *                                                                 *  O2C  210 */
	/*  *  LOWTRAN7 COMPATIBLE:                                           *  O2C  220 */
	/*  *  O2 CONTINUUM SUBROUTINE FOR 1395-1760CM-1                      *  O2C  230 */
	/*  *  MODIFIED BY G.P. ANDERSON, APRIL '88                           *  O2C  240 */
	/*  *                                                                 *  O2C  250 */
	/*  *  THE EXPONENTIAL TEMPERATURE EMPLOYED IN THE FASCOD2 ALGORITHM  *  O2C  260 */
	/*  *  (SEE BELOW) IS NOT READILY SUITABLE FOR LOWTRAN.  THEREFORE    *  O2C  270 */
	/*  *  THE EXPONENTIALS HAVE BEEN LINEARLY EXPANDED, KEEPING ONLY THE *  O2C  280 */
	/*  *  LINEAR AND QUADRATIC TERMS:                                    *  O2C  290 */
	/*  *                                                                 *  O2C  300 */
	/*  *  EXP(A*DT)=1.+ A*DT + (A*DT)**2/2. + ....                       *  O2C  310 */
	/*  *                                                                 *  O2C  320 */
	/*  *     EXP(B*DT*DT)=1.+ B*DT*DT + (B*DT*DT)**2/2. + ....           *  O2C  330 */
	/*  *                                                                 *  O2C  340 */
	/*  *  THE PRODUCT OF THE TWO TERMS IS:                               *  O2C  350 */
	/*  *                                                                 *  O2C  360 */
	/*  *     (1. + A*DT + (A*A/2. + B)*DT*DT )                           *  O2C  370 */
	/*  *                                                                 *  O2C  380 */
	/*  *  THIS EXPANSION ONLY WORKS WELL FOR SMALL VALUES OF X IN EXP(X) *  O2C  390 */
	/*  *                                                                 *  O2C  400 */
	/*  *  SINCE DT = T-220., THE APPROXIMATION IS VERY GOOD UNTIL        *  O2C  410 */
	/*  *  T.GT.260. OR DT.GT.40.   AT T=280, THE MAXIMUM ERRORS ARE STILL*  O2C  420 */
	/*  *  LESS THAN 10% BUT AT T=300, THOSE ERRORS ARE AS LARGE AS 20%   *  O2C  430 */
	/*  *******************************************************************  O2C  440 */
	/*                                                                       O2C  450 */
	/*     THE FOLLOWING COMMENTS ARE EXCERPTED DIRECTLY FROM FASCOD2        O2C  460 */
	/*                                                                       O2C  470 */
	/*      THIS SUBROUTINE CONTAINS THE ROGERS AND WALSHAW                  O2C  480 */
	/*      EQUIVALENT COEFFICIENTS DERIVED FROM THE THEORETICAL             O2C  490 */
	/*      VALUES SUPPLIED BY ROLAND DRAYSON. THESE VALUES USE              O2C  500 */
	/*      THE SAME DATA AS TIMOFEYEV AND AGREE WITH TIMOFEYEV'S RESULTS.   O2C  510 */
	/*      THE DATA ARE IN THE FORM OF STRENGTHS(O2SO) AND TWO              O2C  520 */
	/*      COEFFICIENTS (O2A & O2B),  WHICH ARE USED TO CORRECT FOR         O2C  530 */
	/*      TEMPERATURE. THE DEPENDENCY ON PRESSURE SQUARED                  O2C  540 */
	/*      IS CONTAINED IN THE P*WO2 PART OF THE CONSTANT.                  O2C  550 */
	/*      NOTE THAT SINCE THE COEFFICIENTS ARE FOR AIR, THE                O2C  560 */
	/*      THE STRENGTHS ARE DIVIDED BY THE O2 MIXING RATIO FOR             O2C  570 */
	/*      DRY AIR OF 0.20946 (THIS IS ASSUMED CONSTANT).                   O2C  580 */
	/*      ORIGINAL FORMULATION OF THE COEFFICIENTS WAS BY LARRY GORDLEY.   O2C  590 */
	/*      THIS VERSION WRITTEN BY EARL THOMPSON, JULY 1984.                O2C  600 */
	/*                                                                       O2C  610 */
	/*                                                                       O2C  620 */
	*sigma = 0.f;
	*alpha = 0.f;
	*beta = 0.f;
	if (*v < 1395.f)
	{
		goto L30;
	}
	if (*v > 1760.f)
	{
		goto L30;
	}
	/*                                                                       O2C  700 */
	/*                                                                       O2C  710 */
	o2int_(v, &o2c_1.v1o2, &o2c_1.dvo2, &o2c_1.npto2, &c__, o2c_1.o2s0, &a,
		   o2c_1.o2a, &b, o2c_1.o2b);
	/*                                                                       O2C  730 */
	/*                                                                       O2C  740 */
	/*                                                                       O2C  750 */
	/*     OLD 'FASCOD2' TEMPERATURE DEPENDENCE USING BLOCK DATA ARRAYS      O2C  760 */
	/*                                                                       O2C  770 */
	/*     C(J)=O2S0(I)* EXP(O2A(I)*TD+O2B(I)*TD*TD) /(0.20946*VJ)           O2C  780 */
	/*                                                                       O2C  790 */
	/*     NEW COEFFICIENT DEFINITIONS FOR LOWTRAN FORMULATION               O2C  800 */
	/*                                                                       O2C  810 */
	*alpha = a;
	/* Computing 2nd power */
	r__1 = a;
	*beta = r__1 * r__1 / 2.f + b;
	*sigma = c__ / .20946f;
/*                                                                       O2C  850 */
/*     NEW 'LOWTRAN7' TEMPERATURE DEPENDENCE                             O2C  860 */
/*                                                                       O2C  870 */
/*     THIS WOULD BE THE CODING FOR THE LOWTRAN7 FORMULATION, BUT        O2C  880 */
/*       BECAUSE THE T-DEPENDENCE IS INCLUDED IN THE AMOUNTS, ONLY       O2C  890 */
/*       THE COEFFICIENTS (SIGMA, ALPHA & BETA) ARE BEING RETURNED       O2C  900 */
/*                                                                       O2C  910 */
/*     C(J)=SIGMA*(1.+ALPHA*TD+BETA*TD*TD)                               O2C  920 */
/*                                                                       O2C  930 */
L30:
	return 0;
} /* o2cont_ */

/* Subroutine */ int o2int_(float *v1c, float *v1, float *dv, long *npt, float *c__, float *carray, float *a, float *aarray, float *b, float *barray)
{
	static long i__;

	/*                                                                       O2I  110 */
	/*     INTERPOLATION FOR O2 PRESSURE INDUCED CONTINUUM, NECESSARY FOR    O2I  120 */
	/*          LOWTRAN7 FORMULATION  (MODELED AFTER THE LOWTRAN UV-O3 BANDS)O2I  130 */
	/*                                                                       O2I  140 */
	/* Parameter adjustments */
	--barray;
	--aarray;
	--carray;

	/* Function Body */
	*c__ = 0.f;
	*a = 0.f;
	*b = 0.f;
	i__ = (*v1c - *v1) / *dv + 1.00001f;
	if (i__ < 1)
	{
		goto L10;
	}
	if (i__ > *npt)
	{
		goto L10;
	}
	*c__ = carray[i__];
	*a = aarray[i__];
	*b = barray[i__];
L10:
	return 0;
} /* o2int_ */

/* Subroutine */ int bo2c_(void)
{
	return 0;
} /* bo2c_ */

/* >    BLOCK DATA                                                        BO2  105 */
/*                                                                       BO2  110 */
/*     BLOCK DATA   (IDENTICAL TO BLOCK DATA IN FASCOD2)                 BO2  120 */
/*                                                                       BO2  130 */
/*                                                                       BO2  620 */

/* Subroutine */ int exabin_(void)
{
	/* Initialized data */

	static float rhzone[4] = {0.f, 70.f, 80.f, 99.f};
	static float elwcr[4] = {3.517e-4f, 3.74e-4f, 4.439e-4f, 9.529e-4f};
	static float elwcm[4] = {4.675e-4f, 6.543e-4f, .001166f, .003154f};
	static float elwcu[4] = {3.102e-4f, 3.802e-4f, 4.463e-4f, 9.745e-4f};
	static float elwct[4] = {1.735e-4f, 1.82e-4f, 2.02e-4f, 2.408e-4f};
	static float aflwc = .01295f;
	static float rflwc = .001804f;
	static float culwc = .007683f;
	static float aslwc = .004509f;
	static float stlwc = .005272f;
	static float sclwc = .004177f;
	static float snlwc = .007518f;
	static float bslwc = 1.567e-4f;
	static float fvlwc = 5.922e-4f;
	static float avlwc = 1.675e-4f;
	static float mdlwc = 4.775e-4f;

	/* System generated locals */
	long i__1;

	/* Builtin functions */
	double log(double), exp(double);

	/* Local variables */
	static float a;
	static long i__, m, n;
	static float x, y, a1, a2, e1, e2, x1, x2, y2, y1, z2, z1, ec;
	static long ic, nb, ii, ne;
	static float zk;
	static long ita, itc;
	static float wrh;
	static long itas;

	/*                                                                       EXA  110 */
	/*      LOADS EXTINCTION, ABSORPTION AND ASYMMETRY COEFFICIENTS          EXA  120 */
	/*      FOR THE FOUR AEROSOL ALTITUDE REGIONS                            EXA  130 */
	/*                                                                       EXA  140 */
	/*      MODIFIED FOR ASYMMETRY - JAN 1986 (A.E.R. INC.)                  EXA  150 */
	/*                                                                       EXA  160 */
	/*                                                                       EXA  240 */
	for (i__ = 1; i__ <= 4; ++i__)
	{
		/* L2: */
		_BLNK__5.awccon[i__ - 1] = 0.f;
	}
	for (i__ = 1; i__ <= 47; ++i__)
	{
		/* L5: */
		_BLNK__5.vx0[i__ - 1] = extd_1.vx2[i__ - 1];
	}
	/* C    I1=1                                                              EXA  570 */
	nb = 1;
	ne = 46;
	/*                                                                       EXA  600 */
	/*     47 VALUE CALCULATED IN AEREXT                                     EXA  610 */
	/*                                                                       EXA  620 */
	/* C    IF (IHAZE.EQ.7) I1=2                                              EXA  630 */
	/* C    IF(IHAZE.EQ.3)  I1 = 2                                            EXA  640 */
	for (m = 1; m <= 4; ++m)
	{
		if (card2d_1.ireg[m - 1] != 0)
		{
			goto L185;
		}
		ita = _BLNK__5.ich[m - 1];
		itc = _BLNK__5.ich[m - 1] - 7;
		itas = ita;
		if (card2d_1.iregc[m - 1] != 0)
		{
			goto L100;
		}
		/* L12: */
		wrh = _BLNK__5.w[14];
		if (_BLNK__5.ich[m - 1] == 6 && m != 1)
		{
			wrh = 70.f;
		}
		/*     THIS CODING  DOES NOT ALLOW TROP RH DEPENDENT  ABOVE EH(7,I)      EXA  740 */
		/*     DEFAULTS TO TROPOSPHERIC AT 70. PERCENT                           EXA  750 */
		for (i__ = 2; i__ <= 4; ++i__)
		{
			if (wrh < rhzone[i__ - 1])
			{
				goto L15;
			}
			/* L10: */
		}
		i__ = 4;
	L15:
		ii = i__ - 1;
		if (wrh > 0.f && wrh < 99.f)
		{
			x = log(100.f - wrh);
		}
		x1 = log(100.f - rhzone[ii - 1]);
		x2 = log(100.f - rhzone[i__ - 1]);
		if (wrh >= 99.f)
		{
			x = x2;
		}
		if (wrh <= 0.f)
		{
			x = x1;
		}
		/* L17: */
		i__1 = ne;
		for (n = nb; n <= i__1; ++n)
		{
			ita = itas;
			if (ita == 3 && m == 1)
			{
				goto L18;
			}
			_BLNK__5.absc[m + n * 5 - 6] = 0.f;
			_BLNK__5.extc[m + n * 5 - 6] = 0.f;
			_BLNK__5.asym[m + n * 5 - 6] = 0.f;
			if (ita > 6)
			{
				goto L45;
			}
			if (ita <= 0)
			{
				goto L80;
			}
		L18:
			if (n >= 41 && ita == 3)
			{
				ita = 4;
			}
			/*     RH DEPENDENT AEROSOLS                                             EXA  950 */
			switch (ita)
			{
			case 1:
				goto L20;
			case 2:
				goto L20;
			case 3:
				goto L22;
			case 4:
				goto L25;
			case 5:
				goto L30;
			case 6:
				goto L35;
			}
		L20:
			y2 = log(extd_1.rurext[n + i__ * 47 - 48]);
			y1 = log(extd_1.rurext[n + ii * 47 - 48]);
			z2 = log(extd_1.rurabs[n + i__ * 47 - 48]);
			z1 = log(extd_1.rurabs[n + ii * 47 - 48]);
			a2 = log(extd_1.rursym[n + i__ * 47 - 48]);
			a1 = log(extd_1.rursym[n + ii * 47 - 48]);
			e2 = log(elwcr[i__ - 1]);
			e1 = log(elwcr[ii - 1]);
			goto L40;
		L22:
			if (m > 1)
			{
				goto L25;
			}
			a2 = log(extd_1.ocnsym[n + i__ * 47 - 48]);
			a1 = log(extd_1.ocnsym[n + ii * 47 - 48]);
			a = a1 + (a2 - a1) * (x - x1) / (x2 - x1);
			_BLNK__5.asym[m + n * 5 - 6] = exp(a);
			e2 = log(elwcm[i__ - 1]);
			e1 = log(elwcm[ii - 1]);
			/*                                                                       EXA 1130 */
			/*     NAVY MARITIME AEROSOL CHANGES TO MARINE IN MICROWAVE              EXA 1140 */
			/*     NO NEED TO DEFINE EQUIVALENT WATER                                EXA 1150 */
			/*                                                                       EXA 1160 */
			goto L80;
		L25:
			y2 = log(extd_1.ocnext[n + i__ * 47 - 48]);
			y1 = log(extd_1.ocnext[n + ii * 47 - 48]);
			z2 = log(extd_1.ocnabs[n + i__ * 47 - 48]);
			z1 = log(extd_1.ocnabs[n + ii * 47 - 48]);
			a2 = log(extd_1.ocnsym[n + i__ * 47 - 48]);
			a1 = log(extd_1.ocnsym[n + ii * 47 - 48]);
			e2 = log(elwcm[i__ - 1]);
			e1 = log(elwcm[ii - 1]);
			goto L40;
		L30:
			y2 = log(extd_1.urbext[n + i__ * 47 - 48]);
			y1 = log(extd_1.urbext[n + ii * 47 - 48]);
			z2 = log(extd_1.urbabs[n + i__ * 47 - 48]);
			z1 = log(extd_1.urbabs[n + ii * 47 - 48]);
			a2 = log(extd_1.urbsym[n + i__ * 47 - 48]);
			a1 = log(extd_1.urbsym[n + ii * 47 - 48]);
			e2 = log(elwcu[i__ - 1]);
			e1 = log(elwcu[ii - 1]);
			goto L40;
		L35:
			y2 = log(extd_1.troext[n + i__ * 47 - 48]);
			y1 = log(extd_1.troext[n + ii * 47 - 48]);
			z2 = log(extd_1.troabs[n + i__ * 47 - 48]);
			z1 = log(extd_1.troabs[n + ii * 47 - 48]);
			a2 = log(extd_1.trosym[n + i__ * 47 - 48]);
			a1 = log(extd_1.trosym[n + ii * 47 - 48]);
			e2 = log(elwct[i__ - 1]);
			e1 = log(elwct[ii - 1]);
		L40:
			y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
			zk = z1 + (z2 - z1) * (x - x1) / (x2 - x1);
			a = a1 + (a2 - a1) * (x - x1) / (x2 - x1);
			_BLNK__5.absc[m + n * 5 - 6] = exp(zk);
			_BLNK__5.extc[m + n * 5 - 6] = exp(y);
			_BLNK__5.asym[m + n * 5 - 6] = exp(a);
			if (n == 1)
			{
				ec = e1 + (e2 - e1) * (x - x1) / (x2 - x1);
			}
			if (n == 1)
			{
				_BLNK__5.awccon[m - 1] = exp(ec);
			}
			goto L80;
		L45:
			if (ita > 19)
			{
				goto L75;
			}
			if (itc < 1)
			{
				goto L80;
			}
			switch (itc)
			{
			case 1:
				goto L50;
			case 2:
				goto L55;
			case 3:
				goto L80;
			case 4:
				goto L60;
			case 5:
				goto L65;
			case 6:
				goto L70;
			case 7:
				goto L65;
			case 8:
				goto L70;
			case 9:
				goto L60;
			case 10:
				goto L60;
			case 11:
				goto L70;
			case 12:
				goto L75;
			}
		L50:
			_BLNK__5.absc[m + n * 5 - 6] = extd_1.fg1abs[n - 1];
			_BLNK__5.extc[m + n * 5 - 6] = extd_1.fg1ext[n - 1];
			_BLNK__5.asym[m + n * 5 - 6] = extd_1.fg1sym[n - 1];
			if (n == 1)
			{
				_BLNK__5.awccon[m - 1] = aflwc;
			}
			goto L80;
		L55:
			_BLNK__5.absc[m + n * 5 - 6] = extd_1.fg2abs[n - 1];
			_BLNK__5.extc[m + n * 5 - 6] = extd_1.fg2ext[n - 1];
			_BLNK__5.asym[m + n * 5 - 6] = extd_1.fg2sym[n - 1];
			if (n == 1)
			{
				_BLNK__5.awccon[m - 1] = rflwc;
			}
			goto L80;
		L60:
			_BLNK__5.absc[m + n * 5 - 6] = extd_1.bstabs[n - 1];
			_BLNK__5.extc[m + n * 5 - 6] = extd_1.bstext[n - 1];
			_BLNK__5.asym[m + n * 5 - 6] = extd_1.bstsym[n - 1];
			if (n == 1)
			{
				_BLNK__5.awccon[m - 1] = bslwc;
			}
			goto L80;
		L65:
			_BLNK__5.absc[m + n * 5 - 6] = extd_1.avoabs[n - 1];
			_BLNK__5.extc[m + n * 5 - 6] = extd_1.avoext[n - 1];
			_BLNK__5.asym[m + n * 5 - 6] = extd_1.avosym[n - 1];
			if (n == 1)
			{
				_BLNK__5.awccon[m - 1] = avlwc;
			}
			goto L80;
		L70:
			_BLNK__5.absc[m + n * 5 - 6] = extd_1.fvoabs[n - 1];
			_BLNK__5.extc[m + n * 5 - 6] = extd_1.fvoext[n - 1];
			_BLNK__5.asym[m + n * 5 - 6] = extd_1.fvosym[n - 1];
			if (n == 1)
			{
				_BLNK__5.awccon[m - 1] = fvlwc;
			}
			goto L80;
		L75:
			_BLNK__5.absc[m + n * 5 - 6] = extd_1.dmeabs[n - 1];
			_BLNK__5.extc[m + n * 5 - 6] = extd_1.dmeext[n - 1];
			_BLNK__5.asym[m + n * 5 - 6] = extd_1.dmesym[n - 1];
			if (n == 1)
			{
				_BLNK__5.awccon[m - 1] = mdlwc;
			}
		L80:;
		}
		goto L185;
	L100:
		/* CC                                                                     EXA 1880 */
		/* CC       SECTION TO LOAD EXTINCTION AND ABSORPTION COEFFICIENTS        EXA 1890 */
		/* CC       FOR CLOUD AND OR RAIN MODELS                                  EXA 1900 */
		/* CC                                                                     EXA 1910 */
		i__1 = ne;
		for (n = nb; n <= i__1; ++n)
		{
			_BLNK__5.absc[m + n * 5 - 6] = 0.f;
			_BLNK__5.extc[m + n * 5 - 6] = 0.f;
			_BLNK__5.asym[m + n * 5 - 6] = 0.f;
			ic = card2_1.icld;
			switch (ic)
			{
			case 1:
				goto L125;
			case 2:
				goto L130;
			case 3:
				goto L135;
			case 4:
				goto L140;
			case 5:
				goto L145;
			case 6:
				goto L135;
			case 7:
				goto L145;
			case 8:
				goto L145;
			case 9:
				goto L125;
			case 10:
				goto L125;
			case 11:
				goto L125;
			}
		L125:
			_BLNK__5.absc[m + n * 5 - 6] = extd_1.ccuabs[n - 1];
			_BLNK__5.extc[m + n * 5 - 6] = extd_1.ccuext[n - 1];
			_BLNK__5.asym[m + n * 5 - 6] = extd_1.ccusym[n - 1];
			if (n == 1)
			{
				_BLNK__5.awccon[m - 1] = culwc;
			}
			goto L150;
		L130:
			_BLNK__5.absc[m + n * 5 - 6] = extd_1.calabs[n - 1];
			_BLNK__5.extc[m + n * 5 - 6] = extd_1.calext[n - 1];
			_BLNK__5.asym[m + n * 5 - 6] = extd_1.calsym[n - 1];
			if (n == 1)
			{
				_BLNK__5.awccon[m - 1] = aslwc;
			}
			goto L150;
		L135:
			_BLNK__5.absc[m + n * 5 - 6] = extd_1.cstabs[n - 1];
			_BLNK__5.extc[m + n * 5 - 6] = extd_1.cstext[n - 1];
			_BLNK__5.asym[m + n * 5 - 6] = extd_1.cstsym[n - 1];
			if (n == 1)
			{
				_BLNK__5.awccon[m - 1] = stlwc;
			}
			goto L150;
		L140:
			_BLNK__5.absc[m + n * 5 - 6] = extd_1.cscabs[n - 1];
			_BLNK__5.extc[m + n * 5 - 6] = extd_1.cscext[n - 1];
			_BLNK__5.asym[m + n * 5 - 6] = extd_1.cscsym[n - 1];
			if (n == 1)
			{
				_BLNK__5.awccon[m - 1] = sclwc;
			}
			goto L150;
		L145:
			_BLNK__5.absc[m + n * 5 - 6] = extd_1.cniabs[n - 1];
			_BLNK__5.extc[m + n * 5 - 6] = extd_1.cniext[n - 1];
			_BLNK__5.asym[m + n * 5 - 6] = extd_1.cnisym[n - 1];
			if (n == 1)
			{
				_BLNK__5.awccon[m - 1] = snlwc;
			}
		L150:;
		}
	L185:;
	}
	for (n = 1; n <= 47; ++n)
	{
		_BLNK__5.absc[n * 5 - 1] = 0.f;
		_BLNK__5.extc[n * 5 - 1] = 0.f;
		_BLNK__5.asym[n * 5 - 1] = 0.f;
		_BLNK__5.awccon[4] = 0.f;
		if (card2_1.icld == 18)
		{
			_BLNK__5.extc[n * 5 - 1] = cirr_1.ci32xt[n - 1];
			_BLNK__5.absc[n * 5 - 1] = cirr_1.ci32ab[n - 1];
			_BLNK__5.asym[n * 5 - 1] = cirr_1.ci32g[n - 1];
			_BLNK__5.awccon[4] = .003446f;
		}
		if (card2_1.icld == 19)
		{
			_BLNK__5.extc[n * 5 - 1] = cirr_1.cir2xt[n - 1];
			_BLNK__5.absc[n * 5 - 1] = cirr_1.cir2ab[n - 1];
			_BLNK__5.asym[n * 5 - 1] = cirr_1.cir2g[n - 1];
			_BLNK__5.awccon[4] = .05811f;
		}
		/* L200: */
	}
	return 0;
	/*                                                                       EXA 2430 */
} /* exabin_ */

/* Subroutine */ int aerext_(float *v)
{
	static long i__, n;
	static float v0, xd;
	static long mr;
	static float vxd, alam;
	extern double gamfog_(long *, float *, float *, float *);

	/*                                                                       AEX  110 */
	/*     INTERPOLATES AEROSOL EXTINCTION, ABSORPTION, AND ASYMMETRY        AEX  120 */
	/*     COEFFICIENTS FOR THE WAVENUMBER, V.                               AEX  130 */
	/*                                                                       AEX  140 */
	/*     MODIFIED FOR ASYMMETRY  - JAN 1986 (A.E.R. INC.)                  AEX  150 */
	/*                                                                       AEX  160 */
	/*                                                                       AEX  300 */
	for (i__ = 1; i__ <= 5; ++i__)
	{
		aer_2.extv[i__ - 1] = 0.f;
		aer_2.absv[i__ - 1] = 0.f;
		aer_2.asyv[i__ - 1] = 0.f;
		/* L5: */
	}
	if (*v <= 1e-5f)
	{
		goto L50;
	}
	if (*v <= 33.333f)
	{
		goto L30;
	}
	/* CC                                                                     AEX  380 */
	/* CC   COMPUTE INFRARED ATTENUATION COEFFICIENT                          AEX  390 */
	/* CC                                                                     AEX  400 */
	if (*v <= 50.f)
	{
		for (mr = 1; mr <= 5; ++mr)
		{
			_BLNK__4.extc[mr + 229] = gamfog_(&mr, &c_b1804, &aertm_2.taer[mr - 1], &_BLNK__4.awccon[mr - 1]);
			_BLNK__4.absc[mr + 229] = _BLNK__4.extc[mr + 229];
			_BLNK__4.asyc[mr + 229] = 0.f;
			/* L2: */
		}
	}
	/* C    IF (IHAZE.EQ.0) RETURN                                            AEX  480 */
	v0 = *v;
	alam = 1e4f / v0;
	for (n = 2; n <= 47; ++n)
	{
		xd = alam - _BLNK__4.vx2[n - 1];
		if (xd >= 0.f)
		{
			goto L10;
		}
		else
		{
			goto L15;
		}
	L10:;
	}
	n = 47;
L15:
	vxd = _BLNK__4.vx2[n - 1] - _BLNK__4.vx2[n - 2];
	for (i__ = 1; i__ <= 5; ++i__)
	{
		aer_2.extv[i__ - 1] = (_BLNK__4.extc[i__ + n * 5 - 6] - _BLNK__4.extc[i__ + (n - 1) * 5 - 6]) * xd / vxd + _BLNK__4.extc[i__ + n * 5 - 6];
		aer_2.absv[i__ - 1] = (_BLNK__4.absc[i__ + n * 5 - 6] - _BLNK__4.absc[i__ + (n - 1) * 5 - 6]) * xd / vxd + _BLNK__4.absc[i__ + n * 5 - 6];
		aer_2.asyv[i__ - 1] = (_BLNK__4.asyc[i__ + n * 5 - 6] - _BLNK__4.asyc[i__ + (n - 1) * 5 - 6]) * xd / vxd + _BLNK__4.asyc[i__ + n * 5 - 6];
		/* L20: */
	}
	return 0;
/* CC                                                                     AEX  630 */
L30:
	/* CC    COMPUTE MICROWAVE ATTENUATION COEFFICIENTS                       AEX  650 */
	/* CC                                                                     AEX  660 */
	for (i__ = 1; i__ <= 5; ++i__)
	{
		aer_2.extv[i__ - 1] = gamfog_(&i__, v, &aertm_2.taer[i__ - 1], &_BLNK__4.awccon[i__ - 1]);
		aer_2.absv[i__ - 1] = aer_2.extv[i__ - 1];
		aer_2.asyv[i__ - 1] = 0.f;
		/* L40: */
	}
	return 0;
/* CC                                                                     AEX  730 */
/*     V LE 1.0E-5                                                       AEX  740 */
L50:
	/* CC                                                                     AEX  760 */
	/* CC   EQL=EQLWC(IL)                                                     AEX  770 */
	for (i__ = 1; i__ <= 5; ++i__)
	{
		aer_2.extv[i__ - 1] = 0.f;
		aer_2.absv[i__ - 1] = 0.f;
		aer_2.asyv[i__ - 1] = 0.f;
		/*     WRITE (6,300) I,AWCCON(I)                                         AEX  820 */
		/* L300: */
		/* L60: */
	}
	/* L100: */
	return 0;
} /* aerext_ */

/* Subroutine */ int aertmp_(void)
{
	/* System generated locals */
	long i__1;

	/* Local variables */
	static long kk;
	static float wdf7, sum7, wdf12, wdf13, wdf14, wdf16, sum12, sum13, sum14,
		sum16;

	sum7 = 0.f;
	sum12 = 0.f;
	sum13 = 0.f;
	sum14 = 0.f;
	sum16 = 0.f;
	aertm_1.tae7 = 0.f;
	aertm_1.tae12 = 0.f;
	aertm_1.tae13 = 0.f;
	aertm_1.tae14 = 0.f;
	aertm_1.tae16 = 0.f;
	i__1 = cntrl_1.ikmax;
	for (kk = 1; kk <= i__1; ++kk)
	{
		if (kk == 1)
		{
			wdf7 = _BLNK__1.wpath[kk + 407];
			wdf12 = _BLNK__1.wpath[kk + 747];
			wdf13 = _BLNK__1.wpath[kk + 815];
			wdf14 = _BLNK__1.wpath[kk + 883];
			wdf16 = _BLNK__1.wpath[kk + 1019];
		}
		else
		{
			wdf7 = _BLNK__1.wpath[kk + 407] - _BLNK__1.wpath[kk + 406];
			wdf12 = _BLNK__1.wpath[kk + 747] - _BLNK__1.wpath[kk + 746];
			wdf13 = _BLNK__1.wpath[kk + 815] - _BLNK__1.wpath[kk + 814];
			wdf14 = _BLNK__1.wpath[kk + 883] - _BLNK__1.wpath[kk + 882];
			wdf16 = _BLNK__1.wpath[kk + 1019] - _BLNK__1.wpath[kk + 1018];
		}
		sum7 += wdf7;
		sum12 += wdf12;
		sum13 += wdf13;
		sum14 += wdf14;
		sum16 += wdf16;
		aertm_1.tae7 += wdf7 * _BLNK__1.tbby[kk - 1];
		aertm_1.tae12 += wdf12 * _BLNK__1.tbby[kk - 1];
		aertm_1.tae13 += wdf13 * _BLNK__1.tbby[kk - 1];
		aertm_1.tae14 += wdf14 * _BLNK__1.tbby[kk - 1];
		/* L10: */
		aertm_1.tae16 += wdf16 * _BLNK__1.tbby[kk - 1];
	}
	if (sum7 > 0.f)
	{
		aertm_1.tae7 /= sum7;
	}
	else
	{
		aertm_1.tae7 = _BLNK__1.tbby[0];
	}
	if (sum12 > 0.f)
	{
		aertm_1.tae12 /= sum12;
	}
	else
	{
		aertm_1.tae12 = _BLNK__1.tbby[0];
	}
	if (sum13 > 0.f)
	{
		aertm_1.tae13 /= sum13;
	}
	else
	{
		aertm_1.tae13 = _BLNK__1.tbby[0];
	}
	if (sum14 > 0.f)
	{
		aertm_1.tae14 /= sum14;
	}
	else
	{
		aertm_1.tae14 = _BLNK__1.tbby[0];
	}
	if (sum16 > 0.f)
	{
		aertm_1.tae16 /= sum16;
	}
	else
	{
		aertm_1.tae16 = _BLNK__1.tbby[0];
	}
	return 0;
} /* aertmp_ */

/* Subroutine */ int marine_(float *vis, long *model, float *ws, float *wh,
							 long *icstl, float *bext, float *babs, long *nl)
{
	/* Initialized data */

	static float wspd[8] = {6.9f, 4.1f, 4.1f, 10.29f, 6.69f, 12.35f, 7.2f, 6.9f};
	static float rhd[8] = {80.f, 75.63f, 76.2f, 77.13f, 75.24f, 80.53f, 45.89f, 80.f};

	/* Format strings */
	static char fmt_890[] = "(\0020MARINE AEROSOL MODEL USED\002)";
	static char fmt_920[] = "(\0020  WS NOT SPECIFIED, A DEFAULT VALUE IS US"
							"ED\002)";
	static char fmt_930[] = "(\0020  WH NOT SPECIFIED, A DEFAULT VALUE IS US"
							"ED\002)";
	static char fmt_910[] = "(t10,\002WIND SPEED = \002,f8.2,\002 M/SEC\002,"
							"/,t10,\002WIND SPEED (24 HR AVERAGE) = \002,f8.2,\002 M/SEC\002,"
							"/,t10,\002RELATIVE HUMIDITY = \002,f8.2,\002 PERCENT\002,/,t10"
							",\002AIRMASS CHARACTER =\002,i3)";
	static char fmt_900[] = "(\0020\002,t10,\002VIS = \002,f10.2,\002 KM\002)";

	/* System generated locals */
	float r__1;
	double d__1, d__2, d__3;

	/* Builtin functions */
	long s_wsfe(cilist *), e_wsfe(void), do_fio(long *, char *, long);
	double pow_dd(double *, double *);

	/* Local variables */
	static float c__, f;
	static long i__, j;
	static float a1, a2, a3, rh, qe1, qe2, qe3, t1av, t2av, t3av, t1xv, t2xv,
		t3xv, pisc, ext55, delrh, ratio, total, delrhv;

	/* Fortran I/O blocks */
	static cilist io___1175 = {0, 0, 0, fmt_890, 0};
	static cilist io___1177 = {0, 0, 0, fmt_920, 0};
	static cilist io___1178 = {0, 0, 0, fmt_930, 0};
	static cilist io___1179 = {0, 0, 0, fmt_910, 0};
	static cilist io___1201 = {0, 0, 0, fmt_900, 0};

	/*                                                                       MAR  110 */
	/*        THIS SUBROUTINE DETERMINES AEROSOL EXT + ABS COEFFICIENTS      MAR  120 */
	/*          FOR THE NAVY MARITIME MODEL                                  MAR  130 */
	/*            CODED BY STU GATHMAN                  -  NRL               MAR  140 */
	/*                                                                       MAR  150 */
	/*        INPUTS-                                                        MAR  160 */
	/*        WSS = CURRENT WIND SPEED (M/S)                                 MAR  170 */
	/*        WHH = 24 HOUR AVERAGE WIND SPEED (M/S)                         MAR  180 */
	/*        RHH = RELATIVE HUMIDITY (PERCENTAGE)                           MAR  190 */
	/*        VIS = METEOROLOGICAL RANGE (KM)                                MAR  200 */
	/*        ICTL = AIR MASS CHARACTER  1 = OPEN OCEAN                      MAR  210 */
	/*                      10 = STRONG CONTINENTAL INFLUENCE                MAR  220 */
	/*        MODEL = MODEL ATMOSPHERE                                       MAR  230 */
	/*                                                                       MAR  240 */
	/*        OUTPUTS-                                                       MAR  250 */
	/*        BEXT = EXTINCTION COEFFICIENT (KM-1)                           MAR  260 */
	/*        BABS = ABSORPTION COEFFICIENT (KM-1)                           MAR  270 */
	/*                                                                       MAR  280 */
	/* C    COMMON/AER/A1, A2, A3        X(5)                                 MAR  340 */
	/* Parameter adjustments */
	babs -= 6;
	bext -= 6;

	/* Function Body */
	pisc = cnstns_1.pi / 1e3f;
	io___1175.ciunit = ifil_1.ipr;
	s_wsfe(&io___1175);
	e_wsfe();
	/*                                                                       MAR  410 */
	/*     CHECK LIMITS OF MODEL VALIDITY                                    MAR  420 */
	/*                                                                       MAR  430 */
	rh = mart_1.rhh;
	if (mart_1.rhh > 0.f)
	{
		goto L10;
	}
	rh = rhd[*model];
L10:
	if (*ws > 20.f)
	{
		*ws = 20.f;
	}
	if (*wh > 20.f)
	{
		*wh = 20.f;
	}
	if (rh > 98.f)
	{
		rh = 98.f;
	}
	if (rh < 50.f && rh >= 0.f)
	{
		rh = 50.f;
	}
	if (*icstl < 1 || *icstl > 10)
	{
		*icstl = 3;
	}
	/*                                                                       MAR  520 */
	/*     FIND SIZE DISTRIBUTION PARAMETERS FROM METEOROLOGY INPUT          MAR  530 */
	/*                                                                       MAR  540 */
	if (*wh <= 0.f)
	{
		io___1177.ciunit = ifil_1.ipr;
		s_wsfe(&io___1177);
		e_wsfe();
	}
	if (*wh <= 0.f)
	{
		*wh = wspd[*model];
	}
	if (*ws <= 0.f)
	{
		io___1178.ciunit = ifil_1.ipr;
		s_wsfe(&io___1178);
		e_wsfe();
	}
	if (*ws <= 0.f)
	{
		*ws = *wh;
	}
	io___1179.ciunit = ifil_1.ipr;
	s_wsfe(&io___1179);
	do_fio(&c__1, (char *)&(*ws), (long)sizeof(float));
	do_fio(&c__1, (char *)&(*wh), (long)sizeof(float));
	do_fio(&c__1, (char *)&rh, (long)sizeof(float));
	do_fio(&c__1, (char *)&(*icstl), (long)sizeof(long));
	e_wsfe();
	/*                                                                       MAR  600 */
	/*        F IS A RELATIVE HUMIDITY DEPENDENT GROWTH CORRECTION           MAR  610 */
	/*        TO THE ATTENUATION COEFFICIENT.                                MAR  620 */
	/*                                                                       MAR  630 */
	d__1 = (double)((2.f - rh / 100.f) / ((1.f - rh / 100.f) * 6.f));
	f = pow_dd(&d__1, &c_b1830);
	a1 = *icstl * 2e3f * *icstl;
	/* Computing MAX */
	r__1 = (*wh - 2.2f) * 5.866f;
	a2 = min(r__1, .5f);
	/* CC   A3 = AMAX1(0.01527*(WS-2.2), 1.14E-5)                             MAR  670 */
	d__1 = (double)(*ws * .06f - 2.8f);
	a3 = pow_dd(&c_b1661, &d__1);
	/*                                                                       MAR  690 */
	/*     FIND EXTINCTION AT 0.55 MICRONS AND NORMALIZE TO 1.               MAR  700 */
	/*                                                                       MAR  710 */
	/*     INTERPOLATE FOR RELATIVE HUMIDITY                                 MAR  720 */
	/*                                                                       MAR  730 */
	for (j = 2; j <= 4; ++j)
	{
		if (rh <= a_1.arel[j - 1])
		{
			goto L42;
		}
		/* L40: */
	}
L42:
	delrh = a_1.arel[j - 1] - a_1.arel[j - 2];
	delrhv = rh - a_1.arel[j - 2];
	ratio = delrhv / delrh;
	qe1 = a_1.t1qext[(j - 1) * 40 - 37] + (a_1.t1qext[j * 40 - 37] -
										   a_1.t1qext[(j - 1) * 40 - 37]) *
											  ratio;
	qe2 = a_1.t2qext[(j - 1) * 40 - 37] + (a_1.t2qext[j * 40 - 37] -
										   a_1.t2qext[(j - 1) * 40 - 37]) *
											  ratio;
	qe3 = a_1.t3qext[(j - 1) * 40 - 37] + (a_1.t3qext[j * 40 - 37] -
										   a_1.t3qext[(j - 1) * 40 - 37]) *
											  ratio;
	d__1 = (double)qe1;
	d__2 = (double)qe2;
	d__3 = (double)qe3;
	total = a1 * pow_dd(&c_b1661, &d__1) + a2 * pow_dd(&c_b1661, &d__2) + a3 * pow_dd(&c_b1661, &d__3);
	ext55 = pisc * total / f;
	/*                                                                       MAR  850 */
	/*     IF METEOROLOLICAL RANGE NOT SPECIFIED,FIND FROM METEOR DATA       MAR  860 */
	/*                                                                       MAR  870 */
	if (*vis <= 0.f)
	{
		*vis = 3.912f / (ext55 + .01159f);
	}
	c__ = 1.f / ext55 * (pisc / f);
	a1 = c__ * a1;
	a2 = c__ * a2;
	a3 = c__ * a3;
	/*                                                                       MAR  930 */
	/*     CALCULATE NORMALIZED ATTENUATION COEFICIENTS                      MAR  940 */
	/*                                                                       MAR  950 */
	for (i__ = 1; i__ <= 40; ++i__)
	{
		t1xv = a_1.t1qext[i__ + (j - 1) * 40 - 41] + (a_1.t1qext[i__ + j * 40 - 41] - a_1.t1qext[i__ + (j - 1) * 40 - 41]) * ratio;
		t2xv = a_1.t2qext[i__ + (j - 1) * 40 - 41] + (a_1.t2qext[i__ + j * 40 - 41] - a_1.t2qext[i__ + (j - 1) * 40 - 41]) * ratio;
		t3xv = a_1.t3qext[i__ + (j - 1) * 40 - 41] + (a_1.t3qext[i__ + j * 40 - 41] - a_1.t3qext[i__ + (j - 1) * 40 - 41]) * ratio;
		t1av = a_1.t1qabs[i__ + (j - 1) * 40 - 41] + (a_1.t1qabs[i__ + j * 40 - 41] - a_1.t1qabs[i__ + (j - 1) * 40 - 41]) * ratio;
		t2av = a_1.t2qabs[i__ + (j - 1) * 40 - 41] + (a_1.t2qabs[i__ + j * 40 - 41] - a_1.t2qabs[i__ + (j - 1) * 40 - 41]) * ratio;
		t3av = a_1.t3qabs[i__ + (j - 1) * 40 - 41] + (a_1.t3qabs[i__ + j * 40 - 41] - a_1.t3qabs[i__ + (j - 1) * 40 - 41]) * ratio;
		d__1 = (double)t1xv;
		d__2 = (double)t2xv;
		d__3 = (double)t3xv;
		bext[*nl + i__ * 5] = a1 * pow_dd(&c_b1661, &d__1) + a2 * pow_dd(&c_b1661, &d__2) + a3 * pow_dd(&c_b1661, &d__3);
		d__1 = (double)t1av;
		d__2 = (double)t2av;
		d__3 = (double)t3av;
		babs[*nl + i__ * 5] = a1 * pow_dd(&c_b1661, &d__1) + a2 * pow_dd(&c_b1661, &d__2) + a3 * pow_dd(&c_b1661, &d__3);
		/* L45: */
	}
	io___1201.ciunit = ifil_1.ipr;
	s_wsfe(&io___1201);
	do_fio(&c__1, (char *)&(*vis), (long)sizeof(float));
	e_wsfe();
	return 0;
} /* marine_ */

/* Subroutine */ int mardta_(void)
{
	return 0;
} /* mardta_ */

/* >    BLOCK DATA                                                        MDA  110 */
/*                                                                       MDA  120 */
/*     MARINE AEROSOL EXTINCTION AND ABSORPTION DATA                     MDA  130 */
/*            CODED BY STU GATHMAN                  -  NRL               MDA  140 */
/*                                                                       MDA  150 */

/* Subroutine */ int vsa_(long *ihaze, float *vis, float *ceilht, float *depth, float *zinvht, float *z__, float *rh, float *ahaze, long *ih)
{
	/* Initialized data */

	static float aa[2] = {92.1f, .3981f};
	static float cc[3] = {-.014f, .0125f, -.03f};
	static float kmtom = 1e3f;
	static float ee[4] = {7.f, .7824f, .17009f, .012f};
	static float fac1[9] = {0.f, .03f, .05f, .075f, .1f, .18f, .3f, .45f, 1.f};
	static float fac2[9] = {0.f, .03f, .1f, .18f, .3f, .45f, .6f, .78f, 1.f};

	/* Format strings */
	static char fmt_599[] = "(\0020 VERTICAL STRUCTURE ALGORITHM (VSA) USE"
							"D\002)";
	static char fmt_603[] = "(\002 \002,50x,\002CLOUD DEPTH UNKNOWN\002)";
	static char fmt_604[] = "(\002 \002,50x,\002VSA WILL USE A DEFAULT OF 20"
							"0.0 METERS\002,/)";
	static char fmt_611[] = "(\002 \002,50x,\002CLOUD DEPTH IS \002,f14.1"
							",\002 METERS\002,/)";
	static char fmt_600[] = "(\002 \002,50x,\002CLOUD CEILING HEIGHT UNKNOW"
							"N\002)";
	static char fmt_602[] = "(\002 \002,39x,\002VSA WILL USE A CALCULATED VA"
							"LUE OF \002,f7.1,\002 METERS\002,/)";
	static char fmt_610[] = "(\002 \002,50x,\002CLOUD CEILING HEIGHT IS \002"
							",f9.1,\002 METERS\002,/)";
	static char fmt_601[] = "(\002 \002,50x,\002INVERSION OR BOUNDARY LAYER "
							"HEIGHT UNKNOWN\002,/,\002 \002,50x,\002VSA WILL USE A DEFAULT OF"
							" 2000.0 METERS\002,/)";
	static char fmt_605[] = "(\002 \002,50x,\002RADIATION FOG DEPTH UNKNOW"
							"N\002)";
	static char fmt_612[] = "(\002 \002,50x,\002INVERSION OR BOUNDARY LAYER "
							"HEIGHT IS \002,f7.1,\002 METERS\002,/)";
	static char fmt_614[] = "(\002 \002,50x,\002DEPTH OF RADIATION FOG IS"
							" \002,f7.1,\002 METERS\002,/)";
	static char fmt_619[] = "(5x,\002HEIGHT(KM)\002,5x,\002R.H.(%)\002,5x"
							",\002EXTINCTION(KM-1)\002,5x,\002VIS(3.912/EXTN)\002,5x,\002IHAZE"
							"\002,/)";
	static char fmt_620[] = "(7x,f7.4,7x,f5.1,8x,e12.4,11x,f7.4,10x,i2)";

	/* System generated locals */
	float r__1;

	/* Builtin functions */
	long s_wsfe(cilist *), e_wsfe(void), do_fio(long *, char *, long);
	double log(double), exp(double);

	/* Local variables */
	static float a[2], b[2], c__[2], d__, e, f;
	static long i__, k, ic;
	static float zc, zt, dak, eak, dof, ceil, hmax, anum, zinv, zhigh, zalgo,
		visib;

	/* Fortran I/O blocks */
	static cilist io___1232 = {0, 0, 0, fmt_599, 0};
	static cilist io___1243 = {0, 0, 0, fmt_603, 0};
	static cilist io___1244 = {0, 0, 0, fmt_604, 0};
	static cilist io___1245 = {0, 0, 0, fmt_611, 0};
	static cilist io___1247 = {0, 0, 0, fmt_600, 0};
	static cilist io___1252 = {0, 0, 0, fmt_602, 0};
	static cilist io___1253 = {0, 0, 0, fmt_610, 0};
	static cilist io___1256 = {0, 0, 0, fmt_601, 0};
	static cilist io___1257 = {0, 0, 0, fmt_605, 0};
	static cilist io___1258 = {0, 0, 0, fmt_604, 0};
	static cilist io___1259 = {0, 0, 0, fmt_612, 0};
	static cilist io___1260 = {0, 0, 0, fmt_614, 0};
	static cilist io___1263 = {0, 0, 0, fmt_619, 0};
	static cilist io___1266 = {0, 0, 0, fmt_620, 0};

	/*                                                                       VSA  110 */
	/*     VERTICAL STRUCTURE ALGORITHM                                      VSA  120 */
	/*                                                                       VSA  130 */
	/*     FROM U.S. ARMY ATMOSPHERIC SCIENCES LAB                           VSA  140 */
	/*     WHITE SANDS MISSILE RANGE, NM                                     VSA  150 */
	/*                                                                       VSA  160 */
	/*     CREATES A PROFILE OF AEROSOL DENSITY NEAR THE GROUND,INCLUDING    VSA  170 */
	/*     CLOUDS AND FOG                                                    VSA  180 */
	/*                                                                       VSA  190 */
	/*     THESE PROFILES ARE AT 9 HEIGHTS BETWEEN 0 KM AND 2 KM             VSA  200 */
	/*                                                                       VSA  210 */
	/*                                                                       VSA  220 */
	/*  ***VISIBILITY IS ASSUMED TO BE THE SURFACE VISIBILITY***             VSA  230 */
	/*                                                                       VSA  240 */
	/*     IHAZE  = THE TYPE OF AEROSOL                                      VSA  250 */
	/*     VIS    = VISIBILITY IN KM AT THE SURFACE                          VSA  260 */
	/*     CEILHT = THE CLOUD CEILING HEIGHT IN KM                           VSA  270 */
	/*     DEPTH  = THE CLOUD/FOG DEPTH IN KM                                VSA  280 */
	/*     ZINVHT = THE HEIGHT OF INVERSION OR BOUNDARY LAYER IN KM          VSA  290 */
	/*                                                                       VSA  300 */
	/*     VARIABLES USED IN VSA                                             VSA  310 */
	/*                                                                       VSA  320 */
	/*     ZC     = CLOUD CEILING HEIGHT IN M                                VSA  330 */
	/*     ZT     = CLOUD DEPTH IN M                                         VSA  340 */
	/*     ZINV   = INVERSION HEIGHT IN M                                    VSA  350 */
	/*           SEE BELOW FOR MORE INFORMATION ABOUT ZC, ZT, AND ZINV       VSA  360 */
	/*     D      = INITIAL EXTINCTION AT THE SURFACE (D=3.912/VIS-0.012)    VSA  370 */
	/*     ZALGO  = THE DEPTH OF THE LAYER FOR THE ALGORITHM                 VSA  380 */
	/*                                                                       VSA  390 */
	/*     OUTPUT FROM VSA:                                                  VSA  400 */
	/*                                                                       VSA  410 */
	/*     Z      = HEIGHT IN KM                                             VSA  420 */
	/*     RH     = RELATIVE HUMIDITY AT HEIGHT Z IN PERCENT                 VSA  430 */
	/*     AHAZE  = EXTINCTION AT HEIGHT Z IN KM**-1                         VSA  440 */
	/*     IH     = AEROSAL TYPE FOR HEIGHT Z                                VSA  450 */
	/*     HMAX   = MAXIMUM HEIGHT IN KM USED IN VSA, NOT NECESSARILY 2.0 KM VSA  460 */
	/*                                                                       VSA  470 */
	/*                                                                       VSA  480 */
	/*     THE SLANT PATH CALCULATION USES THE FOLLOWING FUNCTION:           VSA  490 */
	/*                                                                       VSA  500 */
	/*                 EXT55=A*EXP(B*EXP(C*Z))                               VSA  510 */
	/*                                                                       VSA  520 */
	/*     WHERE 'Z' IS THE HEIGHT IN KILOMETERS,                            VSA  530 */
	/*           'A' IS A FUNCTION OF EXT55 AT Z=0.0 AND IS ALWAYS POSITIVE, VSA  540 */
	/*           'B' AND 'C' ARE FUNCTIONS OF CLOUD CONDITIONS AND SURFACE   VSA  550 */
	/*               VISIBILITY (EITHER A OR B CAN BE POSITIVE OR NEGATIVE), VSA  560 */
	/*           'EXT55' IS THE VISIBILE EXTINCTION COEFFICIENT IN KM**-1.   VSA  570 */
	/*                                                                       VSA  580 */
	/*     THEREFORE, THERE ARE 4 CASES DEPENDING ON THE SIGNS OF 'B' AND 'C'VSA  590 */
	/*     CEILHT AND ZINVHT ARE USED AS SWITCHES TO DETERMINE WHICH CASE    VSA  600 */
	/*     TO USE.  THE SURFACE EXTINCTION 'D' IS CALCULATED FROM THE        VSA  610 */
	/*     VISIBILITY USING  D=3.912/VIS-0.012 AS FOLLOWS-                   VSA  620 */
	/*                                                                       VSA  630 */
	/*         CASE=1  FOG/CLOUD CONDITIONS                                  VSA  640 */
	/*                 'B' LT 0.0, 'C' LT 0.0                                VSA  650 */
	/*                 'D' GE 7.0   KM**-1                                   VSA  660 */
	/*                 FOR A CLOUD 7.    KM**-1 IS THE BOUNDARY VALUE AT     VSA  670 */
	/*                 THE CLOUD BASE AND 'Z' IS THE VERTICAL DISTANCE       VSA  680 */
	/*                 INTO THE CLOUD.                                       VSA  690 */
	/*                 VARIABLE USED:   DEPTH                                VSA  700 */
	/*                 ** DEFAULT:  DEPTH OF FOG/CLOUD IS 0.2 KM WHEN        VSA  710 */
	/*                              'DEPTH' IS 0.0                           VSA  720 */
	/*                                                                       VSA  730 */
	/*             =2  CLOUD CEILING PRESENT                                 VSA  740 */
	/*                 'B' GT 0.0, 'C' GT 0.0                                VSA  750 */
	/*                 VARIABLE USED:   CEILHT (MUST BE GE 0.0)              VSA  800 */
	/*                 ** DEFAULTS:  CASE 2 - CEILHT IS CALCULATED FROM      VSA  810 */
	/*                               SURFACE EXTINCTION                      VSA  820 */
	/*                                                                       VSA  850 */
	/*             =3  RADIATION FOG OR INVERSION OR BOUNDARY LAYER PRESENT  VSA  860 */
	/*                 'B' LT 0.0, 'C' GT 0.0                                VSA  870 */
	/*                 VIS LE 2.0 KM DEFAULTS TO A RADIATION FOG AT THE      VSA  880 */
	/*                     GROUND AND OVERRIDES INPUT BOUNDARY AEROSOL TYPE  VSA  890 */
	/*                 VIS GT 2.0 KM FOR AN INVERSION OR BOUNDARY LAYER      VSA  900 */
	/*                     WITH INPUT BOUNDARY AEROSOL TYPE                  VSA  910 */
	/*                 ** IHAZE=9 (RADIATION FOG) ALWAYS DEFAULTS TO A       VSA  920 */
	/*                    RADIATION FOG NO MATTER WHAT THE VISIBILITY IS.    VSA  930 */
	/*                 SWITCH VARIABLE: CEILHT (MUST BE LT 0.0)              VSA  940 */
	/*                 VARIABLE USED:   ZINVHT (MUST BE GE 0.0)              VSA  950 */
	/*                 ** CEILHT MUST BE LT 0.0 FOR ZINVHT TO BE USED **     VSA  960 */
	/*                    HOWEVER, IF DEPTH IS GT 0.0 AND ZINVHT IS EQ 0.0,  VSA  970 */
	/*                    THE PROGRAM WILL SUBSTITUTE DEPTH FOR ZINVHT.      VSA  980 */
	/*                 ** DEFAULT:  FOR A RADIATION FOG ZINVHT IS 0.05 K     VSA  990 */
	/*                              FOR AN INVERSION LAYER ZINVHT IS 2.0 KM  VSA 1000 */

	/*           NOTE: IF IHAZE = 9, BUT VIS GT 2.0 KM RECOMEND */
	/*           THAT IHAZE DEFAULT TO RURAL AEROSOL */
	/*                                                                       VSA 1010 */
	/*             =4  NO CLOUD CEILING, INVERSION LAYER, OR BOUNDARY        VSA 1020 */
	/*                 LAYER PRESENT, I.E. CLEAR SKIES                       VSA 1030 */
	/*                 EXTINCTION PROFILE CONSTANT WITH HEIGHT A SHORT       VSA 1040 */
	/*                 DISTANCE ABOVE THE SURFACE */
	/*                                                                       VSA 1050 */
	/* Parameter adjustments */
	--ih;
	--ahaze;
	--rh;
	--z__;

	/* Function Body */
	/*     THE LAST 3 VALUES OF EE BELOW ARE EXTINCTIONS FOR VISIBILITIES    VSA 1110 */
	/*     EQUAL TO 5.0, 23.0, AND 50.0 KM, RESPECTIVELY.                    VSA 1120 */
	io___1232.ciunit = ifil_1.ipr;
	s_wsfe(&io___1232);
	e_wsfe();
	/*                                                                       VSA 1170 */
	/*     UPPER LIMIT ON VERTICAL DISTANCE - 2 KM                           VSA 1180 */
	zhigh = 2e3f;
	hmax = zhigh;
	if (*vis > 0.f)
	{
		goto L5;
	}
	/*     DEFAULT FOR VISIBILITY DEPENDS ON THE VALUE OF IHAZE.             VSA 1220 */
	if (*ihaze == 8)
	{
		*vis = .2f;
	}
	if (*ihaze == 9)
	{
		*vis = .5f;
	}
	if (*ihaze == 2 || *ihaze == 5)
	{
		*vis = 5.f;
	}
	if (*ihaze == 1 || *ihaze == 4 || *ihaze == 7)
	{
		*vis = 23.f;
	}
	if (*ihaze == 6)
	{
		*vis = 50.f;
	}
/*     IF(IHAZE.EQ.3)VIS= OR IHAZE = 10 VIS IS DETERMINED ELSEWHERE      VSA 1280 */
L5:
	d__ = 3.912f / *vis - .012f;
	/*                                                                       VSA 1300 */
	zc = *ceilht * kmtom;
	zt = *depth * kmtom;
	zinv = *zinvht * kmtom;
	/*     IHAZE=9 (RADIATION FOG) IS ALWAYS CALCULATED AS A RADIATION FOG.  VSA 1340 */
	if (*ihaze == 9)
	{
		zc = -1.f;
	}
	/*     ALSO, CHECK TO SEE IF THE FOG DEPTH FOR A RADIATION FOG           VSA 1360 */
	/*     WAS INPUT TO DEPTH INSTEAD OF THE CORRECT VARIABLE ZINVHT.        VSA 1370 */
	if (*ihaze == 9 && zt > 0.f && zinv == 0.f)
	{
		zinv = zt;
	}
	/*                                                                       VSA 1390 */
	/*     'IC' DEFINES WHICH CASE TO USE.                                   VSA 1400 */
	ic = 2;
	if (d__ >= ee[0] && zc >= 0.f)
	{
		ic = 1;
	}
	/*                                                                       VSA 1430 */
	if (zc < 0.f && ic == 2)
	{
		ic = 3;
	}
	if (zinv < 0.f && ic == 3)
	{
		ic = 4;
	}
	k = 1;
	switch (ic)
	{
	case 1:
		goto L10;
	case 2:
		goto L20;
	case 3:
		goto L40;
	case 4:
		goto L50;
	}
/*                                                                       VSA 1530 */
/*     CASE 1:  DEPTH FOG/CLOUD; INCREASING EXTINCTION WITH HEIGHT FROM  VSA 1540 */
/*              CLOUD/FOG BASE TO CLOUD/FOG TOP.                         VSA 1550 */
L10:
	if (zc < hmax && ic == 2)
	{
		k = 2;
	}
	/*     IC=-1 WHEN A CLOUD IS PRESENT AND THE PATH GOES INTO IT.          VSA 1580 */
	/*     USE CASE 2 OR 2' BELOW CLOUD AND CASE 1 INSIDE IT.                VSA 1590 */
	if (k == 2)
	{
		ic = -1;
	}
	/*     THE BASE OF THE CLOUD HAS AN EXTINCTION COEFFICIENT OF 7.0   KM-1.VSA 1610 */
	if (k == 2)
	{
		d__ = ee[0];
	}
	a[k - 1] = aa[0];
	/*     IF THE SURFACE EXTINCTION IS GREATER THAN THE UPPER LIMIT OF 92.1 VSA 1640 */
	/*     KM**-1, RUN THE ALGORITHM WITH AN UPPER LIMIT OF 'D+10'.          VSA 1650 */
	if (d__ >= aa[0])
	{
		a[k - 1] = d__ + 10.f;
	}
	c__[k - 1] = cc[0];
	if (zt <= 0.f)
	{
		io___1243.ciunit = ifil_1.ipr;
		s_wsfe(&io___1243);
		e_wsfe();
	}
	if (zt <= 0.f)
	{
		io___1244.ciunit = ifil_1.ipr;
		s_wsfe(&io___1244);
		e_wsfe();
	}
	if (zt > 0.f)
	{
		io___1245.ciunit = ifil_1.ipr;
		s_wsfe(&io___1245);
		do_fio(&c__1, (char *)&zt, (long)sizeof(float));
		e_wsfe();
	}
	/*     IF THE DISTANCE FROM THE GROUND TO THE CLOUD/FOG TOP IS LESS      VSA 1710 */
	/*     THAN 2.0 KM, VSA WILL ONLY CALCULATE UP TO THE CLOUD TOP.         VSA 1720 */
	if (zt <= 0.f)
	{
		zt = 200.f;
	}
	/* Computing MIN */
	r__1 = zt + zc;
	hmax = min(r__1, hmax);
	goto L60;
/*                                                                       VSA 1760 */
/*     CASE 2:  CLEAR/HAZY/LIGHTLY FOGGY; INCREASING EXTINCTION WITH HEIGHT    VSA 1770 */
/*              UP TO THE CLOUD BASE.                                    VSA 1780 */
L20:
	a[k - 1] = aa[1];
	e = ee[0];
	if (zc == 0.f)
	{
		io___1247.ciunit = ifil_1.ipr;
		s_wsfe(&io___1247);
		e_wsfe();
	}
	if (zc == 0.f)
	{
		eak = log(e / a[k - 1]);
		dak = log(d__ / a[k - 1]);
		anum = eak / dak;
		if (anum > 0.f)
		{
			ceil = log(anum) / cc[1];
		}
		else
		{
			ceil = 2e3f;
		}
	}
	/* C    IF(ZC.EQ.0.0)CEIL=ALOG(ALOG(E/A(K))/(ALOG(D/A(K))))/CC(2)         VSA 1820 */
	if (zc == 0.f)
	{
		io___1252.ciunit = ifil_1.ipr;
		s_wsfe(&io___1252);
		do_fio(&c__1, (char *)&ceil, (long)sizeof(float));
		e_wsfe();
	}
	if (zc > 0.f)
	{
		io___1253.ciunit = ifil_1.ipr;
		s_wsfe(&io___1253);
		do_fio(&c__1, (char *)&zc, (long)sizeof(float));
		e_wsfe();
	}
	if (zc == 0.f)
	{
		zc = ceil;
	}
	/* Computing 2nd power */
	r__1 = *vis * zc / 350.f;
	f = r__1 * r__1;

	/*     F IS A SCALING FACTOR USED IN CASE 2 */

	dof = d__ / f;
	if (dof >= 1e-4f)
	{
		a[k - 1] = f * (1.f - exp(-d__ / f));
	}
	else
	{
		a[k - 1] = d__ * (1.f - dof * .5f);
	}

	/*     THE COEFFICIENT A IS RECALCULATED BASED UPON THE SCALING FACTOR */

	goto L60;
/*                                                                       VSA 1870 */
/*                                                                       VSA 1970 */
/*     CASE 3:  NO CLOUD CEILING BUT A RADIATION FOG OR AN INVERSION     VSA 1980 */
/*              OR BOUNDARY LAYER PRESENT; DECREASING EXTINCTION WITH    VSA 1990 */
/*              HEIGHT UP TO THE HEIGHT OF THE FOG OR LAYER.             VSA 2000 */
L40:
	a[k - 1] = d__ * 1.1f;
	e = ee[2];
	if (*ihaze == 2 || *ihaze == 5)
	{
		e = ee[1];
	}
	if (*ihaze == 6 || *vis > 2.f && *ihaze != 9)
	{
		e = ee[3];
	}
	if (e > d__)
	{
		e = d__ * .99999f;
	}
	if (zt > 0.f && zinv == 0.f && *vis <= 2.f)
	{
		zinv = zt;
	}
	if (zinv == 0.f && *vis > 2.f && *ihaze != 9)
	{
		io___1256.ciunit = ifil_1.ipr;
		s_wsfe(&io___1256);
		e_wsfe();
	}
	if (zinv == 0.f && (*vis <= 2.f || *ihaze == 9))
	{
		io___1257.ciunit = ifil_1.ipr;
		s_wsfe(&io___1257);
		e_wsfe();
	}
	if (zinv == 0.f && (*vis <= 2.f || *ihaze == 9))
	{
		io___1258.ciunit = ifil_1.ipr;
		s_wsfe(&io___1258);
		e_wsfe();
	}
	if (zinv > 0.f && *vis > 2.f && *ihaze != 9)
	{
		io___1259.ciunit = ifil_1.ipr;
		s_wsfe(&io___1259);
		do_fio(&c__1, (char *)&zinv, (long)sizeof(float));
		e_wsfe();
	}
	if (zinv > 0.f && (*vis <= 2.f || *ihaze == 9))
	{
		io___1260.ciunit = ifil_1.ipr;
		s_wsfe(&io___1260);
		do_fio(&c__1, (char *)&zinv, (long)sizeof(float));
		e_wsfe();
	}
	if (zinv == 0.f && *vis > 2.f && *ihaze != 9)
	{
		zinv = 2e3f;
	}
	if (zinv == 0.f && (*vis <= 2.f || *ihaze == 9))
	{
		zinv = 50.f;
	}
	hmax = min(zinv, hmax);
	zc = 0.f;
	goto L60;
	/*                                                                       VSA 2160 */
	/*     CASE 4:  NO CLOUD CEILING OR INVERSION LAYER;                     VSA 2170 */
	/*              CONSTANT EXTINCTION WITH HEIGHT.                         VSA 2180 */

L50:
	a[k - 1] = ee[3];
	c__[k - 1] = cc[2];
/*                                                                       VSA 2190 */
L60:
	b[k - 1] = log(d__ / a[k - 1]);
	if (ic == 2)
	{
		c__[k - 1] = log(log(e / a[k - 1]) / b[k - 1]) / zc;
	}
	if (ic == 3)
	{
		c__[k - 1] = log(log(e / a[k - 1]) / b[k - 1]) / zinv;
	}
	if (zc < hmax && k == 1 && ic == 2)
	{
		goto L10;
	}
	if (ic == 2)
	{
		hmax = min(zc, hmax);
	}
	zalgo = hmax;
	if (ic < 0)
	{
		zalgo = zc;
	}
	io___1263.ciunit = ifil_1.ipr;
	s_wsfe(&io___1263);
	e_wsfe();
	if (ic < 0)
	{
		k = 1;
	}
	/*                                                                       VSA 2300 */
	for (i__ = 1; i__ <= 9; ++i__)
	{
		if (ic < 0 && i__ == 5)
		{
			k = 2;
		}
		if (ic < 0 && i__ == 5)
		{
			zalgo = hmax - zc;
		}
		z__[i__] = zalgo * (1.f - fac2[10 - i__ - 1]);
		if (ic == 1)
		{
			z__[i__] = zalgo * fac1[i__ - 1];
		}
		if (ic == 4)
		{
			z__[i__] = zalgo * (float)(i__ - 1) / 8.f;
		}
		if (ic < 0 && i__ < 5)
		{
			z__[i__] = zalgo * (1.f - fac2[11 - (i__ << 1) - 1]);
		}
		if (ic < 0 && i__ >= 5)
		{
			z__[i__] = zalgo * fac1[(i__ << 1) - 10];
		}
		/*     IF(IC.LT.0.AND.(I.EQ.7.OR.I.EQ.8))Z(I)=ZALGO*FAC1(2*I-10)         VSA 2390 */
		ahaze[i__] = a[k - 1] * exp(b[k - 1] * exp(c__[k - 1] * z__[i__]));
		if (ic <= 0 && i__ >= 5)
		{
			z__[i__] += zc;
		}
		z__[i__] /= kmtom;
		rh[i__] = log(ahaze[i__]) * 6.953f + 86.407f;
		if (ahaze[i__] >= ee[0])
		{
			rh[i__] = 100.f;
		}
		visib = 3.912f / (ahaze[i__] + .012f);
		ih[i__] = *ihaze;
		/*     IF A RADIATION FOG IS PRESENT (I.E. VIS<=2.0 KM AND IC=3),        VSA 2480 */
		/*     IH IS SET TO 9 FOR ALL LEVELS.                                    VSA 2490 */
		if (visib <= 2.f && ic == 3)
		{
			ih[i__] = 9;
		}
		/*     FOR A DEPTH FOG/CLOUD CASE, IH=8 DENOTING AN ADVECTION FOG.       VSA 2510 */
		if (ic == 1 || ic < 0 && i__ >= 5)
		{
			ih[i__] = 8;
		}
		io___1266.ciunit = ifil_1.ipr;
		s_wsfe(&io___1266);
		do_fio(&c__1, (char *)&z__[i__], (long)sizeof(float));
		do_fio(&c__1, (char *)&rh[i__], (long)sizeof(float));
		do_fio(&c__1, (char *)&ahaze[i__], (long)sizeof(float));
		do_fio(&c__1, (char *)&visib, (long)sizeof(float));
		do_fio(&c__1, (char *)&ih[i__], (long)sizeof(long));
		e_wsfe();
		/* L70: */
	}
	hmax /= kmtom;
	return 0;
	/*                                                                       VSA 2570 */
	/* L613: */
} /* vsa_ */

/* Subroutine */ int hno3_(float *v, float *habs)
{
	/* Initialized data */

	static float h1[15] = {2.197f, 3.911f, 6.154f, 8.15f, 9.217f, 9.461f, 11.56f,
						   11.1f, 11.17f, 12.4f, 10.49f, 7.509f, 6.136f, 4.899f, 2.866f};
	static float h2[16] = {2.828f, 4.611f, 6.755f, 8.759f, 10.51f, 13.74f, 18.f,
						   21.51f, 23.09f, 21.68f, 21.32f, 16.82f, 16.42f, 17.87f, 14.86f, 8.716f};
	static float h3[13] = {5.003f, 8.803f, 14.12f, 19.83f, 23.31f, 23.58f, 23.22f,
						   21.09f, 26.99f, 25.84f, 24.79f, 17.68f, 9.42f};

	static long i__;

	/*                                                                       HNO  110 */
	/*     HNO3  STATISTICAL BAND PARAMETERS                                 HNO  120 */
	/*                                                                       HNO  130 */
	/*     ARRAY H1 CONTAINS HNO3 ABS, COEF(CM-1ATM-1) FROM  850 TO 920 CM-1 HNO  150 */
	/*     ARRAY H2 CONTAINS HNO3 ABS, COEF(CM-1ATM-1) FROM 1275 TO1350 CM-1 HNO  180 */
	/*     ARRAY H3 CONTAINS HNO3 ABS, COEF(CM-1ATM-1) FROM 1675 TO1735 CM-1 HNO  210 */
	*habs = 0.f;
	if (*v >= 850.f && *v <= 920.f)
	{
		goto L5;
	}
	if (*v >= 1275.f && *v <= 1350.f)
	{
		goto L10;
	}
	if (*v >= 1675.f && *v <= 1735.f)
	{
		goto L15;
	}
	return 0;
L5:
	i__ = (*v - 845.f) / 5.f;
	*habs = h1[i__ - 1];
	return 0;
L10:
	i__ = (*v - 1270.f) / 5.f;
	*habs = h2[i__ - 1];
	return 0;
L15:
	i__ = (*v - 1670.f) / 5.f;
	*habs = h3[i__ - 1];
	return 0;
} /* hno3_ */

/* Subroutine */ int ssgeo_(long *ierror, long *iph, long *iparm,
							float *parm1, float *parm2, float *parm3, float *parm4, float *psipo, float *g, long *maxgeo)
{
	/* Format strings */
	static char fmt_960[] = "(2x,\002THETAO < 89.5, OBSERVER ASSUMED TO BE A"
							"T THE SOUTH     POLE, PROBLEM HAS BEEN REMAPPED TO THE EQUATO"
							"R\002)";
	static char fmt_961[] = "(2x,\002THETAO > 89.5, OBSERVER ASSUMED TO BE A"
							"T THE NORTH     POLE, PROBLEM HAS BEEN REMAPPED TO THE EQUATO"
							"R\002)";
	static char fmt_900[] = "(2x,//,\002 SINGLE SCATTERING POINT TO SOURCE P"
							"ATHS \002)";
	static char fmt_950[] = "(\002 SCTTR SCTTR SUBTENDED  SOLAR   PATH  RELA"
							"TIVE  SCTTR   MOLECULAR  \002)";
	static char fmt_952[] = "(\002 POINT  ALT    ANGLE   ZENITH  ZENITH AZIM"
							"UTH   ANGLE   PHASE F    \002/)";
	static char fmt_955[] = "(\002  SUN PATH \002,i3,\002 PASSES THROUGH A T"
							"ANGENT HEIGHT\002)";
	static char fmt_970[] = "(\002  SCATTERING POINT \002,i3,\002 IS IN THE "
							"SHADE\002)";
	static char fmt_917[] = "(\002  SOLAR ZENITH CORRECTION FOR BENDING ="
							" \002,f10.3)";
	static char fmt_951[] = "(1x,i3,6(1x,f7.2),(1x,e10.3))";

	/* System generated locals */
	long i__1, i__2;
	float r__1, r__2;
	double d__1;

	/* Builtin functions */
	long s_wsfe(cilist *), e_wsfe(void), do_fio(long *, char *, long);
	double cos(double), pow_dd(double *, double *);

	/* Local variables */
	static long j, k, l, m;
	static float az[35];
	static long ll;
	static float h1d, h2d;
	static long lp1;
	extern double del_(float *, float *, float *, long *);
	static long ljd[68];
	extern /* Subroutine */ int geo_(long *, float *, long *);
	static float rhd[35];
	static long itd;
	extern double psi_(float *, float *, float *, long *, long *);
	static long ljp1;
	static float angd, betd;
	static long iarb, lend;
	static float delo;
	static long ljdl;
	static float rngd, relh, phio, phis, corr, psio, htop, angl0;
	static long iarbo;
	static float tbdum[68];
	static long jiter;
	static float wpdum[4284] /* was [68][63] */, psist, thtst, psist2,
		bendng, sangle, cosang;
	static long ikmaxd;
	extern double sctang_(float *, float *, float *, long *);
	static float thetao;
	extern /* Subroutine */ int psidel_(float *, float *, float *, float *, float *, float *, float *, long *);
	static float betast, thetas;
	extern /* Subroutine */ int interp_(long *, float *, float *, float *,
										float *, float *, float *);
	static long jturnd;

	/* Fortran I/O blocks */
	static cilist io___1277 = {0, 0, 0, fmt_960, 0};
	static cilist io___1278 = {0, 0, 0, fmt_961, 0};
	static cilist io___1279 = {0, 0, 0, fmt_900, 0};
	static cilist io___1301 = {0, 0, 0, fmt_950, 0};
	static cilist io___1302 = {0, 0, 0, fmt_952, 0};
	static cilist io___1310 = {0, 0, 0, fmt_955, 0};
	static cilist io___1313 = {0, 0, 0, fmt_970, 0};
	static cilist io___1314 = {0, 0, 0, fmt_917, 0};
	static cilist io___1321 = {0, 0, 0, fmt_951, 0};

	/*                                                                       SSG  120 */
	/*     THIS ROUTINE DRIVES THE LOWTRAN GEOMETRY ROUTINES REPEATEDLY      SSG  130 */
	/*     TO OBTAIN THE ABSORBER AMOUNTS FROM THE SCATTERING POINTS ON      SSG  140 */
	/*     THE OPTICAL PATH TO THE EXTRATERRESTRIAL SOURCE, NECESSARY        SSG  150 */
	/*     TO DO THE LAYER BY LAYER SINGLE SCATTERING RADIANCE CALCULATION.  SSG  160 */
	/*                                                                       SSG  170 */
	/*     MOLECULAR AND HENYEY-GREENSTEIN PHASE FUNCTIONS                   SSG  390 */
	/*     NOTE; UNITS ARE (STER-1), X=COS(SCATTERING ANGLE)                 SSG  400 */
	/*     PFMOL(X) = (3/16*PI)*((1+DPL)+(1-DPL)*X**2)*2/(2+DPL)             SSG* 402 */
	/*     WHERE: DPL (THE DEPOLARIZATION RATIO) = 0.0279                    SSG* 406 */
	cntrl_1.iklo = 1;
	ifil_1.npr = 1;
	cntrl_1.issgeo = 1;
	/*     SPECIFY THE GEOMETRICAL CONFIGURATION                             SSG  460 */
	if (*iparm == 2)
	{
		goto L1;
	}
	thetao = *parm1;
	phio = *parm2;
	thetas = *parm3;
	phis = *parm4;
	goto L2;
L1:
	psio = *parm1;
	delo = *parm2;
L2:
	if (*iparm != 0)
	{
		goto L5;
	}
	if (dabs(thetao) < 89.5f)
	{
		goto L5;
	}
	if (thetao > 0.f)
	{
		goto L4;
	}
	/*     OBSERVER IS AT OR NEAR THE SOUTH POLE, REMAP TO EQUATOR           SSG  590 */
	io___1277.ciunit = ifil_1.ipr;
	s_wsfe(&io___1277);
	e_wsfe();
	*psipo -= phis;
	thetao = 0.f;
	phio = 0.f;
	thetas = 0.f;
	phis = thetas + 90.f;
	goto L5;
L4:
	/*     OBSERVER IS AT OR NEAR THE NORTH POLE, REMAP TO EQUATOR           SSG  680 */
	io___1278.ciunit = ifil_1.ipr;
	s_wsfe(&io___1278);
	e_wsfe();
	*psipo = phis - *psipo;
	thetao = 0.f;
	phio = 0.f;
	thetas = 0.f;
	phis = 90.f - thetas;
L5:
	io___1279.ciunit = ifil_1.ipr;
	s_wsfe(&io___1279);
	e_wsfe();
	/*                                                                       SSG  770 */
	/*     SAVE OPTICAL PATH PARAMETERS AND AMOUNTS                          SSG  780 */
	/*                                                                       SSG  790 */
	jturnd = sols_1.jturn;
	ikmaxd = cntrl_1.ikmax + 1;
	h1d = card3_1.h1;
	h2d = card3_1.h2;
	angd = card3_1.angle;
	rngd = card3_1.range;
	betd = card3_1.beta;
	card3_1.beta = 0.f;
	lend = card3_1.len;
	itd = card1_1.itype;
	parmtr_1.imax = cntrl_1.ml;
	i__1 = parmtr_1.imax;
	for (j = 1; j <= i__1; ++j)
	{
		az[j - 1] = rfrpth_1.zp[j - 1];
		/* L10: */
		rhd[j - 1] = _BLNK__4.relhum[j - 1];
	}
	i__1 = ikmaxd;
	for (j = 1; j <= i__1; ++j)
	{
		tbdum[j - 1] = _BLNK__4.tbby[j - 1];
		ljd[j - 1] = sols_1.lj[j - 1];
		if (ljd[j - 1] > parmtr_1.imax)
		{
			ljd[j - 1] = parmtr_1.imax;
		}
		i__2 = cntrl_1.kmax;
		for (k = 1; k <= i__2; ++k)
		{
			/* L11: */
			wpdum[j + k * 68 - 69] = _BLNK__4.wpath[j + k * 68 - 69];
		}
	}
	--parmtr_1.imax;
	/*                                                                       SSG 1010 */
	/*     ESTABLISH PSIO AND DELO                                           SSG 1020 */
	iarbo = 0;
	if (card3_1.angle < .01f || card3_1.angle > 179.99f)
	{
		iarbo = 1;
	}
	/*                                                                       SSG 1050 */
	if (*iparm != 2)
	{
		psidel_(&thetas, &phis, &thetao, &phio, psipo, &psio, &delo, &iarbo);
	}
	/*     INITIAL CONDITIONS AT THE OBSERVER                                SSG 1080 */
	iarb = iarbo;
	betast = 0.f;
	if (iarbo == 0)
	{
		psist = psio;
	}
	angl0 = delo;
	/*                                                                       SSG 1130 */
	/*     LOOP OVER THE POINT TO SUN PATHS TO OBTAIN AMOUNTS                SSG 1140 */
	/*                                                                       SSG 1150 */
	io___1301.ciunit = ifil_1.ipr;
	s_wsfe(&io___1301);
	e_wsfe();
	io___1302.ciunit = ifil_1.ipr;
	s_wsfe(&io___1302);
	e_wsfe();
	i__2 = ikmaxd;
	for (l = cntrl_1.iklo; l <= i__2; ++l)
	{
		if (lend == 1 || jturnd != 0)
		{
			goto L20;
		}
		/*     SHORT PATH, UP                                                    SSG 1240 */
		card3_1.h1 = az[l - 1];
		relh = rhd[l - 1];
		thtst = sols_1.atheta[l - 1];
		if (l >= 2)
		{
			betast += sols_1.adbeta[l - 2];
		}
		goto L30;
	L20:
		/*     LONG PATH, OR SHORT PATH DOWN                                     SSG 1310 */
		if (l >= 2)
		{
			betast += sols_1.adbeta[ljd[l - 2] - 1];
		}
		if (l >= jturnd)
		{
			goto L25;
		}
		ljp1 = ljd[l - 1] + 1;
		card3_1.h1 = az[ljp1 - 1];
		relh = rhd[ljp1 - 1];
		thtst = 180.f - sols_1.atheta[ljp1 - 1];
		goto L30;
	L25:
		ljdl = ljd[l - 1];
		card3_1.h1 = az[ljdl - 1];
		relh = rhd[ljdl - 1];
		thtst = sols_1.atheta[ljdl - 1];
		if (l == jturnd)
		{
			thtst = 180.f - sols_1.atheta[ljdl - 1];
		}
	L30:
		sols_1.ah1[l - 1] = card3_1.h1;
		sols_1.arh[l - 1] = relh;
		if (l < 2)
		{
			goto L35;
		}
		psist = psi_(&psio, &delo, &betast, &iarb, &iarbo);
		angl0 = del_(&psio, &delo, &betast, &iarbo);
	L35:
		corr = 0.f;
		/*     RANGE=UNKNOWN                                                     SSG 1510 */
		card1_1.itype = 3;
		for (jiter = 1; jiter <= 4; ++jiter)
		{
			card3_1.h2 = 0.f;
			card3_1.angle = angl0 - corr;
			card3_1.len = 0;
			if (card3_1.angle <= 90.f)
			{
				goto L40;
			}
			card3_1.len = 1;
			io___1310.ciunit = ifil_1.ipr;
			s_wsfe(&io___1310);
			do_fio(&c__1, (char *)&l, (long)sizeof(long));
			e_wsfe();
		L40:
			htop = parmtr_1.zmax;
			if (card3_1.h1 < htop || card3_1.len == 1)
			{
				goto L60;
			}
			/*     SCATTERING POINT IS AT OR ABOVE HTOP AND LEN=0,                   SSG 1640 */
			/*     SET W(K)=0.0 AND CONTINUE                                         SSG 1650 */
			i__1 = cntrl_1.kmax;
			for (k = 1; k <= i__1; ++k)
			{
				/* L50: */
				_BLNK__4.w[k - 1] = 0.f;
			}
			goto L100;
		/*                                                                       SSG 1690 */
		L60:
			geo_(ierror, &bendng, maxgeo);
			/*                                                                       SSG 1710 */
			/*     IERROR=-5 IF SCATTERING POINT IS IN THE SHADE, ALSO SET W(K)=-5.0 SSG 1720 */
			if (*ierror != -5)
			{
				goto L80;
			}
			io___1313.ciunit = ifil_1.ipr;
			s_wsfe(&io___1313);
			do_fio(&c__1, (char *)&l, (long)sizeof(long));
			e_wsfe();
			i__1 = cntrl_1.kmax;
			for (k = 1; k <= i__1; ++k)
			{
				/* L70: */
				_BLNK__4.w[k - 1] = -5.f;
			}
			*ierror = 0;
			goto L100;
		L80:
			/*     SOLAR ZENITH BENDING CORRECTION                                   SSG 1810 */
			if (jiter > 1)
			{
				io___1314.ciunit = ifil_1.ipr;
				s_wsfe(&io___1314);
				do_fio(&c__1, (char *)&corr, (long)sizeof(float));
				e_wsfe();
			}
			if ((r__1 = corr - bendng, dabs(r__1)) < .1f)
			{
				goto L100;
			}
			/* L90: */
			corr = bendng;
		}
	L100:
		sangle = sctang_(&card3_1.angle, &thtst, &psist, &iarb);
		cosang = cos(cnstns_1.ca * sangle);
		/*     LOAD MOLECULAR PHASE FUNCTION ARRAY                               SSG 1880 */
		/* Computing 2nd power */
		r__1 = cosang;
		sols_1.pr[l - 1] = .06050402f + .0572197f * (r__1 * r__1);
		/*     LOAD AEROSOL PHASE FUNCTION ARRAY                                 SSG 1900 */
		/*     HENYEY-GREENSTEIN                                                 SSG 1910 */
		if (*iph != 0)
		{
			goto L105;
		}
		/* Computing 2nd power */
		r__1 = *g;
		/* Computing 2nd power */
		r__2 = *g;
		d__1 = (double)(1.f + r__2 * r__2 - 2.f * *g * cosang);
		sols_1.pa[l - 1] = (1.f - r__1 * r__1) / (4.f * cnstns_1.pi * pow_dd(&d__1, &c_b1937));
		goto L115;
	L105:
		if (*iph != 1)
		{
			goto L110;
		}
		/*     USER SUPPLIED PHASE FUNCTION                                      SSG 1970 */
		/*     DETERMINE ALTITUDE AND ANGLE INDICES                              SSG 1980 */
		m = 4;
		if (card3_1.h1 <= 30.f)
		{
			m = 3;
		}
		if (card3_1.h1 <= 10.f)
		{
			m = 2;
		}
		if (card3_1.h1 <= 2.f)
		{
			m = 1;
		}
		i__1 = usrdta_1.nangls;
		for (ll = 1; ll <= i__1; ++ll)
		{
			/*                                                                       SSG 2040 */
			/*    INTERPOLATION CORRECTION FOR ANGLE = TO ANGLES READ IN             SSG 2050 */
			/*                                                                       SSG 2060 */
			if (usrdta_1.angf[ll - 1] == sangle)
			{
				sols_1.pa[l - 1] = usrdta_1.f[m + (ll << 2) - 5];
				goto L115;
			}
			if (usrdta_1.angf[ll - 1] > sangle)
			{
				goto L107;
			}
			/* L106: */
		}
	L107:
		lp1 = ll;
		--ll;
		interp_(&c__2, &sangle, &usrdta_1.angf[ll - 1], &usrdta_1.angf[lp1 - 1], &sols_1.pa[l - 1], &usrdta_1.f[m + (ll << 2) - 5], &usrdta_1.f[m + (lp1 << 2) - 5]);
		goto L115;
	L110:
		/*     V DEPENDENT MIE DATA BASE, SAVE SCATTERING ANGLE INSTEAD          SSG 2180 */
		sols_1.pa[l - 1] = sangle;
	L115:
		/*     LOAD AMOUNTS FROM W(K) INTO WPATHS(L,K)                           SSG 2210 */
		i__1 = cntrl_1.kmax;
		for (k = 1; k <= i__1; ++k)
		{
			/* L120: */
			sols_1.wpaths[l + k * 68 - 69] = _BLNK__4.w[k - 1];
		}
		/*     REVERSE SIGN CONVENTION (TO + E OF N) FOR PRINTED OUTPUT          SSG 2240 */
		psist2 = -psist;
		/*                                                                       SSG 2260 */
		/*    CSZEN IS COSINE OF SOLAR ZENTIH FOR EACH LAYER                     SSG 2270 */
		/*                                                                       SSG 2280 */
		sols_1.cszen[l - 1] = cos(card3_1.angle * cnstns_1.ca);
		io___1321.ciunit = ifil_1.ipr;
		s_wsfe(&io___1321);
		do_fio(&c__1, (char *)&l, (long)sizeof(long));
		do_fio(&c__1, (char *)&card3_1.h1, (long)sizeof(float));
		do_fio(&c__1, (char *)&betast, (long)sizeof(float));
		do_fio(&c__1, (char *)&card3_1.angle, (long)sizeof(float));
		do_fio(&c__1, (char *)&thtst, (long)sizeof(float));
		do_fio(&c__1, (char *)&psist2, (long)sizeof(float));
		do_fio(&c__1, (char *)&sangle, (long)sizeof(float));
		do_fio(&c__1, (char *)&sols_1.pr[l - 1], (long)sizeof(float));
		e_wsfe();
		/* L130: */
	}
	/*                                                                       SSG 2330 */
	/*     RESTORE OPTICAL PATH AMOUNTS                                      SSG 2340 */
	/*                                                                       SSG 2350 */
	cntrl_1.ikmax = ikmaxd - 1;
	card3_1.h1 = h1d;
	card3_1.h2 = h2d;
	sols_1.angsun = card3_1.angle;
	card3_1.angle = angd;
	card3_1.range = rngd;
	card3_1.beta = betd;
	card3_1.len = lend;
	card1_1.itype = itd;
	i__2 = ikmaxd;
	for (j = 1; j <= i__2; ++j)
	{
		_BLNK__4.tbby[j - 1] = tbdum[j - 1];
		sols_1.lj[j - 1] = ljd[j - 1];
		i__1 = cntrl_1.kmax;
		for (k = 1; k <= i__1; ++k)
		{
			/* L160: */
			_BLNK__4.wpath[j + k * 68 - 69] = wpdum[j + k * 68 - 69];
		}
	}
	ifil_1.npr = card1_1.noprt;
	/*                                                                       SSG 2510 */
	/*     FORMATS                                                           SSG 2520 */
	/*                                                                       SSG 2530 */
	/* L920: */
	/* L925: */
	/* L930: */
	/* L931: */
	/* L940: */
	return 0;
} /* ssgeo_ */

/* Subroutine */ int psidel_(float *thetas, float *phis, float *thetao, float *phio, float *psipo2, float *psio, float *delo, long *iarbo)
{
	/* Initialized data */

	static float epsiln = 1e-5f;

	/* System generated locals */
	float r__1;

	/* Builtin functions */
	double sin(double), cos(double), tan(double), acos(double), atan(double);

	/* Local variables */
	static float dph, cto, cts, sto, tto, sts, tts, dphi, dtht, thto, thts,
		cdphi, denom, sdphi, psipo, psiso, anumer;

	/*                                                                       PSI  110 */
	/*     THIS ROUTINE CALCULATES PSIO (THE RELATIVE AZIMUTH BETWEEN THE    PSI  120 */
	/*     LINE OF SIGHT AND THE DIRECT SOLAR PATH, AT THE OBSERVER)         PSI  130 */
	/*     AND DELO (THE ANGLE SUBTENDED AT THE EARTH'S CENTER BY THE        PSI  140 */
	/*     OBSERVER AND THE SUBSOLAR POINT).                                 PSI  150 */
	/*                                                                       PSI  190 */
	/*     CHANGE CONVENTION FOR PSIPO FROM (EAST OF NORTH) TO (NORTH OF EASTPSI  200 */
	/*     FOR COMPUTATIONAL PURPOSES. RANGE IS -180 TO +180.                PSI  210 */
	psipo = 90.f - *psipo2;
	if (psipo > 180.f)
	{
		psipo += -360.f;
	}
	/*                                                                       PSI  240 */
	dphi = *phis - *phio;
	dtht = *thetas - *thetao;
	thts = *thetas / cnstns_1.deg;
	thto = *thetao / cnstns_1.deg;
	dph = dphi / cnstns_1.deg;
	sts = sin(thts);
	sto = sin(thto);
	cts = cos(thts);
	cto = cos(thto);
	sdphi = sin(dph);
	cdphi = cos(dph);
	tts = tan(thts);
	tto = tan(thto);
	/*                                                                       PSI  380 */
	/*     CALCULATE DELO,  CHECK FOR SPECIAL CASES%                         PSI  390 */
	if (dabs(dphi) > epsiln)
	{
		goto L10;
	}
	/*     COLONGITUDE                                                       PSI  410 */
	*delo = dabs(dtht);
	goto L30;
L10:
	if (dabs(dtht) > epsiln)
	{
		goto L20;
	}
	/*     COLATITUDE                                                        PSI  450 */
	*delo = dabs(dphi);
	goto L30;
/*     GENERAL CASE                                                      PSI  480 */
L20:
	*delo = cnstns_1.deg * acos(cts * cto * cdphi + sts * sto);
L30:
	if (*delo <= epsiln)
	{
		*delo = 0.f;
	}
	/*     CALCULATE PSIO (=PSISO-PSIPO)                                     PSI  510 */
	/*     CHECK FOR SPECIAL CASES WHERE EITHER PSISO OR PSIPO ARE ARBITRARY PSI  520 */
	/*                                                                       PSI  530 */
	/*     VERTICAL OPTICAL PATH, PSIPO IS ARBITRARY, THIS CASE WAS FLAGGED  PSI  540 */
	/*     IN SSGEO BY SETTING IARBO=1                                       PSI  550 */
	/*                                                                       PSI  560 */
	/*     OBSERVER AND SUBSOLAR POINT COINCIDE, PSISO IS ARBITRARY          PSI  570 */
	if (*delo == 0.f)
	{
		*iarbo += 2;
	}
	if (*iarbo == 0)
	{
		goto L40;
	}
	/*     IARBO=0,1,2,3 FOR% PSIO DEFINITE, PSIPO ARBITRARY, PSISO ARBITRARYPSI  600 */
	/*                        BOTH PSIPO AND PSISO ARBITRARY, RESPECTIVELY.  PSI  610 */
	return 0;
L40:
	anumer = tto * cdphi - tts;
	/* Computing 2nd power */
	r__1 = tto;
	denom = (r__1 * r__1 + 1.f) * cto * sdphi;
	if (dabs(anumer) > epsiln)
	{
		goto L50;
	}
	/*     NUMERATOR=0.0, GREAT CIRCLE CONTAINING THE OBSERVER AND THE SUBSOLPSI  660 */
	/*     POINT IS DUE EAST-WEST AT THE OBSERVER                            PSI  670 */
	psiso = 0.f;
	if (dphi > 0.f)
	{
		psiso = 180.f;
	}
	goto L90;
L50:
	if (dabs(denom) > epsiln)
	{
		goto L60;
	}
	/*     DENOMINATOR =0.0, ATAN(INFINITY)=+90 OR -90                       PSI  720 */
	psiso = 90.f;
	if (dtht < 0.f)
	{
		psiso = -90.f;
	}
	goto L90;
/*     GENERAL CASE                                                      PSI  760 */
L60:
	psiso = cnstns_1.deg * atan(anumer / denom);
	/*     ATAN RETURNS ARGUMENTS BETWEEN -90 AND 90, MAY NEED TO CORRECT    PSI  780 */
	/*     NO CORRECTION NECESSARY                                           PSI  790 */
	if (dphi < 0.f)
	{
		goto L90;
	}
	/*     CORRECTION NECESSARY                                              PSI  810 */
	if (dphi > 0.f)
	{
		goto L70;
	}
	/*     DPHI=0.0                                                          PSI  830 */
	psiso = 90.f;
	if (dtht < 0.f)
	{
		psiso = -90.f;
	}
	goto L90;
/*     DPHI.GT.0.0                                                       PSI  870 */
L70:
	if (psiso > 0.f)
	{
		goto L80;
	}
	psiso += 180.f;
	goto L90;
L80:
	psiso += -180.f;
L90:
	if (*phis > 180.f)
	{
		psipo += 180.f;
		if (*phis > 360.f)
		{
			psipo += -360.f;
		}
		if (psiso < 0.f)
		{
			psiso = 180.f - psiso;
		}
	}
	*psio = psiso - psipo;
	/*     RANGE OF PSIO IS -180.0 TO 180.0, CORRECT IF NECESSARY            PSI  940 */
	if (*psio < -180.f)
	{
		*psio += 360.f;
	}
	if (*psio > 180.f)
	{
		*psio += -360.f;
	}
	/*                                                                       PSI  970 */
	return 0;
} /* psidel_ */

double sctang_(float *anglst, float *thtst, float *psist, long *iarb)
{
	/* System generated locals */
	float ret_val;

	/* Builtin functions */
	double cos(double), acos(double), sin(double);

	/* Local variables */
	static float x, psi, pthzen, sunzen;

	/*                                                                       SCT  110 */
	/*     FUNCTION SCTANG RETURNS THE SCATTERING ANGLE (THAT IS, THE        SCT  120 */
	/*     ANGLE BETWEEN THE SUN'S RAYS AND THE LINE OF SIGHT) AT ANY        SCT  130 */
	/*     POINT ALONG THE OPTICAL PATH.                                     SCT  140 */
	/*                                                                       SCT  170 */
	sunzen = *anglst / cnstns_1.deg;
	pthzen = *thtst / cnstns_1.deg;
	if (*iarb == 0)
	{
		goto L10;
	}
	/*     SPECIAL CASES IF PSI IS ARBITRARY                                 SCT  210 */
	ret_val = cnstns_1.deg * acos(cos(sunzen) * cos(pthzen));
	return ret_val;
L10:
	psi = *psist / cnstns_1.deg;
	/*     GENERAL CASE                                                      SCT  260 */
	x = sin(sunzen) * sin(pthzen) * cos(psi) + cos(sunzen) * cos(pthzen);
	ret_val = cnstns_1.deg * acos(x);
	return ret_val;
} /* sctang_ */

double psi_(float *psio, float *delo, float *beta, long *iarb, long *iarbo)
{
	/* Initialized data */

	static float epsiln = 1e-5f;

	/* System generated locals */
	float ret_val, r__1;

	/* Builtin functions */
	double sin(double), cos(double), atan(double);

	/* Local variables */
	static float betar, denom, delor, psior, anumer;

	/*                                                                       FSI  110 */
	/*     FUNCTION PSI RETURNS THE VALUE OF SOLAR AZIMUTH RELATIVE TO       FSI  120 */
	/*     THE LINE OF SIGHT, AT THE CURRENT SCATTERING LOCATION             FSI  130 */
	delor = *delo / cnstns_1.deg;
	betar = *beta / cnstns_1.deg;
	if (*iarbo == 0)
	{
		goto L5;
	}
	/*     SPECIAL CASES WHEN PSIO IS ARBITRARY                              FSI  200 */
	*iarb = *iarbo;
	if (*iarbo == 1 || *iarbo == 3)
	{
		return ret_val;
	}
	if (*beta <= epsiln)
	{
		return ret_val;
	}
	/*     PSI=180.0 (MOVED OUT FROM UNDER THE SUN)                          FSI  240 */
	*iarb = 0;
	ret_val = 180.f;
	return ret_val;
L5:
	/*     GENERAL CASE                                                      FSI  290 */
	psior = *psio / cnstns_1.deg;
	*iarb = 0;
	anumer = sin(delor) * sin(psior);
	denom = cos(betar) * sin(delor) * cos(psior) - sin(betar) * cos(delor);
	/*     SPECIAL CASES                                                     FSI  340 */
	/*     NUMERATOR GOES TO ZERO IN THE FOLLOWING 3 CASES                   FSI  350 */
	/* 1)  DELO=0.0                                                          FSI  360 */
	if (*delo > epsiln)
	{
		goto L20;
	}
	if (*beta > epsiln)
	{
		goto L10;
	}
	*iarb = 2;
	return ret_val;
L10:
	ret_val = 180.f;
	return ret_val;
/* 2)  PSIO=0.0                                                          FSI  430 */
L20:
	if (dabs(*psio) > epsiln)
	{
		goto L40;
	}
	if ((r__1 = *beta - *delo, dabs(r__1)) >= epsiln)
	{
		goto L30;
	}
	/*     SCATTERING POINT IS DIRECTLY UNDER THE SUN                        FSI  460 */
	*iarb = 2;
	return ret_val;
L30:
	if (*beta < *delo)
	{
		ret_val = 0.f;
	}
	if (*beta > *delo)
	{
		ret_val = 180.f;
	}
	return ret_val;
/* 3)  PSIO=180.0                                                        FSI  520 */
L40:
	if (dabs(*psio) < 180.f - epsiln)
	{
		goto L60;
	}
	ret_val = 180.f;
	return ret_val;
L60:
	/*     DENOMINATOR CAN GO TO ZERO FOR THE FOLLOWING 2 CASES              FSI  570 */
	/* 1)  BETA=DELO AND PSIO=0.0                                            FSI  580 */
	/*     THIS CASE WAS HANDLED EARLIER                                     FSI  590 */
	/* 2)  GENERAL CASE                                                      FSI  600 */
	if (dabs(denom) > epsiln)
	{
		goto L80;
	}
	if (*psio < 0.f)
	{
		ret_val = -90.f;
	}
	if (*psio > 0.f)
	{
		ret_val = 90.f;
	}
	return ret_val;
L80:
	ret_val = cnstns_1.deg * atan(anumer / denom);
	/*     NOTE ATAN RETURNS ARGUMENTS BETWEEN -90 AND 90, PSI               FSI  670 */
	/*     AND PSIO SHOULD BE OF THE SAME SIGN.                              FSI  680 */
	if (*psio > 0.f && ret_val < 0.f)
	{
		ret_val += 180.f;
	}
	if (*psio < 0.f && ret_val > 0.f)
	{
		ret_val += -180.f;
	}
	return ret_val;
} /* psi_ */

double del_(float *psio, float *delo, float *beta, long *iarbo)
{

	/* System generated locals */
	float ret_val;

	/* Builtin functions */
	double cos(double), sin(double), acos(double);

	/* Local variables */
	static float x, betar, delor, psior;

	/*                                                                       DEL  110 */
	/*     FUNCTION DEL RETURNS THE VALUE OF THE SUN'S ZENITH ANGLE          DEL  120 */
	/*     AT ANY POINT ALONG THE OPTICAL PATH BASED UPON STRAIGHT           DEL  130 */
	/*     LINE GEOMETRY (NO REFRACTION). THIS ANGLE IS USED TO SPECIFY      DEL  140 */
	/*     THE SCATTERING POINT TO SUN PATHS. THE BENDING DUE TO REFRACTION  DEL  150 */
	/*     ALONG THIS PATH IS DETERMINED BY THE GEO ROUTINES. IF THE BENDING DEL  160 */
	/*     IS GREATER THAN ONE DEGREE THE ZENITH ANGLE IS CORRECTED ACCORDINGDEL  170 */
	/*     AND THE PATH CALCULATION IS REPEATED.                             DEL  180 */
	/*                                                                       DEL  220 */
	if (*iarbo == 0)
	{
		goto L10;
	}
	/*     SPECIAL CASES IF PSIO IS ARBITRARY                                DEL  240 */
	if (*iarbo == 1)
	{
		ret_val = *delo;
	}
	if (*iarbo == 2)
	{
		ret_val = *beta;
	}
	if (*iarbo == 3)
	{
		ret_val = 0.f;
	}
	return ret_val;
L10:
	psior = *psio / cnstns_1.deg;
	delor = *delo / cnstns_1.deg;
	betar = *beta / cnstns_1.deg;
	/*     GENERAL CASE                                                      DEL  330 */
	x = cos(delor) * cos(betar) + sin(delor) * sin(betar) * cos(psior);
	ret_val = cnstns_1.deg * acos(x);
	return ret_val;
} /* del_ */

/* Subroutine */ int ssrad_(long *iph, long *ik, long *itzero,
							long *ipath, float *v, float *sumssr)
{
	/* System generated locals */
	long i__1;

	/* Local variables */
	static float xa1, xa2, xm1, xm2, tx6, tx7, tx9;
	static long ikk;
	static float tx10, dtasp, dtmsp;
	extern /* Subroutine */ int phasef_(float *, long *, float *, float *,
										float *, float *);

	/*                                                                       SSR  110 */
	/*     SUBROUTINE SSRAD PERFORMS THE LAYER BY LAYER SINGLE SCATTERING    SSR  120 */
	/*     RADIANCE SUM.                                                     SSR  130 */
	/*                                                                       SSR  140 */
	if (*itzero == 1)
	{
		goto L60;
	}
	tx6 = _BLNK__4.tx[5];
	tx7 = _BLNK__4.tx[6];
	tx9 = _BLNK__4.tx[8];
	tx10 = _BLNK__4.tx[9];
	if ((i__1 = *ipath - 2) < 0)
	{
		goto L10;
	}
	else if (i__1 == 0)
	{
		goto L20;
	}
	else
	{
		goto L30;
	}
L10:
	/* C    ISKIP = 0                                                         SSR  330 */
	/*     INITIAL CONDITIONS                                                SSR  340 */
	/*     SINGLE SCATTERING RADIANCE SUM                                    SSR  350 */
	*sumssr = 0.f;
	/*     OPTICAL PATH TRANSMITTANCES                                       SSR  370 */
	srad_1.tasp2 = 1.f;
	srad_1.tmsp2 = 1.f;
	/*     L PATH TRANSMITTANCE                                              SSR  400 */
	srad_1.teb2 = tx9;
	/*     MOLECULAR AND AEROSOL PHASE FUNCTIONS                             SSR  420 */
	srads_1.pmol2 = sols_1.pr[*ik - 1];
	srads_1.paer2 = sols_1.pa[*ik - 1];
	if (*iph == 2)
	{
		phasef_(v, ik, &sols_1.ah1[*ik - 1], &sols_1.pa[*ik - 1], &sols_1.arh[*ik - 1], &srads_1.paer2);
	}
	return 0;
L20:
	/*     CURRENT L PATH TRANSMITTANCE                                      SSR  490 */
	srad_1.teb1 = tx9;
	/*     CURRENT MOLECULAR AND AEROSOL PHASE FUNCTIONS                     SSR  510 */
	srads_1.pmol1 = sols_1.pr[*ik];
	srads_1.paer1 = sols_1.pa[*ik];
	ikk = *ik + 1;
	if (*iph == 2)
	{
		phasef_(v, &ikk, &sols_1.ah1[ikk - 1], &sols_1.pa[ikk - 1], &sols_1.arh[ikk - 1], &srads_1.paer1);
	}
	return 0;
L30:
	/*     CURRENT OPTICAL PATH TRANSMITTANCES                               SSR  590 */
	srad_1.tasp1 = tx7 / tx10;
	srad_1.tmsp1 = tx6;
	/*     SINGLE SCATTERING RADIANCE CALCULATION                            SSR  620 */
	if (srad_1.tasp1 == 0.f || srad_1.tmsp1 == 0.f || srad_1.tmsp2 == 0.f ||
		srad_1.tasp2 == 0.f)
	{
		goto L50;
	}
	xa1 = srads_1.paer1 * srad_1.teb1 / srad_1.tasp1;
	xa2 = srads_1.paer2 * srad_1.teb2 / srad_1.tasp2;
	xm1 = srads_1.pmol1 * srad_1.teb1 / srad_1.tmsp1;
	xm2 = srads_1.pmol2 * srad_1.teb2 / srad_1.tmsp2;
	dtasp = srad_1.tasp2 - srad_1.tasp1;
	dtmsp = srad_1.tmsp2 - srad_1.tmsp1;
	/*     COULD ADD A CHECK FOR SMALL DTMSP,DTASP AND BYPASS CALCULATION    SSR  710 */
	*sumssr += (dtasp * (xa1 + xa2) + dtmsp * (xm1 + xm2)) * .5f;
/*     RESET L AND OPTICAL PATH  TRANSMITTANCES                          SSR  730 */
L50:
	srad_1.tasp2 = srad_1.tasp1;
	srad_1.teb2sv = srad_1.teb2;
	srad_1.tmsp2 = srad_1.tmsp1;
	srad_1.teb2 = srad_1.teb1;
	/*     RESET PHASE FUNTION VALUES                                        SSR  790 */
	srads_1.paer2 = srads_1.paer1;
	srads_1.pmol2 = srads_1.pmol1;
L60:
	return 0;
} /* ssrad_ */

/* Subroutine */ int source_(float *vv, long *isourc, long *iday, float *angle, float *ss)
{
	/* Initialized data */

	/*
	The index of the starting day of each month in the year
	I.e. June 1st = 152nd day. January 1st = 1st Day etc.

	@see https://landweb.modaps.eosdis.nasa.gov/browse/calendar.html
	@see https://www.atmos.anl.gov/ANLMET/OrdinalDay.txt
	*/
	static long nday[13] = {1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335,
							366};

	static float rat[13] = {1.034f, 1.03f, 1.019f, 1.001f, .985f, .972f, .967f,
							.971f, .982f, .998f, 1.015f, 1.029f, 1.034f};
	static float phs[17] = {100.f, 73.2f, 57.8f, 42.3f, 32.f, 23.3f, 16.7f, 12.4f,
							8.7f, 6.7f, 4.7f, 3.6f, 2.4f, 1.2f, .9f, .4f, .002f};
	static float alb[29] = {.001f, .01f, .03f, .075f, .1f, .13f, .155f, .17f, .178f,
							.185f, .2f, .211f, .231f, .25f, .275f, .289f, .285f, .287f, .3f, .29f, .3f,
							.31f, .313f, .319f, .329f, .339f, .345f, .35f, .4f};

	static long i__;
	static float v;
	static long i1, ip;
	extern double sun_(float *);

	/*     SUBROUITNE SOURCE CONTAINS THE SOLAR INTENSITY DATA AS A          SOR  120 */
	/*     FUNTION OF WAVELENGTH. THIS ROUTINE IS ALSO CAPABLE OF CALCULATINGSOR  130 */
	/*     LUNAR INTENSITY BASED ON THE PHASE ANGLE BETWEEN THE SUN, MOON ANDSOR  140 */
	/*     EARTH. CORRECTIONS ARE MADE FOR THE SUN'S ELLIPTIC ORBIT.         SOR  150 */
	/*                                                                       SOR  160 */
	v = 1e4f / *vv;
	if (*vv <= 0.f)
	{
		v = 1e38f;
	}
	if (*isourc != 1)
	{
		goto L50;
	}
	if (icll_1.icall == 1)
	{
		goto L20;
	}
	/*                                                                       SOR  300 */
	/*     MOON PHASE ANGLE FACTOR                                           SOR  310 */
	/*                                                                       SOR  320 */
	icll_1.fphs = 0.f;
	if (*angle > 160.f)
	{
		goto L20;
	}
	ip = *angle / 10.f;
	if ((float)(ip * 10) == *angle)
	{
		goto L10;
	}
	icll_1.fphs = phs[ip] + (*angle - ip * 10.f) * (phs[ip + 1] - phs[ip]) /
								10.f;
	goto L20;
L10:
	icll_1.fphs = phs[ip];
/*                                                                       SOR  400 */
/*     GEOMETRICAL ALBEDO OF THE MOON                                    SOR  410 */
/*                                                                       SOR  420 */
L20:
	icll_1.falb = .4f;
	if (v >= 5.f)
	{
		goto L40;
	}
	if (v > 2.8f)
	{
		goto L30;
	}
	i1 = v * 10;
	icll_1.falb = alb[i1 - 1] + (alb[i1] - alb[i1 - 1]) * (v - i1 * .1f) *
									10.f;
	goto L40;
L30:
	icll_1.falb = alb[27] + (alb[28] - alb[27]) * (v - 2.8f) / 2.2f;
L40:
/*                                                                       SOR  510 */
/*     SUN ELLIPTIC ORBIT FACTOR                                         SOR  520 */
/*                                                                       SOR  530 */
L50:
	if (icll_1.icall == 1)
	{
		goto L90;
	}
	icll_1.forbit = 0.f;
	if (*iday > 0 && *iday < 367)
	{
		goto L55;
	}
	icll_1.forbit = 1.f;
	goto L90;
L55:
	for (i__ = 1; i__ <= 13; ++i__)
	{
		if (nday[i__ - 1] == *iday)
		{
			goto L80;
		}
		if (nday[i__ - 1] > *iday)
		{
			goto L70;
		}
		/* L60: */
	}
L70:
	icll_1.forbit = rat[i__ - 2] + (*iday - nday[i__ - 2]) * (rat[i__ - 1] - rat[i__ - 2]) / (nday[i__ - 1] - nday[i__ - 2]);
	goto L90;
L80:
	icll_1.forbit = rat[i__ - 1];
L90:
	icll_1.icall = 1;
	/*                                                                       SOR  700 */
	/*     SOLAR INTENSITY                                                   SOR  710 */
	/*                                                                       SOR  720 */
	*ss = sun_(vv) * icll_1.forbit;
	/*     CONVERT W/M-2-MICRON TO W/CM-2-MICRON                             SOR  740 */
	if (*isourc == 1)
	{
		*ss = *ss * icll_1.fphs * icll_1.falb * 2.04472e-7f;
	}
	*ss *= 1e-4f;
	return 0;
} /* source_ */

double sun_(float *v)
{
	/* Initialized data */

	static float a = 3.50187e-13f;
	static float b = 3.93281f;

	/* Format strings */
	static char fmt_900[] = "(\0020 *****  WARNING - INPUT FREQUENCY = \002,"
							"1pg12.5,\002CM-1\002,/,\002   OUTSIDE VALID RANGE OF 0 TO 57470 "
							"CM-1    *******\002,/)";

	/* System generated locals */
	float ret_val, r__1, r__2;
	double d__1, d__2;

	/* Builtin functions */
	long s_wsfe(cilist *), do_fio(long *, char *, long), e_wsfe(void);
	double pow_dd(double *, double *), r_mod(float *, float *);

	/* Local variables */
	static long i__;
	static float p;

	/* Fortran I/O blocks */
	static cilist io___1376 = {0, 6, 0, fmt_900, 0};
	static cilist io___1379 = {0, 6, 0, fmt_900, 0};

	/*                                                                       SUN  110 */
	/*        EVALUATES THE EXTRA-TERRESTRIAL SOLAR IRRADIANCE               SUN  120 */
	/*                                                                       SUN  130 */
	/*        INPUT:  V  =  FREQUENCY   (CM-1)                               SUN  140 */
	/*                VALID RANGE   0 TO 57490 (CM-1)                        SUN  150 */
	/*                    (EQUIVALENT TO WAVELENGTHS > 0.174 MICROMETERS)    SUN  160 */
	/*                                                                       SUN  170 */
	/*        OUTPUT:  SUN  =  SOLAR IRRADIANCE  (WATTS M-2 MICROMETER-1)    SUN  180 */
	/*                                                                       SUN  190 */
	/*        WRITES A WARNING MESSAGE TO TAPE6  &  RETURNS  SUN = 0         SUN  200 */
	/*            IF THE INPUT FREQUENCY IS OUT OF RANGE                     SUN  210 */
	/*                                                                       SUN  220 */
	/*       USES  BLOCK DATA SOLAR   WHICH CONTAINS THE VALUES FOR SOLARA + SUN  230 */
	/*                                                                       SUN  240 */
	/*                                                                       SUN  270 */
	/*       WM, W0, W1, W2  ARE STATEMENT FUNCTIONS USED BY                 SUN  280 */
	/*            THE 4 POINT LAGRANGE INTERPOLATION                         SUN  290 */
	/*                                                                       SUN  340 */
	/*           IF  V  IS TOO SMALL,  WRITE WARNING  +  RETURN SUN = 0      SUN  350 */
	if (*v < 0.f)
	{
		ret_val = 0.f;
		s_wsfe(&io___1376);
		do_fio(&c__1, (char *)&(*v), (long)sizeof(float));
		e_wsfe();
		return ret_val;
		/*                                                                       SUN  400 */
	}
	else if (*v >= 0.f && *v < 100.f)
	{
		/*         FOR LOW FREQUENCIES USE A POWER LAW APPROXIMATION             SUN  420 */
		d__1 = (double)(*v);
		d__2 = (double)b;
		ret_val = a * pow_dd(&d__1, &d__2);
		return ret_val;
		/*                                                                       SUN  450 */
	}
	else if (*v >= 100.f && *v < 28420.f)
	{
		/*         USE  4 POINT INTERPOLATION  ON  ARRAY  SOLARA                 SUN  470 */
		/*               WHICH IS AT  20 CM-1  SPACING  FROM 0 TO 28720 CM-1     SUN  480 */
		i__ = (long)(*v / 20.f) + 1;
		p = r_mod(v, &c_b2008) / 20.f;
		/* Computing 2nd power */
		r__1 = p;
		/* Computing 2nd power */
		r__2 = p;
		ret_val = (p * (r__1 * r__1 - 1) * sundat_1.solara[i__ + 1] - 3 * p * (p + 1) * (p - 2) * sundat_1.solara[i__] + 3 * (r__2 * r__2 - 1) * (p - 2) * sundat_1.solara[i__ - 1] - p * (p - 1) * (p - 2) * sundat_1.solara[i__ - 2]) / 6;
		return ret_val;
		/*                                                                       SUN  540 */
	}
	else if (*v >= 28420.f && *v <= 57470.f)
	{
		/*         USE  4 POINT INTERPOLATION  ON  ARRAY  SOLARB                 SUN  560 */
		/*             WHICH IS AT  10 CM-1  SPACING  FROM 28400 TO 57490 CM-1   SUN  570 */
		i__ = (long)(*v / 10.f) - 2839;
		p = r_mod(v, &c_b1750) / 10.f;
		/* Computing 2nd power */
		r__1 = p;
		/* Computing 2nd power */
		r__2 = p;
		ret_val = (p * (r__1 * r__1 - 1) * sundat_1.solarb[i__ + 1] - 3 * p * (p + 1) * (p - 2) * sundat_1.solarb[i__] + 3 * (r__2 * r__2 - 1) * (p - 2) * sundat_1.solarb[i__ - 1] - p * (p - 1) * (p - 2) * sundat_1.solarb[i__ - 2]) / 6;
		return ret_val;
		/*                                                                       SUN  630 */
	}
	else if (*v > 57470.f)
	{
		/*           IF  V  IS TOO LARGE,  WRITE WARNING  +  RETURN SUN = 0      SUN  650 */
		ret_val = 0.f;
		s_wsfe(&io___1379);
		do_fio(&c__1, (char *)&(*v), (long)sizeof(float));
		e_wsfe();
		return ret_val;
		/*                                                                       SUN  690 */
	}
	/*                                                                       SUN  710 */
	return ret_val;
} /* sun_ */

/* Subroutine */ int solar_(void)
{
	return 0;
} /* solar_ */

/* >    BLOCK DATA                                                        SOL  110 */
/*                                                                       SOL  120 */
/*                                                                       SOL  130 */
/*     COMMON /SUNDAT/   SOLARA(1440), SOLARB(2910)                      SOL  140 */
/*                                                                       SOL  220 */
/*         SOLAR SPECTRUM FROM      0 TO    800 CM-1,  IN STEPS OF 20 CM-SOL  230 */
/*         SOLAR SPECTRUM FROM    820 TO   3680 CM-1,  IN STEPS OF 20 CM-SOL  340 */
/*         SOLAR SPECTRUM FROM   3700 TO   6560 CM-1,  IN STEPS OF 20 CM-SOL  540 */
/*         SOLAR SPECTRUM FROM   6580 TO   9440 CM-1,  IN STEPS OF 20 CM-SOL  740 */
/*         SOLAR SPECTRUM FROM   9460 TO  12320 CM-1,  IN STEPS OF 20 CM-SOL  940 */
/*         SOLAR SPECTRUM FROM  12340 TO  15200 CM-1,  IN STEPS OF 20 CM-SOL 1140 */
/*         SOLAR SPECTRUM FROM  15220 TO  18080 CM-1,  IN STEPS OF 20 CM-SOL 1340 */
/*         SOLAR SPECTRUM FROM  18100 TO  20960 CM-1,  IN STEPS OF 20 CM-SOL 1540 */
/*         SOLAR SPECTRUM FROM  20980 TO  23840 CM-1,  IN STEPS OF 20 CM-SOL 1740 */
/*         SOLAR SPECTRUM FROM  23860 TO  26720 CM-1,  IN STEPS OF 20 CM-SOL 1940 */
/*         SOLAR SPECTRUM FROM  26740 TO  28780 CM-1,  IN STEPS OF 20 CM-SOL 2140 */
/*         SOLAR SPECTRUM FROM  28400 TO  29830 CM-1,  IN STEPS OF 10 CM-SOL 2290 */
/*         SOLAR SPECTRUM FROM  29840 TO  31270 CM-1,  IN STEPS OF 10 CM-SOL 2490 */
/*         SOLAR SPECTRUM FROM  31280 TO  32710 CM-1,  IN STEPS OF 10 CM-SOL 2690 */
/*         SOLAR SPECTRUM FROM  32720 TO  34150 CM-1,  IN STEPS OF 10 CM-SOL 2890 */
/*         SOLAR SPECTRUM FROM  34160 TO  35590 CM-1,  IN STEPS OF 10 CM-SOL 3090 */
/*         SOLAR SPECTRUM FROM  35600 TO  37030 CM-1,  IN STEPS OF 10 CM-SOL 3290 */
/*         SOLAR SPECTRUM FROM  37040 TO  38470 CM-1,  IN STEPS OF 10 CM-SOL 3490 */
/*         SOLAR SPECTRUM FROM  38480 TO  39910 CM-1,  IN STEPS OF 10 CM-SOL 3690 */
/*         SOLAR SPECTRUM FROM  39920 TO  41350 CM-1,  IN STEPS OF 10 CM-SOL 3890 */
/*         SOLAR SPECTRUM FROM  41360 TO  42790 CM-1,  IN STEPS OF 10 CM-SOL 4090 */
/*         SOLAR SPECTRUM FROM  42800 TO  44230 CM-1,  IN STEPS OF 10 CM-SOL 4290 */
/*         SOLAR SPECTRUM FROM  44240 TO  45670 CM-1,  IN STEPS OF 10 CM-SOL 4490 */
/*         SOLAR SPECTRUM FROM  45680 TO  47110 CM-1,  IN STEPS OF 10 CM-SOL 4690 */
/*         SOLAR SPECTRUM FROM  47120 TO  48550 CM-1,  IN STEPS OF 10 CM-SOL 4890 */
/*         SOLAR SPECTRUM FROM  48560 TO  49990 CM-1,  IN STEPS OF 10 CM-SOL 5090 */
/*         SOLAR SPECTRUM FROM  50000 TO  51430 CM-1,  IN STEPS OF 10 CM-SOL 5290 */
/*         SOLAR SPECTRUM FROM  51440 TO  52870 CM-1,  IN STEPS OF 10 CM-SOL 5490 */
/*         SOLAR SPECTRUM FROM  52880 TO  54310 CM-1,  IN STEPS OF 10 CM-SOL 5690 */
/*         SOLAR SPECTRUM FROM  54320 TO  55750 CM-1,  IN STEPS OF 10 CM-SOL 5890 */
/*         SOLAR SPECTRUM FROM  55760 TO  57190 CM-1,  IN STEPS OF 10 CM-SOL 6090 */
/*         SOLAR SPECTRUM FROM  57200 TO  57490 CM-1,  IN STEPS OF 10 CM-SOL 6290 */

/* Subroutine */ int subsol_(float *thetas, float *phis, float *time, long *iday)
{
	/* Initialized data */

	static long nday[25] = {1, 9, 21, 32, 44, 60, 91, 121, 141, 152, 160, 172, 182,
							190, 202, 213, 244, 274, 305, 309, 325, 335, 343, 355, 366};
	static float dec[25] = {-23.07f, -22.22f, -20.08f, -17.32f, -13.62f, -7.88f,
							4.23f, 14.83f, 20.03f, 21.95f, 22.87f, 23.45f, 23.17f, 22.47f, 20.63f,
							18.23f, 8.58f, -2.88f, -14.18f, -15.45f, -19.75f, -21.68f, -22.75f,
							-23.43f, -23.07f};
	static float eqt[25] = {-3.23f, -6.83f, -11.17f, -13.57f, -14.33f, -12.63f,
							-4.2f, 2.83f, 3.57f, 2.45f, 1.1f, -1.42f, -3.52f, -4.93f, -6.25f, -6.28f,
							-.25f, 10.02f, 16.35f, 16.38f, 14.3f, 11.27f, 8.02f, 2.32f, -3.23f};

	/* Format strings */
	static char fmt_901[] = "(\002 FROM SUBSOL - IDAY OUT OF RANGE, IDAY="
							"\002,i6)";
	static char fmt_902[] = "(\002 FROM SUBSOL - TIME OUT OF RANGE, TIME="
							"\002,e12.5)";

	/* Builtin functions */
	long s_wsfe(cilist *), do_fio(long *, char *, long), e_wsfe(void);
	/* Subroutine */ int s_stop(char *, long);

	/* Local variables */
	static long i__;
	static float decang, eqtime;

	/* Fortran I/O blocks */
	static cilist io___1386 = {0, 0, 0, fmt_901, 0};
	static cilist io___1387 = {0, 0, 0, fmt_902, 0};

	/*                                                                       SUB  110 */
	/*     SUBROUTINE SUBSOL CALCULATES THE SUBSOLAR POINT ANGLES            SUB  120 */
	/*     THETAS AND PHIS BASED UPON IDAY AND TIME. SINCE EACH              SUB  130 */
	/*     YEAR IS 365.25 DAYS LONG THE EXACT VALUE OF THE DECLINATION       SUB  140 */
	/*     ANGLE CHANGES FROM YEAR TO YEAR.  FOR PRECISE VALUES CONSULT      SUB  150 */
	/*     ' THE AMERICAN EPHEMERIS AND NAUTICAL ALMANAC' PUBLISHED YEARLY   SUB  160 */
	/*     BY THE U.S. GOVT. PRINTING OFFICE.  ALSO, THE SOLAR POSITION      SUB  170 */
	/*     IS CHARACTERIZED BY 25 POINTS BELOW; THIS SHOULD PREDICT THE SUBSOSUB  180 */
	/*     ANGLES WITHIN ONE DEGREE.  FOR INCREASED ACCURACY ADD MORE DATA   SUB  190 */
	/*     POINTS                                                            SUB  200 */
	/*                                                                       SUB  210 */
	/*     THE EQUATION OF TIME, EQT, IS IN MINUTES                          SUB  220 */
	/*     THE DECLINATION ANGLE, DEC IS IN DEGREES                          SUB  230 */
	/*                                                                       SUB  240 */
	if (*iday < 1 || *iday > 366)
	{
		goto L900;
	}
	if (*time < 0.f || *time > 24.f)
	{
		goto L910;
	}
	for (i__ = 1; i__ <= 25; ++i__)
	{
		if (nday[i__ - 1] == *iday)
		{
			goto L30;
		}
		/* L10: */
		if (nday[i__ - 1] > *iday)
		{
			goto L20;
		}
	}
L20:
	--i__;
	eqtime = eqt[i__ - 1] + (eqt[i__] - eqt[i__ - 1]) * (*iday - nday[i__ - 1]) / (nday[i__] - nday[i__ - 1]);
	decang = dec[i__ - 1] + (dec[i__] - dec[i__ - 1]) * (*iday - nday[i__ - 1]) / (nday[i__] - nday[i__ - 1]);
	goto L40;
L30:
	eqtime = eqt[i__ - 1];
	decang = dec[i__ - 1];
L40:
	*thetas = decang;
	eqtime /= 60.f;
	*phis = (*time + eqtime) * 15.f - 180.f;
	if (*phis < 0.f)
	{
		*phis += 360.f;
	}
	return 0;
L900:
	io___1386.ciunit = ifil_1.ipr;
	s_wsfe(&io___1386);
	do_fio(&c__1, (char *)&(*iday), (long)sizeof(long));
	e_wsfe();
	s_stop((char *)"", (long)0);
L910:
	io___1387.ciunit = ifil_1.ipr;
	s_wsfe(&io___1387);
	do_fio(&c__1, (char *)&(*time), (long)sizeof(float));
	e_wsfe();
	s_stop((char *)"", (long)0);
	return 0;
} /* subsol_ */

/* Subroutine */ int phasef_(float *v, long *ik, float *alt, float *sangle,
							 float *rh, float *phfa)
{
	/* Initialized data */

	static float ang[34] = {0.f, 2.f, 4.f, 6.f, 8.f, 10.f, 12.f, 16.f, 20.f, 24.f, 28.f,
							32.f, 36.f, 40.f, 50.f, 60.f, 70.f, 80.f, 90.f, 100.f, 110.f, 120.f, 125.f,
							130.f, 135.f, 140.f, 145.f, 150.f, 155.f, 160.f, 165.f, 170.f, 175.f, 180.f};
	static float wave[27] = {.2f, .3f, .55f, .6943f, 1.06f, 1.536f, 2.f, 2.5f, 2.7f,
							 3.f, 3.2f, 3.39f, 5.f, 6.f, 7.2f, 7.9f, 8.7f, 9.2f, 10.f, 10.59f, 12.5f, 15.f,
							 17.2f, 18.5f, 21.3f, 30.f, 40.f};
	static float rhpts[4] = {0.f, 70.f, 80.f, 99.f};

	/* Format strings */
	static char fmt_901[] = "(\0020FROM PHASEF- SCATTERING ANGLE IS OUT OF R"
							"ANGE, \002,\002ANGLE = \002,e12.5)";
	static char fmt_911[] = "(\0020FROM PHASEF- ALAM IS OUT OF RANGE, ALAM"
							" = \002,e12.5)";

	/* Builtin functions */
	double cos(double);
	long s_wsfe(cilist *), do_fio(long *, char *, long), e_wsfe(void);
	/* Subroutine */ int s_stop(char *, long);

	/* Local variables */
	static long i__;
	static float y;
	static long i1;
	extern double pf_(long *, long *, long *);
	static long nn, nn0;
	static float pf11, pf21, pf12, pf22;
	static long irh;
	static float alam;
	static long iang1, iang2;
	static float phfa1, phfa2, yang1, yang2;
	static long iwav1, iwav2, irhhi, irhlo;
	static float cosang;
	extern /* Subroutine */ int hengns_(float *, float *, float *), interp_(
																		long *, float *, float *, float *, float *, float *, float *);

	/* Fortran I/O blocks */
	static cilist io___1413 = {0, 0, 0, fmt_901, 0};
	static cilist io___1414 = {0, 0, 0, fmt_911, 0};

	/*                                                                       PHS  110 */
	/*     RETURNS THE AEROSOL PHASE FUNCTION FROM THE STORED DATA BASE      PHS  120 */
	/*                                                                       PHS  130 */
	/*                                                                       PHS  140 */
	/*     THE TRUTH TABLE MNUM(27,26) STORED IN COMMON/MNMPHS/              PHS  150 */
	/*     IN SUBROUTINE PHSDTA IS QUERIED TO DETERMINE THE PROPER PHASE     PHS  160 */
	/*     FUNCTION NEEDED.                                                  PHS  170 */
	/*     THE 27 POSITIONS REPRESENT THE 27 SPECIFIC FREQUENCIES SHOWN IN   PHS  180 */
	/*     DATA STATEMENT WAVE  .2-40 MICRONS.                               PHS  190 */
	/*     THE NUMBERS STORED IN THESE 27 POSITIONS REPRESENT THE CORRECT    PHS  200 */
	/*     PHASE FUNCTIONS CHOSEN FROM THE DATA STATEMENT PHSFNC'S 1-70      PHS  210 */
	/*     POSSIBLE CHOICES.                                                 PHS  220 */
	/*     THE 26 DATA STATEMENTS EACH HAVING 27 FREQUENCIES REPRESENT THE   PHS  230 */
	/*     FOLLOWING 26 MODELS;                                              PHS  240 */
	/*      1=RURAL     0%RH   2=RURAL    70%RH   3=RURAL    80%RH           PHS  250 */
	/*      4=RURAL    99%RH   5=MARITIME  0%RH   6=MARITIME 70%RH           PHS  260 */
	/*      7=MARITIME 80%RH   8=MARITIME 99%RH   9=URBAN     0%RH           PHS  270 */
	/*     10=URBAN    70%RH  11=URBAN    80%RH  12=URBAN    99%RH           PHS  280 */
	/*     13=OCEANIC   0%RH  14=OCEANIC  70%RH  15=OCEANIC  80%RH           PHS  290 */
	/*     16=OCEANIC  99%RH  17=TROPOSPH  0%RH  18=TROPOSPH 70%RH           PHS  300 */
	/*     19=TROPOSPH 80%RH  20=TROPOSPH 99%RH  21=STRATOSPHERIC            PHS  310 */
	/*     22=AGED VOLCANIC   23=FRESH VOLCANIC  24=RADIATION FOG            PHS  320 */
	/*     25=ADVECTIVE FOG   26=METEORIC DUST                               PHS  330 */
	/*                                                                       PHS  340 */
	/*                                                                       PHS  350 */
	/*     IN THE PRESENT VERSION THE 4 OCEANIC MODELS 13-16                 PHS  360 */
	/*     ARE NOT UTILIZED.                                                 PHS  370 */
	/*                                                                       PHS  380 */
	/*                                                                       PHS  580 */
	*phfa = 0.f;
	alam = 1e4f / *v;
	if (*v < 1e-5f)
	{
		alam = 1e9f;
	}
	if (*sangle < 0.f || *sangle > 180.f)
	{
		goto L900;
	}
	if (alam - wave[0] < -1e-6f)
	{
		goto L910;
	}
	if (alam > wave[26])
	{
		cosang = cos(cnstns_1.ca * *sangle);
		hengns_(&aer_1.zz1, &cosang, phfa);
		return 0;
	}
	/*     DETERMINE THE AEROSOL MODEL NUMBER                                PHS  680 */
	if (*alt > card2d_1.altb[0])
	{
		goto L95;
	}
	/*                                                                       PHS  700 */
	/*                                                                       PHS  710 */
	/*                                                                       PHS  720 */
	if (card2_1.ihaze == 0)
	{
		goto L400;
	}
	if (card2_1.ihaze == 10)
	{
		cosang = cos(cnstns_1.ca * *sangle);
		hengns_(&aer_1.zz1, &cosang, phfa);
		return 0;
	}
	/*                                                                       PHS  790 */
	/*     CHECK IF CLOUD,RAIN OR DESERT MODEL IS REQUESTED                  PHS  800 */
	/*                                                                       PHS  810 */
	if (card2_1.icld > 0 || card2_1.ihaze == 7)
	{
		cosang = cos(cnstns_1.ca * *sangle);
		/*                                                                       PHS  840 */
		hengns_(&aer_1.zz1, &cosang, phfa);
		return 0;
	}
	if (card2_1.ihaze >= 8)
	{
		goto L90;
	}
	/*                                                                       PHS  890 */
	/*     0-2KM BOUNDARY LAYER MODELS, RH DEPENDENT                         PHS  900 */
	for (i1 = 1; i1 <= 4; ++i1)
	{
		i__ = i1;
		if (rhpts[i__ - 1] == *rh)
		{
			goto L70;
		}
		if (rhpts[i__ - 1] > *rh)
		{
			goto L60;
		}
		/* L50: */
	}
L60:
	irhlo = i__ - 1;
	irhhi = i__;
	goto L80;
L70:
	irhlo = i__;
	irhhi = i__;
L80:
	/*     RURAL MODEL                                                       PHS 1020 */
	if (card2_1.ihaze == 1 || card2_1.ihaze == 2)
	{
		nn0 = 0;
	}
	/*     MARITIME MODEL                                                    PHS 1040 */
	if (card2_1.ihaze == 3 || card2_1.ihaze == 4)
	{
		nn0 = 4;
	}
	/*     URBAN MODEL                                                       PHS 1060 */
	if (card2_1.ihaze == 5)
	{
		nn0 = 8;
	}
	/*     TROPOSPHERIC MODEL                                                PHS 1080 */
	if (card2_1.ihaze == 6)
	{
		nn0 = 16;
	}
	nn = nn0 + irhlo;
	goto L130;
/*     0-2KM FOG MODELS, NO RH DEPENDENCE                                PHS 1120 */
L90:
	if (card2_1.ihaze == 8)
	{
		nn = 24;
	}
	if (card2_1.ihaze == 9)
	{
		nn = 25;
	}
	goto L130;
L95:
	if (*alt > card2d_1.altb[1])
	{
		goto L110;
	}
	/*     2-10KM TROPOSPHERIC MODEL                                         PHS 1170 */
	if (card2_1.icld > 0 || card2_1.ihaze == 7)
	{
		cosang = cos(cnstns_1.ca * *sangle);
		/*                                                                       PHS 1200 */
		hengns_(&aer_1.zz2, &cosang, phfa);
		return 0;
	}
	nn = 18;
	goto L130;
L110:
	if (*alt > card2d_1.altb[2])
	{
		goto L120;
	}
	/*     10-30KM STRATOSPHERIC MODELS                                      PHS 1270 */
	/*     BACKGROUND MODEL                                                  PHS 1280 */
	if (card2_1.ivulcn == 0 || card2_1.ivulcn == 1)
	{
		nn = 21;
	}
	/*     AGED VOLCANIC MODEL                                               PHS 1300 */
	if (card2_1.ivulcn == 2 || card2_1.ivulcn == 4)
	{
		nn = 22;
	}
	/*     FRESH VOLCANIC                                                    PHS 1320 */
	if (card2_1.ivulcn == 3 || card2_1.ivulcn == 5 || card2_1.ivulcn == 8)
	{
		nn = 23;
	}
	/*     BACKGROUND STRATO                                                 PHS 1340 */
	if (card2_1.ivulcn == 6 || card2_1.ivulcn == 7)
	{
		nn = 21;
	}
	goto L130;
/*     30-100KM METEORIC MODEL                                           PHS 1370 */
L120:
	nn = 26;
L130:
	irh = 0;
	/*                                                                       PHS 1400 */
	/*     DETERMINE THE BOUNDING ANGLE INDICES                              PHS 1410 */
	/* L140: */
	for (i1 = 1; i1 <= 34; ++i1)
	{
		i__ = i1;
		if (ang[i__ - 1] == *sangle)
		{
			goto L230;
		}
		if (ang[i__ - 1] > *sangle)
		{
			goto L220;
		}
		/* L210: */
	}
L220:
	iang1 = i__ - 1;
	iang2 = i__;
	goto L240;
L230:
	iang1 = i__;
	iang2 = i__;
L240:
	/*                                                                       PHS 1530 */
	/*     DETERMINE THE BOUNDING WAVELENGTH INDICES                         PHS 1540 */
	for (i1 = 1; i1 <= 27; ++i1)
	{
		i__ = i1;
		if (wave[i__ - 1] == alam)
		{
			goto L270;
		}
		if (wave[i__ - 1] > alam)
		{
			goto L260;
		}
		/* L250: */
	}
L260:
	iwav1 = i__ - 1;
	iwav2 = i__;
	goto L280;
L270:
	iwav1 = i__;
	iwav2 = i__;
L280:
	/*                                                                       PHS 1660 */
	/*     FUNCTION PF CHOOSES DESIRED PHASE FUNCTION FROM LOOK UP TABLE     PHS 1670 */
	/*     MNUM(IWAV,NN)  WHERE IWAV IS FREQ. AND NN IS MODEL NO.            PHS 1680 */
	/*                                                                       PHS 1690 */
	/*     WAVELENGTH INTERPOLATION ONLY USES PF11 AND PF21                  PHS 1700 */
	/*     ANGLE INTERPOLATION ONLY USES PF11 AND PF12                       PHS 1710 */
	/*     WAVELENGTH AND ANGLE INTERPOLATION USES PF11,PF21 AND PF12,PF22.  PHS 1720 */
	/*                                                                       PHS 1730 */
	pf11 = pf_(&nn, &iwav1, &iang1);
	pf21 = pf_(&nn, &iwav2, &iang1);
	pf12 = pf_(&nn, &iwav1, &iang2);
	pf22 = pf_(&nn, &iwav2, &iang2);
	/*     INTERPOLATE IN WAVELENGTH THEN ANGLE                              PHS 1780 */
	if (iwav1 == iwav2)
	{
		goto L310;
	}
	if (iang1 == iang2)
	{
		goto L290;
	}
	/*     BOTH INTERPOLATIONS ARE NECESSARY                                 PHS 1810 */
	interp_(&c__2, &alam, &wave[iwav1 - 1], &wave[iwav2 - 1], &yang1, &pf11, &pf21);
	interp_(&c__2, &alam, &wave[iwav1 - 1], &wave[iwav2 - 1], &yang2, &pf12, &pf22);
	interp_(&c__2, sangle, &ang[iang1 - 1], &ang[iang2 - 1], &y, &yang1, &yang2);
	goto L330;
/*     ONLY WAVELENGTH INTERPOLATION IS NECESSARY                        PHS 1880 */
L290:
	interp_(&c__2, &alam, &wave[iwav1 - 1], &wave[iwav2 - 1], &y, &pf11, &pf21);
	goto L330;
L310:
	if (iang1 == iang2)
	{
		goto L320;
	}
	/*     ONLY ANGLE INTERPOLATION IS NECESSARY                             PHS 1930 */
	interp_(&c__2, sangle, &ang[iang1 - 1], &ang[iang2 - 1], &y, &pf11, &pf12);
	goto L330;
/*     NO INTERPOLATION IS NECESSARY                                     PHS 1970 */
L320:
	y = pf_(&nn, &iwav1, &iang1);
L330:
	*phfa = y;
	/*                                                                       PHS 2010 */
	/*     HUMIDITY DEPENDENCE                                               PHS 2020 */
	if (*alt > card2d_1.altb[0] || nn >= 17 || irhlo == irhhi)
	{
		goto L400;
	}
	if (irh == 1)
	{
		goto L340;
	}
	nn = nn0 + irhhi;
	phfa1 = *phfa;
	irh = 1;
	goto L280;
L340:
	phfa2 = *phfa;
	interp_(&c__1, rh, &rhpts[irhlo - 1], &rhpts[irhhi - 1], phfa, &phfa1, &phfa2);
L400:
	return 0;
L900:
	io___1413.ciunit = ifil_1.ipr;
	s_wsfe(&io___1413);
	do_fio(&c__1, (char *)&(*sangle), (long)sizeof(float));
	e_wsfe();
	s_stop((char *)"", (long)0);
L910:
	io___1414.ciunit = ifil_1.ipr;
	s_wsfe(&io___1414);
	do_fio(&c__1, (char *)&alam, (long)sizeof(float));
	e_wsfe();
	s_stop((char *)"", (long)0);
	return 0;
} /* phasef_ */

/* Subroutine */ int hengns_(float *zz, float *sangle, float *phfa)
{
	/* System generated locals */
	float r__1, r__2;
	double d__1;

	/* Builtin functions */
	double pow_dd(double *, double *);

	/*                                                                       HEN  110 */
	/*    CALCULATES THE PHASE FUNCTION USING THE HENREY GREENSTEIN          HEN  120 */
	/*    METHOD FOR CLOUDS, DESERT AERSOL, RAIN OR USER READ IN MODEL       HEN  130 */
	/*                                                                       HEN  140 */
	/*                                                                       HEN  160 */
	/* Computing 2nd power */
	r__1 = *zz;
	/* Computing 2nd power */
	r__2 = *zz;
	d__1 = (double)(1.f + r__2 * r__2 - 2.f * *zz * *sangle);
	*phfa = (1.f - r__1 * r__1) / (4.f * cnstns_1.pi * pow_dd(&d__1, &c_b1937));
	return 0;
} /* hengns_ */

double pf_(long *nn, long *i__, long *j)
{
	/* System generated locals */
	float ret_val;

	/* Local variables */
	static long m;

	/*     CALL THE APPROPRIATE PHASE FUNCTION                               PF   110 */
	m = mnmphs_1.mnum[*i__ + *nn * 27 - 28];
	ret_val = mnmphs_1.phsfnc[*j + m * 34 - 35];
	return ret_val;
} /* pf_ */

/* Subroutine */ int interp_(long *intype, float *x, float *x1, float *x2,
							 float *f, float *f1, float *f2)
{
	/* Builtin functions */
	double log(double), exp(double);

	/* Local variables */
	static float a, a1, a2;
	static long itype;

	/*     SUBROUTINE INTERP INTERPOLATES TO DETERMINE THE VALUE OF F        INT  110 */
	/*     AT X, GIVEN F1 AT X1 AND F2 AT X2.                                INT  120 */
	/*     INTYPE=1 FOR LINEAR INTERPOLATION                                 INT  130 */
	/*     INTYPE=2 FOR LOGARITHMIC INTERPOLATION                            INT  140 */
	itype = *intype;
	if (*f1 <= 0.f || *f2 <= 0.f)
	{
		itype = 1;
	}
	if (itype == 2)
	{
		goto L100;
	}
	/*     LINEAR INTERPOLATION                                              INT  180 */
	*f = *f1 + (*x - *x1) * (*f2 - *f1) / (*x2 - *x1);
	return 0;
L100:
	a1 = log(*f1);
	a2 = log(*f2);
	a = a1 + (*x - *x1) * (a2 - a1) / (*x2 - *x1);
	*f = exp(a);
	return 0;
} /* interp_ */

double raysct_(float *v)
{
	/* System generated locals */
	float ret_val, r__1, r__2;

	/*     RADIATION FLD OUT                                                 RAY  110 */
	/* **  MOLECULAR SCATTERING                                              RAY  120 */
	ret_val = 0.f;
	if (*v <= 3e3f)
	{
		return ret_val;
	}
	/* Computing 3rd power */
	r__1 = *v;
	/* Computing 2nd power */
	r__2 = *v;
	ret_val = r__1 * (r__1 * r__1) / (9.26799e18f - r__2 * r__2 * 1.07123e9f);
	/*     V**4 FOR RADIATION FLD IN                                         RAY  160 */
	return ret_val;
} /* raysct_ */

/* Subroutine */ int expint_(float *x, float *x1, float *x2, float *a)
{
	/* System generated locals */
	double d__1, d__2;

	/* Builtin functions */
	double pow_dd(double *, double *);

	/*     EXPONENTIAL INTERPOLATION                                         EXP  110 */
	if (*x1 == 0.f || *x2 == 0.f)
	{
		goto L100;
	}
	d__1 = (double)(*x2 / *x1);
	d__2 = (double)(*a);
	*x = *x1 * pow_dd(&d__1, &d__2);
	return 0;
L100:
	*x = *x1 + (*x2 - *x1) * *a;
	return 0;
} /* expint_ */

/* Subroutine */ int equlwc_(void)
{
	/* System generated locals */
	long i__1;

	/* Local variables */
	static long i__;

	/* CC                                                                     EQU  110 */
	/* CC   EQUIVALENT LIQUID  WATER CONSTANTS FOR BEXT (0.55UM)=1.0KM-1      EQU  120 */
	/* CC   AWCCON(1-4) IS SET TO ONE OF THE CONSTANTS FOR EACH AEROSOL       EQU  130 */
	/* CC   IN SUBROUTINE EXABIN AND MULTIPLIED BY THE BEXT (DENSTY(N,I))     EQU  140 */
	/* CC   WHERE N=7,12,13 OR 14 AND I IS THE NUMBER OF LAYERS               EQU  150 */
	/* CC                                                                     EQU  160 */
	i__1 = cntrl_1.ml;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		if (model_1.densty[i__ * 63 - 57] != 0.f)
		{
			model_1.eqlwc[i__ - 1] = model_1.densty[i__ * 63 - 57] *
									 _BLNK__1.awccon[0];
		}
		if (model_1.densty[i__ * 63 - 52] != 0.f)
		{
			model_1.eqlwc[i__ - 1] = model_1.densty[i__ * 63 - 52] *
									 _BLNK__1.awccon[1];
		}
		if (model_1.densty[i__ * 63 - 51] != 0.f)
		{
			model_1.eqlwc[i__ - 1] = model_1.densty[i__ * 63 - 51] *
									 _BLNK__1.awccon[2];
		}
		if (model_1.densty[i__ * 63 - 50] != 0.f)
		{
			model_1.eqlwc[i__ - 1] = model_1.densty[i__ * 63 - 50] *
									 _BLNK__1.awccon[3];
		}
		/* L140: */
	}
	return 0;
} /* equlwc_ */

/* Subroutine */ int indx_(float *wavl, float *tc, long *key, float *reil,
						   float *aimag)
{
	/* Format strings */
	static char fmt_1[] = "(///,30x,\002ATTEMPTING TO EVALUATE FOR A WAVELEN"
						  "GTH LESS THAN ONE MICRON\002,//)";
	static char fmt_2[] = "(///,30x,\002ATTEMPTING TO EVALUATE FOR A TEMPERA"
						  "TURE LESS THAN -20. DEGREES CENTIGRADE\002,//)";

	/* System generated locals */
	double d__1;

	/* Builtin functions */
	long s_wsfe(cilist *), e_wsfe(void);
	double pow_dd(double *, double *), exp(double);

	/* Local variables */
	static float r1, r2;
	extern double ab_(float *, float *, float *, float *, float *), dop_(float *, float *, float *, float *, float *, float *, float *, float *, float *,
																		 float *, float *);
	extern /* Subroutine */ int debye_(float *, float *, long *, float *,
									   float *);

	/* Fortran I/O blocks */
	static cilist io___1423 = {0, 6, 0, fmt_1, 0};
	static cilist io___1424 = {0, 6, 0, fmt_2, 0};

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * INX  110 */
	/* * *                                                                   INX  120 */
	/* * * WAVELENGTH IS IN CENTIMETERS.  TEMPERATURE IS IN DEG. C.      * * INX  130 */
	/* * *                                                                   INX  140 */
	/* * * KEY IS SET TO 1 IN SUBROUTINE GAMFOG                          * * INX  150 */
	/* * *                                                                   INX  160 */
	/* * * KEY IS SET TO 0 IN SUBROUTINE GAMFOG    FOR CIRRUS            * * INX  170 */
	/* * *                                                                   INX  180 */
	/* * * REAL IS THE REAL PART OF THE REFRACTIVE INDEX.                * * INX  190 */
	/* * *                                                                   INX  200 */
	/* * * AIMAG IS THE IMAGINARY PART OF THE REFRACTIVE INDEX IT IS     * * INX  210 */
	/* * *                                                                   INX  220 */
	/* * * RETURNED NEG. I.E.  M= REAL - I*AIMAG  .                      * * INX  230 */
	/* * *                                                                   INX  240 */
	/* * * A SERIES OF CHECKS ARE MADE AND WARNINGS GIVEN.               * * INX  250 */
	/* * *                                                                   INX  260 */
	/* * * RAY APPLIED OPTICS VOL 11,NO.8,AUG 72, PG. 1836-1844          * * INX  270 */
	/* * *                                                                   INX  280 */
	/* * * CORRECTIONS HAVE BEEN MADE TO RAYS ORIGINAL PAPER             * * INX  290 */
	/* * *                                                                   INX  300 */
	/* * *                                                                   INX  310 */
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * INX  320 */
	r1 = 0.f;
	r2 = 0.f;
	if (*wavl < 1e-4f)
	{
		s_wsfe(&io___1423);
		e_wsfe();
	}
	if (*tc < -20.f)
	{
		s_wsfe(&io___1424);
		e_wsfe();
	}
	debye_(wavl, tc, key, reil, aimag);
	/* * *  TABLE 3 WATER PG. 1840                                           INX  430 */
	/* L4: */
	if (*wavl > .034f)
	{
		goto L5;
	}
	goto L7;
L5:
	if (*wavl > .1f)
	{
		goto L11;
	}
	/* L6: */
	r2 = dop_(wavl, &c_b2088, &c_b2089, &c_b2090, &c_b2091, &c_b2092, &c_b2093, &c_b2094, &c_b2095, &c_b2096, &c_b2097);
	d__1 = (double)(*wavl * 2.5e-5f);
	r2 += r2 * (*tc - 25.f) * 1e-4f * exp(pow_dd(&d__1, &c_b2098));
	*reil = *reil * (*wavl - .034f) / .066f + r2 * (.1f - *wavl) / .066f;
	goto L11;
L7:
	if (*wavl > 6e-4f)
	{
		goto L8;
	}
	goto L10;
L8:
	*reil = dop_(wavl, &c_b2088, &c_b2089, &c_b2090, &c_b2091, &c_b2092, &c_b2093, &c_b2094, &c_b2095, &c_b2096, &c_b2097);
	d__1 = (double)(*wavl * 2.5e-5f);
	*reil += *reil * (*tc - 25.f) * 1e-4f * exp(pow_dd(&d__1, &c_b2098));
	if (*wavl > 7e-4f)
	{
		goto L11;
	}
	/* L9: */
	r1 = dop_(wavl, &c_b2113, &c_b2114, &c_b2115, &c_b2116, &c_b2089, &c_b2118, &c_b2119, &c_b2092, &c_b2121, &c_b2122);
	d__1 = (double)(*wavl * 2.5e-5f);
	r1 += r1 * (*tc - 25.f) * 1e-4f * exp(pow_dd(&d__1, &c_b2098));
	*reil = r1 * (7e-4f - *wavl) / 1e-4f + *reil * (*wavl - 6e-4f) / 1e-4f;
	goto L11;
L10:
	*reil = dop_(wavl, &c_b2113, &c_b2114, &c_b2115, &c_b2116, &c_b2089, &c_b2118, &c_b2119, &c_b2092, &c_b2121, &c_b2122);
	d__1 = (double)(*wavl * 2.5e-5f);
	*reil += *reil * (*tc - 25.f) * 1e-4f * exp(pow_dd(&d__1, &c_b2098));
/* * *  TABLE 2 WATER PG. 1840                                           INX  660 */
L11:
	if (*wavl >= .3f)
	{
		goto L57;
	}
	if (*wavl >= .03f)
	{
		goto L12;
	}
	goto L13;
L12:
	*aimag = *aimag + ab_(wavl, &c_b2138, &c_b2139, &c_b2140, &c_b2141) + ab_(wavl, &c_b2142, &c_b2143, &c_b2144, &c_b2145) + ab_(wavl, &c_b2146, &c_b2147, &c_b2148, &c_b2149);
	goto L57;
L13:
	if (*wavl >= .0062f)
	{
		goto L14;
	}
	goto L15;
L14:
	*aimag = *aimag + ab_(wavl, &c_b2146, &c_b2147, &c_b2148, &c_b2149) + ab_(wavl, &c_b2142, &c_b2143, &c_b2144, &c_b2145) + ab_(wavl, &c_b2138, &c_b2139, &c_b2162, &c_b2163);
	goto L57;
L15:
	if (*wavl >= .0017f)
	{
		goto L16;
	}
	goto L17;
L16:
	*aimag = *aimag + ab_(wavl, &c_b2142, &c_b2143, &c_b2144, &c_b2145) + ab_(wavl, &c_b2146, &c_b2147, &c_b2172, &c_b2173) + ab_(wavl, &c_b2138, &c_b2139, &c_b2162, &c_b2163);
	goto L57;
L17:
	if (*wavl >= 6.1e-4f)
	{
		goto L18;
	}
	goto L19;
L18:
	*aimag = *aimag + ab_(wavl, &c_b2180, &c_b2181, &c_b2182, &c_b2183) + ab_(wavl, &c_b2142, &c_b2143, &c_b2186, &c_b2187) + ab_(wavl, &c_b2146, &c_b2147, &c_b2172, &c_b2173);
	goto L57;
L19:
	if (*wavl >= 4.95e-4f)
	{
		goto L20;
	}
	goto L21;
L20:
	*aimag = *aimag + ab_(wavl, &c_b2194, &c_b2195, &c_b2196, &c_b1471) + ab_(wavl, &c_b2180, &c_b2181, &c_b2200, &c_b2163);
	goto L57;
L21:
	if (*wavl >= 2.97e-4f)
	{
		goto L22;
	}
	goto L23;
L22:
	*aimag = *aimag + ab_(wavl, &c_b2204, &c_b2205, &c_b2206, &c_b2163) + ab_(wavl, &c_b2194, &c_b2195, &c_b2210, &c_b1471);
	goto L57;
L23:
	*aimag = *aimag + ab_(wavl, &c_b2204, &c_b2205, &c_b2214, &c_b2163) + ab_(wavl, &c_b2194, &c_b2195, &c_b2210, &c_b1471);
L57:
	return 0;
} /* indx_ */

/* Subroutine */ int debye_(float *wavl, float *tc, long *key, float *re,
							float *ai)
{
	/* System generated locals */
	float r__1, r__2;
	double d__1, d__2, d__3, d__4;

	/* Builtin functions */
	double exp(double), sin(double), pow_dd(double *, double *), cos(double), sqrt(double);

	/* Local variables */
	static float t, c1, c2, e1, e2, es, t125, dem, sig, tau, efin, alpha;

	/* CC                                                                     DBY  110 */
	/* CC    CALCULATES WAVENUMBER DEPENDENCE OF DIELECTRIC CONSTANT          DBY  120 */
	/* CC    OF WATER                                                         DBY  130 */
	/* CC                                                                     DBY  140 */
	t = *tc + 273.15f;
	if (*key != 0)
	{
		goto L1;
	}
	goto L2;
L1:
	efin = *tc * .0216474f + 5.27137f - *tc * .00131198f * *tc;
	alpha = -16.8129f / t + .0609265f;
	tau = exp(2513.98f / t) * 3.3836e-4f;
	sig = 1.25664e9f;
	/* Computing 2nd power */
	r__1 = *tc - 25.f;
	/* Computing 3rd power */
	r__2 = *tc - 25.f;
	es = (1.f - (*tc - 25.f) * .004579f + r__1 * r__1 * 1.19e-5f - r__2 * (r__2 * r__2) * 2.8e-8f) * 78.54f;
	goto L3;
L2:
	efin = 3.168f;
	alpha = *tc * 2.3e-4f * *tc + *tc * .0052f + .288f;
	t125 = 12500.f / (t * 1.9869f);
	if (t125 <= cnstns_1.bigexp)
	{
		sig = exp(-t125) * 1.26f;
	}
	else
	{
		sig = 0.f;
	}
	tau = exp(13200.f / (t * 1.9869f)) * 9.990288e-5f;
	es = *tc * .15f * *tc + 3.168f + *tc * 2.5f + 200.f;
L3:
	c1 = tau / *wavl;
	/* CC                                                                     DBY  370 */
	/* CC    TEMPORARY FIX TO CLASSICAL DEBYE EQUATION                        DBY  380 */
	/* CC    TO HANDLE ZERO CM-1 PROBLEM                                      DBY  390 */
	/* CC                                                                     DBY  400 */
	alpha = 0.f;
	sig = 0.f;
	/* CC                                                                     DBY  430 */
	c2 = alpha * 1.5708f;
	d__1 = (double)c1;
	d__2 = (double)(1.f - alpha);
	d__3 = (double)c1;
	d__4 = (double)((1.f - alpha) * 2.f);
	dem = pow_dd(&d__1, &d__2) * 2.f * sin(c2) + 1.f + pow_dd(&d__3, &d__4);
	d__1 = (double)c1;
	d__2 = (double)(1.f - alpha);
	e1 = efin + (es - efin) * (pow_dd(&d__1, &d__2) * sin(c2) + 1.f) / dem;
	if (*key != 0 && *wavl >= 300.f)
	{
		e1 = 87.53f - *tc * .3956f;
	}
	if (*key != 0 && *wavl >= 300.f)
	{
		e1 = es;
	}
	d__1 = (double)c1;
	d__2 = (double)(1.f - alpha);
	e2 = (es - efin) * pow_dd(&d__1, &d__2) * cos(c2) / dem + sig * *wavl /
																  1.88496e11f;
	/* CC                                                                     DBY  500 */
	/* CC    PERMANENT FIX TO CLSSICAL DEBYE EQUATION                         DBY  510 */
	/* CC    TO HANDLE ZERO CM-1 PROBLEM                                      DBY  520 */
	/* CC                                                                     DBY  530 */
	/* Computing 2nd power */
	r__1 = c1;
	e1 = efin + (es - efin) / (r__1 * r__1 + 1.f);
	/* CC                                                                     DBY  550 */
	/* Computing 2nd power */
	r__1 = c1;
	e2 = (es - efin) * c1 / (r__1 * r__1 + 1.f);
	/* CC                                                                     DBY  570 */
	*re = sqrt((e1 + sqrt(e1 * e1 + e2 * e2)) / 2.f);
	*ai = -e2 / (*re * 2.f);
	return 0;
} /* debye_ */

double dop_(float *wavl, float *a, float *cen1, float *b, float *c__, float *cen2, float *d__, float *e, float *cen3, float *f, float *g)
{
	/* System generated locals */
	float ret_val, r__1;

	/* Builtin functions */
	double sqrt(double);

	/* Local variables */
	static float v, h1, h2, h3, v2;

	/* CC                                                                     DOP  110 */
	/* CC    DESCRIBES THE REAL PART OF THE DIELECTRIC CONSTANT               DOP  120 */
	/* CC                                                                     DOP  130 */
	v = 1.f / *wavl;
	v2 = v * v;
	/* Computing 2nd power */
	r__1 = *cen1;
	h1 = r__1 * r__1 - v2;
	/* Computing 2nd power */
	r__1 = *cen2;
	h2 = r__1 * r__1 - v2;
	/* Computing 2nd power */
	r__1 = *cen3;
	h3 = r__1 * r__1 - v2;
	ret_val = sqrt(*a + *b * h1 / (h1 * h1 + *c__ * v2) + *d__ * h2 / (h2 * h2 + *e * v2) + *f * h3 / (h3 * h3 + *g * v2));
	return ret_val;
} /* dop_ */

double ab_(float *wavl, float *a, float *cen, float *b, float *c__)
{
	/* System generated locals */
	float ret_val, r__1, r__2;
	double d__1, d__2;

	/* Builtin functions */
	double r_lg10(float *), pow_dd(double *, double *), exp(double);

	/* CC                                                                     AB   110 */
	/* CC    DESCRIBES THE IMAGINARY PART OF THE DIELECTRIC CONSTANT          AB   120 */
	/* CC                                                                     AB   130 */
	r__2 = *wavl * 1e4f / *cen;
	d__1 = (r__1 = r_lg10(&r__2) / *b, (double)dabs(r__1));
	d__2 = (double)(*c__);
	ret_val = -(*a) * exp(-pow_dd(&d__1, &d__2));
	return ret_val;
} /* ab_ */

double gamfog_(long *mr, float *freq, float *t, float *rho)
{
	/* System generated locals */
	float ret_val;
	complex q__1, q__2, q__3, q__4, q__5, q__6;

	/* Builtin functions */
	void pow_ci(complex *, complex *, long *), c_div(complex *, complex *,
													 complex *);
	double r_imag(complex *);

	/* Local variables */
	static float tc;
	static long key;
	static float reil;
	extern /* Subroutine */ int indx_(float *, float *, long *, float *, float *);
	static float wavl, aimak;
	static complex cindex;

	/*                                                                       GAM  110 */
	/*        COMPUTES ATTENUATION OF EQUIVALENT LIQUID WATER CONTENT        GAM  120 */
	/*       IN CLOUDS OR FOG IN DB/KM                                       GAM  130 */
	/*       CONVERTED TO NEPERS BY NEW CONSTANT 1.885                       GAM  140 */
	/*                                                                       GAM  150 */
	/*        FREQ = WAVENUMBER (INVERSE CM)                                 GAM  160 */
	/*        T    = TEMPERATURE (DEGREES KELVIN)                            GAM  170 */
	/*        RHO  = EQUIVALENT LIQUID CONTENT  (G/CUBIC METER)              GAM  180 */
	/*      CINDEX=COMPLEX DIELECTRIC CONSTANT M  FROM INDEX                 GAM  190 */
	/*      WAVL = WAVELENGTH IN CM                                          GAM  200 */
	/*                                                                       GAM  210 */
	if (*rho > 0.f)
	{
		goto L2;
	}
	ret_val = 0.f;
	return ret_val;
L2:
	key = 1;
	if (*mr >= 5)
	{
		key = 0;
	}
	wavl = 1.f / *freq;
	tc = *t - 273.2f;
	/* CC                                                                     GAM  310 */
	/* CC    CHANGE TEMP SO THAT MINIMUM IS -20.0 CENT.                       GAM  320 */
	/* CC                                                                     GAM  330 */
	if (tc < -20.f)
	{
		tc = -20.f;
	}
	indx_(&wavl, &tc, &key, &reil, &aimak);
	q__1.r = reil, q__1.i = aimak;
	cindex.r = q__1.r, cindex.i = q__1.i;
	/* CC                                                                     GAM  370 */
	/* CC   ATTENUATION = 6.0*PI*FREQ*RHO*IMAG(-K)                            GAM  380 */
	/* CC    6.0*PI/10. = 1.885 (THE FACTOR OF 10 IS FOR UNITS CONVERSION)    GAM  390 */
	/* CC                                                                     GAM  400 */
	/*     GAMFOG=8.1888*FREQ*RHO*AIMAG( -  (CINDEX**2-1)/(CINDEX**2+2))     GAM  410 */
	pow_ci(&q__4, &cindex, &c__2);
	q__3.r = q__4.r - 1, q__3.i = q__4.i;
	q__2.r = -q__3.r, q__2.i = -q__3.i;
	pow_ci(&q__6, &cindex, &c__2);
	q__5.r = q__6.r + 2, q__5.i = q__6.i;
	c_div(&q__1, &q__2, &q__5);
	ret_val = *freq * 1.885f * *rho * r_imag(&q__1);
	return ret_val;
} /* gamfog_ */

double aitk_(float *arg, float *val, float *x, long *ndim)
{
	/* System generated locals */
	long i__1, i__2;
	float ret_val;

	/* Local variables */
	static float h__;
	static long i__, j, ier, iend;

	/*                                                                       AIT  110 */
	/*      IBM SCIENTIFIC SUBROUTINE                                        AIT  120 */
	/*     AITKEN INTERPOLATION ROUTINE                                      AIT  130 */
	/*                                                                       AIT  140 */
	/* Parameter adjustments */
	--val;
	--arg;

	/* Function Body */
	if ((i__1 = *ndim - 1) < 0)
	{
		goto L9;
	}
	else if (i__1 == 0)
	{
		goto L7;
	}
	else
	{
		goto L1;
	}
/*                                                                       AIT  170 */
/*     START OF AITKEN-LOOP                                              AIT  180 */
L1:
	i__1 = *ndim;
	for (j = 2; j <= i__1; ++j)
	{
		iend = j - 1;
		i__2 = iend;
		for (i__ = 1; i__ <= i__2; ++i__)
		{
			h__ = arg[i__] - arg[j];
			if (h__ != 0.f)
			{
				goto L2;
			}
			else
			{
				goto L13;
			}
		L2:
			val[j] = (val[i__] * (*x - arg[j]) - val[j] * (*x - arg[i__])) /
					 h__;
		}
		/* L6: */
	}
/*     END OF AITKEN-LOOP                                                AIT  260 */
/*                                                                       AIT  270 */
L7:
	j = *ndim;
L8:
	ret_val = val[j];
L9:
	return ret_val;
/*                                                                       AIT  310 */
/*     THERE ARE TWO IDENTICAL ARGUMENT VALUES IN VECTOR ARG             AIT  320 */
L13:
	ier = 3;
	j = iend;
	goto L8;
} /* aitk_ */

/* Subroutine */ int cirrus_(float *cthik, float *calt, long *iseed, float *cprob, float *cext)
{
	/* Initialized data */

	static float camean[5] = {11.f, 10.f, 8.f, 7.f, 5.f};
	static float ptab[5] = {.8f, .4f, .5f, .45f, .4f};
	static float tstat[11] = {0.f, .291f, .509f, .655f, .764f, .837f, .892f, .928f,
							  .96f, .982f, 1.f};
	static struct
	{
		float e_1[10];
	} equiv_1 = {7.5f, 7.3f, 4.5f, 4.5f, 2.5f, 16.5f, 13.5f, 14.f, 9.5f,
				 10.f};

	/* System generated locals */
	long i__1;

	/* Local variables */
	static long i__, iv1, iv2, mdl, iml;
	static float top, urn, pct1, pct2, hmax;
	static long idum;
	static float zmin, zmax;
	static long ihgt1, ihgt2;
#define cbase ((float *)&equiv_1)
	static float denom;
#define cbase1 ((float *)&equiv_1)
#define cbase2 ((float *)&equiv_1 + 5)
	static float brange, dencir;
	extern double ranfun_(long *);
	extern /* Subroutine */ int ranset_(long *);
	static float bottom;

	/* *********************************************************************  CIR  110 */
	/* *  ROUTINE TO GENERATE ALTITUDE PROFILES OF CIRRUS DENSITY         **  CIR  120 */
	/* *  PROGRAMMED BY   M.J. POST                                       **  CIR  130 */
	/* *                  R.A. RICHTER        NOAA/WPL                    **  CIR  140 */
	/* *                                      BOULDER, COLORADO           **  CIR  150 */
	/* *                                      01/27/1981                  **  CIR  160 */
	/* *                                                                  **  CIR  170 */
	/* *  INPUTS!                                                         **  CIR  180 */
	/* *           CHTIK    -  CIRRUS THICKNESS (KM)                      **  CIR  190 */
	/* *                       0 = USE THICKNESS STATISTICS               **  CIR  200 */
	/* *                       .NE. 0 = USER DEFINES THICKNESS            **  CIR  210 */
	/* *                                                                  **  CIR  220 */
	/* *           CALT     -  CIRRUS BASE ALTITUDE (KM)                  **  CIR  230 */
	/* *                       0 = USE CALCULATED VALUE                   **  CIR  240 */
	/* *                       .NE. 0 = USER DEFINES BASE ALTITUDE        **  CIR  250 */
	/* *                                                                  **  CIR  260 */
	/* *           ICIR     -  CIRRUS PRESENCE FLAG                       **  CIR  270 */
	/* *                       0 = NO CIRRUS                              **  CIR  280 */
	/* *                       .NE. 0 = USE CIRRUS PROFILE                **  CIR  290 */
	/* *                                                                  **  CIR  300 */
	/* *           MODEL    -  ATMOSPHERIC MODEL                          **  CIR  310 */
	/* *                       1-5  AS IN MAIN PROGRAM                    **  CIR  320 */
	/* *                       MODEL = 0,6,7 NOT USED SET TO 2            **  CIR  330 */
	/* *                                                                  **  CIR  340 */
	/* *           ISEED    -  RANDOM NUMBER INITIALIZATION FLAG.         **  CIR  350 */
	/* *                       0 = USE DEFAULT MEAN VALUES FOR CIRRUS     **  CIR  360 */
	/* *                       .NE. 0 = INITIAL VALUE OF SEED FOR RANF    **  CIR  370 */
	/* *                       FUNCTION. CHANGE SEED VALUE EACH RUN FOR   **  CIR  380 */
	/* *                       DIFFERENT RANDOM NUMBER SEQUENCES. THIS    **  CIR  390 */
	/* *                       PROVIDES FOR STATISTICAL DETERMINATION     **  CIR  400 */
	/* *                       OF CIRRUS BASE ALTITUDE AND THICKNESS.     **  CIR  410 */
	/* *                                                                  **  CIR  420 */
	/* *  OUTPUTS!                                                        **  CIR  430 */
	/* *         CTHIK        -  CIRRUS THICKNESS (KM)                    **  CIR  440 */
	/* *         CALT         -  CIRRUS BASE ALTITUDE (KM)                **  CIR  450 */
	/* *         DENSTY(16,I) -  ARRAY, ALTITUDE PROFILE OF CIRRUS DENSITY**  CIR  460 */
	/* *         CPROB        -  CIRRUS PROBABILITY                       **  CIR  470 */
	/* *                                                                  **  CIR  480 */
	/* *********************************************************************  CIR  490 */
	/*                                                                       CIR  500 */
	/*                                                                       CIR  640 */
	/*                                                                       CIR  710 */
	/*  SET CIRRUS PROBABILITY AND PROFILE TO ALL ZEROES                     CIR  720 */
	/*                                                                       CIR  730 */
	*cprob = 0.f;
	mdl = card1_1.model;
	/*                                                                       CIR  760 */
	for (i__ = 1; i__ <= 34; ++i__)
	{
		/* L10: */
		model_3.densty[i__ * 63 - 48] = 0.f;
	}
	/*                                                                       CIR  790 */
	/*  CHECK IF USER WANTS TO USE A THICKNESS VALUE HE PROVIDES, CALCULATE  CIR  800 */
	/*  A STATISTICAL THICKNESS, OR USE A MEAN THICKNESS (ISEED = 0).        CIR  810 */
	/*  DEFAULTED MEAN CIRRUS THICKNESS IS 1.0 KM.                           CIR  820 */
	/*                                                                       CIR  830 */
	if (*cthik > 0.f)
	{
		goto L25;
	}
	if (*iseed != 0)
	{
		goto L15;
	}
	*cthik = 1.f;
	goto L25;
/*                                                                       CIR  880 */
/*  CALCULATE CLOUD THICKNESS USING LOWTRAN CIRRUS THICKNESS STATISTICS  CIR  890 */
/*  NOTE - THIS ROUTINE USES A UNIFORM RANDOM NUMBER GENERATOR           CIR  900 */
/*  FUNCTION (RANF) WHICH RETURNS A NUMBER BETWEEN 0 AND 1.              CIR  910 */
/*  THIS FEATURE IS MACHINE DEPENDENT!!                                  CIR  920 */
/*                                                                       CIR  930 */
L15:
	ranset_(iseed);
	urn = ranfun_(&idum);
	for (i__ = 1; i__ <= 10; ++i__)
	{
		if (urn >= tstat[i__ - 1] && urn < tstat[i__])
		{
			*cthik = (float)(i__ - 1);
		}
		/* L20: */
	}
	*cthik = *cthik / 2.f + ranfun_(&idum) / 2.f;
/*                                                                       CIR 1000 */
/*  DENCIR IS CIRRUS DENSITY IN KM-1                                     CIR 1010 */
/*                                                                       CIR 1020 */
L25:
	if (*cext > 0.f)
	{
		dencir = *cext / 2.f;
	}
	else
	{
		dencir = *cthik * .07f;
	}
	/*                                                                       CIR 1080 */
	/*  BASE HEIGHT CALCULATIONS                                             CIR 1090 */
	/*                                                                       CIR 1100 */
	if (card1_1.model < 1 || card1_1.model > 5)
	{
		mdl = 2;
	}
	*cprob = ptab[mdl - 1] * 100.f;
	/*                                                                       CIR 1130 */
	hmax = cbase[mdl + 4] - *cthik;
	brange = hmax - cbase[mdl - 1];
	if (*calt > 0.f)
	{
		goto L27;
	}
	if (*iseed != 0)
	{
		goto L26;
	}
	*calt = camean[mdl - 1];
	goto L27;
L26:
	*calt = brange * ranfun_(&idum) + cbase[mdl - 1];
/*                                                                       CIR 1210 */
/*  PUT CIRRUS DENSITY IN CORRECT ALTITUDE BINS. IF MODEL = 7,           CIR 1220 */
/*  INTERPOLATE EH(16,I) FOR NON-STANDARD ALTITUDE BOUNDARIES.           CIR 1230 */
/*                                                                       CIR 1240 */
L27:
	if (card1_1.model == 7)
	{
		goto L60;
	}
	iv1 = (long)(*calt);
	iv2 = (long)(*calt + *cthik);
	for (i__ = 2; i__ <= 16; ++i__)
	{
		if (i__ >= iv1 && i__ <= iv2)
		{
			model_3.densty[(i__ + 1) * 63 - 48] = dencir;
		}
		/* L30: */
	}
	/*                                                                       CIR 1310 */
	/*  ADJUST FIRST AND LAST CIRRUS LEVEL IF CLOUD DOES NOT ENTIRELY        CIR 1320 */
	/*  FILL EACH LEVEL.                                                     CIR 1330 */
	/*                                                                       CIR 1340 */
	ihgt1 = (long)(*calt);
	ihgt2 = (long)(*calt + *cthik);
	if (ihgt1 != ihgt2)
	{
		goto L35;
	}
	model_3.densty[(ihgt1 + 1) * 63 - 48] *= *cthik;
	return 0;
L35:
	pct1 = 1.f - (*calt - ihgt1);
	model_3.densty[(ihgt1 + 1) * 63 - 48] *= pct1;
	pct2 = *calt + *cthik - ihgt2;
	model_3.densty[(ihgt2 + 1) * 63 - 48] *= pct2;
	return 0;
/*                                                                       CIR 1450 */
/*  INTERPOLATE DENSTY(16,I) FOR USER SUPPLIED ALTITUDE BOUNDARIES       CIR 1460 */
/*                                                                       CIR 1470 */
L60:
	top = *calt + *cthik;
	bottom = *calt;
	if (top < model_3.z__[0])
	{
		return 0;
	}
	if (bottom > model_3.z__[cntrl_1.ml - 1])
	{
		return 0;
	}
	iml = cntrl_1.ml - 1;
	i__1 = iml;
	for (i__ = 1; i__ <= i__1; ++i__)
	{
		zmin = model_3.z__[i__ - 1];
		zmax = model_3.z__[i__];
		denom = zmax - zmin;
		if (bottom <= zmin && top >= zmax)
		{
			model_3.densty[i__ * 63 - 48] = dencir;
		}
		if (bottom >= zmin && top < zmax)
		{
			model_3.densty[i__ * 63 - 48] = dencir * *cthik / denom;
		}
		if (bottom >= zmin && top >= zmax && bottom < zmax)
		{
			model_3.densty[i__ * 63 - 48] = dencir * (zmax - bottom) / denom;
		}
		if (bottom < zmin && top <= zmax && top > zmin)
		{
			model_3.densty[i__ * 63 - 48] = dencir * (top - zmin) / denom;
		}
		/* L70: */
	}
	return 0;
} /* cirrus_ */

#undef cbase2
#undef cbase1
#undef cbase

// ADDED BY GP
int ranset_(long *seed)
{
	srand((unsigned int)*seed);
	return 0;
}

double ranfun_(long *idum)
{
	/* System generated locals */
	float ret_val;

	// TODO ignores idum
	// print(idum);

	return rand();
} /* ranfun_ */
// ADDED BY GP

double abslim_(float *tk, float *awlwc)
{
	/* Initialized data */

	static float pi = 3.14159265f;

	/* System generated locals */
	float ret_val, r__1, r__2;

	/* Builtin functions */
	double exp(double);

	/* Local variables */
	static float tc, es, efin, eqlwc, esmie2, slambd;

	/* CC                                                                     ALM  110 */
	/* CC    FOR CLOUD OR AEROSOL ATTENUATION AS FREQ APPROACHES ZERO         ALM  120 */
	/* CC    MODIFIED DEBYE EQUATIONS FROM RAY (1972) APPL. OPTICS VOL 11     ALM  130 */
	/* CC                                                                     ALM  140 */
	/* CC    ANO= 8.0*10**(-2)  (CM-4)                                        ALM  150 */
	/* CC    ALM= 41.*RR**(-0.21)  (CM-1)  RR IN (MM/HR)                      ALM  160 */
	/* CC                                                                     ALM  170 */
	/* CC   ANO=0.08                                                          ALM  190 */
	/* CC   ALM=41./RR**0.21                                                  ALM  200 */
	tc = *tk - 273.15f;
	/* CC                                                                     ALM  220 */
	efin = tc * .0216474f + 5.27137f - tc * .00131198f * tc;
	/* Computing 2nd power */
	r__1 = tc - 25.f;
	/* Computing 3rd power */
	r__2 = tc - 25.f;
	es = (1.f - (tc - 25.f) * .004579f + r__1 * r__1 * 1.19e-5f - r__2 * (r__2 * r__2) * 2.8e-8f) * 78.54f;
	slambd = exp(2513.98f / *tk) * 3.3836e-4f;
	/* CC                                                                     ALM  270 */
	/* CC   VOL=PI*ANO*ALM**(-4)                                              ALM  280 */
	/* Computing 2nd power */
	r__1 = es + 2.f;
	esmie2 = (es - efin) / (r__1 * r__1);
	/* CC                                                                     ALM  300 */
	/* CC    DIVIDE VOLUME EQUIVALENT LIQUID BY 10 FOR UNITS CONVERSION       ALM  310 */
	/* CC                                                                     ALM  320 */
	eqlwc = *awlwc / 10.f;
	/* CC                                                                     ALM  340 */
	ret_val = *tk * .6951f * 36.f * pi * eqlwc * slambd * esmie2;
	/* CC                                                                     ALM  360 */
	return ret_val;
} /* abslim_ */

/* Subroutine */ int title_(void)
{
	return 0;
} /* title_ */

/* >    BLOCK DATA                                                        BTI  110 */
/*     TITLE INFORMATION                                                 BTI  120 */

/* Subroutine */ int prfdta_(void)
{
	return 0;
} /* prfdta_ */

/* >    BLOCK DATA                                                        PRF  110 */
/*                                                                       PRF  120 */
/*        AEROSOL PROFILE DATA                                           PRF  130 */
/*                                                                       PRF  140 */
/* CC         0-2KM                                                       PRF  150 */
/* CC           HZ2K=5 VIS PROFILES- 50KM,23KM,10KM,5KM,2KM               PRF  160 */
/* CC         >2-10KM                                                     PRF  170 */
/* CC           FAWI50=FALL/WINTER   50KM VIS                             PRF  180 */
/* CC           FAWI23=FALL/WINTER    23KM VIS                            PRF  190 */
/* CC           SPSU50=SPRING/SUMMER  50KM VIS                            PRF  200 */
/* CC           SPSU23=SPRING/SUMMER  23KM VIS                            PRF  210 */
/* CC         >10-30KM                                                    PRF  220 */
/* CC           BASTFW=BACKGROUND STRATOSPHERIC   FALL/WINTER             PRF  230 */
/* CC           VUMOFW=MODERATE VOLCANIC          FALL/WINTER             PRF  240 */
/* CC           HIVUFW=HIGH VOLCANIC              FALL/WINTER             PRF  250 */
/* CC           EXVUFW=EXTREME VOLCANIC           FALL/WINTER             PRF  260 */
/* CC           BASTSS,VUMOSS,HIVUSS,EXVUSS=      SPRING/SUMMER           PRF  270 */
/* CC         >30-100KM                                                   PRF  280 */
/* CC           UPNATM=NORMAL UPPER ATMOSPHERIC                           PRF  290 */
/* CC           VUTONO=TRANSITION FROM VOLCANIC TO NORMAL                 PRF  300 */
/* CC           VUTOEX=TRANSITION FROM VOLCANIC TO EXTREME                PRF  310 */
/* CC           EXUPAT=EXTREME UPPER ATMOSPHERIC                          PRF  320 */

/* Subroutine */ int extdta_(void)
{
	return 0;
} /* extdta_ */

/* >    BLOCK DATA                                                        EXD  110 */
/* CC                                                                     EXD  120 */
/* CC   ALTITUDE REGIONS FOR AEROSOL EXTINCTION COEFFICIENTS              EXD  130 */
/* CC                                                                     EXD  140 */
/* CC                                                                     EXD  150 */
/* CC         0-2KM                                                       EXD  160 */
/* CC           RUREXT=RURAL EXTINCTION   RURABS=RURAL ABSORPTION         EXD  170 */
/* CC           RURSYM=RURAL ASYMMETRY FACTORS                            EXD  180 */
/* CC           URBEXT=URBAN EXTINCTION   URBABS=URBAN ABSORPTION         EXD  190 */
/* CC           URBSYM=URBAN ASYMMETRY FACTORS                            EXD  200 */
/* CC           OCNEXT=MARITIME EXTINCTION  OCNABS=MARITIME ABSORPTION    EXD  210 */
/* CC           OCNSYM=MARITIME ASYMMETRY FACTORS                         EXD  220 */
/* CC           TROEXT=TROPSPHER EXTINCTION  TROABS=TROPOSPHER ABSORPTION EXD  230 */
/* CC           TROSYM=TROPSPHERIC ASYMMETRY FACTORS                      EXD  240 */
/* CC           FG1EXT=FOG1 .2KM VIS EXTINCTION  FG1ABS=FOG1 ABSORPTION   EXD  250 */
/* CC           FG1SYM=FOG1 ASYMMETRY FACTORS                             EXD  260 */
/* CC           FG2EXT=FOG2 .5KM VIS EXTINCTION  FG2ABS=FOG2 ABSORPTION   EXD  270 */
/* CC           FG2SYM=FOG2 ASYMMETRY FACTORS                             EXD  280 */
/* CC         >2-10KM                                                     EXD  290 */
/* CC           TROEXT=TROPOSPHER EXTINCTION  TROABS=TROPOSPHER ABSORPTIONEXD  300 */
/* CC           TROSYM=TROPOSPHERIC ASYMMETRY FACTORS                     EXD  310 */
/* CC         >10-30KM                                                    EXD  320 */
/* CC           BSTEXT=BACKGROUND STRATOSPHERIC EXTINCTION                EXD  330 */
/* CC           BSTABS=BACKGROUND STRATOSPHERIC ABSORPTION                EXD  340 */
/* CC           BSTSYM=BACKGROUND STRATOSPHERIC ASYMMETRY FACTORS         EXD  350 */
/* CC           AVOEXT=AGED VOLCANIC EXTINCTION                           EXD  360 */
/* CC           AVOABS=AGED VOLCANIC ABSORPTION                           EXD  370 */
/* CC           AVOSYM=AGED VOLCANIC ASYMMETRY FACTORS                    EXD  380 */
/* CC           FVOEXT=FRESH VOLCANIC EXTINCTION                          EXD  390 */
/* CC           FVOABS=FRESH VOLCANIC ABSORPTION                          EXD  400 */
/* CC           FVOSYM=FRESH VOLCANIC ASYMMETRY FACTORS                   EXD  410 */
/* CC         >30-100KM                                                   EXD  420 */
/* CC           DMEEXT=METEORIC DUST EXTINCTION                           EXD  430 */
/* CC           DMEABS=METEORIC DUST ABSORPTION                           EXD  440 */
/* CC           DMESYM=METEORIC DUST ASYMMETRY FACTORS                    EXD  450 */
/*                                                                       EXD  460 */
/*     AEROSOL EXTINCTION AND ABSORPTION DATA                            EXD  470 */
/*                                                                       EXD  480 */
/*     MODIFIED TO INCLUDE ASYMMETRY DATA - JAN 1986 (A.E.R. INC.)       EXD  490 */
/*                                                                       EXD  500 */
/*     COMMON /EXTD  /VX2(47),RUREXT(47,4),RURABS(47,4),URBEXT(47,4),    EXD  510 */
/*    1URBABS(47,4),OCNEXT(47,4),OCNABS(47,4),TROEXT(47,4),TROABS(47,4), EXD  520 */
/*    2FG1EXT(47),FG1ABS(47),FG2EXT(47),FG2ABS(47),                      EXD  530 */
/*    3   BSTEXT(47),BSTABS(47),AVOEXT(47),AVOABS(47),FVOEXT(47)         EXD  540 */
/*    4),FVOABS(47),DMEEXT(47),DMEABS(47),                               EXD  550 */
/*                                                                       EXD  560 */
/*                                                                       EXD  570 */
/*                                                                       EXD  770 */
/*         CI64--    STANDARD  CIRRUS  CLOUD  MODEL                      EXD  780 */
/*              ICE 64 MICRON MODE RADIUS CIRRUS CLOUD MODEL             EXD  790 */
/*                                                                       EXD  800 */
/*         CIR4--    OPTICALLY  THIN  CIRRUS  MODEL                      EXD  810 */
/*              ICE  4 MICRON MODE RADIUS CIRRUS CLOUD MODEL             EXD  820 */
/*                                                                       EXD  830 */
/*          EXTINCTION  COEFFICIENTS                                     EXD 7430 */
/*         ABSORPTION  COEFFICIENTS                                      EXD 7550 */
/*         ASYMMETRY  PARAMETER  -  G                                    EXD 7670 */
/*          EXTINCTION COEFFICIENTS                                      EXD 7750 */
/*          ABSORPTION  COEFFICIENTS                                     EXD 7870 */
/*        ASYMMETRY  PARAMETER  -  G                                     EXD 7990 */

/* Subroutine */ int sf296_(void)
{
	return 0;
} /* sf296_ */

/* >    BLOCK DATA                                                        SLF  110 */
/*               06/28/82                                                SLF  120 */
/*               UNITS OF (CM**3/MOL) * 1.E-20                           SLF  130 */
/*                                                                       SLF  220 */
/*                                                                       SLF  230 */
/*                                                                       SLF  260 */
/*                                                                       SLF  270 */
/*                                                                       SLF 4710 */

/* Subroutine */ int sf260_(void)
{
	return 0;
} /* sf260_ */

/* >    BLOCK DATA                                                        B26  110 */
/*               06/28/82                                                B26  120 */
/*               UNITS OF (CM**3/MOL) * 1.E-20                           B26  130 */
/*                                                                       B26  220 */
/*                                                                       B26  230 */
/*                                                                       B26  260 */
/*                                                                       B26  270 */
/*                                                                       B26 4710 */

/* Subroutine */ int bfh2o_(void)
{
	return 0;
} /* bfh2o_ */

/* >    BLOCK DATA                                                        BFH  110 */
/*               06/28/82                                                BFH  120 */
/*               UNITS OF (CM**3/MOL)*1.E-20                             BFH  130 */
/*                                                                       BFH  220 */
/*                                                                       BFH  230 */
/*                                                                       BFH  260 */
/*                                                                       BFH  270 */
/*                                                                       BFH 4710 */

/* Subroutine */ int c4d_(void)
{
	return 0;
} /* c4d_ */

/* >    BLOCK DATA                                                        BC4  110 */
/*        N2 CONTINUUM ABSORPTION COEFFICIENTS                           BC4  130 */
/*     C4 LOCATION  1    V =  2080 CM-1                                  BC4  140 */
/*     C4 LOCATION  133  V =  2740 CM-1                                  BC4  150 */
/*        4M  H2O CONTINUUM                                              BC4  410 */
/*        OZONE U.V. + VISIBLE BAND MODEL ABSORPTION COEFF               BC4  420 */
/*     C8 LOCATION  1    V =  13000  CM-1                                BC4  430 */
/*     C8 LOCATION  56   V =  24200  CM-1                                BC4  440 */
/*        DV = 200  CM-1                                                 BC4  450 */
/*     C8 LOCATION  57   V =  27500  CM-1                                BC4  460 */
/*     C8 LOCATION  102  V =  50000  CM-1                                BC4  470 */
/*        DV = 500  CM-1                                                 BC4  480 */

/* Subroutine */ int phsdta_(void)
{
	return 0;
} /* phsdta_ */

/* >    BLOCK DATA                                                        BPH  110 */
/* CC                                                                     BPH  120 */
/* CC   ROUTINE TO STORE TABLE TO CALL UP PROPER PHASE FUNCTION           BPH  130 */
/* CC   AND 70 AVERAGE PHASE FUNCTIONS                                    BPH  140 */
/* CC                                                                     BPH  150 */
/*     COMMON/MNMPHS/ MNUM(27,26),PHSFNC(34,70)                          BPH  160 */
/* >    END                                                               BPH 6460 */
/* >      SUBROUTINE RANSET(I)                                            BPH 6470 */
/* >      COMMON/RST/ II                                                  BPH 6480 */
/* >      RANET= RAN(I)                                                   BPH 6490 */
/* >        II=RANET                                                      BPH 6500 */
/* >      RETURN                                                          BPH 6510 */
/* >      END                                                             BPH 6520 */
/* >      FUNCTION RANF                                                   BPH 6530 */
/* >      COMMON/RST/ II                                                  BPH 6540 */
/* >      RANF= RAN(II)                                                   BPH 6550 */
/* >        II=RANF                                                       BPH 6560 */
/* >      RETURN                                                          BPH 6570 */

/* Subroutine */ int cptrcg_(void)
{
	return 0;
} /* cptrcg_ */

/* >    BLOCK DATA                                                        CPT  105 */
/*                                                                       CPT  110 */
/*     C' FOR TRACE GASES (NH3, NO, NO2, SO2)                            CPT  120 */
/* =NH3 ====C' FOR    2 BAND MODEL                                        CPT  190 */
/* =NH3 ====    0-  385                                                   CPT  200 */
/* =NH3 ====  390- 2150                                                   CPT  340 */
/* =NO  ====C' FOR    1 BAND MODEL                                        CPT  890 */
/* =NO  ==== 1700- 2005                                                   CPT  900 */
/* =NO2 ====C' FOR    1 BAND MODEL                                        CPT 1010 */
/* =NO2 ====  580-  925, 1515- 1695, 2800- 2970                           CPT 1020 */
/* =SO2 ====C' FOR    2 BAND MODEL                                        CPT 1260 */
/* =SO2 ====    0-  185                                                   CPT 1270 */
/* =SO2 ====  400-  650,  950- 1460, 2415- 2580                           CPT 1350 */

/* Subroutine */ int cpumix_(void)
{
	return 0;
} /* cpumix_ */

/* >    BLOCK DATA                                                        CPU  105 */
/*                                                                       CPU  110 */
/*     C' FOR UNIFORMLY MIXED GASES (CO2, CO, CH4, N2O, O2)              CPU  120 */
/* =CO2 ====C' FOR    8 BAND MODELS                                       CPU  310 */
/* =CO2 ====  425-  835                                                   CPU  320 */
/* =CO2 ====  840- 1440                                                   CPU  460 */
/* =CO2 ==== 1805- 2855                                                   CPU  660 */
/* =CO2 ==== 3070- 3755                                                   CPU 1000 */
/* =CO2 ==== 3760- 4065                                                   CPU 1230 */
/* =CO2 ==== 4530- 5380                                                   CPU 1340 */
/* =CO2 ==== 5905- 7025                                                   CPU 1620 */
/* =CO2 ==== 7395- 7785, 8030- 8335, 9340- 9670                           CPU 1980 */
/* =CO  ====C' FOR    2 BAND MODEL                                        CPU 2310 */
/* =CO  ====    0-  175                                                   CPU 2320 */
/* =CO  ==== 1940- 2285, 4040- 4370                                       CPU 2400 */
/* =CH4 ====C' FOR    1 BAND MODEL                                        CPU 2630 */
/* =CH4 ==== 1065- 1775, 2345- 3230, 4110- 4690, 5865- 6135               CPU 2640 */
/* =N2O ====C' FOR    3 BAND MODEL                                        CPU 3400 */
/* =N2O ====    0-  120                                                   CPU 3410 */
/* =N2O ====  490-  775,  865-  995, 1065- 1385, 1545- 2040, 2090- 2655   CPU 3470 */
/* =N2O ==== 2705- 2865, 3245- 3925, 4260- 4470, 4540- 4785, 4910- 5165   CPU 4030 */
/* =O2  ====C' FOR    2 BAND MODEL                                        CPU 4520 */
/* =O2  ====    0-  265                                                   CPU 4530 */
/* =O2  ==== 7650- 8080, 9235- 9490,12850-13220,14300-14600,15695-15955   CPU 4630 */

/* Subroutine */ int cph2o_(void)
{
	return 0;
} /* cph2o_ */

/* >    BLOCK DATA                                                        BCH  105 */
/*                                                                       BCH  110 */
/*     C' FOR WATER VAPOR (H2O)                                          BCH  120 */
/* =H2O ====C' FOR   14 BAND MODELS                                       BCH  280 */
/* =H2O ====    0-  345                                                   BCH  290 */
/* =H2O ====  350- 1000                                                   BCH  410 */
/* =H2O ==== 1005- 1640                                                   BCH  630 */
/* =H2O ==== 1645- 2530                                                   BCH  850 */
/* =H2O ==== 2535- 3420                                                   BCH 1140 */
/* =H2O ==== 3425- 4310                                                   BCH 1430 */
/* =H2O ==== 4315- 6150                                                   BCH 1720 */
/* =H2O ==== 6155- 8000                                                   BCH 2290 */
/* =H2O ==== 8005- 9615                                                   BCH 2860 */
/* =H2O ==== 9620-11540                                                   BCH 3370 */
/* =H2O ====11545-13070                                                   BCH 3970 */
/* =H2O ====13075-14860                                                   BCH 4450 */
/* =H2O ====14865-16045                                                   BCH 5010 */
/* =H2O ====16340-17860                                                   BCH 5380 */

/* Subroutine */ int cpo3_(void)
{
	return 0;
} /* cpo3_ */

/* >    BLOCK DATA                                                        CPO  105 */
/*                                                                       CPO  110 */
/*     C' FOR O3                                                         CPO  120 */
/* =O3  ====C' FOR    5 BAND MODELS                                       CPO  180 */
/* =O3  ====    0-  200                                                   CPO  190 */
/* =O3  ====  515- 1275                                                   CPO  270 */
/* =O3  ==== 1630- 2295                                                   CPO  520 */
/* =O3  ==== 2670- 2845                                                   CPO  750 */
/* =O3  ==== 2850- 3260                                                   CPO  830 */

/* Subroutine */ int wvbnrg_(void)
{
	return 0;
} /* wvbnrg_ */

/* >    BLOCK DATA                                                        WVB  105 */
/*     WAVENUMBER-LOW AND WAVENUMBER-HIGH SPECIFY A BAND REGION          WVB  110 */
/*     FOR A MOLECULAR ABSORBER.                                         WVB  120 */
/*     THE UNIT FOR WAVENUMBER IS 1/CM.                                  WVB  130 */
/*     -999 IS AN INDICATOR TO INDICATE THE END OF ABSORPTION BANDS      WVB  140 */
/*     FOR ANY SPECIFIC ABSORBER.                                        WVB  150 */
/*                                                                       WVB  230 */
/*                                                                       WVB  280 */
/*                                                                       WVB  310 */
/*                                                                       WVB  360 */
/*                                                                       WVB  390 */
/*                                                                       WVB  420 */
/*                                                                       WVB  470 */
/*                                                                       WVB  500 */
/*                                                                       WVB  530 */
/*                                                                       WVB  560 */
/*                                                                       WVB  590 */

/* Subroutine */ int mdta_(void)
{
	return 0;
} /* mdta_ */

/* >    BLOCK DATA                                                        MLT  110 */
/*                                                                       MLT  120 */
/*     CLOUD AND RAIN   DATA                                             MLT  130 */
/*                                                                       MLT  140 */
/*      COMMON /MDATA/  Z(50),P(50),T(50),WH(50),WCO2(50),WO(50),        MLT  150 */
/*    X WN2O(50),WCO(50),WCH4(50),WO2(50),                               MLT  160 */
/*    X CLD(50,7),RR(50,7)                                               MLT  170 */
/*                                                                       MLT  220 */
/* CC   CLOUD MODELS 1-5                                                  MLT  340 */
/* CC   RAIN MODELS 1-5                                                   MLT  420 */
/*     DATA CO2       /                                                  MLT  510 */

/* Subroutine */ int mlatmb_(void)
{
	return 0;
} /* mlatmb_ */

/* >    BLOCK DATA                                                        MLT  105 */
/* ***********************************************************************MLT  110 */
/*     THIS SUBROUTINE INITIALIZES THE 6 BUILT-IN ATMOSPHERIC PROFILES   MLT  120 */
/*     (FROM 'OPTICAL PROPERTIES OF THE ATMOSPHERE, THIRD EDITION'       MLT  130 */
/*     AFCRL-72-0497 (AD 753 075), 'U.S. STANDARD ATMOSPHERE 1976' AND   MLT  140 */
/*     'SUPPLEMENTS 1966'), PLUS COLLECTED CONSTITUENT PROFILES (REF)    MLT  150 */
/*     AND SETS OTHER CONSTANTS RELATED TO THE ATMOSPHERIC PROFILES      MLT  160 */
/* ***********************************************************************MLT  170 */
/*     COMMON /TRAC/ TRAC(50,21)                                         MLT  320 */
/*     DATA ALT (KM)  /                                                  MLT  370 */
/*     DATA PRESSURE  /                                                  MLT  490 */
/*     DATA TEMPERATUR/                                                  MLT 1160 */
/*     DATA  H2O      /                                                  MLT 1830 */
/*     DATA CO2       /                                                  MLT 2500 */
/*     DATA CO2       /                                                  MLT 2620 */
/*     DATA CO2       /                                                  MLT 2740 */
/*     DATA CO2       /                                                  MLT 2860 */
/*     DATA CO2       /                                                  MLT 2980 */
/*     DATA CO2       /                                                  MLT 3100 */
/*     DATA OZONE     /                                                  MLT 3220 */
/*     DATA  N2O      /                                                  MLT 3890 */
/*     DATA  N2O      /                                                  MLT 4010 */
/*     DATA  N2O      /                                                  MLT 4130 */
/*     DATA  N2O      /                                                  MLT 4250 */
/*     DATA  N2O      /                                                  MLT 4370 */
/*     DATA  N2O      /                                                  MLT 4490 */
/*     DATA CO        /                                                  MLT 4610 */
/*     DATA CO        /                                                  MLT 4730 */
/*     DATA CO        /                                                  MLT 4850 */
/*     DATA CO        /                                                  MLT 4970 */
/*     DATA CO        /                                                  MLT 5090 */
/*     DATA CO        /                                                  MLT 5210 */
/*     DATA  CH4      /                                                  MLT 5330 */
/*     DATA  CH4      /                                                  MLT 5450 */
/*     DATA  CH4      /                                                  MLT 5570 */
/*     DATA  CH4      /                                                  MLT 5690 */
/*     DATA  CH4      /                                                  MLT 5810 */
/*     DATA  CH4      /                                                  MLT 5930 */
/*     DATA O2        /                                                  MLT 6050 */
/*     DATA O2        /                                                  MLT 6170 */
/*     DATA O2        /                                                  MLT 6290 */
/*     DATA O2        /                                                  MLT 6410 */
/*     DATA O2        /                                                  MLT 6530 */
/*     DATA O2        /                                                  MLT 6650 */
/*     DATA DENSITY   /                                                  MLT 6770 */

/* Subroutine */ int schrun_(float *v, float *cprun)
{
	/* Initialized data */

	static float v1 = 49600.f;
	static float v2 = 51710.f;
	static float dv = 5.f;
	static long inum = 425;

	/* Builtin functions */
	long s_wsle(cilist *), do_lio(long *, long *, char *, long),
		e_wsle(void);

	/* Local variables */
	static long ind;

	/* Fortran I/O blocks */
	static cilist io___1531 = {0, 6, 0, 0, 0};

	*cprun = -20.f;
	if (*v < v1)
	{
		goto L20;
	}
	if (*v > v2)
	{
		goto L20;
	}
	ind = (*v - v1) / dv + 1.0001f;
	if (ind > inum)
	{
		s_wsle(&io___1531);
		do_lio(&c__9, &c__1, (char *)"  IND GT INUM  V IND ", (long)21);
		do_lio(&c__4, &c__1, (char *)&(*v), (long)sizeof(float));
		do_lio(&c__3, &c__1, (char *)&ind, (long)sizeof(long));
		e_wsle();
		goto L20;
	}
	*cprun = shur_1.shn[ind - 1];
L20:
	return 0;
} /* schrun_ */

/* Subroutine */ int shumg_(void)
{
	return 0;
} /* shumg_ */

/* >    BLOCK DATA                                                        SHM  110 */
/*                                                                       SHM  120 */
/*     SCHUMANN-RUNGE O2 BAND MODEL - SAMPLE CODING                      SHM  130 */
/*                                                                       SHM  140 */

///* Main program alias */ int lwtrn7_()
//{
//	MAIN__();
//	return 0;
//}
