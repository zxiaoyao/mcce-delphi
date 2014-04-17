#ifndef IO_DATATYPE_H
#define IO_DATATYPE_H

#include <string.h>

#include "../interface/environment.h"
#include "../misc/misc_grid.h"
#include "io_exceptions.h"

class CForce
{
   private:
      string strAtom;       // atom name          a6
      string strResidue;    // residue name       a3
      string strResidueNum; // residue number     a4
      string strChain;      // subunit name       a1
      real   fValue;        // atom radii/charge  f8.4
     
   public:
      CForce()
      {
         this->strAtom       = " ";
         this->strResidue    = " ";
         this->strResidueNum = " ";
         this->strChain      = " ";
         this->fValue        = 0.0;
      };

      void setAtom(const string strAtomIn) {this->strAtom = strAtomIn;}
      
      void setResidue(const string strResidueNameIn) {this->strResidue = strResidueNameIn;}
      
      void setResidueNum(const string strResidueNumIn) 
      {this->strResidueNum = strResidueNumIn;}
  
      void setChain(const string strChainIn) {this->strChain = strChainIn;} 
      
      void setValue(const real fValueIn) {this->fValue = fValueIn;}
  
      string getAtom() const {return this->strAtom;}
      
      string getResidue() const {return this->strResidue;}
      
      string getResidueNum() const {return this->strResidueNum;}
      
      string getChain() const {return this->strChain;}
      
      real getValue() const {return this->fValue;}
};


class CAtomPdb // delphi_pdb_file_record
{
   private:
      real fRadius;
      real fCharge;
      SGrid<real> gPose;
      string strAtInf;

   public:
      CAtomPdb()
      {
         this->fRadius  = 0.0;
         this->fCharge  = 0.0;
         this->gPose.nX = 0.0; this->gPose.nY = 0.0; this->gPose.nZ = 0.0;
         this->strAtInf = " ";
      }; 

      void setRadius(const real fRadiusIn) {this->fRadius = fRadiusIn;}
      
      void setCharge(const real fChargeIn) {this->fCharge = fChargeIn;}
      
      void setPose(const SGrid<real> gPoseIn) {this->gPose = gPoseIn;}
      
      void setPose(const real fX, const real fY, const real fZ) {this->gPose.nX = fX; this->gPose.nY = fY; this->gPose.nZ = fZ;}
      
      void setAtInf(const string strAtInfIn) {this->strAtInf = strAtInfIn;}
      
      real getRadius() const {return this->fRadius;}
      
      real getCharge() const {return this->fCharge;}
      
      SGrid<real> getPose() const {return this->gPose;}
      
      string getAtInf() const {return this->strAtInf;} 
      
};


#endif // IO_DATATYPE_H
