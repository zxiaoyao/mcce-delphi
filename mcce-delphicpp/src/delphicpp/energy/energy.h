/*
 * energy.h
 *
 *  Created on: Feb 23, 2014
 *      Author: Lin Wang
 */


#ifndef ENERGY_H_
#define ENERGY_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>

//#include "../interface/interface_datacontainer.h"
#include "../interface/interface_abstractmodule.h"
#include "../misc/misc_timer.h"
#include "../misc/misc_grid.h"
#include "energy_exceptions.h"

using namespace std;

class CDelphiEnergy:virtual public IAbstractModule
{
   private:

      shared_ptr<CTimer> pTimer;

      const int& iBndyType;
      const string& strEnergyFile;
      const string& strScrgFile;
      const bool& bEngOut;
      const bool& bSurfEngOut;
      const bool& bSurfCrgOut;
      const int& iSurfCrgFormatOut;
      const bool& bGridEng;
      const bool& bSolvEng;
      const bool& bAnalySurfEng;
      const bool& bAnalyEng;
      const bool& bIonsEng;
      const bool& bCoulombEng;
      const bool& bPotentiallnSite;
      const bool& bReactFieldlnFRC;
      const bool& bBuffz;
      const int& iCrgGridNum;
      const real& fEpsOut;
      const bool& bNonlinearEng;
      const int& iMediaNum;

      const real& prgrMediaEps;
      const int& prgiAtomMediaNum;
      const int& iTotalBdyGridNum;
      const int& iCrgBdyGrid;
      const vector< SGrid<int> >& prgigBndyGrid;
      const vector< SGridValue<real> >& prggvAtomicCrg;
      const int& iGrid;
      const int& iCrgedGridB;
      const real& fEpsin;
   //	const bool& DEVELOPER;    // Developer is not from datacontainer now. It changed to the flag.
      const vector<real>& prgfPhimap;
      const real& fScale;
      const SGrid<real>& fgPotentialDrop;
      const vector< SGrid<real> >& prgfgCrgPoseA;
      const vector< SGrid<int> >& prgigGridCrgPose;
      const vector<real>& prgfGridCrg;
      const real& fIonStrength;
      const SGrid<real>& fgBoxCenter;
      const vector<bool>& prgbDielecMap;
      const vector<real>& prgfAtomEps;
      const SExtrema<int>& ieBuffz;

      const int& iObjectNum;
      const int& iAtomNum;
      const int& iDielecBndyOdd;
      const real& fEPKT;
      const vector<CAtomPdb>& prgapAtomPdb;
      vector< SDoubleGridValue >& prgdgvCrgBndyGrid;
      const vector< SGrid<real> >& prgfgSurfCrgA;
      const vector<integer>& prgiCrgAt;
      const vector<integer>& atsurf;


      const real& fTaylorCoeff1;
      const real& fTaylorCoeff2;
      const real& fTaylorCoeff3;
      const real& fTaylorCoeff4;
      const real& fTaylorCoeff5;

      vector < SGridValue<real> > sout;
      SGrid<int> lim_min, lim_max;

      vector <real>& schrg;
      real& ergg;
      real& ergc;
      real& ergs;
      real& ergr;
      real& ergions;

      //***************//

      void energy_clb(real& ergc);
      void energy_clbmedia(real& ergc);
      void energy_clbnonl(real& ergc, real& ergest, int& igridout);
      void energy_clbtotal(real& ergest, real& ergc);
      void energy_react(real& ergs, real& ergas, int& iisitpot);
      void energy_nonl(real& ergnl, int& igridout);


   public:
      CDelphiEnergy(shared_ptr<IDataContainer> pdc,shared_ptr<CTimer> pt):
         IAbstractModule(pdc),
         pTimer(pt),

         iBndyType(pdc->getKey_constRef<int>("ibctyp")),
         strEnergyFile(pdc->getKey_constRef<string>("nrgnam")),
         strScrgFile(pdc->getKey_constRef<string>("scrgnam")),
         bEngOut(pdc->getKey_constRef<bool>("inrgwrt")),
         bSurfEngOut(pdc->getKey_constRef<bool>("isen")),
         bSurfCrgOut(pdc->getKey_constRef<bool>("isch")),
         iSurfCrgFormatOut(pdc->getKey_constRef<int>("scrgfrm")),
         bGridEng(pdc->getKey_constRef<bool>("logg")),
         bSolvEng(pdc->getKey_constRef<bool>("logs")),
         bAnalySurfEng(pdc->getKey_constRef<bool>("logas")),
         bAnalyEng(pdc->getKey_constRef<bool>("loga")),
         bIonsEng(pdc->getKey_constRef<bool>("logions")),
         bCoulombEng(pdc->getKey_constRef<bool>("logc")),
         bPotentiallnSite(pdc->getKey_constRef<bool>("isitpot")),
         bReactFieldlnFRC(pdc->getKey_constRef<bool>("irea")),
         bBuffz(pdc->getKey_constRef<bool>("ibufz")),
         iCrgGridNum(pdc->getKey_constRef<integer>("nqass")),
         fEpsOut(pdc->getKey_constRef<real>("epsout")),
         bNonlinearEng(pdc->getKey_constRef<bool>("lognl")),
         iMediaNum(pdc->getKey_constRef<integer>("nmedia")),
         prgrMediaEps(pdc->getKey_constRef<real>("medeps")),
         prgiAtomMediaNum(pdc->getKey_constRef<integer>("iatmmed")),
         iTotalBdyGridNum(pdc->getKey_constRef<integer>("ibnum")),
         iCrgBdyGrid(pdc->getKey_constRef<integer>("ibc")),
         prgigBndyGrid(pdc->getKey_constRef< vector< SGrid<int> > >("ibgrd")),
         iGrid(pdc->getKey_constRef<integer>("igrid")),
         iCrgedGridB(pdc->getKey_constRef<integer>("icount1b")),
         fEpsin(pdc->getKey_constRef<real>("epsin")),
   //		DEVELOPER(pdc->getKey_constRef<bool>("ideveloper")),
         prgfPhimap(pdc->getKey_constRef< vector<real> >("phimap")),  // phimap read function to convert to 3d array. //
         fScale(pdc->getKey_constRef<real>("scale")),
         fgPotentialDrop(pdc->getKey_constRef< SGrid<real> >("vdrop")),
         prgfgCrgPoseA(pdc->getKey_constRef< vector< SGrid<real> > >("chgpos")),
         prgfGridCrg(pdc->getKey_Ref< vector<real> >("gchrg")),
         prgigGridCrgPose(pdc->getKey_constRef< vector< SGrid<int> > >("gchrgp")),
         prggvAtomicCrg(pdc->getKey_constRef< vector< SGridValue<real> > >("atmcrg")),
         fIonStrength(pdc->getKey_constRef<real>("rionst")),
         fgBoxCenter(pdc->getKey_constRef< SGrid<real> >("oldmid")),
         prgbDielecMap(pdc->getKey_constRef< vector<bool> >("idebmap")),
         prgfAtomEps(pdc->getKey_constRef< vector<real> >("atmeps")),
         ieBuffz(pdc->getKey_constRef< SExtrema<int> >("buffz")),

         iObjectNum(pdc->getKey_constRef<int>("nobject")),
         iAtomNum(pdc->getKey_constRef<int>("natom")),
         iDielecBndyOdd(pdc->getKey_constRef<int>("icount2b")),
         fEPKT(pdc->getKey_constRef<real>("epkt")),
         prgdgvCrgBndyGrid(pdc->getKey_Ref< vector<SDoubleGridValue> >("cgbp")),
         prgapAtomPdb(pdc->getKey_Ref< vector<CAtomPdb> >("delphipdb")),
         prgfgSurfCrgA(pdc->getKey_constRef< vector< SGrid<real> > >("scspos")),
         prgiCrgAt(pdc->getKey_constRef< vector<integer> >("crgatn")),
         atsurf(pdc->getKey_constRef< vector<integer> >("atsurf")),
         fTaylorCoeff1(pdc->getKey_constRef<real>("chi1")),
         fTaylorCoeff2(pdc->getKey_constRef<real>("chi2")),
         fTaylorCoeff3(pdc->getKey_constRef<real>("chi3")),
         fTaylorCoeff4(pdc->getKey_constRef<real>("chi4")),
         fTaylorCoeff5(pdc->getKey_constRef<real>("chi5")),
         schrg(pdc->getKey_Ref< vector<real> >("schrg")),
         ergg(pdc->getKey_Ref<real>("ergg")),
         ergc(pdc->getKey_Ref<real>("ergc")),
         ergs(pdc->getKey_Ref<real>("ergs")),
         ergr(pdc->getKey_Ref<real>("ergr")),
         ergions(pdc->getKey_Ref<real>("ergions"))
      {
#ifdef DEBUG_OBJECT
         cout << endl;
         cout << "****************************************************************\n";
         cout << "*                CDelphiEnergy is constructed                  *\n";
         cout << "****************************************************************\n";
#endif
      };

       ~CDelphiEnergy()
       {
#ifdef DEBUG_OBJECT
         cout << endl;
         cout << "****************************************************************\n";
         cout << "*                 CDelphiEnergy is destroyed                   *\n";
         cout << "****************************************************************\n";
#endif
       };

       virtual void validateInput(){};

       virtual void run();


};



#endif /* ENERGY_H_ */
