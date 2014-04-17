#ifndef CDELPHIDATA_H
#define CDELPHIDATA_H

#include <iostream>
#include <string>
#include <vector>
#include <memory> // std::shared_ptr

#include "../misc/misc_grid.h"
#include "../misc/misc_timer.h"
#include "../io/io_datatype.h"
#include "../interface/environment.h"
#include "../interface/interface_datacontainer.h"
#include "delphi_datamarshal.h"

using namespace std;


//-----------------------------------------------------------------------//

class CDelphiData:virtual public IDataContainer
{	
   private:
      shared_ptr<CDelphiDataMarshal> pddm;

      void flash() const;

      virtual void setMap();

	public:     
      /**
       * constructor I (for regular delphi runs)
       */
      CDelphiData(int argc,char* argv[],shared_ptr<CTimer> pTimer):pddm(new CDelphiDataMarshal(argc,argv,pTimer))
      {
         flash();
      
         pTimer->start(); // start to record program execution time

         pddm->read();
         
         pddm->updateParameters();
                 
         setMap();
                 
#ifdef DEBUG_DELPHI_MAP
         showMap("delphicpp_datacontainer.dat");
#endif   

         pddm.~shared_ptr(); // destroy the CDelphiDataMarshal object
      };
      
      /**
       * constructor II (for calling delphi in mcce)
       */
      CDelphiData(SMCCE * mcce_data,shared_ptr<CTimer> pTimer):pddm(new CDelphiDataMarshal(mcce_data,pTimer))
      {
         flash();

         pTimer->start(); // start to record program execution time

         pddm->updateParameters();

         setMap();

#ifdef DEBUG_DELPHI_MAP
         showMap("delphicpp_datacontainer.dat");
#endif

         pddm.~shared_ptr(); // destroy the CDelphiDataMarshal object
      };


      virtual void showMap(const string& strMapFile);

      virtual void reset(const string& strF95File);
};


#endif // CDELPHIDATA_H
