#ifndef GRID_H
#define GRID_H

#include <iostream>

#include "../interface/environment.h"

using namespace std;
   

// New generic variable types for grid positions and value
// SGrid <real>   : coord 
// SGrid <integer>: int_coord
template <class T>  struct SGrid
{
   T nX,nY,nZ;
};

// SGridValue <real>    - grid_value 
// SGridValue <integer> - int_grid_value
template <class T> struct SGridValue
{
   SGrid <T> nGrid;
   T nValue;
};   
   
template <class T> struct SExtrema
{
   SGrid <T> nMin,nMax;
};

struct SDoubleGridValue
{
   SGrid<real> fgCoord;
   real fVal1;
   real fVal2;
};


/*------------------- newly defined operators on grids ------------------*/

// overload operator <<
template <class T> extern ostream& operator<<(ostream &, SGrid<T> &);
template <class T> extern ostream& operator<<(ostream &, SGridValue<T> &);
template <class T> extern ostream& operator<<(ostream &, SExtrema<T> &);

// overload operator +
template <class T> extern SGrid <T> operator+(const SGrid <T> &, const SGrid <T> &);
template <class T> extern SGrid <T> operator+(const SGrid <T> &, const T &);
template <class T> extern SGrid <T> operator+(const T &, const SGrid <T> &);

// overload operator -
template <class T> extern SGrid <T> operator-(const SGrid <T> &, const SGrid <T> &);
template <class T> extern SGrid <T> operator-(const SGrid <T> &, const T &);
template <class T> extern SGrid <T> operator-(const T &, const SGrid <T> &);
template <class T> extern SGrid <T> operator-(const SGrid <T> &);
   
// overload operator *
template <class T> extern SGrid <T> operator*(const SGrid <T> &, const SGrid <T> &);
template <class T> extern SGrid <T> operator*(const SGrid <T> &, const T &);
template <class T> extern SGrid <T> operator*(const T &, const SGrid <T> &);
   
// overload operator /
template <class T, class N> extern SGrid <T> operator/(const SGrid <N> &, const T &);   
   
// new operator: dot product
template <class T> extern T optDot(const SGrid <T> &, const SGrid <T> &);   
   
// new operator: cross product
template <class T> extern SGrid <T> optCross(const SGrid <T> &, const SGrid <T> &); 
   
// new math func. optSQRT()
extern SGrid <real> optSQRT(const SGrid <real> &);
   
// new math func. optABS()
template <class T> extern SGrid <T> optABS(const SGrid <T> &);
         
// convert one type to another
template <class T, class N> extern SGrid <T> optCast(const SGrid <N> &);
   
// round to the nearest integer
extern SGrid <integer> optRound(const SGrid <real> &);
 
// new math func. optMin() 
template <class T> extern SGrid <T> optMin(const T &, const SGrid <T> &);
template <class T> extern SGrid <T> optMin(const SGrid <T> &, const T &);   
template <class T> extern SGrid <T> optMin(const SGrid <T> &, const SGrid <T> &);   
template <class T> extern T optMin(const SGrid <T> &);
   
// new math func. optMax()
template <class T> extern SGrid <T> optMax(const T &, const SGrid <T> &);
template <class T> extern SGrid <T> optMax(const SGrid <T> &, const T &);
template <class T> extern SGrid <T> optMax(const SGrid <T> &, const SGrid <T> &);
template <class T> extern T optMax(const SGrid <T> &);

// new func. optMinSign()
template <class T> extern SGrid <T> optMinSign(const T &, const SGrid <T> &);
template <class T> extern SGrid <T> optMinSign(const SGrid <T> &, const T &);

// new func. optMaxSign()
template <class T> extern SGrid <T> optMaxSign(const T &, const SGrid <T> &);
template <class T> extern SGrid <T> optMaxSign(const SGrid <T> &, const T &);
  
// new func. optSubMin()  
template <class T> extern SGrid <T> optSubMin(const SGrid <T> &, const SGrid <T> &, const SGrid <T> &);
   
// new func. optSubMax()
template <class T> extern SGrid <T> optSubMax(const SGrid <T> &, const SGrid <T> &, const SGrid <T> &);

// new func. optSum()
template <class T> extern T optSum(const SGrid <T> &);

// new func. optComp()
template <class T> extern T optComp(const SGrid <T> &, const int &);

// new func. optORLT()
template <class T> extern bool optORLT(const SGrid <T> &, const SGrid <T> &);
template <class T> extern bool optORLT(const SGrid <T> &, const T &);
   
// new func. optANDLT()
template <class T> extern bool optANDLT(const SGrid <T> &, const SGrid <T> &);  
template <class T> extern bool optANDLT(const SGrid <T> &, const T &);   
   
// new func. optORLE()  
template <class T> extern bool optORLE(const SGrid <T> &, const SGrid <T> &);
template <class T> extern bool optORLE(const SGrid <T> &, const T &);
  
// new func. optANDLE()  
template <class T> extern bool optANDLE(const SGrid <T> &, const SGrid <T> &);
template <class T> extern bool optANDLE(const SGrid <T> &, const T &);   
   
// new func. optORGT()  
template <class T> extern bool optORGT(const SGrid <T> &, const SGrid <T> &);   
template <class T> extern bool optORGT(const SGrid <T> &, const T &);   
   
// new func. optORGE()  
template <class T> extern bool optORGE(const SGrid <T> &, const SGrid <T> &);   
template <class T> extern bool optORGE(const SGrid <T> &, const T &);   
   
// new func. optANDGT()
template <class T> extern bool optANDGT(const SGrid <T> &, const SGrid <T> &);
template <class T> extern bool optANDGT(const SGrid <T> &, const T &);   
   
// new func. optANDGE()  
template <class T> extern bool optANDGE(const SGrid <T> &, const SGrid <T> &); 
template <class T> extern bool optANDGE(const SGrid <T> &, const T &);   
   
// overlaod logical operator !=  
template <class T> extern bool operator!=(const SGrid <T> &, const T &);   
template <class T> extern bool operator!=(const SGrid <T> &, const SGrid <T> &);
    

#endif // GRID_H

