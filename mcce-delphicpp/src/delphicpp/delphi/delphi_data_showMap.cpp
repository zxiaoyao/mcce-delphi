#include "delphi_data.h"

//-----------------------------------------------------------------------//
void CDelphiData::showMap(const string& strMapFile)
{
   //string strMapFile = "delphicpp.dat";

   ofstream ofMapStream(strMapFile.c_str());
   ofMapStream << boolalpha;
   ofMapStream << fixed << setprecision(7);

//   ofMapStream << endl;
//   ofMapStream << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n";
//   ofMapStream << "+                                                        + \n";
//   ofMapStream << "+  DELPHI DATA CONTAINER size = " <<myData.size() << ")  + \n";
//   ofMapStream << "+                                                        + \n";
//   ofMapStream << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n";

   ofMapStream << "------------------- uniform parameters -----------------"    << endl;
   ofMapStream << "          biomodel : " << getKey_constRef<string>("biomodel")     << endl;
   ofMapStream << "            solver : " << getKey_constRef<string>("solver")       << endl;
   ofMapStream << "------------------- set by statements ------------------"    << endl;
   ofMapStream << "   iautocon(AUTOC) : " << (getKey_constRef<bool>("iautocon")?'T':'F') << endl;
   ofMapStream << "    ibctyp(BNDCON) : " << getKey_constRef<int>("ibctyp")          << endl;
   ofMapStream << "    perfil(PERFIL) : " << getKey_constRef<real>("perfil")         << endl;
   ofMapStream << "     icheb(CHEBIT) : " << (getKey_constRef<bool>("icheb")?'T':'F')<< endl;
   ofMapStream << "      isrf(CLCSRF) : " << (getKey_constRef<bool>("isrf")?'T':'F') << endl;
   ofMapStream << "     icon2(CONFRA) : " << getKey_constRef<int>("icon2")           << endl;
   ofMapStream << "     icon1(CONINT) : " << getKey_constRef<int>("icon1")           << endl;
   ofMapStream << "     iexun(EXITUN) : " << (getKey_constRef<bool>("iexun")?'T':'F')<< endl;
   ofMapStream << "     repsout(EXDI) : " << getKey_constRef<real>("repsout")        << endl;
   ofMapStream << "        isph(FCRG) : " << (getKey_constRef<bool>("isph")?'T':'F') << endl;
   ofMapStream << "      gten(GRDCON) : " << getKey_constRef<real>("gten")           << endl;
   ofMapStream << "      igrid(GSIZE) : " << getKey_constRef<integer>("igrid")       << endl;
   ofMapStream << "      repsin(INDI) : " << getKey_constRef<real>("repsin")         << endl;

   {
      const vector<real> rgfSalt = getKey_constRef< vector<real> >("conc");
      ofMapStream << "  conc(SALT,SALT2) : " << rgfSalt[0] << " " << rgfSalt[1] << endl;
   }

   ofMapStream << "     exrad(IONRAD) : " << getKey_constRef<real>("exrad")          << endl;
   ofMapStream << "       nlit(LINIT) : " << getKey_constRef<int>("nlit")            << endl;
   ofMapStream << "    igraph(LOGGRP) : " << (getKey_constRef<bool>("igraph")?'T':'F')<< endl;
   ofMapStream << "    ipoten(LOGPOT) : " << (getKey_constRef<bool>("ipoten")?'T':'F')<< endl;
   ofMapStream << "        res2(MAXC) : " << getKey_constRef<real>("res2")           << endl;
   ofMapStream << "       nnit(NONIT) : " << getKey_constRef<int>("nnit")            << endl;

   {
      const vector<bool> rgbPeriodicBndy = getKey_constRef< vector<bool> >("iper");
      ofMapStream << "    iper1-3(PBX-Z) : " << (rgbPeriodicBndy[0]?'T':'F') << " "
                                             << (rgbPeriodicBndy[1]?'T':'F') << " "
                                             << (rgbPeriodicBndy[2]?'T':'F') << endl;
      ofMapStream << " iper4-6(VDROPX-Z) : " << (rgbPeriodicBndy[3]?'T':'F') << " "
                                             << (rgbPeriodicBndy[4]?'T':'F') << " "
                                             << (rgbPeriodicBndy[5]?'T':'F') << endl;
   }

   ofMapStream << "     iconc(PHICON) : " << (getKey_constRef<bool>("iconc")?'T':'F') << endl;

   {
      const vector<real> rgfProbeRadius = getKey_constRef< vector<real> >("radprb");
      ofMapStream << "    radprb(PRBRAD) : " << rgfProbeRadius[0] << " " << rgfProbeRadius[1] << endl;
   }

   ofMapStream << "     uspec(RELFAC) : " << getKey_constRef<real>("uspec")          << endl;
   ofMapStream << "    relpar(RELPAR) : " << getKey_constRef<real>("relpar")         << endl;
   ofMapStream << "        res1(RMSC) : " << getKey_constRef<real>("res1")           << endl;
   ofMapStream << "      scale(SCALE) : " << getKey_constRef<real>("scale")          << endl;
   ofMapStream << "     isolv(SOLVPB) : " << (getKey_constRef<bool>("isolv")?'T':'F')<< endl;

   {
      const vector<int> rgiValence1 = getKey_constRef< vector<int> >("ival");
      ofMapStream << " ival(VAL+1,VAL-1) : " << rgiValence1[0] << " " << rgiValence1[1] << endl;
   }

   {
      const vector<int> rgiValence2 = getKey_constRef< vector<int> >("ival2");
      ofMapStream << "ival2(VAL+2,VAL-2) : " << rgiValence2[0] << " " << rgiValence2[1] << endl;
   }

   ofMapStream << "atompotdist(ATPODS): " << getKey_constRef<real>("atompotdist")    << endl;
   ofMapStream << "temperature(TEMPER): " << getKey_constRef<real>("temperature")    << endl;
   ofMapStream << "      vdrop(VDROP) : " << getKey_constRef< SGrid<real> >("vdrop").nX << " "
                                           << getKey_constRef< SGrid<real> >("vdrop").nY << " "
                                           << getKey_constRef< SGrid<real> >("vdrop").nZ << endl;
   ofMapStream << "            iuspec : " << (getKey_constRef<bool>("iuspec")?'T':'F') << endl;
   ofMapStream << "           imanual : " << (getKey_constRef<bool>("imanual")?'T':'F') << endl;
   ofMapStream << "------------------- io file names ------------------"        << endl;
   //ofMapStream << "           prmnam : " << getKey_constRef<string>("prmnam")     << endl;
   //ofMapStream << "          centnam : " << getKey_constRef<string>("centnam")    << endl;
   ofMapStream << "            siznam : " << getKey_constRef<string>("siznam")       << endl;
   ofMapStream << "            crgnam : " << getKey_constRef<string>("crgnam")       << endl;
   ofMapStream << "            pdbnam : " << getKey_constRef<string>("pdbnam")       << endl;
   ofMapStream << "            phinam : " << getKey_constRef<string>("phinam")       << endl;
   ofMapStream << "           frcinam : " << getKey_constRef<string>("frcinam")      << endl;
   ofMapStream << "            frcnam : " << getKey_constRef<string>("frcnam")       << endl;
   ofMapStream << "            epsnam : " << getKey_constRef<string>("epsnam")       << endl;
   ofMapStream << "           phiinam : " << getKey_constRef<string>("phiinam")      << endl;
   ofMapStream << "           mpdbnam : " << getKey_constRef<string>("mpdbnam")      << endl;
   ofMapStream << "           updbnam : " << getKey_constRef<string>("updbnam")      << endl;
   ofMapStream << "           ufrcnam : " << getKey_constRef<string>("ufrcnam")      << endl;
   ofMapStream << "            srfnam : " << getKey_constRef<string>("srfnam")       << endl;
   ofMapStream << "            nrgnam : " << getKey_constRef<string>("nrgnam")       << endl;
   ofMapStream << "           scrgnam : " << getKey_constRef<string>("scrgnam")      << endl;
   ofMapStream << "------------------ set by functions ----------------"             << endl;
   // set by CENTER or CENT function:
   ofMapStream << "            offset : " << getKey_constRef< SGrid<real> >("offset").nX << " "
                                          << getKey_constRef< SGrid<real> >("offset").nY << " "
                                          << getKey_constRef< SGrid<real> >("offset").nZ << endl;
   // set by ACENTER or ACENT function
   ofMapStream << "             acent : " << getKey_constRef< SGrid<real> >("acent").nX << " "
                                          << getKey_constRef< SGrid<real> >("acent").nY<< " "
                                          << getKey_constRef< SGrid<real> >("acent").nZ<< endl;
   ofMapStream << "            iacent : " << (getKey_constRef<bool>("iacent")?'T':'F') << endl;
   // set by READ or IN function
   ofMapStream << "            pdbfrm : " << getKey_constRef<int>("pdbfrm")          << endl;
   ofMapStream << "            ipdbrd : " << (getKey_constRef<bool>("ipdbrd")?'T':'F') << endl;
   // set by WRITE or OUT function
   ofMapStream << "            phiwrt : " << (getKey_constRef<bool>("phiwrt")?'T':'F') << endl;
   ofMapStream << "            phifrm : " << getKey_constRef<int>("phifrm")          << endl;
   ofMapStream << "             ibios : " << (getKey_constRef<bool>("ibios")?'T':'F')<< endl;
   ofMapStream << "              ibem : " << (getKey_constRef<bool>("ibem")?'T':'F') << endl;
   ofMapStream << "             isite : " << (getKey_constRef<bool>("isite")?'T':'F')<< endl;
   ofMapStream << "            frcfrm : " << getKey_constRef<int>("frcfrm")          << endl;
   ofMapStream << "            epswrt : " << (getKey_constRef<bool>("epswrt")?'T':'F') << endl;
   ofMapStream << "            iatout : " << (getKey_constRef<bool>("iatout")?'T':'F')<< endl;
   ofMapStream << "           mpdbfrm : " << getKey_constRef<int>("mpdbfrm")         << endl;
   ofMapStream << "           ipdbwrt : " << (getKey_constRef<bool>("ipdbwrt")?'T':'F')<< endl;
   ofMapStream << "           ifrcwrt : " << (getKey_constRef<bool>("ifrcwrt")?'T':'F')<< endl;
   ofMapStream << "           inrgwrt : " << (getKey_constRef<bool>("inrgwrt")?'T':'F')<< endl;
   ofMapStream << "            iwgcrg : " << (getKey_constRef<bool>("iwgcrg")?'T':'F')<< endl;
   ofMapStream << "              iacs : " << (getKey_constRef<bool>("iacs")?'T':'F') << endl;
   ofMapStream << "            idbwrt : " << (getKey_constRef<bool>("idbwrt")?'T':'F') << endl;
   ofMapStream << "              isen : " << (getKey_constRef<bool>("isen")?'T':'F') << endl;
   ofMapStream << "              isch : " << (getKey_constRef<bool>("isch")?'T':'F') << endl;
   ofMapStream << "           scrgfrm : " << getKey_constRef<int>("scrgfrm")         << endl;
   // set by ENERGY function
   ofMapStream << "              logg : " << (getKey_constRef<bool>("logg")?'T':'F') << endl;
   ofMapStream << "              logs : " << (getKey_constRef<bool>("logs")?'T':'F') << endl;
   ofMapStream << "             logas : " << (getKey_constRef<bool>("logas")?'T':'F')<< endl;
   ofMapStream << "              loga : " << (getKey_constRef<bool>("loga")?'T':'F') << endl;
   ofMapStream << "           logions : " << (getKey_constRef<bool>("logions")?'T':'F') << endl;
   ofMapStream << "              logc : " << (getKey_constRef<bool>("logc")?'T':'F') << endl;
   // set by SITE function: all MUST be initialized to to false
   ofMapStream << "             isita : " << (getKey_constRef<bool>("isita")?'T':'F')<< endl;
   ofMapStream << "             isitq : " << (getKey_constRef<bool>("isitq")?'T':'F')<< endl;
   ofMapStream << "             isitp : " << (getKey_constRef<bool>("isitp")?'T':'F')<< endl;
   ofMapStream << "            isitap : " << (getKey_constRef<bool>("isitap")?'T':'F') << endl;
   ofMapStream << "           isitdeb : " << (getKey_constRef<bool>("isitdeb")?'T':'F') << endl;
   ofMapStream << "             isitf : " << (getKey_constRef<bool>("isitf")?'T':'F')<< endl;
   ofMapStream << "             isitr : " << (getKey_constRef<bool>("isitr")?'T':'F')<< endl;
   ofMapStream << "             isitc : " << (getKey_constRef<bool>("isitc")?'T':'F')<< endl;
   ofMapStream << "             isitx : " << (getKey_constRef<bool>("isitx")?'T':'F')<< endl;
   ofMapStream << "             isiti : " << (getKey_constRef<bool>("isiti")?'T':'F')<< endl;
   ofMapStream << "             isitt : " << (getKey_constRef<bool>("isitt")?'T':'F')<< endl;
   ofMapStream << "            isitrf : " << (getKey_constRef<bool>("isitrf")?'T':'F')<< endl;
   ofMapStream << "            isitcf : " << (getKey_constRef<bool>("isitcf")?'T':'F')<< endl;
   ofMapStream << "            isitmd : " << (getKey_constRef<bool>("isitmd")?'T':'F')<< endl;
   ofMapStream << "            isitsf : " << (getKey_constRef<bool>("isitsf")?'T':'F')<< endl;
   ofMapStream << "            isittf : " << (getKey_constRef<bool>("isittf")?'T':'F')<< endl;
   ofMapStream << "           isitpot : " << (getKey_constRef<bool>("isitpot")?'T':'F') << endl;
   ofMapStream << "              irea : " << (getKey_constRef<bool>("irea")?'T':'F') << endl;
   ofMapStream << "             iself : " << (getKey_constRef<bool>("iself")?'T':'F')<< endl;
   // set by BUFFZ function
   ofMapStream << "              bufz : " << getKey_constRef< SExtrema<integer> >("buffz").nMin.nX << " "
                                          << getKey_constRef< SExtrema<integer> >("buffz").nMin.nY << " "
                                          << getKey_constRef< SExtrema<integer> >("buffz").nMin.nZ   << " "
                                          << getKey_constRef< SExtrema<integer> >("buffz").nMax.nX   << " "
                                          << getKey_constRef< SExtrema<integer> >("buffz").nMax.nY   << " "
                                          << getKey_constRef< SExtrema<integer> >("buffz").nMax.nZ   << endl;
   ofMapStream << "             ibufz : " << (getKey_constRef<bool>("ibufz")?'T':'F') << endl;
   // set by SURFACE function
   ofMapStream << "         isurftype : " << getKey_constRef<int>("isurftype")       << endl;
   ofMapStream << "----------------------- DelPhi ---------------------"        << endl;
   ofMapStream << "            deblen : " << getKey_constRef<real>("deblen")         << endl;
   ofMapStream << "            epsout : " << getKey_constRef<real>("epsout")         << endl;
   ofMapStream << "              cran : " << getKey_constRef< SGrid<real> >("cran").nX << " "
                                          << getKey_constRef< SGrid<real> >("cran").nY << " "
                                          << getKey_constRef< SGrid<real> >("cran").nZ << endl;
   ofMapStream << "              pmid : " << getKey_constRef< SGrid<real> >("pmid").nX << " "
                                          << getKey_constRef< SGrid<real> >("pmid").nY << " "
                                          << getKey_constRef< SGrid<real> >("pmid").nZ << endl;
   ofMapStream << "            oldmid : " << getKey_constRef< SGrid<real> >("oldmid").nX << " "
                                          << getKey_constRef< SGrid<real> >("oldmid").nY << " "
                                          << getKey_constRef< SGrid<real> >("oldmid").nZ << endl;
   ofMapStream << "            rionst : " << getKey_constRef<real>("rionst")         << endl;
   ofMapStream << "            chi1-5 : " << getKey_constRef<real>("chi1") << " "
                                          << getKey_constRef<real>("chi2") << " "
                                          << getKey_constRef<real>("chi3") << " "
                                          << getKey_constRef<real>("chi4") << " "
                                          << getKey_constRef<real>("chi5") << endl;
   ofMapStream << "             lognl : " << (getKey_constRef<bool>("lognl")?'T':'F')<< endl;
   ofMapStream << "              epkt : " << getKey_constRef<real>("epkt")           << endl;
   ofMapStream << "             epsin : " << getKey_constRef<real>("epsin")          << endl;
   ofMapStream << "            ifrcrd : " << (getKey_constRef<bool>("ifrcrd")?'T':'F') << endl;
   ofMapStream << "        idirectalg : " << getKey_constRef<int>("idirectalg")      << endl;
   ofMapStream << "           numbmol : " << getKey_constRef<integer>("numbmol")     << endl;
   ofMapStream << "              rdmx : " << getKey_constRef<real>("rdmx")           << endl;
   ofMapStream << "       uniformdiel : " << (getKey_constRef<bool>("uniformdiel")?'T':'F') << endl;

   {
      const vector< SExtrema<real> >* prgfeExtrema = getKey_constPtr< vector< SExtrema<real> > >("limobject");

      ofMapStream << "         limobject : " << endl;
      if (0 != prgfeExtrema->size())
      {
         for (unsigned int i = 0; i < prgfeExtrema->size(); i++)
         {
            ofMapStream<<setw(6)<<right<<i<<" : ";

            //ofMapStream<<fixed<<setprecision(3);
            ofMapStream << setw(8) << right << prgfeExtrema->at(i).nMin.nX << "  "
                        << setw(8) << right << prgfeExtrema->at(i).nMin.nY << "  "
                        << setw(8) << right << prgfeExtrema->at(i).nMin.nZ << " || "
                        << setw(8) << right << prgfeExtrema->at(i).nMax.nX << "  "
                        << setw(8) << right << prgfeExtrema->at(i).nMax.nY << "  "
                        << setw(8) << right << prgfeExtrema->at(i).nMax.nZ << endl;
         }
      }
   }

   {
      const vector< SGrid<real> >* prgfgAtomCoordA = getKey_constPtr< vector< SGrid<real> > >("xn1");

      ofMapStream << "               xn1 : " << endl;
      if (0 != prgfgAtomCoordA->size())
      {
         for (unsigned int i = 0; i < prgfgAtomCoordA->size(); i++)
         {
            ofMapStream << setw(6) << right << i << " : " << setw(8) << right << prgfgAtomCoordA->at(i).nX << "  "
                        << setw(8) << right << prgfgAtomCoordA->at(i).nY << "  "
                        << setw(8) << right << prgfgAtomCoordA->at(i).nZ << endl;
         }
      }
   }

   {
      const vector< SGrid<real> >* prgfgAtomCoordG = getKey_constPtr< vector< SGrid<real> > >("xn2");

      ofMapStream << "               xn2 : " << endl;
      if (0 != prgfgAtomCoordG->size())
      {
         for (unsigned int i = 0; i < prgfgAtomCoordG->size(); i++)
         {
            ofMapStream << setw(6) << right << i << " : " << setw(8) << right << prgfgAtomCoordG->at(i).nX << "  "
                        << setw(8) << right << prgfgAtomCoordG->at(i).nY << "  "
                        << setw(8) << right << prgfgAtomCoordG->at(i).nZ << endl;
         }
      }
   }

   ofMapStream << "------------------ set by IO class -----------------"        << endl;
   ofMapStream << "         resnummax : " << getKey_constRef<integer>("resnummax")   << endl;
   ofMapStream << "            nmedia : " << getKey_constRef<integer>("nmedia")      << endl;

   {
      const vector<real>* prgfMediaEps = getKey_constPtr< vector<real> >("medeps");

      ofMapStream << "            medeps : " << endl;
      if (0 != prgfMediaEps->size())
      {
         for (unsigned int i = 0; i < prgfMediaEps->size(); i++)
         {
            ofMapStream << setw(6) << right << i << " : " << setw(8) << right << prgfMediaEps->at(i) << endl;
         }
      }
   }

   ofMapStream << "           nobject : " << getKey_constRef<integer>("nobject")     << endl;

   {
      const vector<string>* prgstrObject = getKey_constPtr< vector<string> >("dataobject");

      ofMapStream << "        dataobject : " << endl;
      if (0 != prgstrObject->size())
      {
         for (unsigned int i = 0; i < prgstrObject->size(); i=i+2)
         {
            ofMapStream << setw(6)  << right << i << " : "
                        << setw(15) << right << prgstrObject->at(i)   << " || "
                        << setw(15) << right << prgstrObject->at(i+1) << endl;
         }
      }
   }

   ofMapStream << "             natom : " << getKey_constRef<integer>("natom")       << endl;

   {
      const vector<CAtomPdb>* prgapAtomPdb = getKey_constPtr< vector<CAtomPdb> >("delphipdb");

      ofMapStream << "         delphipdb : " << endl;
      if (0 != prgapAtomPdb->size())
      {
         for (unsigned int i = 0; i < prgapAtomPdb->size(); i++)
         {
            ofMapStream<<setw(6)<< right << i << " : " << setw(8) << right << prgapAtomPdb->at(i).getPose().nX << "  "
                                << setw(8) << right << prgapAtomPdb->at(i).getPose().nY << "  "
                                << setw(8) << right << prgapAtomPdb->at(i).getPose().nZ <<" || "
                                << setw(8) << right << prgapAtomPdb->at(i).getRadius()  <<" || "
                                << setw(8) << right << prgapAtomPdb->at(i).getCharge()  <<" || "
                                << setw(15)<< right << prgapAtomPdb->at(i).getAtInf()   << endl;
         }
      }
   }

   {
      const vector<integer>* prgiAtomMediaNum = getKey_constPtr< vector<integer> >("iatmmed");

      ofMapStream << "           iatmmed : " << endl;
      if (0 != prgiAtomMediaNum->size())
      {
         for (unsigned int i=0; i < prgiAtomMediaNum->size(); i++)
         {
           ofMapStream << setw(6) << right << i << " : " << setw(8) << right << prgiAtomMediaNum->at(i) << endl;
         }
      }
   }

   ofMapStream << "          ionlymol : " << (getKey_constRef<bool>("ionlymol")?'T':'F') << endl;

   ofMapStream << "---------------------- Surface ---------------------"             << endl;
   ofMapStream << "             nqass : " << getKey_constRef<integer>("nqass")       << endl;
   ofMapStream << "              qnet : " << getKey_constRef<real>("qnet")           << endl;
   ofMapStream << "              qmin : " << getKey_constRef<real>("qmin")           << endl;
   ofMapStream << "             qplus : " << getKey_constRef<real>("qplus")          << endl;
   ofMapStream << "            cqplus : " << getKey_constRef< SGrid<real> >("cqplus").nX << " "
                                          << getKey_constRef< SGrid<real> >("cqplus").nY << " "
                                          << getKey_constRef< SGrid<real> >("cqplus").nZ << endl;
   ofMapStream << "             cqmin : " << getKey_constRef< SGrid<real> >("cqmin").nX  << " "
                                          << getKey_constRef< SGrid<real> >("cqmin").nY  << " "
                                          << getKey_constRef< SGrid<real> >("cqmin").nZ  << endl;
   ofMapStream << "              cmin : " << getKey_constRef< SGrid<real> >("cmin").nX   << " "
                                          << getKey_constRef< SGrid<real> >("cmin").nY   << " "
                                          << getKey_constRef< SGrid<real> >("cmin").nZ   << endl;
   ofMapStream << "              cmax : " << getKey_constRef< SGrid<real> >("cmax").nX   << " "
                                          << getKey_constRef< SGrid<real> >("cmax").nY   << " "
                                          << getKey_constRef< SGrid<real> >("cmax").nZ   << endl;
   ofMapStream << "             ibnum : " << getKey_constRef<integer>("ibnum")           << endl;

   {
      const integer iGrid = getKey_constRef<integer>("igrid");

      ofMapStream << "            iepsmp : " << endl;
      if (0 != getKey_constRef< vector< SGrid<integer> > >("iepsmp").size())
      {
         vector< SGrid<integer> >::iterator it = getKey_Ref< vector< SGrid<integer> > >("iepsmp").begin();

         for (unsigned int k = 0; k < (size_t)iGrid; k++)
         {   for (unsigned int j = 0; j < (size_t)iGrid; j++)
             {  for (unsigned int i = 0; i < (size_t)iGrid; i++)
                {
                   ofMapStream << setw(3) << right << i << " " << setw(3) << right << j << " " << setw(3) << right << k << " : "
                               << setw(6) << right << it->nX << setw(6) << right << it->nY << setw(6) << right << it->nZ << endl;
                   it++;
                }
             }
          }
       }
   }

   /*------------------------------ test of getKey_constPtr overloading --------------------------//
   {
      const integer iGrid = getKey_constRef<integer>("igrid");
      const SGrid<integer> *** prgigEpsMap = getKey_constPtr< SGrid<integer> >("iepsmp",iGrid,iGrid,iGrid);

      ofMapStream << "      iepsmp2 : " << endl;
      if (0 != iGrid)
      {
         for (unsigned int i = 0; i < (size_t)iGrid; i++)
         {   for (unsigned int j = 0; j < (size_t)iGrid; j++)
             {  for (unsigned int k = 0; k < (size_t)iGrid; k++)
                {
                   ofMapStream << setw(3) << right << i << " " << setw(3) << right << j << " " << setw(3) << right << k << " : "
                               << setw(6) << right << prgigEpsMap[i][j][k].nX
                               << setw(6) << right << prgigEpsMap[i][j][k].nY
                               << setw(6) << right << prgigEpsMap[i][j][k].nZ << endl;
                }
             }
          }
       }
   }
   //------------------------------ test of getKey_constPtr overloading --------------------------*/

   {
      const integer iGrid = getKey_constRef<integer>("igrid");

      ofMapStream << "           idebmap : " << endl;

      vector<bool>::iterator it = getKey_Ref< vector<bool> >("idebmap").begin();
      if (0 != getKey_constRef< vector<bool> >("idebmap").size())
      {
         for (unsigned int k = 0; k < (size_t)iGrid; k++)
         {
            for (unsigned int j = 0; j < (size_t)iGrid; j++)
            {
               for (unsigned int i = 0; i < (size_t)iGrid; i++)
               {
                  ofMapStream << setw(3) << right << i << "," << setw(3) << right << j << "," << setw(3) << right << k << " : "
                              << setw(8) << right << (*it?'T':'F') << endl;
                  it++;
               }
            }
         }
      }
   }

   {
      const vector< SGrid<integer> >* prgigBndyGrid = getKey_constPtr< vector< SGrid<integer> > >("ibgrd");

      ofMapStream << "             ibgrd : " << endl;
      if (0 != prgigBndyGrid->size())
      {
         for (unsigned int i=0; i < prgigBndyGrid->size(); i++)
         {
           ofMapStream << setw(6) << right << i << " : "
                       << setw(6) << right << prgigBndyGrid->at(i).nX << " "
                       << setw(6) << right << prgigBndyGrid->at(i).nY << " "
                       << setw(6) << right << prgigBndyGrid->at(i).nZ << endl;
         }
      }
   }

   ofMapStream << "             nqgrd : " << getKey_constRef<integer>("nqgrd") << endl;

   {
      const vector< SGridValue<real> >* prggvCrg2Grid = getKey_constPtr< vector< SGridValue<real> > >("chrgv2");

      ofMapStream << "            chrgv2 : " << endl;
      if (0 != prggvCrg2Grid->size())
      {
         for (unsigned int i=0; i < prggvCrg2Grid->size(); i++)
         {
           ofMapStream << setw(6) << right << i << " : "
                   << setw(8) << right << prggvCrg2Grid->at(i).nGrid.nX << " "
                   << setw(8) << right << prggvCrg2Grid->at(i).nGrid.nY << " "
                   << setw(8) << right << prggvCrg2Grid->at(i).nGrid.nZ << " "
                   << setw(8) << right << prggvCrg2Grid->at(i).nValue   << endl;
         }
      }
   }

   {
      const vector<integer>* prgiCrg2GridMap = getKey_constPtr< vector<integer> >("nqgrdtonqass");

      ofMapStream << "      nqgrdtonqass : " << endl;
      if (0 != prgiCrg2GridMap->size())
      {
         for (unsigned int i=0; i < prgiCrg2GridMap->size(); i++)
         {
           ofMapStream << setw(6) << right << i << " : " << setw(6) << right << prgiCrg2GridMap->at(i) << endl;
         }
      }
   }

   {
      const vector< SGridValue<real> >* prggvAtomCrg = getKey_constPtr< vector< SGridValue<real> > >("atmcrg");

      ofMapStream << "            atmcrg : " << endl;
      if (0 != prggvAtomCrg->size())
      {
         for (unsigned int i=0; i < prggvAtomCrg->size(); i++)
         {
           ofMapStream << setw(6) << right << i << " : "
                       << setw(8) << right << prggvAtomCrg->at(i).nGrid.nX << " "
                       << setw(8) << right << prggvAtomCrg->at(i).nGrid.nY << " "
                       << setw(8) << right << prggvAtomCrg->at(i).nGrid.nZ << " "
                       << setw(8) << right << prggvAtomCrg->at(i).nValue << endl;
         }
      }
   }

   {
      const vector< SGrid<real> >* prgfgCrgPoseA = getKey_constPtr< vector< SGrid<real> > >("chgpos");

      ofMapStream << "            chgpos : " << endl;
      if (0 != prgfgCrgPoseA->size())
      {
         for (unsigned int i = 0; i < prgfgCrgPoseA->size(); i++)
         {
            ofMapStream << setw(6) << right << i << " : "
                        << setw(8) << right << prgfgCrgPoseA->at(i).nX << "  "
                        << setw(8) << right << prgfgCrgPoseA->at(i).nY << "  "
                        << setw(8) << right << prgfgCrgPoseA->at(i).nZ << endl;
         }
      }
   }

   {
      const vector< SGrid<real> >* prgfgSurfCrgA = getKey_constPtr< vector< SGrid<real> > >("scspos");

      ofMapStream << "            scspos : " << endl;
      if (0 != prgfgSurfCrgA->size())
      {
         for (unsigned int i = 0; i < prgfgSurfCrgA->size(); i++)
         {
            ofMapStream << setw(6) << right << i <<" : "
                      << setw(8) << right << prgfgSurfCrgA->at(i).nX << "  "
                      << setw(8) << right << prgfgSurfCrgA->at(i).nY << "  "
                      << setw(8) << right << prgfgSurfCrgA->at(i).nZ << endl;
         }
      }
   }

   {
      const vector<integer>* prgiCrgAt = getKey_constPtr< vector<integer> >("crgatn");

      ofMapStream << "            crgatn : " << endl;
      if (0 != prgiCrgAt->size())
      {
         for (unsigned int i=0; i < prgiCrgAt->size(); i++)
         {
           ofMapStream << setw(6) << right << i << " : " << setw(6) << right << prgiCrgAt->at(i) << endl;
         }
      }
   }

   {
      const vector<integer>* prgiAtSurf = getKey_constPtr< vector<integer> >("atsurf");

      ofMapStream << "            atsurf : " << endl;
      if (0 != prgiAtSurf->size())
      {
         for (unsigned int i=0; i < prgiAtSurf->size(); i++)
         {
           ofMapStream << setw(6) << right << i << " : " << setw(6) << right << prgiAtSurf->at(i) << endl;
         }
      }
   }

   {
      const vector<integer>* prgiAtNdx = getKey_constPtr< vector<integer> >("atndx");

      ofMapStream << "             atndx : " << endl;
      if (0 != prgiAtNdx->size())
      {
         for (unsigned int i=0; i < prgiAtNdx->size(); i++)
         {
           ofMapStream << setw(6) << right << i << " : " << setw(6) << right << prgiAtNdx->at(i) << endl;
         }
      }
   }

   {
      const vector< SGrid<real> >* prgfgSurfCrgE = getKey_constPtr< vector< SGrid<real> > >("scsnor");

      ofMapStream << "            scsnor : " << endl;
      if (0 != prgfgSurfCrgE->size())
      {
         for (unsigned int i = 0; i < prgfgSurfCrgE->size(); i++)
         {
            ofMapStream << setw(6) << right << i <<" : "
                        << setw(8) << right << prgfgSurfCrgE->at(i).nX << "  "
                        << setw(8) << right << prgfgSurfCrgE->at(i).nY << "  "
                        << setw(8) << right << prgfgSurfCrgE->at(i).nZ << endl;
         }
      }
   }

   {
      const vector<real>* prgfAtomEps = getKey_constPtr< vector<real> >("atmeps");

      ofMapStream << "            atmeps : " << endl;
      if (0 != prgfAtomEps->size())
      {
         for (unsigned int i=0; i < prgfAtomEps->size(); i++)
         {
           ofMapStream << setw(6) << right << i << " : " << setw(8) << right << prgfAtomEps->at(i) << endl;
         }
      }
   }

   ofMapStream << "---------------------- Solver ----------------------"        << endl;
   ofMapStream << "          icount2b : " << getKey_constRef<integer>("icount2b")    << endl;
   ofMapStream << "          icount1b : " << getKey_constRef<integer>("icount1b")    << endl;

   {
      const vector<real>* prgfGridCrg = getKey_constPtr< vector<real> >("gchrg");

      ofMapStream << "             gchrg : " << endl;
      if (0 != prgfGridCrg->size())
      {
         for (unsigned int i=0; i < prgfGridCrg->size(); i++)
         {
           ofMapStream << setw(6) << right << i << " : " << setw(8) << right << prgfGridCrg->at(i) << endl;
         }
      }
   }

   {
      const vector< SGrid<integer> >* prgigGridCrgPose = getKey_constPtr< vector< SGrid<integer> > >("gchrgp");

      ofMapStream << "            gchrgp : " << endl;
      if (0 != prgigGridCrgPose->size())
      {
         for (unsigned int i = 0; i < prgigGridCrgPose->size(); i++)
         {
            ofMapStream << setw(6) << right << i << " : "
                        << setw(8) << right << prgigGridCrgPose->at(i).nX << "  "
                        << setw(8) << right << prgigGridCrgPose->at(i).nY << "  "
                        << setw(8) << right << prgigGridCrgPose->at(i).nZ << endl;
         }
      }
   }

   ofMapStream << "               ibc : " << getKey_constRef<integer>("ibc")    << endl;

   {
      const vector<SDoubleGridValue>* prgdgvCrgBndyGrid = getKey_constPtr< vector<SDoubleGridValue> >("cgbp");

      ofMapStream << "              cgbp : " << endl;
      if (0 != prgdgvCrgBndyGrid->size())
      {
         for (unsigned int i = 0; i < prgdgvCrgBndyGrid->size(); i++)
         {
            ofMapStream << setw(6) << right << i << " : "
                        << setw(8) << right << prgdgvCrgBndyGrid->at(i).fgCoord.nX << "  "
                        << setw(8) << right << prgdgvCrgBndyGrid->at(i).fgCoord.nY << "  "
                        << setw(8) << right << prgdgvCrgBndyGrid->at(i).fgCoord.nZ << "  "
                        << setw(8) << right << prgdgvCrgBndyGrid->at(i).fVal1      << "  "
                        << setw(8) << right << prgdgvCrgBndyGrid->at(i).fVal2      << endl;
         }
      }
   }

   {
      const integer iGrid = getKey_constRef<integer>("igrid");
      const vector<real>* prgfPhimap = getKey_constPtr< vector<real> >("phimap");

      ofMapStream << "            phimap : " << endl;
      if (0 != prgfPhimap->size())
      {
         for (unsigned int k = 0; k < (size_t)iGrid; k++)

         {
            for (unsigned int j = 0; j < (size_t)iGrid; j++)
            {
               for (unsigned int i = 0; i < (size_t)iGrid; i++)
               {
                  ofMapStream << setw(3) << right << i << "," << setw(3) << right << j << "," << setw(3) << right << k << " : "
                              << setw(11) << right << prgfPhimap->at(k*iGrid*iGrid+j*iGrid+i) << endl;
               }
            }
         }
      }
   }

   ofMapStream << "---------------------- Energy ----------------------"        << endl;
   {
      const vector<real>* prgfSurfCrgE = getKey_constPtr< vector<real> >("schrg");

      ofMapStream << "             schrg : " << endl;

      if(0 != prgfSurfCrgE->size())
      {
         for (unsigned int i = 0; i < prgfSurfCrgE->size(); i++)
         {
            ofMapStream << setw(6) << right << i << " : " << setw(8) << right << prgfSurfCrgE->at(i) << endl;
         }
      }
   }

//   ofMapStream << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n";
//   ofMapStream << "+                                                        + \n";
//   ofMapStream << "+                    DELPHI DATA CONTAINER               + \n";
//   ofMapStream << "+                                                        + \n";
//   ofMapStream << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n";

   ofMapStream.close();

}
