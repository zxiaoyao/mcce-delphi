/**
 * @file delphi_constants.h
 * @brief globally defined constants used for delphicpp
 *
 * @author Chuan Li, chuanli@clemson.edu
 */

#ifndef DELPHI_CONSTANTS_H_
#define DELPHI_CONSTANTS_H_

#include <vector>
#include <string>
#include "../interface/environment.h"
#include "../misc/misc_grid.h"

using namespace std;

#ifdef MX
const real fPi    =  3.141592653589793; ///< pi
const real f4Pi   =  1.256637061435917e+1; ///< 4*pi
const real fSixth =  1.666666666666667e-1; ///< 1/6
const real fZero  =  1.0e-15; ///< practical zero for comparing real numbers
#endif

#ifdef SP
const real fPi    =  3.141593;
const real f4Pi   =  1.256637e+1;
const real fSixth =  1.666667e-1;      
const real fZero  =  1.0e-6;
#endif

#ifdef DP
const real fPi    =  3.141592653589793;
const real f4Pi   =  1.256637061435917e+1;
const real fSixth =  1.666666666666667e-1;
const real fZero  =  1.0e-15;
#endif

#ifdef LD
const real fPi    =  3.1415926535897932384626433832795;
const real f4Pi   =  1.2566370614359172953850573533118e+1; 
const real fSixth =  1.6666666666666666666666666666667e-1;
const real fZero  =  1.0e-15;
#endif 

const int    iStatementNum = 45; ///< number of statements
const int    iFunctionNum_FullName  = 11; ///< number of functions in full name
const int    iFunctionNum_ShortName = 5; ///< number of functions in short name

const int    iDMax = 50;
const double dAbsoluteZero = -273.15; /// temperature of absolute zero
const double dAtomicUnitCrg = 1.602176487e-19; ///< e, Coulomb C
const double dBoltzmannConstant = 1.3806504e-23; ///< k, Joule per Kelvin JK^(-1)
const double dVacuumPermittivity = 8.8541878176e-12; ///< e0, farads per meter Fm^(-1)
const double dEPK = 167100.9162872952; ///< e^2/(4*pi*e0*k*1.0e-10)
      
const char rgcFileMap[] = "qdiffxas: qdiffxs4 with an improved surfacing routine";

/**
 * struct used to pass atom info from delphicpp to mcce
 */
typedef struct {
   real x;
   real y;
   real z;
   real crg;
   real size;
} SAtomInfo;

/**
 * struct used to pass calculated values between delphicpp and mcce
 */
typedef struct {
   //------- IN
   integer gsize;
   real scale;
   float grids_per_ang;
   int del_runs;
   int n_retry; // default = 0, reset delphi failure counter for this conformer
   string pdbfile;
   int pdbformat;
   real indi;
   real exdi;
   real ionrad;
   real prbrad;
   real salt;
   int  bndcon;
   real center[3];
   //string frcfile;
   //string phifile;
   string uniqID;

   //-------- INTERMEDIATE
   vector<real> phimap;
   real scale1;
   SGrid<real> oldmid1;
   integer igrid1;

   //-------- OUT
   real ergs;
   vector<real> phiv;
   char del_err;
} SMCCE;

#endif // DELPHI_CONSTANTS_H_

