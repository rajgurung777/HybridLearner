/*
 * runOscillator.h
 *
 *  Created on: 05-Oct-2021
 *      Author: amit
 */

#ifndef BENCHMARK_OSCILLATOR_RUNOSCILLATOR_H_
#define BENCHMARK_OSCILLATOR_RUNOSCILLATOR_H_


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

void runOscillator(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr user, const std::vector<double> initial_CE_values, intermediateResult::ptr intermediate);


#endif /* BENCHMARK_OSCILLATOR_RUNOSCILLATOR_H_ */
