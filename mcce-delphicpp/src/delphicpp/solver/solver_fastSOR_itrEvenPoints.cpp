/*
 * solver_fastSOR_itrEvenPoints.cpp
 *
 *  Created on: Feb 7, 2014
 *      Author: chuan
 */

#include "solver_fastSOR.h"

void CDelphiFastSOR::itrEvenPoints(const int& forWhom)
{
   integer n,ix,iy,iz;
   integer star,fin;
   real temp1,temp2,temp3,temp4;
   integer itemp1,itemp2,itemp3,itemp4;

   /* the following loops are about four times faster than the original loop over all grid points for
    * several reasons, the biggest being that we are only solving laplace's equation (unless salt is present),
    * which numerically much simpler, hence faster. we put all we leave out, back in below, ending up with
    * an equivalent calculation, but much faster.
    */
   if (1.0e-6 < abs(fIonStrength))  //----- the main loop is as below:
   {
      for (n = 1; n < iGrid-1; n++)
      {
         star = sta2[n]; fin = fi2[n];
         for (ix = star; ix <= fin; ix++)
         {
            temp1 = phimap1[ix-1]         + phimap1[(ix-1)+1];
            temp2 = phimap1[(ix-1)+lat2]  + phimap1[(ix-1)-lat1];
            temp3 = phimap1[(ix-1)+long2] + phimap1[(ix-1)-long1];
            phimap2[ix-1] = phimap2[ix-1]*om1 + (qmap2[ix-1]+temp1+temp2+temp3)*prgfSaltMap2[ix-1];
         }
      }
   }
   else //----- if there is no salt then the main loop is executed without sf saving about 15% in execution time
   {
      for (n = 1; n < iGrid-1; n++)
      {
         star = sta2[n]; fin = fi2[n];
         for (ix = star; ix <= fin; ix++)
         {
            temp1 = phimap1[ix-1]         + phimap1[(ix-1)+1];
            temp2 = phimap1[(ix-1)+lat2]  + phimap1[(ix-1)-lat1];
            temp3 = phimap1[(ix-1)+long2] + phimap1[(ix-1)-long1];
            phimap2[ix-1] = phimap2[ix-1]*om1 + (temp1+temp2+temp3)*sixth;
         }
      }
   }

   /*
    * first we add back the dielectric boundary points, by recalculating them individually. note this is still
    * vectorised by means of a gathering load by the compiler.
    */
   for (n = iDielecBndyEven; n < iDielecBndyOdd; n++)
   {
      ix = prgiBndyDielecIndex[n];
      temp1 = phimap1[ix-1]*prgfBndyDielec[n][0]         + phimap1[ix]*prgfBndyDielec[n][1];
      temp2 = phimap1[(ix-1)-lat1]*prgfBndyDielec[n][2]  + phimap1[(ix-1)+lat2]*prgfBndyDielec[n][3];
      temp3 = phimap1[(ix-1)-long1]*prgfBndyDielec[n][4] + phimap1[(ix-1)+long2]*prgfBndyDielec[n][5];
      phimap2[ix-1] += temp1 + temp2 + temp3;
   }

   /*
    * Now reset boundary values altered in above loops.
    */
   star = (iGrid+2)/2; fin = (iGrid*(iGrid-1)-1)/2; iy = iGrid*(iGrid+2)/2-iGrid+1;
   for (n = 0; n < fin-star+1; n++)
   {
      iy = iy+iGrid; phimap2[iy-1] = bndx3[n]; phimap2[iy+((iGrid+1)/2-1)-1] = bndx4[n];
   }

   /*
    * next we add back an adjustment to all the charged grid points due to the charge assigned. the compiler
    * directive just reassures the vector compiler that all is well as far as recurrence is concerned, i.e. it
    * would think there is a recurrence below, where as in fact there is none.
    */
   if (0 != forWhom)
   {
      for (n = iCrgedGridEven; n < iCrgedGridSum; n++)
      {
         ix = prgiCrgPose[n]; phimap2[ix-1] += prgfCrgValA[n];
      }
   }

   /*
    * if periodic boundary condition option, force periodicity using wrap around update of boundary values:
    *    2nd slice-->last
    *    last-1 slice-->first
    */
   if (rgbPeriodicBndy[2]) //----- z periodicity
   {
      for (iz = 1; iz < (iGrid-2)*(iGrid-2); iz += 2)
      {
         temp1 = ibndz[iz];      itemp1 = (integer)temp1;
         temp2 = temp1 + idif2z; itemp2 = (integer)temp2;
         temp3 = temp2 + inc2za; itemp3 = (integer)temp3;
         temp4 = temp1 + inc2zb; itemp4 = (integer)temp4;
         phimap2[itemp1-1] = phimap1[itemp2-1];
         phimap2[itemp3-1] = phimap1[itemp4-1];
      }
   }

   if (rgbPeriodicBndy[1]) //----- y periodicity
   {
      for (iy = 1; iy < (iGrid-2)*(iGrid-2); iy += 2)
      {
         temp1 = ibndz[iy];      itemp1 = (integer)temp1;
         temp2 = temp1 + idif2y; itemp2 = (integer)temp2;
         temp3 = temp2 + inc2ya; itemp3 = (integer)temp3;
         temp4 = temp1 + inc2yb; itemp4 = (integer)temp4;
         phimap2[itemp1-1] = phimap1[itemp2-1];
         phimap2[itemp3-1] = phimap1[itemp4-1];
      }
   }

   if (rgbPeriodicBndy[0]) //----- x periodicity
   {
      for (ix = 1; ix < (iGrid-2)*(iGrid-2); ix += 2)
      {
         temp1 = ibndx[ix];      itemp1 = (integer)temp1;
         temp2 = temp1 + idif2x; itemp2 = (integer)temp2;
         temp3 = temp2 + inc2xa; itemp3 = (integer)temp3;
         temp4 = temp1 + inc2xb; itemp4 = (integer)temp4;
         phimap2[itemp1-1] = phimap1[itemp2-1];
         phimap2[itemp3-1] = phimap1[itemp4-1];
      }
   }
}
