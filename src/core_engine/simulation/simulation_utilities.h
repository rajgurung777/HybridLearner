/*
 * simulation_utilities.h
 *
 *  Created on: 28-Jul-2022
 *      Author: amit
 */

#include <list>
#include <vector>
#include <string>
#include "MatlabEngine.hpp"
#include "../../commandLineParser/user_inputs.h"
#include "../../utilities/intermediateResult.h"
#include "../../hybridautomata/hybridAutomata.h"
#include "../../commandLineParser/parameters.h"

#include "../../commandLineParser/user_inputs_helper.h"
#include "../../simulinkModelling/simulinkModelConstructor.h"
#include "../../io_functions/summary.h"
#include "../../io_functions/data_structs.h"
#include <boost/timer/timer.hpp>
#include "../learn_ha/model_setup.h"
#include "../../utilities/linux_utilities.h"
#include "../../utilities/myRandomNumberGenerator.h"
#include "../../utilities/polytope/polytope.h"
#include "../../simulation/simulation.h"

#include "../../utilities/string_operations.h"


#ifndef CORE_ENGINE_SIMULATION_SIMULATION_UTILITIES_H_
#define CORE_ENGINE_SIMULATION_SIMULATION_UTILITIES_H_



using namespace std;
using namespace matlab::engine;

//simulate_model(ep, userInputs, init_point, intermediate);
void simu_model_file(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr &userInput,
		std::list<struct timeseries_input> initial_CE_values, std::vector<double> &initial_output_values,
		std::string script_filename, std::string output_filename, intermediateResult::ptr &inter, hybridAutomata::ptr &ha);


void simulate_learned_model_from_learn_ha_loop(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr &user, std::list<struct timeseries_input> initial_CE_values,
		std::vector<double> &initial_output_values, std::string script_filename,
		std::string output_filename, intermediateResult::ptr &intermediate, hybridAutomata::ptr &ha,  model_setup::ptr la_setup);


void simulate_original_model_from_learn_ha_loop(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr &user, std::list<struct timeseries_input> initial_CE_values,
		std::vector<double> &initial_output_values, std::string script_filename,
		std::string output_filename, intermediateResult::ptr &intermediate, hybridAutomata::ptr &ha,  model_setup::ptr la_setup);

void generate_input_information(std::list<struct timeseries_all_var> &initial_simulation_timeSeriesData_ret,
		std::list< std::vector<double> > &initial_output_values_ret, parameters::ptr &params, std::unique_ptr<MATLABEngine> &ep, summary::ptr &report);


void generate_simulation_traces(std::list<struct timeseries_all_var> &initial_simulation_timeSeriesData, std::list<std::vector<double> > &initial_output_values,
		parameters::ptr params, std::unique_ptr<MATLABEngine> &ep);


#endif /* CORE_ENGINE_SIMULATION_SIMULATION_UTILITIES_H_ */
