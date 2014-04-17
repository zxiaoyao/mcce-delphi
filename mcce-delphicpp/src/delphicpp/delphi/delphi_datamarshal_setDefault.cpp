/*
 * delphi_datamarshal_setDefault.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: chuan
 */

#include "delphi_datamarshal.h"

void CDelphiDataMarshal::setDefault()
{
   //----------------------- set by Statments ------------------------//
   bAutoConverge        = true;         // iautocon AUTOC
   iBndyType            = 2;            // ibctyp   BNDCON
   fPercentageFill      = 80.0;         // perfil   PERFIL
   bFixedRelaxParam     = false;        // icheb    CHEBIT
   bOutGraspSurf        = false;        // isrf     CLCSRF
   iConvergeFract       = 1;            // icon2    CONFRA
   iIterateInterval     = 10;           // icon1    CONINT
   bExitUniformDielect  = false;        // iexun    EXITUN
   fExDielec            = 80;           // repsout  EXDI
   bCrgInterplateType   = false;        // isph     FCRG
   fGridConverge        = 0.0;          // gten     GRDCON
   iGrid                = 0;            // igrid    GSIZE
   fInDielec            = 2.0;          // repsin   INDI
   rgfSalt.push_back(0.0);              // conc     SALT,SALT2
   rgfSalt.push_back(0.0);
   fIonRadius           = 2.0;          // exrad    IONRAD
   iLinIterateNum       = 0;            // nlit     LINIT
   bLogGraph            = false;        // igraph   LOGGRP
   bLogPotential        = false;        // ipoten   LOGPOT
   fMaxc                = 0.0;          // res2     MAXC
   iNonIterateNum       = 0;            // nnit     NONIT
   rgbPeriodicBndy.push_back(false);    // iper     PBX,PBY,PBZ
   rgbPeriodicBndy.push_back(false);
   rgbPeriodicBndy.push_back(false);
   rgbPeriodicBndy.push_back(false);
   rgbPeriodicBndy.push_back(false);
   rgbPeriodicBndy.push_back(false);
   bOutCrgDensity       = false;        // iconc    PHICON
   rgfProbeRadius.push_back(1.4);       // radprb   PRBRAD,RADPR2
   rgfProbeRadius.push_back(-1.0);
   fSpectralRadius      = 0.9975;       // uspec    RELFAC
   fRelaxParam          = 1.0;          // relpar   RELPAR
   fRmsc                = 0.0;          // res1     RMSC
   fScale               = 1.2;          // scale    SCALE
   bSolvePB             = true;         // isolv    SOLVPB
   rgiValence1.push_back(1);            // ival     VAL+1,VAL-1
   rgiValence1.push_back(1);
   rgiValence2.push_back(0);            // ival2    VAL+2,VAL-2
   rgiValence2.push_back(0);
   fPotentialUpperBond  = 0.5;          // atompotdist  ATPODS
   fTemper              = 297.3342119;  // temperature  TEMPER
   fgPotentialDrop.nX   = 0.0;          // vdrop
   fgPotentialDrop.nY   = 0.0;
   fgPotentialDrop.nZ   = 0.0;
   bSpectralRadius      = false;        // iuspec
   bManualRelaxParam    = false;        // imanual

   //-------------------------- io file names ------------------------//
   //strParamFile       = "fort.10";    // prmnam
   strSizeFile          = "fort.11";    // siznam
   strCrgFile           = "fort.12";    // crgnam
   strPdbFile           = "fort.13";    // pdbnam
   strPhiFile           = "fort.14";    // phinam
   strFrciFile          = "fort.15";    // frcinam
   strFrcFile           = "fort.16";    // frcnam
   strEpsFile           = "fort.17";    // epsnam
   strPhiiFile          = "fort.18";    // phiinam
   strModifiedPdbFile   = "fort.19";    // mpdbnam
   strUnformatPdbFile   = "fort.20";    // updbnam
   strUnformatFrcFile   = "fort.21";    // ufrcnam
   strGraspFile         = "grasp.srf";  // srfnam
   strEnergyFile        = "energy.dat"; // nrgnam
   strScrgFile          = "scrg.dat";   // scrgnam

   //----------------------- set by functions ------------------------//
   // set by CENTER or CENT function:
   fgOffCenter.nX       = 0.0;          // offset
   fgOffCenter.nY       = 0.0;
   fgOffCenter.nZ       = 0.0;

   // set by ACENTER or ACENT function
   fgAcent.nX           = 0.0;          // acent
   fgAcent.nY           = 0.0;
   fgAcent.nZ           = 0.0;
   bIsAcent             = false;        // iacent

   // set by READ or IN function
   iPdbFormatIn         = 10;           // pdbfrm
   bPdbUnformatIn       = false;        // ipdbrd

   // set by WRITE or OUT function
   bPhimapOut           = false;        // phiwrt
   iPhiFormatOut        = 0;            // phifrm
   bBiosystemOut        = false;        // ibios
   bBemSrfOut           = false;        // ibem
   bSiteOut             = false;        // isite
   iFrcFormatOut        = 0;            // frcfrm
   bEpsOut              = false;        // epswrt
   bModPdbOut           = false;        // iatout
   iModPdbFormatOut     = 0;            // mpdbfrm
   bUnformatPdbOut      = false;        // ipdbwrt
   bUnformatFrcOut      = false;        // ifrcwrt
   bEngOut              = false;        // inrgwrt
   bGridCrgOut          = false;        // iwgcrg
   bHsurf2DatOut        = false;        // iacs
   bDbOut               = false;        // idbwrt
   bSurfEngOut          = false;        // isen
   bSurfCrgOut          = false;        // isch
   iSurfCrgFormatOut    = 0;            // scrgfrm

   // set by ENERGY function
   bGridEng             = false;        // logg
   bSolvEng             = false;        // logs
   bAnalySurfEng        = false;        // logas
   bAnalyEng            = false;        // loga
   bIonsEng             = false;        // logions
   bCoulombEng          = false;        // logc

   // set by SITE function: all MUST be initialized to to false
   bAtomInSite          = false;        // isita
   bCrgInSite           = false;        // isitq
   bGridPotentialInSite = false;        // isitp
   bAtomPotentialInSite = false;        // isitap
   bDebyeFractionInSite = false;        // isitdeb
   bFieldInSite         = false;        // isitf
   bReactPotentialInSite= false;        // isitr
   bCoulombPotentialInSite = false;     // isitc
   bAtomCoordInSite     = false;        // isitx
   bSaltInSite          = false;        // isiti
   bTotalPotentialInSite= false;        // isitt
   bReactForceInSite    = false;        // isitrf
   bCoulombForceInSite  = false;        // isitcf
   bMDInSite            = false;        // isitmd
   bSurfCrgInSite       = false;        // isitsf
   bTotalForceInSite    = false;        // isittf
   bPotentialInSite     = false;        // isitpot
   bReactFieldInFRC     = false;        // irea
   bPDB2FRCInSite       = false;        // iself

   // set by BUFZ function
   ieBuffz.nMin.nX      = 0;            // bufz
   ieBuffz.nMin.nY      = 0;
   ieBuffz.nMin.nZ      = 0;
   ieBuffz.nMax.nX      = 0;
   ieBuffz.nMax.nY      = 0;
   ieBuffz.nMax.nZ      = 0;
   bIsBuffz             = false;        // ibufz

   // set by SURFACE function
   iTypeSurf            = -1;           // iTypeSurf

   //------------------------------ DelPhi ---------------------------//
   fDebyeLength         = 0.0;          // deblen
   fEpsOut              = 80.0;         // epsout
   fgCoordinateRange.nX = 0.0;          // cran
   fgCoordinateRange.nY = 0.0;
   fgCoordinateRange.nZ = 0.0;
   fgGeometricCenter.nX = 0.0;          // pmid
   fgGeometricCenter.nY = 0.0;
   fgGeometricCenter.nZ = 0.0;
   fgBoxCenter.nX       = 0.0;          // oldmid
   fgBoxCenter.nY       = 0.0;
   fgBoxCenter.nZ       = 0.0;
   fIonStrength         = 0.0;          // rionst
   fTaylorCoeff1        = 0.0;          // chi1
   fTaylorCoeff2        = 0.0;          // chi2
   fTaylorCoeff3        = 0.0;          // chi3
   fTaylorCoeff4        = 0.0;          // chi4
   fTaylorCoeff5        = 0.0;          // chi5
   bNonlinearEng        = false;        // lognl
   fEPKT                = 0.0;          // epkt
   fEpsIn               = 2.0;          // epsin
   bFrcUnformatIn       = false;        // ifrcrd
   iDirectEpsMap        = 1;            // iDirectEpsMap
   iMoleculeNum         = 0;            // numbmol
   fMaxRadius           = 0.01;         // rdmx
   bUniformDielec       = true;         // uniformdiel

   //-------------------------------- IO -----------------------------//
   iResidueNum          = 0;            // resnummax
   iMediaNum            = 1;            // nmedia
   iObjectNum           = 1;            // nobject
   iAtomNum             = 0;            // natom
   bOnlyMolecule        = true;         // ionlymol

   //------------------------------ Surface --------------------------//
   iCrgGridNum          = 0;            // nqass
   fNetCrg              = 0.0;          // qnet
   fMinusCrg            = 0.0;          // qmin
   fPlusCrg             = 0.0;          // qplus
   fgPlusCrgCenter.nX   = 0.0;          // cqplus
   fgPlusCrgCenter.nY   = 0.0;
   fgPlusCrgCenter.nZ   = 0.0;
   fgMinusCrgCenter.nX  = 0.0;          // cqmin
   fgMinusCrgCenter.nY  = 0.0;
   fgMinusCrgCenter.nZ  = 0.0;
   fgMinCoordinate.nX   = 6000.0;       // cmin
   fgMinCoordinate.nY   = 6000.0;
   fgMinCoordinate.nZ   = 6000.0;
   fgMaxCoordinate.nX   =-6000.0;       // cmax
   fgMaxCoordinate.nY   =-6000.0;
   fgMaxCoordinate.nZ   =-6000.0;
   iBndyGridNum         = 0;            // ibnum
   iCrg2GridNum         = 0;            // nqgrd

   //------------------------------ Solver ---------------------------//
   iDielecBndySum       = 0;            // icount2b
   iCrgedGridSum        = 0;            // icount1b
   iCrgBdyGrid          = 0;            // ibc

   //---------------------------- statements -------------------------//
   strFullState[0]      = "UNUSED";
   strFullState[1]      = "GSIZE";
   strFullState[2]      = "SCALE";
   strFullState[3]      = "PERFIL";
   strFullState[4]      = "INDI";
   strFullState[5]      = "EXDI";
   strFullState[6]      = "PRBRAD";
   strFullState[7]      = "IONRAD";
   strFullState[8]      = "SALT";
   strFullState[9]      = "BNDCON";
   strFullState[10]     = "LINIT";
   strFullState[11]     = "NONIT";
   //strFullState[12]   = "MEMDAT"; // OBSOLELE. REMOVED FROM THE LIST.
   strFullState[12]     = "UNUSED";
   strFullState[13]     = "FCRG";
   strFullState[14]     = "LOGPOT";
   strFullState[15]     = "LOGGRP";
   strFullState[16]     = "CONINT";
   strFullState[17]     = "CONFRA";
   strFullState[18]     = "PBX";
   strFullState[19]     = "PBY";
   strFullState[20]     = "PBZ";
   strFullState[21]     = "AUTOC";
   strFullState[22]     = "EXITUN";
   strFullState[23]     = "GRDCON";
   strFullState[24]     = "RELFAC";
   strFullState[25]     = "CHEBIT";
   strFullState[26]     = "SOLVPB";
   strFullState[27]     = "CLCSRF";
   strFullState[28]     = "PHICON";
   //strFullState[29]   = "RADPOL"; // ONLY FOR OBJECTS. REMOVED FROM THE LIST.
   strFullState[29]     = "UNUSED";
   strFullState[30]     = "RELPAR";
   strFullState[31]     = "SALT2";
   strFullState[32]     = "RADPR2";
   strFullState[33]     = "VAL+1";
   strFullState[34]     = "VAL-1";
   strFullState[35]     = "VAL+2";
   strFullState[36]     = "VAL-2";
   strFullState[37]     = "RMSC";
   strFullState[38]     = "MAXC";
   //strFullState[39]   = "NORMC"; // UNUSED. REMOVED FROM THE LIST.
   strFullState[39]     = "UNUSED";
   strFullState[40]     = "VDROPX";
   strFullState[41]     = "VDROPY";
   strFullState[42]     = "VDROPZ";
   strFullState[43]     = "ATPODS";
   strFullState[44]     = "TEMPER";

   strShortState[0]     = "UNUSED";
   strShortState[1]     = "GS";
   strShortState[2]     = "SC";
   strShortState[3]     = "PF";
   strShortState[4]     = "ID";
   strShortState[5]     = "ED";
   strShortState[6]     = "PR";
   strShortState[7]     = "IR";
   strShortState[8]     = "IS";
   strShortState[9]     = "BC";
   strShortState[10]    = "LI";
   strShortState[11]    = "NI";
   //strShortState[12]  = "MD"; // OBSOLELE. REMOVED FROM THE LIST.
   strShortState[12]    = "UNUSED";
   strShortState[13]    = "FC";
   strShortState[14]    = "LP";
   strShortState[15]    = "LG";
   strShortState[16]    = "CI";
   strShortState[17]    = "CF";
   strShortState[18]    = "PX";
   strShortState[19]    = "PY";
   strShortState[20]    = "PZ";
   strShortState[21]    = "AC";
   strShortState[22]    = "XU";
   strShortState[23]    = "GC";
   strShortState[24]    = "RF";
   strShortState[25]    = "CI";
   strShortState[26]    = "SP";
   strShortState[27]    = "CS";
   strShortState[28]    = "PC"; // new for PHICON
   strShortState[29]    = "RL";
   strShortState[30]    = "RR";
   strShortState[31]    = "S2";
   strShortState[32]    = "R2";
   strShortState[33]    = "+1";
   strShortState[34]    = "-1";
   strShortState[35]    = "+2";
   strShortState[36]    = "-2";
   strShortState[37]    = "MC";
   strShortState[38]    = "XC";
   strShortState[39]    = "NC";
   strShortState[40]    = "VX";
   strShortState[41]    = "VY";
   strShortState[42]    = "VZ";
   strShortState[43]    = "AD";
   strShortState[44]    = "TE";

   //------------------------------ functions ------------------------//
   strFullFunc[0]       = "UNUSED";
   strFullFunc[1]       = "CENTER";
   strFullFunc[2]       = "ACENTER";
   strFullFunc[3]       = "READ";
   strFullFunc[4]       = "WRITE";
   strFullFunc[5]       = "ENERGY";
   strFullFunc[6]       = "SITE";
   strFullFunc[7]       = "BUFFZ";
   strFullFunc[8]       = "QPREF";
   strFullFunc[9]       = "INSOBJ";
   strFullFunc[10]      = "SURFACE";
   strFullFunc[11]      = "SOLVER";

   strShortFunc[0]      = "UNUSED";
   strShortFunc[1]      = "CENT";
   strShortFunc[2]      = "ACENT";
   strShortFunc[3]      = "IN";
   strShortFunc[4]      = "OUT";

   //------------------------------ LOCAL ----------------------------//
   strCentFile          = "fort.27";    // centnam (not to be mapped)
   fMaxDimension        = 0.0;          // rmaxdim (not to be mapped)
}
