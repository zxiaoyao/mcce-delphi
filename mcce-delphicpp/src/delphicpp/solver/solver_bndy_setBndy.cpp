/*
 * solver_bndy_setBndy.cpp
 *
 *  Created on: Feb 4, 2014
 *      Author: chuan
 */

#include "solver_fastSOR.h"

void CDelphiFastSOR::setBndy()
{
   real *** phimap = pdc->getKey_Ptr<real>("phimap",iGrid,iGrid,iGrid); // pointer to 3D phimap

   bool bSucessFail = false;

#ifdef VERBOSE
   cout << "\n setting boundary conditions\n\n";
#endif

   //----- phimap is initialized to zero for BNDCON == 1 (zero boundary condition)
   //prgfPhiMap.assign(iGrid*iGrid*iGrid,0.0);

   if (6 == iBndyType && !(bIonsEng && 0 == iNonIterateNum && 1.0e-6 < abs(fNetCrg))) iBndyType = 2;

   if (7 == iBndyType && !(bIonsEng && 0 == iNonIterateNum && 1.0e-6 < abs(fNetCrg))) iBndyType = 4;

   switch(iBndyType)
   {
      case 1: // zero option
         bSucessFail = true; break;
      case 2: // quasi coulombic dipole option
         bSucessFail = isDipolarBndy(phimap); break;
      case 3: // focussing option-bc's come from a previous phimap
         bSucessFail = isFocusBndy(phimap); break;
      case 4: // a summation of the potential resulted from each point of charge
         bSucessFail = isCoulombBndy(phimap); break;
      case 5: // constant external field option
         throw CUnknownBndyCondition(iBndyType);
      case 6: // quasi coulombic modified dipole option
         throw CUnknownBndyCondition(iBndyType);
      case 7: // complete summation of the potential resulted from each point of charge
         throw CUnknownBndyCondition(iBndyType);
      default:
         throw CUnknownBndyCondition(iBndyType);
   }

   if (!bSucessFail) throw CSettingBndyError(iBndyType);

#ifdef VERBOSE
   integer iMidGrid = (iGrid + 1)/2;

   cout << " some initial phi values: \n";
   cout << " midg,midg,1; midg,midg,igrid : " << scientific << prgfPhiMap[0*iGrid*iGrid+(iMidGrid-1)*iGrid+(iMidGrid-1)] << "   "
        << prgfPhiMap[(iGrid-1)*iGrid*iGrid+(iMidGrid-1)*iGrid+(iMidGrid-1)] << endl;
   cout << " midg,1,midg; midg,igrid,midg : " << scientific << prgfPhiMap[(iMidGrid-1)*iGrid*iGrid+0*iGrid+(iMidGrid-1)] << "   "
        << prgfPhiMap[(iMidGrid-1)*iGrid*iGrid+(iGrid-1)*iGrid+(iMidGrid-1)] << endl;
   cout << " 1,midg,midg; igrid,midg,midg : " << scientific << prgfPhiMap[(iMidGrid-1)*iGrid*iGrid+(iMidGrid-1)*iGrid+0] << "   "
        << prgfPhiMap[(iMidGrid-1)*iGrid*iGrid+(iMidGrid-1)*iGrid+(iGrid-1)] << endl;
#endif


#ifdef DEBUG_DELPHI_SOLVER_SETBC
   {
      string strTestFile = "test_setbc.dat";
      ofstream ofTestStream(strTestFile.c_str());
      ofTestStream << boolalpha;
      ofTestStream << fixed << setprecision(7);

      int i = 0;

      for (int iz = 0; iz < iGrid; iz++)
      {
         for (int iy = 0; iy < iGrid; iy++)
         {
            for (int ix = 0; ix < iGrid; ix++)
            {
               ofTestStream << setw(3)  << right << ix+1 << setw(3) << right << iy+1 << setw(3) << right << iz+1
                            << setw(11) << right << prgfPhiMap[i] << endl; //phimap[iz][iy][ix] << endl;
               i++;
            }
         }
      }

      ofTestStream.close();
   }
#endif // DEBUG_DELPHI_SOLVER

}