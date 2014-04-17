/*
 * energy_clbmedia.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: Lin Wang
 */

#include "energy.h"

void CDelphiEnergy::energy_clbmedia(real& fEnergy_Coulombic)
{
	real fEnergy_Temp, fDistance;
	int i, j;
	SGrid<real> SGrid_deltaXYZ;

	fEnergy_Coulombic = 0.0;
	for(i=0;i<iCrgGridNum;i++){
		fEnergy_Temp = 0.0;
		for(j=0;j<iCrgGridNum;j++){
			if(i!=j){
				SGrid_deltaXYZ = prgfgCrgPoseA[i]-prgfgCrgPoseA[j];

				fDistance = optDot(SGrid_deltaXYZ,SGrid_deltaXYZ);

				fEnergy_Temp +=(prggvAtomicCrg[j].nValue)/sqrt(fDistance);
			}
		}

		fEnergy_Coulombic += prggvAtomicCrg[i].nValue * fEnergy_Temp / prgfAtomEps[i]; // prgfAtomEps -> atmeps
	}

	fEnergy_Coulombic = fEnergy_Coulombic / 2.0;

}
