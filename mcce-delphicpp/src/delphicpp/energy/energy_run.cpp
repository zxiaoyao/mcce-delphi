/*
 * energy_run.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: Lin Wang
 */

#include "energy.h"

//----------------------------------------------------------//
//    logs= solvation energy
//    logc= coulombic energy
//    loga= analytic energy
//    logg= grid energy
//    logions= ionic contribution
//    lognl=ionic contribution in non linear case
//-----------------------------------------------------------------------//

// inrgwrt    -> bool bEngOut (flag for writing energy in unit 42 file)
// loga       -> bool bAnalyEng (flag for calculating analytic energy)
// logg       -> bool bGridEng (flag for calculating grid energy)
// lognl      -> bool bNonlinearEng	(Flag for non linear energy calculation)
// logs       -> bool bSolvEng (flag for calculating solvation energy)
// logc       -> bool bCoulombEng (flag for calculating coulombic energy)
// logions    -> bool bIonsEng (Flag for energy calculation of contribution from the solvent.)
// nrgnam     -> string	strEnergyFile
// icount1b   -> integer	iCrgedGridB	(number of charged grid points in odd/even arries, to be used in making qval and iqpos)
// gchrgp     -> int_coord	no suggested name (gchrgp is the position of each such charge on the grid)
// ideveloper -> bool DEVELOPER (flag to control the precision of outputs)
// phimap     -> vector<real> prgfPhimap
//
// vdrop      ->
// irea       -> bool bReactFieldInFRC (flag for calculating reaction field and output it in formatted frc file)
// isch       -> bool bSurfCrgOut (flag for outputting surface charge file)

void CDelphiEnergy::run()
{
   int i, iw, iGridOutput, iisitpot;

   real fEnergy_Grid=0.0;
   real fEnergy_Solvation=0.0;
   real fEnergy_AnalySurf=0.0;
	real fEnergy_Nonlinear=0.0;
   real fEnergy_Coulombic=0.0;
    
   real fEnergy_AnalyGrid=0.0;
   real fEnergy_SolvToChgIn=0.0;
	real fEnergy_SolvToChgOut = 0.0;  // solvent contribution to fixed charges  outside the cube is zero.
	real fEnergy_Total=0.0;
//	real fPi = 3.1415926;

	SGrid<int> ixyz;

//	vector<real> deltaphi, finish, phidown, zfieldown, zfieldup;
//	vector<real> phiup, enface;


	bool ido;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef DEBUG_DELPHI_ENERGY
   // ++ To set the flags for test, do it in the app_delphi.cpp   ++//
   cout << "bGridEng         = " << bGridEng << endl;
   cout << "bReactFieldlnFRC = " << bReactFieldlnFRC << endl;
   cout << "bSolvEng         = " << bSolvEng << endl;
   cout << "bNonlinearEng    = " << bNonlinearEng << endl;
   cout << "bAnalySurfEng    = " << bAnalySurfEng << endl;
   cout << "bSurfEngOut      = " << bSurfEngOut << endl;
   cout << "bSurfCrgOut      = " << bSurfCrgOut << endl;
   cout << "bBuffz           = " << bBuffz << endl;
   cout << "bCoulombEng      = " << bCoulombEng << endl;
   cout << "bIonsEng         = " << bIonsEng << endl;
#endif

   // +++++++++++++++++++++ Analytic grid energy +++++++++++++++++++++

	if(bEngOut){		// output energy calculation results "energy.dat"
		ofstream ofEnergyFile;
		ofEnergyFile.open(strEnergyFile);
		ofEnergyFile.close();
	}

		if(bAnalyEng){
			fEnergy_AnalyGrid=0.0;
			cout << " analytic grid energy is no longer available." << endl;


			if(bEngOut){
				ofstream ofEnergyFile;
				ofEnergyFile.open(strEnergyFile,std::fstream::app);
				ofEnergyFile << " analytic grid energy is " << fEnergy_AnalyGrid << " kt.\n";
				ofEnergyFile.close();
			}
			exit (EXIT_FAILURE);
		}

	//  +++++++++++++++ Total grid energy ++++++++++++++++++++++++++++ //

		if(bGridEng){
			fEnergy_Grid=0.0;
			lim_min = 2+ieBuffz.nMin;  //ieBuffz(pdc->getKey_constRef< SExtrema<int> >("bufz"))
			lim_max = iGrid-1-ieBuffz.nMax;	 //lim%min=2+bufz%min ; lim%max=igrid-1-bufz%max


			for(i=0;i<iCrgedGridB;i++){
				ixyz = prgigGridCrgPose[i];


				ido = 1;
				if(optORLT<int>(ixyz,lim_min) || optORGT<int>(ixyz,lim_max)){
					ido = 0;
				}
				if(ido){
					iw = ((ixyz.nZ-1)*iGrid*iGrid)+(ixyz.nY-1)*iGrid+(ixyz.nX-1);  // i, j, k -> k, j, i (z, y, x)

					fEnergy_Grid = fEnergy_Grid + prgfPhimap[iw]*prgfGridCrg[i];

				}


			}

			fEnergy_Grid = fEnergy_Grid / 2.0;

			cout << endl;
			cout << " total grid energy                :               " << setw(8) << right << fEnergy_Grid << " kt" << endl;

			if(bEngOut){
				ofstream ofEnergyFile;
				ofEnergyFile.open(strEnergyFile,std::fstream::app);
				ofEnergyFile << "total grid energy		:   " << setw(8) << fEnergy_Grid << " kt \n";
				ofEnergyFile.close();
			}
		}

		//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


	if(bGridEng && bAnalyEng){
		cout << " difference energy, in kt, is  " << fEnergy_Grid-fEnergy_AnalyGrid << endl;
		cout << " difference energy, in kcals, is  " << (fEnergy_Grid-fEnergy_AnalyGrid)*0.6 << endl;
	}

		//  +++++++++++++++ For polarized membrane (not supported and not tested) +++++ //


	if(iBndyType == 5){
		cout << " WARNING!!!Not completely tested routine for polarized membrane!!" << endl;
        exit (EXIT_FAILURE);

		if(bNonlinearEng || bAnalySurfEng){
			cout << "This option is not yet working with fixed potential difference!" << endl;

			fEnergy_AnalySurf=0.0;fEnergy_Nonlinear=0.0;

		}

/*
		deltaphi=0.0;
		zfieldown=0.0;
		zfieldup=0.0;

		ofstream fields;
		fields.open("fields.txt");
		for(ix=1; ix<iGrid-1; ix++){
			for(iy=1; iy<iGrid-1;iy++){
				phiup = vector<real> prgfPhimap(ix,iy,iGrid);
				phidown = vector<real> prgfPhimap(ix,iy,0);
				deltaphi = deltaphi + (phiup - vector<real> prgfPhimap(ix,iy,iGrid-2));
				zfieldup = zfieldup - (phiup - vector<real> prgfPhimap(ix,iy,iGrid-2))*fScale;
//			averaging over upper and lower cube faces in order to cancel numerical errors.	//
				deltaphi = deltaphi - (phidown - vector<real> prgfPhimap(ix,iy,1));
				zfieldown = zfieldown + (phidown - vector<real> prgfPhimap(ix,iy,1))*fScale;
			}
		}

		enface = deltaphi * fgPotentialDrop.nZ * fEpsOut; * ((iGrid-1.0)/((iGrid-2.0)*(iGrid-2.0))/(4.0*fPi*fScale));// unclear operation here!!
		cout << "Energy contribution from voltage drop = " << enface << " kt" << endl;
		fields.close();

		ofstream potcen;
		potcen.open("potcen.txt");
		cout << "fieldup medio: " << zfieldup/((iGrid - 2)*(iGrid - 2))<< endl;
		cout << "fieldown medio: " << zfieldown/((iGrid - 2)*(iGrid - 2)) << endl;

		for(iz=0;iz<=iGrid;iz++){

			iw = (iGrid+1)/2*iGrid*iGrid + (iGrid+1)/2*iGrid + iz;
			potcen << iz << "   " << prgfPhimap[iw] << endl;
		}
		potcen.close();
*/	}


	//  ++++++++++++++++++ Reaction field energy calculation ++++++++++++++++++++++++++ //


	if(bReactFieldlnFRC || bSolvEng || bNonlinearEng || bAnalySurfEng || bSurfEngOut || bSurfCrgOut){
	// fEnergy_SolvToChgIn = interaction energy of the solvent and the fixed charges. //

		fEnergy_Solvation = 0.0; fEnergy_AnalySurf = 0.0; fEnergy_Nonlinear=0.0; fEnergy_SolvToChgIn = 0.0;

		if(bPotentiallnSite){
			iisitpot = 1;
		}
		else{
			iisitpot = 0;
		}
		energy_react(fEnergy_Solvation, fEnergy_AnalySurf, iisitpot);  // call reaction field function
	}

	//  ++++++++++++++++++ Coulombic energy calculation +++++++++++++++++++++++++++++++ //

	if(bCoulombEng && (!bIonsEng || !bNonlinearEng)){
		fEnergy_Coulombic = 0.0;

		if(bIonsEng){
			fEnergy_SolvToChgIn = 0.0;
			energy_clbtotal(fEnergy_SolvToChgIn, fEnergy_Coulombic);	// call clbtotal function.
			{CIonicCalcUnderTest waring;}
			cout << " solvent contribution to fixed charges" << endl;
			cout << " respectively inside and outside the cube :               ";
			cout << setw(8) << right << fEnergy_SolvToChgIn << "  kt   " << fEnergy_SolvToChgOut << "  kt" << endl;  // where is ergestout??
			cout << " total ionic direct contribution  :               " << setw(8) << right << (fEnergy_SolvToChgIn+fEnergy_SolvToChgOut) << "  kt" << endl;

		}
		else {
			if(iMediaNum == 1){
				energy_clb(fEnergy_Coulombic);	// call clb function.
				fEnergy_Coulombic = fEnergy_Coulombic / fEpsin;
			}
			else{
			energy_clbmedia(fEnergy_Coulombic);	// call clbmedia function.
			}
		}

		cout << " coulombic energy                 :               " << setw(8) << right << fEnergy_Coulombic << " kt" << endl;

		if(bEngOut){
			ofstream ofEnergyFile;
			ofEnergyFile.open(strEnergyFile,std::fstream::app);
			ofEnergyFile << "total coulombic energy  :  " << fEnergy_Coulombic << " kt \n";
			ofEnergyFile.close();
		}
	}

	//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

	if(bNonlinearEng){
		energy_nonl(fEnergy_Nonlinear, iGridOutput);	// call nonlinear function.

		fEnergy_Coulombic = 0.0; fEnergy_SolvToChgIn = 0.0;

		if(bIonsEng){
			energy_clbnonl(fEnergy_Coulombic, fEnergy_SolvToChgIn, iGridOutput);

			cout << " direct ionic contribution inside the box :       " << setw(8) << right << fEnergy_SolvToChgIn << " kt" << endl;
			cout << " coulombic energy                 :               " << setw(8) << right << fEnergy_Coulombic << " kt" << endl;
			if(bEngOut){
				ofstream ofEnergyFile;
				ofEnergyFile.open(strEnergyFile,std::fstream::app);
				ofEnergyFile << "total coulombic energy :  " << setw(8) << fEnergy_Coulombic << " kt \n";
				ofEnergyFile.close();
			}

		}
		sout.clear();
	}

	//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


	if(bSolvEng && bIonsEng){
		cout << " Energy arising from solvent and boundary pol.  " << setw(8) << right << (fEnergy_Nonlinear+fEnergy_Solvation+fEnergy_SolvToChgIn+fEnergy_SolvToChgOut) << " kt" << "\n";
	}

	//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


	if(bNonlinearEng && bGridEng){
		cout << " total non linear grid energy	  :               " << setw(8) << right << (fEnergy_Grid+fEnergy_Nonlinear) << " kt \n";
	}

	//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
   
	fEnergy_Total = fEnergy_Nonlinear + fEnergy_Coulombic + fEnergy_Solvation + fEnergy_SolvToChgIn + fEnergy_SolvToChgOut;

	if(bSolvEng || bCoulombEng){
		cout << " all required energy terms but grid and self_react.:  " << setw(8) << right << fEnergy_Total << " kt" << endl;
		if(bEngOut){
			ofstream ofEnergyFile;
			ofEnergyFile.open(strEnergyFile,std::fstream::app);
			ofEnergyFile << "total required energy (everything calculated but grid and self_reaction energies: " << setw(8) << fEnergy_Total << " kt \n";
			ofEnergyFile.close();
		}
	}

	//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

	if(bAnalySurfEng && bAnalyEng && bGridEng){
		cout << " excess grid energy =               " << setw(8) << right  << (fEnergy_Grid - fEnergy_AnalySurf - fEnergy_AnalyGrid) << endl;
	}

	//  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

	cout << endl;
//	cout << "total time of energy calculation  :  "; pTimer->showElapse(); cout << endl;
	cout << endl;

	ergg    = fEnergy_Grid;
	ergc    = fEnergy_Coulombic;
	ergs    = fEnergy_Solvation;
	ergions = fEnergy_SolvToChgIn + fEnergy_SolvToChgOut;
}



