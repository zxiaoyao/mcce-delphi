#ifndef CIO_H
#define CIO_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>   // std::string
#include <vector>   // std::vector
#include <locale>
#include <stdlib.h> // atof
#include <cmath>

#include "../interface/environment.h"
#include "../misc/misc_grid.h"
#include "io_datatype.h"
#include "io_exceptions.h"

using namespace std;

const int SIZEFILE   = 1;
const int CHARGEFILE = 2;

const int STDPDB     = 10;
const int MODPDB     = 20;
const int PQRPDB     = 21;
const int MOD4PDB    = 30;
const int PQR4PDB    = 31;

class CIO
{
   protected:
      const real fDielec;                // repsin
      const real fEPKT;                  // epkt

      /*
       * miscellany
       */
      string toUpperCase(const string& strLine);

      string removeSpace(const string& strLine);

      bool checkFileFormat(const string& strFile);
                 
      /*
       * for reading atom force (radii/size and charge) file
       * these static attributes are declared here and defined in io_force.cpp
       */
      static integer iRadiusNum;   // nrmax (# of entries in radius file)
      static vector<CForce> prgas; // radii(:)
      static integer iCrgNum;      // nchrec (# of entries in charge file)
      static vector<CForce> prgac; // charge(:)
              
      void readFileInNotPKFormat(ifstream& ifFileStream, const int& iFileType);

      void readFileInPKFormat(ifstream& ifFileStream, const int& iFileType);

#ifdef DEBUG_IO_FORCE
      void printForce(const int& iFileType, const vector<CForce>& prgaf);
#endif

      integer FindRecordIndex(const string& strAtom,const string& strResidue,const string& strResidueNum,const string& strChain,
                              const integer& iRecordNum,vector<CForce>* prgaf);

      integer FindRecord(const string& strAtom,const string& strResidue,const string& strResidueNum,const string& strChain,
                         const int& iFileType, real& fValue);

      //void checkCharge(const bool& bSurfCrgInSite);

      /*
       * for reading PDB file
       */
      integer iObjectMediaNum;  // imedianumb

      void readStdPdbFile(ifstream& ifPdbFileStream);
                          
      void readModFile1(ifstream& ifPdbFileStream);
                        
      void readModFile4(ifstream& ifPdbFileStream);
                        
      void readPqrFile(ifstream& ifPdbFileStream);
                       
      void readMod4File(ifstream& ifPdbFileStream);
                        
      void readPqr4File(ifstream& ifPdbFileStream);
          
      void readUnformattedPdb(const string& strPdbFile,ifstream& ifPdbFileStream,bool& bPostProcess);
                              
#ifdef DEBUG_IO_PDB
      void printPDB();                        
#endif
           
      bool    bExistRadiiInfo;           // iatrad
                                         // whether there is radius info
      vector<integer> prgiObjectMediaNum;// tmpiatmmed(nobjectmax)
                                         // vector containing internal media-number per object

   public:     
      integer    iMediaNum;              // nmedia
                                         // # of media
      integer    iObjectNum;             // nobject
                                         // # of objects
      integer    iAtomNum;               // natom
                                         // # of atoms
      integer    iResidueNum;            // resnummax
                                         // maximum residue number
      bool       bOnlyMolecule;          // ionlymol
                                         // true if there are only molecules in the system (no objects)

      vector<CAtomPdb> vctapAtomPdb;     // delphipdb(Natom)
                                         // array of structure to store info read from pdb file
      vector<real>    vctfMediaEps;      // medeps(0:nmediamax)
                                         // vector containing correspondence media<->epsilon/epkt
      vector<string>  vctstrObject;      // dataobject(nobjectmax,2)
                                         // vector containing string with object data, and pre-elab data
                                         // changed it to vctstrObject(2*nobjectmax)
      vector<integer> vctiAtomMediaNum;  // iatmmed(Natom+Nobjectmax)
                                         // vector containing internal media-number per atom and object

      CIO():fDielec(4.0),fEPKT(167100.9162872952/297.3342119)
      {     
#ifdef DEBUG_OBJECT
         cout << endl;
         cout << "****************************************************************\n";
         cout << "*                     CIO is constructed                       *\n";
         cout << "****************************************************************\n";
#endif

         //iRadiusNum      = 0;
         //iCrgNum         = 0;
         iMediaNum       = 1;
         iObjectNum      = 1;  
         iAtomNum        = 0;
         iObjectMediaNum = 1;
         bOnlyMolecule   = true;
         bExistRadiiInfo = false;
         iResidueNum     = 0;        
      };

      CIO(real fDielecIn,real fEPKTIn):fDielec(fDielecIn),fEPKT(fEPKTIn)
      {
#ifdef DEBUG_OBJECT
         cout << endl;
         cout << "****************************************************************\n";
         cout << "*                     CIO is constructed                       *\n";
         cout << "****************************************************************\n";
#endif

         //iRadiusNum      = 0;
         //iCrgNum         = 0;
         iMediaNum       = 1;
         iObjectNum      = 1;  
         iAtomNum        = 0;
         iObjectMediaNum = 1;
         bOnlyMolecule   = true;
         bExistRadiiInfo = false;
         iResidueNum     = 0;        
      };
      
      /**
       * destructor
       */
      ~CIO()
      {
#ifdef DEBUG_OBJECT
         cout << endl;
         cout << "****************************************************************\n";
         cout << "*                      CIO is destroyed                        *\n";
         cout << "****************************************************************\n";
#endif
      };


      /*
       * for reading atom force (radii/size and charge) file
       */
      void readForceFile(const string& strFile);

      /*
       * for reading/writing PDB file
       */
      void readPdbFile(const string& strPdbFile,const int& iPdbFormat,const bool& bPdbUnformat);
                       
      void writeUnformatPdb(const string& strPdbFile);

      void writeModifiedPdb(const string& strPdbFile,const int& iModPdbFormatOut);
                       
      /*
       * miscellany
       */

      // set DelPhi-style atom list vctapAtomPdb(iAtomNum), i.e, (delphipdb(natom))
      void setDelphiAtom(const bool& bSolvePB,const bool& bSurfCrgInSite,const string& strSizeFile,const string& strCrgFile,
                         const string& strPdbFile,const int& iPdbFormat,const bool& bPdbUnformat);
                                                 
      /*
       * for reading/writing FRC file
       */
      SGrid<real> readFrcFile(const string& strFrcFile,const SGrid<real>& fgOffCenter,const real& fScale);

      //---------- for writing EPS file
      void writeEpsMap(const integer& iAtomNumIn,const integer& iObjectNumIn,const integer& iGrid,const real& fScale,
                       const SGrid<real>& fgBoxCenter,const vector< SGrid<integer> >& vctigEpsMap,const vector<bool>& vctbDielecMap,
                       const string& strEpsFile);
      
      /*
       * for reading/writing PHI file
       */

      /*
       *for writing ENERGY file
       */

      /*
       * for writing HSURF2 file
       */

      /*
       *for writing SURFEN file
       */

      /*
       * for writing SCRG file
       */

};

#endif // CIO_H
