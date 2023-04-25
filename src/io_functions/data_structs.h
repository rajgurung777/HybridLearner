/*
 * data_structs.h
 *
 *  Created on: 26-Sep-2021
 *      Author: amit
 */

#ifndef IO_FUNCTIONS_DATA_STRUCTS_H_
#define IO_FUNCTIONS_DATA_STRUCTS_H_

#include <string>
#include <vector>
#include <list>
//#include "../utilities/math/matrix.h"

using namespace std;

struct plot_variables {
	std::string first_variable;
	unsigned int first_variable_index;

	std::string second_variable;
	unsigned int second_variable_index;
};

struct variable_bounds {
	std::string variable_name;
	unsigned int variable_index;
	std::string variable_category; //input or output.  By default all variables are input, indicating that specification constraints are applied to them.
	double min_value;
	double max_value;
};



struct equivalenceTest {
	unsigned int iteration;
	double time_taken;
	unsigned int traces_checked;
};



struct control_points {
	unsigned int var_index;
	string var_name;
	string var_type;	//Fixed- or Var-Step
	unsigned int numberOf_cp;
	vector<double> cps; //list of random control-points for var_name
};


//Timeseries data obtained for simulink model. Both CE_input and initial_input will have same structure
//Note: list struct is used so that both fixed- and variable-step signals can be maintained for different variables.
struct timeseries_input {
	control_points var_detail;
	std::vector<double> time_values;	//time series vector for corresponding individual variable
	std::vector<double> var_values;	//values for a variable,
};

/*struct timeseries_input {
	//std::vector<double> time_values;	//time series vector
	std::list<std::vector<double>> time_values;	//time series vector, one each for the corresponding variables
	//math::matrix<double> var_values;	//values for each variables, one per column
	std::list<std::vector<double>> var_values;	//values for each variables, The order of variables are maintained as Queue (FIFO)
};*/

struct timeseries_all_var {
	std::list<timeseries_input> timeseries_signal;
};

struct CE_list {
	std::list<timeseries_input> CE_trace;	//CE trace when model supports separate input and output variables
	std::vector<double> CE_initial_point;	//when model is Abstract HS with no distinction between input/output variables
};

//mapping of original and learned model's variable. Other fields may not be required
struct variable_mapping {
	unsigned int var_index;
	string original_var_name;
	string learned_var_name;
	string var_type;	//Fixed- or Var-Step
	unsigned int numberOf_cp;
	vector<double> cps; //list of random control-points for var_name
};



#endif /* IO_FUNCTIONS_DATA_STRUCTS_H_ */
