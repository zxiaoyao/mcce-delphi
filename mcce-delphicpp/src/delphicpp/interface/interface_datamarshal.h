#ifndef IDATAMARSHAL_H
#define IDATAMARSHAL_H

#include <iostream>
#include <fstream>
#include <string> // std::string

#include "environment.h"
#include "interface_exceptions.h"

/**
 * This class is pure abstract. NO objects can be created directly!
 */

class IDataMarshal
{
   protected:     
      /**
       * Function to read biomodel and solver names
       * @param strLineNoSpace line of the parameter file with no spaces or comments
       * @return success/false
       */
      bool getBiomodel(const string &strLineNoSpace);
      
      /**
       * Function to determine the presence of a qinclude command and read it
       * @param strLineNoSpace line of the parameter file with no spaces or comments
       * @return success/false
       */
      bool getQinclude(const string &strLineNoSpace);

      /**
       * Function that reads a line, and determines whether the line is a statement or a function.
       * @param strLineNoSpace line of the parameter file without spaces and comments, and then determines if the function
       * is a statement by the presence of an equal sign which is NOT inside brackets.
       * @return success/false
       */
      bool getParameter(const string &strLineNoSpace); 
      
      /**
       * Function to obtain the value(s) of a statement
       * @param strLineNoSpace line of the parameter file with no spaces or comments
       * @return success/false
       */
      virtual bool getStatement(string strLineNoSpace) = 0;
      
      /**
       * Function to obtain the value(s) from a function
       * @param strLineNoSpace line of the parameter file with no spaces or comments
       * @return success/false
       */
      virtual bool getFunction(string strLineNoSpace) = 0;
            
   public:        
      string strParamFile; ///< read-in parameter file (default: fort.10)
      string strBioModel;  ///< Bio-model to solve (default: PBE)
      string strNumSolver; ///< numerical solver (default: DelPhi)

      /**
       * constructor I (for regular delphi runs)
       */
      IDataMarshal()
      {
         strParamFile = "fort.10";
         strBioModel  = "PBE";
         strNumSolver = "DELPHI"; // default
      };

      /**
       * constructor II (for mcce runs)
       */
      IDataMarshal(int argc, char *argv[])
      {
         strParamFile = "fort.10";
         strBioModel  = "PBE";
         strNumSolver = "DELPHI"; // default
         
         if (1 < argc) strParamFile = argv[1]; // input parameter file name 
      };

      /**
       * destructor
       */
      ~IDataMarshal(){};
     
      /**
       * Read each line of the file with name strParamFile and executes the parsing.
       * This function reads each line, removing any comments and spaces.
       * @return n/a
       */
      void read();

      virtual void updateParameters() = 0;
};

#endif // IDATAMARSHAL_H
