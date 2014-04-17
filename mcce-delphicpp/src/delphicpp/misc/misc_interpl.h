#ifndef INTERPL_H
#define INTERPL_H

#include <vector>
#include <math.h> /* floor */

#include "../interface/environment.h"
#include "../interface/exceptions.h"
#include "misc_grid.h"

using namespace std;

extern real interpl(const integer& ieExtrema, real *** fMap, const SGrid<real>& gPoint);

extern real boolinterpl(const integer& igMaxGrid, const vector<bool>& prgbMap, const SGrid<real>& gPoint);

#endif // INTERPL_H
