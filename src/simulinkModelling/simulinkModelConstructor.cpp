/*
 * simulinkModelConstructor.cpp
 *
 *  Created on: 20-Oct-2021
 *      Author: amit
 */

#include "simulinkModelConstructor.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/stat.h>


void simulinkModelConstructor::printSimulinkModelFile() {

//		extern  unsigned int log_set;
//		std::ofstream log_file("bbc4cps_log_file.txt",  std::ios_base::binary | std::ios_base::app);

	std::string outfile="";

	if (user->getEngine() == "txt2slx") {
		/* if the modelfile supplied by user have absolute or sub path like ../src/testcases/engine/txt2slx/raj.txt
			then, first search the character '/' if found find the position of the last '/' and extract rest character and then extract the extension as done below.
		*/
		std::string outfilename = user->getModelFilename(); //Model file in .txt form supplied by the user
		size_t found = outfilename.rfind("/");	//find if '/' is present from reverse of the string
		if (found != string::npos) { //when found
			outfilename = outfilename.substr (found+1); //from found position+1 rest all substr extract
			//cout << "last part of the filename =" << outfilename << endl;
			//Now, extract the filename without extension
			size_t pos = outfilename.rfind(".");	//extract file-name from extension
			if (pos != string::npos) {
				outfilename = outfilename.substr (0,pos);
			}
		} else {	//only extract the filename without extension
			size_t found = outfilename.rfind(".");	//extract file-name from extension
			if (found != string::npos) {
				outfilename = outfilename.substr (0,found);
			}
		}

		outfile = outfilename;
		//cout <<"Outputfile name =" << outfile << endl;
		intermediate->setOutputfilenameWithoutExtension(outfile);
		//Create a folder by the file name and put the .slx model file inside it
		std::string createCommand = "";
		createCommand.append("mkdir ");
		createCommand.append(outfile);
		int x = system(createCommand.c_str());
		if (x == -1) {
			std::cout <<"Error executing cmd: " << createCommand << std::endl;
		}

	} else if ((user->getEngine() == "learn-ha") || (user->getEngine() == "learn-ha-loop")) {
		std::string outfileName = user->getOutputFilename();	//created learned model
		size_t pos = outfileName.rfind(".");	//extract file-name from extension
		if (pos != string::npos) {
			outfile= outfileName.substr (0,pos);
		}

		//cout <<"Outputfile name =" << outfile << endl;
		intermediate->setOutputfilenameWithoutExtension(outfile);
		//Create a folder by the file name and put the .slx model file inside it
		std::string createCommand = "";
		createCommand.append("mkdir ");
		createCommand.append(outfile);
		struct stat sb; int flag=0;
		if (stat(outfile.c_str(), &sb) ==0 && S_ISDIR(sb.st_mode)){
			flag=1;
		} else {
			int x = system(createCommand.c_str());
			if (x == -1) {
				std::cout <<"Error executing cmd: " << createCommand << std::endl;
				exit(EXIT_FAILURE);
			}
//			else {
//	            cout << "Folder created!" << endl;
//	        }

		}


	} else {	//executed for engine="bbc"
		outfile = intermediate->getOutputfilenameWithoutExtension();
			//Folder already created during verification Process for dReach model, so dump simulink model in this folder
		std::string command = "";
		command.append("cd ");
		command.append(outfile);
		int x = system(command.c_str());
		if (x == -1) {
			cout <<"Error executing cmd: " << command << std::endl;
		}
	}
	//*****************************************

	std::string fileName_with_path = "", scipt_file_with_path = "", model_file_with_path = "";
	fileName_with_path.append(outfile);	//this is the folder-name
	fileName_with_path.append("/");

	scipt_file_with_path=fileName_with_path;
	scipt_file_with_path.append("getModel_");
	scipt_file_with_path.append(outfile);
	scipt_file_with_path.append(to_string(iteration));

	fileName_with_path.append(outfile);
	fileName_with_path.append(to_string(iteration));

	//scipt_file_with_path = fileName_with_path;
	model_file_with_path = fileName_with_path;

	scipt_file_with_path.append(".m");	//script file that generates the simulink model
	model_file_with_path.append(".slx");	//simulink model filename

	//*****************************************
	//std::cout<<"Creating file with path = " << scipt_file_with_path << std::endl;
	//std::cout<<"Creating file with path = " << model_file_with_path << std::endl;

	std::string outfile_withoutExtension = intermediate->getOutputfilenameWithoutExtension();

	simulinkModelName = outfile_withoutExtension.append(std::to_string(iteration));

	std::string script_file_withoutExtension = "getModel_";
	script_file_withoutExtension.append(intermediate->getOutputfilenameWithoutExtension());
	script_file_withoutExtension.append(std::to_string(iteration));
	script_for_simulinkModelName = script_file_withoutExtension;

	intermediate->setSimulinkScriptFilenameWithPath(scipt_file_with_path); //This is not required and is not used, since it is called by just the name.
	intermediate->setSimulinkModelFilenameWithPath(model_file_with_path);

	/*std::string learned_model_path = intermediate->getMatlabDefaultPath();	//This is also done outside
	std::cout <<"****** Default path = " <<learned_model_path << std::endl;
	learned_model_path.append("/");
	learned_model_path.append(outfile);
	std::cout <<"****** Modified path = " <<learned_model_path << std::endl;
	intermediate->setMatlabPathForLearnedModel(learned_model_path);	*/

	//cout <<"****** scipt_file_with_path = "<< scipt_file_with_path <<" **********"<<endl;
	//cout <<"****** script_for_simulinkModelName = "<< script_for_simulinkModelName <<" **********"<<endl;

	ofstream modelfile;
	modelfile.open(scipt_file_with_path);
	if (modelfile.is_open()) {
		//std::cout << "\nFile " << scipt_file_with_path << " created for Matlab (Simulink Model Creation) ...\n";
		//std::cout << "\nFile " << model_file_with_path << " created (Simulink Model) ...\n";
		modelfile << "%% Script file for generating Programmatically Simulink Model!";
		modelfile << "\n";
		generateSimulinkModelScript(modelfile);

	} else {
		std::cout << "Error opening file: " << scipt_file_with_path;
	}

	modelfile.close();
	//std::cout << "\n Script file created ...\n";


}

void simulinkModelConstructor::generateSimulinkModelScript(ofstream &outfile){
	printDefinition(outfile);	//prints the header information

	unsigned int oneVersusOne_oneVersusRest = 1;	//1 for One-Versus-One and 2 for One-Versus-Rest


	if (ha->getTotalLocations() == 3 && oneVersusOne_oneVersusRest==2) {	//Create random Matlab function only when non-deterministic situation arise
		addMatlabFunction(outfile);
	}

	addLocations(outfile);
	addTransitions(outfile);
	addDefaultTransition(outfile);
	variableCreation(outfile);

	//Output ports from the Chart to be connected using lines to the outputComponents
	outfile << "\n\n";
	outfile << "chartOutSignal = get_param('"<< simulinkModelName << "/Chart', 'PortHandles'); \n";
	outfile << "\n\n";
	addInputComponents(outfile);  // when model has input variables
	addOutputComponents(outfile);
	//addConnectionLines(outfile);


	outfile << "\n\n";
	outfile << "Simulink.BlockDiagram.arrangeSystem('"<< simulinkModelName << "'); \n";
	outfile << "Simulink.BlockDiagram.arrangeSystem('"<< simulinkModelName << "/Chart'); \n";

	outfile << "\n\n";
	outfile << "sfsave; \n";
	outfile << "sfclose; \n";
	outfile << "close_system; \n";
	outfile << "bdclose all; \n";
}

void simulinkModelConstructor::printDefinition(ofstream &outfile) {
	//std::cout <<"outfile =" << std::endl;
	string variable_name = "";
	/*string outfile_withoutExtension = intermediate->getOutputfilenameWithoutExtension();
	simulinkModelName = outfile_withoutExtension.append(std::to_string(iteration));*/ //Already done

	outfile << "bdclose all; \n";
	//outfile << "sfnew " << outfile_withoutExtension << iteration << "; \n";
	outfile << "sfnew " << simulinkModelName << "; \n";
	outfile << "rt = sfroot; \n";
	outfile << "ch = find(rt,'-isa','Stateflow.Chart'); \n";
	//outfile << "set_param(bdroot, 'StopTime', 'timeFinal', 'MaxStep', 'timeStepMax'); \n";  //This is for variable-step with MaxStep as timeStepMax
//Working with Fixed-step	outfile << "set_param(bdroot, 'SolverType','Fixed-step', 'StopTime', 'timeFinal', 'FixedStep', 'timeStepMax'); \n";  //This is for Fixed-step size

	if (user->getOdeSolverType()=="variable") {
		//std::cout <<"ODE Solver Type: Variable-step" << std::endl;
		//This makes the model Variable-step
		outfile << "set_param(bdroot, 'SolverType','Variable-step', 'StopTime', 'timeFinal', ";
		outfile << "'SolverName', '" << user->getOdeSolver() <<"'";	// replaced by user decided ODE Solver such as 'ode15s' or 'ode45'.
		//Supported variable-solver are: 'ode15s'/'ode23s'/'ode23t'/'ode23tb'/'ode45'/'ode23'/'ode113'/'odeN'
		outfile << ", 'MaxStep', 'timeStepMax'); \n";  //This is for Variable-step with solver ode15s (stiff/NDF)
		//outfile << "set_param(bdroot, 'StopTime', 'timeFinal', 'FixedStep', 'timeStepMax'); \n";  //This is for Fixed-step size

	} else if (user->getOdeSolverType()=="fixed") {
		//std::cout <<"ODE Solver Type: Fixed-step" << std::endl;
		//This makes the model Fixed-step
		outfile << "set_param(bdroot, 'SolverType','Fixed-step', 'StopTime', 'timeFinal', ";
		outfile << "'SolverName', '" << user->getOdeSolver() <<"'";	// replaced by user decided ODE Solver.
		//Supported fixed-solver are: 'ode14x'/'ode1be'/'ode1'/'ode2'/'ode3'/'ode4'/'ode5'/'ode8'
		outfile << ", 'FixedStep', 'timeStepMax'); \n";  //This is for Variable-step with solver ode15s (stiff/NDF)
		//outfile << "set_param(bdroot, 'StopTime', 'timeFinal', 'FixedStep', 'timeStepMax'); \n";  //This is for Fixed-step size
	}

	outfile << "ch.ActionLanguage = 'C'; \n";
	outfile << "ch.ChartUpdate = 'CONTINUOUS'; \n";
	outfile << "ch.EnableZeroCrossings = 0; \n";
	outfile << "ch.ExecuteAtInitialization = true; \n";
}

void simulinkModelConstructor::addMatlabFunction(ofstream &outfile) {
	outfile << " \n \n %% Adding a Matlab Function that generates random number in the range -2 to +2 \n \n";
	outfile << "function1 = Stateflow.EMFunction(ch); \n";
	outfile << "function1.LabelString = 'rOut = myRandomOut()'; \n";
	outfile << "function1.Position = [10 390 120 60]; \n";
	outfile << "str = ['function rOut=myRandomOut()',10, ... \n";
	outfile << "    'a=-2; %staring number-Range',10, ... \n";
	outfile << "    'b=2;  %ending number-Range',10, ... \n";
	outfile << "    'N=1;  %number of outputs',10, ... \n";

	outfile << "    'coder.cinclude(\"time.h\")',10, ... \n";
	outfile << "    'sd=0;',10, ... \n";
	outfile << "    'sd=coder.ceval(\"time\",[]);',10, ... \n";
	outfile << "    'rng(sd,\"twister\");',10, ... \n";

	outfile << "    'rOut = a + (b-a) * rand(N,1);',10, ... \n";
	outfile << "    'Nn=rOut;',10, ... \n";	//This line is just to add Manual break-point for debug
	outfile << "    'end']; \n";
	outfile << "function1.Script=str; \n";
	}

void simulinkModelConstructor::addLocations(ofstream &outfile){

	outfile << " \n \n %% Adding Locations or States with ODE \n";

	std::map<int, location::ptr> list_locations;
	list_locations = ha->getLocation_List();

	unsigned int pos_x=30, pos_y=30, width=90, height=60, state_gap = 100;

	for (std::map<int, location::ptr>::iterator i = list_locations.begin(); i != list_locations.end(); i++) {

		location::ptr loc = (*i).second;	//since our location starts from 1
		outfile << "loc" << loc->getLocId() << " = Stateflow.State(ch); \n";
		//Calculate the position properly later (dynamicall)
		//outfile << "loc" << loc->getLocId() << ".Position = [30 30 90 60];";
		outfile << "loc" << loc->getLocId() << ".Position = [" << pos_x << " " << pos_y << " " << width << " " << height <<"]; \n";

		outfile << "str = ['" << "loc" << loc->getLocId() << "', 10, ... \n";	//10 here is ASCII char indicate newline char
		outfile << " 'du: ', 10, ... \n";
		//Now get the ODE for each variable_dot
		list<flow_equation> derivatives = loc->getDerivatives();
		//int var_index=0; // fixing this hard-coded indexing approach
		string variableName="", prime_variableName;
		size_t pos;

		//Loop for during block
		//cout <<"var_index = " << var_index << endl;
		for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
			prime_variableName = (*it_flow).varName;	//eg x0'
			pos = prime_variableName.find("'");
			variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol

			//cout<<"Flow:RHS "<<(*it_flow).RHSexpression<<endl;
			//variableName = ha->get_varname(var_index);
			if (!(user->isInputVariable(variableName))) {	//print ode only for output variables and not for input variables
				//outfile << " '    " << ha->get_varname(var_index) << "_dot = ";
				outfile << " '    " << variableName << "_dot = ";
				outfile << (*it_flow).RHSexpression << ";', 10, ...  \n";
			}
			//var_index++;
		}

		//Loop for exit block
		//var_index=0;
		outfile << " 'exit: ', 10, ... \n";
		for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
			prime_variableName = (*it_flow).varName;	//eg x0'
			pos = prime_variableName.find("'");
			variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol

			//variableName = ha->get_varname(var_index);
			if (!(user->isInputVariable(variableName))) {	//print ode only for output variables and not for input variables
				//outfile << " '    " << ha->get_varname(var_index) << "_out = ";
				outfile << " '    " << variableName << "_out = ";
				//outfile << ha->get_varname(var_index) << ";', 10, ...  \n";
				outfile << variableName << ";', 10, ...  \n";
			}
			//var_index++;
		}
		outfile << " ]; \n";
		outfile << "loc" << loc->getLocId() << ".LabelString = str; \n";

		pos_x = pos_x + width + state_gap;

		outfile <<"\n \n";	//Adding blank lines between locations
	}
}

void simulinkModelConstructor::addTransitions(ofstream &outfile) {
	outfile << " \n \n %% Adding Transition for each Locations or States \n";

	std::map<int, location::ptr> list_locations;
	list_locations = ha->getLocation_List();
	unsigned int pos_x=30, width=90, state_gap = 100;
	unsigned int x_pos = pos_x + width + state_gap * 0.5, y_pos=0, next_height = 16;
	unsigned int sourceLoc = 0;
	unsigned int number_of_loop_trans=0;
	double different_position = 1.1;
	for (std::map<int, location::ptr>::iterator i = list_locations.begin(); i != list_locations.end(); i++) {
		//addMainTransitions(outfile); Maybe I should do it in this function itself

		sourceLoc = (*i).second->getLocId();
		list<transition::ptr> trans = (*i).second->getOutGoingTransitions();
		std::string reset_statement_identity = "";	//write a simple function for identity reset and call here
		std::string reset_statement = "";
		//cout <<"====== Outgoing transition ======"<<endl;
		outfile <<"\n %%Transitions for Location loc" << sourceLoc << " \n";
		unsigned int exec_order = 1;
		double sourceOClock = 3.1 + different_position; //start value Todo: proper calculation needed
		different_position += 1.1;
		//If the model is a Single Location with no Transitions this Loop will not be executed
		unsigned int transition_count = 0;
		std::list<std::string> list_guardToInvariant; // equality guard to NotEquality guard for locations' invariant (Matlab's unconditional fixes)
		// However, this fix is not correct when given guard is other than equality guard. For eg x >= 7. Here replacing Not will not work out.
		// Better, fix is to use the actual invariant of the location and replace it. So, here we must have invariant given.
		for (list<transition::ptr>::iterator it_trans = trans.begin(); it_trans != trans.end(); it_trans++) {
			assert(sourceLoc == (*it_trans)->getSourceLocationId());
			//assert(sourceLoc != (*it_trans)->getDestinationLocationId()); //if same should call addLoopTransitions()


			// ************* Using the Modified Guard which replace Equality guard into inequality guard for fixing MATLAB's issue *********
			//Note: converted equality into range by epsilon
			std::list<std::string> guard_modified = (*it_trans)->getGuardModified();

			string inequality_guard = "";
			unsigned int const_count = guard_modified.size(), count=0;
			for (std::list<std::string>::iterator g_modified = guard_modified.begin(); g_modified != guard_modified.end(); g_modified++){
				inequality_guard.append(*g_modified);
				count++;
				if ((const_count > 1) && (count < const_count)){
					inequality_guard.append(" && ");
				}
			}
			reset_statement_identity = resetPrinter();	//Prints a simple identity reset equations. This is used below, in the invariant-loop-transition
			reset_statement = resetPrinter((*it_trans)->getAssignment());	//Prints reset equations from a list of reset equations


			if (sourceLoc == (*it_trans)->getDestinationLocationId()) { //this means it's a Loop Transition
				addLoopTransitions(outfile, sourceLoc, number_of_loop_trans, exec_order, pos_x, next_height, inequality_guard, reset_statement);
				number_of_loop_trans++;
			} else {  //not a loop transition

				outfile << "    t" << (*it_trans)->getTransId() << " = Stateflow.Transition(ch); \n";
				outfile << "    t" << (*it_trans)->getTransId() << ".Source = loc" << sourceLoc << "; \n";
				outfile << "    t" << (*it_trans)->getTransId() << ".Destination = loc" << (*it_trans)->getDestinationLocationId() << "; \n";
				outfile << "    t" << (*it_trans)->getTransId() << ".ExecutionOrder = " << exec_order << "; \n";
				outfile << "    t" << (*it_trans)->getTransId() << ".SourceOClock = " << sourceOClock << "; \n";
				outfile << "    t" << (*it_trans)->getTransId() << ".LabelPosition = [" << x_pos << " " << y_pos <<" 31 "<< next_height <<"]; \n";

				/*
				 *
				std::list<std::string> guard = (*it_trans)->getGuard();
				list<std::string>::iterator it_guard = guard.begin();

				//Here we are assuming all guard is with "guard_str_with_equal_zero", then converting it to "~="
				string guard_str_with_equal_zero = (*it_guard), guard_with_equalequal_zero, guard_with_not_equal_zero;
				guard_with_equalequal_zero = guard_str_with_equal_zero;
				unsigned int pos = guard_str_with_equal_zero.find("=");
				guard_with_equalequal_zero.replace(pos, 1, "==");
				guard_with_not_equal_zero = guard_str_with_equal_zero;
				guard_with_not_equal_zero.replace(pos, 1, "~=");
				list_guardToInvariant.push_back(guard_with_not_equal_zero);
				*/
				//outfile << "    t" << (*it_trans)->getTransId() << ".LabelString = '[ " << guard_with_equalequal_zero << "]"; //Matlab failed to hit this guard


				outfile << "    t" << (*it_trans)->getTransId() << ".LabelString = '[ " << inequality_guard << "]";
				// ************* Using the Modified Guard which replace Equality guard into inequality guard for fixing MATLAB's issue *********

				outfile << reset_statement<<"'; \n";

			}

			exec_order++;
			sourceOClock +=2; //Randomly added 2. Note OClock value ranges from 0 to 12, clock values.
			y_pos +=next_height; //height of the Transition Label is set as 16. Need to check later
			transition_count++;	//counts the number of transitions
		}

		//exec_order this will be for loop-transtions now

		//****** addLoopTransitions(outfile); //This is the Invariant Loop ******
		outfile <<"\n \n";	//Adding blank lines before Invariants handling (using Connectives-Self Loops)
		outfile <<"%% Adding Loop Transition to represent Invariant Condition \n";
		outfile << "c" << sourceLoc << "_" << number_of_loop_trans << " = Stateflow.Junction(ch); \n";
		outfile << "c" << sourceLoc << "_" << number_of_loop_trans << ".Position.Center = [" << pos_x - 20 << " 0]; \n";
		outfile << "c" << sourceLoc << "_" << number_of_loop_trans << ".Position.Radius = 10; \n";

		outfile <<"\n";	//Adding blank lines
		outfile << "ca" << sourceLoc << "_" << number_of_loop_trans << " = Stateflow.Transition(ch); \n";
		outfile << "ca" << sourceLoc << "_" << number_of_loop_trans << ".Source = loc" << sourceLoc << "; \n";
		outfile << "ca" << sourceLoc << "_" << number_of_loop_trans << ".Destination = c" << sourceLoc << "_" << number_of_loop_trans << "; \n";

		outfile <<"\n";	//Adding blank lines
		outfile << "cb" << sourceLoc << "_" << number_of_loop_trans << " = Stateflow.Transition(ch); \n";
		outfile << "cb" << sourceLoc << "_" << number_of_loop_trans << ".Source = c" << sourceLoc << "_" << number_of_loop_trans << "; \n";
		outfile << "cb" << sourceLoc << "_" << number_of_loop_trans << ".Destination = loc" << sourceLoc << "; \n";
		outfile << "cb" << sourceLoc << "_" << number_of_loop_trans << ".LabelPosition = [" << pos_x - 20 << " " << 10 <<" 31 "<< next_height <<"]; \n";
		//outfile << "cb" << sourceLoc << ".LabelString = '" << reset_statement<<"'; \n";
		if (transition_count == 0) {
			outfile << "cb" << sourceLoc << "_" << number_of_loop_trans << ".LabelString = '" << reset_statement_identity<<"'; \n";
		} else { //For one or more transitions
			/*Get all guards (for multiple transitions and convert it into in-equilatity (~=) and concatenate with || */
			//Now it is better by replacing with the actual invariant constraints
			//------------ new code --------------
			std::string condition_str="";
			std::list<std::string> inv_list = (*i).second->getInvariant();
			unsigned int inv_count = inv_list.size(), cnt=0;
			if (user->getInvariant() == 0) {	//include both input and output constraints as invariant
				for (std::list<std::string>::iterator it_guard_inv = inv_list.begin(); it_guard_inv != inv_list.end(); it_guard_inv++) {
					condition_str.append((*it_guard_inv));
					//cout << "condition_str = " <<condition_str << endl;
					if ((inv_count > 1) && (cnt < (inv_count - 1))) {
						condition_str.append(" && "); 	// && since when all other outgoing transition are not satisfied then the loop/inv transitions takes
					}
					cnt++;	//since all condition are included so count increments for each loop
				}
			} else if (user->getInvariant() == 1) {	//include only output constraints and remove input constraints as invariant
				/*
				 * check the constraint, I assume all constraints is of the form "left op val", where left is the variable involving the constraint, op is the operator
				 * valid operators are  >=, <= etc and val is the numeric value
				 * So, just check if the left is in input-variable list in the variable-mapping then discard this constraint, otherwise include it.
				 */
				std::string variableName;
				for (std::list<std::string>::iterator it_guard_inv = inv_list.begin(); it_guard_inv != inv_list.end(); it_guard_inv++) {

					variableName = getVariableComponent((*it_guard_inv));

					if (!(user->isInputVariable(variableName))) {
						if ((cnt>=1) && (inv_count > 1) && (cnt <= (inv_count - 1))) {
							condition_str.append(" && "); 	// && since it is possible that after the 1st condition remaining may not satisfy so && should not be added
						}
						condition_str.append((*it_guard_inv));
						//cout << "condition_str = " <<condition_str << endl;

						cnt++;
					}



				}
			}


			//Here checking is done to either remove or include the invariant constraints
			if (user->getInvariant() == 0 || user->getInvariant() == 1) {
				outfile << "cb" << sourceLoc << "_" << number_of_loop_trans << ".LabelString = '[" << condition_str << "]" << reset_statement_identity<<"'; \n";
			} else if (user->getInvariant() == 2) {
				outfile << "cb" << sourceLoc << "_" << number_of_loop_trans << ".LabelString = '" << reset_statement_identity<<"'; \n";
			}

			// ------------------------------------






			/* Old code: used simple conjunction of other guards with their negation
			 * std::string condition_str="";
			std::list<std::string>::iterator list_guard_inv = list_guardToInvariant.begin();
			for (unsigned int cnt = 0; cnt < transition_count; cnt++) {
				condition_str.append((*list_guard_inv));
				if ((transition_count > 1) && (cnt < (transition_count - 1))){
					//condition_str.append(" || ");
					condition_str.append(" && "); 	//modified to && since when all other outgoing transition are not satified then the loop transitions takes
				}
				list_guard_inv++;
			}
			outfile << "cb" << sourceLoc << ".LabelString = '[" << condition_str << "]" << reset_statement_identity<<"'; \n";*/
		}
		number_of_loop_trans++;	//every location has a loop-transition that represents an invariant

		pos_x = pos_x + width + state_gap;	//Next Location/State 's Position
	} //End of all Locations
}

/*
 * I assume Input is a constraint string of the form "left op val", where left is the variable involving the constraint, op is the operator
 * valid operators are  >=, <= etc and val is the numeric value
 * Returns left which is a variable name.
 */
std::string simulinkModelConstructor::getVariableComponent(std::string constriant_str) {

	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(" ");
	tokenizer tokens(constriant_str, sep);
	std::string var_component;
	tokenizer::iterator tok_iter = tokens.begin();
	var_component = (std::string) *tok_iter;	//access the first component which is left

	return var_component;
}



void simulinkModelConstructor::addDefaultTransition(ofstream &outfile) {
	unsigned int init = ha->getInitialId();
	outfile <<"\n \n";	//Adding blank lines
	outfile <<"%% Default or Initial Transition \n";
	outfile << "init" << init << " = Stateflow.Transition(ch); \n";
	outfile << "init" << init << ".Destination = loc" << init << "; \n";

	std::string initialValues = generateInitialValues();
	outfile << "init" << init << ".LabelString = '" << initialValues << "'; \n"; //Note a0, a1 are the initial values for the variable;
	outfile << "init" << init << ".DestinationOClock = 0; \n";
	outfile << "init" << init << ".SourceEndpoint = init" << init << ".DestinationEndpoint - [0 30]; \n";
	outfile << "init" << init << ".Midpoint = init" << init << ".DestinationEndpoint - [0 15]; \n";

}

std::string simulinkModelConstructor::generateInitialValues() {
	std::string init_str="";
	//Read any one of the location and parse through the ODE's varName this contains the prime-variable


	init_str.append("{");

/*	location::ptr loc = ha->getLocation(1);	//since our location starts from 1
	list<flow_equation> derivatives = loc->getDerivatives();
	unsigned int val = 0;
	//our Learned Model's variable start from x0, x1, etc. So, similarly initial values are a0, a1, etc.
	for (std::list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
		std::string prime_variableName = (*it_flow).varName;	//eg x0'
		size_t pos = prime_variableName.find("'");
		std::string variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol
		if (!(user->isInputVariable(variableName))) {	//print only for output variables and not for input variables
			init_str.append(variableName);
			init_str.append(" = a");
			init_str.append(std::to_string(val));
			init_str.append("; ");
		}
		val++;
	}*/
	//The above approach has issue with naming "aindex"

	for (unsigned int index=0; index < ha->map_size(); index++) {
		std::string variableName = ha->get_varname(index);
		if (!(user->isInputVariable(variableName))) {	//print only for output variables and not for input variables
			init_str.append(variableName);
			init_str.append(" = a");
			init_str.append(std::to_string(index));
			init_str.append("; ");
		}
	}
	init_str.append("}");



	return init_str;
}

void simulinkModelConstructor::variableCreation(ofstream &outfile) {
	outfile <<"\n\n %% *** Variable Declaration Block **** \n";	//Adding blank lines
	inputVariableCreation(outfile); //when model has input variables
	outputVariableCreation(outfile);
	localVariableCreation(outfile);
	parameterVariableCreation(outfile);
}


void simulinkModelConstructor::addInputComponents(ofstream &outfile) {
	//Read the data_structure listVariableTypeMapping supplied by the user
	std::list<std::string> inputVariables = user->getListInputVariables();

	outfile <<"\n %% *** Adding Input  components **** \n";
	unsigned int y_pos=18, height=33, next_height=40;
	unsigned int number_of_input_variables= inputVariables.size(), portNo = 1;	// Assuming the order is maintained
	//cout <<"number_of_input_variables="<<number_of_input_variables <<endl;
	if (number_of_input_variables >= 1) {
		for (list<std::string>::iterator it = inputVariables.begin(); it != inputVariables.end(); it++) {
			string variableName = *it;	//extract the variable name
			outfile << "add_block('simulink/Sources/In1', '" << simulinkModelName << "/" << variableName << "In'); \n";
			outfile << variableName << "Input = get_param('" << simulinkModelName << "/" << variableName <<"In', 'PortHandles'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"In', 'Port', '" << portNo << "'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"In', 'SignalType', 'auto'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"In', 'position', [-40, " << y_pos << ", 0, " << height << "]); \n";

			outfile <<"\n \n";	//Adding the line here itself
			outfile <<"add_line('" << simulinkModelName << "', " << variableName <<"Input.Outport(1), chartOutSignal.Inport(" << portNo << ")); \n";
			outfile <<"\n \n";

			height +=next_height;
			y_pos += next_height;
			outfile << "\n";
			portNo++;
		}
	}

}

//backup
/*
void simulinkModelConstructor::addOutputComponents(ofstream &outfile) {
	//The number of output components is equal to the number of variables. Not anymore now they are separate.
	//Read any one of the location and parse through the ODE's varName this contains the prime-variable
	location::ptr loc = ha->getLocation(1);	//since our location starts from 1
	list<flow_equation> derivatives = loc->getDerivatives();
	unsigned int portNo = 1;	// Assuming the order is maintained
	outfile <<"\n\n %% *** Adding Output components **** \n";
	unsigned int y_pos=18, height=33, next_height=40;

	//Chart connecting to output components
	for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
		string prime_variableName = (*it_flow).varName;	//eg x0'
		size_t pos = prime_variableName.find("'");
		string variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol

		if (!(user->isInputVariable(variableName))) {	//print reset only for output variables and not for input variables

			outfile << "add_block('simulink/Sinks/Out1', '" << simulinkModelName << "/" << variableName << "Out'); \n";
			outfile << variableName << "In = get_param('" << simulinkModelName << "/" << variableName <<"Out', 'PortHandles'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'SignalName', '" << variableName << "Out'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'Port', '" << portNo << "'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'SignalType', 'auto'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'position', [140, " << y_pos << ", 180, " << height << "]); \n";

			outfile <<"\n \n";	//Adding the line here itself
			outfile <<"add_line('" << simulinkModelName << "', chartOutSignal.Outport(" << portNo << "), " << variableName <<"In.Inport(1)); \n";
			outfile <<"\n \n";

			height +=next_height;
			y_pos += next_height;
			outfile << "\n";
			portNo++;
		}
	}
}
*/


void simulinkModelConstructor::addOutputComponents(ofstream &outfile) {
	//The number of output components is equal to the number of variables. Not anymore now they are separate.
	//Read any one of the location and parse through the ODE's varName this contains the prime-variable
	location::ptr loc = ha->getLocation(1);	//since our location starts from 1
	list<flow_equation> derivatives = loc->getDerivatives();
	unsigned int portNo = 1;	// Assuming the order is maintained
	outfile <<"\n\n %% *** Adding Output components **** \n";
	unsigned int y_pos=18, height=33, next_height=40;

	for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
		string prime_variableName = (*it_flow).varName;	//eg x0'
		size_t pos = prime_variableName.find("'");
		string variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol

		//connecting the output port of the Chart to input port of the Output component
		if (!(user->isInputVariable(variableName))) {	//for output variables
			//Creating an output-component for every variable (both input and output variables)
			outfile << "add_block('simulink/Sinks/Out1', '" << simulinkModelName << "/" << variableName << "Out'); \n";
			outfile << variableName << "Output = get_param('" << simulinkModelName << "/" << variableName <<"Out', 'PortHandles'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'SignalName', '" << variableName << "Out'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'Port', '" << portNo << "'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'SignalType', 'auto'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'position', [140, " << y_pos << ", 180, " << height << "]); \n";

			outfile <<"\n \n";	//Adding the line here itself
			outfile <<"add_line('" << simulinkModelName << "', chartOutSignal.Outport(" << portNo << "), " << variableName <<"Output.Inport(1)); \n";
			outfile <<"\n \n";
			height +=next_height;
			y_pos += next_height;
			outfile << "\n";
			portNo++;
		}

	}

/*	//portNo will follow the sequence Output variable followed by Input variables
	for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
		string prime_variableName = (*it_flow).varName;	//eg x0'
		size_t pos = prime_variableName.find("'");
		string variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol
		//connecting the output port of the Chart to input port of the Output component
		if ((user->isInputVariable(variableName))) {	//for input variables
			//Creating an output-component for every variable (both input and output variables)
			outfile << "add_block('simulink/Sinks/Out1', '" << simulinkModelName << "/" << variableName << "Out'); \n";
			outfile << variableName << "Output = get_param('" << simulinkModelName << "/" << variableName <<"Out', 'PortHandles'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'SignalName', '" << variableName << "Out'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'Port', '" << portNo << "'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'SignalType', 'auto'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'position', [140, " << y_pos << ", 180, " << height << "]); \n";

			outfile <<"\n \n";	//Adding the line here itself
			//Input components directly connecting to the output components. This is need so as to get the actual input data from MatLab simulation
			//port ID for input variables are ordered after output variables
			outfile <<"add_line('" << simulinkModelName << "', " <<variableName <<"Input.Outport(1), " << variableName <<"Output.Inport(1)); \n";
			outfile <<"\n \n";
			height +=next_height;
			y_pos += next_height;
			outfile << "\n";
			portNo++;
		}
	}*/

	//portNo will follow the sequence Output variable followed by Input variables
	std::list<std::string> inputVariables = user->getListInputVariables();
	unsigned int number_of_input_variables= inputVariables.size();
	if (number_of_input_variables >= 1) {
		for (list<std::string>::iterator it = inputVariables.begin(); it != inputVariables.end(); it++) {
			string variableName = *it;	//extract the variable name
			outfile << "add_block('simulink/Sinks/Out1', '" << simulinkModelName << "/" << variableName << "Out'); \n";
			outfile << variableName << "Output = get_param('" << simulinkModelName << "/" << variableName <<"Out', 'PortHandles'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'SignalName', '" << variableName << "Out'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'Port', '" << portNo << "'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'SignalType', 'auto'); \n";
			outfile << "set_param('" << simulinkModelName << "/" << variableName <<"Out', 'position', [140, " << y_pos << ", 180, " << height << "]); \n";
			outfile <<"add_line('" << simulinkModelName << "', " <<variableName <<"Input.Outport(1), " << variableName <<"Output.Inport(1)); \n";
			outfile <<"\n \n";
			height +=next_height;
			y_pos += next_height;
			outfile << "\n";
			portNo++;
		}
	}








}

/*void simulinkModelConstructor::addConnectionLines(ofstream &outfile){
	;
}*/

// ** Auxiliary functions **
/*void simulinkModelConstructor::addMainTransitions(ofstream &outfile){
	;
}*/

void simulinkModelConstructor::addLoopTransitions(ofstream &outfile, unsigned int sourceLoc, unsigned int number_loop_trans, unsigned int exec_order, unsigned int pos_x,
		unsigned int next_height, std::string condition_str, std::string reset_str) {
	outfile <<"%% Transition to represent Invariants: Current fix is using Junction Connection to avoid inner Transitions \n";
	pos_x += 10;
	next_height += 10;
	string junction_object_name = "c";
	junction_object_name.append(to_string(sourceLoc));
	junction_object_name.append("_");
	junction_object_name.append(to_string(number_loop_trans));

	string trans_loc_to_junction="ca";
	trans_loc_to_junction.append(to_string(sourceLoc));
	trans_loc_to_junction.append("_");
	trans_loc_to_junction.append(to_string(number_loop_trans));

	string trans_junction_to_loc="cb";
	trans_junction_to_loc.append(to_string(sourceLoc));
	trans_junction_to_loc.append("_");
	trans_junction_to_loc.append(to_string(number_loop_trans));

	//exec_order this will be for loop-transtions now
	outfile <<"\n \n";	//Adding blank lines before Invariants handling (using Connectives-Self Loops)
	outfile <<"%% Adding Loop Transition to represent Invariant Condition \n";
	outfile << junction_object_name << " = Stateflow.Junction(ch); \n";
	outfile << junction_object_name << ".Position.Center = [" << pos_x - 20 << " 0]; \n";
	outfile << junction_object_name << ".Position.Radius = 10; \n";

	outfile <<"\n";	//Adding blank lines
	outfile << trans_loc_to_junction << " = Stateflow.Transition(ch); \n";
	outfile << trans_loc_to_junction << ".Source = loc" << sourceLoc << "; \n";
	outfile << trans_loc_to_junction << ".Destination = " << junction_object_name << "; \n";

	outfile <<"\n";	//Adding blank lines
	outfile << trans_junction_to_loc << " = Stateflow.Transition(ch); \n";
	outfile << trans_junction_to_loc << ".Source = " << junction_object_name << "; \n";
	outfile << trans_junction_to_loc << ".Destination = loc" << sourceLoc << "; \n";
	outfile << trans_junction_to_loc << ".LabelPosition = [" << pos_x - 20 << " " << 10 <<" 31 "<< next_height <<"]; \n";
	outfile << trans_junction_to_loc << ".LabelString = '[" << condition_str << "]" << reset_str<<"'; \n";

	//createConnectiveJunction(outfile);
	//completeLoopTransitions(outfile);
}

/*void simulinkModelConstructor::createConnectiveJunction(ofstream &outfile){
	;
}
void simulinkModelConstructor::completeLoopTransitions(ofstream &outfile){
	;
}*/


void simulinkModelConstructor::inputVariableCreation(ofstream &outfile){
	//Read the data_structure listVariableTypeMapping supplied by the user
	std::list<std::string> inputVariables = user->getListInputVariables();

	outfile <<"\n %% *** Input Variable Declaration **** \n";
	unsigned int number_of_input_variables= inputVariables.size(), portNo = 1;	// Assuming the order is maintained
	if (number_of_input_variables >= 1) {
		for (list<std::string>::iterator it = inputVariables.begin(); it != inputVariables.end(); it++) {
			string variableName = *it;	//extract the variable name

			outfile << variableName << "_in  = Stateflow.Data(ch); \n";
			outfile << variableName << "_in.Name = '" << variableName << "'; \n";
			outfile << variableName << "_in.Scope = 'Input'; \n";
			outfile << variableName << "_in.Port = " << portNo <<"; \n";
			outfile << variableName << "_in.Props.Type.Method = 'Inherit'; \n";
			outfile << variableName << "_in.DataType = 'Inherit: Same as Simulink'; \n";
			outfile << variableName << "_in.UpdateMethod = 'Discrete'; \n";

			outfile << "\n";
			portNo++;
		}
	}

}


void simulinkModelConstructor::outputVariableCreation(ofstream &outfile){
	//Read any one of the location and parse through the ODE's varName this contains the prime-variable
	location::ptr loc = ha->getLocation(1);	//since our location starts from 1
	list<flow_equation> derivatives = loc->getDerivatives();
	unsigned int portNo = 1;	// Assuming the order is maintained
	outfile <<"\n %% *** Output Variable Declaration **** \n";
	for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
		string prime_variableName = (*it_flow).varName;	//eg x0'
		size_t pos = prime_variableName.find("'");
		string variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol

		if (!(user->isInputVariable(variableName))) {	//print only for output variables and not for input variables
			outfile << variableName << "_out  = Stateflow.Data(ch); \n";
			outfile << variableName << "_out.Name = '" << variableName << "_out'; \n";
			outfile << variableName << "_out.Scope = 'Output'; \n";
			outfile << variableName << "_out.Port = " << portNo <<"; \n";
			outfile << variableName << "_out.Props.Type.Method = 'Inherit'; \n";
			outfile << variableName << "_out.DataType = 'Inherit: Same as Simulink'; \n";
			outfile << variableName << "_out.UpdateMethod = 'Discrete'; \n";
			outfile << "\n";
			portNo++;
		}
	}
}

void simulinkModelConstructor::localVariableCreation(ofstream &outfile){
	//Read any one of the location and parse through the ODE's varName this contains the prime-variable
	location::ptr loc = ha->getLocation(1);	//since our location starts from 1
	list<flow_equation> derivatives = loc->getDerivatives();
	outfile <<"\n\n %% *** Local Variable Declaration **** \n";	//Adding blank lines
	for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
		string prime_variableName = (*it_flow).varName;	//eg x0'
		size_t pos = prime_variableName.find("'");
		string variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol

		if (!(user->isInputVariable(variableName))) {	//print only for output variables and not for input variables

			outfile << variableName << " = Stateflow.Data(ch); \n";
			outfile << variableName << ".Name = '" << variableName << "'; \n";
			outfile << variableName << ".Scope = 'Local'; \n";
			outfile << variableName << ".UpdateMethod = 'Continuous'; \n";
			outfile << "\n";
		}
	}
}

unsigned int simulinkModelConstructor::getIteration() const {
	return iteration;
}

void simulinkModelConstructor::setIteration(unsigned int iteration) {
	this->iteration = iteration;
}

const string& simulinkModelConstructor::getSimulinkModelName() const {
	return simulinkModelName;
}

void simulinkModelConstructor::setSimulinkModelName(
		const string &simulinkModelName) {
	this->simulinkModelName = simulinkModelName;
}

void simulinkModelConstructor::parameterVariableCreation(ofstream &outfile){
	//Read any one of the location and parse through the ODE's varName this contains the prime-variable


	outfile <<"\n\n %% *** Parameter Variable Declaration **** \n";	//Adding blank lines
	/*
	location::ptr loc = ha->getLocation(1);	//since our location starts from 1
	list<flow_equation> derivatives = loc->getDerivatives();
	unsigned int val = 0;

	for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
		string prime_variableName = (*it_flow).varName;	//eg x0'
		size_t pos = prime_variableName.find("'");
		string variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol

		if (!(user->isInputVariable(variableName))) {	//print only for output variables and not for input variables

			outfile << "a" << val << " = Stateflow.Data(ch); \n";
			outfile << "a" << val << ".Name = 'a" << val << "'; \n";
			outfile << "a" << val << ".Scope = 'Parameter'; \n";
			outfile << "a" << val << ".Tunable = true; \n";
			outfile << "a" << val << ".Props.Type.Method = 'Inherit'; \n";
			outfile << "a" << val << ".DataType = 'Inherit: Same as Simulink'; \n";

			outfile << "\n";

		}
		val++;
	}*/

	for (unsigned int index=0; index < ha->map_size(); index++) {
		std::string variableName = ha->get_varname(index);
		if (!(user->isInputVariable(variableName))) {	//print only for output variables and not for input variables
			outfile << "a" << index << " = Stateflow.Data(ch); \n";
			outfile << "a" << index << ".Name = 'a" << index << "'; \n";
			outfile << "a" << index << ".Scope = 'Parameter'; \n";
			outfile << "a" << index << ".Tunable = true; \n";
			outfile << "a" << index << ".Props.Type.Method = 'Inherit'; \n";
			outfile << "a" << index << ".DataType = 'Inherit: Same as Simulink'; \n";

			outfile << "\n";
		}
	}



}

//Printing an identity mapping for reset equations
string simulinkModelConstructor::resetPrinter() {
	string reset_str="";
	//Read any one of the location and parse through the ODE's varName this contains the prime-variable

	location::ptr loc = ha->getLocation(1);	//since our location starts from 1
	list<flow_equation> derivatives = loc->getDerivatives();

	reset_str.append("{");
	for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
		string prime_variableName = (*it_flow).varName;	//eg x0'
		size_t pos = prime_variableName.find("'");
		string variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol

		if (!(user->isInputVariable(variableName))) {	//print reset only for output variables and not for input variables
			reset_str.append(variableName);
			reset_str.append(" = ");
			reset_str.append(variableName);
			reset_str.append("; ");
		}

	}
	reset_str.append("}");

	return reset_str;
}

std::string simulinkModelConstructor::resetPrinter(std::list<reset_equation> reset_list){
	std::string reset_str="";

	reset_str.append("{");
	for (std::list<reset_equation>::iterator it_reset = reset_list.begin(); it_reset != reset_list.end(); it_reset++) {
		string prime_variableName = (*it_reset).varName;	//eg x0'
		size_t pos = prime_variableName.find("'");
		string variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol

		if (!(user->isInputVariable(variableName))) {	//print reset only for output variables and not for input variables
			reset_str.append(variableName);
			reset_str.append(" = ");
			reset_str.append((*it_reset).RHSexpression);
			reset_str.append("; ");
		}

	}
	reset_str.append("}");

	return reset_str;;
}


int simulinkModelConstructor::executeSimulinkModelConstructor(std::unique_ptr<MATLABEngine> &ep) {
//int simulinkModelConstructor::executeSimulinkModelConstructor(Engine *ep) {

	//cout <<"Inside generateTraceFile function Engine &ep = "<< &ep <<endl;


	/*unsigned int  BUFSIZE = 256;
	char buffer[BUFSIZE+1];
	buffer[BUFSIZE] = '\0';
	engOutputBuffer(ep, buffer, BUFSIZE);
	int x = engEvalString(ep, "pwd");
	printf("Matlab PWD is %s", buffer);
	cout <<"Tool PWD is ";
	system("pwd");
	if (x == -1){
		std::cout <<"Matlab Execution Error: " << "pwd" << std::endl;
	}*/

	/*
	 * Note: when this function is called for the first time when the oscillator model is executed
	 * The Present-Working-Director of
	 * Matlab is : '/home/amit/workspace/BBC4CPS/src/benchmark/oscillator'
	 * Tool is : /home/amit/workspace/BBC4CPS/Release
	 * And the Target directory now for Equivalence Testing is obtained by
	 * 		cd ../../../Release/oscillator
	 */

	unsigned int execution_count = user->getNumberMatlabSimulationExecutedEquivalenceTest(); //todo: this is now also called from engine=learn-ha

	if (execution_count == 0) {	//running for the first time
		//cout <<"Running for the first iteration \n" << endl;
		string folderName = intermediate->getOutputfilenameWithoutExtension();
		//cout << "folderName="<< folderName << endl;
		/*string cmd1 = "addpath (genpath('../../../Release/";
		cmd1.append(folderName);	//I assume this will take with respect to the present-working-directory, i.e. Release
		cmd1.append("'))");
		cout << cmd1 << endl;*/

		//engEvalString(ep, "addpath (genpath('circle'))"); //Since tool BBC4CPS will be executed from Release or Debug
		string cmd1 = "addpath (genpath('";
		cmd1.append(intermediate->getMatlabPathForLearnedModel());
		cmd1.append("'))");
//		std::cout << cmd1 << endl;
		//x = engEvalString(ep, cmd1.c_str());
		ep->eval(convertUTF8StringToUTF16String(cmd1));
	}


	std::string cmd2="";
	//cmd2="cd('../../../Release/";
	//cmd2.append(folderName);
	//cmd2.append("')");
//	cout<< "Learned model path=" << intermediate->getMatlabPathForLearnedModel() << endl;
	//engEvalString(ep, "cd('../src/benchmark/circle')");
	cmd2="cd('";
	cmd2.append(intermediate->getMatlabPathForLearnedModel());
	cmd2.append("')");
	//cout << "cmd2=" << cmd2 << endl;
	ep->eval(convertUTF8StringToUTF16String(cmd2));

	// ------------------------------------ ******* ------------------------------------------
	//ep->eval(convertUTF8StringToUTF16String(simulinkModelName));
	ep->eval(convertUTF8StringToUTF16String(script_for_simulinkModelName)); //Executed the script file to create a simulink model file
	// ------------------------------------ ******* ------------------------------------------

	user->setNumberMatlabSimulationExecutedEquivalenceTest(execution_count + 1);

	ep->eval(u"sfclose;");
	ep->eval(u"bdclose all;");
	ep->eval(u"clear;");

	//printf("Simulink Model of the Learned Model created!!\n");

	return EXIT_SUCCESS;

}

const string& simulinkModelConstructor::getScriptForSimulinkModelName() const {
	return script_for_simulinkModelName;
}

void simulinkModelConstructor::setScriptForSimulinkModelName(
		const string &scriptForSimulinkModelName) {
	script_for_simulinkModelName = scriptForSimulinkModelName;
}

void simulinkModelConstructor::createSetupScriptFile(std::list<struct timeseries_input> init_point, std::vector<double> initial_output_values) {

/*
 * This file is called from the engine/module: txt2slx
 * This function creates a Matlab script file for running the .slx model generated by the engine txt2slx.
 * Since main function of the engine is to generate the .slx model and not perform simulation. Thus, the script file only contain sample code.
 */
	ofstream modelfile;
	std::string filePath = intermediate->getMatlabPathForLearnedModel();
	std::string filename = "run_";
	filename.append(intermediate->getOutputfilenameWithoutExtension());
	filename.append(to_string(iteration));
	//filename.append(to_string(user->getNumberMatlabSimulationExecutedEquivalenceTest()));
	filename.append(".m");
	std::string cmd = filePath; //Absolute path
	cmd.append("/");
	cmd.append(filename);
	modelfile.open(cmd);
	if (modelfile.is_open()) {
		std::cout << "\nFile " << cmd << " created for Matlab (Setting up and Execution of Simulink Model) ...\n";
		//std::cout << "\nFile " << model_file_with_path << " created (Simulink Model) ...\n";
		modelfile << "%% ******** Simulate Learned Model ******** \n";
		modelfile << "% Run the simulation and generate a txt file containing a result of the simulation. \n";
		modelfile << "% run this file with the following variables in the workspace \n";
		modelfile << "%       time_horizon:  Simulation Stop time or the simulation Time-Horizon \n";
		modelfile << "%       time_step:   Maximum simulation time-step \n";
		modelfile << "%       x0_0:       First variable initial value \n";
		modelfile << "%       x1_0:       Second variable initial value \n";
		modelfile << "\n \n \n";

//		modelfile << "timeFinal = " << user->getTimeHorizon() << "; %Simulation Stop time or the simulation Time-Horizon \n";
//		modelfile << "timeStepMax =" << user->getSampleTime() << "; %Maximum simulation time-step \n";

		modelfile << "timeFinal = "<< user->getTimeHorizon() <<"; %Simulation Stop time or the simulation Time-Horizon \n";
		modelfile << "timeStepMax = "<< user->getSampleTime() <<"; %Maximum simulation time-step \n";

		modelfile << "\n % initial values for Simulation \n";

		std::string reset_str=""; //Read one of the location and parse through the ODE's varName this contains the prime-variable

		location::ptr loc = ha->getLocation(1);	//since our location starts from 1
		list<flow_equation> derivatives = loc->getDerivatives();
		unsigned int val = 0, dim=ha->map_size(); //size of the variable mapping


		//use output variables to match only output variables and get the value. Assumed order is maintained even in the initial polytope creation
		assert(initial_output_values.size() == ha->map_size());	//double check
		for (unsigned int index=0; index < ha->map_size(); index++) {
			std::string varName = ha->get_varname(index);
			//std::cout <<"varName:" << varName << " index:" << index << std::endl;
			if (!(user->isInputVariable(varName))) {
				modelfile << "a" << index << " = " << initial_output_values[index] << ";  % user modifies this initial (state) values to the desired values\n";
			}
		}

/*
		for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
			string prime_variableName = (*it_flow).varName;	//eg x0'
			size_t pos = prime_variableName.find("'");
			string variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol
			//modelfile << "a" << val << " = x" << val << "_0; \n";

			if (!(user->isInputVariable(variableName))) {	//print only for output variables and not for input variables
				// Todo: generate random input from user supplied initial set
				//modelfile << "a" << val << " = initial_point(" << val + 1 << "); \n"; //val+1 since Matlab is One-Indexing
				modelfile << "a" << val << " = 1.0; % user modifies this initial (state) values to the desired values\n"; // Hopping user will modify this initial values from 1.0 to the desired values
			}

			val++;
		}*/



		string simulinkModelName = intermediate->getOutputfilenameWithoutExtension();
		simulinkModelName.append(to_string(iteration));

		modelfile << "\n %% Putting the Warning Off \n";
		modelfile << "\nwarning('off','all'); \n";

		modelfile << "\n %% Load the model \n";
		modelfile << "mdl ='" << simulinkModelName << "'; \n" ;
		modelfile << "load_system(mdl); \n" ;
		modelfile << "format shortG; \n" ;



		//Todo: obtain from the user-supplied parameters: Type:fixed-step/linear/sin-wave/spline
		//Only If the input variable is present in the model, then create the input time-series data ds and load into the model as LoadExternalInput=on
		if (user->getListInputVariables().size() > 0) {

			modelfile << "%%%%% Non-deterministic inputs %%%%%%% These values are obtained from \n";
			modelfile << "%%%%% our Tool using random bounded by initial input values or from CE \n";

			modelfile << "% Make SimulationData.Dataset to feed to the Simulink model \n";
			modelfile << "ds = Simulink.SimulationData.Dataset; \n";
			modelfile << "%% \n";

			//cout <<"\nData Set Details are " << endl;
			//cout <<"Check-out size of time-signal per-simulation =" << init_point.size()<< endl;
			std::string input_data_varName ="", input_time_varName ="", input_variable_data="", time_data="";
			std::string timeseries_input_value="", timeseries_varName="";
			std::string str_addElement="", input_port_Name="";

			unsigned int tot_size=0;
			for (std::list<struct timeseries_input>::iterator it_in = init_point.begin(); it_in != init_point.end(); it_in++) {
				input_variable_data="";	time_data="";	input_data_varName="";
				 input_time_varName =""; timeseries_input_value=""; timeseries_varName="";
				str_addElement="";	input_port_Name="";
				if (user->isInputVariable((*it_in).var_detail.var_name)) {

					input_data_varName.append((*it_in).var_detail.var_name);
					input_data_varName.append("_input");
					input_variable_data.append(input_data_varName);
					input_variable_data.append(" = [");
					//cout <<"\nDataVector are: ";
					tot_size = (*it_in).var_values.size();
					for (unsigned int i=0; i<(*it_in).var_values.size(); i++) {
						//cout <<(*it_in).var_values[i] << "\t";
						input_variable_data.append(to_string((*it_in).var_values[i]));
						if (i < (tot_size - 1)) {
							input_variable_data.append(" ");
						}
					}
					input_variable_data.append("]; \n");
					modelfile << input_variable_data ;

					input_time_varName.append((*it_in).var_detail.var_name);
					input_time_varName.append("_time");
					time_data.append(input_time_varName);
					time_data.append(" = [");
					assert(tot_size == (*it_in).time_values.size()); //is a must for MatLab
					for (unsigned int i=0; i<(*it_in).time_values.size(); i++) {
						//cout <<(*it_in).time_values[i] << "\t";
						time_data.append(to_string((*it_in).time_values[i]));
						if (i < (tot_size - 1)) {
							time_data.append(" ");
						}
					}
					time_data.append("]; \n");
					modelfile << time_data;

					//Eg., timeseriese_varName_input = timeseries(u_input, u_time); \n"
					timeseries_varName.append("timeseries_");
					timeseries_varName.append(input_data_varName);

					timeseries_input_value.append(timeseries_varName);
					timeseries_input_value.append(" = timeseries(");
					timeseries_input_value.append(input_data_varName);
					timeseries_input_value.append(", ");
					timeseries_input_value.append(input_time_varName);
					timeseries_input_value.append("); \n");

					modelfile << timeseries_input_value;
					/*
					 * We have to assume here the input-port name would be "varName" followed by "In". Eg.,  "x0In" or "x1In"
					 * This is the naming convention applied in the "txt2slx" process/engine.
					 */
					input_port_Name.append((*it_in).var_detail.var_name);
					input_port_Name.append("In");

					str_addElement.append("ds = ds.addElement(");
					str_addElement.append(timeseries_varName);
					str_addElement.append(", '");
					str_addElement.append(input_port_Name);
					//Note: the variable 'u' should be created as input_port in the simulink model
					str_addElement.append("'); \n %% \n");

					modelfile << str_addElement;

				} //working only for input variables

			} //end of iterating all the variables




			//modelfile << "%% This is sample-code, below present code only for a single input u. Similarly, it can be extended for more input variables. \n";
			//modelfile << "u_input = [5 10 15]; \n";
			//modelfile << "u_time = [0 5 10]; \n";
//			modelfile << "%%%%%% Deterministic single input value %%%%%%  \n";
//			modelfile << "% u_input = 10;   % In Breach use SetParamRanges({'Pedal_Angle_pulse_period', 'Pedal_Angle_pulse_amp'}, [10 20; 10 60]) \n";
//			modelfile << "% u_time = 0; \n";
			//modelfile << "timeseriese_input_value = timeseries(u_input, u_time); \n";
			//modelfile << "% Make SimulationData.Dataset to feed to the Simulink model \n";
			//modelfile << "ds = Simulink.SimulationData.Dataset; \n";


			//modelfile << "ds = ds.addElement(timeseriese_input_value,'u'); \n";	//Note: the variable 'u' should be created as input_port in the simulink model
			//modelfile << "%% \n";
			modelfile << "set_param(mdl, 'LoadExternalInput', 'on');  \n";
			modelfile << "set_param(mdl, 'ExternalInput', 'ds'); % Set the initial input values in the model. \n";

		} //end-if check on input variable count



		modelfile << "simOut = sim(mdl, 'SaveOutput', 'on', 'OutputSaveName', 'yOut', 'SaveTime', 'on','TimeSaveName','tOut', 'LimitDataPoints', 'off', 'SaveFormat', 'Array'); \n";

		modelfile << "%% Plot the result \n" ;
		modelfile << "y = simOut.get('yOut'); \n" ;
		modelfile << "t = simOut.get('tOut'); \n" ;
		modelfile << "[rsize, csize] = size(y); \n" ;
		modelfile << "for i=1:csize \n" ;
		modelfile << "	figure(i); \n" ;
		modelfile << "	plot(t, y( : , i)); \n" ;
		modelfile << "end \n" ;

		modelfile << "%Write the simulation result to the txt file \n" ;
		//modelfile << "result_matrix = [t, y( : , 1), y( : , 2)]; \n" ;
		string output_str="result_matrix = [t, ";
		unsigned int i=1;
		for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
			output_str.append("y( : ,");
			output_str.append(to_string(i));
			output_str.append(")");
			if (dim > 1 && i < dim) {
				output_str.append(", ");
			}
			i++;
		}
		output_str.append("]; \n");
		modelfile << output_str;




/*		modelfile << "result = sim('"<< simulinkModelName << "'); \n" ;
		modelfile << "tout = result.tout;  \n" ;

		//Get the variable name for plotting from the user and use only those two variables
		unsigned int i=0;
		for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
			string prime_variableName = (*it_flow).varName;	//eg x0'
			size_t pos = prime_variableName.find("'");
			string variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol

			modelfile << "x" << i <<  "= result.yout.getElement('" << variableName<< "Out').Values.Data; \n" ;
			modelfile << "figure(" << i + 1 << ");  \n" ;
			modelfile << "plot(tout, x" << i <<"); \n" ;

			i++;
		}*/

		/*
		modelfile << "figure(1);  \n" ;
		modelfile << "x1 = result.yout.getElement('" << user->getPlotVars().first_variable << "Out').Values.Data; \n" ;
		modelfile << "x2 = result.yout.getElement('" << user->getPlotVars().second_variable << "Out').Values.Data; \n" ;
		modelfile << "plot(x1,x2); \n" ;*/

/*
		modelfile << "%Write the simulation result to the txt file \n" ;
		//modelfile << "result_matrix = [tout, x1, x2]; \n" ;
		string output_str="result_matrix = [tout, ";
		i=0;
		for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
			output_str.append("x");
			output_str.append(to_string(i));
			if (dim > 1 && i < (dim - 1)) {
				output_str.append(", ");
			}
			i++;
		}
		output_str.append("]; \n");
		modelfile << output_str;
*/


		//modelfile << "result_filename = 'result.tsv'; \n" ;
		modelfile << "result_filename = 'result.txt'; \n" ;
		//modelfile << "writematrix(result_matrix, result_filename, 'FileType', 'text', 'Delimiter', 'tab'); \n" ;
		modelfile << "writematrix(result_matrix, result_filename, 'Delimiter', 'tab'); \n" ;

	} else {
		std::cout << "Error opening file: " << cmd;
	}

	modelfile.close();
	std::cout << "\n Script file created for running the Learned Simulink Model ...\n";
}


/*
 * This run-script generator do not write the actual values (input-data) into the file, only variable names are written onto it, unlike the above function createSetupScriptFile()
 * simulink_model_filename: is the simulink model filename that has the automaton design
 * script_filename: is the script file with .m extention to be created for running the simulink model with initial input/output values
 * output_filename: is a text-file containing time-serise trace in the order of time, followed by input and then output variables.
 * The files will be created in the folder specified by/in intermediate->getMatlabPathForLearnedModel().
 * Note: input-port in the simulink model must be assigned names as "x0In", "x1In", etc. Moreover, list of input and output variables must be supplied in the command-line.
 */
void simulinkModelConstructor::create_runScript_for_simu_engine(std::string simulink_model_filename, std::string script_filename, std::string output_filename) {

	/*
	 * This file is called from the engine/module: simu and equi-test and now from learn-ha also
	 * This function creates a Matlab script file for running the .slx model supplied by the user.
	 * Since main function of this engine is to perform simulation and return the accumulated time-serise data
	 */
	ofstream modelfile;
	std::string filePath="";
	if ((user->getEngine()=="simu") || (user->getEngine()=="equi-test")) {
		filePath = intermediate->getMatlabPathForLearnedModel();
	} else if ((user->getEngine()=="learn-ha") || (user->getEngine()=="learn-ha-loop")) {
		filePath = intermediate->getMatlabPathForOriginalModel();
	}

	/*std::cout <<"File name without path:" << script_filename << std::endl;
	std::cout <<"File name with path:" << simulink_model_filename << std::endl;
	std::cout <<"getMatlabPathForLearnedModel:" << filePath << std::endl;*/

	std::string filename = script_filename;	//"run_script_simu_user_model.m";
	std::string cmd = filePath; //Absolute path
	cmd.append("/");
	cmd.append(filename);

	//std::cout <<"File name:" << cmd << std::endl;

	modelfile.open(cmd);
	if (modelfile.is_open()) {
//		std::cout << "\nRunning Script File " << cmd << " created!!\n";
		//std::cout << "\nFile " << model_file_with_path << " created (Simulink Model) ...\n";
		modelfile << "%% ******** Simulate User Supplied Model ******** \n";
		modelfile << "% Run the simulation and generate a txt file containing a result of the simulation. \n";
		modelfile << "% run this file with the following variables in the workspace \n";
		modelfile << "%    timeFinal:  is the simulation Stop time or the simulation Time-Horizon. Note, .slx must have it set in the Model Settings->Solver menu. \n";
		modelfile << "%    timeStepMax: is the Maximum simulation time-step or 'Max step size'. Note, .slx must set it in the Model Settings->Solver menu. \n";
		modelfile << "%    a0, a1, and so on...: the initial values for state/output variables should also be loaded in the workspace. \n";

		modelfile << "%    x0_input:       control point for the first input variable \n";
		modelfile << "%    x0_time:       time series for the first input variable \n";
		modelfile << "%    x1_input:       control point for the second input variable \n";
		modelfile << "%    x1_time:       time series for the second input variable ..... and so on. \n";
		modelfile << "%     \n";
		modelfile << "% Note: If the .slx model has input variable, then the inport must be labelled as \n";
		modelfile << "%   x0In for the first input variable, x1In for the second input variable ..... and so on. \n";


		modelfile << "\n \n \n";

		modelfile << "timeFinal = " << user->getTimeHorizon() << "; %Simulation Stop time or the simulation Time-Horizon \n";
		modelfile << "timeStepMax = "<< user->getSampleTime() <<"; %Maximum simulation time-step \n";

		modelfile << "\n % initial values for Simulation \n";

		std::string reset_str=""; //Read one of the location and parse through the ODE's varName this contains the prime-variable


		std::string outfilename = simulink_model_filename;	//has the .slx extension supplied by the user. //todo maybe also check the absolute-or-relative-path

		size_t found = outfilename.find(".");	//extract file-name from extension
		if (found != string::npos) {
			outfilename = outfilename.substr (0,found);
		}

		std::string simulinkModelName = outfilename; //intermediate->getOutputfilenameWithoutExtension();

		modelfile << "\n %% Putting the Warning Off \n";
		modelfile << "\nwarning('off','all'); \n";

		modelfile << "\n %% Load the model \n";
		modelfile << "mdl ='" << simulinkModelName << "'; \n" ;
		modelfile << "load_system(mdl); \n" ;
		modelfile << "format shortG; \n" ;


		//Todo: obtain from the user-supplied parameters: Type:fixed-step/linear/sin-wave/spline
		//Only If the input variable is present in the model, then create the input time-series data ds and load into the model as LoadExternalInput=on
		if (user->getListInputVariables().size() > 0) {

			modelfile << "%%%%% Non-deterministic inputs %%%%%%% These values are obtained from \n";
			modelfile << "%%%%% our Tool using random bounded by initial input values or from CE \n";

			modelfile << "% Make SimulationData.Dataset to feed to the Simulink model \n";
			modelfile << "ds = Simulink.SimulationData.Dataset; \n";
			modelfile << "%% \n";

			//cout <<"\nData Set Details are " << endl;
			//cout <<"Check-out size of time-signal per-simulation =" << init_point.size()<< endl;
			std::string input_data_varName ="", input_time_varName ="", input_variable_data="", time_data="";
			std::string timeseries_input_value="", timeseries_varName="";
			std::string str_addElement="", input_port_Name="";

			//unsigned int tot_size=0;
			std::list<std::string> input_variables= user->getListInputVariables();

			for (std::list<std::string>::iterator inputVar = input_variables.begin(); inputVar != input_variables.end(); inputVar++) {
				std::string varName = (*inputVar);
				input_variable_data="";	time_data="";	input_data_varName="";
				 input_time_varName =""; timeseries_input_value=""; timeseries_varName="";
				str_addElement="";	input_port_Name="";
				if (user->isInputVariable(varName)) {	//Although now this check is not required

					input_data_varName.append(varName);
					input_data_varName.append("_input");

					input_time_varName.append(varName);
					input_time_varName.append("_time");

					//Eg., timeseriese_varName_input = timeseries(u_input, u_time); \n"
					timeseries_varName.append("timeseries_");
					timeseries_varName.append(input_data_varName);

					timeseries_input_value.append(timeseries_varName);
					timeseries_input_value.append(" = timeseries(");
					timeseries_input_value.append(input_data_varName);
					timeseries_input_value.append(", ");
					timeseries_input_value.append(input_time_varName);
					timeseries_input_value.append("); \n");

					modelfile << timeseries_input_value;
					/*
					 * Todo:
					 * We have to assume here the input-port name would be "varName" followed by "In". Eg.,  "x0In" or "x1In"
					 * This is the naming convention applied in the "txt2slx" process/engine. In general, when no name is assigned in the simulink model it is "In1" "In2" by default
					 */
					input_port_Name.append(varName);
					input_port_Name.append("In");

					str_addElement.append("ds = ds.addElement(");
					str_addElement.append(timeseries_varName);
					str_addElement.append(", '");
					str_addElement.append(input_port_Name);
					//Note: the variable 'u' should be created as input_port in the simulink model
					str_addElement.append("'); \n %% \n");

					modelfile << str_addElement;

				} //working only for input variables

			} //end of iterating all the variables


			modelfile << "set_param(mdl, 'LoadExternalInput', 'on');  \n";
			modelfile << "set_param(mdl, 'ExternalInput', 'ds'); % Set the initial input values in the model. \n";

		} //end-if check on input variable count



		modelfile << "simOut = sim(mdl, 'SaveOutput', 'on', 'OutputSaveName', 'yOut', 'SaveTime', 'on','TimeSaveName','tOut', 'LimitDataPoints', 'off', 'SaveFormat', 'Array'); \n";

		modelfile << "%% Plot the result \n" ;
		modelfile << "y = simOut.get('yOut'); \n" ;
		modelfile << "t = simOut.get('tOut'); \n" ;
		modelfile << "[rsize, csize] = size(y); \n" ;
		//*********** Plotting the original output from the Simulink model *****************
		modelfile << "for i=1:csize \n" ;
		modelfile << "	figure(i); \n" ;
		modelfile << "	plot(t, y( : , i)); \n" ;
		modelfile << "	title('Original Model','FontSize',26, 'FontWeight', 'bold'); \n" ;
		modelfile << "	xlabel('time', 'FontSize',26, 'FontWeight', 'bold'); \n" ;
		modelfile << "	grid on; \n" ;
		modelfile << "	grid minor; \n" ;
		modelfile << "end \n" ;

		//*********** Plotting original output done *****************

		// ******* If Data Filtering required by the user ***********

		//std::cout<<" user selected fixed/variable-step solver?: " << user->getFixedIntervalData() << std::endl;
		if (user->getFixedIntervalData()==1) {	// 0: variable outputs obtained from the model-solver. 1: get fixed timestep outputs.
			addFilteringCode(modelfile);
		}

		// *********** Data Filtering done ***********


		modelfile << "% Write the simulation result to the txt file \n" ;
		//modelfile << "result_matrix = [t, y( : , 1), y( : , 2)]; \n" ;
		string output_str="result_matrix = [t, ";
		//unsigned int i=1;

		//location::ptr loc = ha->getLocation(1);	//since our location starts from 1
		//list<flow_equation> derivatives = loc->getDerivatives();
		unsigned int dim=ha->map_size(); //size of the variable mapping

		// ---------------------------------
		//Todo: first write the input variables and then the output variables
		unsigned int input_size = user->getListInputVariables().size();
		unsigned int output_size = user->getListOutputVariables().size();

		//Writing first the input variables, which is all followed by the output ports
		for (unsigned int i=output_size; i < dim; i++) {
			output_str.append("y( : , ");
			output_str.append(to_string(i+1));   //+1 Matlab begin 1-based indexing
			output_str.append(")");
			if (dim > 1) {
				output_str.append(", ");
			}
		}

		//Writing then the output variables, which are the starting output ports
		for (unsigned int i=0; i < output_size; i++) {
			output_str.append("y( : , ");
			output_str.append(to_string(i+1));   //+1 Matlab begin 1-based indexing
			output_str.append(")");
			if (dim > 1 && i < (output_size - 1)) {
				output_str.append(", ");
			}
		}

		// ---------------------------------

		output_str.append("]; \n");
		modelfile << output_str;

		//modelfile << "result_filename = 'result_simu_data.txt'; \n" ;
		modelfile << "result_filename = '";
		modelfile << output_filename;
		modelfile << "'; \n" ;
		modelfile << "writematrix(result_matrix, result_filename, 'Delimiter', 'tab'); \n" ;

	} else {
		std::cout << "Error opening file: " << cmd;
	}

	modelfile.close();
//	std::cout << "\n Script file created for running the User supplied Simulink Model ...\n";
}

void simulinkModelConstructor::create_runScript_for_learn_ha_loop_engine(std::string simulink_model_filename, std::string script_filename, std::string output_filename) {

	/*
	 * This file is called from the engine/module: simu and equi-test and now from learn-ha also
	 * This function creates a Matlab script file for running the .slx model supplied by the user.
	 * Since main function of this engine is to perform simulation and return the accumulated time-serise data
	 */
	ofstream modelfile;
	std::string filePath="";
	if (user->getEngine()=="learn-ha-loop") {
		filePath = intermediate->getMatlabPathForLearnedModel();
	}

	//std::cout <<"File name without path:" << script_filename << std::endl;

	std::string filename = script_filename;	//"run_script_simu_user_model.m";
	std::string cmd = filePath; //Absolute path
	cmd.append("/");
	cmd.append(filename);

//	std::cout <<"File name:" << cmd << std::endl;

	modelfile.open(cmd);
	if (modelfile.is_open()) {
//		std::cout << "\nRunning Script File " << cmd << " created!!\n";
		//std::cout << "\nFile " << model_file_with_path << " created (Simulink Model) ...\n";
		modelfile << "%% ******** Simulate User Supplied Model ******** \n";
		modelfile << "% Run the simulation and generate a txt file containing a result of the simulation. \n";
		modelfile << "% run this file with the following variables in the workspace \n";
		modelfile << "%    timeFinal:  is the simulation Stop time or the simulation Time-Horizon. Note, .slx must have it set in the Model Settings->Solver menu. \n";
		modelfile << "%    timeStepMax: is the Maximum simulation time-step or 'Max step size'. Note, .slx must set it in the Model Settings->Solver menu. \n";
		modelfile << "%    a0, a1, and so on...: the initial values for state/output variables should also be loaded in the workspace. \n";

		modelfile << "%    x0_input:       control point for the first input variable \n";
		modelfile << "%    x0_time:       time series for the first input variable \n";
		modelfile << "%    x1_input:       control point for the second input variable \n";
		modelfile << "%    x1_time:       time series for the second input variable ..... and so on. \n";
		modelfile << "%     \n";
		modelfile << "% Note: If the .slx model has input variable, then the inport must be labelled as \n";
		modelfile << "%   x0In for the first input variable, x1In for the second input variable ..... and so on. \n";


		modelfile << "\n \n \n";

		modelfile << "timeFinal = " << user->getTimeHorizon() << "; %Simulation Stop time or the simulation Time-Horizon \n";
		modelfile << "timeStepMax = "<< user->getSampleTime() <<"; %Maximum simulation time-step \n";

		modelfile << "\n % initial values for Simulation \n";

		std::string reset_str=""; //Read one of the location and parse through the ODE's varName this contains the prime-variable


		std::string outfilename = simulink_model_filename;	//has the .slx extension supplied by the user. //todo maybe also check the absolute-or-relative-path

		size_t found = outfilename.find(".");	//extract file-name from extension
		if (found != string::npos) {
			outfilename = outfilename.substr (0,found);
		}

		std::string simulinkModelName = outfilename; //intermediate->getOutputfilenameWithoutExtension();

		modelfile << "\n %% Putting the Warning Off \n";
		modelfile << "\nwarning('off','all'); \n";

		modelfile << "\n %% Load the model \n";
		modelfile << "mdl ='" << simulinkModelName << "'; \n" ;
		modelfile << "load_system(mdl); \n" ;
		modelfile << "format shortG; \n" ;


		//Todo: obtain from the user-supplied parameters: Type:fixed-step/linear/sin-wave/spline
		//Only If the input variable is present in the model, then create the input time-series data ds and load into the model as LoadExternalInput=on
		if (user->getListInputVariables().size() > 0) {

			modelfile << "%%%%% Non-deterministic inputs %%%%%%% These values are obtained from \n";
			modelfile << "%%%%% our Tool using random bounded by initial input values or from CE \n";

			modelfile << "% Make SimulationData.Dataset to feed to the Simulink model \n";
			modelfile << "ds = Simulink.SimulationData.Dataset; \n";
			modelfile << "%% \n";

			//cout <<"\nData Set Details are " << endl;
			//cout <<"Check-out size of time-signal per-simulation =" << init_point.size()<< endl;
			std::string input_data_varName ="", input_time_varName ="", input_variable_data="", time_data="";
			std::string timeseries_input_value="", timeseries_varName="";
			std::string str_addElement="", input_port_Name="";

			//unsigned int tot_size=0;
			std::list<std::string> input_variables= user->getListInputVariables();

			for (std::list<std::string>::iterator inputVar = input_variables.begin(); inputVar != input_variables.end(); inputVar++) {
				std::string varName = (*inputVar);
				input_variable_data="";	time_data="";	input_data_varName="";
				 input_time_varName =""; timeseries_input_value=""; timeseries_varName="";
				str_addElement="";	input_port_Name="";
				if (user->isInputVariable(varName)) {	//Although now this check is not required

					input_data_varName.append(varName);
					input_data_varName.append("_input");

					input_time_varName.append(varName);
					input_time_varName.append("_time");

					//Eg., timeseriese_varName_input = timeseries(u_input, u_time); \n"
					timeseries_varName.append("timeseries_");
					timeseries_varName.append(input_data_varName);

					timeseries_input_value.append(timeseries_varName);
					timeseries_input_value.append(" = timeseries(");
					timeseries_input_value.append(input_data_varName);
					timeseries_input_value.append(", ");
					timeseries_input_value.append(input_time_varName);
					timeseries_input_value.append("); \n");

					modelfile << timeseries_input_value;
					/*
					 * Todo:
					 * We have to assume here the input-port name would be "varName" followed by "In". Eg.,  "x0In" or "x1In"
					 * This is the naming convention applied in the "txt2slx" process/engine. In general, when no name is assigned in the simulink model it is "In1" "In2" by default
					 */
					input_port_Name.append(varName);
					input_port_Name.append("In");

					str_addElement.append("ds = ds.addElement(");
					str_addElement.append(timeseries_varName);
					str_addElement.append(", '");
					str_addElement.append(input_port_Name);
					//Note: the variable 'u' should be created as input_port in the simulink model
					str_addElement.append("'); \n %% \n");

					modelfile << str_addElement;

				} //working only for input variables

			} //end of iterating all the variables


			modelfile << "set_param(mdl, 'LoadExternalInput', 'on');  \n";
			modelfile << "set_param(mdl, 'ExternalInput', 'ds'); % Set the initial input values in the model. \n";

		} //end-if check on input variable count



		modelfile << "simOut = sim(mdl, 'SaveOutput', 'on', 'OutputSaveName', 'yOut', 'SaveTime', 'on','TimeSaveName','tOut', 'LimitDataPoints', 'off', 'SaveFormat', 'Array'); \n";

		modelfile << "%% Plot the result \n" ;
		modelfile << "y = simOut.get('yOut'); \n" ;
		modelfile << "t = simOut.get('tOut'); \n" ;
		modelfile << "[rsize, csize] = size(y); \n" ;
		modelfile << "for i=1:csize \n" ;
		modelfile << "	figure(i); \n" ;
		modelfile << "	plot(t, y( : , i)); \n" ;
		modelfile << "	title('Learned Model','FontSize',26, 'FontWeight', 'bold'); \n" ;
		modelfile << "	xlabel('time', 'FontSize',26, 'FontWeight', 'bold'); \n" ;
		modelfile << "	grid on; \n" ;
		modelfile << "	grid minor; \n" ;
		modelfile << "end \n" ;





		// ******* Data Filtering: Fixed timestep output for equivalence testing required ***********


		// ******* If Data Filtering required by the user ***********

		//std::cout<<" user selected fixed/variable-step solver?: " << user->getFixedIntervalData() << std::endl;
		if (user->getFixedIntervalData()==1) {	// 0: (As-it-is in the .slx model) outputs obtained from the model-solver. 1: get fixed-time step outputs.
			addFilteringCode(modelfile);
		}

		//addFilteringCode(modelfile); // modified after NFM
		// *********** Data Filtering done ***********




		modelfile << "%Write the simulation result to the txt file \n" ;
		//modelfile << "result_matrix = [t, y( : , 1), y( : , 2)]; \n" ;
		string output_str="result_matrix = [t, ";
		//unsigned int i=1;

		//location::ptr loc = ha->getLocation(1);	//since our location starts from 1
		//list<flow_equation> derivatives = loc->getDerivatives();
		unsigned int dim=ha->map_size(); //size of the variable mapping

		// ---------------------------------
		//Todo: first write the input variables and then the output variables
		unsigned int input_size = user->getListInputVariables().size();
		unsigned int output_size = user->getListOutputVariables().size();

		//Writing first the input variables, which is all followed by the output ports
		for (unsigned int i=output_size; i < dim; i++) {
			output_str.append("y( : , ");
			output_str.append(to_string(i+1));   //+1 Matlab begin 1-based indexing
			output_str.append(")");
			if (dim > 1) {
				output_str.append(", ");
			}
		}

		//Writing then the output variables, which are the starting output ports
		for (unsigned int i=0; i < output_size; i++) {
			output_str.append("y( : , ");
			output_str.append(to_string(i+1));   //+1 Matlab begin 1-based indexing
			output_str.append(")");
			if (dim > 1 && i < (output_size - 1)) {
				output_str.append(", ");
			}
		}

		// ---------------------------------

		output_str.append("]; \n");
		modelfile << output_str;

		//modelfile << "result_filename = 'result_simu_data.txt'; \n" ;
		modelfile << "result_filename = '";
		modelfile << output_filename;
		modelfile << "'; \n" ;
		modelfile << "writematrix(result_matrix, result_filename, 'Delimiter', 'tab'); \n" ;

	} else {
		std::cout << "Error opening file: " << cmd;
	}

	modelfile.close();
//	std::cout << "\n Script file created for running the User supplied Simulink Model ...\n";
}

void simulinkModelConstructor::addFilteringCode(ofstream &modelfile) {
	/*
	 * Addon code called from create_runScript_for_simu_engine() to perform Data Filtering
	 * Filtering: Extract simulation data based on fixed timestep values and discard the data obtained due to variable Solver used in the Simulink model.
	 *
	 * Assumption:
	 *     This being an addon code, it assume that the data are in the matlab variable 't' and 'y'.
	 *     Variable t is one-dimensional array of variable timestep values with values containing at least one instance of fixed timestep value for each increasing timestep.
	 *     Variable y is n-dimensional array of variable containing values for each n dimensions corresponding t values.
	 *	   rsize and csize is obtained using [rsize, csize] = size(y); in the calling function.
	 */
	// ***************** Actual Matlab Code for Data Filtering *****************

	/*
		tstep=0;
		seq_index=1;
		totalSamples = timeFinal / timeStepMax + 1;
		t_temp1 = zeros(totalSamples, 1);
		y_temp1 = zeros(totalSamples, csize);
		firstFound = 1;
		for i= 1:rsize  %rsize is the total rows of y or y_temp
		   diffVal = t(i) - tstep; %initially time-step will be >= 0
		   if (diffVal >= 0)
			   firstFound = 1;
		   end
		   if (diffVal >= 0 && firstFound == 1)   %1st value that matches, i.e., positive value
				t_temp1(seq_index) = t(i);
				for j = 1:csize
					y_temp1(seq_index, j) = y(i, j);
				end

				seq_index = seq_index +1;
				tstep = tstep + timeStepMax;
				firstFound = 0;
		   end
		end
		t = t_temp1;
		y = y_temp1;
	 */


	modelfile << "tstep = 0;  \n";
	modelfile << "seq_index = 1;  \n";
	modelfile << "totalSamples = timeFinal / timeStepMax + 1;  \n";		//
	modelfile << "t_temp1 = zeros(totalSamples, 1);  \n";
	modelfile << "y_temp1 = zeros(totalSamples, csize);  \n";
	modelfile << "firstFound = 1; \n";

	modelfile << "for i = 1:rsize     %rsize is the total rows of y or y_temp  \n";

	modelfile << "  diffVal = t(i) - tstep;     %initially time-step will be >= 0  \n";
	modelfile << "	if (diffVal >= 0)    \n";
	modelfile << "		firstFound = 1;    \n";
	modelfile << "	end \n \n";
	modelfile << "	if (diffVal >= 0 && firstFound == 1)  %1st value that matches, i.e., positive value    \n";
	modelfile << "		t_temp1(seq_index) = t(i);   \n";
	modelfile << "      for j = 1:csize     %csize is the total columns of y or y_temp, i.e., for each variables  \n";
	modelfile << "          y_temp1(seq_index, j) = y(i, j);   \n";
	modelfile << "      end   \n";
	modelfile << "		seq_index = seq_index + 1;    \n";
	modelfile << "		tstep = tstep + timeStepMax;  \n";
	modelfile << "		firstFound = 0;    \n";
	modelfile << "	end    \n";		 //end of if
	modelfile << "end   \n";									 //end of for i= 1:r
	// ***************** Code for creating variables *****************

	// ******* Fixing minor bug *************
	//Due to variable time-step sometime some fixed timestep values are missed (unavailable in the simulation result).
	//Observed: Usually happened only one record for eg., 0.0010 is missed. Further inspection on more than one miss is required
	//Fix: we just replace the last zero values to non-zero value.
	modelfile << "last_row = y_temp1(totalSamples, :);   \n";
	modelfile << "if last_row == 0   \n";

	modelfile << "	secondlast_row = y_temp1(totalSamples - 1, :);   \n";
	modelfile << "	y_temp1(totalSamples, :) = secondlast_row;   \n";
	modelfile << "	secondlast_row_time = t_temp1(totalSamples - 1);   \n";
	modelfile << "	t_temp1(totalSamples) = secondlast_row_time;   \n";
	modelfile << "end   \n";
	// ***

	modelfile << "t = t_temp1; \n";		// replacing the filtered data back to the original variable t
	modelfile << "y = y_temp1; \n";	// replacing the filtered data back to the original variable y
}


void simulinkModelConstructor::createSmallScriptFile_ForFixedOutput(){

	ofstream modelfile;
	std::string filePath = intermediate->getMatlabPathForLearnedModel();
	std::string filename = "runSmallScript_";
	filename.append(intermediate->getOutputfilenameWithoutExtension());
	filename.append(to_string(iteration));
	//filename.append(to_string(user->getNumberMatlabSimulationExecutedEquivalenceTest()));
	filename.append(".m");
	std::string cmd = filePath; //Absolute path
	cmd.append("/");
	cmd.append(filename);
	modelfile.open(cmd);
	if (modelfile.is_open()) {
		//std::cout << "\nFile " << cmd << " created for Matlab (helping script for Execution of Simulink Model and generating output-file) ...\n";
		modelfile << "%% ******** Simulate Learned Model ******** \n";
		modelfile << "% Run the simulation and generate a txt file containing a result of the simulation using Fixed-step. \n";

		// ***************** Code for creating variables for writing to the file *****************

		/*
		[r,c]=size(learned_tout);
		tstep=0;
		seq_index=1;
		totalSamples = timeFinal / timeStepMax + 1;
		t_out = zeros(totalSamples, 1);
		x0 = zeros(totalSamples, 1);
		x1 = zeros(totalSamples, 1);
		disp(['Size r = ' num2str(r)])
		% x0(seq_index) = temp_x0(1);
		% x1(seq_index) = temp_x1(1);
		firstFound = 1;
		for i= 1:r
			disp(['learned_tout(i) = ' num2str(learned_tout(i))])
			diffVal = learned_tout(i) - tstep; %initially time-step will be >= 0
			if (diffVal >= 0)
				 firstFound = 1;
			end
			if (diffVal >= 0 && firstFound == 1)   %1st value that matches, i.e., positive value
				t_out(seq_index) = learned_tout(i);
				x0(seq_index) = temp_x0(i);
				x1(seq_index) = temp_x1(i);
				disp(['temp_x0(i) = ' num2str(temp_x0(i))])
				disp(['x0(i) = ' num2str(x0(seq_index))])

				seq_index = seq_index +1;
				tstep = tstep + timeStepMax;
				firstFound = 0;
			end
		 end
		 */
		modelfile << "[r,c]=size(learned_tout);";
		modelfile << "\n";
		modelfile << "tstep=0;";
		modelfile << "\n";
		modelfile << "seq_index=1;";
		modelfile << "\n";
		modelfile << "totalSamples = timeFinal / timeStepMax + 1;";
		modelfile << "\n";
		modelfile << "t_out = zeros(totalSamples, 1);";
		modelfile << "\n";
		string varName ="", varTempName="", varName_create="";
		//varName =""; varNamereate=""; varTempName="";
		for (unsigned int v=0; v < user->getSysDimension(); v++) {
			varName  = "x";
			varName.append(to_string(v));
			varName_create = varName;
			varName_create.append(" = zeros(totalSamples, 1);");
			modelfile << varName_create;
			modelfile << "\n";
		}
		modelfile << "firstFound = 1;";		modelfile << "\n";
		varName ="";	varTempName="";		varName_create="";
		modelfile << "for i= 1:r";
		modelfile << "\n";
		//modelfile << "disp(['learned_tout(i) = ' num2str(learned_tout(i))])"; 	modelfile << "\n";
		modelfile << "diffVal = learned_tout(i) - tstep; %initially time-step will be >= 0"; 	modelfile << "\n";
		modelfile << "	if (diffVal >= 0)";		modelfile << "\n";
		modelfile << "		firstFound = 1;";		modelfile << "\n";
		modelfile << "	end";		modelfile << "\n";			modelfile << "\n";
		modelfile << "	if (diffVal >= 0 && firstFound == 1)  %1st value that matches, i.e., positive value";	modelfile << "\n";
		modelfile << "		t_out(seq_index) = learned_tout(i);";	modelfile << "\n";
		for (unsigned int v=0; v < user->getSysDimension(); v++) {
			varTempName  = "temp_x";
			varTempName.append(to_string(v));
			varName  = "x";
			varName.append(to_string(v));
			varName_create = "		";
			varName_create.append(varName);
			varName_create.append("(seq_index) = ");
			varName_create.append(varTempName);
			varName_create.append("(i);");
			modelfile << varName_create;
			modelfile << "\n";
		}	//Initialise the vector for efficient operation (avoids resizing of the vector)
		//modelfile << "disp(['temp_x0(i) = ' num2str(temp_x0(i))])";		modelfile << "\n";
		//modelfile << "disp(['x0(i) = ' num2str(x0(seq_index))])";		modelfile << "\n";

		modelfile << "		seq_index = seq_index +1;";	modelfile << "\n";
		modelfile << "		tstep = tstep + timeStepMax;";	modelfile << "\n";
		modelfile << "		firstFound = 0; ";	modelfile << "\n";
		modelfile << "	end";				modelfile << "\n";		 //end of if
		modelfile << "end";									 //end of for i= 1:r

		// ***************** Code for creating variables *****************

	} else {
		std::cout << "Error opening file: " << cmd;
	}

	modelfile.close();
	//std::cout << "\n Script file created for being used in the Learned Simulink Model ...\n";

}
