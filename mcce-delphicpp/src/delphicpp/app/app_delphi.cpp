/**
 * [QUICK REFERENCE TO ACCESS SVN REPOSITORY ON SERVER consus.clemson.edu] \n
 * - TO SHOW LOG HISTORY FOR THIS PROJECT:
 *   	svn log svn+ssh://username\@consus.clemson.edu/home/common/delphi_distr/delphicpp
 * - TO CHECKOUT THE LATEST REVERSION: 
 *   	svn co svn+ssh://username\@consus.clemson.edu/home/common/delphi_distr/delphicpp
 * - TO REMOVE/ADD FILES FROM A CHECKED-OUT PROJECT:
 *   	svn rm  <file/directory name>
 *   	svn add <file/directory name>
 * - TO REVIEW LOCAL CHANGES:
 *   	svn status
 * - TO COMMIT CHANGES:
 *   	export SVN_EDITOR=/usr/bin/vim
 *   	svn commit
 * - TO UPDATE YOUR LOCAL FILES:
 *   	svn update
 *
 *   (See "subversion user guide" created by S. Sarkar and C. Li for other svn options)
 * 
 * [SUBMITTED REVERSIONS] \n
 * - r01   chuan   2013July01   The 1st reversion in SVN.
 * - r02   chuan   2013Nov25    1. Updated reading size and charge files in IO class. \n
 *                              2. Updated excel file. \n
 * - r03   chuan   2013Dec04    1. Completed reading/writing PDB file in IO class. \n
 *                              2. Completed assigning size and charge to atoms. \n
 * - r04   chuan   2013Dec05    fixed bugs in IO class.
 * - r05   chuan   2013Dec10    major changes in prototypes, delphi, main and misc.
 * - r06   chuan   2013Dec13    overhauled the subsystems of prototypes, delphi, misc, io. \n
 *                              1. Now the part of code before surface construction is completed. \n
 *                              2. Now the code requires GCC 4.3+ with option std=c++0x to compile due to the additional feature of
 *                              initializing values when creating large arrays. (see comments in makefile)
 * - r07   chuan   2013Dec24    Another set of major changes includes:
 *                              1. Converted map<string,void *> to map<string,boost::any> \n
 *                              2. Converted all regular and dynamically allocated multi-dimensional arrays to 1D stl::vector<T> in the map. \n
 *                              The reasons to do so are: 1) contiguous memory allocation. 2) faster 1-layer loop instead of
 *                              multi-layer loop. 3) Easier allocate/deallocate arrays \n
 *                              3. Started using smart pointers instead of raw pointers in  order to avoid possible memory leak. \n
 *                              4. Removed datadistr(:) and ndistr from the map \n
 *                              5. Now the class of DataContainer provides 4 template functions to access the map:
 *                            	   1) read-only by value:         getKey_constRef
 *                            	   2) read-only by pointer:       getKey_constPtr
 *                            	   3) writable access by value:   getKey_Val
 *                            	   4) writable access by pointer: getKey_Ptr
 *                              6. Reorganized the code structure.
 * - r08   chuan   2014Jan07    Re-config the code to have datacontainer and datamarshal loosely paired.
 * - n/a   chuan   2014Jan10    1. Added new piece of code to read ibnum, ibgrd, iepsmp and idebmap from forSolver.dat without Lin's
 *                              surface construction class. \n
 *                              2. Fixed various bugs. \n
 * - r09   chuan   2014Jan18    1st reversion to use Eclipse and Doxygen.
 * - r10   chuan   2014Jan18    cleaned two additional files
 * - r11   chuan   2014Feb17    completed solver class with other updates.
 * - r12   chuan   2014Feb26    Added new class of writing site and phimap.
 * - r13   chuan   2014Mar26    Added new derectory of examples with 3 super-large proteins.
 * - r14   LinWang 2014Apr03    Energy Class added
 * - r15   LinLi   2014Apr03    space class and examples added
 * - r16   LinLi   2014Apr03    app_delphi.cpp for space added
 * - r17   lwang3  2014Apr07    Energy class modified: 1.Renamed variables. 2.Warning message added for some testing functions.
 * - r18   lwang3  2014Apr08    Example files cleanup.
 * - r19   chuan   2014Apr08    1. new function reset is added in datacontainer class for testing purpose.
 *                              2. modified delphi95.r16 is added to svn.
 * - r20   lwang3  2014Apr08    Fix bugs in delphi_datamarshal_getFunction.cpp.
 *                              Now it can control energy output by parameter file instead of setting flags.
 * - r21   chuan   2014Apr08    updated app_delphi.cpp to include all individual classes. F95 code have been updated accordingly.
 * - r22   LinLi   2014Apr10    Space module has been tested using showmap, now the aftersurf.dat are identical in fortran and C++
 * - r23   Chuan   2014Apr14    Modified app_delphi.cpp to show map after realizing every object.
 */

#include "../delphi/delphi_data.h"
#include "../space/space.h"
#include "../solver/solver_fastSOR.h"
#include "../energy/energy.h"
#include "../site/site.h"

int main(int argc, char *argv[])
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
      //                  read the parameter, size, charge, PDB files                   //
      //                                                                                //
      //********************************************************************************//

      //---------- a shared_ptr to an object of IDataContainer
      shared_ptr<IDataContainer> pDataContainer( new CDelphiData(argc,argv,pTimer) );

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

      /*****************************************************************************
            !2011-05-10 Parameters transferred via modules qlog and pointers
            call epsmak
            !++++I have postponed crgarr to epsmak

            !make some charge arrays for boundary conditions etc.
            if (isolv) then
               !increased the starting dimension of crgatn and..+++++
               extracrg=0
               if (ndistr.gt.0) extracrg=igrid**3

               !2011-05-30 Allocation of the arrays below is moved to the
               !           body of crgarr subroutine, arrays are accessible
               !           via pointers module. Sizes of arrays are
               !           determined before allocation inside the crgarr
               !           subroutine
               !i_crgatn=memalloc(i_crgatn,4,natom+extracrg)
               !i_chrgv2=memalloc(i_chrgv2,realsiz,4*(natom+extracrg))
               !i_nqgrdtonqass=memalloc(i_nqgrdtonqass,4,natom+extracrg)
               !i_atmeps=memalloc(i_atmeps,realsiz,natom+extracrg)
               !i_chgpos=memalloc(i_chgpos,realsiz,3*ncrgmx)

               !2011-05-30 Parameters transfered via qlog and pointers modules
               call crgarr

               if (logs.or.lognl) then
                  ico=0

                  do ic=1,nqass
                     if ((chgpos(ic).vorlt.xl).or.(chgpos(ic).vorgt.xr)) then
                        if (crgatn(ic).lt.0) then
                           write (6,'(''!WARNING: distribution'',I4,&
                                 &'' outside the box'')') (-crgatn(ic))
                        else
                           if (crgatn(ic).gt.natom) then
                              write(6,'(''WARNING:crg'',I4,'',object'',I4,&
                                   &'' outside the box'',3f8.3)')&
                                   &ic,(crgatn(ic)-natom),chgpos(ic)
                           else
                              write(6, '(''!!! WARNING : charge '',&
                                   &a15,'' outside the box'')') &
                                   &  delphipdb(crgatn(ic))%atinf
                           end if
                        end if

                        ico=1
                     end if
                  end do

                  if (ico.gt.0.and.ibctyp.ne.3) then
                     write(6,*)'CHARGES OUTSIDE THE BOX AND &
                               &NOT DOING FOCUSSING, THEREFORE STOP'
                     stop
                  end if
               end if
            end if
      ******************************************************************************/

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

      /*
      pDataContainer->getKey_Ref<bool>("inrgwrt") = false;
      pDataContainer->getKey_Ref<bool>("loga")    = false;
      pDataContainer->getKey_Ref<bool>("logg")    = true;
      pDataContainer->getKey_Ref<bool>("logs")    = true;
      pDataContainer->getKey_Ref<bool>("logas")   = false;
      pDataContainer->getKey_Ref<bool>("logc")    = true;
      pDataContainer->getKey_Ref<bool>("logions") = false;
      pDataContainer->getKey_Ref<bool>("lognl")   = false;
      */
      pDataContainer->getKey_Ref<bool>("irea")    = false;
      pDataContainer->getKey_Ref<bool>("isch")    = false;
      pDataContainer->getKey_Ref<bool>("isen")    = false;
      pDataContainer->getKey_Ref<bool>("isitpot") = false;
      pDataContainer->getKey_Ref<bool>("ibufz")   = false;

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

      return 0;        
   }

   //cout << "\033[1;31mbold red text\033[0m\n";

   cout << "\n\n .........  PROGRAM EXITS SUCCESSFULLY : WITH TOTAL " << CWarning::iWarningNum << " WARNING(S) ........\n\n";
 
   cout.unsetf(ios_base::floatfield); // return to cout default notation 

   return 0;

}




