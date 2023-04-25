/*
 * learn_ha_loop.h
 *
 *  Created on: 22-Feb-2023
 *      Author: amit
 */


#include <iostream>
#include <list>
#include <vector>
#include "model_setup.h"
#include <boost/timer/timer.hpp>
#include "../../modelParser/modelParser.h"
#include "../../commandLineParser/parameters.h"
#include "../../io_functions/summary.h"
#include "../../utilities/linux_utilities.h"
#include "../../utilities/intermediateResult.h"
#include "../../simulinkModelling/simulinkModelConstructor.h"
#include "MatlabEngine.hpp"
#include "../simulation/simulation_utilities.h"
#include "../../io_functions/data_structs.h"
#include "../../learningHA/learnHA_caller.h"
#include "../equivalence_testing/equivalence_test_utils.h"

#ifndef CORE_ENGINE_LEARN_HA_LEARN_HA_LOOP_H_
#define CORE_ENGINE_LEARN_HA_LEARN_HA_LOOP_H_

using namespace std;
using namespace matlab::engine;

void execute_learn_ha_loop(parameters::ptr params, summary::ptr &report, std::unique_ptr<MATLABEngine> &ep);

void initial_processing_for_InputFileName(parameters::ptr params);

void generate_initial_traces_for_learn_ha_loop(std::list<struct timeseries_all_var> &list_input_variable_values,
		std::list<std::vector<double> > &list_output_variable_values, parameters::ptr params, std::unique_ptr<MATLABEngine> &ep, summary::ptr &report);

void initial_setup_for_learning(parameters::ptr params);

void updateTraceFile(unsigned int iteration, std::vector<double> CE, list<struct timeseries_input> CE_trace, parameters::ptr params);

void call_LearnHA(parameters::ptr params, summary::ptr &report);

void constructModel(unsigned int count, parameters::ptr params, std::unique_ptr<MATLABEngine> &ep);

bool equivalenceTesting_for_learn_ha_loop(unsigned int iteration, model_setup::ptr la_setup, std::list<struct timeseries_all_var> &list_inputs,
		std::list<std::vector<double> > &list_outputs, std::vector<double> &CE_output_var, std::list<struct timeseries_input> &CE_input_var, parameters::ptr params, std::unique_ptr<MATLABEngine> &ep);

void generate_simulation_traces_original_model_to_learn(std::list<struct timeseries_all_var> &initial_simulation_timeSeriesData,
		std::list<std::vector<double> > &initial_output_values, parameters::ptr params, std::unique_ptr<MATLABEngine> &ep, summary::ptr &report);

#endif /* CORE_ENGINE_LEARN_HA_LEARN_HA_LOOP_H_ */
