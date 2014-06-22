/**
 * @file environment.h
 * @brief pre-processor marco's used for compiling the code
 *
 * @author Chuan Li, chuanli@clemson.edu
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

/**
 * preprocessor marco to choose data types for real and integer numbers \n
 * - MX -- double      &      int [mixed double/single precision, mostly used]
 * - SP -- float       &      int [single precision]
 * - DP -- double      & long int [double precision]
 * - LD -- long double & long int [extreme case,rarely used]
 */
#define MX

/**
 * flag for additional outputs at run time
 */
#define VERBOSE

/**
 * flag to control the precision of output numbers
 */
#define DEVELOPER

/**
 * flag to embed delphicpp in mcce
 */
#define MCCE

/**
 * Introduce namespace "delphi" here and used in getFunction and getStatement to avoid ambiguous reference
 * to data type "real" when compiling the code in Mac system
 */

namespace delphi
{
#ifdef SP
typedef int   integer;
typedef float real;
#endif

#ifdef MX
typedef int    integer;
typedef double real;
#endif

#ifdef DP
typedef long int integer;
typedef double   real;
#endif

#ifdef LD
typedef long int    integer;
typedef long double real;
#endif

/**
 * flag to debug the function(s) of reading SIZE file
 */
//#define DEBUG_IO_SIZE

#ifdef DEBUG_IO_SIZE
#define DEBUG_IO_FORCE
#endif

/**
 * flag to debug the function(s) of reading CHARGE file
 */
//#define DEBUG_IO_CHARGE

#ifdef DEBUG_IO_CHARGE
#define DEBUG_IO_FORCE
#endif

/**
 * flag to debug the function(s) of reading PDB file
 */
//#define DEBUG_IO_PDB

/**
 * flag to debug the function(s) of IDataMarshal class
 */
//#define DEBUG_DATAMARSHAL

/**
 * flag to debug the function(s) of CDelphiData class
 */
//#define DEBUG_DELPHI_MAP

/**
 * flag to debug the function(s) of CSpace class
 */
//#define DEBUG_DELPHI_SPACE

/**
 * flag to debug the function(s) of CDelphiFastSOR class
 */
//#define DEBUG_DELPHI_SOLVER

#ifdef DEBUG_DELPHI_SOLVER
#define DEBUG_DELPHI_SOLVER_MKDBSF1
#define DEBUG_DELPHI_SOLVER_MKDBSF
#define DEBUG_DELPHI_SOLVER_ITIT
#define DEBUG_DELPHI_SOLVER_RELFAC
#define DEBUG_DELPHI_SOLVER_SETBC
#define DEBUG_DELPHI_SOLVER_SETCRG
#endif

/**
 * flag to debug the function(s) of CDelphiEnergy class
 */
//#define DEBUG_DELPHI_ENERGY

/**
 * flag to debug the function(s) of CSite class
 */
//#define DEBUG_DELPHI_SITE

/**
 * flag to debug calling delphicpp in mcce
 */
//#define DEBUG_MCCE

/**
 * flag to debug constructing/destroying objects
 */
#define DEBUG_OBJECT

}

using namespace delphi;

#endif //ENVIRONMENT_H_
