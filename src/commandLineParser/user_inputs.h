/*
 * user_inputs.h
 *
 *  Created on: 08-Sep-2021
 *      Author: amit
 */

#ifndef COMMANDLINEPARSER_USER_INPUTS_H_
#define COMMANDLINEPARSER_USER_INPUTS_H_


#include <string>
#include <list>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include "../io_functions/data_structs.h"
#include "../benchmark/model_variable_mapping.h"
#include <boost/algorithm/string.hpp>	//used for trim()

class user_inputs {
private:

	int isAbstractHS_model; //1 for Yes and 0 for No (meaning model has separate input and output variables)
	std::list<std::string> simulink_model_filenames;	//list (two) of file names supplied by the user for equivalence testing as a list
	std::list< std::vector<double> > random_initial_points_EquivalenceTest;	//storing to avoid generating multiple times for Equivalence Test

	unsigned int guard;	//either 0 or 1 as user's input to decide to modify/or not from the equality guard to range (+/- epsilon)
	unsigned int invariant;	//either 0, 1 or 2 as user's input to decide to include (input/output), remove input or remove both invariants
	unsigned int max_generateTrace_size; //variable use to store value which is greater then max_traces and simu_init_size. used for debug and getting reproducible reading

	//********** To be removed**********
	double DTW_simu_time;		//used in the DTW Clustering algorithm for internal simulation for similarity check
	unsigned int DTW_sample_size;		//used in the DTW Clustering algorithm for internal simulation for similarity check
	//std::string simu_init_point;	//string containing the simulation points to start the simulations
	std::string extra;	//This is an extra input from the command line for internal use mainly for debugging
	std::string controller_filename;
	std::string config_filename;	//output file for future use
	unsigned int sys_dimension; //dimension of the system under test (SUT)
	unsigned int simulation_check; //Enable or Disable Safety-violation check during initial simulations. 0:disable and 1:enable

//	********** Parameters for dReal Solver and input-file for dReach/dReal**********
	double precision;			//used to store for precision for solver dReal
	double max_value;	//Assumed maximum [-m, +m] constant value that all system variables can take. Default is 1000
	std::string MinMax_Bounds;	//input string of variable's bounds. Syntax:  x0:minVal,maxVal & x1:minVal,maxVal
	std::list<struct variable_bounds> list_variable_bounds;	//list of variables and their bounds
	int upper_bound;			//maximum upper bound for unrolling
	int lower_bound;			//lower bound for unrolling


//	********** Main parameters for HybridLearner **********
	int model;		//Select the desired built-in Model for Simulation/Learning
	int modes;		//Number of desired Locations/modes
	double sample_time;			//used to store for sampling time
	double time_horizon;		//total time bound
	double cluster_error_tol;		//used to store the relative-difference-error tolerated during segmentation to detect the boundary in the Learning Algorithm
	double segmentation_fine_error; //used to store the relative-difference-fine-error tolerated during segmentation near the boundary in the Learning Algorithm
	int filter_last_segment;	//user choice for option disable(0) or enable(1) for removing last segment in each trajecotry during segmentation.
	int lmm_step_size;	// user choice for Linear Multi-step Method's step size M (default is set to 5)
	double precision_equivalence;	//used to store for precision value used for Equivalence Testing algorithm. Eg. distance between two points
	double precision_guard_range;	//store an epsilon value used for converting the equality-guard condition to range-guard condition (+/- epsilon) for Simulink simulation
	std::string variable_category;	//user's input for each variable category (input or output category)
	std::list<std::string> list_input_variables;	//keeps track of the list of input variables
	std::list<std::string> list_output_variables;	//keeps track of the list of output variables
	std::map<std::string, std::string> variable_type_mapping;	//mapping of variable name to its category/type, i.e., input or output
	std::string tool;	//Name of the tool such as HIT or Naijun's implementation
	std::string clust_algo;	//dbscan or DTW or Naijun's approach (piecelinear)
	double DBScan_eps_dist;	//input epsilon value for DBSCAN algorithm
	unsigned int DBScan_min_samples;	//input minimum samples value for DBSCAN algorithm
	double correlation_threshold;		//used in the DTW Clustering algorithm
	double distance_threshold;		//used in the DTW Clustering algorithm

	std::string Engine; // The Engine options learn-ha(default), simu, mdl2SLX, equi-test
	std::string model_filename;  //filename supplied by user as .txt for tranlation to .slx model
	std::string simulink_model_filename;  //filename supplied by user as .slx model
	std::string simu_trace_filename;  //filename supplied by user containing simulation traces of the system under learning
	std::string simulink_model_files;  //two file names supplied by the users as a string for equivalence testing
	int max_degree;		//Degree of the Polynomial ODEs
	int boundary_degree; 		//Degree of the Polynomial Guard
	std::string output_filename;	//output file that
	std::string input_filename;
	std::string simulation_filename; //internally generated file
	std::string ODESolver;	//stores user's choice of ODE Solver for .slx model creation
	std::string ODESolverType; //stores user's choice for the ODE Solver Type (variable or fixed)
	int fixed_interval_data;	//store user's choice to extract data as fixed timestep from simulation to be pass for the learning algorithm
	double max_stoptime;	//Set the Maximum Stop Time for the whole HybridLearner in seconds.
	double max_stoptime_equitest;	//Set the Maximum Stop Time for the Equivalence Testing in seconds.
	unsigned int max_traces; //Set the Maximum number of points/traces for Equivalence Testing default is set to 10 traces.
	struct plot_variables plot_vars;
	unsigned int ode_speedup;	//Maximum number of segments to be included for ODE computing and pruning all segments above this value.
	unsigned int seed; //takes input from the user the seed for random number generation

//  ********** Specification for Verification**********
	std::string goal_property;	//string variable that will hold the goal property (for simple goal), for more complex property property can be used
	std::string initial_set;	// initial-value (bounded) for each variable from where the simulation starts
	std::string input_signal_type; //syntax of input string="x0=fixed-step & x1=fixed-linear"   var-step can be thought later
	std::string numberOf_control_points; //syntax of input string="x0=2 & x1=3"
	std::string input_signal_sine_wave_parameter; //syntax of input string syntax: "x0={20,5} & x1={100,1000}"; Here 100 is the amplitude
												  // and starting point is 1000. So, the sine wave has a max=1100 and min=900 height.
	std::map<std::string, std::pair<double, double>> input_variable_sinewave_parameter_mapping;	//mapping of input variable's sine-wave parameters (amplitude and zero_offset)
	unsigned int simu_init_size; //number (or size) of simulation points to start the simulations

//  ********** Type annotation for Transition's Update**********
	std::string variable_types;	//Human annotation for Jump-Rest variables. Eg., 'x0=t1,x1=t2'
	std::string t2_values;		//Human annotation for Jump-Rest: Pool of values for type 't2' variables. Eg., 'x1={1,2,3,4}' for the above variable_types
	std::string t3_values;		//Human annotation for Jump-Rest: Assignments for type 't3' variables. Eg., 'x1=0 & x2=' for the above variable_types

// 	********** This functions can be separated from this class*******************************************
	unsigned int number_matlab_simulation_executed;	//Keep trace of the number of times matlab_simulation_executed (Original Model)
	unsigned int number_matlab_simulation_executed_EquivalenceTest;	//Keep trace of the number of times matlab_simulation_executed during EquivalenceTest
	unsigned int number_randomPoints_generated_EquivalenceTest; //Keep trace of the number of times random points generated for EquivalenceTest
	unsigned int number_matlab_simulation_learnedModel_executed;	//Keep trace of the number of times matlab_simulation_executed (Learned Model)

//	********** helper functions*******************************************
	void setBounds(string varName, double minValue, double maxValue);
	std::map<std::string, std::string> getVariableCategory_map();
	std::map<std::string, std::pair<double, double> > getSinewaveParameterMapping();

public:
	typedef boost::shared_ptr<user_inputs> ptr;

	model_variable_mapping::ptr simulation_model;

	user_inputs(){
		simulation_model = model_variable_mapping::ptr(new model_variable_mapping());

		sample_time=0.0;			//used to store for sampling time
		model=0;		//Select the desired Model (built-in) for Simulation and Learning it and check
		modes=0;		//Number of desired Locations/modes
		precision=0.0;			//used to store for precision for solver dReal
		precision_equivalence=0.0;	//used to store for precision value used for Equivalence Testing algorithm. Eg. distance between two points
		precision_guard_range=0.0;
		cluster_error_tol = 0.0;
		isAbstractHS_model = 1;	//1 meaning has not separate input and output variables

		time_horizon=0.0;		//total time bound
		max_value=0.0;
		upper_bound=0;			//maximum upper bound for unrolling
		lower_bound=0;			//lower bound for unrolling
		max_degree=0;		//Degree of the Polynomial ODEs
		boundary_degree=0; 		//Degree of the Polynomial Guard
		sys_dimension=0; //dimension of the system under test (SUT)
		simu_init_size =0; //number (or size) of simulation points to start the simulations
		number_matlab_simulation_executed=0;	//Keep trace of the number of times matlab_simulation_executed (Original Model)
		number_matlab_simulation_executed_EquivalenceTest=0;	//Keep trace of the number of times matlab_simulation_executed during EquivalenceTest
		number_randomPoints_generated_EquivalenceTest=0; //Keep trace of the number of times random points generated for EquivalenceTest
		number_matlab_simulation_learnedModel_executed=0;	//Keep trace of the number of times matlab_simulation_executed (Learned Model)

		max_stoptime = 0;
		max_stoptime_equitest = 0;
		max_traces = 0;
		max_generateTrace_size = 0;
		seed = 0;
		ode_speedup = 1;
		simulation_check = 1; //Default is enabled
		guard = 0; //Default
		invariant = 2; //Default

		DBScan_eps_dist =0.2;	//Default
		DBScan_min_samples = 1; //Default
		distance_threshold = 0;
		correlation_threshold=0.8;
		fixed_interval_data = 1; //Default

		DTW_simu_time=0;
		DTW_sample_size=0;

	};

	double getSampleTime() const;
	void setSampleTime(double sampleTime);
	int getModeSize() const;
	void setModeSize(int numModes);
	double getTimeHorizon() const;
	void setTimeHorizon(double timeHorizon);

	//Assumed maximum [-m, +m] constant value that all system variables can take. Default is 1000
	double getMaxValue() const;
	void setMaxValue(double maxValue);
	double getPrecision() const;
	void setPrecision(double precision);
	int getLowerBound() const;		// unrolling lower depth for dReal (SMT unrolling depth)
	void setLowerBound(int lowerBound);
	int getUpperBound() const;
	void setUpperBound(int upperBound);

	void setGoalProperty(const std::string& goalProperty);
	//Returns the same goal string entered by the user
	const std::string& getGoalString() const;

	void setInitialSet(const std::string& initial_set);
	const std::string& getInitialSet_userInput(); //to get what was supplied by the user using the setInitialSet(string)
	std::list<std::string> getInitialSet();

	void setTool(const std::string& goalProperty);	//wrapper to include/plug new learning algorithms
	const std::string& getTool();

	void setClusterAlgorithm(const std::string& goalProperty);
	const std::string& getClusterAlgorithm();
	int getPolyDegree() const;
	void setPolyDegree(int degree);

	const std::string& getInputFilename();
	void setInputFilename(const std::string& inputFilename);
	const std::string& getOutputFilename() const;
	void setOutputFilename(const std::string& outputFilename);
	const struct plot_variables& getPlotVars() const;
	void setPlotVars(const struct plot_variables &plotVars);

	int getModel() const;
	void setModel(int model);

	unsigned int getSimuInitSize() const;
	void setSimuInitSize(unsigned int simuInitSize);

	const std::string& getSimulationFilename() const;
	void setSimulationFilename(const std::string& simulationFilename);

	int getBoundaryDegree() const;
	void setBoundaryDegree(int boundaryDegree);

	double getPrecisionEquivalence() const;
	void setPrecisionEquivalence(double precisionEquivalence);
	double getMaxStoptime() const;
	void setMaxStoptime(double maxStoptime);
	double getMaxStoptimeEquitest() const;
	void setMaxStoptimeEquitest(double maxStoptimeEquitest);
	unsigned int getMaxTraces() const;
	void setMaxTraces(unsigned int maxTraces);
	double getPrecisionGuardRange() const;
	void setPrecisionGuardRange(double precisionGuardRange);

	const std::string& getInputSignalType() const;
	void setInputSignalType(const std::string &inputSignalType);
	const std::string& getNumberOfControlPoints() const;
	void setNumberOfControlPoints(const std::string &numberOfControlPoints);
	int getIsAbstractHsModel() const;
	void setIsAbstractHsModel(int isAbstractHsModel);

	double getClusterError() const;
	void setClusterError(double clusterError);

	const std::string& getMinMaxBounds() const;
	void setMinMaxBounds(const std::string &minMaxBounds);

	unsigned int getSeed() const;
	void setSeed(int seed);

	const std::string& getT2Values() const;
	void setT2Values(const std::string &t2Values);
	const std::string& getVariableTypes() const;
	void setVariableTypes(const std::string &variableTypes);

	const std::string& getEngine() const;
	void setEngine(const std::string &engine);

	const std::string& getModelFilename() const;
	void setModelFilename(const std::string &modelFilename);
	unsigned int getGuard() const;
	void setGuard(unsigned int guard);
	const std::string& getVariableCategory() const;
	void setVariableCategory(const std::string &variableCategory);
	const std::list<std::string>& getListInputVariables() const;
	void setListInputVariables(const std::list<std::string> &listInputVariables);
	const std::list<std::string>& getListOutputVariables() const;
	void setListOutputVariables(const std::list<std::string> &listOutputVariables);

	const std::string& getInputSignalSineWaveParameter() const;
	void setInputSignalSineWaveParameter(const std::string &inputSignalSineWaveParameter);

	const std::map<std::string, std::pair<double, double> >& getInputVariableSinewaveParameterMapping() const;
	void setInputVariableSinewaveParameterMapping(const std::map<std::string, std::pair<double, double> > &inputVariableSinewaveParameterMapping);

	const std::string& getSimuTraceFilename() const;
	void setSimuTraceFilename(const std::string &simuTraceFilename);

	const std::string& getSimulinkModelFilename() const;
	void setSimulinkModelFilename(const std::string &simulinkModelFilename);

	void setSimulinkModelFiles(const std::string &simulinkModelFiles);
	const std::list<std::string>& getSimulinkModelFilenames() const;
	void setSimulinkModelFilenames(
			const std::list<std::string> &simulinkModelFilenames);
	double getDbScanEpsDist() const;
	void setDbScanEpsDist(double dbScanEpsDist);
	unsigned int getDbScanMinSamples() const;
	void setDbScanMinSamples(unsigned int dbScanMinSamples);
	const std::string& getOdeSolver() const;
	void setOdeSolver(const std::string &odeSolver);
	int getFixedIntervalData() const;
	void setFixedIntervalData(int fixedIntervalData);
	double getCorrelationThreshold() const;
	void setCorrelationThreshold(double correlationThreshold);
	double getDistanceThreshold() const;
	void setDistanceThreshold(double distanceThreshold);

	unsigned int getMaxGenerateTraceSize() const;
	void setMaxGenerateTraceSize(unsigned int maxGenerateTraceSize);
	unsigned int getOdeSpeedup() const;
	void setOdeSpeedup(unsigned int odeSpeedup);

	const std::string& getOdeSolverType() const;
	void setOdeSolverType(const std::string &odeSolverType);


	// ********** helper functions*******************************************
	//Clears the list of input and list of output variables
	void clearVariableList();
	bool isInputVariable(string variableName);
	unsigned int getInvariant() const;
	void setInvariant(unsigned int invariant);

	const std::map<std::string, std::string>& getVariableTypeMapping() const;		//although related but not used directly here
	void setVariableTypeMapping(const std::map<std::string, std::string> &variableTypeMapping);
	void setVariableBounds();
	const std::list<struct variable_bounds>& getListVariableBounds() const;
	/* * Returns as reference the bound values both min and max, including the variable category for a given variable name varName	 */
	void getVariableBounds(string varName, double &minValue, double &maxValue, std::string &varCategory);
	void setListVariableBounds(const std::list<struct variable_bounds> &listVariableBounds);
	//std::list<struct control_points> getUserInputSignal_parameter();
	//void setVariableType(std::list<struct control_points> &res, string variableName, string variableType);
	//void setVariable_CP_Size(std::list<struct control_points> &res, string variableName, double cp_size);
	//Returns the goal property as a list of expression string converted from the user's data
	std::list<std::string> getGoalProperty();

	//********** related helper functions*******************************************
	unsigned int getNumberMatlabSimulationExecutedEquivalenceTest() const;
	void setNumberMatlabSimulationExecutedEquivalenceTest(
			unsigned int numberMatlabSimulationExecutedEquivalenceTest);
	const std::list<std::vector<double> >& getRandomInitialPoints_EquivalenceTest() const;
	void setRandomInitialPoints_EquivalenceTest(
			const std::list<std::vector<double> > &randomInitialPoints);
	//Random initial points used in Equivalence Test consisting of 50 initial points for Example
	unsigned int getNumberRandomPointsGeneratedEquivalenceTest() const;
	void setNumberRandomPointsGeneratedEquivalenceTest(
			unsigned int randomPointsGeneratedEquivalenceTest);
	unsigned int getNumberMatlabSimulationLearnedModelExecuted() const;
	void setNumberMatlabSimulationLearnedModelExecuted(
			unsigned int numberMatlabSimulationLearnedModelExecuted);
	//keeps track of the number of times the Original model is simulated
	unsigned int getNumberMatlabSimulationExecuted() const;
	void setNumberMatlabSimulationExecuted(
			unsigned int numberMatlabSimulationExecuted);

	//********** to be removed*******************************************
	unsigned int getDTW_SampleSize() const;
	void setDTW_SampleSize(unsigned int dtwSampleSize);
	double getDTW_SimuTime() const;
	void setDTW_SimuTime(double dtwSimuTime);
	unsigned int getSimulationCheck() const;
	void setSimulationCheck(unsigned int simulationCheck);
	unsigned int getSysDimension() const;
	void setSysDimension(unsigned int sysDimension);
	const std::string& getExtra() const;
	void setExtra(const std::string &extra);

	//*******************************************
	const std::string& getSimuInitPoint() const;	//to be removed after verifying code in engine=HybridLearner
	void setSimuInitPoint(const std::string &simuInitPoint);
	std::list< std::vector<double> > getSimulationInitialPoints();
	const std::string& getControllerFilename() const;
	void setControllerFilename(const std::string& controllerFilename);
	const std::string& getConfigFilename() const;
	void setConfigFilename(const std::string& configFilename);
	int getFilterLastSegment() const;
	void setFilterLastSegment(int filterLastSegment);
	double getSegmentationFineError() const;
	void setSegmentationFineError(double segmentationFineError);

	const std::string& getT3Values() const;
	void setT3Values(const std::string &t3Values);
	int getLmmStepSize() const;
	void setLmmStepSize(int lmmStepSize);
};



#endif /* COMMANDLINEPARSER_USER_INPUTS_H_ */
