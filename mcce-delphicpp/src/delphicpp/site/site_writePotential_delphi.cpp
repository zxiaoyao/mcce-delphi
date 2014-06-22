/*
 * site_writePotential_delphi.cpp
 *
 *  Created on: Feb 26, 2014
 *      Author: chuan
 */

#include "site.h"

void CSite::writePotential_delphi()
{
   cout << "\nwriting potential map in DELPHI format\n\n";
   cout << "potential map written to file " << strPhiFile << endl << endl;

   char nxtlbl[10],head[21] = "now starting phimap ",tail[16] = " end of phimap ";
   real scalesingle = fScale;
   SGrid<real> oldmidsingle = fgBoxCenter;
   integer igrid = iGrid;

   ofstream ofPhiStream(strPhiFile.c_str(),ios::binary);

   if (bOutCrgDensity && (0 != fIonStrength))
      strcpy(nxtlbl,"concentrat");
   else
      strcpy(nxtlbl,"potential ");

   ofPhiStream.write(head,21);
   ofPhiStream.write(nxtlbl,10);
   ofPhiStream.write(rgcFileMap,54);
   {
      real* prgfData = prgfPhiMap.data();

      for (vector<real>::iterator it = prgfPhiMap.begin(); it != prgfPhiMap.end(); ++it)
      {
         ofPhiStream.write(reinterpret_cast<char*>(prgfData),sizeof(real));
         prgfData++;
      }
   }
   ofPhiStream.write(tail,16);
   ofPhiStream.write(reinterpret_cast<char*>(&scalesingle),sizeof(real));
   ofPhiStream.write(reinterpret_cast<char*>(&oldmidsingle),sizeof(SGrid<real>));
   ofPhiStream.write(reinterpret_cast<char*>(&igrid),sizeof(real));

   ofPhiStream.close();
}
