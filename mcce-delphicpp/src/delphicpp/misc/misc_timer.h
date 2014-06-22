#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <time.h>  /* or include ctime */

class CTimer
{
   private:
      //for print out current date and time
      time_t tStart, tNow;
      tm * tmStartDateTime, * tmNowDateTime;
      //for precise calculating elapsed time
      clock_t clockStart, clockNow, clockElapse; 
      
      void formattedOutElapse(long int &) const;

   public:
      CTimer()
      { 
#ifdef DEBUG_OBJECT
         cout << endl;
         cout << "****************************************************************\n";
         cout << "*                   CTimer is constructed                      *\n";
         cout << "****************************************************************\n";
#endif

         tStart = time(0); tmStartDateTime = localtime(&tStart); 
         clockStart = clock();
      };
      
      ~CTimer()
      {
#ifdef DEBUG_OBJECT
         cout << endl;
         cout << "****************************************************************\n";
         cout << "*                    CTimer is destroyed                       *\n";
         cout << "****************************************************************\n";
#endif
      };
      
      void start();
           
      void exit();
      
      void showTime();
      
      void showElapse(); 
};


#endif // TIMER_H
