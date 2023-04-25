/*
 * model_translator.h
 *
 *  Created on: 21-Feb-2023
 *      Author: amit
 */

#include "../../simulinkModelling/simulinkModelConstructor.h"
#include "../../modelParser/modelParser.h"
#include "../../commandLineParser/parameters.h"
#include "../../utilities/linux_utilities.h"
#include "../../utilities/intermediateResult.h"
#include "../../commandLineParser/user_inputs_helper.h"
#include "../../io_functions/summary.h"


#ifndef CORE_ENGINE_MODEL_TRANSLATOR_MODEL_TRANSLATOR_H_
#define CORE_ENGINE_MODEL_TRANSLATOR_MODEL_TRANSLATOR_H_

using namespace std;
using namespace matlab::engine;

void model_translator(parameters::ptr params, std::unique_ptr<MATLABEngine> &ep, summary::ptr &report);

void run_script_generator(simulinkModelConstructor::ptr &model, parameters::ptr params, std::unique_ptr<MATLABEngine> &ep);



#endif /* CORE_ENGINE_MODEL_TRANSLATOR_MODEL_TRANSLATOR_H_ */
