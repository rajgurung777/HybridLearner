/*
 * model_translator.cpp
 *
 *  Created on: 21-Feb-2023
 *      Author: amit
 */


#include "model_translator.h"


//Performs the actual model parsing and creating .slx model
void model_translator(parameters::ptr params, std::unique_ptr<MATLABEngine> &ep, summary::ptr &report) {
	/*
	 * Step-1 parse the txt model file and create an object of hybrid-automaton class
	 * 		Note: the txt model can only have ODE on the output variables. It can as well have ODE on the input variables (our learning algo gives ODE on all variables together)
	 * 		our hybrid-automaton object store all and on printing the .slx we print ODE only for output variables.
	 * Step-2 create .slx model file using the object of hybrid-automaton class
	 */

	intermediateResult::ptr intermediate = params->getIntermediate();
	user_inputs::ptr userInputs = params->getUserInputs();
	hybridAutomata::ptr H = params->getH();

	//Ask user if convert equality guard to range (+/- epsilon) constraints.
	ha_model_parser(H, userInputs, intermediate); //locations (invariant and ode) followed by transitions (guard and reset)
	//verifyHA_output(H);

	/*
	 * Setting the variable-index and type mapping in the automata H based on user's input (listInputVariables and listOutputVariables).
	 * Since, we want to provide index in order of input-variables followed by output-variables, so accordingly we first store input variables followed by output.
	 * We assume user do not make mistake in supplying variable name and it's proper type/category
	 */
	// --------------
	std::list<std::string> inputVarList =  userInputs->getListInputVariables();
	std::string variableName;
	unsigned int index=0;
	for (std::list<std::string>::iterator it = inputVarList.begin(); it != inputVarList.end(); it++) {
		//std::cout << "VarName=" << (*it) <<"  index=" << ind << std::endl;
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

	/*// Mapping variable name and index using ODE. when user do not supply variable type/category
	location::ptr loc = H->getLocation(1);	//since our location starts from 1
	list<flow_equation> derivatives = loc->getDerivatives();
	unsigned int index=0;
	for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
		string prime_variableName = (*it_flow).varName;	//eg x0'
		size_t pos = prime_variableName.find("'");
		string variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol
		//Todo: currently only output variable is mapped, input variables also need to be recorded with some indication. Otherwise, use user-supplied information
		H->insert_to_map(variableName, index);
		//H->insert_output_to_map(variableName, index);	//mapping the output variable

		index++;
	}*/

	//This fixing for userInputs: sys_dimension is a hard to remember fix. Better fixing can be applied later.
	H->setDimension(H->map_size());
	//std::cout << "sysDim=" << H->getDimension() << std::endl;
	userInputs->setSysDimension(H->getDimension());
	//H->print_var_mapping();
	//  ------------

	//Step-2: Obtain .slx model from object H
	//--- Starting Matlab engine only when required ---- For engine HybridLearner
	boost::timer::cpu_timer matlab_start;

	std::cout << "\nStarting Matlab Engine ... please wait!!" << std::endl;
	matlab_start.start();
	ep = connectMATLAB();
	matlab_start.stop();

	double wall_clock;
	wall_clock = matlab_start.elapsed().wall / 1000000; //convert nanoseconds to milliseconds
	double running_time = wall_clock / (double) 1000;	//convert milliseconds to seconds
	std::cout << "Matlab engine start: Running Time (in Seconds) = " << running_time << std::endl;
	report->setRuntimeMatlabStart(running_time);
	// ---------

	simulinkModelConstructor::ptr model = simulinkModelConstructor::ptr(new simulinkModelConstructor(H, userInputs, intermediate));
	unsigned int iterations_count = 0; // just a label for the first model creation
	model->setIteration(iterations_count);
	model->printSimulinkModelFile();
	cout << "Done Creating the script file for creating Simulink Model!!!" << endl;


	// ---------- few Path setting for execution to create the .slx model
	linux_utilities::ptr linux_util = linux_utilities::ptr (new linux_utilities());
	intermediate->setMatlabDefaultPath(linux_util->getCurrentWorkingDirectoryWithPath());
	intermediate->setToolRootPath(linux_util->getParentWorkingDirectoryWithPath());
	std::string  learned_path ="";
	//cout << "pwd = " << linux_util->getCurrentWorkingDirectoryWithPath() << endl;
	learned_path.append(linux_util->getCurrentWorkingDirectoryWithPath());	//either Release or Debug
	learned_path.append("/");
	learned_path.append(intermediate->getOutputfilenameWithoutExtension());
	intermediate->setMatlabPathForLearnedModel(learned_path);		//Very important Line for running Matlab script

	std::cout <<"Creating Simulink model file with extension .slx .... please wait..." << std::endl;
	model->executeSimulinkModelConstructor(ep);
	std::cout << "Model .slx file created successfully!!" << std::endl;


	run_script_generator(model, params, ep);

}

//Performs the actual running-script creation tasks
void run_script_generator(simulinkModelConstructor::ptr &model, parameters::ptr params, std::unique_ptr<MATLABEngine> &ep){

	// -------------------    generating input time-serise data   ---------------------
	myRandomNumberGenerator::ptr randomGenObject = params->getRandomGenObj(); //myRandomNumberGenerator::ptr(new myRandomNumberGenerator(100)); //todo maybe just do this creating in the construction
	user_inputs::ptr user_copy = user_inputs::ptr(new user_inputs());
	user_copy = params->getUserInputs();	//  userInputs;

	//summary::ptr report = summary::ptr(new summary()); //not used
	//toolFrame::ptr toolFrame_for_inputSignal = toolFrame::ptr(new toolFrame(ep, H, user_copy, report, intermediate, randomGenObject));	//Opens a MatLab Engine Connection locally from toolFrame


	std::list<struct timeseries_all_var> initial_simulation_timeSeriesData;

	// Creating object of user_inputs_helper class for calling helper functions
	user_inputs_helper::ptr user_inputs_helper_object = user_inputs_helper::ptr(new user_inputs_helper());
	initial_simulation_timeSeriesData = user_inputs_helper_object->generate_input_signals(ep, params);  //create init_poly in this function
	//initial_simulation_timeSeriesData = toolFrame_for_inputSignal->generate_input_signals();  //create init_poly in this function


	//polytope::ptr initial_poly = toolFrame_for_inputSignal->getInitialPolytope(); //using init_poly created in the above line
	polytope::ptr initial_poly = params->getInitPoly(); //using init_poly created in the above line. todo: verify if params retains the value of init_poly


	std::list<struct timeseries_all_var>::iterator it_single_simu = initial_simulation_timeSeriesData.begin();
	std::list<struct timeseries_input> inputVar_init_point = (*it_single_simu).timeseries_signal;	//here we only have a single simulation, so iteration->begin() is fine.

	std::list< std::vector<double> > initial_points = getInternalPoints(initial_poly, user_copy->getSimuInitSize(), randomGenObject);
	//-------------------             ---------------------

	std::list< std::vector<double> >::iterator it=initial_points.begin();
	std::vector<double> initial_output_values =  (*it);


	//Todo: better use this for the above lines, but fix for single simulation : generate_input_information(inputVar_init_point, initial_output_values);

	if (user_copy->getEngine()=="txt2slx") {
			//model->createSmallScriptFile_ForFixedOutput();	// Now creating script file for later running the simulation and obtaining output-file having fixed time-step
		//Creating a script file for Running the simulink model just created.
		model->createSetupScriptFile(inputVar_init_point, initial_output_values);
	}

}
