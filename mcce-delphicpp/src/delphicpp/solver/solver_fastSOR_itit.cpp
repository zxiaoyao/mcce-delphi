/*
 * solver_fastSOR_itit.cpp
 *
 *  Created on: Feb 10, 2014
 *      Author: chuan
 */

#include "solver_fastSOR.h"

void CDelphiFastSOR::itit()
{
   real rmsch,rmsch2,rmxch,rmxch2;
   int itr,ires;
   real grden,grdn[5] = {0.0,0.0,0.0,0.0,0.0};
   integer ix,iy,iz;
   real maxres = (fRmsc>fMaxc)?fRmsc:fMaxc; maxres = (maxres>fGridConverge)?maxres:fGridConverge;
   vector<real> rmsl(nxran,0.0),rmaxl(nxran,0.0);

#ifdef VERBOSE
   if (0.0 < fGridConverge) cout << "  rms-change     max change    grid energy    #iterations" << endl;
   else                     cout << "  rms-change     max change       #iterations" << endl;
#endif

   if (0 == iConvergeFract) { iIterateInterval = 10; iConvergeFract = 1; }

   if (iIterateInterval > iLinIterateNum) iIterateInterval = iLinIterateNum;

   initOddEvenItr(1); // forWhom = 1

#ifdef DEBUG_DELPHI_SOLVER_ITIT
   {
      string strTestFile = "test_itit.dat";
      ofstream ofTestStream(strTestFile.c_str());
      ofTestStream << boolalpha;
      ofTestStream << fixed << setprecision(7);

      ix = 1;
      for (vector<integer>::iterator it = ibndx.begin(); it != ibndx.end(); ++it)
      {
         ofTestStream << "ibndx[" << setw(6) << right << ix << "] = " << setw(8) << right << *it << endl;
         ix++;
      }

      ix = 1;
      for (vector<integer>::iterator it = ibndy.begin(); it != ibndy.end(); ++it)
      {
         ofTestStream << "ibndy[" << setw(6) << right << ix << "] = " << setw(8) << right << *it << endl;
         ix++;
      }

      ix = 1;
      for (vector<integer>::iterator it = ibndz.begin(); it != ibndz.end(); ++it)
      {
         ofTestStream << "ibndz[" << setw(6) << right << ix << "] = " << setw(8) << right << *it << endl;
         ix++;
      }

      ix = 1;
      for (vector<real>::iterator it = bndx1.begin(); it != bndx1.end(); ++it)
      {
         ofTestStream << "bndx1[" << setw(6) << right << ix << "] = " << setw(11) << right << *it << endl;
         ix++;
      }

      ix = 1;
      for (vector<real>::iterator it = bndx2.begin(); it != bndx2.end(); ++it)
      {
         ofTestStream << "bndx2[" << setw(6) << right << ix << "] = " << setw(11) << right << *it << endl;
         ix++;
      }

      ix = 1;
      for (vector<real>::iterator it = bndx3.begin(); it != bndx3.end(); ++it)
      {
         ofTestStream << "bndx3[" << setw(6) << right << ix << "] = " << setw(11) << right << *it << endl;
         ix++;
      }

      ix = 1;
      for (vector<real>::iterator it = bndx4.begin(); it != bndx4.end(); ++it)
      {
         ofTestStream << "bndx4[" << setw(6) << right << ix << "] = " << setw(11) << right << *it << endl;
         ix++;
      }

      ix = 1;
      for (vector<real>::iterator it = phimap1.begin(); it != phimap1.end(); ++it)
      {
         ofTestStream << "phimap1[" << setw(6) << right << ix << "] = " << setw(11) << right << *it << endl;
         ix++;
      }

      ix = 1;
      for (vector<real>::iterator it = phimap2.begin(); it != phimap2.end(); ++it)
      {
         ofTestStream << "phimap2[" << setw(6) << right << ix << "] = " << setw(11) << right << *it << endl;
         ix++;
      }

      ofTestStream.close();
   }
#endif // DEBUG_DELPHI_SOLVER_ITIT

   itr = 1; ires = 0;
   do
   {
      rmsch = 0.0; rmxch = 0.0;

      /*
       * iterate over odd points
       */
      itrOddPoints(1); // forWhom = 1

      if (bFixedRelaxParam)
      {
         int itr2 = 2*itr-1;
         om3 = 1.0/(1.0-om2*fSpec*0.25);
         if (fZero > om1) om3 = 1.0/(1.0-om2*fSpec*0.5);
         om4 = om3/om2; om2 = om3; om1 = 1.0-om2;

         if (0.0 < fIonStrength)
         {
            if (1 == itr2%2)
            {
               for (vector<real>::iterator it = prgfSaltMap1.begin(); it != prgfSaltMap1.end(); ++it)
                  *it = (*it)*om4;
            }
            else
            {
               for (vector<real>::iterator it = prgfSaltMap2.begin(); it != prgfSaltMap2.end(); ++it)
                  *it = (*it)*om4;
            }
         }

         for (vector<real>::iterator it = prgfCrgValA.begin(); it != prgfCrgValA.end(); ++it)
            *it = (*it)*om4;

         for (integer iy = 0; iy < iDielecBndyOdd; iy++)
            for (integer ix = 0; ix < 6; ix++)
               prgfBndyDielec[iy][ix] = prgfBndyDielec[iy][ix]*om4;

         sixth = sixth*om4;
      }

#ifdef DEBUG_DELPHI_SOLVER_ITIT
      if (1 == itr)
      {
         string strTestFile = "test_itit.dat";
         ofstream ofTestStream(strTestFile.c_str());
         ofTestStream << boolalpha;
         ofTestStream << fixed << setprecision(7);

         ix = 1;
         for (vector<real>::iterator it = phimap1.begin(); it != phimap1.end(); ++it)
         {
            ofTestStream << "phimap1[" << setw(6) << right << ix << "] = " << setw(11) << right << *it << endl;
            ix++;
         }

         ix = 1;
         for (vector<real>::iterator it = phimap2.begin(); it != phimap2.end(); ++it)
         {
            ofTestStream << "phimap2[" << setw(6) << right << ix << "] = " << setw(11) << right << *it << endl;
            ix++;
         }

         ofTestStream.close();
      }
#endif // DEBUG_DELPHI_SOLVER_ITIT

      /*
       * Next update phimap2 using the new phimap1
       */
      itrEvenPoints(1); // forWhom = 1

      if (bFixedRelaxParam)
      {
         int itr2 = 2*itr;
         om3 = 1.0/(1.0-om2*fSpec*0.25);
         if (fZero > om1) om3 = 1.0/(1.0-om2*fSpec*0.5);
         om4 = om3/om2; om2 = om3; om1 = 1.0-om2;

         if (0.0 < fIonStrength)
         {
            if (1 == itr2%2)
            {
               for (vector<real>::iterator it = prgfSaltMap1.begin(); it != prgfSaltMap1.end(); ++it)
                  *it = (*it)*om4;
            }
            else
            {
               for (vector<real>::iterator it = prgfSaltMap2.begin(); it != prgfSaltMap2.end(); ++it)
                  *it = (*it)*om4;
            }
         }

         for (vector<real>::iterator it = prgfCrgValA.begin(); it != prgfCrgValA.end(); ++it)
            *it = (*it)*om4;

         for (integer iy = 0; iy < iDielecBndyOdd; iy++)
            for (integer ix = 0; ix < 6; ix++)
               prgfBndyDielec[iy][ix] = prgfBndyDielec[iy][ix]*om4;

         sixth = sixth*om4;
      }

#ifdef DEBUG_DELPHI_SOLVER_ITIT
      if (1 == itr)
      {
         string strTestFile = "test_itit.dat";
         ofstream ofTestStream(strTestFile.c_str());
         ofTestStream << boolalpha;
         ofTestStream << fixed << setprecision(7);

         ix = 1;
         for (vector<real>::iterator it = phimap1.begin(); it != phimap1.end(); ++it)
         {
            ofTestStream << "phimap1[" << setw(6) << right << ix << "] = " << setw(11) << right << *it << endl;
            ix++;
         }

         ix = 1;
         for (vector<real>::iterator it = phimap2.begin(); it != phimap2.end(); ++it)
         {
            ofTestStream << "phimap2[" << setw(6) << right << ix << "] = " << setw(11) << right << *it << endl;
            ix++;
         }

         ofTestStream.close();
      }
#endif // DEBUG_DELPHI_SOLVER_ITIT

      /*
       * we also save time by only checking convergence every 10 iterations, rather than every single iteration.
       * store phi2 in phi3 to compare against next iteration
       */
      if (iIterateInterval-1 == itr%iIterateInterval) // itr = 9,19,29,...
      {
         for (ix = 1; ix < iHalfGridNum; ix += iConvergeFract)
         {
            prgfPhiMap[ix] = phimap2[ix];
         }
      }

      if (0.0 < fGridConverge)
      {
         grden = 0.0;

         for(ix = 0; ix < iCrgedGridEven; ix++)
         {
            iy = prgiCrgPose[ix];
            grden += phimap1[iy-1]*prgfCrgValG[ix];
         }

         for(ix = iCrgedGridEven; ix < iCrgedGridSum; ix++)
         {
            iy = prgiCrgPose[ix];
            grden += phimap2[iy-1]*prgfCrgValG[ix];
         }

         grdn[itr%5] = grden/2.0;
         if (10 < itr)
         {
            bool igt = true;
            for (int i = 0; i < 5; i++)
               for (int j = 0; j < 5; j++)
                  if (abs(grdn[j]-grdn[i]) > fGridConverge) igt =false;
            if (igt)
            {
               cout << grdn[0] << " " << grdn[1] << " " << grdn[2] << " " << grdn[3] << " " << grdn[4] << endl;
               ires = 1;
            }
         }
      }

      if (0 == itr%iIterateInterval || 1 == ires) //----- check to see if accuracy is sufficient
      {
         real rnorm2=0.0, temp2;

         for (ix = 1; ix < iHalfGridNum; ix += iConvergeFract)
         {
            temp2   = prgfPhiMap[ix] - phimap2[ix];
            rnorm2 += temp2*temp2;
            rmxch   = max(rmxch,abs(temp2));
         }

         rmsch   = sqrt((real)iConvergeFract*rnorm2/((iGrid-2)*(iGrid-2)*(iGrid-2)));
         //rnormch = sqrt(rnorm2);
         rmsch2  = rmsch;
         rmxch2  = rmxch;

#ifdef VERBOSE
         if (0.0 < fGridConverge)
            cout << scientific << rmsch2 << "  "  << rmxch2 << "  " << grden << "  at  " << setw(5) << left << itr << " iterations\n";
         else
            cout << scientific << rmsch2 << "  "  << rmxch2 << "  at  " << setw(5) << left << itr << " iterations\n";
#endif

         if (fRmsc > rmsch || fMaxc > rmxch) ires = 1;

         if (bLogGraph)
         {
            int ibin;
            for (int j = itr-9; j <= itr; j++)
            {
               ibin = (j-1)*(60-1)/(iLinIterateNum-1)+1;
               rmsl[ibin-1]  = rmsch;
               rmaxl[ibin-1] = rmxch;
            }
         }
      }

      itr++;

      /*
       * check to see if accuracy is sufficient
       */
      if (1.0e-7 > maxres)
      {
         if (iLinIterateNum >= itr && 0 == ires)
            continue;
         else
            break;
      }
      else
      {
         if ((iLinIterateNum >= itr || bAutoConverge) && (0 == ires))
            continue;
         else
            break;
      }
   } while(true);

   postItr(rmaxl,rmsl);

   /*
    * code phimap corner, for use in transference from irises to convex and via versa
    */
   {
      real ap1,ap2,ap3,ap4;
      ap1 = prgfPhiMap[0]; ap2 = ap1*10000.0; ap3 = (int)ap2;
      if (0 < ap3) ap4 = (ap3+0.8)/10000.0;
      else         ap4 = (ap3-0.8)/10000.0;
      prgfPhiMap[0] = ap4;
   }

#ifdef DEBUG_DELPHI_SOLVER_ITIT
   {
      string strTestFile = "test_itit.dat";
      ofstream ofTestStream(strTestFile.c_str());
      ofTestStream << boolalpha;
      ofTestStream << fixed << setprecision(7);

      const real *** phimap = pdc->getKey_constPtr<real>("phimap",iGrid,iGrid,iGrid); // const pointer to 3D phimap
      for (iz = 0; iz < iGrid; iz++)
      {
         for (iy = 0; iy < iGrid; iy++)
         {
            for (ix = 0; ix < iGrid; ix++)
            {
               ofTestStream << "phimap[" << setw(6) << right << iz+1 << "," << setw(6) << right << iy+1 << ","
                            << setw(6) << right << ix+1 << "] = " << setw(12) << right << phimap[iz][iy][ix] << endl;
            }
         }
      }

      ofTestStream.close();
   }
#endif // DEBUG_DELPHI_SOLVER_ITIT
}
