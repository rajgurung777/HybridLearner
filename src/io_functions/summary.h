/*
 * summary.h
 *
 *  Created on: 13-Oct-2021
 *      Author: amit
 */

#ifndef IO_FUNCTIONS_SUMMARY_H_
#define IO_FUNCTIONS_SUMMARY_H_

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <list>
#include "data_structs.h"


class summary {
public:
	typedef boost::shared_ptr<summary> ptr;
	summary(){
		runtime_matlab_start = 0;
		runtime_matlab_initial_simulation = 0;
		runtime_learning_algo = 0;
		runtime_model_parsing = 0;
		runtime_property_falsification = 0;
		runtime_matlab_counterexample_simulation = 0;
		runtime_matlab_termination = 0;
		runtime_input_model_construction = 0;
		runtime_json_parser = 0;
		runtime_CE_validity_check = 0;
		runtime_simulink_model_creation = 0;

		equivalenceTest_report.iteration=0;
		equivalenceTest_report.time_taken = 0.0;
		equivalenceTest_report.traces_checked = 0;

		total_equivalenceTest_report.iteration = 0;
		total_equivalenceTest_report.time_taken = 0.0;
		total_equivalenceTest_report.traces_checked = 0;
	};

	double getRuntimeLearningAlgo() const;
	void setRuntimeLearningAlgo(double runtimeLearningAlgo);
	double getRuntimeMatlabCounterexampleSimulation() const;
	void setRuntimeMatlabCounterexampleSimulation(
			double runtimeMatlabCounterexampleSimulation);
	double getRuntimeMatlabInitialSimulation() const;
	void setRuntimeMatlabInitialSimulation(
			double runtimeMatlabInitialSimulation);
	double getRuntimeMatlabTermination() const;
	void setRuntimeMatlabTermination(double runtimeMatlabTermination);
	double getRuntimeModelParsing() const;
	void setRuntimeModelParsing(double runtimeModelParsing);
	double getRuntimePropertyFalsification() const;
	void setRuntimePropertyFalsification(double runtimePropertyFalsification);
	double getRuntimeMatlabStart() const;
	void setRuntimeMatlabStart(double runtimeMatlabStart);

	void printSummary();

	void printAllIterationSummary();

	const std::list<double>& getListRuntimeLearningAlgo() const;
	void setListRuntimeLearningAlgo(double value);
	const std::list<double>& getListRuntimeMatlabCounterexampleSimulation() const;
	void setListRuntimeMatlabCounterexampleSimulation(double value);
	const std::list<double>& getListRuntimeMatlabInitialSimulation() const;
	void setListRuntimeMatlabInitialSimulation(double value);
	const std::list<double>& getListRuntimeMatlabStart() const;
	void setListRuntimeMatlabStart(double value);
	const std::list<double>& getListRuntimeModelParsing() const;
	void setListRuntimeModelParsing(double value);

	const std::list<double>& getListRuntimePropertyFalsification() const;
	void setListRuntimePropertyFalsification(double value);

	const std::list<double>& getListRuntimeMatlabTermination() const;
	void setListRuntimeMatlabTermination(double value);

	const std::list<double>& getListRuntimeInputModelConstruction() const;
	void setListRuntimeInputModelConstruction(double value);

	double getRuntimeInputModelConstruction() const;
	void setRuntimeInputModelConstruction(double runtimeInputModelConstruction);


	double getRuntimeJsonParser() const;
	void setRuntimeJsonParser(double runtimeJsonParser);

	const std::list<double>& getListRuntimeJsonParser() const;
	void setListRuntimeJsonParser(double value);

	double getRuntimeCEValidityCheck() const;
	void setRuntimeCEValidityCheck(double runtimeCeValidityCheck);

	const std::list<double>& getListRuntimeCEValidityCheck() const;
	void setListRuntimeCEValidityCheck(double value);

	double getRuntimeSimulinkModelCreation() const;
	void setRuntimeSimulinkModelCreation(double runtimeSimulinkModelCreation);


	const std::list<double>& getListRuntimeSimulinkModelCreation() const;
	void setListRuntimeSimulinkModelCreation(double value);


	equivalenceTest equivalenceTest_report; //Keeps track of the Last executions.
//	std::list<equivalenceTest> list_equivalenceTest_report; //Keeps the record of all the executions.

	equivalenceTest total_equivalenceTest_report; //total-summary of equivalenceTest_report

	const std::list<equivalenceTest>& getListEquivalenceTestReport() const;
	void setListEquivalenceTestReport(equivalenceTest structValue);



	/*
	 * Returns the total time elapsed so far.
	 * This time includes the sum of all the iterations of:
	 * (1) Initial-Simulation time for generating time-serise data for the Learning algorithm and the time for Learning the model.
	 *     Includes: simulations + Learning Algorithm + parsing and creating hybrid automaton C++ object + model construction (for model checker).
	 * (2) Model Checker's time for Property verification + Simulation and Checking time if a counterexample is found by the Model Checker.
	 *     Includes: model-checker's Property verification time + simulation with original model to check if Valid CE found.
	 * (3) Equivalence Testing time i.e., the simulations of traces by both the learned and original model and the Equivalence Checking time to check if the traces are equivalent.
	 *     Includes: simulations of N-points by both the Learned and Original models
	 */
	double computeTotalTimeElapsed();
	const std::string& getModelName() const;
	void setModelName(const std::string &modelName);

private:

	//These variables will record the sum of times for all iterations
	double runtime_matlab_start;
	double runtime_matlab_initial_simulation;	//Starting Matlab and Simulink and generation of initial simulation traces for input to the Learning Algorithm
	double runtime_learning_algo;	//Execution and output from the Learning Algorithm
	double runtime_model_parsing;	//reading the file generated by the Learning Algorithm and creating an HA object
	double runtime_property_falsification;	//Execution of dReach tool to verify safety property
	double runtime_matlab_counterexample_simulation;	//generation of simulation traces using the counterexample obtained from dReach
	double runtime_matlab_termination;	//for closing the Matlab Engine and exiting Matlab
	double runtime_input_model_construction; //creating input-file for Model checker: fileName.drh for dReach tool
	double runtime_json_parser; //parsing the .json file to retrieve an initial point from the counterexample trace generated by the tool dReach.
	double runtime_CE_validity_check;	//check if CE generated by dReach model-check is VALID (violates Forbidden state)
	double runtime_simulink_model_creation;	//time to create the Simulink model of the Learned Automaton

	std::list<double> list_runtime_matlab_start;
	std::list<double> list_runtime_matlab_initial_simulation;
	std::list<double> list_runtime_learning_algo;
	std::list<double> list_runtime_model_parsing;
	std::list<double> list_runtime_property_falsification;
	std::list<double> list_runtime_matlab_counterexample_simulation;
	std::list<double> list_runtime_matlab_termination;

	std::list<double> list_runtime_input_model_construction;
	std::list<double> list_runtime_json_parser;
	std::list<double> list_runtime_CE_validity_check;
	std::list<double> list_runtime_simulink_model_creation;

	std::list<equivalenceTest> list_equivalenceTest_report; //Keeps the record of all the executions.

	std::string modelName;	//Name of the Benchmark being executed

};



#endif /* IO_FUNCTIONS_SUMMARY_H_ */
