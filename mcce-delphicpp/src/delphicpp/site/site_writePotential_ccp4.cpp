/*
 * site_writePotential_ccp4.cpp
 *
 *  Created on: Feb 26, 2014
 *      Author: chuan
 */

#include "site.h"

void CSite::writePotential_ccp4(vector<real>& phimapIn)
{
   cout << "\nwriting potential map in CCP4 format\n\n";
   cout << "potential map written to file " << strPhiFile << endl << endl;

   integer igrid = iGrid;
   int mode = 2,ncstart = 1,nrstart = 1,nsstart = 1,nx = iGrid-1,ny = iGrid-1,nz = iGrid-1;
   real xlen = (iGrid-1)/fScale,ylen = (iGrid-1)/fScale,zlen = (iGrid-1)/fScale;
   real alpha = 90.0,beta = 90.0,gamma = 90.0;
   int mapc = 1,mapr = 2,maps = 3;
   real minim,maxim,somma,average;
   int ispg = 1, nsymbt = 1, lskflg = 0;
   real fzero = 0.0;
   int izero = 0;
   char map[] = "MAP ";
   int machst = 1, nlabl = 0;
   real arms = 0.0;

   ofstream ofPhiStream(strPhiFile.c_str(),ios::binary); int formatflag = 0; //unformatted
   ofPhiStream.write(reinterpret_cast<char*>(&igrid),  sizeof(integer)); // NC
   ofPhiStream.write(reinterpret_cast<char*>(&igrid),  sizeof(integer)); // NR
   ofPhiStream.write(reinterpret_cast<char*>(&igrid),  sizeof(integer)); // NS
   ofPhiStream.write(reinterpret_cast<char*>(&mode),   sizeof(int));     // MODE
   ofPhiStream.write(reinterpret_cast<char*>(&ncstart),sizeof(int));     // NCSTART
   ofPhiStream.write(reinterpret_cast<char*>(&nrstart),sizeof(int));     // NRSTART
   ofPhiStream.write(reinterpret_cast<char*>(&nsstart),sizeof(int));     // NSSTART
   ofPhiStream.write(reinterpret_cast<char*>(&nx),     sizeof(int));     // NX
   ofPhiStream.write(reinterpret_cast<char*>(&ny),     sizeof(int));     // NY
   ofPhiStream.write(reinterpret_cast<char*>(&nz),     sizeof(int));     // NZ
   ofPhiStream.write(reinterpret_cast<char*>(&xlen),   sizeof(real));    // X-LENGTH
   ofPhiStream.write(reinterpret_cast<char*>(&ylen),   sizeof(real));    // Y-LENGTH
   ofPhiStream.write(reinterpret_cast<char*>(&zlen),   sizeof(real));    // Z-LENGTH
   ofPhiStream.write(reinterpret_cast<char*>(&alpha),  sizeof(real));    // ALPHA
   ofPhiStream.write(reinterpret_cast<char*>(&beta),   sizeof(real));    // BETA
   ofPhiStream.write(reinterpret_cast<char*>(&gamma),  sizeof(real));    // GAMMA
   ofPhiStream.write(reinterpret_cast<char*>(&mapc),   sizeof(int));     // MAPC
   ofPhiStream.write(reinterpret_cast<char*>(&mapr),   sizeof(int));     // MAPR
   ofPhiStream.write(reinterpret_cast<char*>(&maps),   sizeof(int));     // MAPS

   minim = 10000.0; maxim = -10000.0; somma = 0.0;

   for (vector<real>::iterator it = phimapIn.begin(); it != phimapIn.end(); ++it)
   {
      if (minim > *it) minim = *it;
      if (maxim < *it) maxim = *it;
      somma += *it;
   }
   average = somma/(iGrid*iGrid*iGrid);

   ofPhiStream.write(reinterpret_cast<char*>(&minim),  sizeof(real));    // amin
   ofPhiStream.write(reinterpret_cast<char*>(&maxim),  sizeof(real));    // amax
   ofPhiStream.write(reinterpret_cast<char*>(&average),sizeof(real));    // amean
   ofPhiStream.write(reinterpret_cast<char*>(&ispg),   sizeof(int));     // ispg
   ofPhiStream.write(reinterpret_cast<char*>(&nsymbt), sizeof(int));     // nsymbt
   ofPhiStream.write(reinterpret_cast<char*>(&lskflg), sizeof(int));     // lskflg
   for (int i = 0; i < 9; i++)                                           // skwmat(3,3)
      ofPhiStream.write(reinterpret_cast<char*>(&izero),sizeof(int));
   for (int i = 0; i < 3; i++)                                           // skwtrn(3),future use
      ofPhiStream.write(reinterpret_cast<char*>(&fzero),sizeof(real));
   for (int i = 0; i < 15; i++)                                          // 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
      ofPhiStream.write(reinterpret_cast<char*>(&izero),sizeof(int));
   ofPhiStream.write(map,sizeof(map));                                   // 'MAP '
   ofPhiStream.write(reinterpret_cast<char*>(&machst), sizeof(int));     // MACHST
   ofPhiStream.write(reinterpret_cast<char*>(&arms),   sizeof(real));    // ARMS
   ofPhiStream.write(reinterpret_cast<char*>(&nlabl),  sizeof(int));     // NLABL
   for (int i = 0; i < 200; i++)
      ofPhiStream.write(reinterpret_cast<char*>(&izero),sizeof(int));

   writePhiMap(formatflag,phimapIn,ofPhiStream);

   ofPhiStream.close();
}
