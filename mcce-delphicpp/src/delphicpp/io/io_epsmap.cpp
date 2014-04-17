/*
 * io_epsmap.cpp
 *
 *  Created on: Feb 4, 2014
 *      Author: chuan li
 *
 * description:
 *  kim sharp/9 feb 88
 *  reformats epsilon array epsmap to compact array (MKG format)
 *     old format: epsmap(65,65,65,3) real*4
 *     new format: neps(5,65,65,3) integer*2
 *  where first index 1-65 now compressed into 1-5 plus offset into 16 bit words
 *  compact format also contains oldmid, the center of the protein in real coordinates
 *  compaction is effected by storing real eps (which take values of 0. and 1.) as bits in a 16 bit word access is
 *  via pointers idimx and ioffset thus x arrary indices of reps 0-15 -> word 1, 16-31 -> word 2 etc
 */

#include "io.h"

void CIO::writeEpsMap(const integer& iAtomNumIn,const integer& iObjectNumIn,const integer& iGrid,const real& fScale,
                      const SGrid<real>& fgBoxCenter, const vector< SGrid<integer> >& prgigEpsMap,const vector<bool>& prgbDielecMap,
                      const string& strEpsFile)
{
   iAtomNum = iAtomNumIn; iObjectNum = iObjectNumIn;

   const integer iMaxWord = iGrid/16+1,iEpsDim = iAtomNum+iObjectNum+2;

   //----- LOCAL
   vector<integer> idimx,ip2,ioffset;
   integer ix,iy,iz,iw,i,k1;
   SGrid<integer> j123;

   int kmap = 1;
   real scale = fScale;
   SGrid<real> oldmid = fgBoxCenter;

   cout << " setting up pointers...\n";
   for (ix = 0; ix < iGrid; ix++)
   {
      idimx.push_back( (ix+1)/16+1 );
      ioffset.push_back( (ix+1)%16 );

      if (15 != ix%16) ip2.push_back( (integer)pow(2.0,(ix+1)%16) );
      else             ip2.push_back( (integer)-pow(2.0,15.0) );
   }

   cout << " clearing bits...\n";
   SGrid<integer> *** neps = new SGrid<integer> ** [iGrid];
   for (iz = 0; iz < iGrid; iz++)
   {
      neps[iz] = new SGrid<integer> * [iGrid];
      for (iy = 0; iy < iGrid; iy++)
      {
         neps[iz][iy] = new SGrid<integer> [iMaxWord];
         for (i = 0; i < iMaxWord; i++)
         {
            neps[iz][iy][i].nX = 0; neps[iz][iy][i].nY = 0; neps[iz][iy][i].nZ = 0;
         }
      }
   }

   integer *** keps = new integer ** [iGrid];
   for (iz = 0; iz < iGrid; iz++)
   {
      keps[iz] = new integer * [iGrid];
      for (iy = 0; iy < iGrid; iy++)
      {
         keps[iz][iy] = new integer [iMaxWord];
         for (i = 0; i < iMaxWord; i++)
         {
            keps[iz][iy][i] = 0;
         }
      }
   }

   cout << " generating compact fine epsilon array...\n";
   for (iz = 0; iz < iGrid; iz++)
   {
      for (ix = 0; ix < iGrid; ix++)
      {
         i = idimx[ix];
         for (iy = 0; iy < iGrid; iy++)
         {
            j123.nX = 0; j123.nY = 0; j123.nZ = 0; k1 = 0;

            iw = iz*iGrid*iGrid + iy*iGrid + ix;
            if (0 != prgigEpsMap[iw].nX/iEpsDim) j123.nX = ip2[ix];
            if (0 != prgigEpsMap[iw].nY/iEpsDim) j123.nY = ip2[ix];
            if (0 != prgigEpsMap[iw].nZ/iEpsDim) j123.nZ = ip2[ix];
            if (prgbDielecMap[iw])               k1      = ip2[ix];

            neps[iz][iy][i-1] = neps[iz][iy][i-1] + j123;
            keps[iz][iy][i-1] = keps[iz][iy][i-1] + k1;
         }
      }
   }

   cout << " writing to compact epsilon file\n\n";
   cout << "dielectric map written to file" << strEpsFile << "\n\n";

   ofstream ofEpsFileStream(strEpsFile.c_str(),ios::binary);
   ofEpsFileStream.write(reinterpret_cast<char*>(&kmap),sizeof(kmap));
   ofEpsFileStream.write(reinterpret_cast<char*>(&scale),sizeof(scale));
   ofEpsFileStream.write(reinterpret_cast<char*>(&oldmid),sizeof(oldmid));

   for (iz = 0; iz < iGrid; iz++)
   {
      for (iy = 0; iy < iGrid; iy++)
      {
         for (i = 0; i < iMaxWord; i++)
         {
            ofEpsFileStream.write(reinterpret_cast<char*>(&neps[iz][iy][i]),sizeof(SGrid<integer>));
         }
      }
   }

   for (iz = 0; iz < iGrid; iz++)
   {
      for (iy = 0; iy < iGrid; iy++)
      {
         for (i = 0; i < iMaxWord; i++)
         {
            ofEpsFileStream.write(reinterpret_cast<char*>(&keps[iz][iy][i]),sizeof(integer));
         }
      }
   }

   ofEpsFileStream.close();
}

