#ifndef IABSTRACTMODULE_H
#define IABSTRACTMODULE_H

#include <iostream> 
#include <memory> 

#include "environment.h"
#include "interface_datacontainer.h"

using namespace std;

class IAbstractModule
{
   protected:
      shared_ptr<IDataContainer> pdc;

   public:
      IAbstractModule(shared_ptr<IDataContainer> pdcIn) {pdc = pdcIn;};
      
      ~IAbstractModule(){};
      
      virtual void run() = 0;
      
      virtual void validateInput() = 0;
};



#endif // IABSTRACTMODULE_H
