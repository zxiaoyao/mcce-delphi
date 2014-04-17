/**
 * Globally defined enviromental varibales.
 */

#define MX  // MX -- double      &      int [most cases]
            // SP -- float       &      int [small/short runs]
            // DP -- double      & long int [large/long runs] 
            // LD -- long double & long int [extreme cases,rarely used]

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

//-----------------------------------------------------------------------//

#define VERBOSE   // flag for removing part of standard output

#define DEVELOPER // flag to control the precision of outputs between developers and users
                  
//#define DEBUG_IO_SIZE            // debug reading size file
//#define DEBUG_IO_CHARGE          // debug reading charge file
//#define DEBUG_IO_PDB             // debug reading PDB file
//#define DEBUG_DATAMARSHAL        // debug datamarshal class
//#define DEBUG_DELPHI_MAP         // debug delphi_data class
#ifdef DEBUG_IO_SIZE
#define DEBUG_IO_FORCE
#endif

#ifdef DEBUG_IO_CHARGE
#define DEBUG_IO_FORCE
#endif

//#define DEBUG_DELPHI_SPACE

//#define DEBUG_DELPHI_SOLVER        // debug delphi_fastSOR class


#ifdef DEBUG_DELPHI_SOLVER
//#define DEBUG_DELPHI_SOLVER_MKDBSF1
#define DEBUG_DELPHI_SOLVER_MKDBSF
#define DEBUG_DELPHI_SOLVER_ITIT
#define DEBUG_DELPHI_SOLVER_RELFAC
#define DEBUG_DELPHI_SOLVER_SETBC
#define DEBUG_DELPHI_SOLVER_SETCRG
#endif


//#define DEBUG_DELPHI_ENERGY        // debug CDelphiEnergy class

//#define DEBUG_DELPHI_SITE




