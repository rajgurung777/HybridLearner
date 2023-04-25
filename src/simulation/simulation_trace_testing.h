/*
 * simulation_trace_testing.h
 *
 *  Created on: 21-Feb-2022
 *      Author: amit
 */

#ifndef SIMULATION_SIMULATION_TRACE_TESTING_H_
#define SIMULATION_SIMULATION_TRACE_TESTING_H_


#include "../commandLineParser/user_inputs.h"
#include "../utilities/polytope/polytope.h"
#include <boost/shared_ptr.hpp>
#include "simulation_datastruct.h"


class simulation_trace_testing {
	//struct simu_dataStruct violation_result; //data-structure containing the result of safety violation

public:
	typedef boost::shared_ptr<simulation_trace_testing> ptr;

	/*
	 * Returns True immediately, when the simulation traceFileName violates the input safety property
	 * The safety property is a simple string bounded constraints which can obtain a polytope along with lower and upper time bound (global time variable gt).
	 * Returns False when no violation found.
	 */
	bool safetyViolationCheck(user_inputs::ptr &user, std::string traceFileName, struct simu_dataStruct &violation_result);

};



#endif /* SIMULATION_SIMULATION_TRACE_TESTING_H_ */
