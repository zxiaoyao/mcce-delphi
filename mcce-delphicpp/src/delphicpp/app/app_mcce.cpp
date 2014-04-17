/*
 * app_mcce.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: chuan
 */

#include "../delphi/delphi_data.h"
#include "../space/space.h"
#include "../solver/solver_fastSOR.h"
#include "../energy/energy.h"
#include "../site/site.h"

int mcce_delphi(SMCCE * mcce_data)
{
   /*
    * bool values are inserted/extracted by their textual representation: either true or false, instead of integral values.
    * This flag can be unset with the noboolalpha manipulator.
    */
   cout << boolalpha;

#ifdef DEVELOPER
   cout << fixed << setprecision(7); //cout.precision(15)
#else
   cout << fixed << setprecision(3); //cout.precision(7)
#endif

   try
   {
      shared_ptr<CTimer> pTimer( new CTimer); // record execution time

      //********************************************************************************//
      //                                                                                //
      //                      get inputs from the struct mcce_data                      //
      //                                                                                //
      //********************************************************************************//

      //---------- a shared_ptr to an object of IDataContainer
      shared_ptr<IDataContainer> pDataContainer( new CDelphiData(mcce_data,pTimer) );

      //********************************************************************************//
      //                                                                                //
      //    realize an object of CDelphiSpace class to construct molecular surfaces     //
      //                                                                                //
      //********************************************************************************//

//#ifdef DEBUG_DELPHI_SPACE
      cerr << "\n\033[1;31m" << "---[DEBUG_DELPHI_SPACE] data container is written into file test_delphicpp_atbeginning.dat---\n\n"
           << "\033[0m";

      pDataContainer->showMap("test_delphicpp_atbeginning.dat");
//#endif

      unique_ptr<IAbstractModule> pSpace( new CDelphiSpace(pDataContainer,pTimer) );

      pSpace->run();

      pSpace.release();

//#ifdef DEBUG_DELPHI_SPACE
      cerr << "\n\033[1;31m" << "---[DEBUG_DELPHI_SPACE] data container is written into file test_delphicpp_aftersurf.dat---\n\n"
           << "\033[0m";

      pDataContainer->showMap("test_delphicpp_aftersurf.dat");
//#endif

      cout << endl;

      cout << " number of atom coordinates read  :" << right << setw(10) << pDataContainer->getKey_constRef<integer>("natom") << endl;

      if (pDataContainer->getKey_constRef<bool>("isolv"))
      {
         cout << " total number of assigned charges :" << right << setw(10) << pDataContainer->getKey_constRef<integer>("nqass") << endl;
         cout << " net assigned charge              :" << right << setw(10) << pDataContainer->getKey_constRef<real>("qnet") << endl;
         cout << " assigned positive charge         :" << right << setw(10) << pDataContainer->getKey_constRef<real>("qplus") << endl;
         cout << " centred at (gu)                  :" << right << setw(10) << pDataContainer->getKey_constRef< SGrid<real> >("cqplus").nX
                                                       << right << setw(10) << pDataContainer->getKey_constRef< SGrid<real> >("cqplus").nY
                                                       << right << setw(10) << pDataContainer->getKey_constRef< SGrid<real> >("cqplus").nZ << endl;
         cout << " assigned negative charge         :" << right << setw(10) << pDataContainer->getKey_constRef<real>("qmin") << endl;
         cout << " centred at (gu)                  :" << right << setw(10) << pDataContainer->getKey_constRef< SGrid<real> >("cqmin").nX
                                                       << right << setw(10) << pDataContainer->getKey_constRef< SGrid<real> >("cqmin").nY
                                                       << right << setw(10) << pDataContainer->getKey_constRef< SGrid<real> >("cqmin").nZ << endl;
         cout << "\nnumber of dielectric boundary points" << right << setw(10) << pDataContainer->getKey_constRef<integer>("ibnum") << endl;

         if (pDataContainer->getKey_constRef<bool>("iexun") && 0 == pDataContainer->getKey_constRef<integer>("ibnum"))
            throw CNoBndyAndDielec(pTimer);
      } // ---------- end of if (pDataContainer->getKey_constRef<bool>("isolv"))

      //++++++++++ above is to be moved into biosystem.run() ++++++++++//

      //********************************************************************************//
      //                                                                                //
      //   realize an object of CDelphiFastSOR class to calculate potentials on grids   //
      //                                                                                //
      //********************************************************************************//

      if (pDataContainer->getKey_constRef<bool>("isolv"))
      {
#ifdef DEBUG_DELPHI_SOLVER
         cerr << "\n\033[1;31m" << "---[DEBUG_DELPHI_SOLVER] data container is read from file test_fromsurf.dat---\n\n" << "\033[0m";

         pDataContainer->reset("test_fromsurf.dat");

         cerr << "\n\033[1;31m" << "---[DEBUG_DELPHI_SOLVER] data container is written into file test_delphicpp_beforeitr.dat---\n\n"
              << "\033[0m";

         pDataContainer->showMap("test_delphicpp_beforeitr.dat");

#endif // DEBUG_DELPHI_SOLVER

         unique_ptr<IAbstractModule> pSolver( new CDelphiFastSOR(pDataContainer,pTimer) );

         pSolver->run();

         pSolver.release();

//#ifdef DEBUG_DELPHI_SOLVER
         cerr << "\n\033[1;31m" << "---[DEBUG_DELPHI_SOLVER] data container is written into file test_delphicpp_afteritr.dat---\n\n"
                    << "\033[0m";

         pDataContainer->showMap("test_delphicpp_afteritr.dat");
//#endif // DEBUG_DELPHI_SOLVER
      }

      //********************************************************************************//
      //                                                                                //
      //          realize an object of CDelphiEnergy class to calculate energys         //
      //                                                                                //
      //********************************************************************************//

#ifdef DEBUG_DELPHI_ENERGY
      cerr << "\n\033[1;31m" << "---[DEBUG_DELPHI_ENERGY] data container is read from file test_fromsurf.dat "
           << "and test_fromsolver.dat---\n\n" << "\033[0m";

      pDataContainer->reset("test_fromsurf.dat");

      pDataContainer->reset("test_fromsolver.dat");

      cerr << "\n\033[1;31m" << "---[DEBUG_DELPHI_SOLVER] data container is written into file test_delphicpp_beforeenergy.dat---\n\n"
           << "\033[0m";

      pDataContainer->showMap("test_delphicpp_beforeenergy.dat");

#endif // DEBUG_DELPHI_ENERGY

      unique_ptr<IAbstractModule> pEnergy( new CDelphiEnergy(pDataContainer,pTimer) );

      pEnergy->run();

      pEnergy.release();

//#ifdef DEBUG_DELPHI_ENERGY
      cerr << "\n\033[1;31m" << "---[DEBUG_DELPHI_ENERGY] data container is written into file test_delphicpp_aftereng.dat---\n\n"
           << "\033[0m";

      pDataContainer->showMap("test_delphicpp_aftereng.dat");
//#endif // DEBUG_DELPHI_ENERGY

      //********************************************************************************//
      //                                                                                //
      //               realize an object of CSite class to write site info              //
      //                                                                                //
      //********************************************************************************//

#ifdef DEBUG_DELPHI_SITE
      cerr << "\n\033[1;31m" << "---[DEBUG_DELPHI_SITE] data container is read from file test_fromsurf.dat, "
           << "test_fromsolver.dat and test_fromenergy.dat---\n\n" << "\033[0m";

      pDataContainer->reset("test_fromsurf.dat");
      pDataContainer->reset("test_fromsolver.dat");
      pDataContainer->reset("test_fromenergy.dat");

      cerr << "\n\033[1;31m" << "---[DEBUG_DELPHI_SOLVER] data container is written into file test_delphicpp_beforesite.dat---\n\n"
           << "\033[0m";

      pDataContainer->showMap("test_delphicpp_beforesite.dat");
#endif // DEBUG_DELPHI_SITE

      unique_ptr<CSite> pSite( new CSite(pDataContainer,pTimer) );

      //pDataContainer->getKey_Ref<bool>("isite") = true;

      if (pDataContainer->getKey_constRef<bool>("isite"))
      {
         int iisitsf = 0;
         if (pDataContainer->getKey_Ref<bool>("isitsf")) iisitsf = 1;
         pSite->writeSite(iisitsf);
      }

      if (pDataContainer->getKey_constRef<bool>("phiwrt")) pSite->writePhi();

      pSite.release();

//#ifdef DEBUG_DELPHI_SITE
      cerr << "\n\033[1;31m" << "---[DEBUG_DELPHI_SITE] data container is written into file test_delphicpp_atend.dat---\n\n"
           << "\033[0m";

      pDataContainer->showMap("test_delphicpp_atend.dat");
//#endif // DEBUG_DELPHI_SITE

      //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

      pTimer->exit();

      //---------- shared_ptr will be released automatically but unique_ptr must call unique_ptr.release() before exiting this scope

   } // ---------- end of try block
   catch (CException)
   {
      cerr << "\n\n ......... PROGRAM ABORTS WITH AN EXCEPTION AND " << CWarning::iWarningNum << " WARNING(S) ........\n\n";

      return 1;
   }

   cout << "\n\n .........  PROGRAM EXITS SUCCESSFULLY : WITH TOTAL " << CWarning::iWarningNum << " WARNING(S) ........\n\n";

   cout.unsetf(ios_base::floatfield); // return to cout default notation

   return 0;

}

