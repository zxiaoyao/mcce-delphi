/*
 * energy_clb.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: Lin Wang
 */

#include "energy.h"


void CDelphiEnergy::energy_clb(real& fEnergy_Coulombic)
{

    real fEnergy_Temp = 0.0;
    real fDistance = 0.0;
	int i, j;
	SGrid<real> SGrid_deltaXYZ;

	fEnergy_Coulombic = 0.0;  // coulombic energy
	for(i=0;i<iCrgGridNum-1;i++){		// iCrgGridNum -> nqass, number of assigned charges
		fEnergy_Temp = 0.0;

		for(j=i+1;j<iCrgGridNum;j++){
			// prgfgCrgPoseA -> chgpos	charge position in angstroms

			SGrid_deltaXYZ = prgfgCrgPoseA[i]-prgfgCrgPoseA[j];

			fDistance = optDot(SGrid_deltaXYZ,SGrid_deltaXYZ);

			fEnergy_Temp += (prggvAtomicCrg[j].nValue)/sqrt(fDistance);  // prggvAtomicCrg -> atmcrg
		}

		fEnergy_Coulombic += (prggvAtomicCrg[i].nValue) * fEnergy_Temp;
	}

}
