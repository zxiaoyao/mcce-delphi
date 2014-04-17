#include "delphi_datamarshal.h"

//-----------------------------------------------------------------------//
void CDelphiDataMarshal::updateParameters()
{
   // ++++++ update parameters after reading the parameter file ++++++//
   //*****************************************************************//
   //                                                                 //
   //        perform updates after reading the parameter file         //
   //                                                                 //
   //*****************************************************************// 

   if (-1 == rgfProbeRadius[1]) 
      rgfProbeRadius[1] = rgfProbeRadius[0];

   // parameters set at the end of subroutine rdprm
   if (0 > fExDielec || 0 > fInDielec)
   {
      CMinusDielec warning(fExDielec, fInDielec);
      
      fExDielec = abs(fExDielec); 
      fInDielec = abs(fInDielec);
   }  

   real fZ1Plus  = rgiValence1[0];  // valence 1
   real fZ1Minus = rgiValence1[1];
   real fZ2Plus  = rgiValence2[0];  // valence 2
   real fZ2Minus = rgiValence2[1];

   // concentration of positive ion
   real fZ1PlusConcentrate = rgfSalt[0]*fZ1Minus;
   real fZ2PlusConcentrate = rgfSalt[1]*fZ2Minus;
   
   fIonStrength = (fZ1PlusConcentrate*fZ1Plus*(fZ1Plus+fZ1Minus) + fZ2PlusConcentrate*fZ2Plus*(fZ2Plus+fZ2Minus))/2.0;
                        
   // coefficients in Taylor series of the charge concentration apart from n! 
   // (order >=1)
   // 2012-04-24 chuan Correct coefficients in Taylor series. NOT in compact
   //            form just for clean math formula
   fTaylorCoeff1 = -2.0*fIonStrength;
   
   fTaylorCoeff2 =  ( fZ1PlusConcentrate*fZ1Plus *pow(fZ1Plus, 2) - 
                      fZ1PlusConcentrate*fZ1Minus*pow(fZ1Minus,2) +
                      fZ2PlusConcentrate*fZ2Plus *pow(fZ2Plus, 2) -
                      fZ2PlusConcentrate*fZ2Minus*pow(fZ2Minus,2) )/2.0;

   fTaylorCoeff3 = -( fZ1PlusConcentrate*fZ1Plus *pow(fZ1Plus, 3) + 
                      fZ1PlusConcentrate*fZ1Minus*pow(fZ1Minus,3) +
                      fZ2PlusConcentrate*fZ2Plus *pow(fZ2Plus, 3) +
                      fZ2PlusConcentrate*fZ2Minus*pow(fZ2Minus,3) )/6.0;
                         
   fTaylorCoeff4 =  ( fZ1PlusConcentrate*fZ1Plus *pow(fZ1Plus, 4) - 
                      fZ1PlusConcentrate*fZ1Minus*pow(fZ1Minus,4) +
                      fZ2PlusConcentrate*fZ2Plus *pow(fZ2Plus, 4) -
                      fZ2PlusConcentrate*fZ2Minus*pow(fZ2Minus,4) )/24.0;
                        
   fTaylorCoeff5 = -( fZ1PlusConcentrate*fZ1Plus *pow(fZ1Plus, 5) + 
                      fZ1PlusConcentrate*fZ1Minus*pow(fZ1Minus,5) +
                      fZ2PlusConcentrate*fZ2Plus *pow(fZ2Plus, 5) +
                      fZ2PlusConcentrate*fZ2Minus*pow(fZ2Minus,5) )/120.0;
                          
   // convert ionic strength to debye length
   if (dMinimalDebyeLength < fIonStrength)
   {
      real fDebyeFactor = 0.01990076478*sqrt(fTemper*fExDielec);
      fDebyeLength = fDebyeFactor/sqrt(fIonStrength);
   
      if (0 < iNonIterateNum) bNonlinearEng = true;
   }
   else
   {
      bIonsEng = false; 
      fDebyeLength = dMinimalDebyeLength;
   }
                          
   // epkt assignment as a function of temperature
   fEPKT = dEPK/fTemper;
   
   // set epsin and epsout (= epkt adjusted dielectrics such that all distances are in angstroms, charges in e)
   fEpsIn  = fInDielec/fEPKT; 
   fEpsOut = fExDielec/fEPKT; 
   
   // test for unformatted pdb and frc files
   // the same tests have been implemented in class CIO. However, here users may make mistakes in parameter file to
   // require wrong format of the files. So check again to reset format flags.
   string strASCI = "1234567890 .-+#,$asdfghjklzxcvbnmqwertyuiopASDFGHJKLZXCVBNMQWERTYUIOP)(}{][/";

   ifstream ifFileHandle;
   char cTestChar[80];  
   
   if (!bPdbUnformatIn) // PDB file
   {
      ifFileHandle.open(strPdbFile.c_str());
    
      if (!ifFileHandle.is_open()) throw CUnknownFile(strPdbFile);   
   
      ifFileHandle.read(cTestChar,80);

      int iCount = 0;
   
      for (int i = 0; i < 80; i++)
      {
         if (string::npos == strASCI.find(cTestChar[i]) ) iCount += 1;
      }
   
      if (10 < iCount) // unformatted PDB
      {
         bPdbUnformatIn = true; 
         CToUnformattedFile warning(strPdbFile,strASCI); 
      }   
   
      ifFileHandle.close();
   }   
   
   if (bUnformatFrcOut) // FRC file
   {
      ifFileHandle.open(strFrcFile.c_str());
    
      if (!ifFileHandle.is_open()) throw CUnknownFile(strFrcFile);   
   
      ifFileHandle.read(cTestChar,80);

      int iCount = 0;
   
      for (int i = 0; i < 80; i++)
      {
         if (string::npos == strASCI.find(cTestChar[i]) ) iCount += 1;
      }
   
      if (10 < iCount) // unformatted FRC
      {
         CToUnformattedFile warning(strFrcFile,strASCI); 
         bFrcUnformatIn = true; 
      }   
   
      ifFileHandle.close();
   }  
   
   //*****************************************************************//
   //                                                                 //
   //               read size, charge, PDB files                      //
   //                                                                 //
   //*****************************************************************//           
   unique_ptr<CIO> pio(new CIO(fInDielec,fEPKT)); // smart unique_ptr
   
   pio->setDelphiAtom(bSolvePB,bSurfCrgInSite,strSizeFile,strCrgFile,strPdbFile,iPdbFormatIn,bPdbUnformatIn);

   iMediaNum        = pio->iMediaNum;        // nmedia
   iObjectNum       = pio->iObjectNum;       // nobject
   iAtomNum         = pio->iAtomNum;         // natom
   iResidueNum      = pio->iResidueNum;      // resnummax
   bOnlyMolecule    = pio->bOnlyMolecule;    // ionlymol
   prgapAtomPdb     = pio->prgapAtomPdb;     // delphipdb(natom)
   prgfMediaEps     = pio->prgfMediaEps;     // medeps(0:nmediamax)
   prgstrObject     = pio->prgstrObject;     // dataobject(nobjectmax,2)
   prgiAtomMediaNum = pio->prgiAtomMediaNum; // iatmmed(Natom+Nobjectmax)

   // write unformatted PDB file       
   if (bUnformatPdbOut) pio->writeUnformatPdb(strUnformatPdbFile);
         
   // write mod/pqr/mod4/pqr4-type PDB file
   if (bModPdbOut) 
      pio->writeModifiedPdb(strModifiedPdbFile,iModPdbFormatOut);

   if (1 < iMediaNum) iDirectEpsMap = 1;   
   
   fEpsIn = pio->prgfMediaEps[1];
   
   //--------------------------- extrmobjects ------------------------//
   // extrmobjects: find extrema of each object and  according to them limobject contains extreme values of each object
   // for a molecule it has extreme but without radii 
    
   iMoleculeNum = 0;    // numbmol
   fMaxRadius   = 0.01; // rdmx
   
   SExtrema<real> tmpExtrema;
   for (unsigned int i = 0; i < prgstrObject.size(); i=i+2)
   {
      string strLine = prgstrObject[2*i]; // prgstrObject[0][nobject]
   
      if (0 != strLine.compare(0,4,"is a")) throw CIsAnObjectType(strLine);
      
      iMoleculeNum += 1;

#ifdef VERBOSE
      cout << "Object number " << i << " is a molecule\n";
#endif       
         
      if (0 == iAtomNum) throw CNoAtomsInMolecule(i);
      
      SGrid<real> gMinCoord = prgapAtomPdb[0].getPose();
      SGrid<real> gMaxCoord = prgapAtomPdb[0].getPose();
      fMaxRadius       = prgapAtomPdb[0].getRadius();        
      for (integer j = 1; j < iAtomNum; j++)
      {
         gMinCoord = optMin<real>(gMinCoord,prgapAtomPdb[j].getPose());
         gMaxCoord = optMax<real>(gMaxCoord,prgapAtomPdb[j].getPose());
         fMaxRadius = max(fMaxRadius,prgapAtomPdb[j].getRadius());
      }
         
      tmpExtrema.nMin = gMinCoord; tmpExtrema.nMax = gMaxCoord;
      prgfeExtrema.push_back(tmpExtrema);
   }
   
   
   //------------------------------ extrm ---------------------------//
   // find extrema and calculate scale according to them and to the percent box fill
   fgMinCoordinate.nX = 6000.0; fgMinCoordinate.nY = 6000.0; fgMinCoordinate.nZ = 6000.0;
   
   fgMaxCoordinate.nX =-6000.0; fgMaxCoordinate.nY =-6000.0; fgMaxCoordinate.nZ =-6000.0;
   
   for (integer i = 0; i < iAtomNum; i++)
   {
      fgMinCoordinate = optMin<real>(fgMinCoordinate,prgapAtomPdb[i].getPose()-prgapAtomPdb[i].getRadius());
      fgMaxCoordinate = optMax<real>(fgMaxCoordinate,prgapAtomPdb[i].getPose()+prgapAtomPdb[i].getRadius());
   }
   
   fgGeometricCenter = (fgMinCoordinate + fgMaxCoordinate)/2.0;
   
   //------------------------------- off ----------------------------//   
   if (bIsAcent) 
      fgBoxCenter = fgAcent;
   else
   {
      fgBoxCenter = fgGeometricCenter - fgOffCenter/fScale;
   
      if (1.0e-6 > abs(fgOffCenter.nX-999.0) || 1.0e-6 > abs(fgOffCenter.nX-777.0))
      {
         if (1.0e-6 > abs(fgOffCenter.nX-999.0))
         {
            cout << "modifying midpoints using frc input file \n";
            fgBoxCenter = pio->readFrcFile(strFrciFile,fgOffCenter,fScale);
         }
         else
         {
            cout << "modifying midpoints using fort.27 \n";
            fgBoxCenter = pio->readFrcFile(strCentFile,fgOffCenter,fScale);
         }
      } // ---------- end of if (1.0e-6 > abs(fgOffCenter-999.0) || 
        //            1.0e-6 > abs(fgOffCenter-777.0))
   } // ---------- end of if (bIsAcent) 

   fgCoordinateRange = fgMaxCoordinate - fgMinCoordinate;

   {
      SGrid<real> gVec1 = 2.0*optABS<real>(fgMaxCoordinate-fgBoxCenter);
      real fMaxVal1 = optMax<real>(gVec1);
      
      SGrid<real> gVec2 = 2.0*optABS<real>(fgMinCoordinate-fgBoxCenter);
      real fMaxVal2 = optMax<real>(gVec2);
   
      fMaxDimension = (fMaxVal1 > fMaxVal2) ? fMaxVal1 : fMaxVal2;
   }
   
   if (0 == iGrid)
   {
      if (1.0e-6 > abs(fScale-10000.0) )          fScale = 2.0;
      if (1.0e-6 > abs(fPercentageFill-10000.0) ) fPercentageFill = 80.0;
      iGrid = fScale*100.0/fPercentageFill*fMaxDimension;
   }
   else if (1.0e-6 > abs(fScale-10000.0) )
   {
      if (1.0e-6 > abs(fPercentageFill-10000.0) )
      {
         fScale          = 2.0;
         fPercentageFill = 100.0*fMaxDimension*fScale/(iGrid-1);
      }
      else
         fScale = (iGrid-1)*fPercentageFill/(100.0*fMaxDimension);   
   }
   else
      fPercentageFill = 100.0*fMaxDimension*fScale/(iGrid-1);

   if (0 == iGrid%2) iGrid += 1; 
   
   prgfMediaEps[0] = fEpsOut;
   
   if (bPdbUnformatIn && bUnformatPdbOut)
      CReadWriteUnformatPdb warning(bUnformatPdbOut); 
   
   if (bFrcUnformatIn && bUnformatFrcOut)
      CReadWriteUnformatFrc warning(bUnformatPdbOut);   
         
   
   SGrid<real> gLeftBndy  = fgBoxCenter - (1.0/fScale)*(iGrid+1)*0.5;
   SGrid<real> gRightBndy = fgBoxCenter + (1.0/fScale)*(iGrid+1)*0.5;
   if (optORLT(fgMinCoordinate,gLeftBndy) || optORGT(fgMaxCoordinate,gRightBndy))
      CSystemOutsideBox warning; 
                                
   // convert atom coordinates from angstroms to grid units
   // Added allocation of xn1 array in order to deal with different names in real (atpos) 
   // and dummy (xn1) arguments in following subroutines
   
   for (integer i = 0; i < iAtomNum; i++)
   {
      prgfgAtomCoordA.push_back( prgapAtomPdb[i].getPose() );
      prgfgAtomCoordG.push_back( (prgapAtomPdb[i].getPose()-fgBoxCenter)*fScale+(real)((iGrid+1)/2) );
   }
   
   // verify if dielectric is uniform 
   bUniformDielec = true;
   for (integer i = 0; i < iMediaNum; i++)
   {
      if (prgfMediaEps[i] != prgfMediaEps[i+1]) bUniformDielec = false;
   }
   
   // now pass uniformdiel to epsmak make the epsmap, and also a listing of boundary 
   // elements, and the second epsmap used for the molecular surface scaling   
   //prgiEpsMap.assign(iGrid*iGrid*iGrid,0); 
   //prgbDielecMap.assign(iGrid*iGrid*iGrid,false); 
   
   showParameters();

   pio.release(); //---------- smart pointer pointer pio is destroied after exiting this function

}

