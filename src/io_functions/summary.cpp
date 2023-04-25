/*
 * summary.cpp
 *
 *  Created on: 13-Oct-2021
 *      Author: amit
 */


#include "summary.h"

using namespace std;

double summary::getRuntimeLearningAlgo() const {
	return runtime_learning_algo;
}

void summary::setRuntimeLearningAlgo(double runtimeLearningAlgo) {
	runtime_learning_algo += runtimeLearningAlgo;
	setListRuntimeLearningAlgo(runtimeLearningAlgo);
}

double summary::getRuntimeMatlabCounterexampleSimulation() const {
	return runtime_matlab_counterexample_simulation;
}

void summary::setRuntimeMatlabCounterexampleSimulation(
		double runtimeMatlabCounterexampleSimulation) {
	runtime_matlab_counterexample_simulation +=
			runtimeMatlabCounterexampleSimulation;
	setListRuntimeMatlabCounterexampleSimulation(runtimeMatlabCounterexampleSimulation);
}

double summary::getRuntimeMatlabInitialSimulation() const {
	return runtime_matlab_initial_simulation;
}

void summary::setRuntimeMatlabInitialSimulation(
		double runtimeMatlabInitialSimulation) {
	runtime_matlab_initial_simulation += runtimeMatlabInitialSimulation;
	setListRuntimeMatlabInitialSimulation(runtimeMatlabInitialSimulation);
}

double summary::getRuntimeMatlabTermination() const {
	return runtime_matlab_termination;
}

void summary::setRuntimeMatlabTermination(double runtimeMatlabTermination) {
	runtime_matlab_termination += runtimeMatlabTermination;
	setListRuntimeMatlabTermination(runtimeMatlabTermination); //Will not be used
}

double summary::getRuntimeModelParsing() const {
	return runtime_model_parsing;
}

void summary::setRuntimeModelParsing(double runtimeModelParsing) {
	runtime_model_parsing += runtimeModelParsing;
	setListRuntimeModelParsing(runtimeModelParsing);
}

double summary::getRuntimePropertyFalsification() const {
	return runtime_property_falsification;
}

void summary::setRuntimePropertyFalsification(
		double runtimePropertyFalsification) {
	runtime_property_falsification += runtimePropertyFalsification;
	setListRuntimePropertyFalsification(runtimePropertyFalsification);
}

double summary::getRuntimeMatlabStart() const {
	return runtime_matlab_start;
}

void summary::setRuntimeMatlabStart(double runtimeMatlabStart) {
	runtime_matlab_start += runtimeMatlabStart;
	setListRuntimeMatlabStart(runtimeMatlabStart); //Will not be used
}

const std::list<double>& summary::getListRuntimeLearningAlgo() const {
	return list_runtime_learning_algo;
}

void summary::setListRuntimeLearningAlgo(double RuntimeLearningAlgo) {
	list_runtime_learning_algo.push_back(RuntimeLearningAlgo);
}

const std::list<double>& summary::getListRuntimeMatlabCounterexampleSimulation() const {
	return list_runtime_matlab_counterexample_simulation;
}

void summary::setListRuntimeMatlabCounterexampleSimulation(double value) {
	list_runtime_matlab_counterexample_simulation.push_back(value);
}

const std::list<double>& summary::getListRuntimeMatlabInitialSimulation() const {
	return list_runtime_matlab_initial_simulation;
}

void summary::setListRuntimeMatlabInitialSimulation(double value) {
	list_runtime_matlab_initial_simulation.push_back(value);
}

const std::list<double>& summary::getListRuntimeMatlabStart() const {
	return list_runtime_matlab_start;
}

void summary::setListRuntimeMatlabStart(double value) {
	list_runtime_matlab_start.push_back(value);
}

const std::list<double>& summary::getListRuntimeModelParsing() const {
	return list_runtime_model_parsing;
}

void summary::setListRuntimeModelParsing(double value) {
	list_runtime_model_parsing.push_back(value);
}

const std::list<double>& summary::getListRuntimePropertyFalsification() const {
	return list_runtime_property_falsification;
}

void summary::setListRuntimePropertyFalsification(double value) {
	list_runtime_property_falsification.push_back(value);
}

const std::list<double>& summary::getListRuntimeMatlabTermination() const {
	return list_runtime_matlab_termination;
}

void summary::setListRuntimeMatlabTermination(double value) {
	list_runtime_matlab_termination.push_back(value);
}


void summary::printSummary(){

	std::cout << "\n************ Summary of Running Time (in Seconds) ************* " << std::endl;
	std::cout << " Running Benchmark: " << modelName << endl;
	std::cout << " Matlab Engine start: " << runtime_matlab_start << endl;
	std::cout << " Matlab Simulink (initial simulations): " << runtime_matlab_initial_simulation << endl;
	std::cout << " Learning Algorithm: " << runtime_learning_algo << endl;
	std::cout << " Model parsing into Hybrid Automaton: " << runtime_model_parsing << endl;
	std::cout << " Construct Input model file for Model-Checker: " << runtime_input_model_construction << endl;
	std::cout << " Model checking- Safety Property + CE-parsing (json): " << runtime_property_falsification << " + " << runtime_json_parser << endl;
	std::cout << " Matlab Simulation using CE + Valid Safety Violation: " << runtime_matlab_counterexample_simulation << " + " << runtime_CE_validity_check << endl;
	std::cout << " Matlab Learned Model Creation (Simulink): "<< runtime_simulink_model_creation << endl;
	std::cout << " Equivalence Testing Total: Traces Tested=" << total_equivalenceTest_report.traces_checked << " , Time-Taken (seconds)=" << total_equivalenceTest_report.time_taken << endl;
	std::cout << " Matlab Engine Termination: " << runtime_matlab_termination << endl;

	std::cout << "\n************ End of the Summary ************* " << std::endl;

}

void summary::printAllIterationSummary() {
	unsigned int total_iters = list_runtime_learning_algo.size();

	//All iterators with .begin() pointer
	std::list<double>::iterator matlab_init_simulation = list_runtime_matlab_initial_simulation.begin(),
			learning_algo = list_runtime_learning_algo.begin(), model_parsing = list_runtime_model_parsing.begin(),
			property_falsification = list_runtime_property_falsification.begin(),
			matlab_ce_simulation = list_runtime_matlab_counterexample_simulation.begin(),
			matlab_termination = list_runtime_matlab_termination.begin(), matlab_start = list_runtime_matlab_start.begin(),
			simulink_create = list_runtime_simulink_model_creation.begin(),
			inputFile_model = list_runtime_input_model_construction.begin(),
			json_parser = list_runtime_json_parser.begin(), valid_violation = list_runtime_CE_validity_check.begin();

	std::list<equivalenceTest>::iterator equiTest = list_equivalenceTest_report.begin();

	std::cout << "\n************ Summary of Running Time (in Seconds) ************* " << std::endl;
	for (unsigned int i=0; i < total_iters; i++) {

		std::cout << "\n************ Iteration No: " << i+1 << " ************* " << std::endl;
//		if (i==0) {
//			std::cout << " Matlab Engine start: " << runtime_matlab_start << endl;
//		}

		std::cout << " Matlab Engine start: " << (*matlab_start) << endl;
		std::cout << " Matlab Simulink (initial simulations): " << (*matlab_init_simulation) << endl;
		std::cout << " Learning Algorithm: " << (*learning_algo) << endl;
		std::cout << " Model parsing into Hybrid Automaton: " << (*model_parsing) << endl;
		std::cout << " Construct Input model file for Model-Checker: " << (*inputFile_model) << endl;
		std::cout << " Model checking- Safety Property + CE-parsing (json): " << (*property_falsification) << " + " << (*json_parser) << endl;
		std::cout << " Matlab Simulation using CE + Valid Safety Violation: " << (*matlab_ce_simulation) << " + " << (*valid_violation) << endl;
		std::cout << " Matlab Learned Model Creation (Simulink): "<< (*simulink_create) << endl;
		std::cout << " Equivalence Testing-: Traces Tested=" << (*equiTest).traces_checked << " , Time-Taken (seconds)=" << (*equiTest).time_taken << endl;
		std::cout << " Matlab Engine Termination: " << (*matlab_termination) << endl;
		std::cout << "\n************ End of Iteration No: " << i+1 << " ************* " << std::endl;

		matlab_init_simulation++;
		learning_algo++;
		model_parsing++;
		property_falsification++;
		json_parser++;
		matlab_ce_simulation++;
		matlab_termination++;
		matlab_start++;
		equiTest++;
		inputFile_model++;
		simulink_create++;
		valid_violation++;

	}
	//std::cout << " Matlab Engine Termination: " << runtime_matlab_termination << endl;
	std::cout << "\n************ End of the Summary ************* " << std::endl;
}

const std::string& summary::getModelName() const {
	return modelName;
}

void summary::setModelName(const std::string &modelName) {
	this->modelName = modelName;
}

/*
 * Returns the total time elapsed so far.
 * This time includes the sum of all the iterations of:
 * (1) Initial-Simulation time for generating time-serise data for the Learning algorithm and the time for Learning the model.
 *     Includes: simulations + Learning Algorithm + parsing and creating hybrid automaton C++ object + model construction (for model checker).
 * (2) Model Checker's time for Property verification + Simulation and Checking time if a counterexample is found by the Model Checker.
 *     Includes: model-checker's Property verification time + json-file parser for CE + simulation with original model + check if trace is VALID.
 * (3) Equivalence Testing time i.e., the simulations of traces by both the learned and original model and the Equivalence Checking time to check if the traces are equivalent.
 *     Includes: Learned simulink model creation + simulations of N-points by both the Learned and Original models
 */
double summary::computeTotalTimeElapsed() {
	double totalTime = 0.0;

	//(1)
	totalTime = runtime_matlab_initial_simulation + runtime_learning_algo + runtime_model_parsing + runtime_input_model_construction;
	//(2)
	totalTime += runtime_property_falsification + runtime_json_parser + runtime_matlab_counterexample_simulation + runtime_CE_validity_check;
	//(3)
	double tot_equiTest = 0.0;
	for (std::list<equivalenceTest>::iterator equiTest = list_equivalenceTest_report.begin(); equiTest != list_equivalenceTest_report.end(); equiTest++) {
		tot_equiTest += (*equiTest).time_taken;
	}
	totalTime += runtime_simulink_model_creation + tot_equiTest;

	return totalTime;
}

const std::list<double>& summary::getListRuntimeInputModelConstruction() const {
	return list_runtime_input_model_construction;
}

void summary::setListRuntimeInputModelConstruction(double value) {
	list_runtime_input_model_construction.push_back(value);
}

double summary::getRuntimeInputModelConstruction() const {
	return runtime_input_model_construction;
}

void summary::setRuntimeInputModelConstruction(
		double runtimeInputModelConstruction) {
	runtime_input_model_construction += runtimeInputModelConstruction;
	setListRuntimeInputModelConstruction(runtimeInputModelConstruction);
}

double summary::getRuntimeJsonParser() const {
	return runtime_json_parser;
}

void summary::setRuntimeJsonParser(double runtimeJsonParser) {
	runtime_json_parser += runtimeJsonParser;
	setListRuntimeJsonParser(runtimeJsonParser);
}

const std::list<double>& summary::getListRuntimeJsonParser() const {
	return list_runtime_json_parser;
}

void summary::setListRuntimeJsonParser(double value) {
	list_runtime_json_parser.push_back(value);
}

double summary::getRuntimeCEValidityCheck() const {
	return runtime_CE_validity_check;
}

void summary::setRuntimeCEValidityCheck(double runtimeCeValidityCheck) {
	runtime_CE_validity_check += runtimeCeValidityCheck;
	setListRuntimeCEValidityCheck(runtimeCeValidityCheck);
}

const std::list<double>& summary::getListRuntimeCEValidityCheck() const {
	return list_runtime_CE_validity_check;
}

void summary::setListRuntimeCEValidityCheck(double value) {
	list_runtime_CE_validity_check.push_back(value);
}

double summary::getRuntimeSimulinkModelCreation() const {
	return runtime_simulink_model_creation;
}

void summary::setRuntimeSimulinkModelCreation(
		double runtimeSimulinkModelCreation) {
	runtime_simulink_model_creation += runtimeSimulinkModelCreation;
	setListRuntimeSimulinkModelCreation(runtimeSimulinkModelCreation);
}

const std::list<double>& summary::getListRuntimeSimulinkModelCreation() const {
	return list_runtime_simulink_model_creation;
}

void summary::setListRuntimeSimulinkModelCreation(double value) {
	list_runtime_simulink_model_creation.push_back(value);
}

const std::list<equivalenceTest>& summary::getListEquivalenceTestReport() const {
	return list_equivalenceTest_report;
}

void summary::setListEquivalenceTestReport(equivalenceTest structValue) {
	list_equivalenceTest_report.push_back(structValue);
	total_equivalenceTest_report.iteration = structValue.iteration; //Assuming iteration always increases
	total_equivalenceTest_report.time_taken += structValue.time_taken;
	total_equivalenceTest_report.traces_checked += structValue.traces_checked;

}
