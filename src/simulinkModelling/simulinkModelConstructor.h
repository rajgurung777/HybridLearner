/*
 * simulinkModelConstructor.h
 *
 *  Created on: 20-Oct-2021
 *      Author: amit
 */

#ifndef SIMULINKMODELLING_SIMULINKMODELCONSTRUCTOR_H_
#define SIMULINKMODELLING_SIMULINKMODELCONSTRUCTOR_H_


//#include "MatlabDataArray.hpp"
#include "MatlabEngine.hpp"

//#include "engine.h"

#include <iomanip>
#include <sstream>
#include <fstream>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "string.h"
#include <string>

#include "../hybridautomata/hybridAutomata.h"
#include "../commandLineParser/user_inputs.h"
#include "../utilities/intermediateResult.h"

#include <boost/shared_ptr.hpp>

using namespace std;
using namespace matlab::engine;


class simulinkModelConstructor {
	hybridAutomata::ptr ha;
	//ofstream outfile;
	user_inputs::ptr user;
	intermediateResult::ptr intermediate;
	unsigned int iteration; //Keeps track of the number of iterations (when the .slx file created)

	std::string simulinkModelName; //without the extension For eg.,   circle0 for 1st iteration, circle1 for 2nd iteration
	std::string script_for_simulinkModelName; //without the extension For eg.,   getModel_circle0 for 1st iteration, getModel_circle1 for 2nd iteration

	//Printing an identity mapping for reset equations
	std::string resetPrinter();
	//Prints reset equations when the mapping is known
	std::string resetPrinter(std::list<reset_equation> reset_list);

	std::string generateInitialValues();

	//Auxiliary function
	/*
//	 * I assume Input is a constraint string of the form "left op val", where left is the variable involving the constraint, op is the operator
	 * valid operators are  >=, <= etc and val is the numeric value
	 * Returns left which is a variable name.
	 */
	std::string getVariableComponent(std::string constriant_str);

	void addFilteringCode(ofstream &modelfile);

public:
	typedef boost::shared_ptr<simulinkModelConstructor> ptr;

	simulinkModelConstructor(){
		user = user_inputs::ptr (new user_inputs());
		intermediate  = intermediateResult::ptr(new intermediateResult());
		ha = hybridAutomata::ptr(new hybridAutomata());
		iteration = 0;
	};
	simulinkModelConstructor(hybridAutomata::ptr &H, user_inputs::ptr &user_input, intermediateResult::ptr &inter) {
		ha = H;
		user = user_input;
		intermediate = inter;
		iteration = 0;
	};

	int executeSimulinkModelConstructor(std::unique_ptr<MATLABEngine> &ep);

	void generateSimulinkModelScript(ofstream &outfile);
	void printSimulinkModelFile();
	void printDefinition(ofstream &outfile);
	void addMatlabFunction(ofstream &outfile);	//Adds a MATLAB Function inside StateFlow.Chart to generate a Random number for non-deterministic transitions
	void addLocations(ofstream &outfile);
//	void invariantPrinter(); Could not learned Invariant
	void addTransitions(ofstream &outfile);
	void addDefaultTransition(ofstream &outfile);
	void variableCreation(ofstream &outfile);
	void addInputComponents(ofstream &outfile);
	void addOutputComponents(ofstream &outfile);
	//void addConnectionLines(ofstream &outfile);

// ** Auxiliary functions **
	//void addMainTransitions(ofstream &outfile);
	void addLoopTransitions(ofstream &outfile, unsigned int sourceLoc, unsigned int number_loop_trans, unsigned int exec_order, unsigned int pos_x,
			unsigned int next_height, std::string condition_str, std::string reset_str);
//	void createConnectiveJunction(ofstream &outfile);
//	void completeLoopTransitions(ofstream &outfile);


	void inputVariableCreation(ofstream &outfile);
	void outputVariableCreation(ofstream &outfile);
	void localVariableCreation(ofstream &outfile);
	void parameterVariableCreation(ofstream &outfile);

	unsigned int getIteration() const;
	//The keeps track of the number of times Equivalence Test is executed and so it the .slx model files created.
	void setIteration(unsigned int iteration);

	const string& getSimulinkModelName() const;
	void setSimulinkModelName(const string &simulinkModelName);

	void createSetupScriptFile(std::list<struct timeseries_input> init_point, std::vector<double> initial_output_values);

	//This is specific to the engine="simu"
	void create_runScript_for_simu_engine(std::string simulink_model_filename, std::string script_filename, std::string output_filename);

	//This has similar function like create_runScript_for_simu_engine() but differs in the path
	void create_runScript_for_learn_ha_loop_engine(std::string simulink_model_filename, std::string script_filename, std::string output_filename);

	const string& getScriptForSimulinkModelName() const;
	void setScriptForSimulinkModelName(
			const string &scriptForSimulinkModelName);

	void createSmallScriptFile_ForFixedOutput();
};


#endif /* SIMULINKMODELLING_SIMULINKMODELCONSTRUCTOR_H_ */
