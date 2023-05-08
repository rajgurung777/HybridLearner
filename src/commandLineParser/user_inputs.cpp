/*
 * user_inputs.cpp
 *
 *  Created on: 08-Sep-2021
 *      Author: amit
 */



#include "user_inputs.h"

#include <fstream>

using namespace std;



double user_inputs::getSampleTime() const {
	return sample_time;
}

void user_inputs::setSampleTime(double sampleTime) {
	sample_time = sampleTime;
}

int user_inputs::getModeSize() const {
	return modes;
}

void user_inputs::setModeSize(int numModes) {
	modes = numModes;
}

int user_inputs::getPolyDegree() const {
	return max_degree;
}

void user_inputs::setPolyDegree(int degree) {
	max_degree = degree;
}

double user_inputs::getPrecision() const {
	return precision;
}

void user_inputs::setPrecision(double precision) {
	this->precision = precision;
}

double user_inputs::getTimeHorizon() const {
	return time_horizon;
}

void user_inputs::setTimeHorizon(double timeHorizon) {
	time_horizon = timeHorizon;
}

double user_inputs::getMaxValue() const {
	return max_value;
}

void user_inputs::setMaxValue(double maxValue) {
	max_value = maxValue;
}


int user_inputs::getLowerBound() const {
	return lower_bound;
}

void user_inputs::setLowerBound(int lowerBound) {
	lower_bound = lowerBound;
}

int user_inputs::getUpperBound() const {
	return upper_bound;
}

void user_inputs::setUpperBound(int upperBound) {
	upper_bound = upperBound;
}


void user_inputs::setGoalProperty(const std::string& goalProperty) {
	goal_property = goalProperty;
}

const std::string& user_inputs::getGoalString() const {
	return goal_property;
}

std::list<std::string> user_inputs::getGoalProperty() {
	std::list<std::string> goal_list;
	std::string goalSt = goal_property;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("& ");
	tokenizer tokens(goalSt, sep);

	for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter) {
		goal_list.push_back((std::string) *tok_iter);
	}
	return goal_list;
}

void user_inputs::setInitialSet(const std::string& initial) {
	initial_set = initial;
}
const std::string& user_inputs::getInitialSet_userInput(){
	return initial_set;
}

std::list<std::string> user_inputs::getInitialSet() {
	std::list<std::string> initial_list;
	std::string initialSet = initial_set;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("& ");
	tokenizer tokens(initialSet, sep);

	for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter) {
		initial_list.push_back((std::string) *tok_iter);
	}
	return initial_list;
}

void user_inputs::setTool(const std::string& algo) {
	tool = algo;
}

const std::string& user_inputs::getTool() {
	return tool;
}

void user_inputs::setClusterAlgorithm(const std::string& algo) {
	clust_algo = algo;
}
const std::string& user_inputs::getClusterAlgorithm() {
	return clust_algo;
}



const std::string& user_inputs::getInputFilename() {
	return input_filename;
}

void user_inputs::setInputFilename(const std::string& inputFilename) {
	input_filename = inputFilename;
}
const std::string& user_inputs::getOutputFilename() const {
	return output_filename;
}

void user_inputs::setOutputFilename(const std::string& outputFilename) {
	output_filename = outputFilename;
}


//*******************************************
const std::string& user_inputs::getControllerFilename() const {
	return controller_filename;
}

void user_inputs::setControllerFilename(const std::string& controllerFilename) {
	controller_filename = controllerFilename;
}

const std::string& user_inputs::getConfigFilename() const {
	return config_filename;
}

void user_inputs::setConfigFilename(const std::string& configFilename) {
	config_filename = configFilename;

	std::cout << "\nConfiguration File: parsing Done...\n";
}

const struct plot_variables& user_inputs::getPlotVars() const {
	return plot_vars;
}

void user_inputs::setPlotVars(const struct plot_variables &plotVars) {
	plot_vars = plotVars;
}


int user_inputs::getModel() const {
	return model;
}

unsigned int user_inputs::getSimuInitSize() const {
	return simu_init_size;
}

/*const std::string& user_inputs::getSimuInitPoint() const {
	return simu_init_point;
}

void user_inputs::setSimuInitPoint(const std::string &simuInitPoint) {
	simu_init_point = simuInitPoint;
}*/

unsigned int user_inputs::getSysDimension() const {
	return sys_dimension;
}

const std::string& user_inputs::getSimulationFilename() const {
	return simulation_filename;
}

unsigned int user_inputs::getNumberMatlabSimulationExecuted() const {
	return number_matlab_simulation_executed;
}

int user_inputs::getBoundaryDegree() const {
	return boundary_degree;
}

void user_inputs::setBoundaryDegree(int boundaryDegree) {
	boundary_degree = boundaryDegree;
}

void user_inputs::setNumberMatlabSimulationExecuted(
		unsigned int numberMatlabSimulationExecuted) {
	number_matlab_simulation_executed = numberMatlabSimulationExecuted;
}

void user_inputs::setSimulationFilename(const std::string& simulationFilename) {
	simulation_filename = simulationFilename;
}

void user_inputs::setSysDimension(unsigned int sysDimension) {
	sys_dimension = sysDimension;
}

/*
//Note: simu-init-point must contains string of the form "x0=5,x1=6 & x0=10,x1=16" multiple points separated by & (without any extra space)
std::list< std::vector<double> > user_inputs::getSimulationInitialPoints(){
	std::list< std::vector<double> > init_points; //list of points
	std::list<std::string> all_init_points;

	std::string simuStr = simu_init_point;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("& ");
	tokenizer tokens(simuStr, sep);

	for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter) {
		all_init_points.push_back((std::string) *tok_iter);
	}


//	 Now read each of this string and get the x0 and x1 values and create a list of vector of double
//	 More assumption: user supply input in order of variables eg 1st value 1st followed by 2nd values.
//	 Variable naming of the Original model do not match with the learned model.
//	 Learned model has variables such as x0, x1, etc
//	 Another alternative is: since we already know the built-in model, so we can create a variable-mapping with the original name as
//	 defined in the simulink model.


	std::vector<double> init_point(sys_dimension, 0); //when model is selected the dimension is also set.
	std::list<std::string> each_value;

	//For each initial points
	for (std::list<std::string>::iterator st = all_init_points.begin(); st != all_init_points.end(); ++st) {
		std::string expr =  *st;	//Now expression is of the "x0=5,x1=6"
		boost::char_separator<char> sep1(",");
		tokenizer each_term(expr, sep1);
		for (tokenizer::iterator it = each_term.begin(); it != each_term.end(); ++it) {
			each_value.push_back((std::string) *it);
		}



		for (std::list<std::string>::iterator st = each_value.begin(); st != each_value.end(); ++st) {
			std::string expr = *st;	//Now expression is of the "x0=5"
			boost::char_separator<char> sep1("=");
			tokenizer each_term(expr, sep1);
			tokenizer::iterator it = each_term.begin(); //Reading the first token, which is Variable's name

			std::string varName =  *it;	//variable name
			it++;	//Reading the second token, which is Variable's value
			std::string varVal = *it;
			double varValue = (double) std::atof(varVal.c_str());

			unsigned int var_index = simulation_model->get_index(varName);
			init_point[var_index] = varValue;
		}

		init_points.push_back(init_point);
	} //end of multiple points

	return init_points;
}
*/


void user_inputs::setSimuInitSize(unsigned int simuInitSize) {
	simu_init_size = simuInitSize;
}

void user_inputs::setModel(int model) {
	this->model = model;
}



unsigned int user_inputs::getNumberMatlabSimulationExecutedEquivalenceTest() const {
	return number_matlab_simulation_executed_EquivalenceTest;
}

void user_inputs::setNumberMatlabSimulationExecutedEquivalenceTest(
		unsigned int numberMatlabSimulationExecutedEquivalenceTest) {
	number_matlab_simulation_executed_EquivalenceTest =
			numberMatlabSimulationExecutedEquivalenceTest;
}

const std::list<std::vector<double> >& user_inputs::getRandomInitialPoints_EquivalenceTest() const {
	return random_initial_points_EquivalenceTest;
}

void user_inputs::setRandomInitialPoints_EquivalenceTest(
		const std::list<std::vector<double> > &randomInitialPoints) {
	random_initial_points_EquivalenceTest = randomInitialPoints;
}

unsigned int user_inputs::getNumberRandomPointsGeneratedEquivalenceTest() const {
	return number_randomPoints_generated_EquivalenceTest;
}

void user_inputs::setNumberRandomPointsGeneratedEquivalenceTest(
		unsigned int randomPointsGeneratedEquivalenceTest) {
	number_randomPoints_generated_EquivalenceTest =
			randomPointsGeneratedEquivalenceTest;
}

unsigned int user_inputs::getNumberMatlabSimulationLearnedModelExecuted() const {
	return number_matlab_simulation_learnedModel_executed;
}

double user_inputs::getPrecisionEquivalence() const {
	return precision_equivalence;
}

double user_inputs::getMaxStoptime() const {
	return max_stoptime;
}

void user_inputs::setMaxStoptime(double maxStoptime) {
	max_stoptime = maxStoptime;
}

double user_inputs::getMaxStoptimeEquitest() const {
	return max_stoptime_equitest;
}

void user_inputs::setMaxStoptimeEquitest(double maxStoptimeEquitest) {
	max_stoptime_equitest = maxStoptimeEquitest;
}

unsigned int user_inputs::getMaxTraces() const {
	return max_traces;
}

void user_inputs::setMaxTraces(unsigned int maxTraces) {
	max_traces = maxTraces;
}

void user_inputs::setPrecisionEquivalence(double precisionEquivalence) {
	precision_equivalence = precisionEquivalence;
}

void user_inputs::setNumberMatlabSimulationLearnedModelExecuted(
		unsigned int numberMatlabSimulationLearnedModelExecuted) {
	number_matlab_simulation_learnedModel_executed =
			numberMatlabSimulationLearnedModelExecuted;
}

double user_inputs::getPrecisionGuardRange() const {
	return precision_guard_range;
}

const std::string& user_inputs::getInputSignalType() const {
	return input_signal_type;
}

const std::string& user_inputs::getNumberOfControlPoints() const {
	return numberOf_control_points;
}

int user_inputs::getIsAbstractHsModel() const {
	return isAbstractHS_model;
}

void user_inputs::setIsAbstractHsModel(int isAbstractHsModel) {
	isAbstractHS_model = isAbstractHsModel;
}

void user_inputs::setNumberOfControlPoints(
		const std::string &numberOfControlPoints) {
	numberOf_control_points = numberOfControlPoints;
}

void user_inputs::setInputSignalType(const std::string &inputSignalType) {
	input_signal_type = inputSignalType;
}

void user_inputs::setPrecisionGuardRange(double precisionGuardRange) {
	precision_guard_range = precisionGuardRange;
}




double user_inputs::getClusterError() const {
	return cluster_error_tol;
}


void user_inputs::setClusterError(double clusterError) {
	cluster_error_tol = clusterError;
}


const std::string& user_inputs::getMinMaxBounds() const {
	return MinMax_Bounds;
}

void user_inputs::setMinMaxBounds(const std::string &minMaxBounds) {
	MinMax_Bounds = minMaxBounds;
}

const std::list<struct variable_bounds>& user_inputs::getListVariableBounds() const {
	return list_variable_bounds;
}

void user_inputs::setListVariableBounds(
		const std::list<struct variable_bounds> &listVariableBounds) {
	list_variable_bounds = listVariableBounds;
}

unsigned int user_inputs::getSeed() const {
	return seed;
}

unsigned int user_inputs::getSimulationCheck() const {
	return simulation_check;
}

void user_inputs::setSimulationCheck(unsigned int simulationCheck) {
	simulation_check = simulationCheck;
}

void user_inputs::setSeed(int seed) {
	this->seed = seed;
}

void user_inputs::setVariableBounds() {
	// ******** Parsing input_signal_type ********
	std::list<std::string> minmax_list;
	std::string minmax_bounds = MinMax_Bounds;	//Syntax: x0:minVal,maxVal & x1:minVal,maxVal
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("& ");
	tokenizer tokens(minmax_bounds, sep);
	for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter) {
		minmax_list.push_back((std::string) *tok_iter);
	}

	for (std::list<std::string>::iterator st = minmax_list.begin(); st != minmax_list.end(); ++st) {	//each list is x0:minVal,maxVal
		std::string expr = *st;	//Now expression is of the form "x0:minVal,maxVal"
		boost::char_separator<char> sep1(":");
		tokenizer each_term(expr, sep1);
		tokenizer::iterator it = each_term.begin(); //Reading the first token, which is Variable's name

		std::string varName =  *it;	//variable name
		//cout <<"varName is = " << varName <<endl;
		it++;	//Reading the second token, which is Variable's value
		std::string varBounds = *it;	//varBounds	//Now expression is of the form "minVal,maxVal"
		//cout <<"varBounds is = " << varBounds <<endl;

		boost::char_separator<char> sep2(",");
		tokenizer each_term2(varBounds, sep2);
		tokenizer::iterator it2 = each_term2.begin(); //Reading the first token, which is Variable's name

		double minValue =  (double) std::atof((*it2).c_str());	//Min bound value
		//cout <<"minValue is = " << minValue <<endl;
		it2++;	//Reading the second token, which is Variable's value
		double maxValue = (double) std::atof((*it2).c_str());	//Max bound value
		//cout <<"maxValue is = " << maxValue <<endl;

		setBounds(varName, minValue, maxValue);
	}

	//Debug -----
//	for (std::list<struct variable_bounds>::iterator it = list_variable_bounds.begin(); it != list_variable_bounds.end(); it++){
//		cout << "Variable Name=" << (*it).variable_name << "  " <<	(*it).min_value <<"  ,   " << (*it).max_value << endl;
//	}
	//Debug -----
}

void user_inputs::setBounds(string varName, double minValue, double maxValue){
	//std::list<struct variable_bounds> listVar = list_variable_bounds;
	bool flag=false;
	for (std::list<struct variable_bounds>::iterator it = list_variable_bounds.begin(); it != list_variable_bounds.end(); it++){
		if ((*it).variable_name == varName) {
			(*it).min_value = minValue;
			(*it).max_value = maxValue;
			flag = true;
			break;
		}
	}
	if (flag==false){
		cout <<"Invalid variable name for the command Option --MinMax-bounds"<<endl;
		exit(1);
	}
}


void user_inputs::getVariableBounds(string varName, double &minValue, double &maxValue, std::string &varCategory){
	bool flag=false;
	for (std::list<struct variable_bounds>::iterator it = list_variable_bounds.begin(); it != list_variable_bounds.end(); it++){
		if ((*it).variable_name == varName) {
			minValue = (*it).min_value;
			maxValue = (*it).max_value;
			varCategory = (*it).variable_category;
			flag = true;
			break;
		}
	}
	if (flag==false) { //should return -MinMaxValue and +MinMaxValue, the global min-max values for all system variables
		minValue = -1 * this->max_value;
		maxValue = this->max_value;
		varCategory = "input"; //Default
	}
}

const std::string& user_inputs::getT2Values() const {
	return t2_values;
}

void user_inputs::setT2Values(const std::string &t2Values) {
	t2_values = t2Values;
}

const std::string& user_inputs::getVariableTypes() const {
	return variable_types;
}

void user_inputs::setVariableTypes(const std::string &variableTypes) {
	variable_types = variableTypes;
}

const std::string& user_inputs::getEngine() const {
	return Engine;
}

void user_inputs::setEngine(const std::string &engine) {
	Engine = engine;
}

const std::string& user_inputs::getModelFilename() const {
	return model_filename;
}

void user_inputs::setModelFilename(const std::string &modelFilename) {
	model_filename = modelFilename;
}

unsigned int user_inputs::getGuard() const {
	return guard;
}

void user_inputs::setGuard(unsigned int guard) {
	this->guard = guard;
}

const std::string& user_inputs::getVariableCategory() const {
	return variable_category;
}

/*
 * Function returns a map of variable-type based on the key as variable-name
 * it also creates a list of input and list of output variables
 */
std::map<std::string, std::string> user_inputs::getVariableCategory_map(){
	std::map<std::string, std::string> variable_type;
	//Takes the data variable_category. Parse it to construct a map of variable-name and its type
	std::string var_type = variable_category;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(", ");
	tokenizer tokens(var_type, sep);
	std::list<std::string> input_var_types;
	for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
		input_var_types.push_back((std::string) *tok_iter);
	}


	for (std::list<std::string>::iterator st = input_var_types.begin(); st != input_var_types.end(); ++st) {	//each list is x0:minVal
		std::string expr = *st;	//Now expression is of the form "x0:minVal,maxVal"
		boost::char_separator<char> sep1(":");
		tokenizer each_term(expr, sep1);
		tokenizer::iterator it = each_term.begin(); //Reading the first token, which is Variable's name

		std::string varName =  *it;	//variable name
//		std::cout <<"varName is = " << varName << std::endl;

		it++;	//Reading the second token, which is Variable's value
		std::string varType = *it;	//varBounds	//Now expression is of the form "minVal,maxVal"
//		std::cout <<"varType is = " << varType << std::endl;

		variable_type[varName] = varType;
		if (varType == "input"){
			list_input_variables.push_back(varName);
		} else if (varType == "output") {
			list_output_variables.push_back(varName);
		}
	}


	return variable_type;
}

const std::list<std::string>& user_inputs::getListInputVariables() const {
	return list_input_variables;
}

void user_inputs::setListInputVariables(
		const std::list<std::string> &listInputVariables) {
	list_input_variables = listInputVariables;
}

const std::list<std::string>& user_inputs::getListOutputVariables() const {
	return list_output_variables;
}

const std::map<std::string, std::string>& user_inputs::getVariableTypeMapping() const {
	return variable_type_mapping;
}

void user_inputs::setVariableTypeMapping(
		const std::map<std::string, std::string> &variableTypeMapping) {
	variable_type_mapping = variableTypeMapping;
}

void user_inputs::setListOutputVariables(
		const std::list<std::string> &listOutputVariables) {
	list_output_variables = listOutputVariables;
}

void user_inputs::clearVariableList(){
	list_input_variables.clear();
	list_output_variables.clear();
}

void user_inputs::setVariableCategory(const std::string &variableCategory) {
	variable_category = variableCategory;
	setVariableTypeMapping(getVariableCategory_map());
}

unsigned int user_inputs::getInvariant() const {
	return invariant;
}

const std::string& user_inputs::getInputSignalSineWaveParameter() const {
	return input_signal_sine_wave_parameter;
}

const std::map<std::string, std::pair<double, double> >& user_inputs::getInputVariableSinewaveParameterMapping() const {
	return input_variable_sinewave_parameter_mapping;
}



std::map<std::string, std::pair<double, double> > user_inputs::getSinewaveParameterMapping() {

	std::map<std::string, std::pair<double, double> > sine_params;

	std::list<std::string> var_param_list;
	std::string input_str = input_signal_sine_wave_parameter;	//Syntax: "x0={20,5} & x1={100,1000}"
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("&");
	tokenizer tokens(input_str, sep);
	std::string tmp_str;
	for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter) {
		tmp_str = (std::string) *tok_iter;
		boost::trim(tmp_str);

		var_param_list.push_back(tmp_str);
	}


	double amplitude, zero_offset;

	for (std::list<std::string>::iterator st = var_param_list.begin(); st != var_param_list.end(); ++st) {	//each list is x0={20,5}
		std::string expr = *st;	//Now expression is of the form "x0={20,5}"
		boost::char_separator<char> sep1("=");
		tokenizer each_term(expr, sep1);
		tokenizer::iterator it = each_term.begin(); //Reading the first token, which is Variable's name

		std::string varName =  *it;	//variable name
		//std::cout <<"varName is = " << varName << std::endl;

		it++;	//Reading the second token, which is {20,5}
		tmp_str = *it;	//Now expression is of the form  {20,5}
		//std::cout <<"tmp_str is = " << tmp_str << std::endl;
		unsigned int ll = tmp_str.length();
		tmp_str = tmp_str.substr(1, ll-2);	//extracts the string without the first and the last character

		boost::char_separator<char> sep2(",");
		tokenizer params(tmp_str, sep2);
		tokenizer::iterator it2 = params.begin(); //Reading the first token, which is Variable's name
		amplitude = (double) std::atof((*it2).c_str());
		it2++;
		zero_offset = (double) std::atof((*it2).c_str());

		std::pair<double, double> parameter;
		parameter.first = amplitude;
		parameter.second = zero_offset;

		sine_params[varName] = parameter;
	}

	return sine_params;
}

void user_inputs::setInputVariableSinewaveParameterMapping(
		const std::map<std::string, std::pair<double, double> > &inputVariableSinewaveParameterMapping) {
	input_variable_sinewave_parameter_mapping =
			inputVariableSinewaveParameterMapping;
}

void user_inputs::setInputSignalSineWaveParameter(
		const std::string &inputSignalSineWaveParameter) {
	input_signal_sine_wave_parameter = inputSignalSineWaveParameter;
	setInputVariableSinewaveParameterMapping(getSinewaveParameterMapping());

/*
	//Debug ---
	for (std::map<std::string, std::pair<double, double> >::iterator mapit=input_variable_sinewave_parameter_mapping.begin(); mapit != input_variable_sinewave_parameter_mapping.end(); mapit++) {
		cout << "variable=" << (*mapit).first << "  amp:" <<(*mapit).second.first << "  offset:" << (*mapit).second.second << endl;
	}
	// ----
*/
}

void user_inputs::setInvariant(unsigned int invariant) {
	this->invariant = invariant;
}

bool user_inputs::isInputVariable(const std::string variableName) {

	bool isInputVariable = false;

	unsigned int number_of_input_variables= list_input_variables.size();
	if (number_of_input_variables >= 1) {
		for (list<std::string>::iterator it = list_input_variables.begin(); it != list_input_variables.end(); it++) {
			string varName = *it;	//extract the variable name
			if (varName == variableName) {
				isInputVariable = true;
				break;
			}
		}
	}
	return isInputVariable;
}

const std::string& user_inputs::getSimuTraceFilename() const {
	return simu_trace_filename;
}

void user_inputs::setSimuTraceFilename(const std::string &simuTraceFilename) {
	simu_trace_filename = simuTraceFilename;
}

const std::string& user_inputs::getSimulinkModelFilename() const {
	return simulink_model_filename;
}

void user_inputs::setSimulinkModelFilename(
		const std::string &simulinkModelFilename) {
	simulink_model_filename = simulinkModelFilename;

}

void user_inputs::setSimulinkModelFiles(const std::string &simulinkModelFiles) {
	simulink_model_files = simulinkModelFiles;
	//now parse this and populate the list into the variable simulink_model_filenames
	std::list<std::string> list_filenames;

	std::string input_str = simulinkModelFiles;	//Syntax: "file1.slx file2.slx"
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(" ");
	tokenizer tokens(input_str, sep);
	std::string tmp_str;
	for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter) {
		tmp_str = (std::string) *tok_iter;
		boost::trim(tmp_str);

		list_filenames.push_back(tmp_str);
	}

	setSimulinkModelFilenames(list_filenames);
}


void user_inputs::setSimulinkModelFilenames(
		const std::list<std::string> &simulinkModelFilenames) {
	simulink_model_filenames = simulinkModelFilenames;
}

const std::list<std::string>& user_inputs::getSimulinkModelFilenames() const {
	return simulink_model_filenames;
}

double user_inputs::getDbScanEpsDist() const {
	return DBScan_eps_dist;
}

void user_inputs::setDbScanEpsDist(double dbScanEpsDist) {
	DBScan_eps_dist = dbScanEpsDist;
}

unsigned int user_inputs::getDbScanMinSamples() const {
	return DBScan_min_samples;
}

const std::string& user_inputs::getOdeSolver() const {
	return ODESolver;
}

int user_inputs::getFixedIntervalData() const {
	return fixed_interval_data;
}

double user_inputs::getCorrelationThreshold() const {
	return correlation_threshold;
}

void user_inputs::setCorrelationThreshold(double correlationThreshold) {
	correlation_threshold = correlationThreshold;
}

double user_inputs::getDistanceThreshold() const {
	return distance_threshold;
}

unsigned int user_inputs::getDTW_SampleSize() const {
	return DTW_sample_size;
}

void user_inputs::setDTW_SampleSize(unsigned int dtwSampleSize) {
	DTW_sample_size = dtwSampleSize;
}

double user_inputs::getDTW_SimuTime() const {
	return DTW_simu_time;
}

unsigned int user_inputs::getMaxGenerateTraceSize() const {
	return max_generateTrace_size;
}

unsigned int user_inputs::getOdeSpeedup() const {
	return ode_speedup;
}

const std::string& user_inputs::getOdeSolverType() const {
	return ODESolverType;
}

void user_inputs::setOdeSolverType(const std::string &odeSolverType) {
	ODESolverType = odeSolverType;
}

void user_inputs::setOdeSpeedup(unsigned int odeSpeedup) {
	ode_speedup = odeSpeedup;
}

void user_inputs::setMaxGenerateTraceSize(unsigned int maxGenerateTraceSize) {
	max_generateTrace_size = maxGenerateTraceSize;
}

void user_inputs::setDTW_SimuTime(double dtwSimuTime) {
	DTW_simu_time = dtwSimuTime;
}

void user_inputs::setDistanceThreshold(double distanceThreshold) {
	distance_threshold = distanceThreshold;
}

void user_inputs::setFixedIntervalData(int fixedIntervalData) {
	fixed_interval_data = fixedIntervalData;
}

void user_inputs::setOdeSolver(const std::string &odeSolver) {
	ODESolver = odeSolver;
}

void user_inputs::setDbScanMinSamples(unsigned int dbScanMinSamples) {
	DBScan_min_samples = dbScanMinSamples;
}

int user_inputs::getFilterLastSegment() const {
	return filter_last_segment;
}

double user_inputs::getSegmentationFineError() const {
	return segmentation_fine_error;
}

const std::string& user_inputs::getT3Values() const {
	return t3_values;
}

int user_inputs::getLmmStepSize() const {
	return lmm_step_size;
}

void user_inputs::setLmmStepSize(int lmmStepSize) {
	lmm_step_size = lmmStepSize;
}

void user_inputs::setT3Values(const std::string &t3Values) {
	t3_values = t3Values;
}

void user_inputs::setSegmentationFineError(double segmentationFineError) {
	segmentation_fine_error = segmentationFineError;
}

void user_inputs::setFilterLastSegment(int filterLastSegment) {
	filter_last_segment = filterLastSegment;
}
