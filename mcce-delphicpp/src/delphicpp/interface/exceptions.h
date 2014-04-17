#ifndef CEXCEPTIONS_H
#define CEXCEPTIONS_H

#include <iostream>

using namespace std;

class CException // Program exits when exception occurs
{
   public:
      CException()
      {
         //cout << "\n[[EXCEPTION]] ";
         cerr << "\033[1;31m" << "[EXCEPTION]";
      }

      ~CException()
      {
         cerr << "\033[0m";
      }
};


class CWarning // Program continues its run with warnings
{
   private:

   public:
      static int iWarningNum;
      
      CWarning()
      {
         iWarningNum++;     
      
         //cout << "\n@@WARNING_" << iWarningNum << "@@ ";
         cerr << "   " << "\033[1;34m" << "[WARNING #" << iWarningNum << "] ";
      }

      ~CWarning()
      {
         cerr << "\033[0m";
      }
};

#endif // CEXCEPTIONS_H
