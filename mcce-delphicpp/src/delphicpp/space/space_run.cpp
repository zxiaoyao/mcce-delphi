/*
 * Space_Run.cpp
 *
 */

#include "space.h"

void CDelphiSpace::run()
{

    if(space_debug) cout << "############### run in Space module.... ##################" << endl;


//    SGrid <integer> *** testEpsmap=pdc->getKey_Ptr("iepsmap",iNatom,iNatom,iNatom);
    /*
        cout << "iNatom: " << iNatom << endl;
        cout << "xn1[0].nX: " << xn1[0].nX << endl;
        cout << "delphipdb[0].getRadius: " << delphipdb[0].getRadius() << endl;
        cout << "delphipdb[0].getPose: " << delphipdb[0].getPose().nX << endl;

        //bDebMap.assign(iNatom*iNatom*iNatom,false);
        //iEpsMap.assign(iNatom*iNatom*iNatom, {0,0,0});

        iEpsMap[1][2][3].nX=54;

        egrid_v[0].nX=66;

        cout << "iEpsMap_v[iGrid*iGrid-1].nX " << iEpsMap_v[iGrid*iGrid+2*iGrid+3].nX << endl;
        cout << "iEpsMap[1][0][0].nX " << iEpsMap[1][2][3].nX << endl;
        cout << "bDebMap_v[0]" << bDebMap_v[0] << endl;
        cout << "iEpsMap_v[0]" << iEpsMap_v[0] << endl;
        cout << "egrid_v[0].nX: " << egrid_v[0].nX << endl;
    */

    integer i,j,k,ix,iy,iz,ic,ico;
    real fRMid;
    SGrid <integer> epstmp;
    bool debtmp;
    SGrid <real> xl,xr;
    fRMid=(iGrid+1)/2.0;
    space_debug=true;
    //######### initialize bDebMap: #########
    for (ix=1; ix<=iGrid; ix++)
    {
        for (iy=1; iy<=iGrid; iy++)
        {
            for (iz=1; iz<=iGrid; iz++)
            {

                bDebMap[ix-1][iy-1][iz-1]=true;
            }
        }
    }

    //##### navigate iepsmp and idebmap, xn1,xn2,fRadProb: ##########
    idebmap=Move_index_3d <bool> (bDebMap,iGrid,iGrid,iGrid);
    iepsmp=Move_index_3d <SGrid <integer> > (iEpsMap,iGrid,iGrid,iGrid);

    xn1=&xn1_v[-1];
    xn2=&xn2_v[-1];
    fRadPrb=&fRadPrb_v[-1];
    //ibgrd=&ibgrd_v[-1];
    //atmcrg=&atmcrg_v[-1];
    //chgpos=&chgpos_v[-1];
    //crgatn=&crgatn_v[-1];
    //atmeps=&atmeps_v[-1];
    //chrgv2=&chrgv2_v[-1];
    //nqgrdtonqass=&nqgrdtonqass_v[-1];

    //for (i=0; i<=iNatom-1; i++)
    //{
    //    cout << "xn2,xn2_v: " << xn2[i] << " " << xn2_v[i-1] << endl;
    //}
//######### initialize sDelPhiPDB: #########

    for (i=0; i<=iNatom-1; i++)
    {
        sDelPhiPDB[i+1].radius=delphipdb[i].getRadius();
        sDelPhiPDB[i+1].xyz=delphipdb[i].getPose();
        sDelPhiPDB[i+1].charge=delphipdb[i].getCharge();

    }
//######## from qdiff4v:  ########
    for (i=1; i<=iNatom; i++)
    {
        xn1[i]=sDelPhiPDB[i].xyz;
        xn2[i]=(sDelPhiPDB[i].xyz-cOldMid)*fScale+fRMid;
        //cout << "cOldMid, fScale, fRMid: " << cOldMid.nX  << " " << cOldMid.nY  << " " << cOldMid.nZ << " " << fScale << " " << fRMid << endl;
        //cout << "i,xn1[i],xn2[i]: " <<i<< xn1[i] << xn2[i] << endl;

    }

    epsmak();


// Now start crgarr


    if (isolv)
    {
//increased the starting dimension of crgatn and..+++++
        extracrg=0;
        if (ndistr>0) extracrg=iGrid*iGrid*iGrid;
        cout << "ndistr: " << ndistr;
//2011-05-30 Allocation of the arrays below is moved to the body of crgarr void, arrays are accessible
// via pointers module. Sizes of arrays are determined before allocation inside the crgarr void

        crgarr();

        xl=cOldMid-(1.0/fScale)*(iGrid+1)*0.5;
        xr=cOldMid+(1.0/fScale)*(iGrid+1)*0.5;

        if (logs||lognl)
        {
            ico=0;
            for(ic=1; ic<=nqass; ic++)
            {
                if ( optORLT(chgpos[ic],xl) || optORGT(chgpos[ic],xr) )
                {
                    if (crgatn[ic]<0)
                    {
                        cout << "!WARNING: distribution " << -crgatn[ic] << "outside the box" << endl;
                    }
                    else
                    {
                        if (crgatn[ic]>iNatom)
                        {
                            cout << "WARNING:crg " << ic << "object " << crgatn[ic]-iNatom << "outside the box " << chgpos[ic] << endl;
                        }
                        else
                        {
                            cout << "//!! WARNING : charge " << delphipdb[crgatn[ic]-1].getAtInf() << "outside the box";
                        }// if
                    }// if
                    ico=1;
                }// if
            }// do
            if (ico>0&&ibctyp!=3)
            {
                cout <<"CHARGES OUTSIDE THE BOX AND NOT DOING FOCUSSING << THEREFORE STOP" << endl;
                exit(0);
            }// if
        }// if
    }// if

    if(space_debug) cout << "#### Lin Li: coverting the matrix...." << endl;
    for(i=1;i<=iGrid-1;i++){
    //for(i=1;i<=iGrid;i++){
       for(j=1;j<=iGrid;j++){
          for(k=i+1;k<=iGrid;k++){
          //for(k=1;k<=iGrid;k++){
	     //cout <<"i,j,k,iepsmp: "<< i <<" " << j << " " << " " << k << " "  << iepsmp[i][j][k] << endl;
	     //cout <<"i,j,k,idebmap: "<< i <<" " << j << " " << " " << k << " "  << idebmap[i][j][k] << " "  << idebmap[k][j][i] << endl;

             epstmp=iepsmp[i][j][k];
             iepsmp[i][j][k]=iepsmp[k][j][i];
             iepsmp[k][j][i]=epstmp;

             //debtmp=idebmap[i][j][k];
             //idebmap[i][j][k]=idebmap[k][j][i];
             //idebmap[k][j][i]=debtmp;

	     //if(i==5&&j==6&&k==1) cout << "i,j,k,iepsmp: " << i << " " << j << " " << k << " " << iepsmp[i][j][k] << endl;
          }
       }
    }


    for(i=1;i<=iGrid;i++){
    //for(i=1;i<=iGrid;i++){
        for(j=1;j<=iGrid;j++){
            for(k=1;k<=iGrid;k++){
                bDebMap_v[(i-1)*iGrid*iGrid+(j-1)*iGrid+(k-1)]=idebmap[k][j][i];

            }
        }
    }

}

