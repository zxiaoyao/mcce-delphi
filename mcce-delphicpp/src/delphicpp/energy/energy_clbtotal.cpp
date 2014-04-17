/*
 * energy_clbtotal.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: Lin Wang
 */

#include "energy.h"

void CDelphiEnergy::energy_clbtotal(real& fEnergy_SolvToChgIn, real& fEnergy_Coulombic)
{
	real fCutedges_i, fCutedges_j, fCutedges_k;

	real fEnergy_Temp1, fEnergy_Temp2;
	real fDistance, gX, gY, gZ;
	real goff, carica, fPhi, fTemp, c;
	int i, j, k, n, iw, iGridOutput;
	SGrid<real> SGrid_deltaXYZ;
	SGridValue<real> fGridValue_Temp;
	vector < SGridValue<real> > sout2;


	fEnergy_Coulombic = 0.0;
	goff = (iGrid + 1.0) / 2.0;
	gX = (-goff / fScale) + fgBoxCenter.nX;
	gY = (-goff / fScale) + fgBoxCenter.nY;
	gZ = (-goff / fScale) + fgBoxCenter.nZ;


	c = fScale*fScale*fScale;

	fTemp = -2.0 * fIonStrength / c;

	for(k=0;k<iGrid;k++){
		fCutedges_k = 1.0;
		if(k==0 || k==iGrid-1){
			fCutedges_k = 0.5;
		}
		for(j=0;j<iGrid;j++){
			fCutedges_j = fCutedges_k;
			if(j==0 || j==iGrid-1){
				fCutedges_j = fCutedges_k * 0.5;
			}
			for(i=0;i<iGrid;i++){
				fCutedges_i = fCutedges_j;
				if(i==0 || i==iGrid-1){
					fCutedges_i = fCutedges_j * 0.5;
				}

				iw = k*iGrid*iGrid+j*iGrid+i;
				if(prgbDielecMap[iw]){
					fPhi = prgfPhimap[iw];
					carica = fPhi * fTemp;

					fGridValue_Temp.nGrid.nX = i/fScale + gX + 1;
					fGridValue_Temp.nGrid.nY = j/fScale + gY + 1;
					fGridValue_Temp.nGrid.nZ = k/fScale + gZ + 1;
					fGridValue_Temp.nValue = carica * fCutedges_i;

					sout2.push_back(fGridValue_Temp);

				}
			}
		}
	}

	iGridOutput = sout2.size();

	cout << " number of g.p. in solution contributing to the energy :  " << iGridOutput << endl;

	for(i=0;i<iCrgGridNum;i++){
		fEnergy_Temp1=0.0; fEnergy_Temp2=0.0;
		for(j=0;j<iCrgGridNum;j++){
			if(i!=j){
				SGrid_deltaXYZ = prgfgCrgPoseA[i]-prgfgCrgPoseA[j];

				fDistance = optDot(SGrid_deltaXYZ,SGrid_deltaXYZ);

				fEnergy_Temp1 += prggvAtomicCrg[j].nValue/sqrt(fDistance);
			}
		}

		fEnergy_Coulombic += prggvAtomicCrg[i].nValue * fEnergy_Temp1 / prgfAtomEps[i];

		// calculation for the solvent contribution.

		for(n=0;n<iGridOutput;n++){

			SGrid_deltaXYZ = prgfgCrgPoseA[i] - sout2[n].nGrid;

			fDistance = optDot(SGrid_deltaXYZ,SGrid_deltaXYZ);

			fEnergy_Temp2 += sout2[n].nValue/sqrt(fDistance);

		}

		fEnergy_SolvToChgIn = fEnergy_SolvToChgIn + fEnergy_Temp2*prggvAtomicCrg[i].nValue;
	}

	fEnergy_Coulombic = fEnergy_Coulombic / 2.0;
	fEnergy_SolvToChgIn = fEnergy_SolvToChgIn * 0.0006023 / (2.0 * fEpsOut);

}
