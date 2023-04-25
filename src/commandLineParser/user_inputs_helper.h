/*
 * user_inputs_helper.h
 *
 *  Created on: 21-Feb-2023
 *      Author: amit
 */


#include "../io_functions/data_structs.h"
#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include "parameters.h"
#include "commandLineParser.h"
#include "../simulation/simulation.h"


#ifndef COMMANDLINEPARSER_USER_INPUTS_HELPER_H_
#define COMMANDLINEPARSER_USER_INPUTS_HELPER_H_

class user_inputs_helper {

public:
	typedef boost::shared_ptr<user_inputs_helper> ptr;

	user_inputs_helper();
	virtual ~user_inputs_helper();



	void setVariable_CP_Size(std::list<struct control_points> &res, string variableName, double cp_size);
	void setVariableType(std::list<struct control_points> &res, string variableName, string variableType);
	std::list<struct control_points> getUserInputSignal_parameter(user_inputs::ptr user_Inputs);	//parameters::ptr params);

	std::list<struct timeseries_all_var> generate_input_signals(std::unique_ptr<MATLABEngine> &ep, parameters::ptr params);
};

#endif /* COMMANDLINEPARSER_USER_INPUTS_HELPER_H_ */
