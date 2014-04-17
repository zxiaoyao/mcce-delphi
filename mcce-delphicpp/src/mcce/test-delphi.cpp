/*
 * test-delphi.cpp
 *
 *  Created on: Apr 17, 2014
 *      Author: xzhu
 */
#include "../delphicpp/delphi/delphi_constants.h"
#include <iostream>
/*
 *
 * typedef struct {
   real gsize;
   real scale;
   real indi;
   real exdi;
   real ionrad;
   real prbrad;
   real salt;
   int  bndcon;
   real center[3];
} SMCCE;
 *
 */

int mcce_delphi(SMCCE *sm);

int test() {
	SMCCE sm;
	mcce_delphi(&sm);
	std::cout << "from test, " << sm.bndcon << std::endl;

	return 0;
}



