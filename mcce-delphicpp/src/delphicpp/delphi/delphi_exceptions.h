#ifndef DELPHI_EXCEPTIONS_H
#define DELPHI_EXCEPTIONS_H

#include "../interface/exceptions.h"

//---------------- define delphi-used exception classes -----------------//
class CZeroGrid : public CException 
{
   public:
      CZeroGrid(const integer & iGrid)
      {
         cerr << "ERROR OCCURS DUE TO \"GRID = " << iGrid << "\" AFTER READING THE PARAMETER FILE. " << endl;
         cerr << "\t TWO OF THE PARAMTERS (GSIZE, SCALE AND PERFIL) MUST BE SPECIFIED IN THE PARAMETER FILE." << endl;
      }
};

class CInvalidEpsInMedium : public CException 
{
   public:
      CInvalidEpsInMedium(const integer & iMedium)
      {
         cerr << "ERROR OCCURS DUE TO DIELECTRIC IN MEDIUM NUMBER " << iMedium << "\" < 1.0 " << endl;
         cerr << "\t DELPHI IS NOT ABLE TO DEAL WITH EPS < 1.0. THEREFORE EXITING... " << endl;
      }
};

class CIsAnObjectType : public CException 
{
   public:
      CIsAnObjectType(const string & strObject)
      {
         cerr << "OBJECT TYPES (SPHERE, CYLINDER, CONE AND BOX) ARE NO LONG SUPPORTED IN DELPHI C++" << endl;
         cerr << "\t USE ProNOI TO GENERATE ATOMIC STYLE OBJECTS INSTEAD AND TRY AGAIN... " << endl;
      }
};

class CNoAtomsInMolecule : public CException 
{
   public:
      CNoAtomsInMolecule(const integer & iObject)
      {
         cerr << "OBJECT " << iObject << " IS A MOLECULE WITH NO ATOMS (TOTAL ATOM NUMBER = 0)" << endl;
         cerr << "\t CHECK THE INPUT FILES AND TRY AGAIN... " << endl;
      }
};

class CNoBndyAndDielec : public CException 
{
   public:
      CNoBndyAndDielec(shared_ptr<CTimer> pTimer)
      {
         cerr << "EXITING AS NO BOUNDARY ELEMENTS AND UNIFORM DIELECTRIC EXIT FLAG HAS BEEN SET" << endl;
         pTimer->exit();
      }
};


class CBadStatementAssignment : public CWarning
{
   public:
      CBadStatementAssignment(const string & strArgument, const string & strStatement)
      {
         cerr << "WRONG STATEMENT ASSIGNMENT \"" << strStatement << " = " << strArgument << "\" : CANNOT ASSIGN TRUE OR FALSE ";
         cerr << "(DEFAULT VALUE OF \"" << strStatement << "\" IS USED)" << endl;
      }	   
};
	   
class CNoEnoughIterations : public CWarning
{
   public:
      CNoEnoughIterations(int & iIterationNum)
      {
         cerr << "REQUIRES AT LEAST 30 NONLINEAR ITERATIONS (RESET TO 30 ITERATIONS)" << endl;
         
         iIterationNum = 30;
      }
};

class CInUnknownSizeFormat : public CWarning
{
   public:
      CInUnknownSizeFormat(const string & strFormat)
      {
         cerr << "REDUNDANT READ-IN SIZE (RADII) FILE FORMAT \"" << strFormat << "\" IS SPECIFIED ";
         cerr << "(FORMAT IS DETERMINED BY THE HEADER OF READ-IN SIZE FILE)" << endl;
      }	   
}; 

class CInUnknownCrgFormat : public CWarning
{
   public:
      CInUnknownCrgFormat(const string & strFormat)
      {
         cerr << "REDUNDANT READ-IN CHARGE FILE FORMAT \"" << strFormat << "\" IS SPECIFIED ";
         cerr << "(FORMAT IS DETERMINED BY THE HEADER OF READ-IN CHARGE FILE)" << endl;
      }	   
}; 
	   
class CInUnknownPDBFormat : public CWarning
{
   public:
      CInUnknownPDBFormat(const string & strFormat)
      {
         cerr << "UNKNOWN READ-IN PDB FILE FORMAT " << strFormat << " (DEFAULT PDB FILE FORMAT IS USED)" << endl;
      }	   
}; 
	   
class CInUnknownFRCFormat : public CWarning
{
   public:
      CInUnknownFRCFormat(const string & strFormat)
      {
         cerr << "UNKNOWN READ-IN FRC FILE FORMAT " << strFormat << " (DEFAULT FRC FILE FORMAT IS USED)" << endl;
      }	   
}; 	   
	   
class COutUnknownFRCFormat : public CWarning
{
   public:
      COutUnknownFRCFormat(const string & strFormat)
      {
         cerr << "UNKNOWN WRITE-OUT FRC FILE FORMAT " << strFormat << " (DEFAULT FRC FILE FORMAT IS USED)" << endl;
      }	   
};

class CInUnknownPHIFormat : public CWarning
{
   public:
      CInUnknownPHIFormat(const string & strFormat)
      {
         cerr << "UNKNOWN READ-IN PHIMAP FILE FORMAT " << strFormat << " (DEFAULT PHIMAP FILE FORMAT IS USED)" << endl;
      }	   
}; 
	   
class COutUnknownPHIFormat : public CWarning
{
   public:
      COutUnknownPHIFormat(const string & strFormat)
      {
         cerr << "UNKNOWN WRITE-OUT PHIMAP FILE FORMAT " << strFormat << " (DEFAULT PHIMAP FILE FORMAT IS USED)" << endl;
      }	   
}; 

class COutUnknownEPSFormat : public CWarning
{
   public:
      COutUnknownEPSFormat(const string & strFormat)
      {
         cerr << "UNKNOWN WRITE-OUT EPS FILE FORMAT " << strFormat << " (DEFAULT EPS FILE FORMAT IS USED)" << endl;
	   }	   
}; 	   

class COutUnknownMODPDBFormat : public CWarning
{
   public:
      COutUnknownMODPDBFormat(const string & strFormat)
      {
         cerr << "UNKNOWN WRITE-OUT MODIFIED PDB FILE FORMAT" << strFormat << " (DEFAULT MODIFIED PDB FILE FORMAT IS USED)" << endl;
      }
}; 
	   
class COutUnknownUNPDBFormat : public CWarning
{
   public:
      COutUnknownUNPDBFormat(const string & strFormat)
      {
         cerr << "UNKNOWN WRITE-OUT UNFORMATTED PDB FILE FORMAT " << strFormat << " (DEFAULT UNFORMATTED PDB FILE FORMAT IS USED)" << endl;
	   }	   
};
	   
class COutUnknownUNFRCFormat : public CWarning
{
   public:
      COutUnknownUNFRCFormat(const string & strFormat)
      {
         cerr << "UNKNOWN WRITE-OUT UNFORMATTED FRC FILE FORMAT " << strFormat << " (DEFAULT UNFORMATTED FRC FILE FORMAT IS USED)" << endl;
	   }	   
};	   
	   
class COutUnknownEnergyFormat : public CWarning
{
   public:
      COutUnknownEnergyFormat(const string & strFormat)
      {
         cerr << "UNKNOWN WRITE-OUT UNFORMATTED ENERGY FORMAT " << strFormat << " (DEFAULT UNFORMATTED ENERGY FORMAT IS USED)" << endl;
	   }	   
};	 	   
	    	   
class COutOBSOLETEPDBAFormat : public CWarning
{
   public:
      COutOBSOLETEPDBAFormat(const string & strFormat)
      {
         cerr << "WRITE-OUT OPTION " << strFormat << " NO LONGER SUPPORTED!" << " (DEFAULT SCRG FORMAT IS USED)" << endl;
      }	   
};	 	   

class COutUnknownSurfCrgFormat : public CWarning
{
   public:
      COutUnknownSurfCrgFormat(const string & strFormat)
      {
         cerr << "UNKNOWN WRITE-OUT SURFACE CHARGE FORMAT" << strFormat << " (DEFAULT SURFACE CHARGE FORMAT IS USED)" << endl;
      }	   
};

class CUnknownFunction : public CWarning
{
   public:
      CUnknownFunction(const string & strFuncName)
      {
         cerr << " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << endl;
         cerr << " The function specifier   " << strFuncName << " is" << endl;
         cerr << " not recognised. Therefore the function will not be processed " << endl;
         cerr << " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << endl;
	   }	   
};
	
class CMinusDielec : public CWarning
{
   public:
      CMinusDielec(const real & fExDielec, const real & fInDielec)
      {
         cerr << "NEGATIVE DIELECTRIC CONSTANT(S): OUT = " << fExDielec << ", IN = " << fInDielec;
         cerr << " (RESET TO BE THEIR ABSOLUTE VALUE(S))" << endl;
	   }
};

class CToUnformattedFile : public CWarning
{
   public:
      CToUnformattedFile(const string & strFile, const string & strASCI)
      {
         cerr << "MORE THAN 10 CHARACTERS OUT OF THE FIRST 80 CHARACTERS IN THE FILE " << strFile << " ARE NOT IN THE LIST OF ASCI \n"
              << "<" << strASCI << "> (RESET THE PDB FILE FORMAT TO BE \"UNFORMATTED\")" << endl;
      }	   
};

class CSystemOutsideBox : public CWarning
{
   public:
      CSystemOutsideBox()
      {
         cerr << "PART OF SYSTEM OUTSIDE THE BOX!" << endl;
      }	   
};

class CReadWriteUnformatPdb : public CWarning
{
   public:
      CReadWriteUnformatPdb(bool & bOutPdbFormat)
      {
         cerr << "CANNOT WRITE AN UNFORMATTED PDB FILE, WHILE READING IN AN UNFORMATTED PDB FILE (THE WRITE OPTION IS DISABLED)" << endl;
         
         bOutPdbFormat = false;
      }	   
};

class CReadWriteUnformatFrc : public CWarning
{
   public:
      CReadWriteUnformatFrc(bool & bOutFrcFormat)
      {
         cerr << "CANNOT WRITE AN UNFORMATTED FRC FILE, WHILE READING IN AN UNFORMATTED PDB FILE (WRITE OPTION IS DISABLED)" << endl;
         
         bOutFrcFormat = false;  
      }	   
};

#endif // DELPHI_EXCEPTIONS_H
