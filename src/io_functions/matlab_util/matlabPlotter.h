/*
 * matlabPlotter.h
 *
 *  Created on: 21-Dec-2021
 *      Author: amit
 */

#ifndef IO_FUNCTIONS_MATLAB_UTIL_MATLABPLOTTER_H_
#define IO_FUNCTIONS_MATLAB_UTIL_MATLABPLOTTER_H_


# include <string>
# include "../../utilities/polytope/polytope.h"
#include "MatlabEngine.hpp"
#include "../../utilities/intermediateResult.h"

using namespace matlab::engine;

//Calls Matlab to convert H-Polytope or constraints represenation of Polytope into V-Polytope or vertices representation of Polytope.
void printPolytope2File(std::unique_ptr<MATLABEngine> &ep,
		intermediateResult::ptr intermediate, user_inputs::ptr users,
		polytope::ptr poly, std::string fileName);



#endif /* IO_FUNCTIONS_MATLAB_UTIL_MATLABPLOTTER_H_ */
