/*
 * engineSelector.cpp
 *
 *  Created on: 27-Jun-2022
 *      Author: amit
 */

#include "engineSelector.h"

engineSelector::engineSelector() {
	// Constructor stub
}

engineSelector::engineSelector(user_inputs::ptr user_Inputs) {
	userInputs = user_Inputs;
	intermediate  = intermediateResult::ptr(new intermediateResult());
	H = hybridAutomata::ptr (new hybridAutomata());
	report = summary::ptr(new summary());

}

/* selects the Simulation engine */
void engineSelector::selectSimu() {

	std::cout << "Running Engine: trajectory simulation ... \n";
	/*
	 * Step 1: Generate input data using user's initial values and parameters related to input variables
	 * Step 2: Create a script file for running it with initial-input and output(use a0, a1, etc) as specific variable names
	 * Step 3: Using a for-loop of the size equal to the #number of simulation
	 * 		   populate initial values of the specific input and output variables created in Step 2,
	 * 		   into Matlab's Workspace and execute the script file, generating result_simu_data.txt
	 * Step 4: Append each result file into an output file. Return this file as the final output file.
	 * We assume user correctly assigns appropriate name/label to every inport in the .slx model using the naming conventions as x0In, x1In, where x0 and x1 are input variable names.
	 *
	 * Setting the variable-index and type mapping in the automata H based on user's input (listInputVariables and listOutputVariables).
	 * Since, we want to provide index in order of input-variables followed by output-variables, so accordingly we first store input variables followed by output.
	 * We assume user do not make mistake in supplying variable name and it's proper type/category
	 */
	// --------------
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

	// --------------

	parameters::ptr params = parameters::ptr(new parameters());
	/*params->setUserInputs(userInputs);
	params->setH(H);
	params->setParameters(userInputs, H);*/
	params->setParameters(userInputs, H, intermediate);


	std::list<std::vector<double> > initial_output_values;
	std::list<struct timeseries_all_var> initial_inputValues_timeSeriesData;

	generate_input_information(initial_inputValues_timeSeriesData, initial_output_values, params, ep, report);	//initial values

	generate_simulation_traces(initial_inputValues_timeSeriesData, initial_output_values, params, ep);


}

/* Translates the model file in .txt to .SLX (Matlab's Simulink model) */
void engineSelector::selectMdl2Slx(){

	parameters::ptr params = parameters::ptr(new parameters());
	unsigned int seedValue=userInputs->getSeed();
	myRandomNumberGenerator::ptr randomGenObject = myRandomNumberGenerator::ptr(new myRandomNumberGenerator(seedValue));  // setting 100 as default seed
	params->setRandomGenObj(randomGenObject);
	params->setParameters(userInputs, H, intermediate);

	std::cout << "Running Engine: txt2slx ... \n";
	model_translator(params, ep, report);
}

/* Creates an Hybrid Automaton model (.txt file) from user supplied simulation trajectories */

void engineSelector::selectLearn_HA() {
	//This function is called from the engine "learn-ha"
	std::cout << "Running Engine: Learning Hybrid Automaton  ... \n";

	parameters::ptr params = parameters::ptr(new parameters());
	params->setParameters(userInputs, H, intermediate);

	/*
	 * To call learning algorithm implemented in Python have to copy the input file(simulation-trace)
	 * inside the folder "src/learnHA/data" since at the moment Python project is reading file only within its location (current folder)
	 */
	initial_setting(params);	//copy the file from user supplied or current folder to "src/pwa/naijun/filename" this being the working directory for the learning algorithm.

	boost::timer::cpu_timer naijun_runtime;
	naijun_runtime.start();
	learnHA_caller(userInputs);	//Make is Simple and call it from everywhere. This invokes our "HA learning Algorithm".
	//system("pwd"); //although supplied cd ../src/pwa but still in the current Release location
	naijun_runtime.stop();



	double wall_clock;
	wall_clock = naijun_runtime.elapsed().wall / 1000000; //convert nanoseconds to milliseconds

	double running_time = wall_clock / (double) 1000;	//convert milliseconds to seconds
	//std::cout << "\n\n*******Learning Nonlinear Switched Dynamical Systems (specific Hybrid Automata)****\n \t Running Time (Boost/Wall clock time) (in Seconds) = " << running_time<<std::endl;
	std::cout << "\nRunning Time (Boost/Wall clock time) (in Seconds) = " << running_time<<std::endl;

	report->setRuntimeLearningAlgo(running_time);

	std::cout << "\nModel Learning Phase completed ........"<<std::endl;

	// ********* Now copy/move the learned model file from "/src/pwa" to current folder *********
	string copycommand ="";
	//system("pwd");
	copycommand.append("cp ");
	copycommand.append("../src/learnHA/");

	copycommand.append(userInputs->getOutputFilename());
	copycommand.append(" .");	//to the current working directory, i.e. in the Release directory
	int x = system(copycommand.c_str());
	if (x == -1) {
		cout << "Error executing cmd: " << copycommand << endl;
	}

}


void engineSelector::selectLearn_HA_loop() {

	parameters::ptr params = parameters::ptr(new parameters());
	params->setParameters(userInputs, H, intermediate);

	execute_learn_ha_loop(params, report, ep);

}


/* selects the equi-test (Equivalence Testing) engine
 * Both the model-1 and model-2 should have the same variable naming conventions.
 * We also assume at the moment both models are in the same folder so that a single path for running is set in MatLab.
 * TODO: to support models to be executed from different folders with different path for each.
 * */
bool engineSelector::selectEquiTest(){

	parameters::ptr params = parameters::ptr(new parameters());
	unsigned int seedValue=userInputs->getSeed();
	myRandomNumberGenerator::ptr randomGenObject = myRandomNumberGenerator::ptr(new myRandomNumberGenerator(seedValue));  // setting 100 as default seed
	params->setRandomGenObj(randomGenObject);
	params->setParameters(userInputs, H, intermediate);

	randomEquivalenceTesting::ptr randomEquiTest = randomEquivalenceTesting::ptr(new randomEquivalenceTesting());
	bool isEquivalent = randomEquiTest->execute_random_equivalence_test(params, ep, report);

	return isEquivalent;
}

/*
 * Selects the different engines provided in the tool
 */
void engineSelector::select() {


	// ----Selects trajectory simulation engine: Generates simulation trace file for a given .slx or .mdl simulink-model file (with input specifications)
	if (boost::algorithm::iequals(userInputs->getEngine(),"simu")==true) {
		selectSimu();
		return;
	}

	// Selects model translator engine: Converts a model from .txt to .slx
	if(boost::algorithm::iequals(userInputs->getEngine(),"txt2slx")==true) {
		selectMdl2Slx();
		return;
	}

	// Selects the engine learn-ha: learns an HA in a single iteration using a given simulation traces file
	if(boost::algorithm::iequals(userInputs->getEngine(),"learn-ha")==true) {
		selectLearn_HA();
		return;
	}

	// Select the engine learn-ha-loop: learns an HA in a loop using a simulink model (and input specifications) as input
	if(boost::algorithm::iequals(userInputs->getEngine(),"learn-ha-loop")==true) {
		selectLearn_HA_loop();

		return;
	}

	//select the engine equi-test: performs equivalence testing of two user provided compatible simulink model files.
	if(boost::algorithm::iequals(userInputs->getEngine(),"equi-test")==true) {
		selectEquiTest();
		return;
	}



}

engineSelector::~engineSelector() {
	// Destructor stub
}
