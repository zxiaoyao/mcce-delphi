#ifndef SOLVER_FASTSOR_H
#define SOLVER_FASTSOR_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <memory>
#include <cmath>      // std::abs
//#include <deque>

#include "../interface/interface_abstractmodule.h"
#include "../misc/misc_timer.h"
#include "../delphi/delphi_constants.h"
#include "../io/io.h"
#include "solver_exceptions.h"

using namespace std;

class CDelphiFastSOR:virtual public IAbstractModule
{
   private:                                            // In DATA CONTAINER
      shared_ptr<CTimer> pTimer; 

      /*********************************************************************************************
       *                                                                                           *
       *              references to the variables obtained from the data container                 *
       *                                                                                           *
       ********************************************************************************************/

      //++++++++++++++ const references to read-only variables from data container +++++++++++++++//
      //----- uniform parameters
      const string&  strBioModel;                      // biomodel
      const string&  strNumSolver;                     // solver
      //----- set by Statements
      const integer& iAtomNum;                         // natom
      const bool&    bCrgInterplateType;               // isph true-spherical false-cubic
      const bool&    bSpectralRadius;                  // iuspec
      const real&    fSpectralRadius;                  // uspec
      const vector<bool>& rgbPeriodicBndy;             // iper
      const int&     iNonIterateNum;                   // nnit
      const real&    fIonRadius;                       // exrad
      const bool&    bFixedRelaxParam;                 // icheb
      const bool&    bAutoConverge;                    // iautocon
      const real&    fGridConverge;                    // gten
      const real&    fRmsc;                            // res1
      const real&    fMaxc;                            // res2
      const bool&    bLogGraph;                        // igraph
      const bool&    bLogPotential;                    // ipoten
      const bool&    bManualRelaxParam;                // imanual
      //----- io file names
      const string&  strEpsFile;                       // epsnam
      const string&  strPhiiFile;                      // phiinam
      //----- set by functions      
      const bool&    bDbOut;                           // idbwrt
      const bool&    bGridCrgOut;                      // iwgcrg
      const bool&    bEpsOut;                          // epswrt
      const bool&    bIonsEng;                         // logions
      //----- set by DelPhi      
      const real&    fEpsOut;                          // epsout
      const real&    fDebyeLength;                     // deblen
      const real&    fScale;                           // scale
      const real&    fEpsIn;                           // epsin
      const real&    fIonStrength;                     // rionst
      const int&     iDirectEpsMap;                    // idirectalg
      const real&    fEPKT;                            // epkt
      const SGrid<real>& fgBoxCenter;                  // oldmid
      const SGrid<real>& fgPotentialDrop;              // vdrop
      const real&    fTaylorCoeff2;                    // chi2
      const real&    fTaylorCoeff3;                    // chi3
      const real&    fTaylorCoeff4;                    // chi4
      const real&    fTaylorCoeff5;                    // chi5
      //----- set by IO class      
      const integer& iMediaNum;                        // nmedia
      const integer& iObjectNum;                       // nobject
      const vector<real>& prgfMediaEps;                // medeps(0:nmediamax)
      //----- set by Surface class
      const integer& iCrgGridNum;                      // nqass
      const real&    fMinusCrg;                        // qmin
      const real&    fPlusCrg;                         // qplus
      const SGrid<real>& fgPlusCrgCenter;              // cqplus
      const SGrid<real>& fgMinusCrgCenter;             // cqmin
      const integer& iBndyGridNum;                     // ibnum
      const vector< SGrid<integer> >& prgigBndyGrid;   // ibgrd(ibnum)
      const vector< SGrid<integer> >& prgigEpsMap;     // iepsmp(igrid,igrid,igrid)
      const vector<bool>& prgbDielecMap;               // idebmap(igrid,igrid,igrid)
      const integer& iCrg2GridNum;                     // nqgrd
      const vector< SGridValue<real> >& prggvCrg2Grid; // chrgv2(nqgrd)
      const vector<integer>& prgiCrg2GridMap;          // nqgrdtonqass(nqgrd)
      const vector<real>& prgfAtomEps;                 // atmeps(nqass)
      const vector< SGridValue<real> >& prggvCrgedAtom;// atmcrg(nqass)
      //const vector< SGrid<real> >& prgfgSurfCrgA;    // scspos(ibnum)

      //++++++++++++++++ reference to read-and-write variables from data container +++++++++++++++//
      integer& iGrid;                                  // igrid (modified in setFocusBndy)
      int&     iBndyType;                              // ibctyp (modified in setBndy)
      real&    fNetCrg;                                // qnet (modified in setCoulombBndy and setDipolarBndy)
      int&     iLinIterateNum;                         // nlit
      int&     iIterateInterval;                       // icon1
      int&     iConvergeFract;                         // icon2
      real&    fRelaxParam;                            // relpar
      //----- out into data container
      integer& iDielecBndyOdd;                         // icount2b
      integer& iCrgedGridSum;                          // icount1b
      vector<real>& prgfGridCrg;                       // gchrg(icount1b)
      vector< SGrid<integer> >& prgigGridCrgPose;      // gchrgp(icount1b)
      integer& iCrgBndyGridNum;                        // ibc
      vector< SDoubleGridValue >& prgdgvCrgBndyGrid;   // cgbp(ibc)
      vector<real>& prgfPhiMap;                        // phimap(igrid,igrid,igrid)
      /*********************************************************************************************
       *                                                                                           *
       *                            variables defined in this class                                *
       *                                                                                           *
       ********************************************************************************************/

      //+++++++++++++++++++++++++++++++++ const class variables ++++++++++++++++++++++++++++++++++//
      const integer iTotalGridNum;                     // ngp=igrid*igrid*igrid+1
      const integer iHalfGridNum;                      // nhgp=ngp/2
      const integer iBndyDielecNum;                    // nsp=2*(ibnum+1)
      const real    fDebFct;                           // debfct
      const real    fEpsDiff;                          // difeps
      const real    fSixEps;                           // sixeps
      const integer iEpsDim;                           // epsdim
      const int     nxran;                             // nxran
      const int     nyran;                             // nyran

      //+++++++++++++++++++++++++++++ local variables in this class ++++++++++++++++++++++++++++++//
      //------ Using either std:vector or std:deque we can construct idpos, db etc. w/o realignment
      integer iDielecBndyEven;                         // icount2a
      vector<integer> prgiBndyDielecIndex;             // idpos(nsp)
      vector< vector<real> > prgfBndyDielec;           // db(6,nsp) <--> prgfBndyDielec[iBndyDielecNum][6]
      vector<real> prgfSaltMap1;                       // sf1(nhgp)
      vector<real> prgfSaltMap2;                       // sf2(nhgp)

      integer iCrgedGridEven;                          // icount1a
      vector<integer> prgiCrgPose;                     // iqpos(icount1b)
      vector<real> prgfCrgValA;                        // qval(icount1b)
      vector<real> prgfCrgValG;                        // gval(icount1b)

      real fSpec;                                      // spec
      vector<integer> ibndx,ibndy,ibndz;
      integer idif1x,idif2x,inc1xa,inc1xb,inc2xa,inc2xb;
      integer idif1y,idif2y,inc1ya,inc1yb,inc2ya,inc2yb;
      integer idif1z,idif2z,inc1za,inc1zb,inc2za,inc2zb;
      vector<integer> sta1,sta2,fi1,fi2;
      integer lat1,lat2,long1,long2;
      vector<real> phimap1,phimap2;
      vector<real> bndx1,bndx2,bndx3,bndx4;
      vector<real> qmap1,qmap2;
      vector<real> debmap1,debmap2;
      real om1,om2,om3,om4,sixth;

      void setDielecBndySaltMap(); // subroutine mkdbsf()

      void setCrg(); // subroutine setcrg()
      
      void setBndy(); // subroutine setbc()

      //+++++ choices of boundary conditions
      bool isDipolarBndy(real *** phimap); // ibctyp = 2

      bool isFocusBndy(real *** phimap);   // ibctyp = 3

      bool isCoulombBndy(real *** phimap); // ibctyp = 4

      void initOddEvenItr(const int& forWhom);

      void itrOddPoints(const int& forWhom);

      void itrEvenPoints(const int& forWhom);

      void conplt(const vector<real>& array,const string& title,const int& iclr,const int& iscl,const int& imk,
                  const int& iplt,const char symb,const int& ixmin,const int& ixmax,vector<string>& iplot,real& ymin,real& ymax);

      void postItr(const vector<real>& rmaxl,const vector<real>& rmsl);

      real calculateRelaxFactor(); // subroutine relfac()

      void itit(); // subroutine itit()

      void nitit(const real& qfact); // subroutine nitit(qfact)
   
   public:
      CDelphiFastSOR(shared_ptr<IDataContainer> pdc,shared_ptr<CTimer> pt):
      /*********************************************************************************************
       *                                                                                           *
       *              references to the variables obtained from the data container                 *
       *                                                                                           *
       ********************************************************************************************/

      //++++++++++++++ const references to read-only variables from data container +++++++++++++++//
      IAbstractModule(pdc),
      pTimer(pt),
      //----- uniform parameters
      strBioModel(pdc->getKey_constRef<string>("biomodel")),
      strNumSolver(pdc->getKey_constRef<string>("solver")),
      //----- set by Statments
      iAtomNum(pdc->getKey_constRef<integer>("natom")),
      bCrgInterplateType(pdc->getKey_constRef<bool>("isph")),
      bSpectralRadius(pdc->getKey_constRef<bool>("iuspec")),
      fSpectralRadius(pdc->getKey_constRef<real>("uspec")),
      rgbPeriodicBndy(pdc->getKey_constRef< vector<bool> >("iper")),
      iNonIterateNum(pdc->getKey_constRef<int>("nnit")),
      fIonRadius(pdc->getKey_constRef<real>("exrad")),
      bFixedRelaxParam(pdc->getKey_constRef<bool>("icheb")),
      bAutoConverge(pdc->getKey_constRef<bool>("iautocon")),
      fGridConverge(pdc->getKey_constRef<real>("gten")),
      fRmsc(pdc->getKey_constRef<real>("res1")),
      fMaxc(pdc->getKey_constRef<real>("res2")),
      bLogGraph(pdc->getKey_constRef<bool>("igraph")),
      bLogPotential(pdc->getKey_constRef<bool>("ipoten")),
      bManualRelaxParam(pdc->getKey_constRef<bool>("imanual")),
      //----- io file names
      strEpsFile(pdc->getKey_constRef<string>("epsnam")),
      strPhiiFile(pdc->getKey_constRef<string>("phiinam")),
      //----- set by functions
      bDbOut(pdc->getKey_constRef<bool>("idbwrt")),
      bGridCrgOut(pdc->getKey_constRef<bool>("iwgcrg")),
      bEpsOut(pdc->getKey_constRef<bool>("epswrt")),
      bIonsEng(pdc->getKey_constRef<bool>("logions")),
      //----- set by DelPhi
      fEpsOut(pdc->getKey_constRef<real>("epsout")),
      fDebyeLength(pdc->getKey_constRef<real>("deblen")),
      fScale(pdc->getKey_constRef<real>("scale")),
      fEpsIn(pdc->getKey_constRef<real>("epsin")),
      fIonStrength(pdc->getKey_constRef<real>("rionst")),
      iDirectEpsMap(pdc->getKey_constRef<int>("idirectalg")),
      fEPKT(pdc->getKey_constRef<real>("epkt")),
      fgBoxCenter(pdc->getKey_constRef< SGrid<real> >("oldmid")),
      fgPotentialDrop(pdc->getKey_constRef< SGrid<real> >("vdrop")),
      fTaylorCoeff2(pdc->getKey_constRef<real>("chi2")),
      fTaylorCoeff3(pdc->getKey_constRef<real>("chi3")),
      fTaylorCoeff4(pdc->getKey_constRef<real>("chi4")),
      fTaylorCoeff5(pdc->getKey_constRef<real>("chi5")),
      //----- set by IO class
      iMediaNum(pdc->getKey_constRef<integer>("nmedia")),
      iObjectNum(pdc->getKey_constRef<integer>("nobject")),
      prgfMediaEps(pdc->getKey_constRef< vector<real> >("medeps")),
      //----- set by Surface class
      iCrgGridNum(pdc->getKey_constRef<integer>("nqass")),
      fMinusCrg(pdc->getKey_constRef<real>("qmin")),
      fPlusCrg(pdc->getKey_constRef<real>("qplus")),
      fgPlusCrgCenter(pdc->getKey_constRef< SGrid<real> >("cqplus")),
      fgMinusCrgCenter(pdc->getKey_constRef< SGrid<real> >("cqmin")),
      iBndyGridNum(pdc->getKey_constRef<integer>("ibnum")),
      prgigBndyGrid(pdc->getKey_constRef< vector< SGrid<integer> > >("ibgrd")),
      prgigEpsMap(pdc->getKey_constRef< vector< SGrid<integer> > >("iepsmp")),
      prgbDielecMap(pdc->getKey_constRef< vector<bool> >("idebmap")),
      iCrg2GridNum(pdc->getKey_constRef<integer>("nqgrd")),
      prggvCrg2Grid(pdc->getKey_constRef< vector< SGridValue<real> > >("chrgv2")),
      prgiCrg2GridMap(pdc->getKey_constRef< vector<integer> >("nqgrdtonqass")),
      prgfAtomEps(pdc->getKey_constRef< vector<real> >("atmeps")),
      prggvCrgedAtom(pdc->getKey_constRef< vector<SGridValue<real> > >("atmcrg")),
      //prgfgSurfCrgA(pdc->getKey_constRef< vector< SGrid<real> > >("scspos")),

      //++++++++++++++++ reference to read-and-write variables from data container +++++++++++++++//
      iGrid(pdc->getKey_Ref<integer>("igrid")), // modified in setFocusBndy
      iBndyType(pdc->getKey_Ref<int>("ibctyp")), // modified in setBndy
      fNetCrg(pdc->getKey_Ref<real>("qnet")), // modified in setCoulombBndy and setDipolarBndy
      iLinIterateNum(pdc->getKey_Ref<int>("nlit")),
      iIterateInterval(pdc->getKey_Ref<int>("icon1")),
      iConvergeFract(pdc->getKey_Ref<int>("icon2")),
      fRelaxParam(pdc->getKey_Ref<real>("relpar")),
      //----- out into data container
      iDielecBndyOdd(pdc->getKey_Ref<integer>("icount2b")),
      iCrgedGridSum(pdc->getKey_Ref<integer>("icount1b")), // modified in setcrg
      prgfGridCrg(pdc->getKey_Ref< vector<real> >("gchrg")), // modified in setcrg
      prgigGridCrgPose(pdc->getKey_Ref< vector< SGrid<integer> > >("gchrgp")), // modified in setcrg
      iCrgBndyGridNum(pdc->getKey_Ref<integer>("ibc")), // modified in setcrg
      prgdgvCrgBndyGrid(pdc->getKey_Ref< vector<SDoubleGridValue> >("cgbp")), // modified in setcrg
      prgfPhiMap(pdc->getKey_Ref< vector<real> >("phimap")),
      /*********************************************************************************************
       *                                                                                           *
       *                            variables defined in this class                                *
       *                                                                                           *
       ********************************************************************************************/

      //+++++++++++++++++++++++++++++++++ const class variables ++++++++++++++++++++++++++++++++++//
      iTotalGridNum(iGrid*iGrid*iGrid+1),
      iHalfGridNum(iTotalGridNum/2),
      iBndyDielecNum(2*(iBndyGridNum+1)),
      fDebFct(fEpsOut/(fDebyeLength*fScale*fDebyeLength*fScale)),
      fEpsDiff(fEpsIn-fEpsOut),
      fSixEps(fEpsOut*6.0),
      iEpsDim(iAtomNum+iObjectNum+2),
      nxran(60),
      nyran(20)
      {      
         if (0 != strBioModel.compare("PBE") && 0 != strNumSolver.compare("DELPHI"))
            throw CUnknownBioModelSolver(strBioModel,strNumSolver);

         //++++++++++++++++++++++++++++ local variables in this class ++++++++++++++++++++++++++++//
         iDielecBndyEven = 0;
         iCrgedGridEven  = 0;
         fSpec           = 0.0;
         prgfPhiMap.assign(iGrid*iGrid*iGrid,0.0);
         qmap1.assign(iHalfGridNum,0.0);
         qmap2.assign(iHalfGridNum,0.0);

      };               
      
      ~CDelphiFastSOR(){};
           
      virtual void validateInput();
      
      virtual void run();
};

#endif // SOLVER_FASTSOR_H
