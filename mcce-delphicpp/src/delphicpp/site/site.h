/*
 * site.h
 *
 *  Created on: Feb 17, 2014
 *      Author: chuan
 */

#ifndef SITE_H_
#define SITE_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include <cstdio>

#include "../interface/interface_datacontainer.h"
#include "../misc/misc_timer.h"
#include "../misc/misc_interpl.h"
#include "../delphi/delphi_constants.h"
#include "../io/io.h"
#include "site_exceptions.h"

using namespace std;

class CSite:public CIO
{
   private:
      /*********************************************************************************************
       *                                                                                           *
       *              references to the variables obtained from the data container                 *
       *                                                                                           *
       ********************************************************************************************/
      shared_ptr<CTimer> pTimer;
      //----- set by statements
      const integer& iGrid;                             // igrid
      const real&    fPercentageFill;                   // perfil
      const real&    fExDielec;                         // repsout
      const real&    fIonRadius;                        // exrad
      const vector<real>& rgfProbeRadius;               // radprb
      const int&     iLinIterateNum;                    // nlit
      const int&     iNonIterateNum;                    // nnit
      const int&     iBndyType;                         // ibctyp
      const real&    fPotentialUpperBond;               // atompotdist
      const bool&    bOutCrgDensity;                    // iconc
      //----- io file names
      const string&  strFrciFile;                       // frcinam
      const string&  strFrcFile;                        // frcnam
      const string&  strPhiFile;                        // phinam
      //----- set by functions
      const bool&    bAtomInSite;                       // isita
      const bool&    bSaltInSite;                       // isiti
      const bool&    bMDInSite;                         // isitmd
      const bool&    bPotentialInSite;                  // isitpot
      const int&     iPhiFormatOut;                     // phifrm
      const bool&    bBiosystemOut;                     // ibios
      //----- set by DelPhi
      const real&    fIonStrength;                      // rionst
      const SGrid<real>& fgBoxCenter;                   // oldmid
      const vector< SGrid<real> >& prgfgAtomCoordA;     // xn1(natom)
      const real&    fTaylorCoeff1;                     // chi1
      const real&    fTaylorCoeff2;                     // chi2
      const real&    fTaylorCoeff3;                     // chi3
      const real&    fTaylorCoeff4;                     // chi4
      const real&    fTaylorCoeff5;                     // chi5
      //----- set by Surface class
      const integer& iBndyGridNum;                      // ibnum
      const integer& iCrgGridNum;                       // nqass
      const vector< SGridValue<real> >& prggvAtomicCrg; // atmcrg(nqass)
      const vector< SGrid<real> >& prgfgCrgPoseA;       // chgpos(ibnum)
      const vector< SGrid<real> >& prgfgSurfCrgA;       // scspos(ibnum)
      const vector<integer>& prgiCrgAt;                 // crgatn(nqass)
      const vector<integer>& prgiAtSurf;                // atsurf(ibnum)
      const vector< SGrid<real> >& prgfgSurfCrgE;       // scsnor(ibnum)
      const vector<bool>& prgbDielecMap;                // idebmap(igrid,igrid,igrid)
      const vector< SGrid<integer> >& prgigBndyGrid;    // ibgrd(ibnum)
      const vector<real>& prgfAtomEps;                  // atmeps(nqass)
      const vector<integer>& prgiAtNdx;                 // atndx(ibnum)
      //----- set by Solver class
      const integer& iDielecBndySum;                    // icount2b
      //----- set by Energy class
      const vector<real>& prgfSurfCrgE;                 // schrg(ibnum)
      //++++++++++++++++ reference to read-and-write variables from data container +++++++++++++++//
      bool&          bAtomCoordInSite;                  // isitx
      bool&          bCrgInSite;                        // isitq
      bool&          bFieldInSite;                      // isitf
      bool&          bGridPotentialInSite;              // isitp
      bool&          bReactPotentialInSite;             // isitr
      bool&          bCoulombPotentialInSite;           // isitc
      bool&          bAtomPotentialInSite;              // isitap
      bool&          bDebyeFractionInSite;              // isitdeb
      bool&          bSurfCrgInSite;                    // isitsf
      bool&          bTotalForceInSite;                 // isittf
      bool&          bReactForceInSite;                 // isitrf
      bool&          bTotalPotentialInSite;             // isitt
      bool&          bCoulombForceInSite;               // isitcf
      bool&          bPDB2FRCInSite;                    // iself
      int&           iFrcFormatOut;                     // frcfrm
      real&          fScale;                            // scale
      vector<real>&  prgfPhiMap;                        // phimap
      /*********************************************************************************************
       *                                                                                           *
       *                            variables defined in this class                                *
       *                                                                                           *
       ********************************************************************************************/
      real *** phimap;

      vector< SGrid<real> > rforceeps1();

      vector< SGrid<real> > rforce();

      //real debinterpl(const SGrid<real> & gPoint);

      real tops(const SGrid<real>& xxo,const SGrid<real>& xxu,const real& crg,const real& eps,const int& flag);

      void phicon();

      void writePotential_insight(vector<real>& phimapIn);

      void writePotential_grasp(vector<real>& phimapIn);

      void writePotential_ccp4(vector<real>& phimapIn);

      void writePotential_fromPrevious(vector<real>& phimapIn);

      void writePotential_cube();

      void writePotential_delphi();

      void writePhiMap(const int& formatflag,vector<real>& phimap4,ofstream& ofFileStream);

      void expand(const int& mgrid, vector<real>& phimapIn);

   public:
      CSite(shared_ptr<IDataContainer> pdc,shared_ptr<CTimer> pt):
         CIO(pdc->getKey_Val<real>("repsin"),pdc->getKey_Val<real>("epkt")),
         pTimer(pt),
         //----- set by statements
         iGrid(pdc->getKey_constRef<integer>("igrid")), // modified in setFocusBndy
         fPercentageFill(pdc->getKey_constRef<real>("perfil")),
         fExDielec(pdc->getKey_constRef<real>("repsout")),
         fIonRadius(pdc->getKey_constRef<real>("exrad")),
         rgfProbeRadius(pdc->getKey_constRef< vector<real> >("radprb")),
         iLinIterateNum(pdc->getKey_constRef<int>("nlit")),
         iNonIterateNum(pdc->getKey_constRef<int>("nnit")),
         iBndyType(pdc->getKey_constRef<int>("ibctyp")),
         fPotentialUpperBond(pdc->getKey_constRef<real>("atompotdist")),
         bOutCrgDensity(pdc->getKey_constRef<bool>("iconc")),
         //----- io file names
         strFrciFile(pdc->getKey_constRef<string>("frcinam")),
         strFrcFile(pdc->getKey_constRef<string>("frcnam")),
         strPhiFile(pdc->getKey_constRef<string>("phinam")),
         //----- set by functions
         bAtomInSite(pdc->getKey_constRef<bool>("isita")),
         bSaltInSite(pdc->getKey_constRef<bool>("isiti")),
         bMDInSite(pdc->getKey_constRef<bool>("isitmd")),
         bPotentialInSite(pdc->getKey_constRef<bool>("isitpot")),
         iPhiFormatOut(pdc->getKey_constRef<int>("phifrm")),
         bBiosystemOut(pdc->getKey_constRef<bool>("ibios")),
         //----- set by DelPhi
         fIonStrength(pdc->getKey_constRef<real>("rionst")),
         fgBoxCenter(pdc->getKey_constRef< SGrid<real> >("oldmid")),
         prgfgAtomCoordA(pdc->getKey_constRef< vector< SGrid<real> > >("xn1")),
         fTaylorCoeff1(pdc->getKey_constRef<real>("chi1")),
         fTaylorCoeff2(pdc->getKey_constRef<real>("chi2")),
         fTaylorCoeff3(pdc->getKey_constRef<real>("chi3")),
         fTaylorCoeff4(pdc->getKey_constRef<real>("chi4")),
         fTaylorCoeff5(pdc->getKey_constRef<real>("chi5")),
         //----- set by Surface class
         iBndyGridNum(pdc->getKey_constRef<integer>("ibnum")),
         iCrgGridNum(pdc->getKey_constRef<integer>("nqass")),
         prggvAtomicCrg(pdc->getKey_constRef< vector< SGridValue<real> > >("atmcrg")),
         prgfgCrgPoseA(pdc->getKey_constRef< vector< SGrid<real> > >("chgpos")),
         prgfgSurfCrgA(pdc->getKey_constRef< vector< SGrid<real> > >("scspos")),
         prgiCrgAt(pdc->getKey_constRef< vector<integer> >("crgatn")),
         prgiAtSurf(pdc->getKey_constRef< vector<integer> >("atsurf")),
         prgfgSurfCrgE(pdc->getKey_constRef< vector< SGrid<real> > >("scsnor")),
         prgbDielecMap(pdc->getKey_constRef< vector<bool> >("idebmap")),
         prgigBndyGrid(pdc->getKey_constRef< vector< SGrid<integer> > >("ibgrd")),
         prgfAtomEps(pdc->getKey_constRef< vector<real> >("atmeps")),
         prgiAtNdx(pdc->getKey_constRef< vector<integer> >("atndx")),
         //----- set by Solver class
         iDielecBndySum(pdc->getKey_constRef<integer>("icount2b")),
         //----- set by Energy class
         prgfSurfCrgE(pdc->getKey_constRef< vector<real> >("schrg")),
         //++++++++++++++ reference to read-and-write variables from data container ++++++++++++++//
         bAtomCoordInSite(pdc->getKey_Ref<bool>("isitx")),
         bCrgInSite(pdc->getKey_Ref<bool>("isitq")),
         bFieldInSite(pdc->getKey_Ref<bool>("isitf")),
         bGridPotentialInSite(pdc->getKey_Ref<bool>("isitp")),
         bReactPotentialInSite(pdc->getKey_Ref<bool>("isitr")),
         bCoulombPotentialInSite(pdc->getKey_Ref<bool>("isitc")),
         bAtomPotentialInSite(pdc->getKey_Ref<bool>("isitap")),
         bDebyeFractionInSite(pdc->getKey_Ref<bool>("isitdeb")),
         bSurfCrgInSite(pdc->getKey_Ref<bool>("isitsf")),
         bTotalForceInSite(pdc->getKey_Ref<bool>("isittf")),
         bReactForceInSite(pdc->getKey_Ref<bool>("isitrf")),
         bTotalPotentialInSite(pdc->getKey_Ref<bool>("isitt")),
         bCoulombForceInSite(pdc->getKey_Ref<bool>("isitcf")),
         bPDB2FRCInSite(pdc->getKey_Ref<bool>("iself")),
         iFrcFormatOut(pdc->getKey_Ref<int>("frcfrm")),
         fScale(pdc->getKey_Ref<real>("scale")),
         prgfPhiMap(pdc->getKey_Ref< vector<real> >("phimap"))
      {
         //----- variables inherited from CIO class
         iResidueNum  = pdc->getKey_Val<integer>("resnummax");
         prgfMediaEps = pdc->getKey_Val< vector<real> >("medeps");
         iMediaNum    = pdc->getKey_Val<integer>("nmedia");
         iAtomNum     = pdc->getKey_Val<integer>("natom");
         prgapAtomPdb = pdc->getKey_Val< vector<CAtomPdb> >("delphipdb");

         //----- local variables
         phimap = pdc->getKey_Ptr<real>("phimap",iGrid,iGrid,iGrid); // pointer to 3D phimap

         //cout << "fDielec = " << fDielec << endl;
      };

      void writeSite(const int& iisitsf);

      void writePhi();

};



#endif /* SITE_H_ */
