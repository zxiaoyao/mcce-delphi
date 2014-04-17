/**
 * Globally defined macros and constants.
 */
#ifndef DELPHI_CONSTANTS_H
#define DELPHI_CONSTANTS_H

#include "../interface/environment.h"

#ifdef MX
const real fPi    =  3.141592653589793; ///< pi
const real f4Pi   =  1.256637061435917e+1; ///< 4*pi
const real fSixth =  1.666666666666667e-1; ///< 1/6
#endif

#ifdef SP
const real fPi    =  3.141593;
const real f4Pi   =  1.256637e+1;
const real fSixth =  1.666667e-1;      
#endif

#ifdef DP
const real fPi    =  3.141592653589793;
const real f4Pi   =  1.256637061435917e+1;
const real fSixth =  1.666666666666667e-1;
#endif

#ifdef LD
const real fPi    =  3.1415926535897932384626433832795;
const real f4Pi   =  1.2566370614359172953850573533118e+1; 
const real fSixth =  1.6666666666666666666666666666667e-1;
#endif 

const int    iDMax = 50;
const double dAbsoluteZero = -273.15;
const double dMinimalDebyeLength = 1.0e-6;
const double dAtomicUnitCrg = 1.602176487e-19; ///< e, Coulomb C
const double dBoltzmannConstant = 1.3806504e-23; ///< k, Joule per Kelvin JK^(-1)
const double dVacuumPermittivity = 8.8541878176e-12; ///< e0, farads per meter Fm^(-1)
const double dEPK = 167100.9162872952; ///< e^2/(4*pi*e0*k*1.0e-10)
      
const char rgcFileMap[] = "qdiffxas: qdiffxs4 with an improved surfacing routine";

typedef struct {
   real gsize;
   real scale;
   real indi;
   real exdi;
   real ionrad;
   real prbrad;
   real salt;
   int  bndcon;
   real center[3];

} SMCCE;




#endif

