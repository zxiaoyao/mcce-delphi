#include "delphi_datamarshal.h"

//-----------------------------------------------------------------------//
void CDelphiDataMarshal::showParameters() const
{
   cout << fixed; // set the floatfield format flag for the str stream to fixed

   cout << "   " << endl;
   
   if (1 < iMediaNum) 
   {
      cout << "Attention, many dielectrics! Not all the surface charges are facing the solution!!" << endl;
   }

   cout << "Direct mapping of epsilon: (0/1)(n/y)   " << iDirectEpsMap << endl;
  
   cout << "time to read in and/or assign rad/chrg = "; pTimer->showElapse();

   // calcolo quante deblen di soluzione sono contenute nel box
   if (1000000 < fDebyeLength)
   {
      real fDebyeNum = (100.0/fPercentageFill-1.0)*fMaxDimension/fDebyeLength;
      cout << "Debye Lengths contained in the finite diff. box" << fDebyeNum << endl;
   }

   cout << "grid size                  :" << right << setw(10) << iGrid << endl;
   cout << "percent of box to be filled:" << right << setw(10) << fPercentageFill << endl;
   cout << "scale,in grids/A :" << right << setw(10) << fScale << endl;
   cout << "xmin,xmax     (A):" << right << setw(10) << fgMinCoordinate.nX << right << setw(10) << fgMaxCoordinate.nX << endl;
   cout << "ymin,ymax     (A):" << right << setw(10) << fgMinCoordinate.nY << right << setw(10) << fgMaxCoordinate.nY << endl;
   cout << "zmin,zmax     (A):" << right << setw(10) << fgMinCoordinate.nZ << right << setw(10) << fgMaxCoordinate.nZ << endl;
   cout << "x,y,z range   (A):" << right << setw(10) << fgCoordinateRange.nX << right << setw(10) << fgCoordinateRange.nY << right << setw(10) << fgCoordinateRange.nZ << endl;
   cout << "system geometric center in (A):" << right << setw(10) << fgGeometricCenter.nX << right << setw(10) << fgGeometricCenter.nY << right << setw(10) << fgGeometricCenter.nZ << endl;
   cout << "grid box is centered in (A)   :" << right << setw(10) << fgBoxCenter.nX << right << setw(10) << fgBoxCenter.nY << right << setw(10) << fgBoxCenter.nZ << endl;
   cout << "object centre offset (gu)     :" << right << setw(10) << fgOffCenter.nX << right << setw(10) << fgOffCenter.nY << right << setw(10) << fgOffCenter.nZ  << endl;
        
   if (bSolvePB)
   {
      cout << "outer dielectric              :" << right << setw(10) << fExDielec << endl;
    
      for (integer i = 1; i <= iMediaNum; i++)
      {
         real fEspInMedium = prgfMediaEps[i]*fEPKT;
         
         if (1.0 > fEspInMedium) throw CInvalidEpsInMedium(i);
         
         cout << "dielectric in medium number " << i << " :" 
              << right << setw(10) << fEspInMedium << endl;    
      }
      
      cout << "first kind salt concentration (M)   :" << right << setw(10) << rgfSalt[0] << endl;
      cout << "valences salt 1 are        " << left << setw(5) << rgiValence1[0] << "and" << right << setw(5) << rgiValence1[1] << endl;
           
      cout << "second kind salt concentration (M)   :" << right << setw(10) << rgfSalt[1] << endl;
      cout << "valences salt 2 are        " << left << setw(5) << rgiValence2[0] << "and" << right << setw(5) << rgiValence2[1] << endl;
      cout << "ionic strength (M)         :" << right << setw(10) << fIonStrength << endl;
      cout << "debye length (A)           :" << right << setw(10) << fDebyeLength << endl;
      cout << "absolute temperature (K)   :" << right << setw(10) << fTemper      << endl;
      cout << "ion exclusion radius (A)   :" << right << setw(10) << fIonRadius   << endl;
      cout << "probe radius facing water(A:" << right << setw(10) << rgfProbeRadius[0] << endl;
      cout << "probe radius, internal (A) :" << right << setw(10) << rgfProbeRadius[1] << endl;
      switch (iBndyType)
      {
         case 1: cout << "boundary conditions        :     zero\n";         break;
         case 2: cout << "boundary conditions        :     dipolar\n";      break;
         case 3: cout << "boundary conditions        :     focussing\n";    break;
         case 4: cout << "boundary conditions        :     coulombic\n";    break;
         case 5: cout << "boundary conditions        :     Voltage Drop\n"; break;
      }
      cout << "x,y,z periodic bc. and volt. drop flags :" << right << setw(6) << rgbPeriodicBndy[0] << right << setw(6) << rgbPeriodicBndy[1]
                                                          << right << setw(6) << rgbPeriodicBndy[2] << right << setw(6) << rgbPeriodicBndy[3]
														  << right << setw(6) << rgbPeriodicBndy[4] << right << setw(6) << rgbPeriodicBndy[5] << endl;
      
      if (rgbPeriodicBndy[3] || rgbPeriodicBndy[4] || rgbPeriodicBndy[5]) 
         cout << "Voltage drops along x,y,z :" << right << setw(10) << fgPotentialDrop.nX << right << setw(10) << fgPotentialDrop.nY << right << setw(10) << fgPotentialDrop.nZ << endl;
    
      if (bAutoConverge)
      {
         if (0.0 < fGridConverge)
            cout << "convergence by grid energy :" << right << setw(10) << fGridConverge << " kt\n";
         else
            cout << "# of linear iterations     : automatic\n";        
      }
      else
         cout << "# of linear iterations     :" << right << setw(10) << iLinIterateNum << endl;
      
      if (0.0 < fRmsc || 0.0 < fMaxc)
      {
         cout << "convergence by rms  change :" << right << setw(10) << fRmsc << " kt\n";
         cout << "convergence by max  change :" << right << setw(10) << fMaxc << " kt\n"; 
      }
      
      if (1.0e-6 > fIonStrength && 0 < iNonIterateNum)
         cout << "ionic strength=0 ==> only linear iterations \n";
      else
      {
         cout << "# of non-linear iterations :" << right << setw(6) << iNonIterateNum << endl;
         cout << "non-linear energy calculat.:" << right << setw(6) << bNonlinearEng << endl;
         cout << "manual relaxation parameter:" << right << setw(6) << bManualRelaxParam << endl;
      }   
      
      cout << "ionic direct energy contribution:" << right << setw(6) << bIonsEng << endl;
      cout << "concentration map output   :" << right << setw(6) << bOutCrgDensity << endl;
      cout << "spherical charge distbn.   :" << right << setw(6) << bCrgInterplateType << endl;
      cout << "INSIGHT format output      :" << right << setw(6) << bBiosystemOut << endl;
      cout << "ionic direct energy contribution:" << right << setw(6) << bSiteOut << endl;
   } // ---------- end of if (bSolvePB)
   
   cout << "modified atom file output     : " << right << setw(6) << bModPdbOut << endl; 
   cout << "map file label                : " << rgcFileMap << endl;
   
   if (bPdbUnformatIn)  cout << " set to read  unformatted pdb file\n";
   if (bUnformatPdbOut) cout << " set to write unformatted pdb file\n";   
   if (bFrcUnformatIn)  cout << " set to read  unformatted frc.pdb file\n";
   if (bUnformatFrcOut) cout << " set to write unformatted frc.pdb file\n";
   if (!bLogGraph)      cout << " convergence graph turned off\n";
   if (!bLogPotential)  cout << " potential listings turned off\n";   
   
   if (10 != iIterateInterval || 1 != iConvergeFract)
   {
      cout << "convergence test interval is every" << right << setw(6) << iIterateInterval << " loops \n";
      cout << "testing" << right << setw(6) << 100/iConvergeFract << "% \n";      
   }

   cout << endl;
}
