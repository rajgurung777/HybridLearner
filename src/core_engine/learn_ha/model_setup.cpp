/*
 * learn_ha.cpp
 *
 *  Created on: 19-Aug-2022
 *      Author: amit
 */

#include <core_engine/learn_ha/model_setup.h>

model_setup::model_setup (std::string variable_category, std::string input_signal_type, std::string numberOf_control_points, std::string initial_set){

	this->original_variable_category = variable_category;
	this->original_input_signal_type = input_signal_type;
	this->original_numberOf_control_points = numberOf_control_points;
	this->original_initial_set = initial_set;
}


// Replacing tasks from original input to fix for the Learned model variables
model_setup::model_setup(hybridAutomata::ptr ha, user_inputs::ptr userInputs){

	hybridAutomata::ptr ha_copy = hybridAutomata::ptr( new hybridAutomata());
	ha_copy = ha;
	this->ha_original_copy = ha_copy;

	user_inputs::ptr user_copy = user_inputs::ptr( new user_inputs());
	user_copy = userInputs;
	this->userInputs_original_copy = user_copy;



	//Original user's input backed-up
	this->original_variable_category = userInputs->getVariableCategory();
	this->original_input_signal_type = userInputs->getInputSignalType();
	this->original_numberOf_control_points = userInputs->getNumberOfControlPoints();
	this->original_initial_set = userInputs->getInitialSet_userInput();


	// -------------- Creating variable-category for learned model -----------------------
	unsigned int input_variable_size = userInputs->getListInputVariables().size();
	unsigned int output_variable_size = userInputs->getListOutputVariables().size();

	std::list<struct variable_mapping> userInputOutputData;

	std::list<std::string> inputVarList =  userInputs->getListInputVariables();
	std::string variableName, newVariableCategory="";
	unsigned int index=0;
	for (std::list<std::string>::iterator orig_it = inputVarList.begin(); orig_it != inputVarList.end(); orig_it++) {	//Assuming order is maintained by the user
		struct variable_mapping userDataValue;

		variableName = "x";
		variableName.append(to_string(index));

		newVariableCategory.append(variableName);
		newVariableCategory.append(":input");
		newVariableCategory.append(", ");		//at least one output variable will be present

		userDataValue.learned_var_name = variableName;
		userDataValue.original_var_name = (*orig_it);
		userDataValue.var_index = index;
		//userDataValue.var_type =
		userInputOutputData.push_back(userDataValue);

		index++;
	}
	std::list<std::string> outputVarList =  userInputs->getListOutputVariables();
	index = input_variable_size;
	unsigned int i_val=0;
	for (std::list<std::string>::iterator orig_it = outputVarList.begin(); orig_it != outputVarList.end(); orig_it++) {
		struct variable_mapping userDataValue;

		variableName = "x";
		variableName.append(to_string(index));

		newVariableCategory.append(variableName);
		newVariableCategory.append(":output");
		if (i_val != (output_variable_size - 1)) {
			newVariableCategory.append(", ");
		}

		userDataValue.learned_var_name = variableName;
		userDataValue.original_var_name = (*orig_it);
		userDataValue.var_index = index;
		//userDataValue.var_type =
		userInputOutputData.push_back(userDataValue);
		index++;  i_val++;
	}
	// ----------------Creating variable-category Done----------------------
	//std::cout <<"New variable mapping Done!!" << std::endl;

	// ----------------Creating new_input_signal_type and new_numberOfCPs Done----------------------
	list<string> list_original_input_variable = userInputs->getListInputVariables();
	list<string> list_original_output_variable = userInputs->getListOutputVariables();
	string new_input_signal_type = "";	//this->original_input_signal_type;
	string new_numberOfCPs = "";	 //syntax of input string="x0=2 & x1=3"


	user_inputs_helper::ptr user_inputs_helper_object = user_inputs_helper::ptr(new user_inputs_helper());
//	std::list<struct control_points> userData = userInputs->getUserInputSignal_parameter(userInputs);
	std::list<struct control_points> userData = user_inputs_helper_object->getUserInputSignal_parameter(userInputs);
	list<string>::iterator input_it=list_original_input_variable.begin();
	index = 0;
	unsigned int list_inputVar_size = list_original_input_variable.size();
	for (std::list<struct control_points>::iterator it=userData.begin(); it != userData.end(); it++, input_it++) {	//assume order is maintained by the user
		struct control_points varData = (*it);
		string orig_varName = (*input_it);
		string new_varName = "x";
		new_varName.append(to_string(index));
		cout << "VarName=" << varData.var_name << " type:" <<varData.var_type << " numberOf_cp:" << varData.numberOf_cp << endl;
		new_input_signal_type.append(new_varName);		//syntax of input string="x0=fixed-step & x1=fixed-linear"
		new_input_signal_type.append("=");
		new_input_signal_type.append(varData.var_type);

		new_numberOfCPs.append(new_varName);
		new_numberOfCPs.append("=");
		new_numberOfCPs.append(to_string(varData.numberOf_cp));

		index++;
		if (index<(list_inputVar_size)){
			new_input_signal_type.append(" & ");
			new_numberOfCPs.append(" & ");
		}
	}
	// ----------------Creating Done----------------------
//	cout << "New learned newVariableCategory =" <<  newVariableCategory << endl;
//	cout << "New learned new_input_signal_type =" <<  new_input_signal_type << endl;
//	cout << "New learned new_numberOfCPs =" <<  new_numberOfCPs << endl;

	//Storing the new replacing strings of user's input for learned model
	this->new_variable_category = newVariableCategory;
	this->new_input_signal_type = new_input_signal_type;
	this->new_numberOf_control_points = new_numberOfCPs;

	this->userVariable_Mapping = userInputOutputData;

	// ----------------Creating new_initial_value ----------------------
	std::list<std::string> list_input_constraints = userInputs->getInitialSet(); //returns list of separate  per variable per linear-constraint from user's input string
	//Now use this list to scan and match the variable mapping and replace the linear-constraint with new-learned-variable names
	string new_initial_value = "";	// syntax of initial_set "x0>=10.2 & x0<=10.5 & x1>=15 & x1<=15"

	index = 0;
	unsigned int tot_constriants = list_input_constraints.size();
	for (list<string>::iterator it= list_input_constraints.begin(); it != list_input_constraints.end(); it++) {
		//cout << (*it) << endl;
		std::string input_constraints =(*it);	//each constriants is of the form   x<= value or x>= value or x=value
		std::string op="", orig_varName="", val;

		getVariableOperatorValue(input_constraints, orig_varName, op, val);
		string new_learn_varName = getEquivalentLearnedVariableName(userInputOutputData, orig_varName); //get learn_varName mapping to orig_varName

		new_initial_value.append(new_learn_varName);
		new_initial_value.append(op);
		new_initial_value.append(val);

		index++;
		if (index < tot_constriants) {
			new_initial_value.append(" & ");
		}
	}
	this->new_initial_set = new_initial_value;
	//cout << "New learned new_initial_set =" <<  new_initial_set << endl;

	// ----------------Creating Done----------------------


}





void model_setup::setup_for_learned_model(hybridAutomata::ptr ha, user_inputs::ptr userInputs){


	//ha->print_var_mapping();
	ha->erase_all_mapping();	//delete the variable name mapping. This will automatically also affect the ha_original_copy being a static mapping
	// -------------- Creating new variable names and mapping it to HA ------------------------
	assign_learnVariable_to_HA(ha, userInputs);
	// ----------------Creating new variable names and mapping it to HA Done----------------------
	/* Now get the original user's input string and search and replace variable names */
	userInputs->clearVariableList();	//clears the list of input and list of output variables in the list-variables

	userInputs->setVariableCategory(new_variable_category);	//on setting it also creates list of input and output variables' list
	userInputs->setInputSignalType(new_input_signal_type);
	userInputs->setNumberOfControlPoints(new_numberOf_control_points);
	userInputs->setInitialSet(new_initial_set);

/*
	unsigned int input_variable_size = userInputs->getListInputVariables().size();
	unsigned int output_variable_size = userInputs->getListOutputVariables().size();
	//cout << "New input_variable_size = " << input_variable_size << endl;
	//cout << "New output_variable_size = " << output_variable_size << endl;

	cout <<"Input Variables:" << endl;
	list<string> list_learn_I = userInputs->getListInputVariables();
	for (list<string>::iterator it= list_learn_I.begin(); it != list_learn_I.end(); it++) {
		cout << (*it) <<endl;
	}
	cout <<"Output Variables:" << endl;
	list<string> list_learn_O = userInputs->getListOutputVariables();
	for (list<string>::iterator it= list_learn_O.begin(); it != list_learn_O.end(); it++) {
		cout << (*it) <<endl;
	}

	cout << "Original variables are"  << endl;
	list_learn_I = list_original_input_variable;
	for (list<string>::iterator it= list_learn_I.begin(); it != list_learn_I.end(); it++) {
		cout << (*it) <<endl;
	}
	list_learn_O = list_original_output_variable;
	for (list<string>::iterator it= list_learn_O.begin(); it != list_learn_O.end(); it++) {
		cout << (*it) <<endl;
	}
*/

}




// reverting back to original user's input
void model_setup::setup_for_original_model(hybridAutomata::ptr ha, user_inputs::ptr userInputs){

	/* Now get the original user's input string and search and replace variable names */
	userInputs->clearVariableList();	//clears the list of input and list of output variables in the list-variables

	userInputs->setVariableCategory(original_variable_category);	//on setting it also creates list of input and output variables' list
	userInputs->setInputSignalType(original_input_signal_type);
	userInputs->setNumberOfControlPoints(original_numberOf_control_points);
	userInputs->setInitialSet(original_initial_set);


//	unsigned int input_variable_size = userInputs->getListInputVariables().size();
//	unsigned int output_variable_size = userInputs->getListOutputVariables().size();
	//cout << "Original input_variable_size = " << input_variable_size << endl;
	//cout << "Original output_variable_size = " << output_variable_size << endl;


	// -------------- Creating new variable names and mapping it to HA ------------------------


	//ha->print_var_mapping();
	ha->erase_all_mapping();	//delete the variable name mapping. This will automatically also affect the ha_original_copy being a static mapping
	//assign_learnVariable_to_HA(ha, userInputs);

	//cout <<"Input Variables:" << endl;
	unsigned int index=0;
	list<string> list_learn_I = userInputs->getListInputVariables();
	for (list<string>::iterator it= list_learn_I.begin(); it != list_learn_I.end(); it++) {
		//cout <<"varName=" << (*it) << "   index=" << index <<endl;
		ha->insert_to_map((*it), index);
		index++;
	}
	//cout <<"Output Variables:" << endl;
	index=userInputs->getListInputVariables().size();
	list<string> list_learn_O = userInputs->getListOutputVariables();
	for (list<string>::iterator it= list_learn_O.begin(); it != list_learn_O.end(); it++) {
		//cout <<"varName=" << (*it) << "   index=" << index <<endl;
		ha->insert_to_map((*it), index);
		index++;
	}
	// ----------------Creating new variable names and mapping it to HA Done----------------------


}






//Takes the input-constraints as input and separates into varName, operator and value
void model_setup::getVariableOperatorValue(std::string input_constraints, std::string &orig_varName, std::string &op, std::string &val) {

	string testStr="dummy dummy";
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("& ");
	tokenizer tokens(testStr, sep);

	std::string varname;
	std::string tokString = input_constraints;

	tokenizer::iterator tok_iter;

	if (tokString.find("<=")!=std::string::npos ) { // less than equal to constraint
		sep = boost::char_separator<char>("<=");
		tokens = tokenizer(tokString,sep);
		tok_iter = tokens.begin();
		orig_varName = *tok_iter;	//first token the variable-name
		tok_iter++;
		op = "<=";
		val = *tok_iter; //not converting it to double to maintain original value as it is.
		//val = std::atof((*tok_iter).c_str());
	} else if(tokString.find(">=")!=std::string::npos){ // greater than equal to constraint
		sep = boost::char_separator<char>(">=");
		tokens = tokenizer(tokString,sep);
		tok_iter = tokens.begin();
		orig_varName = *tok_iter;	//first token the variable-name
		tok_iter++;
		op = ">=";
		val = *tok_iter; //not converting it to double to maintain original value as it is.
		//val = std::atof((*tok_iter).c_str());
	}  else if(tokString.find(">")!=std::string::npos){ // greater than equal to constraint
		sep = boost::char_separator<char>(">");
		tokens = tokenizer(tokString,sep);
		tok_iter = tokens.begin();
		orig_varName = *tok_iter;	//first token the variable-name
		tok_iter++;
		op = ">";
		val = *tok_iter; //not converting it to double to maintain original value as it is.
		//val = std::atof((*tok_iter).c_str());
	}  else if(tokString.find("<")!=std::string::npos){ // greater than equal to constraint
		sep = boost::char_separator<char>("<");
		tokens = tokenizer(tokString,sep);
		tok_iter = tokens.begin();
		orig_varName = *tok_iter;	//first token the variable-name
		tok_iter++;
		op = "<";
		val = *tok_iter; //not converting it to double to maintain original value as it is.
		//val = std::atof((*tok_iter).c_str());
	} else if ((tokString.find("=")!=std::string::npos) || (tokString.find("==")!=std::string::npos)) {
		sep = boost::char_separator<char>("=");
		tokens = tokenizer(tokString,sep);
		tok_iter = tokens.begin();
		orig_varName = *tok_iter;	//first token the variable-name
		tok_iter++;
		op = "=";
		val = *tok_iter; //not converting it to double to maintain original value as it is.
		//val = std::atof((*tok_iter).c_str());
	} else{
		throw std::runtime_error("Input (Goal/Input Set) string improper: <= or >= constraint expected\n");
	}

}



//returns equivalent variable name for the learned model for the given orig_name.
std::string model_setup::getEquivalentLearnedVariableName(std::list<struct variable_mapping> &userInputOutputData, std::string orig_varName) {
	std::string learn_varName="";
	bool found=false;
	for (std::list<struct variable_mapping>::iterator it= userInputOutputData.begin(); it != userInputOutputData.end(); it++) {
		if ((*it).original_var_name == orig_varName) {
			learn_varName = (*it).learned_var_name;
			found=true;
			break;
		}
	}
	if (!found) {
		std::cout <<"Error: Original variable name not found!" << std::endl;
	}
	return learn_varName;
}

void model_setup::assign_learnVariable_to_HA(hybridAutomata::ptr ha, user_inputs::ptr userInputs) {

	//ha->print_var_mapping();
	ha->erase_all_mapping();	//delete the variable name mapping. This will automatically also affect the ha_original_copy being a static mapping
//	std::cout << "mapping size = " << ha->map_size() <<std::endl;

	// -------------- Creating new variable names and mapping it to HA ------------------------
	unsigned int input_variable_size = userInputs->getListInputVariables().size();
	unsigned int output_variable_size = userInputs->getListOutputVariables().size();

	std::list<struct variable_mapping> userInputOutputData;

	std::list<std::string> inputVarList =  userInputs->getListInputVariables();
	std::string variableName, newVariableCategory="";
	unsigned int index=0;
	for (index=0; index < input_variable_size; index++) {
		variableName = "x";
		variableName.append(to_string(index));
		ha->insert_to_map(variableName, index);
	}
	 index=input_variable_size;
	for (unsigned int i=0; i < output_variable_size; i++) {
		variableName = "x";
		variableName.append(to_string(index));
		ha->insert_to_map(variableName, index);
		index++;
	}
	// ----------------Creating new variable names and mapping it to HA Done----------------------
}


bool model_setup::replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}


//Returns the position of the last replace done
size_t model_setup::replaceAll(std::string& str, size_t start_pos, const std::string& from, const std::string& to) {
    if(from.empty())
        return 0;
    size_t found_pos=0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        cout <<"start_pos = "<< start_pos <<endl;
        found_pos = start_pos;	//found position when the last replace hits
    }
    return found_pos;
}



const std::string& model_setup::getInitialSet() const {
	return original_initial_set;
}

void model_setup::setInitialSet(const std::string &initialSet) {
	original_initial_set = initialSet;
}

const std::string& model_setup::getInputSignalType() const {
	return original_input_signal_type;
}

void model_setup::setInputSignalType(const std::string &inputSignalType) {
	original_input_signal_type = inputSignalType;
}

const std::string& model_setup::getNumberOfControlPoints() const {
	return original_numberOf_control_points;
}

const std::string& model_setup::getVariableCategory() const {
	return original_variable_category;
}

void model_setup::setVariableCategory(const std::string &variableCategory) {
	original_variable_category = variableCategory;
}

void model_setup::setNumberOfControlPoints(
		const std::string &numberOfControlPoints) {
	original_numberOf_control_points = numberOfControlPoints;
}

const hybridAutomata::ptr& model_setup::getHaOriginalCopy() const {
	return ha_original_copy;
}

void model_setup::setHaOriginalCopy(const hybridAutomata::ptr &haOriginalCopy) {
	ha_original_copy = haOriginalCopy;
}

const user_inputs::ptr& model_setup::getUserInputsOriginalCopy() const {
	return userInputs_original_copy;
}

const std::list<struct variable_mapping>& model_setup::getUserVariableMapping() const {
	return userVariable_Mapping;
}

void model_setup::setUserVariableMapping(
		const std::list<struct variable_mapping> &userVariableMapping) {
	userVariable_Mapping = userVariableMapping;
}

void model_setup::setUserInputsOriginalCopy(
		const user_inputs::ptr &userInputsOriginalCopy) {
	userInputs_original_copy = userInputsOriginalCopy;
}
