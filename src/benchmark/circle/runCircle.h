/*
 * runCircle.h
 *
 *  Created on: 05-Oct-2021
 *      Author: amit
 */

#ifndef BENCHMARK_CIRCLE_RUNCIRCLE_H_
#define BENCHMARK_CIRCLE_RUNCIRCLE_H_

//#include "MatlabDataArray.hpp"
#include "MatlabEngine.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "string.h"
#include <string>
//#include "engine.h"
#include "../../commandLineParser/user_inputs.h"
#include "../../utilities/intermediateResult.h"

using namespace std;
using namespace matlab::engine;

int runCircle(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr& user, std::vector<double> initial_CE_values, intermediateResult::ptr &intermediate);



#endif /* BENCHMARK_CIRCLE_RUNCIRCLE_H_ */
