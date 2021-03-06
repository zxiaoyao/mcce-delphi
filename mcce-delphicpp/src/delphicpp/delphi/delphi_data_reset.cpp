/*
 * delphi_data_reset.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: chuan
 */

#include "delphi_data.h"

void CDelphiData::reset(const string& strF95File)
{
   ifstream ifFileStream;
   ifFileStream.open(strF95File.c_str());
   string strLine;

   while(!ifFileStream.eof())
   {
      getline(ifFileStream,strLine);

      //------------------- set by Surface class ---------------------//
      if (string::npos != strLine.find("-nqass-"))
      {
         getline(ifFileStream,strLine);
         this->getKey_Ref<integer>("nqass") = atoi(strLine.c_str());
         continue;
      }

      if (string::npos != strLine.find("-qnet-"))
      {
         getline(ifFileStream,strLine);
         this->getKey_Ref<real>("qnet") = atof(strLine.c_str());
         continue;
      }

      if (string::npos != strLine.find("-qmin-"))
      {
         getline(ifFileStream,strLine);
         this->getKey_Ref<real>("qmin") = atof(strLine.c_str());
         continue;
      }

      if (string::npos != strLine.find("-qplus-"))
      {
         getline(ifFileStream,strLine);
         this->getKey_Ref<real>("qplus") = atof(strLine.c_str());
         continue;
      }

      if (string::npos != strLine.find("-cqplus-"))
      {
         getline(ifFileStream,strLine);
         this->getKey_Ref< SGrid<real> >("cqplus").nX = atof(strLine.substr(0, 21).c_str());
         this->getKey_Ref< SGrid<real> >("cqplus").nY = atof(strLine.substr(21,21).c_str());
         this->getKey_Ref< SGrid<real> >("cqplus").nZ = atof(strLine.substr(42,21).c_str());
         continue;
      }

      if (string::npos != strLine.find("-cqmin-"))
      {
         getline(ifFileStream,strLine);
         this->getKey_Ref< SGrid<real> >("cqmin").nX = atof(strLine.substr(0, 21).c_str());
         this->getKey_Ref< SGrid<real> >("cqmin").nY = atof(strLine.substr(21,21).c_str());
         this->getKey_Ref< SGrid<real> >("cqmin").nZ = atof(strLine.substr(42,21).c_str());
         continue;
      }

      if (string::npos != strLine.find("-cmin-"))
      {
         getline(ifFileStream,strLine);
         this->getKey_Ref< SGrid<real> >("cmin").nX = atof(strLine.substr(0, 21).c_str());
         this->getKey_Ref< SGrid<real> >("cmin").nY = atof(strLine.substr(21,21).c_str());
         this->getKey_Ref< SGrid<real> >("cmin").nZ = atof(strLine.substr(42,21).c_str());
         continue;
      }

      if (string::npos != strLine.find("-cmax-"))
      {
         getline(ifFileStream,strLine);
         this->getKey_Ref< SGrid<real> >("cmax").nX = atof(strLine.substr(0, 21).c_str());
         this->getKey_Ref< SGrid<real> >("cmax").nY = atof(strLine.substr(21,21).c_str());
         this->getKey_Ref< SGrid<real> >("cmax").nZ = atof(strLine.substr(42,21).c_str());
         continue;
      }

      if (string::npos != strLine.find("-ibnum-"))
      {
         getline(ifFileStream,strLine);
         this->getKey_Ref<integer>("ibnum") = atoi(strLine.c_str());
         continue;
      }

      if (string::npos != strLine.find("-iepsmp-"))
      {
         vector< SGrid<integer> >& iepsmp = this->getKey_Ref< vector< SGrid<integer> > >("iepsmp");

         if (0 != iepsmp.size()) vector< SGrid<integer> >().swap(iepsmp);

         const integer iGrid = this->getKey_Val<integer>("igrid");

         for (int i = 0; i < iGrid*iGrid*iGrid; i += 1)
         {
            getline(ifFileStream,strLine);

            SGrid<integer> grid;

            grid.nX = atoi(strLine.substr(0,6).c_str());
            grid.nY = atoi(strLine.substr(6,6).c_str());
            grid.nZ = atoi(strLine.substr(12,6).c_str());

            iepsmp.push_back(grid);
         }

         continue;
      }

      if (string::npos != strLine.find("-idebmap-"))
      {
         vector<bool>& idebmap = this->getKey_Ref< vector<bool> >("idebmap");

         if (0 != idebmap.size()) vector<bool>().swap(idebmap);

         const integer iGrid = this->getKey_Val<integer>("igrid");

         for (int i = 0; i < iGrid*iGrid*iGrid; i += 1)
         {
            getline(ifFileStream,strLine);

            if (string::npos != strLine.find("T"))
               idebmap.push_back(true);
            else if(string::npos != strLine.find("F"))
               idebmap.push_back(false);
         }

         continue;
      }

      if (string::npos != strLine.find("-ibgrd-"))
      {
         vector< SGrid<integer> >& ibgrd = this->getKey_Ref< vector< SGrid<integer> > >("ibgrd");

         if (0 != ibgrd.size()) vector< SGrid<integer> >().swap(ibgrd);

         for (int i = 0; i < this->getKey_constRef<integer>("ibnum"); i += 1)
         {
            getline(ifFileStream,strLine);

            SGrid<integer> grid;

            grid.nX = atoi(strLine.substr(0,6).c_str());
            grid.nY = atoi(strLine.substr(6,6).c_str());
            grid.nZ = atoi(strLine.substr(12,6).c_str());

            ibgrd.push_back(grid);
         }

         continue;
      }

      if (string::npos != strLine.find("-nqgrd-"))
      {
         getline(ifFileStream,strLine);
         this->getKey_Ref<integer>("nqgrd") = atoi(strLine.c_str());
         continue;
      }

      if (string::npos != strLine.find("-chrgv2-"))
      {
         vector<SGridValue<real> >& chrgv2 = this->getKey_Ref< vector<SGridValue<real> > >("chrgv2");

         if (0 != chrgv2.size()) vector<SGridValue<real> >().swap(chrgv2);

         for (int i = 0; i < this->getKey_Ref<integer>("nqgrd"); i += 1)
         {
            getline(ifFileStream,strLine);

            SGridValue<real> fgVal;

            fgVal.nGrid.nX = atof(strLine.substr(0, 21).c_str());
            fgVal.nGrid.nY = atof(strLine.substr(21,21).c_str());
            fgVal.nGrid.nZ = atof(strLine.substr(42,21).c_str());
            fgVal.nValue   = atof(strLine.substr(63,21).c_str());

            chrgv2.push_back(fgVal);
         }

         continue;
      }

      if (string::npos != strLine.find("-nqgrdtonqass-"))
      {
         vector<integer>& nqgrdtonqass = this->getKey_Ref< vector<integer> >("nqgrdtonqass");

         if (0 != nqgrdtonqass.size()) vector<integer>().swap(nqgrdtonqass);

         for (int i = 0; i < this->getKey_Ref<integer>("nqgrd"); i += 1)
         {
            getline(ifFileStream,strLine);

            integer iVal = atoi(strLine.c_str());

            nqgrdtonqass.push_back(iVal);
         }

         continue;
      }

      if (string::npos != strLine.find("-atmcrg-"))
      {
         vector< SGridValue<real> >& atmcrg = this->getKey_Ref< vector<SGridValue<real> > >("atmcrg");

         if (0 != atmcrg.size()) vector< SGridValue<real> >().swap(atmcrg);

         for (int i = 0; i < this->getKey_Ref<integer>("nqass"); i += 1)
         {
            getline(ifFileStream,strLine);

            SGridValue<real> fgVal;

            fgVal.nGrid.nX = atof(strLine.substr(0, 21).c_str());
            fgVal.nGrid.nY = atof(strLine.substr(21,21).c_str());
            fgVal.nGrid.nZ = atof(strLine.substr(42,21).c_str());
            fgVal.nValue   = atof(strLine.substr(63,21).c_str());

            atmcrg.push_back(fgVal);
         }

         continue;
      }

      if (string::npos != strLine.find("-chgpos-"))
      {
         vector< SGrid<real> >& chgpos = this->getKey_Ref< vector<SGrid<real> > >("chgpos");

         if (0 != chgpos.size()) vector< SGrid<real> >().swap(chgpos);

         for (int i = 0; i < this->getKey_Ref<integer>("nqass"); i += 1)
         {
            getline(ifFileStream,strLine);

            SGrid<real> fgCoord;

            fgCoord.nX = atof(strLine.substr(0, 21).c_str());
            fgCoord.nY = atof(strLine.substr(21,21).c_str());
            fgCoord.nZ = atof(strLine.substr(42,21).c_str());

            chgpos.push_back(fgCoord);
         }

         continue;
      }

      if (string::npos != strLine.find("-scspos-"))
      {
         vector< SGrid<real> >& scspos = this->getKey_Ref< vector<SGrid<real> > >("scspos");

         if (0 != scspos.size()) vector< SGrid<real> >().swap(scspos);

         for (int i = 0; i < this->getKey_Ref<integer>("ibnum"); i += 1)
         {
            getline(ifFileStream,strLine);

            SGrid<real> fgCoord;

            fgCoord.nX = atof(strLine.substr(0, 21).c_str());
            fgCoord.nY = atof(strLine.substr(21,21).c_str());
            fgCoord.nZ = atof(strLine.substr(42,21).c_str());

            scspos.push_back(fgCoord);
         }

         continue;
      }

      if (string::npos != strLine.find("-crgatn-"))
      {
         vector<integer>& crgatn = this->getKey_Ref< vector<integer> >("crgatn");

         if (0 != crgatn.size()) vector<integer>().swap(crgatn);

         for (int i = 0; i < this->getKey_Ref<integer>("nqass"); i += 1)
         {
            getline(ifFileStream,strLine);

            integer iVal = atoi(strLine.c_str());

            crgatn.push_back(iVal);
         }

         continue;
      }

      if (string::npos != strLine.find("-atsurf-"))
      {
         vector<integer>& atsurf = this->getKey_Ref< vector<integer> >("atsurf");

         if (0 != atsurf.size()) vector<integer>().swap(atsurf);

         for (int i = 0; i < this->getKey_Ref<integer>("ibnum"); i += 1)
         {
            getline(ifFileStream,strLine);

            integer iVal = atoi(strLine.c_str());

            atsurf.push_back(iVal);
         }

         continue;
      }

      if (string::npos != strLine.find("-atndx-"))
      {
         vector<integer>& atndx = this->getKey_Ref< vector<integer> >("atndx");

         if (0 != atndx.size()) vector<integer>().swap(atndx);

         for (int i = 0; i < this->getKey_Ref<integer>("ibnum"); i += 1)
         {
            getline(ifFileStream,strLine);

            integer iVal = atoi(strLine.c_str());

            atndx.push_back(iVal);
         }

         continue;
      }

      if (string::npos != strLine.find("-scsnor-"))
      {
         vector< SGrid<real> >& scsnor = this->getKey_Ref< vector<SGrid<real> > >("scsnor");

         if (0 != scsnor.size()) vector< SGrid<real> >().swap(scsnor);

         for (int i = 0; i < this->getKey_Ref<integer>("ibnum"); i += 1)
         {
            getline(ifFileStream,strLine);

            SGrid<real> fgCoord;

            fgCoord.nX = atof(strLine.substr(0, 21).c_str());
            fgCoord.nY = atof(strLine.substr(21,21).c_str());
            fgCoord.nZ = atof(strLine.substr(42,21).c_str());

            scsnor.push_back(fgCoord);
         }

         continue;
      }

      if (string::npos != strLine.find("-atmeps-"))
      {
         vector<real>& atmeps = this->getKey_Ref< vector<real> >("atmeps");

         if (0 != atmeps.size()) vector<real>().swap(atmeps);

         for (int i = 0; i < this->getKey_Ref<integer>("nqass"); i += 1)
         {
            getline(ifFileStream,strLine);

            real fVal = atof(strLine.c_str());

            atmeps.push_back(fVal);
         }

         continue;
      }

      //-------------------- set by Solver class ---------------------//

      if (string::npos != strLine.find("-icount2b-"))
      {
         getline(ifFileStream,strLine);
         this->getKey_Ref<integer>("icount2b") = atoi(strLine.c_str());
         continue;
      }

      if (string::npos != strLine.find("-icount1b-"))
      {
         getline(ifFileStream,strLine);
         this->getKey_Ref<integer>("icount1b") = atoi(strLine.c_str());
         continue;
      }

      if (string::npos != strLine.find("-gchrg-"))
      {
         vector<real>& gchrg = this->getKey_Ref< vector<real> >("gchrg");

         if (0 != gchrg.size()) vector<real>().swap(gchrg);

         for (int i = 0; i < this->getKey_Ref<integer>("icount1b"); i += 1)
         {
            getline(ifFileStream,strLine);

            real fVal = atof(strLine.c_str());

            gchrg.push_back(fVal);
         }

         continue;
      }

      if (string::npos != strLine.find("-gchrgp-"))
      {
         vector< SGrid<integer> >& gchrgp = this->getKey_Ref< vector< SGrid<integer> > >("gchrgp");

         if (0 != gchrgp.size()) vector< SGrid<integer> >().swap(gchrgp);

         for (int i = 0; i < this->getKey_Ref<integer>("icount1b"); i += 1)
         {
            getline(ifFileStream,strLine);

            SGrid<integer> grid;

            grid.nX = atoi(strLine.substr(0,6).c_str());
            grid.nY = atoi(strLine.substr(6,6).c_str());
            grid.nZ = atoi(strLine.substr(12,6).c_str());

            gchrgp.push_back(grid);
         }

         continue;
      }

      if (string::npos != strLine.find("-ibc-"))
      {
         getline(ifFileStream,strLine);
         this->getKey_Ref<integer>("ibc") = atoi(strLine.c_str());
         continue;
      }

      if (string::npos != strLine.find("-cgbp-"))
      {
         vector<SDoubleGridValue>& cgbp = this->getKey_Ref< vector<SDoubleGridValue> >("cgbp");

         if (0 != cgbp.size()) vector<SDoubleGridValue>().swap(cgbp);

         for (int i = 0; i < this->getKey_Ref<integer>("ibc"); i += 1)
         {
            getline(ifFileStream,strLine);

            SDoubleGridValue fDbVal;

            fDbVal.fgCoord.nX = atof(strLine.substr( 0,21).c_str());
            fDbVal.fgCoord.nY = atof(strLine.substr(21,21).c_str());
            fDbVal.fgCoord.nZ = atof(strLine.substr(42,21).c_str());
            fDbVal.fVal1      = atof(strLine.substr(63,21).c_str());
            fDbVal.fVal2      = atof(strLine.substr(84,21).c_str());

            cgbp.push_back(fDbVal);
         }

         continue;
      }

      if (string::npos != strLine.find("-phimap-"))
      {
         vector<real>& phimap = this->getKey_Ref< vector<real> >("phimap");

         if (0 != phimap.size()) vector<real>().swap(phimap);

         const integer iGrid = this->getKey_Val<integer>("igrid");

         for (int i = 0; i < iGrid*iGrid*iGrid; i += 1)
         {
            getline(ifFileStream,strLine);

            real fVal = atof(strLine.c_str());

            phimap.push_back(fVal);
         }

         continue;
      }

      //-------------------- set by Energy class ---------------------//
      if (string::npos != strLine.find("-schrg-"))
      {
         vector<real>& schrg = this->getKey_Ref< vector<real> >("schrg");

         if (0 != schrg.size()) vector<real>().swap(schrg);

         for (int i = 0; i < this->getKey_Val<integer>("ibnum"); i += 1)
         {
            getline(ifFileStream,strLine);

            real fVal = atof(strLine.c_str());

            schrg.push_back(fVal);
         }

         continue;
      }
   }

   ifFileStream.close();

}
