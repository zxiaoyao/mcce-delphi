/*
 * site_writeSite.cpp
 *
 *  Created on: Feb 17, 2014
 *      Author: chuan
 *
 *  Description:
 *  write a file containing site potentials and/or fields and/or atom information. adapted april 92
 *  to enable flexible output/input possible fields include atom information, coordinates, charge,
 *  potential salt concentration, reaction potentials, coulombic potential, and fields the default
 *  of which is coordinates, charges, potentials and fields.
 *
 *  nqass    = number of assigned charges
 *  icount2b = number of boundary elements
 *  scspos   = position in angstroms of induced surface charges
 *  xn1      = positions of all atoms in angstroms,
 *  natm     = number of atoms
 */

#include "site.h"

void CSite::writeSite(const int& iisitsf)
{
   //---------------------------------------------------------------------------------------------//
   bool isita  = bAtomInSite,            isiti  = bSaltInSite,             isitmd = bMDInSite,            isitpot = bPotentialInSite,
        isitx  = bAtomCoordInSite,       isitq  = bCrgInSite,              isitf  = bFieldInSite,         isitp   = bGridPotentialInSite,
        isitr  = bReactPotentialInSite,  isitc  = bCoulombPotentialInSite, isitap = bAtomPotentialInSite, isitdeb = bDebyeFractionInSite,
        isitsf = bSurfCrgInSite,         isittf = bTotalForceInSite,       isitrf = bReactForceInSite,    isitt   = bTotalPotentialInSite,
        isitcf = bCoulombForceInSite,    iself  = bPDB2FRCInSite;

   //----- ifrm is true if ANY of the flags for special output have been set
   bool ifrm = isita || isitq || isitp || isitf || isitr || isitt || isitc || isitx || isiti || isitrf || isitcf || isitap ||
               isittf || isitdeb;
   bool isitmp1 = ifrm; ifrm = ifrm || isitsf;
   bool ofrm = true;

   if (isitmd || isitpot) {iFrcFormatOut = -1; ofrm = false;}

   if (!ifrm && (0 == iFrcFormatOut || 3 == iFrcFormatOut))
   {
      isitx = true; isitq = true; isitf = true; isitp = true;
   }

   switch (iFrcFormatOut)
   {
      case 1: isitx = true; isitq = true; isitr = true; isitc = true; break;
      case 2: isitx = true; isitq = true; isitr = true; break;
      case 3: ofrm = false; break;
   }

   string vrow(80,' '),datum(65,' '); int j = 0, k = 0;

   if (isita)
   {
      vrow.substr(j,15) = "ATOM DESCRIPTOR"; datum.substr(k,5) = "ATOM ";
      j += 20; k += 5;
   }

   if (isitx)
   {
      vrow.substr(j+4,24) = "ATOM COORDINATES (X,Y,Z)"; datum.substr(k,12) = "COORDINATES ";
      j += 30; k += 12;
   }

   if (isitq)
   {
      vrow.substr(j+3,6) = "CHARGE"; datum.substr(k,7) = "CHARGE ";
      j += 10; k += 7;
   }

   if (isitp)
   {
      vrow.substr(j+2,8) = "GRID PT."; datum.substr(k,11) = "POTENTIALS ";
      j += 10; k += 11;
   }

   if (isiti)
   {
      vrow.substr(j+1,8) = "SALT CON"; datum.substr(k,5) = "SALT ";
      j += 10; k += 5;
   }

   if (80 <= j)
   {
      isitr  = false; isitc  = false; isitap = false; isitdeb = false; isitf = false;
      isitsf = false; isittf = false; isitrf = false; isitcf  = false; isitt = false;
   }

   if (isitr)
   {
      vrow.substr(j,10) = " REAC. PT."; datum.substr(k,9) = "REACTION ";
      j += 10; k += 9;
   }

   if (80 <= j)
   {
                      isitc  = false; isitap = false; isitdeb = false; isitf = false;
      isitsf = false; isittf = false; isitrf = false; isitcf  = false; isitt = false;
   }

   if (isitc)
   {
      vrow.substr(j,10) = " COUL. POT"; datum.substr(k,10) = "COULOMBIC ";
      j += 10; k += 10;
   }

   if (80 <= j)
   {
                                      isitap = false; isitdeb = false; isitf = false;
      isitsf = false; isittf = false; isitrf = false; isitcf  = false; isitt = false;
   }

   if (isitap)
   {
      vrow.substr(j+2,8) = "ATOM PT."; datum.substr(k,11) = "ATOMIC PT. ";
      j += 10; k += 11;
   }

   if (80 <= j)
   {
                                                      isitdeb = false; isitf = false;
      isitsf = false; isittf = false; isitrf = false; isitcf  = false; isitt = false;
   }

   if (isitdeb)
   {
      vrow.substr(j+3,11) = "DEBFRACTION"; datum.substr(k,12) = "DEBFRACTION ";
      j += 14; k += 12;
   }

   if (60 <= j)
   {
                                                                       isitf = false;
      isitsf = false; isittf = false; isitrf = false; isitcf  = false; isitt = false;
   }

   if (isitf)
   {
      vrow.substr(j+4,25) = "GRID FIELDS: (Ex, Ey, Ez)"; datum.substr(k,7) = "FIELDS ";
      j += 30;
   }

   if (60 <= j)
   {
      isitsf = false; isittf = false; isitrf = false; isitcf  = false; isitt  = false;
   }

   if (isitrf)
   {
      vrow.substr(j+4,25) = "REAC. FORCE: (Rx, Ry, Rz)"; datum.substr(k,7) = "RFORCE ";
      j += 30;
   }

   if (60 <= j)
   {
      isitsf = false; isittf = false; isitcf  = false; isitt  = false;
   }

   if (isitcf)
   {
      vrow.substr(j+4,25) = "COUL. FORCE: (Cx, Cy, Cz)"; datum.substr(k,7) = "CFORCE ";
      j += 30;
   }

   if (60 <= j)
   {
      isitsf = false; isittf = false; isitt  = false;
   }

   if (isittf)
   {
      vrow.substr(j+4,25) = "TOTAL FORCE: (Tx, Ty, Tz)"; datum.substr(k,7) = "TFORCE ";
      j += 30;
   }

   if (70 <= j)
   {
      isitt  = false;
   }

   if (isitt)
   {
      vrow.substr(j+4,6) = " TOTAL"; datum.substr(k,6) = "TOTAL ";
      j += 10;
   }

   if (50 <= j) isitsf = false;

   if (isitsf)
   {
      vrow.substr(j+4,65) = "sCharge,    x          y       z       urf.E°n,surf. E[kT/(qA)]";
      datum.substr(k,35)  = "SCh, x, y, z, surf En, surf. E";
      j += 50;
   }

   //---------------------------------------------------------------------------------------------//
   /*
    * if site potentials required and unformatted read/write, skip during formatted frc file read/write can write unformatted frc.pdb
    */
   bool ifrm2 = false, iqass = true;
   ifstream ifFileStream;
   vector<bool> residsf(iResidueNum,false);

   if (!(isitmd || isitpot)) cout << "\nwriting potentials at given sites...\n";

   if (iself)
   {
      cout << "using the current pdb file\n";
      ifrm2 = true; iqass = false;
   }
   else
   {
      if (!isitpot)
      {
         ifFileStream.open(strFrciFile.c_str());
         if (!ifFileStream.is_open())
         {
            CUnknownInFrcFile warning(strFrciFile);
            ifFileStream.close();
            return;
         }
         else
         {
            cout << "coordinates, etc for potential output read from file " << strFrciFile << endl;
            ifrm2 = checkFileFormat(strFrciFile);
         }
      }
   }

   //----- if unformatted may not contain all the info needed for all options, i.e atom info
   if (!ifrm2 && isita)
   {
      CNoAtomInfo warning(strFrciFile);
      isita = false; iqass = false;
   }

   if (!ifrm2) iqass = false;

   if (!iself && !isitpot)
   {
      if (ifrm2) ifFileStream.open(strFrciFile.c_str());
      else       ifFileStream.open(strFrciFile.c_str(),ios::binary);

      if (!ifFileStream.is_open()) CUnknownInFrcFile warning(strFrciFile);
   }

   if (isitsf) //----- isitsf assumes ifrm2=.true.
   {
      ifstream ifFileStream15;
      string strLine,strHead;
      int iresnum;

      ifFileStream15.open(strFrciFile.c_str());
      if (!ifFileStream15.is_open())
      {
         CUnknownInFrcFile warning(strFrciFile);
      }
      else
      {
         cout << "coordinates, etc for potential output read from file " << strFrciFile << endl;
         while (!ifFileStream15.eof()) // loop D302
         {
            getline(ifFileStream15,strLine);
            strHead = strLine.substr(0,6);
            if (0 != strHead.compare("      ")) strHead = toUpperCase(strHead);
            if (0 != strHead.compare("ATOM  ") && 0 != strHead.compare("HETATM")) continue;
            iresnum = atoi(strLine.substr(23,4).c_str());
            residsf[iresnum-1] = true;
         }
      }
      ifFileStream15.close();
   }

   //---------------------------------------------------------------------------------------------//
   ofstream ofFileStream;

   if (ofrm) ofFileStream.open(strFrcFile.c_str());
   if(!(ofrm || isitmd || isitpot)) ofFileStream.open(strFrcFile.c_str(),ios::binary);

   if (!isitmd && !isitpot) cout << "potentials written to file " << strFrcFile << endl << endl;

   if (ofrm)
   {
      ofFileStream << "DELPHI SITE POTENTIAL FILE\n";
      ofFileStream << "grid size,percent fill:" << iGrid << " " << fPercentageFill << endl;
      ofFileStream << "outer diel. and first one assigned : " << fExDielec << " " << prgfMediaEps[1]*fEPKT << endl;
      ofFileStream << "ionic strength (M): " << fIonStrength << endl;
      ofFileStream << "ion excl., probe radii: " << fIonRadius << " " << rgfProbeRadius[0] << " " << rgfProbeRadius[1] << endl;
      ofFileStream << "linear, nolinear iterations: " << iLinIterateNum << " " << iNonIterateNum << endl;
      ofFileStream << "boundary condition: " << iBndyType << endl;
      ofFileStream << "Data Output: " << datum << endl;
      ofFileStream << "title: " << rgcFileMap << endl;
      ofFileStream << "\n\n";
      ofFileStream << vrow;
   }

   if (!ofrm && (!(isitmd || isitpot)))
   {
      ofFileStream << fixed << setprecision(4);

      string strLine;
      strLine = "DELPHI FRC FILE"; ofFileStream << strLine << endl;
      strLine = "FORMAT NUMBER=1"; ofFileStream << strLine << endl;
      strLine = "DATA="; strLine.append(datum); ofFileStream << strLine << endl;
      ofFileStream << setw(5) << right << iGrid << setw(10) << right << fPercentageFill << setw(10) << right << fExDielec
                   << setw(10) << right << fIonStrength << endl;
      for (int i = 1; i <= iMediaNum; i++)
         ofFileStream << "dielectric in medium nr. " << i << ": " << prgfMediaEps[i]*fEPKT << endl;
      ofFileStream << setw(10) << right << fIonRadius << setw(10) << right << rgfProbeRadius[0] << setw(10) << right << rgfProbeRadius[1]
                   << setw(5) << right << iLinIterateNum << setw(5) << right << iNonIterateNum << setw(5) << right << iBndyType << endl;

      ofFileStream.unsetf(ios_base::floatfield);
   }

   if (!iself && (isitrf || isitmd || isittf))
   {
      CCalcReactForceError warning;
      isitrf = false; isittf = false; isitmd = false;
   }

   vector< SGrid<real> > rfield;

   if (isitrf || isitmd || isittf)
   {
      if (1 == iMediaNum && 1.0e-6 > abs(prgfMediaEps[1]*fEPKT-1.0))
         rfield = rforceeps1();
      else
         rfield = rforce();
   }

   //---------------------------------------------------------------------------------------------//
   integer nnatom,inum,ncrgs;
   SGrid<real> cxyz = {0.0,0.0,0.0},xo,xn,fu,fl,xo2,fxyz,vtemp,xu2,xu,rxyz;
   real chrgv,radu,goff,vphi,aphi,etot,phiv,temp,phii,debyefraction,phirt,phict,phir,phias,tcrgs,dist,phirtt,crgs,phiat,phic,phiac,eps,phiact,phit;
   real sdist,ff,fn;
   string atm,res,rnum,chn,crdstr,atnum,atdes(16,' '),strLine,strHead;
   bool isitmp;
   int iFound,iresnum,idist,ncrg,jtmp;
   vector<bool> atmsf(iAtomNum*iisitsf,false);
   vector<real> sold,scomp;
   char otemp[10];
   string oline(80,' ');

   nnatom = 0; chrgv = 0.0; goff = ((real)iGrid+1.0)/2.0; etot = 0.0; phirt = 0.0; phict =0.0;

   if (isitpot)
   {
      CSitePhiError warning;
   }
   else
   {
      do // beginning of the big loop on natom
      {
         if(iself)
         {
            if (iAtomNum == nnatom) break;
            xo    = prgfgAtomCoordA[nnatom];
            chrgv = prgapAtomPdb[nnatom].getCharge();
            radu  = prgapAtomPdb[nnatom].getRadius()*fScale;
            atm   = prgapAtomPdb[nnatom].getAtInf().substr(0,4);
            res   = prgapAtomPdb[nnatom].getAtInf().substr(6,3);
            rnum  = prgapAtomPdb[nnatom].getAtInf().substr(11,4);
            chn   = prgapAtomPdb[nnatom].getAtInf().substr(10,1);
         }
         else
         {
            if (!ifFileStream.is_open()) break;

            if(ifrm2) // formatted reading
            {
               getline(ifFileStream,strLine);
               strHead = strLine.substr(0,6); strHead = toUpperCase(strHead);
               if (0 != strHead.compare("ATOM  ") && 0 != strHead.compare("HETATM")) continue;
               crdstr = strLine.substr(30,24);
               atnum = strLine.substr(6,5);
               xo.nX = atof(crdstr.substr(0,8).c_str()); xo.nY = atof(crdstr.substr(8,8).c_str()); xo.nZ = atof(crdstr.substr(16,8).c_str());
               inum = atoi(atnum.c_str());
            }
            else // unformatted (binary) reading
            {
               ifFileStream.read( reinterpret_cast<char*>(&xo.nX),sizeof(real) );
               ifFileStream.read( reinterpret_cast<char*>(&xo.nY),sizeof(real) );
               ifFileStream.read( reinterpret_cast<char*>(&xo.nZ),sizeof(real) );
               ifFileStream.read( reinterpret_cast<char*>(&radu), sizeof(real) );
               ifFileStream.read( reinterpret_cast<char*>(&chrgv),sizeof(real) );
            }
         } //----- end of atom reading

         nnatom++;

         isitmp = (isitq && iqass) || isitap || isitp;

         if((isita || isitmp) && !iself)
         {
            atm  = strLine.substr(11,5);
            res  = strLine.substr(17,3);
            rnum = strLine.substr(22,4);
            chn  = strLine.substr(21,1);

            if (0 !=  atm.compare("     ")) {atm  = removeSpace(atm);  atm  = toUpperCase(atm);}
            if (0 !=  res.compare("   "))   {res  = removeSpace(res);  res  = toUpperCase(res);}
            if (0 != rnum.compare("    "))  {rnum = removeSpace(rnum); rnum = toUpperCase(rnum);}
            if (0 != chn.compare(" "))      {chn  = removeSpace(chn);  chn  = toUpperCase(chn);}
         }

         xn = (xo-fgBoxCenter)*fScale+goff; // scale atoms to grid space

         if (isita)
         {
            atdes.substr(0,4)  = atm.substr(0,4);
            atdes.substr(5,3)  = res.substr(0,3);
            atdes.substr(9,1)  = chn.substr(0,1);
            atdes.substr(11,4) = rnum.substr(0,4);
         }

         /*
          * assign charge to atom, searching for decreasingly specific specification
          * note if no charge record found, is assumed to be 0.0
          */

         if(!iself && ifrm2 && isitmp)
         {
            chrgv = 0.0;
            iFound = FindRecord(atm,res,rnum,chn,CHARGEFILE,chrgv);
            if(isitap) iFound = FindRecord(atm,res,rnum,chn,SIZEFILE,radu);
            radu = radu*fScale;
         }

         if (isitsf)
         {
            iresnum = atoi(rnum.c_str());
            atmsf[nnatom-1] = false;
            if (residsf[iresnum-1]) atmsf[nnatom-1] = true;
         }

         if(isitap && 1.0e-6 < abs(chrgv))
         {
            real rads = min(radu,fPotentialUpperBond*fScale);
            SGrid<real> xt;

            xt = xn; xt.nX += rads;
            vphi = interpl(iGrid,phimap,xt);
            aphi = vphi;

            xt = xn; xt.nX -= rads;
            vphi = interpl(iGrid,phimap,xt);
            aphi += vphi;

            xt = xn; xt.nY += rads;
            vphi = interpl(iGrid,phimap,xt);
            aphi += vphi;

            xt = xn; xt.nY -= rads;
            vphi = interpl(iGrid,phimap,xt);
            aphi += vphi;

            xt = xn; xt.nZ += rads;
            vphi = interpl(iGrid,phimap,xt);
            aphi += vphi;

            xt = xn; xt.nZ -= rads;
            vphi = interpl(iGrid,phimap,xt);
            aphi += vphi;

            aphi = aphi/6.0;
         }

         if (isitp || isiti || (isitap && 1.0e-6 > abs(chrgv)))
         {
            vphi = interpl(iGrid,phimap,xn);
            if (isitap && 1.0e-6 > abs(chrgv)) aphi = vphi;
            if (isitp) { etot += chrgv*vphi; phiv = vphi; }

            if (isiti)
            {
               CNoIDebMap warning;

               /*
                * we have changed the iconc action so that the phimap has NOT been converted to salt concentrations. therefore
                */
               if (0 != iNonIterateNum)
               {
                  temp = vphi*fTaylorCoeff5+fTaylorCoeff4; temp = vphi*temp+fTaylorCoeff3;
                  temp = vphi*temp+fTaylorCoeff2;          temp = vphi*temp+fTaylorCoeff1;
                  phii = vphi*temp;
               }
               else
                  phii = -fIonStrength*2.0*vphi;
            }
         } //----- end if isitp or isiti, salt and or potentials

         if (isitdeb) // it calculates the fraction of closest grid points that are in solution
         {
            cout << "Calculating Debye Fraction\n";
            debyefraction = boolinterpl(iGrid,prgbDielecMap,xn);
         }

         if (isitf)
         {
            xn.nX += 1.0;               fu.nX = interpl(iGrid,phimap,xn);
            xn.nX -= 2.0;               fl.nX = interpl(iGrid,phimap,xn);
            xn.nX += 1.0; xn.nY += 1.0; fu.nY = interpl(iGrid,phimap,xn);
            xn.nY -= 2.0;               fl.nY = interpl(iGrid,phimap,xn);
            xn.nY += 1.0; xn.nZ += 1.0; fu.nZ = interpl(iGrid,phimap,xn);
            xn.nZ -= 2.0;               fl.nZ = interpl(iGrid,phimap,xn);
            xn.nZ += 1.0;
            fxyz = (fl-fu)*0.5*fScale; // the electric field is opposite the potential gradient so I change the sign
         }

         /*
          * check if this point is within the box.
          */
         if (isitt)
         {
            SExtrema<real> bedge;
            bedge.nMin = fgBoxCenter-0.5*(iGrid-1)/fScale; bedge.nMax = fgBoxCenter+0.5*(iGrid-1)/fScale;

            int it = 0;
            if ( optORLT<real>(xo,bedge.nMin) || optORGT<real>(xo,bedge.nMax) ) it = 1;

            if (0 == it)
            {
               xo2 = (xo-fgBoxCenter)*fScale+goff;

               /*
                * first find reaction field from surface elements inside of the box..
                */
               phir=0.0; phias=0.0; ncrgs=0; tcrgs=0.0; sold.assign(30,0.0);

               for (integer i = 0; i < iDielecBndySum; i++)
               {
                  vtemp = xo - prgfgSurfCrgA[i]; dist = sqrt(optDot(vtemp,vtemp));
                  //----- first find reaction field from surface elements inside of the box
                  ncrgs++; tcrgs += prgfSurfCrgE[i]; phirtt = prgfSurfCrgE[i]/dist;
                  //----- medeps either epsin contain the 561.0 factor....
                  phirtt = phirtt*fEPKT; phir += phirtt;
                  xu2.nX = (real)prgigBndyGrid[i].nX; xu2.nY = (real)prgigBndyGrid[i].nY; xu2.nZ = (real)prgigBndyGrid[i].nZ;
                  crgs = prgfSurfCrgE[i];
                  //----- took place of repsin because eps is no more included in schrg , surface charge
                  phiat = tops(xu2,xo2,crgs,1.0,1); phiat = phiat*2.0; phias += phiat;
                  idist = (int)dist; sold[idist] += phiat - phirtt;
               }

               temp = 0.0;
               cout << "Writing sold(1:30) and temp \n";
               for (integer i = 0; i < 30; i++)
               {
                  temp += sold[i];
                  cout << sold[i] << " " << temp;
               }
               cout << endl;

               /*
                * next find the colombic potential for that site from charges within the box
                */
               phic = 0.0; phiac = 0.0; ncrg = 0;

               for (integer i = 0; i < iCrgGridNum; i++)
               {
                  it = 0;
                  if (optORLT<real>(prgfgCrgPoseA[i],bedge.nMin) || optORGT<real>(prgfgCrgPoseA[i],bedge.nMax)) it = 1;

                  if (0 == it)
                  {
                     ncrg++;
                     vtemp = xo - prgfgCrgPoseA[i]; dist = sqrt(optDot(vtemp,vtemp));

                     if (5.0 > dist)
                     {
                        if (1.0e-6 < dist) {temp = prggvAtomicCrg[i].nValue/dist; phic += temp/prgfAtomEps[i];}
                        //----- find analytic potential from this real charge..=phiac
                        xu  = prgfgCrgPoseA[i]; crgs = prggvAtomicCrg[i].nValue;
                        xu2 = (xu-fgBoxCenter)*fScale+goff;
                        eps = prgfAtomEps[i]*fEPKT;
                        phiact = tops(xu2,xo2,crgs,eps,1);
                        phiac += phiact;
                     }
                  }
               }

               /*
                * medeps, either epsin contain the 561.0 factor....
                */
               phiac = phiac*2.0;

               /*
                * find the grid potentials..
                */
               phiv = interpl(iGrid,phimap,xn);

               string strFileName7 = "extra.dat";
               ofstream ofFileSteam;
               ofFileSteam.open(strFileName7.c_str());
               ofFileSteam << phic << " " << phir << " " << phiv << " " << phias << " " << phiac << " "<< ncrg << " "
                           << ncrgs << " " << tcrgs << endl;
               ofFileSteam.close();

               phit = phic + phir + phiv - phias - phiac;
            }
            else
               phit = 0.0;

            /*
             * phit contains the total corrected potential
             */
         }

         if (isitr)
         {
            scomp.assign(30,0.0); sold.assign(30,0.0); phir = 0.0;

            for (integer i = 0; i < iDielecBndySum; i++)
            {
               vtemp = xo - prgfgSurfCrgA[i]; dist = sqrt(optDot(vtemp,vtemp));
               idist = (int)dist;
               if (30 > idist) sold[idist] += fEPKT*prgfSurfCrgE[i]/dist;
               phir += prgfSurfCrgE[i]/dist;
            }

            /*
             * medeps either epsin contains the 561.0 factor....
             */
            phir = phir*fEPKT;

            for (integer i = 0; i < 30; i++)
            {
               if (0 == i) scomp[i] = sold[i];
               if (0 != i) scomp[i] = scomp[i-1]+sold[i];
            }

            phirt += phir*chrgv;
         }

         /*
          * medeps either epsin contains the 561.0 factor....
          */
         if (isitrf || isitmd || isittf) rxyz = rfield[nnatom-1]*fEPKT;

         if(isitcf || isitmd || isittf)
         {
            cxyz.nX = 0.0; cxyz.nY = 0.0; cxyz.nZ = 0.0;

            if (1.0e-6 < abs(chrgv))
            {
               for (integer i = 0; i < iCrgGridNum; i++)
               {
                  vtemp = xo - prgfgCrgPoseA[i]; dist = optDot(vtemp,vtemp);
                  if (1.0e-6 < dist)
                  {
                     sdist = sqrt(dist)*dist;
                     temp  = prggvAtomicCrg[i].nValue/(prgfAtomEps[i]*sdist);
                     cxyz  = cxyz + vtemp*temp;
                  }
               }

               /*
                * atmeps and medeps and epsin contain the 561.0 factor....
                */
               cxyz = cxyz*chrgv;
            }
         }

         if (isitc)
         {
            phic = 0.0;

            for (integer i = 0; i < iCrgGridNum; i++)
            {
               vtemp = xo - prgfgCrgPoseA[i]; dist = optDot(vtemp,vtemp);
               if (1.0e-6 < dist)
               {
                  sdist = sqrt(dist);
                  temp  = prggvAtomicCrg[i].nValue/sdist;
                  phic += temp/prgfAtomEps[i];
               }
            }

            /*
             * atmeps and medeps and epsin contain the 561.0 factor....
             */
            phict += phic*chrgv;
         }

         //---------------------------------------------------------------------------------------//
         /*
          * write out calculated/assigned charges
          *
          * need otemp cos can not write into a substring apparently
          * otemp needs to be at least 15 long to avoid an error!!
          */
         j = 0;

         if (isita)
         {
            oline.substr(j,16) = atdes.substr(0,16);
            j += 20;
         }

         if (isitx)
         {
            sprintf(otemp,"%10.4f",xo.nX); oline.substr(j,10) = otemp; j += 10;
            sprintf(otemp,"%10.4f",xo.nY); oline.substr(j,10) = otemp; j += 10;
            sprintf(otemp,"%10.4f",xo.nZ); oline.substr(j,10) = otemp; j += 10;
         }

         if (isitq)
         {
            sprintf(otemp,"%10.4f",chrgv); oline.substr(j,10) = otemp; j += 10;
         }

         if (isitp)
         {
            sprintf(otemp,"%10.4f",phiv);  oline.substr(j,10) = otemp; j += 10;
         }

         if (isiti)
         {
            sprintf(otemp,"%10.4f",phii);  oline.substr(j,10) = otemp; j += 10;
         }

         if (isitr)
         {
            sprintf(otemp,"%10.4f",phir);  oline.substr(j,10) = otemp; j += 10;
         }

         if (isitc)
         {
            sprintf(otemp,"%10.4f",phic);  oline.substr(j,10) = otemp; j += 10;
         }

         if (isitap)
         {
            sprintf(otemp,"%10.4f",aphi);  oline.substr(j,10) = otemp; j += 10;
         }

         if (isitdeb)
         {
            sprintf(otemp,"%10.4f",debyefraction); oline.substr(j,10) = otemp; j += 10;
         }

         if (isitf)
         {
            sprintf(otemp,"%10.4f",fxyz.nX); oline.substr(j,10) = otemp; j += 10;
            sprintf(otemp,"%10.4f",fxyz.nY); oline.substr(j,10) = otemp; j += 10;
            sprintf(otemp,"%10.4f",fxyz.nZ); oline.substr(j,10) = otemp; j += 10;
         }

         if (isitrf)
         {
            sprintf(otemp,"%10.4f",rxyz.nX); oline.substr(j,10) = otemp; j += 10;
            sprintf(otemp,"%10.4f",rxyz.nY); oline.substr(j,10) = otemp; j += 10;
            sprintf(otemp,"%10.4f",rxyz.nZ); oline.substr(j,10) = otemp; j += 10;
         }

         if (isitcf)
         {
            sprintf(otemp,"%10.4f",cxyz.nX); oline.substr(j,10) = otemp; j += 10;
            sprintf(otemp,"%10.4f",cxyz.nY); oline.substr(j,10) = otemp; j += 10;
            sprintf(otemp,"%10.4f",cxyz.nZ); oline.substr(j,10) = otemp; j += 10;
         }

         if (isittf)
         {
            vtemp = rxyz + cxyz;
            sprintf(otemp,"%10.4f",vtemp.nX); oline.substr(j,10) = otemp; j += 10;
            sprintf(otemp,"%10.4f",vtemp.nY); oline.substr(j,10) = otemp; j += 10;
            sprintf(otemp,"%10.4f",vtemp.nZ); oline.substr(j,10) = otemp; j += 10;
         }

         if (isitmd)
         {
            vtemp = rxyz + cxyz;
            cout << "atom: " << nnatom << " rx= " << rxyz.nX << " cx= " << cxyz.nX << " tx= " << vtemp.nX << endl;
            cout << "atom: " << nnatom << " ry= " << rxyz.nY << " cy= " << cxyz.nY << " ty= " << vtemp.nY << endl;
            cout << "atom: " << nnatom << " rz= " << rxyz.nZ << " cz= " << cxyz.nZ << " tz= " << vtemp.nZ << endl;
         }

         if (isitt)
         {
            sprintf(otemp,"%10.4f",phit); oline.substr(j,10) = otemp; j += 10;
         }

         if (ofrm && isitmp1) ofFileStream << oline << endl;

         if (!ofrm && isitmp1)
         {
            if (isita)  ofFileStream << atdes << endl;
            if (isitx)  ofFileStream << xo    << endl;
            if (isitq)  ofFileStream << chrgv << endl;
            if (isitp)  ofFileStream << phiv  << endl;
            if (isiti)  ofFileStream << phii  << endl;
            if (isitr)  ofFileStream << phir  << endl;
            if (isitc)  ofFileStream << phic  << endl;
            if (isitap) ofFileStream << aphi  << endl;
            if (isitf)  ofFileStream << fxyz  << endl;
            if (isitrf) ofFileStream << rxyz  << endl;
            if (isitcf) ofFileStream << cxyz  << endl;
            if (isittf) { vtemp = rxyz + cxyz; ofFileStream << vtemp << endl;}
         }
      } while(true); // end of the big loop on natom
   }

   if (isitsf)
   {
      for (integer jj = 0; jj < iBndyGridNum; jj++)
      {
         integer i = prgiAtSurf[jj];

         if (atmsf[i-1] && (0 < prgiAtNdx[jj]))
         {
            /*
             * if the bgp belongs to the interesting site
             * attention: using always radprb(1), in some case might be inappropriate
             */
            xo = prgfgSurfCrgA[jj]+rgfProbeRadius[0]*prgfgSurfCrgE[jj];
            xn = (xo-fgBoxCenter)*fScale+goff;

            xn.nX += 1.0;               fu.nX = interpl(iGrid,phimap,xn);
            xn.nX -= 2.0;               fu.nX = interpl(iGrid,phimap,xn);
            xn.nX += 1.0; xn.nY += 1.0; fu.nY = interpl(iGrid,phimap,xn);
            xn.nY -= 2.0;               fu.nY = interpl(iGrid,phimap,xn);
            xn.nY += 1.0; xn.nZ += 1.0; fu.nZ = interpl(iGrid,phimap,xn);
            xn.nZ -= 2.0;               fu.nZ = interpl(iGrid,phimap,xn);
            xn.nZ += 1.0;

            fxyz = fl - fu;
            fn   = 0.5*fScale*(optDot(fxyz,prgfgSurfCrgE[jj]));
            ff   = 0.5*fScale*(optDot(fxyz,fxyz));

            if (ofrm)
            {
               jtmp = j;

               sprintf(otemp,"%10.4f",prgfSurfCrgE[jj]); oline.substr(jtmp,10) = otemp; jtmp += 10;
               sprintf(otemp,"%10.4f",xo.nX);            oline.substr(jtmp,10) = otemp; jtmp += 10;
               sprintf(otemp,"%10.4f",xo.nY);            oline.substr(jtmp,10) = otemp; jtmp += 10;
               sprintf(otemp,"%10.4f",xo.nZ);            oline.substr(jtmp,10) = otemp; jtmp += 10;
               sprintf(otemp,"%10.4f",fn);               oline.substr(jtmp,10) = otemp; jtmp += 10;
               sprintf(otemp,"%10.4f",ff);               oline.substr(jtmp,10) = otemp; jtmp += 10;

               ofFileStream << oline << endl;
            }

            if (!ofrm)  ofFileStream << prgfSurfCrgE[jj] << " " << fn << endl;
         }
      }
   }

   if(!iself) ifFileStream.close();

#ifdef VERBOSE
   cout << "\n number of atom coordinates read : " << nnatom << endl << endl;
#endif

   etot = etot/2.0;

   if (ofrm)
   {
      if (0 == iFrcFormatOut)
      {
         ofFileStream << "total energy = " << etot << " kt\n";
         if (isitr)  ofFileStream << "corrected reaction field energy= " << phirt/2.0 << " kt\n";
         if (isitap) ofFileStream << "Atomic potential for charged atoms is averaged over a spherical surface of less than "
                                  << fPotentialUpperBond << " A\n";
      }

      if (1 == iFrcFormatOut)
      {
         ofFileStream << "corrected reaction field energy= " << phirt/2.0 << " kt\n";
         ofFileStream << "total coulombic energy     = " << phict/2.0 << " kt\n";
         if (isitap) ofFileStream << "Atomic potential for charged atoms is averaged over a spherical surface of less than "
                                  << fPotentialUpperBond << " A\n";
      }

      if (2 == iFrcFormatOut)
      {
         ofFileStream << "corrected reaction field energy= " << phirt/2.0 << " kt\n";
         if (isitap) ofFileStream << "Atomic potential for charged atoms is averaged over a spherical surface of less than "
                                  << fPotentialUpperBond << " A\n";
      }
   }

   /*
    * end of formatted frc read/write and unformatted frc write
    * end of unformatted frc.pdb read and frc write
    */
   ofFileStream.close();

#ifdef VERBOSE
   cout << "frc stuff now done at "; pTimer->showTime(); cout << endl;
#endif
}
