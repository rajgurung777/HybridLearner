/*
 * randomEquivalenceTesting.cpp
 *
 *  Created on: 22-Feb-2023
 *      Author: amit
 */

#include "randomEquivalenceTesting.h"

randomEquivalenceTesting::randomEquivalenceTesting() {
	// TODO Auto-generated constructor stub

}

randomEquivalenceTesting::~randomEquivalenceTesting() {
	// TODO Auto-generated destructor stub
}



bool randomEquivalenceTesting::execute_random_equivalence_test(parameters::ptr params, std::unique_ptr<MATLABEngine> &ep, summary::ptr &report){

	intermediateResult::ptr intermediate = params->getIntermediate();
	user_inputs::ptr userInputs = params->getUserInputs();
	hybridAutomata::ptr H = params->getH();


	std::cout << "Running Engine: Equivalence Testing  ... \n";
	std::cout <<" We assume the two Simulink model files are compatible (input and output variables are equal and in same order)" << std::endl;
/*	std::cout <<" List of files are " << std::endl;
	std::list<std::string> simufiles = userInputs->getSimulinkModelFilenames();
	for (std::list<std::string>::iterator it=simufiles.begin(); it != simufiles.end(); it++) {
		std::cout << (*it) << std::endl;
	}*/

	/* Step 1: Generate input data using user's initial values and parameters related to input variables
	 * Step 2: Create a script file each for running both the simulink file with initial-input and output(use a0, a1, etc) as specific variable names
	 * Step 3: Using a for-loop of the size equal to the #number of simulation or the #number of equivalence traces
	 * 		   populate initial values of the specific input and output variables created in Step 2,
	 * 		   into Matlab's Workspace and execute the script file, generating two result files result_file1.txt and result_file2.txt
	 * Step 4: Now open both the result files and read them each line at a time and compute the difference.
	 * 	We assume user correctly assigns (x0, x1, etc.) input and output variable names.
	 *----------------------------------------------------------------------------------------------------------------------------------------------------------
	 * 	Setting the variable-index and type mapping in the automata H based on user's input (listInputVariables and listOutputVariables).
	 * 	Since, we want to provide index in order of input-variables followed by output-variables, so accordingly we first store input variables followed by output.
	 * 	We assume user do not make mistake in supplying variable name and it's proper type/category, including
	 */

	// -------------- variable mapping in the automaton object-variable --------------
	std::list<std::string> inputVarList =  userInputs->getListInputVariables();
	std::string variableName;
	unsigned int index=0;
	for (std::list<std::string>::iterator it = inputVarList.begin(); it != inputVarList.end(); it++) {
		variableName = (*it);
		H->insert_to_map(variableName, index);
		index++;
	}
	std::list<std::string> outputVarList =  userInputs->getListOutputVariables();
	//ind=0; should continue
	for (std::list<std::string>::iterator it = outputVarList.begin(); it != outputVarList.end(); it++) {
		//std::cout << "VarName=" << (*it) <<"  index=" << ind << std::endl;
		variableName = (*it);
		H->insert_to_map(variableName, index);
		index++;
	}
	unsigned int tot_dim = inputVarList.size() + outputVarList.size();
	userInputs->setSysDimension(tot_dim); //dimension is required in equivalence_testing() function below
	// -------------- --------------



	// -------------- initial input-signal's time-serise input data --------------
	std::list<std::vector<double> > initial_output_values;
	std::list<struct timeseries_all_var> initial_inputValues_timeSeriesData;
	generate_input_information(initial_inputValues_timeSeriesData, initial_output_values, params, ep, report);	//initial values
	// -------------- --------------

	std::string path_for_file_one = "", path_for_file_two = "";

	std::list<std::string> model_files = userInputs->getSimulinkModelFilenames();
	assert(model_files.size()==2);	//Two model file should be provided to run Equivalence Test
	std::list<std::string>::iterator it=model_files.begin();
	std::string model_file_one = getFileName_without_Path((*it), path_for_file_one);
	it++; //next iterator for next model filename
	std::string model_file_two = getFileName_without_Path((*it), path_for_file_two);
	//
	std::cout <<" List of files are " << std::endl;
	std::cout <<" Model File one = " << model_file_one << "   path_for_file_one = " << path_for_file_one << std::endl;
	std::cout <<" Model File two = " << model_file_two << "   path_for_file_two = " << path_for_file_two << std::endl;



	std::string script_filename_one = "run_script_", output_filename_one="result_", script_extension=".m", result_extension=".txt";
	std::string script_filename_two = "run_script_", output_filename_two="result_";
	//Note: this hard-coded filenames if required to be changed, also change in the function above engineSelector::generate_run_script_file(std::string model_filename)
	std::string filename_without_extension_one, filename_without_extension_two;
	size_t found = model_file_one.find(".");	//extract .slx from the model file
	if (found != string::npos){
		filename_without_extension_one = model_file_one.substr(0, found);
	}
	script_filename_one.append(filename_without_extension_one);	//user supplied simulink-model filename without extension
	script_filename_one.append(script_extension);	//.m extension appended

	output_filename_one.append(filename_without_extension_one);
	output_filename_one.append(result_extension);

	found = model_file_two.find(".");	//extract .slx from the model file
	if (found != string::npos){
		filename_without_extension_two = model_file_two.substr(0, found);
	}
	script_filename_two.append(filename_without_extension_two);	//user supplied simulink-model filename without extension
	script_filename_two.append(script_extension);	//.m extension appended

	output_filename_two.append(filename_without_extension_two);
	output_filename_two.append(result_extension);

	// -------------- create script files for running the simulink model --------------
	intermediate->setMatlabPathForLearnedModel(path_for_file_one);
	generate_run_script_file(model_file_one, params);	// ----- Create first run_script from .slx model

	intermediate->setMatlabPathForLearnedModel(path_for_file_two);
	generate_run_script_file(model_file_two, params);	// ----- Create second run_script from .slx model

	// ------------------------------------------

	std::string output_filename_one_withPath = getFileNameWithPath(output_filename_one, path_for_file_one);
	std::string output_filename_two_withPath = getFileNameWithPath(output_filename_two, path_for_file_two);


	// -------------- Simulate the two models for each initial input signal and test for equivalence --------------


	bool flagEquivalent=true;
	double maxDistance=0.0;
	std::list<std::vector<double> >::iterator it_out_val = initial_output_values.begin(); //iterator for the output variables
	for (std::list<struct timeseries_all_var>::iterator it =initial_inputValues_timeSeriesData.begin(); it != initial_inputValues_timeSeriesData.end(); it++, it_out_val++) {

		std::list<struct timeseries_input> init_point = (*it).timeseries_signal;
		//cout <<"init_point.size()=" << init_point.size() << endl;
		std::vector<double> output_variable_init_values = (*it_out_val);

		// ***************  --------------------------------- ***************
		intermediate->setMatlabPathForLearnedModel(path_for_file_one);
		simu_model_file(ep, userInputs, init_point, output_variable_init_values, script_filename_one, output_filename_one, intermediate, H); //Populate initial data in Matlab's Workspace and then run the script file

		intermediate->setMatlabPathForLearnedModel(path_for_file_two);
		simu_model_file(ep, userInputs, init_point, output_variable_init_values, script_filename_two, output_filename_two, intermediate, H); //Populate initial data in Matlab's Workspace and then run the script file
		// ***************  --------------------------------- ***************


		// -------------- Read the two files and compare --------------
		flagEquivalent = compute_trace_equivalence(output_filename_one_withPath, output_filename_two_withPath, maxDistance, params);
		std::cout <<"Maximum Euclidean Distance=" << maxDistance << std::endl;
		// -------------- --------------

		if (flagEquivalent==false)	//found a counter-example
			break;
	}



	if (flagEquivalent==true){
		std::cout << "The two Simulink models are Equivalent!!!" << std::endl;
	} else {
		std::cout << "The two Simulink models are NOT Equivalent!!!" << std::endl;
	}


	return flagEquivalent;
}



