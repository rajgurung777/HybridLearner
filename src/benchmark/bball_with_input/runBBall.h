/*
 * runBBall.h
 *
 *  Created on: 10-Mar-2023
 *      Author: amit
 */

#ifndef BENCHMARK_BBALL_WITH_INPUT_RUNBBALL_H_
#define BENCHMARK_BBALL_WITH_INPUT_RUNBBALL_H_

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

void runBBall_with_input(std::unique_ptr<MATLABEngine> &ep,
		user_inputs::ptr user,
		std::list<struct timeseries_input> initial_CE_values,
		std::vector<double> output_variable_init_values,
		intermediateResult::ptr intermediate);


#endif /* BENCHMARK_BBALL_WITH_INPUT_RUNBBALL_H_ */
