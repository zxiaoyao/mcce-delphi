#ifndef IO_EXCEPTIONS_H
#define IO_EXCEPTIONS_H

#include "../interface/exceptions.h"

class CUnknownIOFile : public CException
{
   public:
      CUnknownIOFile(const string & strFileName)
      {
         cerr << "ERROR OCCURS WHILE READING IO FILE " << strFileName << " : FILE DOES NOT EXIST" << endl;
      }
};

class CUnknownForceFileHeader : public CException
{
   public:
      CUnknownForceFileHeader(const string & strFile, const string & strHeader)
      {
         cerr << "UNKNOWN HEADER IN FILE " << strFile << " : " << strHeader << endl;
         cerr << "\t VALID HEADER FOR SIZE FILE IS \'atom__res_radius\' OR \'atom__resnumbc_radius_\'" << endl;
         cerr << "\t VALID HEADER FOR CHARGE FILE IS \'atom__res_radius\' OR \'atom__resnumbc_radius_\'" << endl;
      }
};

class CUnknownDelphiPdb : public CException
{
   public:
      CUnknownDelphiPdb(const string & strFile)
      {
         cerr << "THE FILE " << strFile << " IS NOT A DELPHI PDB FILE! " << endl;
         cerr << "\t CHECK THE FILE TYPE! " << endl;           
      }
};

class CUnknownUnformattedPdb : public CException
{
   public:
      CUnknownUnformattedPdb(const string & strFile)
      {
         cerr << "ERROR OCCURS WHEN READING THE UNFORMATTED PDB FILE " << strFile << endl;
         cerr << "\t CHECK THE FILE AND TRY AGAIN! " << endl;           
      }
};

class CUnknownModPdb : public CException
{
   public:
      CUnknownModPdb(const string & strFile, const int & iFormatID)
      {
         cerr << "THE FORMAT ID " << iFormatID << " SPECIFIED IN THE MOD PDB FILE " << strFile << " IS NO LONG SUPPORTED." << endl;
         cerr << "\t CURRENT SUPPORTED ID = 1, 4 FOR MOD PDB FILE" << endl;           
      }
};

class CUnsupportedCRGDST : public CException
{
   public:
      CUnsupportedCRGDST(const string & strLine)
      {
         cerr << "THE INPUT PDB FILE CONTAINS A LINE \"" << strLine << "\" WITH KEYWORD \"crgdst\" WHICH IS NO LONGER SUPPORTED " << endl;
         cerr << "\t PLEASE UPDATE THE PDB FILE AND TRY AGAIN..." << endl;           
      }
};

class CUnknownRadius : public CException
{
   public:
      CUnknownRadius(const string & strLine)
      {
         cerr << "NO RADIUS RECORD FOUND FOR \"" << strLine << "\" " << endl;
         cerr << "\t PLEASE CHECK THE .siz FILE AND RETRY..." << endl;
      }
};

class CNoAtomObjectData : public CException
{
   public:
      CNoAtomObjectData()
      {
         cerr << "# OF ATOMS = 0 AND # OF OBJECTS = 0" << endl;
         cerr << "\t EXITING DUE T NON-EXISTENCE OF ATOM FILE NOR OBJECT DATA" << endl;
      }
};

class CZeroHeavyAtomRadius : public CWarning
{
   public:
      CZeroHeavyAtomRadius(const string & strLine)
      {
         cerr << "RADIUS OF HEAVEY ATOM IN \"" << strLine << "\" IS SET TO ZERO"<< endl;
      }
};

class CUnknownCharge : public CWarning
{
   public:
      CUnknownCharge(const string & strLine)
      {
         cerr << "NO CHARGE RECORD FOUND FOR \"" << strLine << "\" (CHARGE IS SET = 0)" << endl;
      }
};

class CNonZeroNetCrg : public CWarning
{
   public:
      CNonZeroNetCrg(const string & strResidue, const string & strResidueNum, const real & fNetCharge)
      {
         cerr << "\"" << strResidue << strResidueNum << "\" HAS A NET CHARGE OF " << fNetCharge << endl;
      }
};

class CEmptyAtomsInFile : public CWarning
{
   public:
      CEmptyAtomsInFile(const string & strFile)
      {
         cerr << "EMPTY ATOMS FOR MIDPOINT DETERMINATION IN FILE "  << strFile << " (ASSUMING ZERO OFFSETS)" << endl;
      }	   
};	   

#endif // IO_EXCEPTIONS_H
