#include <cmath>
#include "misc_grid.h"
#include "misc_grid_impls.cpp"


/*--------------------- overlaod operator << --------------------*/
template <class T> extern ostream& operator<< (ostream& os, SGrid<T>& data)
{
   os << "(" << data.nX << ", " << data.nY << ", " << data.nZ << ")";

   return os;
}


template <class T> extern ostream& operator<< (ostream& os, SGridValue<T>& data)
{
   os << "("  << data.nGrid.nX << ", " << data.nGrid.nY << ", " << data.nGrid.nZ << "; " << data.nValue << ")";

   return os;
}


template <class T> extern ostream& operator<< (ostream& os, SExtrema<T>& data)
{
   os << "("  << data.nMin.nX << ", " << data.nMin.nY << ", " << data.nMin.nZ << "; "
      << data.nMax.nX << ", " << data.nMax.nY << ", " << data.nMax.nZ << ")";

   return os;
}

/*------------------- overload operator + -----------------------*/
   
/**
 *  Adds two variables of coord/int_coord derived type
 *
 * \code
 * SGrid <real>    fVec = fVec1 + fVec2: vplus(a,b);
 * SGrid <integer> iVec = iVec1 + iVec2: ivplus(a,b)
 * \endcode
 */
template <class T> SGrid <T> operator+ (const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   SGrid <T> nVector3;
      
   nVector3.nX = nVector1.nX + nVector2.nX;
   nVector3.nY = nVector1.nY + nVector2.nY;
   nVector3.nZ = nVector1.nZ + nVector2.nZ;    
   return nVector3;
};   
  
/**
 * Adds real/integer variable to coord/int_coord derived type
 *
 * \code
 * SGrid <real>    fVec2 = fVec1 + fVal:  vplus2(a,b);
 * SGrid <integer> iVec2 = iVec1 + iVal: ivplus2(a,b)
 * \endcode
 */
template <class T> SGrid <T> operator+ (const SGrid <T>& nVector, const T& nValue)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = nVector.nX + nValue;
   nRtVector.nY = nVector.nY + nValue;
   nRtVector.nZ = nVector.nZ + nValue;    
   return nRtVector;
};   
   
/**
 * Adds coord/int_coord derived type to real/integer variable
 *
 * \code
 * SGrid <real>    fVec2 = fVal + fVec1:  vplus3(a,b);
 * SGrid <integer> iVec2 = iVal + iVec1: ivplus3(a,b)
 * \endcode
 */
template <class T> SGrid <T> operator+ (const T& nValue , const SGrid <T>& nVector)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = nValue + nVector.nX;
   nRtVector.nY = nValue + nVector.nY;
   nRtVector.nZ = nValue + nVector.nZ;    
   return nRtVector;
};   

/*------------------- overload operator - -----------------------*/
   
/**
 * Substracts two variables of coord/int_coord derived type
 *
 * \code
 * SGrid <real>    fVec = fVec1 - fVec2:  vminus(a,b);
 * SGrid <integer> iVec = iVec1 - iVec2: ivminus(a,b)
 * \endcode
 */
template <class T> SGrid <T> operator- (const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   SGrid <T> nVector3;
      
   nVector3.nX = nVector1.nX - nVector2.nX;
   nVector3.nY = nVector1.nY - nVector2.nY;
   nVector3.nZ = nVector1.nZ - nVector2.nZ;    
   return nVector3;
};

/**
 * Substracts real/integer variable from coord/int_coord derived type
 *
 * \code
 * SGrid <real>    fVec2 = fVec1 - fVal:  vminus2(a,b);
 * SGrid <integer> iVec2 = iVec1 - iVal: ivminus2(a,b)
 * \endcode
 */
template <class T> SGrid <T> operator- (const SGrid <T>& nVector, const T& nValue)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = nVector.nX - nValue;
   nRtVector.nY = nVector.nY - nValue;
   nRtVector.nZ = nVector.nZ - nValue;    
   return nRtVector;
};   

/**
 * Substracts coord/int_coord derived type from real/integer variable
 *
 * \code
 * SGrid <real>    fVec2 = fVal - fVec1:  vminus3(a,b);
 * SGrid <integer> iVec2 = iVal - iVec1: ivminus3(a,b)
 * \endcode
 */
template <class T> SGrid <T> operator- (const T& nValue, const SGrid <T>& nVector)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = nValue - nVector.nX;
   nRtVector.nY = nValue - nVector.nY;
   nRtVector.nZ = nValue - nVector.nZ;    
   return nRtVector;
};

/**
 * Negation of variable of coord/int_coord derived type
 *
 * \code
 * SGrid <real>    fVec2 = -fVec1:  neg(a);
 * SGrid <integer> iVec2 = -iVec1: ineg(a)
 * \endcode
 */
template <class T> SGrid <T> operator- (const SGrid <T>& nVector)
{
   SGrid <T> nRtVector;
   
   nRtVector.nX = -nVector.nX;
   nRtVector.nY = -nVector.nY;
   nRtVector.nZ = -nVector.nZ;
   return nRtVector;
};
  
/*------------------- overload operator * -----------------------*/
   
/**
 * Multiplies two variables of coord/int_coord derived type
 *
 * \code
 * SGrid <real>    fVec = fVec1 * fVec2:  vmult(a,b);
 * SGrid <integer> iVec = iVec1 * iVec2: ivmult(a,b)
 * \endcode
 */
template <class T> SGrid <T> operator* (const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   SGrid <T> nVector3;
      
   nVector3.nX = nVector1.nX * nVector2.nX;
   nVector3.nY = nVector1.nY * nVector2.nY;
   nVector3.nZ = nVector1.nZ * nVector2.nZ;    
   return nVector3;
};     
   
/**
 * Multiplies real/integer variable to coord/int_coord derived type
 *
 * \code
 * SGrid <real>    fVec2 = fVec1 * fVal:  vmult2(a,b);
 * SGrid <integer> iVec2 = iVec1 * iVal: ivmult2(a,b)
 * \endcode
 */
template <class T> SGrid <T> operator* (const SGrid <T>& nVector, const T& nValue)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = nVector.nX * nValue;
   nRtVector.nY = nVector.nY * nValue;
   nRtVector.nZ = nVector.nZ * nValue;    
   return nRtVector;
};    
   
/**
 * Multiplies coord/int_coord derived type to real/integer variable
 *
 * \code
 * SGrid <real>    fVec2 = fVal * fVec1:  vmult3(a,b);
 * SGrid <integer> iVec2 = iVal * iVec1: ivmult3(a,b)
 * \endcode
 */
template <class T> SGrid <T> operator* (const T& nValue, const SGrid <T>& nVector)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = nValue * nVector.nX;
   nRtVector.nY = nValue * nVector.nY;
   nRtVector.nZ = nValue * nVector.nZ;    
   return nRtVector;
};      
   
/*--------------------- overload operator / ---------------------*/

/**
 * Divides coord derived type by real or divides int_coord derived type by real/integer
 *
 * \code
 * SGrid <real,real>       fVec2 = fVec1/fVal:   vdiv(a,b);
 * SGrid <real,integer>    fVec1 = iVec1/fVal:  ivdiv(a,b);
 * SGrid <integer,integer> iVec2 = iVec1/iVal: ivdiv2(a,b)
 * \endcode
 */
template <class T, class N> SGrid <T> operator/ (const SGrid <N>& nVector, const T& nValue)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = (T)(nVector.nX)/nValue;
   nRtVector.nY = (T)(nVector.nY)/nValue;
   nRtVector.nZ = (T)(nVector.nZ)/nValue;   
   
  return nRtVector;
};

/*------------------ new operator: dot product ------------------*/
   
/**
 * dot product
 *
 * \code
 * real    fResult = optDot<real>(fVec1,fVec2)   :  vdot(a,b);
 * integer iResult = optDot<integer>(iVec1,iVec2): ivdot(a,b) 
 * \endcode
 */
template <class T> T optDot(const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   T nValue;
   nValue = nVector1.nX*nVector2.nX + nVector1.nY*nVector2.nY + nVector1.nZ*nVector2.nZ;
   return nValue;
};
   
/*----------------- new operator: cross product -----------------*/
   
/**
 * cross product
 *
 * \code
 * SGrid <real>    fVec3 = optCross<real>(fVec1,fVec2)   :  vx(a,b);
 * SGrid <integer> iVec3 = optCross<integer>(iVec1,iVec2): ivx(a,b)
 * \endcode
 */
template <class T> SGrid <T> optCross(const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   SGrid <T> nVector3;
      
   nVector3.nX = nVector1.nY*nVector2.nZ - nVector1.nZ*nVector2.nY;
   nVector3.nY = nVector1.nZ*nVector2.nX - nVector1.nX*nVector2.nZ;
   nVector3.nZ = nVector1.nX*nVector2.nY - nVector1.nY*nVector2.nX;
   return nVector3; 
};   
   
/*-------------------- new math func. optSQRT() -----------------*/
   
/**
 * square root
 *
 * \code
 * SGrid <real> fVec2 = optSQRT(fVec1): vsqrt(a)
 * \endcode
 */   
SGrid <real> optSQRT(const SGrid <real>& nVector)
{
   SGrid <real> nRtVector;
      
   nRtVector.nX = sqrt(nVector.nX);
   nRtVector.nY = sqrt(nVector.nY);
   nRtVector.nZ = sqrt(nVector.nZ);
   return nRtVector;
};
   
/*--------------------- new math func. optABS() -----------------*/

/**
 * absolute value
 *
 * \code
 * SGrid <real>    fVec2 = optABS<real>(fVec1):     vabs(a)
 * SGrid <integer> iVec2 = optABS<integer>(iVec1): ivabs(a)
 * \endcode
 */
template <class T> SGrid <T> optABS(const SGrid <T>& nVector)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = nVector.nX > 0 ? nVector.nX : -nVector.nX;
   nRtVector.nY = nVector.nY > 0 ? nVector.nY : -nVector.nY;
   nRtVector.nZ = nVector.nZ > 0 ? nVector.nZ : -nVector.nZ;
      
   return nRtVector;
};  

/*----------------- convert one type to another -----------------*/
   
/**
 * Converts coord type into int_coord type:
 *
 * \code
 * SGrid <integer> iVec = optCast<integer,real>(fVec): ivint(a)
 * \endcode
 *
 * Converts int_coord type into coord type:
 * \code
 * SGrid <real> iVec = optCast<real,integer>(iVec): vfloat(a)
 * \endcode
 */   
template <class T, class N> SGrid <T> optCast(const SGrid <N>& nVector)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = (T)(nVector.nX);
   nRtVector.nY = (T)(nVector.nY);
   nRtVector.nZ = (T)(nVector.nZ);
   return nRtVector;
};

/*----------------- round to the nearest integer ----------------*/

/**
 * Notes: C++ always truncates, aka rounds down. If you want it to 
 * round to the nearest intager, add 0.5 or 0.5f before casting.
 *
 * Converts coord type into int_coord type with nint
 *
 * \code
 * SGrid <integer> iVec = optRound<integer>(fVec): ivnint(a)
 * \endcode
 */ 
SGrid <integer> optRound(const SGrid <real>& nVector)
{
   SGrid <integer> nRtVector;
   nRtVector.nX = (integer)(nVector.nX + (real)0.5);
   nRtVector.nY = (integer)(nVector.nY + (real)0.5);
   nRtVector.nZ = (integer)(nVector.nZ + (real)0.5);
      
   return nRtVector;
};

/*--------------------- new math func. optMin() -----------------*/

/**
 * minimal entry (version I)
 *
 * \code
 * SGrid <real>    fVec2 = optMin<real>(fVal,fVec1):     vmin(b,a);
 * SGrid <integer> iVec2 = optMin<integer>(iVal,iVec1): ivmin(b,a)
 * \endcode
 */
template <class T> SGrid <T> optMin(const T& nValue, const SGrid <T>& nVector)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = nValue < nVector.nX ? nValue : nVector.nX;
   nRtVector.nY = nValue < nVector.nY ? nValue : nVector.nY;
   nRtVector.nZ = nValue < nVector.nZ ? nValue : nVector.nZ;
      
   return nRtVector;
}; 

/**
 * minimal entry (version II)
 *
 * \code
 * SGrid <real>    fVec2 = optMin<real>(fVec1,fVal):     vmin2(b,a);
 * SGrid <integer> iVec2 = optMin<integer>(iVec1,iVal): ivmin2(b,a)
 * \endcode
 */
template <class T> SGrid <T> optMin(const SGrid <T>& nVector, const T& nValue)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = nValue < nVector.nX ? nValue : nVector.nX;
   nRtVector.nY = nValue < nVector.nY ? nValue : nVector.nY;
   nRtVector.nZ = nValue < nVector.nZ ? nValue : nVector.nZ;
      
   return nRtVector;
}; 

/**
 * minial entry (version III)
 *
 * \code
 * SGrid <real>    fVec3 = optMin<real>(fVec1,fVec2):     vmin3(b,a);
 * SGrid <integer> iVec3 = optMin<integer>(iVec1,iVec2): ivmin3(b,a)
 * \endcode
 */
template <class T> SGrid <T> optMin(const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = nVector1.nX < nVector2.nX ? nVector1.nX : nVector2.nX;
   nRtVector.nY = nVector1.nY < nVector2.nY ? nVector1.nY : nVector2.nY;
   nRtVector.nZ = nVector1.nZ < nVector2.nZ ? nVector1.nZ : nVector2.nZ;
      
   return nRtVector;
}; 

/**
 * minial entry (vesion IV)
 *
 * \code
 * SGrid <real>    fVal = optMin<real>(fVec1):     vmin4(a);
 * SGrid <integer> iVal = optMin<integer>(iVec1): ivmin4(a)
 * \endcode
 */
template <class T> T optMin(const SGrid <T>& nVector)
{
   T nRtVal;   
      
   nRtVal = nVector.nX < nVector.nY ? nVector.nX : nVector.nY;
   nRtVal = nRtVal < nVector.nZ ? nRtVal : nVector.nZ;

   return nRtVal;
}; 

/*------------------ new math func. optMax() ------------------*/

/**
 * maximal entry (version I)
 *
 * \code
 * SGrid <real>    fVec2 = optMax<real>(fVal,fVec1):     vmax(b,a);
 * SGrid <integer> iVec2 = optMax<integer>(iVal,iVec1): ivmax(b,a)
 * \endcode
 */
template <class T> SGrid <T> optMax(const T& nValue, const SGrid <T>& nVector)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = nValue > nVector.nX ? nValue : nVector.nX;
   nRtVector.nY = nValue > nVector.nY ? nValue : nVector.nY;
   nRtVector.nZ = nValue > nVector.nZ ? nValue : nVector.nZ;
      
   return nRtVector;
}; 

/**
 * maximal entry (version II)
 *
 * \code
 * SGrid <real>    fVec2 = optMax<real>(fVec1,fVal):     vmax2(b,a);
 * SGrid <integer> iVec2 = optMax<integer>(iVec1,iVal): ivmax2(b,a)
 * \endcode
 */
template <class T> SGrid <T> optMax(const SGrid <T>& nVector, const T& nValue)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = nValue > nVector.nX ? nValue : nVector.nX;
   nRtVector.nY = nValue > nVector.nY ? nValue : nVector.nY;
   nRtVector.nZ = nValue > nVector.nZ ? nValue : nVector.nZ;
      
   return nRtVector;
}; 

/**
 * maximal entry (version III)
 *
 * \code
 * SGrid <real>    fVec3 = optMax<real>(fVec1,fVec2):     vmax3(b,a);
 * SGrid <integer> iVec3 = optMax<integer>(iVec1,iVec2): ivmax3(b,a)
 * \endcode
 */
template <class T> SGrid <T> optMax(const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = nVector1.nX > nVector2.nX ? nVector1.nX : nVector2.nX;
   nRtVector.nY = nVector1.nY > nVector2.nY ? nVector1.nY : nVector2.nY;
   nRtVector.nZ = nVector1.nZ > nVector2.nZ ? nVector1.nZ : nVector2.nZ;
   return nRtVector;
}; 

/**
 * maximal entry (version IV)
 *
 * \code
 * SGrid <real>    fVal = optMax<real>(fVec1):     vmax4(a);
 * SGrid <integer> iVal = optMax<integer>(iVec1): ivmax4(a)
 * \endcode
 */
template <class T> T optMax(const SGrid <T>& nVector)
{
   T nRtVal;   
      
   nRtVal = nVector.nX > nVector.nY ? nVector.nX : nVector.nY;
   nRtVal = nRtVal > nVector.nZ ? nRtVal : nVector.nZ;
      
   return nRtVal;
};


/*--------------------- new func. optMinSign() ------------------*/

/**
 * minimal sign (version I)
 *
 * \code
 * SGrid <real> fVec2 = optMinSign<real>(fVal,fVec1): vmsign(b,a)
 * \endcode
 */
template <class T> SGrid <T> optMinSign(const T& nValue, const SGrid <T>& nVector)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = (nVector.nX > 0.0) ? -nValue*nVector.nX : nValue*nVector.nX;
   nRtVector.nY = (nVector.nY > 0.0) ? -nValue*nVector.nY : nValue*nVector.nY;
   nRtVector.nZ = (nVector.nZ > 0.0) ? -nValue*nVector.nZ : nValue*nVector.nZ;
   return nRtVector;
};

/**
 * minial sign (version II)
 *
 * \code
 * SGrid <real> fVec2 = optMinSign<real>(fVec1,fVal): vmsign2(b,a)
 * \endcode
 */
template <class T> SGrid <T> optMinSign(const SGrid <T>& nVector, const T& nValue)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = (nVector.nX > 0.0) ? -nValue*nVector.nX : nValue*nVector.nX;
   nRtVector.nY = (nVector.nY > 0.0) ? -nValue*nVector.nY : nValue*nVector.nY;
   nRtVector.nZ = (nVector.nZ > 0.0) ? -nValue*nVector.nZ : nValue*nVector.nZ;
   return nRtVector;
};

/*--------------------- new func. optMaxSign() ------------------*/

/**
 * maxmal sign (version I)
 *
 * \code
 * SGrid <real> fVec2 = optMaxSign<real>(fVal,fVec1): vpsign(b,a)
 * \endcode
 */
template <class T> SGrid <T> optMaxSign(const T& nValue, const SGrid <T>& nVector)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = (nVector.nX < 0.0) ? -nValue*nVector.nX : nValue*nVector.nX;
   nRtVector.nY = (nVector.nY < 0.0) ? -nValue*nVector.nY : nValue*nVector.nY;
   nRtVector.nZ = (nVector.nZ < 0.0) ? -nValue*nVector.nZ : nValue*nVector.nZ;
   return nRtVector;
};

/**
 * maximal sign (version II)
 *
 * \code
 * SGrid <real> fVec2 = optMaxSign<real>(fVec1,fVal): vpsign2(b,a)
 * \endcode
 */
template <class T> SGrid <T> optMaxSign(const SGrid <T>& nVector, const T& nValue)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = (nVector.nX < 0.0) ? -nValue*nVector.nX : nValue*nVector.nX;
   nRtVector.nY = (nVector.nY < 0.0) ? -nValue*nVector.nY : nValue*nVector.nY;
   nRtVector.nZ = (nVector.nZ < 0.0) ? -nValue*nVector.nZ : nValue*nVector.nZ;
   return nRtVector;
};

/*--------------------- new func. optSubMin() -------------------*/

/**
 * \code
 * SGrid <real> fVec4 = optSubMin<real>(fVec1,fVec2,fVec3): vsubmin(a,b,c)
 * \endcode
 */
template <class T> SGrid <T> optSubMin(const SGrid <T>& nVector1, const SGrid <T>& nVector2, const SGrid <T>& nVector3)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = (nVector3.nX > 0.0) ? nVector2.nX : nVector1.nX;
   nRtVector.nY = (nVector3.nY > 0.0) ? nVector2.nY : nVector1.nY;
   nRtVector.nZ = (nVector3.nZ > 0.0) ? nVector2.nZ : nVector1.nZ;
   return nRtVector;  
};

/*--------------------- new func. optSubMax() -------------------*/

/**
 * \code
 * SGrid <real> fVec4 = optSubMax<real>(fVec1,fVec2,fVec3): vsubmax(a,b,c)
 * \endcode
 */
template <class T> SGrid <T> optSubMax(const SGrid <T>& nVector1, const SGrid <T>& nVector2, const SGrid <T>& nVector3)
{
   SGrid <T> nRtVector;
      
   nRtVector.nX = (nVector3.nX < 0.0) ? nVector2.nX : nVector1.nX;
   nRtVector.nY = (nVector3.nY < 0.0) ? nVector2.nY : nVector1.nY;
   nRtVector.nZ = (nVector3.nZ < 0.0) ? nVector2.nZ : nVector1.nZ;
   return nRtVector;  
};

/*----------------------- new func. optSum() --------------------*/

/**
 * sum of entries
 *
 * \code
 * real    fVal = optSum<real>(fVec1):  vsum(a);
 * integer iVal = optSum<integer>(iVec1): ivsum(a)
 * \endcode
 */
template <class T> T optSum(const SGrid <T>& nVector)
{
   T nRtVal;
      
   nRtVal = nVector.nX + nVector.nY + nVector.nZ;
   return nRtVal;
};

/*----------------------- new func. optComp() -------------------*/

/**
 * comparison of grid to a scalar
 *
 * \code
 * real    fVal1 = optComp<real>(fVec1,iVal1):  vcomp(a,b);
 * integer iVal2 = optComp<integer>(iVec1,iVal1): ivcomp(a,b)
 * \endcode
 */
template <class T> T optComp(const SGrid <T>& nVector, const int& nValue)
{
   switch(nValue)
   {
       case 1: return nVector.nX; 
       case 2: return nVector.nY; 
       case 3: return nVector.nZ; 
      default: return (T)0.0;
   }
};

/*--------------------- new func. optORLT() ---------------------*/

/**
 * grid or less than (version I)
 *
 * \code
 * bool bRtVal = optORLT<real>(fVec1,fVec2):     vorlt(a,b);
 * bool bRtVal = optORLT<integer>(iVec1,iVec2): ivorlt(a,b)
 * \endcode
 */
template <class T> bool optORLT(const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   bool bRtValue = false;
      
   if (nVector1.nX < nVector2.nX || nVector1.nY < nVector2.nY || nVector1.nZ < nVector2.nZ)
      bRtValue = true;
         
   return bRtValue;   
};

/**
 * grid or less than (version II)
 *
 * \code
 * bool bRtVal = optORLT<real>(fVec1,fVal):     vorlt2(a,b);
 * bool bRtVal = optORLT<integer>(iVec1,iVal): ivorlt2(a,b)
 * \endcode
 */
template <class T> bool optORLT(const SGrid <T>& nVector1, const T& nValue)
{
   bool bRtValue = false;
      
   if (nVector1.nX < nValue || nVector1.nY < nValue || nVector1.nZ < nValue) 
      bRtValue = true;
         
   return bRtValue;   
};

/*--------------------- new func. optANDLT() --------------------*/

/**
 * grid and less than (version I)
 *
 * \code
 * bool bRtVal = optANDLT<real>(fVec1,fVec2):     vandlt(a,b);
 * bool bRtVal = optANDLT<integer>(iVec1,iVec2): ivandlt(a,b)
 * \endcode
 */
template <class T> bool optANDLT(const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   bool bRtValue = false;
      
   if (nVector1.nX < nVector2.nX && nVector1.nY < nVector2.nY && nVector1.nZ < nVector2.nZ)
      bRtValue = true;
         
   return bRtValue;   
};

/**
 * grid and less than (version II)
 *
 * \code
 * bool bRtVal = optANDLT<real>(fVec1,fVal):     vandlt2(a,b);
 * bool bRtVal = optANDLT<integer>(iVec1,iVal): ivandlt2(a,b)
 * \endcode
 */
template <class T> bool optANDLT(const SGrid <T>& nVector1, const T& nValue)
{
   bool bRtValue = false;
      
   if (nVector1.nX < nValue && nVector1.nY < nValue && nVector1.nZ < nValue) 
      bRtValue = true;
         
   return bRtValue;   
 };

/*--------------------- new func. optORLE() ---------------------*/

/**
 * grid or less than or equal to (version I)
 *
 * \code
 * bool bRtVal = optORLE<real>(fVec1,fVec2):     vorle(a,b);
 * bool bRtVal = optORLE<integer>(iVec1,iVec2): ivorle(a,b)
 * \endcode
 */
template <class T> bool optORLE(const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   bool bRtValue = false;
      
   if (nVector1.nX <= nVector2.nX || nVector1.nY <= nVector2.nY || nVector1.nZ <= nVector2.nZ)
      bRtValue = true;
         
   return bRtValue;   
};

/**
 * grid or less than or equal to
 *
 * \code
 * bool bRtVal = optORLE<real>(fVec1,fVal):     vorle2(a,b);
 * bool bRtVal = optORLE<integer>(iVec1,iVal): ivorle2(a,b)
 * \endcode
 */
template <class T> bool optORLE(const SGrid <T>& nVector1, const T& nValue)
{
   bool bRtValue = false;
      
   if (nVector1.nX <= nValue || nVector1.nY <= nValue || nVector1.nZ <= nValue) 
      bRtValue = true;
         
   return bRtValue;   
};

/*--------------------- new func. optANDLE() --------------------*/

/**
 * grid and less than or equal to (version I)
 *
 * \code
 * bool bRtVal = optANDLE<real>(fVec1,fVec2):     vandle(a,b);
 * bool bRtVal = optANDLE<integer>(iVec1,iVec2): ivandle(a,b)
 * \endcode
 */
template <class T> bool optANDLE(const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   bool bRtValue = false;
      
   if (nVector1.nX <= nVector2.nX && nVector1.nY <= nVector2.nY && nVector1.nZ <= nVector2.nZ)
      bRtValue = true;
         
   return bRtValue;   
};

/**
 * grid and less than or equal to (version II)
 *
 * \code
 * bool bRtVal = optANDLE<real>(fVec1,fVal):     vandle2(a,b);
 * bool bRtVal = optANDLE<integer>(iVec1,iVal): ivandle2(a,b)
 * \endcode
 */
template <class T> bool optANDLE(const SGrid <T>& nVector1, const T& nValue)
{
   bool bRtValue = false;
      
   if (nVector1.nX <= nValue && nVector1.nY <= nValue && nVector1.nZ <= nValue) 
      bRtValue = true;
         
   return bRtValue;   
};

/*--------------------- new func. optORGT() ---------------------*/

/**
 * grid or greater than (version I)
 *
 * \code
 * bool bRtVal = optORGT<real>(fVec1,fVec2):     vorgt(a,b);
 * bool bRtVal = optORGT<integer>(iVec1,iVec2): ivorgt(a,b)
 * \endcode
 */
template <class T> bool optORGT(const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   bool bRtValue = false;
      
   if (nVector1.nX > nVector2.nX || nVector1.nY > nVector2.nY || nVector1.nZ > nVector2.nZ)
      bRtValue = true;
         
   return bRtValue;   
};

/**
 * grid or greater than (version II)
 *
 * \code
 * bool bRtVal = optORGT<real>(fVec1,fVal):     vorgt2(a,b);
 * bool bRtVal = optORGT<integer>(iVec1,iVal): ivorgt2(a,b)
 * \endcode
 */
template <class T> bool optORGT(const SGrid <T>& nVector1, const T& nValue)
{
   bool bRtValue = false;
      
   if (nVector1.nX > nValue || nVector1.nY > nValue || nVector1.nZ > nValue) 
      bRtValue = true;
         
   return bRtValue;   
};

/*--------------------- new func. optORGE() ---------------------*/

/**
 * grid or greater than or equal to (version I)
 *
 * \code
 * bool bRtVal = optORGE<real>(fVec1,fVec2):     vorge(a,b);
 * bool bRtVal = optORGE<integer>(iVec1,iVec2): ivorge(a,b)
 * \endcode
 */
template <class T> bool optORGE(const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   bool bRtValue = false;
      
   if (nVector1.nX >= nVector2.nX || nVector1.nY >= nVector2.nY ||
       nVector1.nZ >= nVector2.nZ) 
      bRtValue = true;
         
   return bRtValue;   
};

/**
 * grid or greater than or equal to (version II)
 *
 * \code
 * bool bRtVal = optORGE<real>(fVec1,fVal):     vorge2(a,b);
 * bool bRtVal = optORGE<integer>(iVec1,iVal): ivorge2(a,b)
 * \endcode
 */
template <class T> bool optORGE(const SGrid <T>& nVector1, const T& nValue)
{
   bool bRtValue = false;
      
   if (nVector1.nX >= nValue || nVector1.nY >= nValue || nVector1.nZ >= nValue) 
      bRtValue = true;
         
   return bRtValue;   
};

/*--------------------- new func. optANDGT() --------------------*/

/**
 * grid and greater than (version I)
 *
 * \code
 * bool bRtVal = optANDGT<real>(fVec1,fVec2):     vandgt(a,b);
 * bool bRtVal = optANDGT<integer>(iVec1,iVec2): ivandgt(a,b)
 * \endcode
 */
template <class T> bool optANDGT(const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   bool bRtValue = false;
      
   if (nVector1.nX > nVector2.nX && nVector1.nY > nVector2.nY && nVector1.nZ > nVector2.nZ)
      bRtValue = true;
         
   return bRtValue;   
};

/**
 * grid and greater than (version II)
 *
 * \code
 * bool bRtVal = optANDGT<real>(fVec1,fVal):     vandgt2(a,b);
 * bool bRtVal = optANDGT<integer>(iVec1,iVal): ivandgt2(a,b)
 * \endcode
 */
template <class T> bool optANDGT(const SGrid <T>& nVector1, const T& nValue)
{
   bool bRtValue = false;
      
   if (nVector1.nX > nValue && nVector1.nY > nValue && nVector1.nZ > nValue) 
      bRtValue = true;
         
   return bRtValue;   
};

/*--------------------- new func. optANDGE() --------------------*/

/**
 * grid and greater than or equal to (version I)
 *
 * \code
 * bool bRtVal = optANDGE<real>(fVec1,fVec2):     vandge(a,b);
 * bool bRtVal = optANDGE<integer>(iVec1,iVec2): ivandge(a,b)
 * \endcode
 */
template <class T> bool optANDGE(const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   bool bRtValue = false;
      
   if (nVector1.nX >= nVector2.nX && nVector1.nY >= nVector2.nY && nVector1.nZ >= nVector2.nZ)
      bRtValue = true;
         
   return bRtValue;   
};

/**
 * grid and greater than or equal to (version II)
 *
 * \code
 * bool bRtVal = optANDGE<real>(fVec1,fVal):     vandge2(a,b);
 * bool bRtVal = optANDGE<integer>(iVec1,iVal): ivandge2(a,b)
 * \endcode
 */
template <class T> bool optANDGE(const SGrid <T>& nVector1, const T& nValue)
{
   bool bRtValue = false;
      
   if (nVector1.nX >= nValue && nVector1.nY >= nValue && nVector1.nZ >= nValue) 
      bRtValue = true;
         
   return bRtValue;   
};

/*--------------------- overlaod operator != --------------------*/

/**
 * grid not equal to (version I)
 *
 * \code
 * bool bRtVal = (fVec != fVal):  vorne(a,b);
 * bool bRtVal = (iVec != iVal): ivorne(a,b)
 * \endcode
 */
template <class T> bool operator!=(const SGrid <T>& nVector1, const T& nValue)
{
   bool bRtValue = false;
      
   if (nVector1.nX != nValue || nVector1.nY != nValue || nVector1.nZ != nValue) 
      bRtValue = true; 
         
   return bRtValue;   
};

/**
 * grid not equal to (version II)
 *
 * \code
 * bool bRtVal = (fVec1 != fVec2):  vorne2(a,b);
 * bool bRtVal = (iVec1 != iVec2): ivorne2(a,b)
 * \endcode
 */
template <class T> bool operator!=(const SGrid <T>& nVector1, const SGrid <T>& nVector2)
{
   bool bRtValue = false;
      
   if (nVector1.nX != nVector2.nX || nVector1.nY != nVector2.nY || nVector1.nZ != nVector2.nZ)
      bRtValue = true; 
         
   return bRtValue;   
};

