/**
 * @file app_mcce.cpp
 * @brief Main function to generate the executable mcce_delphicpp
 *
 * @author Chuan Li, chuanli@clemson.edu
 *
 * An interface allowing data to be transferred between the program mcce and delphicpp without intensive IO operations.
 *
 * @note a good reference for programs which wish to incorporate delphicpp
 */

//#include <fstream>

#include "../delphi/delphi_data.h"
#include "../space/space.h"
#include "../solver/solver_fastSOR.h"
#include "../energy/energy.h"
#include "../site/site.h"

#include <sstream>

/**
 * a class to redirect cout to a file instead of screen
 */
class StreamRedirector
{
    public:
    explicit StreamRedirector(std::ios& stream, std::streambuf* newBuf) : savedBuf_(stream.rdbuf()), stream_(stream)
    {
        stream_.rdbuf(newBuf);
    }

    ~StreamRedirector()
    {
        stream_.rdbuf(savedBuf_);
    }

    private:
    std::streambuf* savedBuf_;
    std::ios& stream_;
};


/**
 * single delphi run, the same as app_delphi.cpp
 */
bool runDelphi(SMCCE * mcce_data)
{
   /*
    * bool values are inserted/extracted by their textual representation: either true or false, instead of integral values.
    * This flag can be unset with the noboolalpha manipulator.
    */
   cout << boolalpha;

   cerr << boolalpha;

#ifdef DEVELOPER
   cout << fixed << setprecision(7); //cout.precision(15)
#else
   cout << fixed << setprecision(3); //cout.precision(7)
#endif

   shared_ptr<CTimer> pTimer(new CTimer); // record execution time

   //---------- a shared_ptr to an object of CDelphiData
   shared_ptr<IDataContainer> pDataContainer( new CDelphiData(mcce_data,pTimer) );

   pDataContainer->showMap("test_delphicpp_atbeginning.dat");

   try
   {
      //********************************************************************************//
      //                                                                                //
      //    realize an object of CDelphiSpace class to construct molecular surfaces     //
      //                                                                                //
      //********************************************************************************//

      unique_ptr<IAbstractModule> pSpace( new CDelphiSpace(pDataContainer,pTimer) );

      pSpace->run();

      pSpace.reset(); // !!! need to be changed to pSpace.reset();

      //---------- print out results after constructing molecular surfaces
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

         //********************************************************************************//
         //                                                                                //
         //   realize an object of CDelphiFastSOR class to calculate potentials on grids   //
         //                                                                                //
         //********************************************************************************//

         unique_ptr<CDelphiFastSOR> pSolver( new CDelphiFastSOR(pDataContainer,pTimer) );

         if (3 == mcce_data->bndcon) pSolver->getMCCE(mcce_data);

         pSolver->run();

         pSolver.reset();

         //********************************************************************************//
         //                                                                                //
         //          realize an object of CDelphiEnergy class to calculate energys         //
         //                                                                                //
         //********************************************************************************//

         unique_ptr<IAbstractModule> pEnergy( new CDelphiEnergy(pDataContainer,pTimer) );

         pEnergy->run();

         pEnergy.reset();

         //********************************************************************************//
         //                                                                                //
         //               realize an object of CSite class to write site info              //
         //                                                                                //
         //********************************************************************************//

         unique_ptr<CSite> pSite( new CSite(pDataContainer,pTimer) );

         if (pDataContainer->getKey_constRef<bool>("isite"))
         {
            int iisitsf = 0;
            if (pDataContainer->getKey_Ref<bool>("isitsf")) iisitsf = 1;
            pSite->writeSite(iisitsf);
         }

         if (pDataContainer->getKey_constRef<bool>("phiwrt")) pSite->writePhi();

         /*
          * equivalent to out(frc,file="filename") in the parameter file
          */
         if (0 == pSite->mcce_phiv.size())
         {
            pSite.reset();
            pTimer->exit(); pTimer.reset();
            return false;
         }

         mcce_data->phiv = pSite->mcce_phiv;

         pSite.reset();

         /*
          * equivalent to out(phi,file="filename") in the parameter file
          */
         mcce_data->phimap  = pDataContainer->getKey_Val< vector<real> >("phimap");
         mcce_data->scale1  = pDataContainer->getKey_Val<real>("scale");
         mcce_data->oldmid1 = pDataContainer->getKey_Val< SGrid<real> >("oldmid");
         mcce_data->igrid1  = pDataContainer->getKey_Val<integer>("igrid");

         /*
          * equivalent to energy(s) in the parameter file
          */
         mcce_data->ergs = pDataContainer->getKey_Val<real>("ergs");
      }

      pDataContainer.reset();

      pTimer->exit(); pTimer.reset();
   }
   catch (CException&)
   {
      cerr << "\n\n ......... PROGRAM ABORTS WITH AN EXCEPTION AND " << CWarning::iWarningNum << " WARNING(S) ........\n\n";
      return false;
   }

   cout << "\n\n .........  PROGRAM EXITS SUCCESSFULLY : WITH TOTAL " << CWarning::iWarningNum << " WARNING(S) ........\n\n";
   cout.unsetf(ios_base::floatfield); // return to cout default notation
   return true;
}

/**
 * interface function to pass the calculated energies, values etc., from delphicpp to mcce
 *
 * @param[in,out]  mcce_data the struct containing the values required to run delphicpp and to be returned back to mcce
 * @return true if successfully calling delphicpp
 */
bool conf_energies_delphi(SMCCE * mcce_data)
{
   int notpassed = 1;
   bool bDelPhiReturn = false;
   char FileName[80];

   while(notpassed)
   {
      if (2 > mcce_data->n_retry)
      {
         /*
          * save log and errors in different files
          *
         sprintf(FileName,"%s%02d.log","delphi",1);
         ofstream logFile(FileName);
         StreamRedirector redirect_cout(cout,logFile.rdbuf());

         sprintf(FileName,"%s%02d.err","delphi",1);
         ofstream errFile(FileName);
         StreamRedirector redirect_cerr(cerr,errFile.rdbuf());
         */

         /*
          * save log and errors in the same file
          */
         sprintf(FileName,"%s%02d.log","delphi",1);
         ofstream logFile(FileName);
         StreamRedirector redirect_cout(cout,logFile.rdbuf());
         StreamRedirector redirect_cerr(cerr,logFile.rdbuf());

         bDelPhiReturn = runDelphi(mcce_data);
      }
      else if (2 <= mcce_data->n_retry && 100 > mcce_data->n_retry)
      {
         printf("   Trying changing scale on trial %d\n",mcce_data->n_retry);
         bDelPhiReturn = runDelphi(mcce_data);
      }
      else
      {
         printf("   FATAL: too many failed delphi runs (%d), quitting...\n",mcce_data->n_retry);
         return false;
      }

      if (false == bDelPhiReturn)
      {
         printf("\n   WARNING: Delphi failed at focusing depth %d of %s, retry\n", 1, mcce_data->uniqID.c_str());
         mcce_data->n_retry++;
         mcce_data->del_err = 1;
         continue;
      }

      /*
       * prepare for focusing runs
       */
      if (1 < mcce_data->del_runs) mcce_data->bndcon = 3;

      for (int i = 1; i < mcce_data->del_runs; i++)
      {
         /*
          * update mcce_data to prepare for focusing runs
          */
         mcce_data->del_runs -= i;

         if (100 > mcce_data->n_retry)
         {
            /*
             * save log and errors in different files
             *
            sprintf(FileName,"%s%02d.log","delphi",i+1);
            ofstream logFile(FileName);
            StreamRedirector redirect_cout(cout,logFile.rdbuf());

            sprintf(FileName,"%s%02d.err","delphi",i+1);
            ofstream errFile(FileName);
            StreamRedirector redirect_cerr(cerr,errFile.rdbuf());
            */

            /*
             * save log and errors in the same file
             */
            sprintf(FileName,"%s%02d.log","delphi",i+1);
            ofstream logFile(FileName);
            StreamRedirector redirect_cout(cout,logFile.rdbuf());
            StreamRedirector redirect_cerr(cerr,logFile.rdbuf());

            bDelPhiReturn = runDelphi(mcce_data);
         }
         else
         {
            printf("   FATAL: too many failed delphi runs (%d), quitting...\n",mcce_data->n_retry);
            return false;
         }

         if (false == bDelPhiReturn)
         {
            printf("\n   WARNING: Delphi failed at focusing depth %d of %s, retry\n",i+1,mcce_data->uniqID.c_str());
            mcce_data->n_retry++;
            mcce_data->del_err = 1;
            break;
         }

         mcce_data->del_err = 0;
      }

      if (mcce_data->del_err) notpassed = 1;
      else notpassed = 0; /* so far so good */
   }

   return true;
}


bool conf_rxn_delphi(SMCCE * mcce_data,float rxn[])
{
   bool bDelPhiReturn = false;
   char FileName[80];

   /*
    * save log and errors in the same file
    */
   sprintf(FileName,"%s%02d.log","rxn",1);
   ofstream logFile(FileName);
   StreamRedirector redirect_cout(cout,logFile.rdbuf());
   StreamRedirector redirect_cerr(cerr,logFile.rdbuf());

   bDelPhiReturn = runDelphi(mcce_data);

   if (false == bDelPhiReturn)
   {
      printf("\n   WARNING: Delphi failed at focusing depth %d of %s, retry\n", 1, mcce_data->uniqID.c_str());
      return false;
   }

   rxn[0] = mcce_data->ergs;

   /*
    * prepare for focusing runs
    */
   mcce_data->bndcon = 3;

   for (int i = 1; i < mcce_data->del_runs; i++)
   {
      /*
       * update mcce_data to prepare for focusing runs
       */
      mcce_data->del_runs -= i;

      /*
       * save log and errors in the same file
       */
      sprintf(FileName,"%s%02d.log","rxn",i+1);
      ofstream logFile(FileName);
      StreamRedirector redirect_cout(cout,logFile.rdbuf());
      StreamRedirector redirect_cerr(cerr,logFile.rdbuf());

      bDelPhiReturn = runDelphi(mcce_data);

      if (false == bDelPhiReturn)
      {
         printf("\n   WARNING: Delphi failed at focusing depth %d of %s, retry\n", 1, mcce_data->uniqID.c_str());
         return false;
      }

      rxn[i] = mcce_data->ergs;
   }


   return true;
}

