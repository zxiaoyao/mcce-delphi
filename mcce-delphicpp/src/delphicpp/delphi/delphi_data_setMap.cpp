#include "delphi_data.h"

//-----------------------------------------------------------------------//
void CDelphiData::setMap()
{
   //--------------------- uniform parameters ---------------------//
   myData["biomodel"]    = pddm->strBioModel;
   myData["solver"]      = pddm->strNumSolver;
 
   //--------------------- set by Statements ----------------------//
   myData["iautocon"]    = pddm->bAutoConverge;
   myData["ibctyp"]      = pddm->iBndyType;
   myData["perfil"]      = pddm->fPercentageFill;
   myData["icheb"]       = pddm->bFixedRelaxParam;
   myData["isrf"]        = pddm->bOutGraspSurf;
   myData["icon2"]       = pddm->iConvergeFract;
   myData["icon1"]       = pddm->iIterateInterval;
   myData["iexun"]       = pddm->bExitUniformDielect;
   myData["repsout"]     = pddm->fExDielec;
   myData["isph"]        = pddm->bCrgInterplateType;
   myData["gten"]        = pddm->fGridConverge;
   myData["igrid"]       = pddm->iGrid;
   myData["repsin"]      = pddm->fInDielec;
   myData["conc"]        = pddm->rgfSalt; // std::vector
   myData["exrad"]       = pddm->fIonRadius;
   myData["nlit"]        = pddm->iLinIterateNum;
   myData["igraph"]      = pddm->bLogGraph;
   myData["ipoten"]      = pddm->bLogPotential;
   myData["res2"]        = pddm->fMaxc;
   myData["nnit"]        = pddm->iNonIterateNum;
   myData["iper"]        = pddm->rgbPeriodicBndy; // std::vector
   myData["iconc"]       = pddm->bOutCrgDensity;
   myData["radprb"]      = pddm->rgfProbeRadius; // std::vector
   myData["uspec"]       = pddm->fSpectralRadius;
   myData["relpar"]      = pddm->fRelaxParam;
   myData["res1"]        = pddm->fRmsc;
   myData["scale"]       = pddm->fScale;
   myData["isolv"]       = pddm->bSolvePB;
   myData["ival"]        = pddm->rgiValence1; // std::vector
   myData["ival2"]       = pddm->rgiValence2; // std::vector
   myData["atompotdist"] = pddm->fPotentialUpperBond;
   myData["temperature"] = pddm->fTemper;
   myData["vdrop"]       = pddm->fgPotentialDrop; // SGrid<real>
   myData["iuspec"]      = pddm->bSpectralRadius;
   myData["imanual"]     = pddm->bManualRelaxParam;
   //-------------------------- io file names ------------------------//   
   //myData["prmnam"]    = pddm->strParamFile[0]; // (not to be mapped)
   myData["siznam"]      = pddm->strSizeFile;
   myData["crgnam"]      = pddm->strCrgFile;
   myData["pdbnam"]      = pddm->strPdbFile;
   myData["phinam"]      = pddm->strPhiFile;
   myData["frcinam"]     = pddm->strFrciFile;
   myData["frcnam"]      = pddm->strFrcFile;
   myData["epsnam"]      = pddm->strEpsFile;
   myData["phiinam"]     = pddm->strPhiiFile;
   myData["mpdbnam"]     = pddm->strModifiedPdbFile;
   myData["updbnam"]     = pddm->strUnformatPdbFile;
   myData["ufrcnam"]     = pddm->strUnformatFrcFile;
   myData["srfnam"]      = pddm->strGraspFile;
   myData["nrgnam"]      = pddm->strEnergyFile;
   myData["scrgnam"]     = pddm->strScrgFile;
   //myData["centnam"]   = pddm->strCentFile; // renamed to be fort.27 (not to be mapped)
   //----------------------- set by functions ------------------------//
   // set by CENTER or CENT function: 
   myData["offset"]      = pddm->fgOffCenter; // SGrid<real>

   // set by ACENTER or ACENT function
   myData["acent"]       = pddm->fgAcent; // SGrid<real>
   myData["iacent"]      = pddm->bIsAcent;
   
   // set by READ or IN function
   myData["pdbfrm"]      = pddm->iPdbFormatIn;
   myData["ipdbrd"]      = pddm->bPdbUnformatIn;
   
   // set by WRITE or OUT function
   myData["phiwrt"]      = pddm->bPhimapOut;
   myData["phifrm"]      = pddm->iPhiFormatOut;
   myData["ibios"]       = pddm->bBiosystemOut;
   myData["ibem"]        = pddm->bBemSrfOut;
   myData["isite"]       = pddm->bSiteOut;
   myData["frcfrm"]      = pddm->iFrcFormatOut;
   myData["epswrt"]      = pddm->bEpsOut;
   myData["iatout"]      = pddm->bModPdbOut;
   myData["mpdbfrm"]     = pddm->iModPdbFormatOut;
   myData["ipdbwrt"]     = pddm->bUnformatPdbOut;   
   myData["ifrcwrt"]     = pddm->bUnformatFrcOut;
   myData["inrgwrt"]     = pddm->bEngOut;
   myData["iwgcrg"]      = pddm->bGridCrgOut;
   myData["iacs"]        = pddm->bHsurf2DatOut;
   myData["idbwrt"]      = pddm->bDbOut;
   myData["isen"]        = pddm->bSurfEngOut;
   myData["isch"]        = pddm->bSurfCrgOut;
   myData["scrgfrm"]     = pddm->iSurfCrgFormatOut;
   
   // set by ENERGY function
   myData["logg"]        = pddm->bGridEng;
   myData["logs"]        = pddm->bSolvEng;
   myData["logas"]       = pddm->bAnalySurfEng;
   myData["loga"]        = pddm->bAnalyEng;
   myData["logions"]     = pddm->bIonsEng;
   myData["logc"]        = pddm->bCoulombEng;
   
   // set by SITE function: all MUST be initialized to to false
   myData["isita"]       = pddm->bAtomInSite;
   myData["isitq"]       = pddm->bCrgInSite;
   myData["isitp"]       = pddm->bGridPotentialInSite;
   myData["isitap"]      = pddm->bAtomPotentialInSite;
   myData["isitdeb"]     = pddm->bDebyeFractionInSite;
   myData["isitf"]       = pddm->bFieldInSite;
   myData["isitr"]       = pddm->bReactPotentialInSite;
   myData["isitc"]       = pddm->bCoulombPotentialInSite;
   myData["isitx"]       = pddm->bAtomCoordInSite;
   myData["isiti"]       = pddm->bSaltInSite;
   myData["isitt"]       = pddm->bTotalPotentialInSite;
   myData["isitrf"]      = pddm->bReactForceInSite;
   myData["isitcf"]      = pddm->bCoulombForceInSite;
   myData["isitmd"]      = pddm->bMDInSite;
   myData["isitsf"]      = pddm->bSurfCrgInSite;
   myData["isittf"]      = pddm->bTotalForceInSite;
   myData["isitpot"]     = pddm->bPotentialInSite;
   myData["irea"]        = pddm->bReactFieldInFRC;
   myData["iself"]       = pddm->bPDB2FRCInSite;

   // set by BUFFZ function
   myData["buffz"]       = pddm->ieBuffz;
   myData["ibufz"]       = pddm->bIsBuffz;
   
   // set by SURFACE function
   myData["isurftype"]   = pddm->iTypeSurf;
   //----------------------- set by DelPhi ------------------------//   
   myData["deblen"]      = pddm->fDebyeLength;    
   myData["epsout"]      = pddm->fEpsOut;   
   myData["cran"]        = pddm->fgCoordinateRange;
   myData["pmid"]        = pddm->fgGeometricCenter;
   myData["oldmid"]      = pddm->fgBoxCenter;
   myData["rionst"]      = pddm->fIonStrength;
   myData["chi1"]        = pddm->fTaylorCoeff1;   
   myData["chi2"]        = pddm->fTaylorCoeff2;
   myData["chi3"]        = pddm->fTaylorCoeff3;
   myData["chi4"]        = pddm->fTaylorCoeff4;
   myData["chi5"]        = pddm->fTaylorCoeff5;
   myData["lognl"]       = pddm->bNonlinearEng;
   myData["epkt"]        = pddm->fEPKT;
   myData["epsin"]       = pddm->fEpsIn;  
   myData["ifrcrd"]      = pddm->bFrcUnformatIn;
   myData["idirectalg"]  = pddm->iDirectEpsMap;
   myData["numbmol"]     = pddm->iMoleculeNum;
   myData["rdmx"]        = pddm->fMaxRadius;   
   myData["uniformdiel"] = pddm->bUniformDielec;   
   myData["limobject"]   = pddm->prgfeExtrema;     // std::vector< SExtrema<real> >
   myData["xn1"]         = pddm->prgfgAtomCoordA;  // std::vector< SGrid<real> >
   myData["xn2"]         = pddm->prgfgAtomCoordG;  // std::vector< SGrid<real> >
   //----------------------- set by IO class ------------------------//
   myData["resnummax"]   = pddm->iResidueNum;
   myData["nmedia"]      = pddm->iMediaNum;   
   myData["medeps"]      = pddm->prgfMediaEps;     // std::vector<real>
   myData["nobject"]     = pddm->iObjectNum;   
   myData["dataobject"]  = pddm->prgstrObject;     // std::vector<string>
   myData["natom"]       = pddm->iAtomNum;   
   myData["delphipdb"]   = pddm->prgapAtomPdb;     // std::vector<CAtomPdb>
   myData["iatmmed"]     = pddm->prgiAtomMediaNum; // std::vector<integer>
   myData["ionlymol"]    = pddm->bOnlyMolecule;    
   //myData["ndistr"]    = pddm->iCrgDistrNum;
   //myData["datadistr"] = pddm->prgstrCrgDistr;   
   //------------------- set by Surface class ---------------------//
   myData["nqass"]       = pddm->iCrgGridNum;
   myData["qnet"]        = pddm->fNetCrg;
   myData["qmin"]        = pddm->fMinusCrg;
   myData["qplus"]       = pddm->fPlusCrg; 
   myData["cqplus"]      = pddm->fgPlusCrgCenter;
   myData["cqmin"]       = pddm->fgMinusCrgCenter;
   myData["cmin"]        = pddm->fgMinCoordinate;
   myData["cmax"]        = pddm->fgMaxCoordinate;
   myData["ibnum"]       = pddm->iBndyGridNum; 
   myData["iepsmp"]      = pddm->prgigEpsMap;      // std::vector< SGrid<integer> >
   myData["idebmap"]     = pddm->prgbDielecMap;    // std::vector<bool>
   myData["ibgrd"]       = pddm->prgigBndyGrid;    // std::vector< SGrid<integer> >
   myData["nqgrd"]       = pddm->iCrg2GridNum;
   myData["chrgv2"]      = pddm->prggvCrg2Grid;    // std::vector< SGridValue<real> >
   myData["nqgrdtonqass"]= pddm->prgiCrg2GridMap;  // std::vector<integer>
   myData["atmcrg"]      = pddm->prggvAtomCrg;     // std::vector< SGridValue<real> >
   myData["chgpos"]      = pddm->prgfgCrgPoseA;    // std::vector< SGrid<real> >
   myData["scspos"]      = pddm->prgfgSurfCrgA;    // std::vector< SGrid<real> >
   myData["crgatn"]      = pddm->prgiCrgAt;        // std::vector<integer>
   myData["atsurf"]      = pddm->prgiAtSurf;       // std::vector<integer>
   myData["atndx"]       = pddm->prgiAtSurf;       // std::vector<integer>
   myData["scsnor"]      = pddm->prgfgSurfCrgE;    // std::vector< SGrid<real> >
   myData["atmeps"]      = pddm->prgfAtomEps;      // std::vector<real>
   //------------------- set by Solver class ---------------------//
   myData["icount2b"]    = pddm->iDielecBndySum;
   myData["icount1b"]    = pddm->iCrgedGridSum;
   myData["gchrg"]       = pddm->prgfGridCrg;      // std::vector<real>
   myData["gchrgp"]      = pddm->prgigGridCrgPose; // std::vector< SGrid<integer> >
   myData["ibc"]         = pddm->iCrgBdyGrid;
   myData["cgbp"]        = pddm->prgdgvCrgBndyGrid;// std::vector<SDoubleGridValue>
   myData["phimap"]      = pddm->prgfPhimap;       // std::vector<real>
   //------------------- set by Energy class ---------------------//
   myData["schrg"]       = pddm->prgfSurfCrgE;     // std::vector<real>
}



