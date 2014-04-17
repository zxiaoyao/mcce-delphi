/*
 * solver_fastSOR_run.cpp
 *
 *  Created on: Feb 10, 2014
 *      Author: chuan
 */

#include "solver_fastSOR.h"

void CDelphiFastSOR::run()
{
   validateInput();
   
   setDielecBndySaltMap();

   setCrg();

   cout << "iepsmp to db, and charging done at "; pTimer->showElapse();

   cout << "number of grid points assigned charge " << iCrgedGridSum << endl;

   if (bEpsOut) //----- write dielectric map
   {
      unique_ptr<CIO> pio(new CIO()); // smart unique_ptr
      pio->writeEpsMap(iAtomNum,iObjectNum,iGrid,fScale,fgBoxCenter,prgigEpsMap,prgbDielecMap,strEpsFile);
      pio.release();
   }

   //----- the order of calculateRelaxFactor and setBndy cannnot be reverted! prgfPhiMap is used
   //      as temporary array in calculateRelaxFactor...
   if (bSpectralRadius)
   {
      fSpec = fSpectralRadius;
      cout << "using entered value for relaxation of: " << fSpec << endl;
   }
   else
   {
      fSpec = calculateRelaxFactor();
   }

   int noit = (int)(7.8/log(1.0+sqrt(1-fSpec)));

   cout << "estimated iterations to convergence " << noit << endl;

   if (bAutoConverge) iLinIterateNum = noit;

   setBndy();

   cout << endl; cout << "setup time was "; pTimer->showElapse(); cout << endl;

   if (0.3 < (real)iCrgBndyGridNum/iBndyGridNum && bAutoConverge)
   {
      iLinIterateNum = iLinIterateNum*iCrgBndyGridNum/(0.3*iBndyGridNum);
      cout << "Re-estimated iterations now : " << iLinIterateNum;
   }

#ifdef VERBOSE
   cout << "now iterating on "; pTimer->showTime(); cout << endl;
#endif

   if (0 == iNonIterateNum || 1.0e-6 > fIonStrength)
      itit();
   else
   {
      if (50 < noit)
      {
         iLinIterateNum = noit/2;
         cout << "Re-estimated iterations now : " << iLinIterateNum;
      }

      real qfact = abs(fNetCrg)*(real)iCrgBndyGridNum/iBndyGridNum;

      nitit(qfact);
   }
}





































