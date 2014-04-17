#include "delphi_datamarshal.h"

//-----------------------------------------------------------------------//
bool CDelphiDataMarshal::getStatement(string strLineNoSpace)
{  
   string strLineUpperCase, strStatement, strArgument;
   
   size_t found, typearg;
   
   locale loc;
   
   int iboolint;
   
   // transform the statement to upper case
   for (size_t ii = 0; ii < strLineNoSpace.length(); ++ii)
		strLineUpperCase += toupper(strLineNoSpace[ii],loc);
   
   // find the equal sign which is used to separate the statement and argument
   found = strLineUpperCase.find_first_of("=");
   
   // get the statement and the argument of the statement
   strStatement = strLineUpperCase.substr(0,found);
   strArgument  = strLineUpperCase.substr(found+1,strLineUpperCase.size()-found-1);
   
   typearg = 0; // initialize to be 0 as an error indicator

   if (2 == found) // strStatment is a 2-letter short statement. One in strLineUpperCase
   {
      for (int ii = 1; ii < 45; ii++)
      {   
         if (strShortState[ii] == strStatement)
         { typearg = ii; break; }
      }
   } 
   else if ( (2 < found) && (7 > found) ) // strStatment is a full statement shown in strFullState
                                          // the string length is btw 2 and 7 
   {
      strShortState = strFullState;

      for (int ii = 1; ii < 45; ii++)
      {   
         if (strShortState[ii] == strStatement)
         { typearg = ii; break; }
      }      
   }                              
   else // use statments in long form which are described in section 4.4
	     // Index of statements and their shorthand, delphi manual version 5.1, pp 19 - 21.
   {
      char c1stLetter[1];
      strStatement.copy(c1stLetter,1,0);
   
      switch (c1stLetter[0])
      {
         case 'A':
            if (       "AUTOMATICCONVERGENCE" == strStatement) typearg = 21;
            if (            "AUTOCONVERGENCE" == strStatement) typearg = 21;
            if (                    "AUTOCON" == strStatement) typearg = 21;
            if (                "ATOMPOTDIST" == strStatement) typearg = 43;
            break;
         case 'B':
            if (                    "BOXFILL" == strStatement) typearg =  3;
            if (          "BOUNDARYCONDITION" == strStatement) typearg =  9;
            if (         "BOUNDARYCONDITIONS" == strStatement) typearg =  9;
            break;
         case 'C':
            if (        "CONVERGENCEINTERVAL" == strStatement) typearg = 16;
            if (        "CONVERGENCEFRACTION" == strStatement) typearg = 17;
            break;
         case 'E':
            if (         "EXTERIORDIELECTRIC" == strStatement) typearg =  5;
            if (         "EXTERNALDIELECTRIC" == strStatement) typearg =  5;
            if (      "EXITUNIFORMDIELECTRIC" == strStatement) typearg = 22;
            break;
         case 'F':
            if (                "FANCYCHARGE" == strStatement) typearg = 13;
            break;
         case 'G':
            if (                   "GRIDSIZE" == strStatement) typearg =  1;
            if (            "GRIDCONVERGENCE" == strStatement) typearg = 23;
            break;
         case 'I':
            if (                  "IONRADIUS" == strStatement) typearg =  7;
            if (         "INTERIORDIELECTRIC" == strStatement) typearg =  4;
            if (                 "ITERATIONS" == strStatement) typearg = 10;
            if (                  "ITERATION" == strStatement) typearg = 10;
            break;
         case 'L':
            if (            "LINEARITERATION" == strStatement) typearg = 10;
            if (           "LINEARITERATIONS" == strStatement) typearg = 10;
            if (          "LOGFILEPOTENTIALS" == strStatement) typearg = 14;
            if (         "LOGFILECONVERGENCE" == strStatement) typearg = 15;
            break;
         case 'M':
            // OBSOLELE. REMOVED FROM THE LIST.
            //if (               "MEMBRANEDATA" == strStatement) typearg = 12;
            if (             "MAXCONVERGENCE" == strStatement) typearg = 38;
            break;
         case 'N':
            if (         "NONLINEARITERATION" == strStatement) typearg = 11;
            if (        "NONLINEARITERATIONS" == strStatement) typearg = 11;
            // UNUSED. REMOVED FROM THE LIST.
            //if (            "NORMCONVERGENCE" == strStatement) typearg = 39;
            break;
         case 'P':
            if (          "PERIODICBOUNDARYX" == strStatement) typearg = 18;
            if (          "PERIODICBOUNDARYY" == strStatement) typearg = 19;
            if (          "PERIODICBOUNDARYZ" == strStatement) typearg = 20;
            if (                "PROBERADIUS" == strStatement) typearg =  6;
            if (             "PERCENTBOXFILL" == strStatement) typearg =  3;
            if (                "PERCENTFILL" == strStatement) typearg =  3;
            break;
         case 'R':
            if (           "RELAXATIONFACTOR" == strStatement) typearg = 24;
            if (                  "RADPOLEXT" == strStatement) typearg = 29;
            if (                     "RELPAR" == strStatement) typearg = 30;
            if (             "RMSCONVERGENCE" == strStatement) typearg = 37;
            break;
         case 'S':
            if (                   "SALTCONC" == strStatement) typearg =  8;
            if (          "SALTCONCENTRATION" == strStatement) typearg =  8;
            if ("SPHERICALCHARGEDISTRIBUTION" == strStatement) typearg = 13;
            break;
         case 'T':
            if (                "TEMPERATURE" == strStatement) typearg = 44;  
            break;
      } // end of switch (c1stLetter[1])

   } 

   if (0 == typearg) return false; // invalid statement

   switch (typearg)
   {
      case 1:
         iGrid = (integer)(atoi(strArgument.c_str())); 
         break;
      case 2:
         fScale = (real)(atof(strArgument.c_str())); 
         break;
      case 3:
         fPercentageFill = (real)(atof(strArgument.c_str())); 
         break;
      case 4:
         fInDielec = (real)(atof(strArgument.c_str())); 
         break;
      case 5: 
         fExDielec = (real)(atof(strArgument.c_str())); 
         break;
      case 6:
         rgfProbeRadius[0] = (real)(atof(strArgument.c_str())); 
         break;
      case 7:
         fIonRadius = (real)(atof(strArgument.c_str())); 
         break;
      case 8:
         rgfSalt[0] = (real)(atof(strArgument.c_str())); 
         break;
      case 9:
         iBndyType = atoi(strArgument.c_str()); 
         break;
      case 10:
         iLinIterateNum = atoi(strArgument.c_str()); 
         bAutoConverge  = false; 
         break;
      case 11:
         iNonIterateNum = atoi(strArgument.c_str()); 
         if (30 > iNonIterateNum)
         {   
            CNoEnoughIterations warning(iNonIterateNum);
            //iNonIterateNum = 30;
         }
         break;
      // case 12: // OBSOLELE. REMOVED FROM THE LIST.
      //   if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
      //      imem = iboolint;
      //   break;
      case 13:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            bCrgInterplateType = iboolint;
         break;          
      case 14:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            bLogPotential = iboolint;
         break;       
      case 15:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            bLogGraph = iboolint;
         break;
      case 16:
         iIterateInterval = atoi(strArgument.c_str()); 
         break;                      
      case 17:
         iConvergeFract = atoi(strArgument.c_str()); 
         break;
      case 18:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            rgbPeriodicBndy[0] = (bool)iboolint;
         break;             
      case 19:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            rgbPeriodicBndy[1] = (bool)iboolint;
         break;
      case 20:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            rgbPeriodicBndy[2] = (bool)iboolint;
         break;
      case 21:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            bAutoConverge = (bool)iboolint;
         break;
      case 22:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            bExitUniformDielect = (bool)iboolint;
         break;
      case 23:
         fGridConverge = (real)(atof(strArgument.c_str()));
         bAutoConverge = true;
         break;
      case 24:
         fSpectralRadius = (real)(atof(strArgument.c_str()));
         bSpectralRadius = true;
         break;
      case 25:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            bFixedRelaxParam = (bool)iboolint;
         break;
      case 26:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            bSolvePB = (bool)iboolint;
         break; 
      case 27:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            bOutGraspSurf = (bool)iboolint;
         break;       
      case 28:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            bOutCrgDensity = (bool)iboolint;
         break;                
      // ONLY FOR OBJECTS. REMOVED FROM THE LIST.
      // case 29:
      //   fRadPolExt = (real)(atof(strArgument.c_str()));
      //   break;
      case 30:
         fRelaxParam = (real)(atof(strArgument.c_str()));
         bManualRelaxParam = true;
         break;
      case 31:
         rgfSalt[1] = (real)(atof(strArgument.c_str()));
         break; 
      case 32:
         rgfProbeRadius[1] = (real)(atof(strArgument.c_str()));
         break;
      case 33:
         rgiValence1[0] = atoi(strArgument.c_str()); 
         break;         
      case 34:
         rgiValence1[1] = atoi(strArgument.c_str()); 
         break;
      case 35:
         rgiValence2[0] = atoi(strArgument.c_str()); 
         break;
      case 36:
         rgiValence2[1] = atoi(strArgument.c_str()); 
         break;
      case 37:
         fRmsc = (real)(atof(strArgument.c_str())); 
         break;
      case 38:
         fMaxc = (real)(atof(strArgument.c_str())); 
         break;         
      // case 39: // UNUSED. REMOVED FROM THE LIST.
      //    fNormc = (real)(atof(strArgument.c_str())) ;
      //    break;
      case 40:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            rgbPeriodicBndy[3] = (bool)iboolint;
         fgPotentialDrop.nX = (real)(atof(strArgument.c_str()));   
         break;
      case 41:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            rgbPeriodicBndy[4] = (bool)iboolint;
         fgPotentialDrop.nY = (real)(atof(strArgument.c_str()));           
         break;
      case 42:
         if ( -1 < (iboolint = yesno(strArgument, strStatement)) )  
            rgbPeriodicBndy[5] = (bool)iboolint;
         fgPotentialDrop.nZ = (real)(atof(strArgument.c_str()));           
         break;         
      case 43:
         fPotentialUpperBond = (real)(atof(strArgument.c_str()));
         break;               
      case 44:
         fTemper = (real)(atof(strArgument.c_str())); 
         fTemper -= dAbsoluteZero;
         break;       
  
   } // end of switch (typearg)
   
   return true;   
}

//-----------------------------------------------------------------------//
int CDelphiDataMarshal::yesno(string strArgument, string strStatement)
{
    	
   if (string::npos != strArgument.find("TRUE"))  return 1;
   
   if (string::npos != strArgument.find("YES"))   return 1;

   if (string::npos != strArgument.find("ON"))    return 1;

   if (string::npos != strArgument.find("T"))     return 1;
   
   if (string::npos != strArgument.find("FALSE")) return 0;

   if (string::npos != strArgument.find("OFF"))   return 0;

   if (string::npos != strArgument.find("NO"))    return 0;

   if (string::npos != strArgument.find("F"))     return 0;

   //throw CBadStatementAssignment(strArgument, strStatement);
   CBadStatementAssignment warning(strArgument, strStatement);
   
   
   //cout << "WARNING: WRONG STATEMENT. CANNOT ASSIGN TRUE OR FALSE TO " << strStatement.c_str() << endl;
   //
   return -1;    	
}

