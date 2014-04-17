/*
 * site_writePhiMap.cpp
 *
 *  Created on: Feb 26, 2014
 *      Author: chuan
 */

#include "site.h"

void CSite::writePhiMap(const int& formatflag,vector<real>& phimapIn,ofstream& ofFileStream)
{
   if (0 == phimapIn.size()) { CEmptyPhiMap warning(); return; }

   if (1 == formatflag) // formatted write
   {
      int i = 0;

      for (vector<real>::iterator it = phimapIn.begin(); it != phimapIn.end(); ++it)
      {
         i++;
         ofFileStream << *it << " ";
         if (iGrid == i) { i = 0; ofFileStream << endl; }
      }
   }
   else // unformatted (binary) write
   {
      real* prgfData = phimapIn.data();

      for (vector<real>::iterator it = phimapIn.begin(); it != phimapIn.end(); ++it)
      {
         ofFileStream.write(reinterpret_cast<char*>(prgfData),sizeof(real));
         prgfData++;
      }
   }
}
