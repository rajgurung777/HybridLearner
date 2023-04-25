/*
 * runAFC.h
 *
 *  Created on: 07-Jan-2022
 *      Author: amit
 */

#ifndef BENCHMARK_AFC_RUNAFC_H_
#define BENCHMARK_AFC_RUNAFC_H_



//#include "MatlabDataArray.hpp"
#include "MatlabEngine.hpp"


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "string.h"
#include <string>

#include "../../commandLineParser/user_inputs.h"
#include "../../utilities/intermediateResult.h"
#include "../../io_functions/data_structs.h"

using namespace std;
using namespace matlab::engine;

//void runAFC(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr user, const std::vector<double> initial_CE_values, intermediateResult::ptr intermediate);
void runAFC(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr user, std::list<struct timeseries_input> initial_CE_values, intermediateResult::ptr intermediate);




#endif /* BENCHMARK_AFC_RUNAFC_H_ */
