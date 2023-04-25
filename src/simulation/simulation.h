/*
 * simulation.h
 *
 *  Created on: 05-Oct-2021
 *      Author: amit
 */

#ifndef SIMULATION_SIMULATION_H_
#define SIMULATION_SIMULATION_H_

//#include "MatlabDataArray.hpp"
#include "MatlabEngine.hpp"

#include <vector>
#include "../commandLineParser/user_inputs.h"
#include "../utilities/polytope/polytope.h"
//#include "engine.h"
#include "../utilities/hyperbox/hyperbox.h"
#include "../utilities/math/randomGenerator.h"
#include "../utilities/intermediateResult.h"
#include "simulation_trace_testing.h"
#include "../utilities/myRandomNumberGenerator.h"


#include "../benchmark/circle/runCircle.h"
#include "../benchmark/oscillator/runOscillator.h"
#include "../benchmark/shared_gas_burner/runSharedGasBurner.h"
#include "../benchmark/nav_inst1/runNav_inst1.h"
#include "../benchmark/AFC/runAFC.h"
#include "../benchmark/AT/runAT.h"
#include "../benchmark/bball_with_input/runBBall.h"



using namespace std;
using namespace matlab::engine;

void simulate_model(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr &user, std::vector<double> initial_CE_values, intermediateResult::ptr &intermediate);
//void simulate(Engine *ep, user_inputs::ptr &user, std::list < std::vector<double> > list_initial_points, intermediateResult::ptr& intermediate);
//void simulate_model(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr& userInput, std::list<struct timeseries_input> initial_CE_values, intermediateResult::ptr& inter);
void simulate_model(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr &userInput,
		std::list<struct timeseries_input> initial_CE_values, std::vector<double> output_variable_init_values,
		intermediateResult::ptr &inter);


void simulate(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr &user, std::list < std::vector<double> > list_initial_points, intermediateResult::ptr& intermediate);
void simulate(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr &user, std::list<struct timeseries_all_var> input_for_simulation,
		std::list<std::vector<double>> output_for_simulation, intermediateResult::ptr &intermediate, struct simu_dataStruct &violation_result);


bool safetyCheck(user_inputs::ptr &user, double &violation_TimeHorizon);

bool variableBoundCheck(string varName, double varValue, std::list<struct variable_bounds> list_VarBounds);

const std::string getSimulationOutputFileName(unsigned int model, const std::string &toolRootPath);


/*
 * Generate random simulation points from a Polytope (Note: polytope should obey the
 * formation rule of a hyberbox. Each dimension should have both the upper and lower bounds. Ax <= b where b is the bound.
 */

std::list< std::vector<double> > getInternalPoints(polytope::ptr &poly, unsigned int n, myRandomNumberGenerator::ptr &randomGenObj);


std::list<std::list<struct control_points>> getInternalControlPoints(polytope::ptr &poly, unsigned int n_simulations, list<struct control_points> list_var_cps, myRandomNumberGenerator::ptr &randomGenObj);

std::list<std::list<struct control_points>> getInternalControlPoints_PureRandom(polytope::ptr &poly, unsigned int n_simulations, list<struct control_points> list_var_cps);

void fixed_step_signal(double th, std::vector<double> cps, std::vector<double> &time_vector, std::vector<double> &data_vector);


void linear_signal(double th, std::vector<double> cps, std::vector<double> &time_vector, std::vector<double> &data_vector);

void spline_signal(std::unique_ptr<MATLABEngine> &ep, double th, std::vector<double> cps, std::vector<double> &time_vector, std::vector<double> &data_vector);


void sine_wave_signal(double timeHorizon, double amplitude, double zero_offset, std::vector<double> &time_vector, std::vector<double> &data_vector);


#endif /* SIMULATION_SIMULATION_H_ */
