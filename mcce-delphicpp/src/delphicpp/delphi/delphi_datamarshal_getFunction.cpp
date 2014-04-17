#include "delphi_datamarshal.h"

//-----------------------------------------------------------------------//
bool CDelphiDataMarshal::getFunction(string strLineNoSpace)
{
   locale loc;
   
   // find the position of the bracket    	   
   size_t pos = strLineNoSpace.find_first_of('(');

   // if there is no '(' report error
   if (string::npos == pos) return false;
   
   // get the function name
   string strTempFunc = strLineNoSpace.substr(0,pos);
   
   // string that contains the function name transform the function name to upper case
   string strFunc; 
   for (size_t ii = 0; ii < strTempFunc.length(); ++ii) 
      strFunc += toupper(strTempFunc[ii], loc);

   // string with the argument of the function not in upper case to keep the name of the input file if there is one
   string strDirecFileName;
   strDirecFileName = strLineNoSpace.substr(pos, strLineNoSpace.size()-pos); 

   // string with the argument of the function in upper case the argument is put into upper case
   string strDirecUpperCase;
   for (size_t ii = 0; ii < strDirecFileName.length()-1; ++ii) 
      strDirecUpperCase += toupper(strDirecFileName[ii], loc); 

   size_t typearg = 0; // initialize to be 0 as an error indicator
   
   // select the function name  
   for (int ii = 1; ii < 12; ii++)
   {
      if (strFullFunc[ii] == strFunc) { typearg = ii; break; }
   }
   
   for (int ii = 1; ii < 5; ii++)
   {
      if (strShortFunc[ii] == strFunc) { typearg = ii; break; }
   }

   if (0 == typearg) return false; // invalid function name

   // if there is a frm, form or format argument, find it and its position
   size_t kk = 0, pos1 = 0, pos2 = 0;

   if ( string::npos != (pos = strDirecUpperCase.find("FRM=")) ) 
      kk = pos+4;
   else if ( string::npos != (pos = strDirecUpperCase.find("FORM=")) )    
      kk = pos+5;
   else if ( string::npos != (pos = strDirecUpperCase.find("FORMAT=")) )   
      kk = pos+7;

   // if the frm argument was found, find the format value in upper case
   bool bFormat = false;
   
   string strFormatString;
   
   if (0 != kk)
   {
      bFormat = true;
      if (string::npos != (pos = strDirecUpperCase.find(")",kk))) pos1 = pos;
      if (string::npos != (pos = strDirecUpperCase.find(",",kk))) pos2 = pos;
         
      pos = (pos1 > pos2) ? pos1 : pos2;   
   
      //ISN'T strDirecUpperCase ALREADY IN UPPER CASE???
      for (size_t ii=kk; ii<pos; ++ii) 
         strFormatString += toupper(strDirecUpperCase[ii],loc); 
   }
   
   // find the unit or form argument, and its position
   int kk2 = 0, kk3 = 0;
   
   if (string::npos != (pos = strDirecUpperCase.find("UNIT=")))
      kk2 = pos+5;
   else if (string::npos != (pos = strDirecUpperCase.find("FILE=")))  
      kk3 = pos+5; 
      
   bool bFile = false;
   if (0 != kk2+kk3) bFile = true;
     
   switch (typearg)
   {
      case 1: // CENTER or CENT function
      {
         int iJ0 = 0;
      
         if ( "()" == strDirecUpperCase || "(0,0,0)" == strDirecUpperCase )
            // fgOffCenter initialized to be {0.0, 0.0, 0.0}, no need to reset here
            iJ0 = 1;
      
         if (bFile)
            strCentFile = getFileName(strDirecFileName, kk2, kk3);       
      
         if (0 != kk2+kk3)
         {
            fgOffCenter.nX = 999.0; fgOffCenter.nY = 0.0; fgOffCenter.nZ = 0.0;
         }
            
         if (string::npos != strDirecUpperCase.find("AN=1"))
         {
            fgOffCenter.nX = 999.0; fgOffCenter.nY = 999.0; fgOffCenter.nZ = 0.0;   
         }
            
         if (0 == kk2+kk3+iJ0)
         {
            size_t n1, n2;
            
            n1 = strDirecUpperCase.find(",",1);
            fgOffCenter.nX = (real)( atof(strDirecUpperCase.substr(1, n1-1).c_str()) );
            
            n2 = strDirecUpperCase.find(",",n1+1);
            fgOffCenter.nY = (real)( atof(strDirecUpperCase.substr(n1+1,n2-n1-1).c_str()) );
         
            n1 = n2 + 1; n2 = strDirecUpperCase.find(")", n1);
            fgOffCenter.nZ = (real)( atof(strDirecUpperCase.substr(n1,n2-n1).c_str()) );
         }   
         
         break;   
      }
      
      case 2: // ACENTER or ACENT function
      {
         size_t n1, n2;
         
         n1 = strDirecUpperCase.find(",",1);
         fgAcent.nX = (real)( atof(strDirecUpperCase.substr(1, n1-1).c_str()) );
            
         n2 = strDirecUpperCase.find(",",n1+1);
         fgAcent.nY = (real)( atof(strDirecUpperCase.substr(n1+1,n2-n1-1).c_str()) );
         
         n1 = n2 + 1; n2 = strDirecUpperCase.find(")", n1);
         fgAcent.nZ = (real)( atof(strDirecUpperCase.substr(n1,n2-n1).c_str()) );
    
         bIsAcent = true;
         
         break;
      }
                  
      case 3: // READ or IN function
         if ("SIZ" == strDirecUpperCase.substr(1,3)) // size file
         {
            if (bFile) strSizeFile = getFileName(strDirecFileName,kk2,kk3);
            
            if (bFormat) 
            {
               CInUnknownSizeFormat warning(strFormatString);
            }
         }
         
         if ("CRG" == strDirecUpperCase.substr(1,3)) // charge file
         {
            if (bFile) strCrgFile = getFileName(strDirecFileName,kk2,kk3); 
            
            if (bFormat) 
            {
               CInUnknownCrgFormat warning(strFormatString);
            }   
         }
         
         if ("PDB" == strDirecUpperCase.substr(1,3))    // pdb file
         {
            iPdbFormatIn = STDPDB;
            
            if (bFile) strPdbFile = getFileName(strDirecFileName,kk2,kk3);
         }

         if ("MODPDB" == strDirecUpperCase.substr(1,6)) // modified pdb
         {
            iPdbFormatIn = MODPDB;

            if (bFile) strPdbFile = getFileName(strDirecFileName,kk2,kk3);
         
            if (bFormat)
            {
               if      ("MOD" == strFormatString) iPdbFormatIn = MODPDB;
               else if ("PQR" == strFormatString) iPdbFormatIn = PQRPDB;
               else    { CInUnknownPDBFormat warning(strFormatString); }
               
               /*
               if (0 < iPdbFormatIn)
                  bPdbUnformatIn = true; (obsolete)
               else
               {
                  CInUnknownPDBFormat warning(strFormatString);
               }
               */
            }
         }
         
         if ("MODPDB4" == strDirecUpperCase.substr(1,7)) 
         {
            iPdbFormatIn = MOD4PDB;

            if (bFile) strPdbFile = getFileName(strDirecFileName,kk2,kk3);
            
            if (bFormat)
            {
               //if    ("UN"  == strFormatString) iPdbFormatIn = 41;
               if      ("MOD" == strFormatString) iPdbFormatIn = MOD4PDB;
               else if ("PQR" == strFormatString) iPdbFormatIn = PQR4PDB;
               else    { CInUnknownPDBFormat warning(strFormatString); }

               /*
               if (40 < iPdbFormatIn)
                  bPdbUnformatIn = true; (obsolete)
               else
                  CInUnknownPDBFormat warning(strFormatString);
               */
            }
         } 
         
         // new options are added to allow users easily select pqr formats
         if ("PQR" == strDirecUpperCase.substr(1,3))    // pqr file
         {
            iPdbFormatIn = PQRPDB;
            if (bFile) strPdbFile = getFileName(strDirecFileName,kk2,kk3);
         }
         
         if ("PQR4" == strDirecUpperCase.substr(1,4))    // pqr4 file
         {
            iPdbFormatIn = PQR4PDB;
            if (bFile) strPdbFile = getFileName(strDirecFileName,kk2,kk3);
         }
         
         if ("FRC" == strDirecUpperCase.substr(1,3))
         {
            if (bFile) strFrciFile = getFileName(strDirecFileName,kk2,kk3);
            
            if (bFormat) 
            {
               if ("SELF"  == strFormatString) 
                  bPDB2FRCInSite = true;
               else   
               {   
                  CInUnknownFRCFormat warning(strFormatString);
               }
            }
         }
         
         if ("PHI" == strDirecUpperCase.substr(1,3))
         {
            if (bFile) strPhiiFile = getFileName(strDirecFileName,kk2,kk3);
            
            if (bFormat) 
            {
               CInUnknownPHIFormat warning(strFormatString);
            }     
         }
      
         break;
      
      case 4: // WRITE or OUT function
      {
         bool bFlag = false, bIJ4;

         if ("OFF" != strDirecUpperCase.substr(1,3)) bFlag = true;
            
         bIJ4 = bFlag && bFile;   

         if ("PHI" == strDirecUpperCase.substr(1,3))  
         {
            bPhimapOut = bFlag;
            
            if (bIJ4) strPhiFile = getFileName(strDirecFileName,kk2,kk3);
            
            if (bFormat)
            {
               if      ("BIOSYM" == strFormatString) iPhiFormatOut = 1;
               else if ("GRASP"  == strFormatString) iPhiFormatOut = 2;
               else if ("CCP4"   == strFormatString) iPhiFormatOut = 3;
               else if ("DIFF"   == strFormatString) iPhiFormatOut = 4;
               else if ("CUBE"   == strFormatString) iPhiFormatOut = 5;
            
               if (1 == iPhiFormatOut) bBiosystemOut = true;
               
               if (0 == iPhiFormatOut) 
               {
                  COutUnknownPHIFormat warning(strFormatString);
               }   
            }
         }
         
         if ("SRF" == strDirecUpperCase.substr(1,3))  
         {
            bOutGraspSurf = true;
            
            if(bIJ4) strGraspFile = getFileName(strDirecFileName,kk2,kk3);
            
            if (bFormat && ("BEM" == strFormatString) ) bBemSrfOut = true;
         }
         
         if ("FRC" == strDirecUpperCase.substr(1,3))
         {
            bSiteOut = bFlag;
         
            if (bIJ4) strFrcFile = getFileName(strDirecFileName,kk2,kk3);
            
            if (bFormat)
            {
               if      ("RC" == strFormatString) iFrcFormatOut = 1;
               else if ("R"  == strFormatString) iFrcFormatOut = 2;
               else if ("UN" == strFormatString) iFrcFormatOut = 3;
               
               if (1 == iFrcFormatOut || 2 == iFrcFormatOut) 
                  bReactFieldInFRC = true;
                  
               if (1 > iFrcFormatOut || 3 < iFrcFormatOut)
               {  
                  COutUnknownFRCFormat warning(strFormatString);
               }
            }        
         }
         
         if ("EPS" == strDirecUpperCase.substr(1,3))
         {
            bEpsOut = bFlag;
            
            if (bIJ4) strEpsFile = getFileName(strDirecFileName,kk2,kk3);
            
            if (bFormat) 
            {
               COutUnknownEPSFormat waring(strFormatString);
            }   
         }
         
         if ("MODPDB" == strDirecUpperCase.substr(1,6))
         {
            bModPdbOut = bFlag; iModPdbFormatOut = MODPDB;
            
            if (bIJ4) 
               strModifiedPdbFile = getFileName(strDirecFileName,kk2,kk3);
               
            if (bFormat)
            {
               if ("PQR" == strFormatString) 
                  iModPdbFormatOut = PQRPDB;
               else
               {   
                  COutUnknownMODPDBFormat warning(strFormatString);
               }   
            }
         }
         
         if ("MODPDB4" == strDirecUpperCase.substr(1,7))         
         {
            bModPdbOut = bFlag; iModPdbFormatOut = MOD4PDB;
            
            if (bIJ4) 
               strModifiedPdbFile = getFileName(strDirecFileName,kk2,kk3);

            if (bFormat)
            {
               if ("PQR" == strFormatString) 
                  iModPdbFormatOut = PQR4PDB;
               else
               {
                  COutUnknownMODPDBFormat warning(strFormatString);
               }   
            }         
         }
         
         if ("UNPDB" == strDirecUpperCase.substr(1,5))
         {
            bUnformatPdbOut = bFlag;
            
            if (bIJ4) 
               strUnformatPdbFile = getFileName(strDirecFileName,kk2,kk3);
         
            if (bFormat) 
            {
               COutUnknownUNPDBFormat warning(strFormatString);
            }
         }
         
         if ("UNFRC" == strDirecUpperCase.substr(1,5))
         {
            bUnformatFrcOut = bFlag;            
         
            if (bIJ4) 
               strUnformatFrcFile = getFileName(strDirecFileName,kk2,kk3);
         
            if (bFormat) 
            {
               COutUnknownUNFRCFormat warning(strFormatString);
            }   
         }
         
         if ("ENERGY" == strDirecUpperCase.substr(1,6))
         {
            bEngOut = bFlag;            
         
            if (bIJ4) 
               strEnergyFile = getFileName(strDirecFileName,kk2,kk3);
         
            if (bFormat) 
            {
               COutUnknownEnergyFormat warning(strFormatString); 
            }   
         }         
         
         if ("GCRG" == strDirecUpperCase.substr(1,4))
            bGridCrgOut = true;
            
         if ("HSURF" == strDirecUpperCase.substr(1,5))
            bHsurf2DatOut = true;
            
         if ("DB" == strDirecUpperCase.substr(1,2))
            bDbOut = true;
            
         if ("SURFEN" == strDirecUpperCase.substr(1,6))
            bSurfEngOut = true;     
            
         if ("SCRG" == strDirecUpperCase.substr(1,4))
         {
            bSurfCrgOut = bFlag;
            
            if (bIJ4) strScrgFile = getFileName(strDirecFileName,kk2,kk3);
         
            if (bFormat)
            {
               if ("PDB" == strFormatString) iSurfCrgFormatOut = 1;
               
               if ("PDBA" == strFormatString) 
               {
                  COutOBSOLETEPDBAFormat warning(strFormatString);
               }
                  
               if (1 > iSurfCrgFormatOut || 2 < iSurfCrgFormatOut)
               {   
                  COutUnknownSurfCrgFormat warning(strFormatString);
               }   
            }
         }                   

         break;
      }
      
      case 5: // ENERGY function
              // since energy can have many arguments, the comma is important
              // it helps to separate the commands so that when looking for S 
              // does not find SOLVATION instead
      {
         strDirecUpperCase.insert(strDirecUpperCase.end()-1,','); // comma is replaced for all arguments

         if (string::npos != strDirecUpperCase.find("GRID,")) bGridEng = true;
         
         unsigned long int iString; // change to long integer for out of range bug
         
         iString = strDirecUpperCase.find("S,"); // look for AS or S 
         if (string::npos != iString)
         {
            if ( 0 != strDirecUpperCase.compare(iString-1,1,"A") ) // S
               bSolvEng = true;
            else // AS
               bAnalySurfEng = true;
         }
      
         iString = strDirecUpperCase.find("G,"); // look for AG or G
         if (string::npos != iString)
         {      
            if ( 0 != strDirecUpperCase.compare(iString-1,1,"A") ) // S
               bGridEng = true;
            else
               bAnalyEng = true;               
         }
      
         // look for each of the following strings, and set the boolean 
         // accordingly
         if ( string::npos != strDirecUpperCase.find("ION,") || string::npos != strDirecUpperCase.find("IONIC_C,") )
        	 bIonsEng = true;
         if ( string::npos != strDirecUpperCase.find("SOLVATION,") || string::npos != strDirecUpperCase.find("SOL,") )
            bSolvEng = true;
         if ( string::npos != strDirecUpperCase.find("C,") || string::npos != strDirecUpperCase.find("COU,") || string::npos != strDirecUpperCase.find("COULOMBIC,") )
            bCoulombEng = true;                   
         if ( string::npos != strDirecUpperCase.find("AS,") || string::npos != strDirecUpperCase.find("ANASURF,") || string::npos != strDirecUpperCase.find("ANALYTICSURFACE,") )
            bAnalySurfEng = true; 
         if ( string::npos != strDirecUpperCase.find("AG,") || string::npos != strDirecUpperCase.find("ANAGRID,") || string::npos != strDirecUpperCase.find("ANALYTICGRID,") )
            bAnalyEng = true;             
      
         break;
      }
          
      case 6: // SITE function
         // empty bracket means reset all quantities to false
         // reset back to false in fortran code - no need here since 
         // they are already initialized to be false in contructor 
         if (2 == strDirecUpperCase.length()) { };
         
         if (string::npos != strDirecUpperCase.find("ATOM,"))
            bAtomInSite = true;
         if (string::npos != strDirecUpperCase.find("CHARGE,"))
            bCrgInSite = true;  
         if (string::npos != strDirecUpperCase.find("POTENTIAL,"))
            bGridPotentialInSite = true; 
         if (string::npos != strDirecUpperCase.find("ATOMICPOT,"))
            bAtomPotentialInSite = true;             
         if (string::npos != strDirecUpperCase.find("DEBYEFRACTION,"))
            bDebyeFractionInSite = true;    
         if (string::npos != strDirecUpperCase.find("FIELD,"))
            bFieldInSite = true;      
         if (string::npos != strDirecUpperCase.find("REACTION,"))
            bReactPotentialInSite = true;               
         if (string::npos != strDirecUpperCase.find("COULOMB,"))
            bCoulombPotentialInSite = true;              
         if (string::npos != strDirecUpperCase.find("COORDINATES,"))
            bAtomCoordInSite = true;               
         if (string::npos != strDirecUpperCase.find("SALT,"))
            bSaltInSite = true;             
         if (string::npos != strDirecUpperCase.find("TOTAL,"))
            bTotalPotentialInSite = true;
         if (string::npos != strDirecUpperCase.find("REACTIONFORCE,")) // new
            bReactForceInSite = true;
         if (string::npos != strDirecUpperCase.find("COULOMBFORCE,")) // new
            bCoulombForceInSite = true;
         if (string::npos != strDirecUpperCase.find("MOLECULARDYNAMICS,"))//new
            bMDInSite = true;
         if (string::npos != strDirecUpperCase.find("SURFACECHARGE,")) // new
            bSurfCrgInSite = true;
         if (string::npos != strDirecUpperCase.find("TOTALFORCE,")) // new
            bTotalForceInSite = true;

         // can only do the last letter like this if there is no cooincindence with those above
         if (string::npos != strDirecUpperCase.find("A,"))
            bAtomInSite = true;
         if (string::npos != strDirecUpperCase.find("Q,"))
            bCrgInSite = true;  
         if (string::npos != strDirecUpperCase.find("P,"))
            bGridPotentialInSite = true; 
         if (string::npos != strDirecUpperCase.find("ATPO,"))
            bAtomPotentialInSite = true;             
         if (string::npos != strDirecUpperCase.find("DEB,"))
            bDebyeFractionInSite = true;    
         if (string::npos != strDirecUpperCase.find("F,")) 
         {
            if (string::npos != strDirecUpperCase.find("RF,"))
               bReactForceInSite = true; 
            if (string::npos != strDirecUpperCase.find("CF,"))
               bCoulombForceInSite = true;
            if (string::npos != strDirecUpperCase.find("MDF,"))
               bMDInSite = true;         
            if (string::npos != strDirecUpperCase.find("SF,"))
               bSurfCrgInSite = true;
            if (string::npos != strDirecUpperCase.find("TF,"))
               bTotalForceInSite = true;
            if ( !(bReactForceInSite || bCoulombForceInSite || bMDInSite || bSurfCrgInSite || bTotalForceInSite) )
               bFieldInSite = true; 
         }
         if (string::npos != strDirecUpperCase.find("R,"))
            bReactPotentialInSite = true;        
         if (string::npos != strDirecUpperCase.find("C,"))
            bCoulombPotentialInSite = true;              
         if (string::npos != strDirecUpperCase.find("X,"))
            bAtomCoordInSite = true;               
         if (string::npos != strDirecUpperCase.find("I,"))
            bSaltInSite = true;             
         if (string::npos != strDirecUpperCase.find("T,"))
            bTotalPotentialInSite = true; 

         if ( bReactPotentialInSite || bReactForceInSite || bMDInSite || bTotalForceInSite || bTotalPotentialInSite || bSurfCrgInSite )
            bReactFieldInFRC = true;
            
         if (bSurfCrgInSite) bPDB2FRCInSite = true;       
            
         break;              
      
      case 7: // BUFFZ function
      {
         string strStringChar;
         
         strStringChar = strDirecUpperCase.substr(0,3);
         ieBuffz.nMin.nX = (integer)( atoi(strStringChar.c_str()) );
         
         strStringChar = strDirecUpperCase.substr(3,3);         
         ieBuffz.nMin.nY = (integer)( atoi(strStringChar.c_str()) );
         
         strStringChar = strDirecUpperCase.substr(6,3);         
         ieBuffz.nMin.nZ = (integer)( atoi(strStringChar.c_str()) );
      
         strStringChar = strDirecUpperCase.substr(9,3);         
         ieBuffz.nMax.nX = (integer)( atoi(strStringChar.c_str()) );
         
         strStringChar = strDirecUpperCase.substr(12,3);         
         ieBuffz.nMax.nY = (integer)( atoi(strStringChar.c_str()) );
         
         strStringChar = strDirecUpperCase.substr(15,3);         
         ieBuffz.nMax.nZ = (integer)( atoi(strStringChar.c_str()) );    
      
         bIsBuffz = true;
      
         break;
      }
      
      case 8: // QPREF function
              // TAKE NO ACTION.
         
         break;
            
      case 9: // INSOBJ function
              // ONLY FOR OBJECTS. REMOVED FROM THE LIST AND TAKE NO ACTION.
         
         break;   
      
      case 10: // SURFACE function
         if (string::npos != strDirecUpperCase.find("CONNOLLY")) 
            iTypeSurf = 0;
         
         if (string::npos != strDirecUpperCase.find("SKIN"))    
            iTypeSurf = 1;
         
         if (string::npos != strDirecUpperCase.find("BLOBBY"))    
            iTypeSurf = 2;
         
         if (string::npos != strDirecUpperCase.find("MESH"))    
            iTypeSurf = 3;
         
         if (string::npos != strDirecUpperCase.find("MSMS"))    
            iTypeSurf = 4;            
            
         break;   
   
      default:
      {
         CUnknownFunction warning(strFunc);
         break;
      }
   } // end of switch (typearg)
   
   return true;

}

//-----------------------------------------------------------------------//
string CDelphiDataMarshal::getFileName(string strArgument, int iUnitPosit, int iFilePosit)
{
   size_t pos;
   string strFileName;
   string strNumber = "0123456789";
   string strLetter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.:_-+=!@#$^1234567890abcdefghijklmnopqrstuvwxyz|/?><";

   if (0 != iUnitPosit)
   {
      strFileName = "fort.";
      
      for (size_t ii = iUnitPosit; ii < strArgument.length(); ++ii)
      {
         pos = strNumber.find_first_of(strArgument[ii]);
         if (string::npos == strNumber.find_first_of(strArgument[ii])) break;
         strFileName += strNumber[pos];     
      }
   }

   if (0 != iFilePosit)
   {
      for (size_t ii = iFilePosit; ii < strArgument.length(); ++ii)
      {
         if (string::npos != strLetter.find_first_of(strArgument[ii]))
            strFileName += strArgument[ii];
      }
   }
   
   return strFileName;
}
