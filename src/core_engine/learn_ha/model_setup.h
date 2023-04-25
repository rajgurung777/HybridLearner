/*
 * learn_ha.h
 *
 *  Created on: 18-Aug-2022
 *      Author: amit
 *
 *	This class is used in engine = "learn-ha-loop"
 *
 *  This class may have redundant functions with minor differences.
 *  This is required for learned model files having different variable names from original model
 *  In our learned model we assume variables as x0, x1 and so on. x0:input, x1:output, etc. Whereas original model may have u:input and x:output, v:output.
 */

#ifndef CORE_ENGINE_LEARN_HA_MODEL_SETUP_H_
#define CORE_ENGINE_LEARN_HA_MODEL_SETUP_H_

#include <list>
#include <string>
#include <boost/shared_ptr.hpp>
#include "../../commandLineParser/user_inputs.h"
#include "../../commandLineParser/user_inputs_helper.h"
#include "../../hybridautomata/hybridAutomata.h"
#include "../../io_functions/data_structs.h"

using namespace std;

/*
 * Prepares variables renaming for running the learned model
 * Tasks:
 * 1) replace ha->mapping of all variables' name for eg.,  --variable-category "u:input, x:output, v:output" should be mapped to "x0:input, x1:output, x2:output"
 * 2) Accordingly, replace user->list_inputVariables and user->list_outputVariables.
 * 3) "initial-value" input string to be replaced with learned variable names for eg., --initial-value "u>=-9.81 & u<=-9.81 & x>=10.2 & x<=10.9 & v>=15 & v<=16"
 *    to be replaced with --initial-value "x0>=-9.81 & x0<=-9.81 & x1>=10.2 & x1<=10.9 & x2>=15 & x2<=16"
 *
 * 4) input-signal-type for eg., "u=fixed-step" should also be mapped to "x0=fixed-step" and
 * 5) numberOf-control-points for eg., "u=1" should also be mapped to "x0=1" and
 */
class model_setup {
	//backup original user's input: Todo: this list can be increased as and when required
	std::string original_variable_category;	//user's input for each variable category (input or output category)
	std::string original_input_signal_type; //syntax of input string="x0=fixed-step & x1=fixed-linear"   var-step can be thought later
	std::string original_numberOf_control_points; //syntax of input string="x0=2 & x1=3"
	std::string original_initial_set;	// initial-value (bounded) for each variable from where the simulation starts


	std::string new_variable_category;	//new learned setup
	std::string new_input_signal_type;	//new learned setup
	std::string new_numberOf_control_points;	//new learned setup
	std::string new_initial_set;	//new learned setup

	std::list<struct variable_mapping> userVariable_Mapping;	// used in a couple of places

	hybridAutomata::ptr ha_original_copy;	//**THIS WILL NOT BE ABLE TO RETAIN THE COPY we are using pointers.
	user_inputs::ptr userInputs_original_copy;	//**THIS WILL NOT BE ABLE TO RETAIN THE COPY we are using pointers.

	size_t replaceAll(std::string& str, size_t start_pos, const std::string& from, const std::string& to);	//Not used
	bool replace(std::string& str, const std::string& from, const std::string& to);	//Not used

	void getVariableOperatorValue(std::string input_constraints, std::string &orig_varName, std::string &op, std::string &val);
	void assign_learnVariable_to_HA(hybridAutomata::ptr ha, user_inputs::ptr userInputs);

public:
	typedef boost::shared_ptr<model_setup> ptr;

	model_setup (){
		;
	}

	model_setup (hybridAutomata::ptr ha, user_inputs::ptr userInputs);

	model_setup (std::string variable_category, std::string input_signal_type, std::string numberOf_control_points, std::string initial_set );


	// Destructor
	virtual ~model_setup (){
		;
	}

	std::string getEquivalentLearnedVariableName(std::list<struct variable_mapping> &userInputOutputData, std::string orig_varName);

	// Replacing tasks from original input to fix for the Learned model variables
	void setup_for_learned_model(hybridAutomata::ptr ha, user_inputs::ptr userInputs);


	// reverting back to original user's input
	void setup_for_original_model(hybridAutomata::ptr ha, user_inputs::ptr userInputs);

	const std::string& getInitialSet() const;
	void setInitialSet(const std::string &initialSet);
	const std::string& getInputSignalType() const;
	void setInputSignalType(const std::string &inputSignalType);
	const std::string& getNumberOfControlPoints() const;
	void setNumberOfControlPoints(const std::string &numberOfControlPoints);
	const std::list<std::string>& getListInputVariables() const;
	void setListInputVariables(
			const std::list<std::string> &listInputVariables);
	const std::list<std::string>& getListOutputVariables() const;
	void setListOutputVariables(
			const std::list<std::string> &listOutputVariables);
	const std::string& getVariableCategory() const;
	void setVariableCategory(const std::string &variableCategory);
	const hybridAutomata::ptr& getHaOriginalCopy() const;
	void setHaOriginalCopy(const hybridAutomata::ptr &haOriginalCopy);
	const user_inputs::ptr& getUserInputsOriginalCopy() const;
	void setUserInputsOriginalCopy(
			const user_inputs::ptr &userInputsOriginalCopy);
	const std::list<struct variable_mapping>& getUserVariableMapping() const;
	void setUserVariableMapping(
			const std::list<struct variable_mapping> &userVariableMapping);
};



#endif /* CORE_ENGINE_LEARN_HA_MODEL_SETUP_H_ */
