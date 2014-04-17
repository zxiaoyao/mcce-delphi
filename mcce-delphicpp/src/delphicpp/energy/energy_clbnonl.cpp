/*
 * energy_clbnonl.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: Lin Wang
 */

#include "energy.h"

void CDelphiEnergy::energy_clbnonl(real& fEnergy_Coulombic, real& fEnergy_SolvToChgIn, int& iGridOutput)
{
	real fEnergy_Temp, fEnergy_Temp1, fEnergy_Temp2, fDistance;
	int i, j, n;
	SGrid<real> SGrid_deltaXYZ;
	real c=0.0006023;
	fEnergy_Temp = 0.0;

	for(i=0;i<iCrgGridNum;i++){
		fEnergy_Temp1 = 0.0;
		fEnergy_Temp2 = 0.0;
		for(j=0;j<iCrgGridNum;j++){
			if(i!=j){
				SGrid_deltaXYZ = prgfgCrgPoseA[i]-prgfgCrgPoseA[j];
				fDistance = optDot(SGrid_deltaXYZ,SGrid_deltaXYZ);

				fEnergy_Temp1 += prggvAtomicCrg[j].nValue/sqrt(fDistance);
			}
		}

		fEnergy_Temp += prggvAtomicCrg[i].nValue * fEnergy_Temp1 / prgfAtomEps[i];

		// Calculation for the solvent contribution
	    // Array sout is declared in pointers module and allocated in nlener subroutine

		if(fIonStrength > 1.0e-6){
			for(n=0;n<iGridOutput;n++){
				SGrid_deltaXYZ =  prgfgCrgPoseA[i]-sout[n].nGrid;

				fDistance = optDot(SGrid_deltaXYZ,SGrid_deltaXYZ);

				fEnergy_Temp2 += sout[n].nValue/sqrt(fDistance);
			}

			fEnergy_SolvToChgIn = fEnergy_SolvToChgIn + fEnergy_Temp2 * prggvAtomicCrg[i].nValue;
		}
	}

	fEnergy_Temp = fEnergy_Temp / 2.0;
	fEnergy_Coulombic = fEnergy_Temp;
	fEnergy_SolvToChgIn = fEnergy_SolvToChgIn * c / (2.0 * fEpsOut);

}

