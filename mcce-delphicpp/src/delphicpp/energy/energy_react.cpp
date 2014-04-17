/*
 * energy_react.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: Lin Wang
 */

#include "energy.h"

void CDelphiEnergy::energy_react(real& fEnergy_Solvation, real& fEnergy_AnalySurf, int& iisitpot){


//	sitephi(5,npotenziali+nvincfit),schrg(ibnum))
//	sqs(ibnum),spdiv(ibnum),sen(ibnum),spot(ibnum),cqs(nqass)
//	gchrgp= (i,j,k)  for the icount1b charged grid points


	bool ido;
	int ix, iy, iz;
	int i, j, ii, jj, qq;
	real fRadius, fEnergy_SelfReaction, fCost, fVal;
	real fEnergy_Temp, fEnergy_Temp1, fEnergy_TotalCharge;
	real dist, dist4, fEnergy_Temp2, fEnergy_Temp3, fFact, prod, ptemp;
	real schrgj, temp, temp1, temp2, temp3, spt1, fConstSixth;

	vector<real> spdiv, sqs, cqs, sen, spot;
	SGrid<int> ixyz;
	SGrid<real> scspos, chgpos, xo;
	SGridValue<real> fCGridValue_Temp;

	fFact = 0.9549296586/(2.0*fScale*fEPKT);
	fConstSixth = 1.0/6.0;
    fEnergy_Temp1=0.0;
    fEnergy_SelfReaction=0.0;

	for(i=0;i<iTotalBdyGridNum;i++){

		ix=prgigBndyGrid[i].nX;
		iy=prgigBndyGrid[i].nY;
		iz=prgigBndyGrid[i].nZ;

		temp1 = prgfPhimap[(iz-1)*iGrid*iGrid+(iy-1)*iGrid+ix]+prgfPhimap[(iz-1)*iGrid*iGrid+(iy-1)*iGrid+(ix-2)];
		temp2 = prgfPhimap[(iz-1)*iGrid*iGrid+(iy)*iGrid+(ix-1)]+prgfPhimap[(iz-1)*iGrid*iGrid+(iy-2)*iGrid+(ix-1)];
		temp3 = prgfPhimap[(iz)*iGrid*iGrid+(iy-1)*iGrid+(ix-1)]+prgfPhimap[(iz-2)*iGrid*iGrid+(iy-1)*iGrid+(ix-1)];
		temp = prgfPhimap[(iz-1)*iGrid*iGrid+(iy-1)*iGrid+(ix-1)]-(temp1+temp2+temp3)*fConstSixth;

		spdiv.push_back(temp);

	}

	if(iCrgBdyGrid!=0){   // iCrgBdyGrid -> ibc (number of charged boundary grid points) here=30
							// iTotalBdyGridNum -> ibnum (# of boundary grid points) here=149
							// prgigBndyGrid -> ibgrd (boundary grids) here = 149
							// prgdgvCrgBndyGrid -> cgbp (information on the charged boundary grid points) size(ibc) here=30
		vector < SGridValue<real> > cgrid;

		for(i=0;i<iTotalBdyGridNum;i++){
			fCGridValue_Temp.nGrid.nX = prgigBndyGrid[i].nX;
			fCGridValue_Temp.nGrid.nY = prgigBndyGrid[i].nY;
			fCGridValue_Temp.nGrid.nZ = prgigBndyGrid[i].nZ;
			fCGridValue_Temp.nValue = spdiv[i];
			cgrid.push_back(fCGridValue_Temp);
		}

		for(i=0;i<iCrgBdyGrid;i++){
			ix = prgdgvCrgBndyGrid[i].fgCoord.nX;
			iy = prgdgvCrgBndyGrid[i].fgCoord.nY;
			iz = prgdgvCrgBndyGrid[i].fgCoord.nZ;
			fVal = prgdgvCrgBndyGrid[i].fVal1;

			for(j=0;j<iTotalBdyGridNum;j++){
				if(cgrid[j].nGrid.nX == ix && cgrid[j].nGrid.nY == iy && cgrid[j].nGrid.nZ == iz){

					cgrid[j].nValue = cgrid[j].nValue - fVal;

				}
			}
		}



		for(i=0;i<iTotalBdyGridNum;i++){
			spdiv[i] = cgrid[i].nValue;
		}

		cgrid.clear();
	}

	fEnergy_Temp1=0.0;
	for(i=0;i<iTotalBdyGridNum;i++){
		temp=spdiv[i]*fFact;
		schrg.push_back(temp);
		fEnergy_Temp1=fEnergy_Temp1+temp;

		}

	if(bReactFieldlnFRC || bSolvEng || bNonlinearEng || bSurfEngOut || bSurfCrgOut){
		for(i=0;i<iTotalBdyGridNum;i++){
			scspos = prgfgSurfCrgA[i];
			temp = 0.5 * optDot(scspos,scspos);
			sqs.push_back(temp);
		}

		if(bSolvEng || bNonlinearEng){

			fEnergy_Temp=0.0; fEnergy_Temp2=0.0; fEnergy_Temp3=0.0; fEnergy_TotalCharge=0.0; fCost=0.0;
			if(iMediaNum>0){
				for(i=0;i<iCrgGridNum;i++){
					fRadius = 1.0; // fortran code, radius = radpolext, which is removed
					ii = prgiCrgAt[i];
					if(ii>0 && ii<=iAtomNum){
						fRadius = prgapAtomPdb[ii-1].getRadius();
						fCost = 1.0/(fEPKT*prgfAtomEps[i])-1.0;

						if(prgfAtomEps[i]<=0){
							cout << " atmeps error  " << i << "  " << ii << endl;
						}

						if(fRadius<=0){
							cout << " charged atom number " << ii << "  radius changed from zero to " << 1.0 << endl;
							cout << " BE CAREFUL!! REACTION FIELD ENERGY MIGHT BE OVERESTIMATED!!!!" << endl;
							fRadius = 1.0;
						}

					}

					fEnergy_SelfReaction = fEnergy_SelfReaction + 0.5*prggvAtomicCrg[i].nValue*prggvAtomicCrg[i].nValue*fCost/fRadius; // not very clear

				}

				fEnergy_SelfReaction = fEnergy_SelfReaction * fEPKT;

				cout << " self-reaction field energy       :               " << setw(8) << right << fEnergy_SelfReaction << " kt" << endl;

				if(bEngOut){
					ofstream ofEnergyFile;
					ofEnergyFile.open(strEnergyFile,std::fstream::app);
					ofEnergyFile << "self-reaction field energy     :  " << fEnergy_SelfReaction << " kt \n";
				    ofEnergyFile.close();
				}
			}

			if(bBuffz){		// bBuffz -> ibufz (flag activating the BUFFZ feature for reaction field energy)
				for(i=0;i<iCrgGridNum;i++){
					chgpos = prgfgCrgPoseA[i];
					temp = optDot(chgpos,chgpos)/2.0;
					cqs.push_back(temp);
				}

				fEnergy_Temp = 0.0;
				lim_min = 2 + ieBuffz.nMin;
				lim_max = iGrid - 1 - ieBuffz.nMax;

				for(j=0;j<iTotalBdyGridNum;j++){
						ixyz = prgigBndyGrid[i];
						ido = 1;
						if(optORLT<int>(ixyz,lim_min) || optORGT<int>(ixyz,lim_max)){
						ido = 0;
						}
						if(ido){
							dist4 = sqs[j];
							schrgj = schrg[j]/sqrt(2.0);
							fEnergy_Temp1 = 0.0;
							fEnergy_TotalCharge = fEnergy_TotalCharge + schrg[j];

							for(i=0;i<iCrgGridNum;i++){
								// prgfgCrgPoseA -> chgpos
								// prgfgSurfCrgA -> scspos
								// prod=scspos(j).dot.chgpos(i)

								scspos = prgfgSurfCrgA[j];
								chgpos = prgfgCrgPoseA[i];
								prod = optDot(scspos,chgpos);
								dist = dist4 + cqs[i] - prod;
								temp = prggvAtomicCrg[i].nValue/sqrt(dist);
								fEnergy_Temp1 = fEnergy_Temp1 + temp;
							}

							fEnergy_Temp = fEnergy_Temp + fEnergy_Temp1*schrgj;
							temp1 = schrgj*fEnergy_Temp1;
							sen.push_back(temp1);

						}

				}  // j loop ends

				fEnergy_Solvation = fEnergy_Temp*fEPKT/2.0;
				cout << " tot s.charge, no epsin carrying  :               " << setw(8) << right << fEnergy_TotalCharge << endl;
				cout << " corrected reaction field energy  :               " << setw(8) << right << fEnergy_Solvation << " kt" << endl;
				cout << " total reaction field energy      :               " << setw(8) << right << (fEnergy_SelfReaction+fEnergy_Solvation) << " kt" << endl;

				if(bEngOut){
					ofstream ofEnergyFile;
					ofEnergyFile.open(strEnergyFile,std::fstream::app);
					ofEnergyFile << "corrected reaction field energy :  " << fEnergy_Solvation << " kt\n";
					ofEnergyFile << "total reaction field energy    :  " << (fEnergy_SelfReaction+fEnergy_Solvation) << " kt\n";
					ofEnergyFile.close();
				}
			}
			if(!bBuffz){
				for(i=0;i<iTotalBdyGridNum;i++){
					ptemp = 0.0;
					for(j=0;j<iCrgGridNum;j++){
						xo= prgfgSurfCrgA[i] - prgfgCrgPoseA[j];
						dist = sqrt(optDot(xo,xo));
						ptemp = ptemp + prggvAtomicCrg[j].nValue/dist;
					}
					spot.push_back(ptemp);
				} // i loop ends

				fEnergy_Temp=0.0; fEnergy_TotalCharge = 0.0;

				for(i=0;i<iTotalBdyGridNum;i++){
					temp = spot[i]*schrg[i];
					fEnergy_TotalCharge = fEnergy_TotalCharge + schrg[i];
					fEnergy_Temp = fEnergy_Temp + temp;
				}

				fEnergy_Solvation = fEnergy_Temp*fEPKT/2.0;

				cout << " total s.charge,no epsin carrying :               " << setw(8) << right << fEnergy_TotalCharge << endl;
				if(iTotalBdyGridNum==0 || iGrid<5){
					cout << " Midpoints are out side the cube and delphi cannot determine the molecular surface." << endl;
					cout << " Please enlarge the gsize or decrease the perfil value." << endl;
				}
				cout << " corrected reaction field energy  :               " << setw(8) << right << fEnergy_Solvation << " kt" << endl;
				cout << " total reaction field energy      :               " << setw(8) << right << (fEnergy_SelfReaction+fEnergy_Solvation) <<" kt" << endl;
				if(bEngOut){
					ofstream ofEnergyFile;
					ofEnergyFile.open(strEnergyFile,std::fstream::app);
					ofEnergyFile << "corrected reaction field energy : " << fEnergy_Solvation << " kt\n";
					ofEnergyFile << "total reaction field energy     : " << (fEnergy_SelfReaction+fEnergy_Solvation) <<" kt\n";
					ofEnergyFile.close();
				}
			}
		}

		if(bSurfCrgOut){
			cout << "writing surface charge file : scrg.dat" << endl;
			ofstream ofScrgFile;
			ofScrgFile.open ("scrg.dat");
			// iSurfCrgFormatOut -> scrgfrm; integer Format of file scrgnam, = 0 if unknown format, = 1 if �PDB�.

			if(iSurfCrgFormatOut==1 || iSurfCrgFormatOut==2 ){
				ofScrgFile << "DELPHI FORMAT PDB" << endl;
				ofScrgFile << "FORMAT NUMBER = " << iSurfCrgFormatOut << endl;
				ofScrgFile << "      bgp# atom SC   res#      pos  scrg          surf energy" << endl;

			}
			if(bBuffz){
				lim_min = 2+ieBuffz.nMin;
				lim_max = iGrid-1-ieBuffz.nMax;
			}
			for(i=0;i<iTotalBdyGridNum;i++){
					ixyz = prgigBndyGrid[i];
					if(bBuffz){
						ido = 1;
						if(optORLT<int>(ixyz,lim_min) || optORGT<int>(ixyz,lim_max)){
							ido = 0;
						}
						if(ido==0) continue;
					}

					fEnergy_Temp1 = schrg[i];
					spt1 = spot[i]*fEnergy_Temp1*fEPKT/2.0;

					if(iSurfCrgFormatOut==0){
						ofScrgFile << setw(8) << fixed << right << i+1 << "  " << prgfgSurfCrgA[i].nX << "  " << prgfgSurfCrgA[i].nY << "  " << prgfgSurfCrgA[i].nZ << "  " << fEnergy_Temp1 << endl;
					}

					if(iSurfCrgFormatOut==1 || iSurfCrgFormatOut==2){
						jj = atsurf[i];	   //from surface construction class
						qq = atoi(prgapAtomPdb[jj].getAtInf().substr(11,4).c_str());
						// line
					}



			}
		}

		if(bSurfEngOut){
			cout << " writing surface energy file: surfen.dat" << endl;
			ofstream surfen;
			surfen.open("surfen.dat");
			fEnergy_Temp2=0.0;
			for(i=0;i<iTotalBdyGridNum;i++){

				fEnergy_Temp1 = sen[i]/2.0;
				surfen << setw(8) << fixed << right << i+1 << "  " << prgfgSurfCrgA[i].nX << "  " << prgfgSurfCrgA[i].nY << "  " << prgfgSurfCrgA[i].nZ << "  " << fEnergy_Temp1 << endl;

			}
			surfen.close();
		}

	}
	spdiv.clear(); sqs.clear(); cqs.clear(); sen.clear(); spot.clear();

}

