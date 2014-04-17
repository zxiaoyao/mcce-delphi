#ifndef INTERFACE_EXCEPTIONS_H
#define INTERFACE_EXCEPTIONS_H

#include "exceptions.h"
	   
class CInexistentKey : public CException
{
   public:
	   CInexistentKey(const string & strKey)
	   {
	      cerr << "KEY " << strKey << " DOES NOT EXIST" << endl;   
	   }
};

class CUnknownFile : public CException
{
   public:
	CUnknownFile(const string & strFileName)
	{
	   cerr << "ERROR OCCURS WHILE READING " << strFileName << " FILE : FILE DOES NOT EXIST" << endl;
	}
};

class CUnmatchSize : public CException
{
   public:
   CUnmatchSize(const string & strFileName)
   {
      cerr << "ERROR OCCURS WHILE CONVERTING THE VECTOR " << strFileName << " TO MULTI-DIMENSIONAL ARRAY : THE SPECIFIED DIMESION DOES NOT MATCH" << endl;
   }
};

class CUnknownLine : public CWarning
{
   public:
	   CUnknownLine(const string & strFileName, const string & strLine)
	   {
	      cerr << "UNKNOWN LINE \"" << strLine << "\" IN FILE " << strFileName << "(SKIP THIS LINE...)" << endl;
	   }
};


class CNoBiomodel : public CWarning
{
   public:
      CNoBiomodel(const string & strBiomodel, const string & strSolver)
      {
         cerr << "UNDEFINED DBIOMODEL OR SOLVER (USING DEFAULT: BIOMODEL=" << strBiomodel << ", SOLVER=" << strSolver << ")" << endl;
      }
};


//class CResetArray : public CWarning
//{
//   public:
//      CResetArray(const string & strKey)
//      {
//         cerr << "THE ARRAY POINTED BY KEY \"" << strKey << "\" IS NOT NULL. \n"
//              << "\n\tTHE MEMORY ALLOCATED BEFORE WILL BE RELEASED..." << endl;
//      }
//};

#endif // INTERFACE_EXCEPTIONS_H
