/*
 * equivalence_testing.cpp
 *
 *  Created on: 22-Feb-2023
 *      Author: amit
 */

#include "equivalence_testing.h"

equivalence_testing::equivalence_testing() {
	// TODO Auto-generated constructor stub

}

equivalence_testing::~equivalence_testing() {
	// TODO Auto-generated destructor stub
}


/* Generates script file for running the simulink model for the given simulink model_filename
 * This function is used in engine:
 * 		equi-test
 *
 */
void equivalence_testing::generate_run_script_file(std::string model_filename, parameters::ptr params) {

	intermediateResult::ptr intermediate = params->getIntermediate();
	user_inputs::ptr userInputs = params->getUserInputs();
	hybridAutomata::ptr H = params->getH();


	simulinkModelConstructor::ptr model = simulinkModelConstructor::ptr(new simulinkModelConstructor(H, userInputs, intermediate));
	// ---------- Create run_script from .slx model
	std::string script_filename = "run_script_", script_extension=".m", output_filename="result_", result_extension=".txt";
	//Note: this hard-coded filenames if required to be changed, also change in the function below engineSelector::selectEquiTest().
	std::string filename_without_extension;
	size_t found = model_filename.find(".");	//extract .slx from the model file
	if (found != string::npos){
		filename_without_extension = model_filename.substr(0, found);
	}
	script_filename.append(filename_without_extension);	//user supplied simulink-model filename without extension
	script_filename.append(script_extension);	//.m extension appended

	output_filename.append(filename_without_extension);
	output_filename.append(result_extension);

	model->create_runScript_for_simu_engine(model_filename, script_filename, output_filename);

	// ------------------------------------------------------------------------


}

/*
 * This function is used in engine:
 * 		equi-test
 *
 */
/*
void equivalence_testing::generate_script_files(parameters::ptr params){

	intermediateResult::ptr intermediate = params->getIntermediate();
	user_inputs::ptr userInputs = params->getUserInputs();


	// ---------- few Path setting for execution to create the .slx model
	linux_utilities::ptr linux_util = linux_utilities::ptr (new linux_utilities());
	intermediate->setMatlabDefaultPath(linux_util->getCurrentWorkingDirectoryWithPath());
	intermediate->setToolRootPath(linux_util->getParentWorkingDirectoryWithPath());
	std::string  learned_path ="";
	//cout << "pwd = " << linux_util->getCurrentWorkingDirectoryWithPath() << endl;
	learned_path.append(linux_util->getCurrentWorkingDirectoryWithPath());	//either Release or Debug
//	learned_path.append("/");		Maybe for now, engine==equi-test, we do not want to create any folder, just output in the Release folder
//	learned_path.append(intermediate->getOutputfilenameWithoutExtension());
	intermediate->setMatlabPathForLearnedModel(learned_path);	//todo: currently for engine=='equi-test', we will use interface for LearnedModel
	// ------------------------------------------------------------------------

	std::list<std::string> model_files = userInputs->getSimulinkModelFilenames();
	assert(model_files.size()==2);	//Two model file should be provided to run Equivalence Test
	std::list<std::string>::iterator it=model_files.begin();
	std::string model_file_one = (*it);
	it++; //next iterator for next model filename
	std::string model_file_two = (*it);
	// ------------------------------------------------------------------------
	generate_run_script_file(model_file_one, params);	// ----- Create first run_script from .slx model
	generate_run_script_file(model_file_two, params);	// ----- Create second run_script from .slx model

	// ------------------------------------------------------------------------

}
*/

