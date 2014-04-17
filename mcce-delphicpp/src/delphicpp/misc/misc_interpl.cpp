/* interpolates the potential at any point inside a cubical volume using the potential 
 * values at the 8 vertices by means of a trilinear function:
 *
 *	   W = A1.XYZ + A2.XY + A3.XZ + A4.YZ + A5.X +A6.Y + A7.Z + A8
 *
 * where Ai coefficients are linear combinations of Wi at the cube corners
 */

#include "misc_interpl.h"

//-----------------------------------------------------------------------//
class CPointOutBox : public CWarning
{
   public:
      CPointOutBox(const SGrid<real> & gPoint, const integer& igMaxGrid)
      {
         cerr << "PAY ATTENSION, POINT OUT OF THE CUBE!! \n";
         cerr << "VALUES: " << gPoint.nX << " " << gPoint.nY << " " << gPoint.nZ << " GRID: " << igMaxGrid << endl;
         cerr << "\t VALUE AT THIS POINT IS SET = 0." << endl;
      }
};

//-----------------------------------------------------------------------//
real interpl(const integer& igMaxGrid, real *** prgfMap, const SGrid<real>& gPoint)
{
   real fInterpl = 0.0; // return interploation value

   SGrid<real> fgMaxGrid = {(real)(igMaxGrid),(real)(igMaxGrid),(real)(igMaxGrid)};
       
   // return 0.0 if outside grid
   if (optORLT(gPoint,0.0) || optORGT(gPoint,fgMaxGrid)) 
   {
      CPointOutBox waring(gPoint,igMaxGrid);
      return fInterpl = 0.0;
   }

   // find lower left bottom grid point
   SGrid<integer> iFloor = {(integer)floor(gPoint.nX),(integer)floor(gPoint.nY),(integer)floor(gPoint.nZ)}; //nx,ny,nz
   
   SGrid<integer> iCeiling = iFloor+1; //nx1,ny1,nz1
   if (iCeiling.nX > igMaxGrid) iCeiling.nX = iFloor.nX;
   if (iCeiling.nY > igMaxGrid) iCeiling.nY = iFloor.nY;
   if (iCeiling.nZ > igMaxGrid) iCeiling.nZ = iFloor.nZ;
   
   // calculate cube coordinates of point
   SGrid<real> fFloor = {(real)iFloor.nX,(real)iFloor.nY,(real)iFloor.nZ};
   fFloor = gPoint - fFloor; // xgr,ygr,zgr

   // calculate coefficients of trilinear function
   real a8 = prgfMap[iFloor.nX][iFloor.nY][iFloor.nZ],
        a7 = prgfMap[iFloor.nX][iFloor.nY][iCeiling.nZ]-a8,
        a6 = prgfMap[iFloor.nX][iCeiling.nZ][iFloor.nZ]-a8,
        a5 = prgfMap[iCeiling.nX][iFloor.nZ][iFloor.nZ]-a8,
        a4 = prgfMap[iFloor.nX][iCeiling.nZ][iCeiling.nZ]-a8-a7-a6,
        a3 = prgfMap[iCeiling.nX][iFloor.nZ][iCeiling.nZ]-a8-a7-a5,
        a2 = prgfMap[iCeiling.nX][iCeiling.nZ][iFloor.nZ]-a8-a6-a5,
        a1 = prgfMap[iCeiling.nX][iCeiling.nZ][iCeiling.nZ]-a8-a7-a6-a5-a4-a3-a2;
        
   // determine value of phi     
   fInterpl = a1*fFloor.nX*fFloor.nY*fFloor.nZ + a2*fFloor.nX*fFloor.nY + a3*fFloor.nX*fFloor.nZ + a4*fFloor.nY*fFloor.nZ +
              a5*fFloor.nX + a6*fFloor.nY + a7*fFloor.nZ + a8;

   return fInterpl;
}

//-----------------------------------------------------------------------//
real boolinterpl(const integer& igMaxGrid, const vector<bool>& prgbMap, const SGrid<real>& gPoint)
{
   real fInterpl = 0.0; // return interploation value

   SGrid<real> fgMaxGrid = {(real)(igMaxGrid),(real)(igMaxGrid),(real)(igMaxGrid)};

   // return 0.0 if outside grid
   if (optORLT(gPoint,0.0) || optORGT(gPoint,fgMaxGrid))
   {
      CPointOutBox waring(gPoint,igMaxGrid);
      return fInterpl = 0.0;
   }

   // find lower left bottom grid point
   SGrid<integer> iFloor = {(integer)floor(gPoint.nX),(integer)floor(gPoint.nY),(integer)floor(gPoint.nZ)}; //nx,ny,nz

   SGrid<integer> iCeiling = iFloor+1; //nx1,ny1,nz1
   if (iCeiling.nX > igMaxGrid) iCeiling.nX = iFloor.nX;
   if (iCeiling.nY > igMaxGrid) iCeiling.nY = iFloor.nY;
   if (iCeiling.nZ > igMaxGrid) iCeiling.nZ = iFloor.nZ;

   // calculate cube coordinates of point
   SGrid<real> fFloor = {(real)iFloor.nX,(real)iFloor.nY,(real)iFloor.nZ};
   fFloor = gPoint - fFloor; // xgr,ygr,zgr

   // convert logical idebmap to real
   real debm[8];
   integer nx  = iFloor.nX,   ny  = iFloor.nY,   nz  = iFloor.nZ;
   integer nx1 = iCeiling.nX, ny1 = iCeiling.nY, nz1 = iCeiling.nZ;

   integer nw;

   nw = nz*igMaxGrid*igMaxGrid+ny*igMaxGrid+nx;
   if (prgbMap[nw]) debm[0] = 1.0;

   nw = nz1*igMaxGrid*igMaxGrid+ny*igMaxGrid+nx;
   if (prgbMap[nw]) debm[1] = 1.0;

   nw = nz*igMaxGrid*igMaxGrid+ny1*igMaxGrid+nx;
   if (prgbMap[nw]) debm[2] = 1.0;

   nw = nz*igMaxGrid*igMaxGrid+ny*igMaxGrid+nx1;
   if (prgbMap[nw]) debm[3] = 1.0;

   nw = nz1*igMaxGrid*igMaxGrid+ny1*igMaxGrid+nx;
   if (prgbMap[nw]) debm[4] = 1.0;

   nw = nz1*igMaxGrid*igMaxGrid+ny*igMaxGrid+nx1;
   if (prgbMap[nw]) debm[5] = 1.0;

   nw = nz*igMaxGrid*igMaxGrid+ny1*igMaxGrid+nx1;
   if (prgbMap[nw]) debm[6] = 1.0;

   nw = nz1*igMaxGrid*igMaxGrid+ny1*igMaxGrid+nx1;
   if (prgbMap[nw]) debm[7] = 1.0;

   // calculate coefficients of trilinear function
   real a8 = debm[0],
        a7 = debm[1]-a8,
        a6 = debm[2]-a8,
        a5 = debm[3]-a8,
        a4 = debm[4]-a8-a7-a6,
        a3 = debm[5]-a8-a7-a5,
        a2 = debm[6]-a8-a6-a5,
        a1 = debm[7]-a8-a7-a6-a5-a4-a3-a2;

   // determine value of phi
   fInterpl = a1*fFloor.nX*fFloor.nY*fFloor.nZ + a2*fFloor.nX*fFloor.nY + a3*fFloor.nX*fFloor.nZ + a4*fFloor.nY*fFloor.nZ +
              a5*fFloor.nX + a6*fFloor.nY + a7*fFloor.nZ + a8;

   return fInterpl;
}




























