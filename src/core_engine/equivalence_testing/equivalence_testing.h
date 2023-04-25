/*
 * equivalence_testing.h
 *
 *  Created on: 22-Feb-2023
 *      Author: amit
 */

#include <string>
#include "../../utilities/linux_utilities.h"
#include "../../utilities/intermediateResult.h"
#include "../../commandLineParser/parameters.h"
#include "../../io_functions/summary.h"
#include "../../hybridautomata/hybridAutomata.h"
#include "../../simulinkModelling/simulinkModelConstructor.h"

#ifndef CORE_ENGINE_EQUIVALENCE_TESTING_EQUIVALENCE_TESTING_H_
#define CORE_ENGINE_EQUIVALENCE_TESTING_EQUIVALENCE_TESTING_H_


using namespace std;
using namespace matlab::engine;

class equivalence_testing {
public:
	equivalence_testing();
	virtual ~equivalence_testing();

	void generate_run_script_file(std::string model_filename, parameters::ptr params);
	//void generate_script_files(parameters::ptr params);

	virtual bool execute_random_equivalence_test(parameters::ptr params, std::unique_ptr<MATLABEngine> &ep, summary::ptr &report) = 0;
	//This pure virtual function makes this class an abstract class.
};

#endif /* CORE_ENGINE_EQUIVALENCE_TESTING_EQUIVALENCE_TESTING_H_ */
