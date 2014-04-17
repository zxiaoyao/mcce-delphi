#ifndef SPACE_H
#define SPACE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <memory>
//#include <deque>

#include <cmath>      // std::abs

#include "../interface/interface_abstractmodule.h"
#include "../misc/misc_timer.h"
#include "../delphi/delphi_constants.h"
#include "../io/io.h"
#include "../interface/interface_datacontainer.h"
#include "space_templates.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class CDelphiSpace:virtual public IAbstractModule
{
private:                                            // In DATA CONTAINER
    shared_ptr<CTimer> pTimer;

    /*********************************************************************************************
    *                                                                                           *
    *              references to the variables obtained from the data container                 *
    *                                                                                           *
    ********************************************************************************************/

    //++++++++++++++ const references to read-only variables from data container +++++++++++++++//

    const integer& iNatom;                           // natom
    const real&    fScale;                           // scale
    const integer& iGrid;                            // igrid (modified in setFocusBndy)
    const integer& iNObject;                         // nobject

    const bool& bUniformDiel;                       //
    //const bool& bVerbose;                           // removed
    const bool& bOnlyMol;                           //
    const bool& isolv;                           //
    const bool& irea;                           //
    const bool& logs;                           //
    const bool& lognl;                           //
    const bool& isen;                           //
    const bool& isch;                           //
    const bool& isite;                           //
    const bool& ibem;                           //
    const bool& ibctyp;
    const bool& isitsf;



    //const bool& bDebug;                             //

    //const int& iTestGloble;                         //
    //const int& ibmx;                                //ibmx is removed
    //const int& iGaussian;
    const integer& iNMedia;
    const integer& numbmol;

    const integer& scrgfrm;
    //const integer& ndistr;
    const SGrid<real>& cOldMid;

    const real& fIonStrenth;
    const real& fExternRadius;
    const real& fRMax;
    const vector < real >& fRadPrb_v;
    const real* fRadPrb;


    const vector <CAtomPdb>& delphipdb;              //delphipdb

    const vector <string> & dataobject_v;




    //++++++++++++++++ reference to read-and-write variables from data container +++++++++++++++//

    integer ndistr;                         // ndistr

    integer& iBoundNum;                       // ibnum
    real& rdmx;                            // rdmx
    integer& nqass;
    integer& nqgrd;
    bool& iacs;                               //
    bool& isrf;
    SGrid<real>& cMin;
    SGrid<real>& cMax;
    real& qnet;
    real& qmin;
    real& qplus;
    SGrid<real>& cqmin;
    SGrid<real>& cqplus;

    vector <real>& medeps;
    vector < SGrid<real> >& xn1_v;      //prgfgAtomCoordA
    vector < SGrid<real> >& xn2_v;      //prgfgAtomCoordG

    vector <bool>& bDebMap_v;             //idebmap

    vector < SGrid<integer> >& iEpsMap_v; //iepsmap

    vector <integer>& iAtomMed_v;                 //iatmmed
    vector < SExtrema<real> >& sLimObject;       //limobject

    vector <SGrid <integer> >& ibgrd_v;               //ibgrd

    vector < SGrid <real> >& scspos_v;

    vector < SGrid <real> >& chgpos_v;

    vector <integer>& crgatn_v;
    vector <integer>& nqgrdtonqass_v;
    vector <real>& atmeps_v;
    vector< SGridValue<real> >& atmcrg_v;
    vector< SGridValue<real> >& chrgv2_v;

    vector < SGrid <real> >& scsnor_v;
    vector < integer >& atsurf_v;
    vector < integer >& atndx_v;



    //+++++++++++++++++++ NON-refereces: +++++++++++++++++++++++++++++++++++++++++++++
    struct delphipdb_struc
    {
        SGrid <real> xyz;
        real charge;
        real radius;
    };

    delphipdb_struc * sDelPhiPDB;




    //################# semi global variables in this class #########################

    bool space_debug;
    integer iBoundNumsurf,extot,iall,lcb, mcb, ncb, lcb1, mcb1, ncb1;
    real radpmax,grdi, cbai, sideinter, sidemin;
    SGrid <real> mnxyz, xyzo, mxxyz;
    SGrid <integer> lmncb1, lmncb;;
    SExtrema <integer> LimEps;
    integer iGaussian;
    integer extracrg;

    vector <integer>  iab1_v, iab2_v, icume, ast, cbn1_v, cbn2_v, cbal, icbn;
    vector <real> r0,r02,rs2;
    vector < SGrid <real> > expos;
    vector < SExtrema<real> > sLimGridUnit;


    vector < SGrid <real> > vert, vnorm, vnorm2;
    vector < SGrid <integer> > vindx;
    vector <integer> vtlen, vtlst, vtpnt;

    integer ** tmlst;

    //SGrid <real> * scsnor;
    //integer * atsurf;
    //integer * atndx;



    SGrid<real> * xn1;
    SGrid<real> * xn2;

    SGrid <integer> * ibgrd;               //ibgrd
    SGridValue <real> * atmcrg;
    SGridValue <real> * chrgv2;
    SGrid <real> * scspos;
    SGrid <real> * chgpos;

    SGrid <real> * scsnor;
    integer * atsurf;
    integer * atndx;



    integer * crgatn;
    integer * nqgrdtonqass;
    real * atmeps;


    SGrid <integer> *** egrid;
    bool *** bDebMap;
    bool *** idebmap;
    SGrid <integer> *** iepsmp;
    integer *** cbn1, *** cbn2, *** iab1, *** iab2;
    integer * iAtomMed;


/*
    template <class T> T *** getKey_Ptr3( vector <T> v_1d, const int& iRows, const int& iColumns, const int& iPages)
    {
        //if (!keyExists(strKey)) throw CInexistentKey(strKey);

        //vector<T> * nConstVectorPtr = any_cast< vector<T> >(&myData[strKey]);

        //if (nConstVectorPtr->size() != (unsigned int)iRows*iColumns*iPages) throw CUnmatchSize(strKey);
        cout << "in getkey_ptr3: " << endl;
        if (v_1d.size() != (unsigned int)iRows*iColumns*iPages) cerr << "error while getting ptr" << endl;

        T * nConstDataPtr = v_1d.data();

        T *** prg3D = new T ** [iRows];

        for (int i = 0; i < iRows; i++)
        {
            prg3D[i] = new T * [iColumns];

            for (int j = 0; j < iColumns; j++)
                prg3D[i][j] = &nConstDataPtr[i*iColumns*iPages+j*iPages];
        }

        return prg3D;
    }
*/

    //############### Functions in other files: ######################
    void epsmak();
    void setout();
    void VdwToMs();
    void VdwToMs_piece(bool & , const integer& , const integer& , const integer& , const integer& , const real& , const SGrid <real>& , integer * , integer * , integer &  ,real & );
    void sas();
    void cube();
    void cubedata(real, real );
    void indverdata(real);
    void indver(integer);
    void sclbp();
    void msrf();
    void crgarr();


    SGrid <int> int_coord( const int& a, const int& b,  const int& c);

    SGrid <float> coord( const float& a,  const float& b,  const float& c);

    SGrid <int> Float2Int( const SGrid <float>& a );

    int Float2Int(const float& a);

    SGrid <float> Int2Float( const SGrid <int>& a );

    float Int2Float(const int& a);

    shared_ptr<IDataContainer> test_pdc;





public:
    SGrid <integer> *** iEpsMap;
    CDelphiSpace(shared_ptr<IDataContainer> pdc,shared_ptr<CTimer> pt):
/*********************************************************************************************
*                                                                                           *
*              references to the variables obtained from the data container                 *
*                                                                                           *
********************************************************************************************/

        //++++++++++++++ const references to read-only variables from data container +++++++++++++++//
        IAbstractModule(pdc),
        pTimer(pt),

        iNatom (pdc->getKey_constRef<integer>("natom")),
        fScale (pdc->getKey_constRef<real>("scale")),
        iGrid (pdc->getKey_constRef<integer>("igrid")),
        iNObject (pdc->getKey_constRef<integer>("nobject")),
        //ndistr (pdc->getKey_constRef<integer>("ndistr")),
        bUniformDiel (pdc->getKey_constRef<bool>("uniformdiel")),
        bOnlyMol (pdc->getKey_constRef<bool>("ionlymol")),
        isolv (pdc->getKey_constRef<bool>("isolv")),
        irea (pdc->getKey_constRef<bool>("irea")),
        logs (pdc->getKey_constRef<bool>("logs")),
        isen (pdc->getKey_constRef<bool>("isen")),
        isch (pdc->getKey_constRef<bool>("isch")),
        lognl (pdc->getKey_constRef<bool>("lognl")),
        isite (pdc->getKey_constRef<bool>("isite")),
        ibem (pdc->getKey_constRef<bool>("ibem")),
        ibctyp (pdc->getKey_constRef<bool>("ibctyp")),
        isitsf (pdc->getKey_constRef<bool>("isitsf")),



        //bDebug (pdc->getKey_constRef<bool>("debug")),

        //iTestGloble (pdc->getKey_constRef<int>(" ")),
        //iGaussian (pdc->getKey_constRef<int>(" ")),
        iNMedia (pdc->getKey_constRef<integer>("nmedia")),
        numbmol (pdc->getKey_constRef<integer>("numbmol")),
        scrgfrm (pdc->getKey_constRef<integer>("scrgfrm")),

        //ndistr (pdc->getKey_constRef<integer>("ndistr")),

        //fRMid (pdc->getKey_constRef<real>("rmid")),
        fIonStrenth (pdc->getKey_constRef<real>("rionst")),
        fExternRadius (pdc->getKey_constRef<real>("exrad")),
        fRMax (pdc->getKey_constRef<real>("rdmx")),
        fRadPrb_v (pdc->getKey_constRef<vector <real> >("radprb")),

        delphipdb (pdc->getKey_constRef<vector <CAtomPdb> >("delphipdb")),

        cOldMid(pdc->getKey_constRef< SGrid<real> >("oldmid")),
        dataobject_v(pdc->getKey_constRef< vector<string> >("dataobject")),

        //++++++++++++++++ reference to read-and-write variables from data container +++++++++++++++//

        iBoundNum (pdc->getKey_Ref<integer>("ibnum")),
        nqass (pdc->getKey_Ref<integer>("nqass")),
        nqgrd (pdc->getKey_Ref<integer>("nqgrd")),

        rdmx (pdc->getKey_Ref<real>("rdmx")),
        iAtomMed_v(pdc->getKey_Ref< vector<integer> >("iatmmed")),
        sLimObject(pdc->getKey_Ref< vector < SExtrema<real> > >("limobject")),
        iacs(pdc->getKey_Ref< bool >("iacs")),
        isrf(pdc->getKey_Ref< bool >("isrf")),
        cMin(pdc->getKey_Ref< SGrid<real> >("cmin")),
        cMax(pdc->getKey_Ref< SGrid<real> >("cmax")),

        qnet(pdc->getKey_Ref< real >("qnet")),
        qmin(pdc->getKey_Ref< real >("qmin")),
        qplus(pdc->getKey_Ref< real >("qplus")),
        cqmin(pdc->getKey_Ref< SGrid<real> >("cqmin")),
        cqplus(pdc->getKey_Ref< SGrid<real> >("cqplus")),
        medeps(pdc->getKey_Ref < vector < real > >("medeps")),




        ibgrd_v(pdc->getKey_Ref< vector< SGrid<integer> > >("ibgrd")),
        scspos_v(pdc->getKey_Ref< vector< SGrid<real> > >("scspos")),
        chgpos_v(pdc->getKey_Ref< vector< SGrid<real> > >("chgpos")),
        crgatn_v(pdc->getKey_Ref< vector< integer > >("crgatn")),
        atmeps_v(pdc->getKey_Ref< vector< real > >("atmeps")),

        nqgrdtonqass_v(pdc->getKey_Ref< vector< integer > >("nqgrdtonqass")),
        atmcrg_v(pdc->getKey_Ref< vector< SGridValue<real> > >("atmcrg")),
        chrgv2_v(pdc->getKey_Ref< vector< SGridValue<real> > >("chrgv2")),

        scsnor_v(pdc->getKey_Ref< vector< SGrid<real> > >("scsnor")),

        atsurf_v(pdc->getKey_Ref< vector< integer > >("atsurf")),
        atndx_v(pdc->getKey_Ref< vector< integer > >("atndx")),

        xn1_v(pdc->getKey_Ref< vector< SGrid<real> > >("xn1")),
        xn2_v(pdc->getKey_Ref< vector< SGrid<real> > >("xn2")),
        bDebMap_v( pdc->getKey_Ref< vector< bool > >("idebmap")),
        iEpsMap_v( pdc->getKey_Ref< vector< SGrid<integer> > > ("iepsmp"))



    {
        //bDebMap_v=pdc->getKey_Ref< vector< bool > >("idebmap");
        bDebMap_v.assign(iGrid*iGrid*iGrid, true);
        iEpsMap_v.assign(iGrid*iGrid*iGrid, {0,0,0});
        iEpsMap=pdc->getKey_Ptr < SGrid <integer> > ( "iepsmp",iGrid,iGrid,iGrid);
        iAtomMed=&iAtomMed_v[-1];


        sDelPhiPDB = new delphipdb_struc [iNatom+1];
        bDebMap=get_pt3d <bool> (iGrid,iGrid,iGrid);

        //egrid = get_pt3d <SGrid <integer> > (iGrid,iGrid,iGrid);

        iGaussian=0;
        ndistr = 0;


        test_pdc=pdc;

    };


    ~CDelphiSpace() {};

    virtual void validateInput();

    virtual void run();
};

#endif // SPACE_H
