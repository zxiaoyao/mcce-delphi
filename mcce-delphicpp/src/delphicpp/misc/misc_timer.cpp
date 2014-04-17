#include "misc_timer.h"

using namespace std;


void CTimer :: formattedOutElapse(long int & tSec) const
{
   int tHour, tMin;

   if (tSec < 60) // less than 1 minute
   {
      cout << fixed << (float)clockElapse/CLOCKS_PER_SEC << "   sec "<< endl;
   }
   else
   {
      tHour = tSec/3600; tSec = tSec - tHour*3600; 
      tMin  = tSec/60;   tSec = tSec - tMin*60;
   
      cout << tHour << ":" << tMin << ":" << tSec << endl;
   }

}


void CTimer :: start()
{   
   clockNow = clockStart;
   
   tNow = tStart; tmNowDateTime = tmStartDateTime;  
   cout << "\nProgram started on ";
   this->showTime(); 
}


void CTimer :: exit()
{    
   long int tSec;

   clockElapse = clock() - clockStart;
   tSec = clockElapse/CLOCKS_PER_SEC;
 
   tNow = time(0); tmNowDateTime = localtime(&tNow);  

   cout << endl << "   total cpu time was  ";
   this->formattedOutElapse(tSec); 

   cout << endl;

   cout << "Delphi exited on ";
   this->showTime();  

}


void CTimer :: showTime()
{
   tNow = time(0); tmNowDateTime = localtime(&tNow); 

   cout << 1900 + tmNowDateTime->tm_year << "-" << 1 + tmNowDateTime->tm_mon << "-" << tmNowDateTime->tm_mday << " at "
		<< tmNowDateTime->tm_hour << ":" << tmNowDateTime->tm_min << ":" << tmNowDateTime->tm_sec << endl;
}


void CTimer :: showElapse()
{   
   long int tSec;
      
   clock_t clockPast = clockNow;
   clockNow = clock(); clockElapse = clockNow - clockPast;

   tSec = clockElapse/CLOCKS_PER_SEC;
   
   this->formattedOutElapse(tSec);

}

