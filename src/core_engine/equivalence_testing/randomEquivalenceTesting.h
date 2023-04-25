/*
 * randomEquivalenceTesting.h
 *
 *  Created on: 22-Feb-2023
 *      Author: amit
 *      This is a concrete Equivalence Testing Class implementing a simple approach of random generation of input signals.
 *      The input signals are feed in the two simulink models to generate output traces.
 *      The traces are then compared for equivalence using one of the following methods:
 *      	(1) Euclidean distances between points (for the same time values) lies within supplied epsilon value.
 *      	(2) May also try DTW distances between the two traces for some given min-distance and/or correlation value.
 */

#include "equivalence_testing.h"
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <list>
#include "../../commandLineParser/parameters.h"
#include "../../io_functions/summary.h"
#include "MatlabEngine.hpp"
#include "../simulation/simulation_utilities.h"
#include "equivalence_test_utils.h"


#ifndef CORE_ENGINE_EQUIVALENCE_TESTING_RANDOMEQUIVALENCETESTING_H_
#define CORE_ENGINE_EQUIVALENCE_TESTING_RANDOMEQUIVALENCETESTING_H_


using namespace std;
using namespace matlab::engine;

class randomEquivalenceTesting: public equivalence_testing {
public:
	typedef boost::shared_ptr<randomEquivalenceTesting> ptr;

	randomEquivalenceTesting();
	virtual ~randomEquivalenceTesting();

	bool execute_random_equivalence_test(parameters::ptr params, std::unique_ptr<MATLABEngine> &ep, summary::ptr &report);

};

#endif /* CORE_ENGINE_EQUIVALENCE_TESTING_RANDOMEQUIVALENCETESTING_H_ */
