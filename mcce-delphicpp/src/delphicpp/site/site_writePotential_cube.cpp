/*
 * site_writePotential_cube.cpp
 *
 *  Created on: Feb 26, 2014
 *      Author: chuan
 */

#include "site.h"

void CSite::writePotential_cube()
{
   cout << " potential map in cube format written to file " << strPhiFile << endl;

   real coeff = 0.5291772108, stepsize = 1.0/fScale;
   SGrid<real> origin = (fgBoxCenter-stepsize*(iGrid-1)/2.0)/coeff;

   ofstream ofPhiStream(strPhiFile.c_str());

   ofPhiStream << fixed << setprecision(6);

   ofPhiStream << "qdiffxs4 with an improved surfacing routine\n";
   ofPhiStream << "Gaussian cube format phimap\n";
   ofPhiStream << setw(5) << right << 1 << setw(14) << right << origin.nX << setw(14) << right << origin.nY << setw(14) << right << origin.nZ << endl;
   ofPhiStream << setw(5) << right << iGrid << setw(14) << right << stepsize/coeff << setw(14) << right << 0.0 << setw(14) << right << 0.0 << endl;
   ofPhiStream << setw(5) << right << iGrid << setw(14) << right << 0.0 << setw(14) << right << stepsize/coeff << setw(14) << right << 0.0 << endl;
   ofPhiStream << setw(5) << right << iGrid << setw(14) << right << 0.0 << setw(14) << right << 0.0 << setw(14) << right << stepsize/coeff << endl;
   ofPhiStream << setw(5) << right << 1 << setw(14) << right << 0.0 << setw(14) << right << 0.0 << setw(14) << right << 0.0 << setw(14) << right << 0.0 << endl;

   ofPhiStream.unsetf(ios_base::floatfield); // return to ofPhiStream default notation

   ofPhiStream.precision(5);

   for (int i = 0; i < iGrid; i++)
   {
      for (int j = 0; j < iGrid; j++)
      {
         for (int k = 0; k < iGrid; k++)
         {
            ofPhiStream << scientific << setw(13) << right << phimap[k][j][i];
         }
         ofPhiStream << endl;
      }
   }

   ofPhiStream.close();
}
