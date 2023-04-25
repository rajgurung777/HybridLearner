/*
 * commandLineParser.cpp
 *
 *  Created on: 08-Sep-2021
 *      Author: amit
 */

#include "commandLineParser.h"
#include <fstream>

using namespace std;
namespace po = boost::program_options;

void commandLineParser(int argc, char *argv[], user_inputs::ptr& userInputs) {


	po::options_description desc("HybridLearner options");
	po::variables_map vm;

	if (argc == 1) { //No argument::
		std::cout << "Missing arguments!\n";
		throw(new exception());
	}

	desc.add_options()("help,h", "produce help message")
	("time-horizon,Z", po::value<double>(), "Set the global time horizon of computation.")
	("sampling-time,s", po::value<double>(), "Sets the sampling time (time-step)")

	("precision-equivalence", po::value<double>()->default_value(0.001), "set precision for Equivalence Testing (default 0.001)")
	("precision-guard-range", po::value<double>()->default_value(0.0), "set precision for Equality Guard as range of +/- epsilon (default 0.0)")


	("max-stoptime", po::value<double>(), "Set the Maximum Stop Time for the whole HybridLearner in seconds.")
	("max-stoptime-equitest", po::value<double>(), "Set the Maximum Stop Time for the Equivalence Testing in seconds.")
	("max-traces", po::value<int>()->default_value(10), "Set the Maximum number of points/traces for Equivalence Testing default set to 10 traces. \n"
		"Equivalence Testing stops on either of the condition hits earlier (max-traces or max-stoptime-equitest).")
	("goal,F", po::value<std::string>(), "Goal property to test, syntax: 'expr-1 & expr-2'; For e.g. expr-1 is x0>=2. \n"
		"In addition local (lt) and global (gt) time constriants can also be provided. E.g. gt>=10 & gt<=50")
	("initial-value,V", po::value<std::string>(), "Initial set for Property Verification, syntax: 'expr-1 & expr-2'; For e.g. expr-1 is x0>=2\n"
		"Note: Enter bounds for input followed by output variables. Moreover, variable names are x0, x1, ... learned by the Learning Algorithm\n") //

	("max-value,x", po::value<double>()->default_value(1000), "Assumed maximum [-m, +m] constant value that all system variables can take. Default is 1000")
	("MinMax-bounds", po::value<std::string>(), "Bounds on each variables. Syntax:  x0:minVal,maxVal & x1:minVal,maxVal \n"
		"x0,x1 are the variables and minVal and maxVal are min/max constant values.")

	("variable-category", po::value<std::string>(), "Type/Category of the variable. Syntax:  x0:input, x1:input, x2:output, etc.")

	("input-signal-type", po::value<std::string>(), "Type for input signal generation. Options are fixed-step, linear, spline and sine-wave.\n"
			"syntax: 'x0=fixed-step & x1=linear & x2=spline'; Note: sine-wave generate one-cycle with desired amplitude and zero-offset.\n")
	("sine-wave-parameter", po::value<std::string>(), "For input signal of type sine-wave supply parameter: amplitude and zero-offset.\n"
			"syntax: 'x0={20,5} & x1={100,1000}'; Here 100 is the amplitude and starting point is 1000. So, the sine wave \n"
			"has a max=1100 and min=900 height.  More values can be separated by & symbol.\n" )

	("numberOf-control-points", po::value<std::string>(), "Number of control points for each variables.\n"
			"syntax: 'x0=2 & x1=3'; Note: control-points are randomly generated, bounded by supplied initial-value\n")

	("variable-types", po::value<std::string>(), "Annotation for variable types, for jump-reset of variables.\n"
			"syntax: 'x0=t3,x1=t4,x2=t4,x3=t1,x4=t2';\n Note below the different type of variables:\n"
			"t1: continuous and constant throughout\n"
			"t2: takes a possible value from {c1,...,cn}\n"
			"t3: any arbitrary constant value. E.g., ball-position reset to zero; x1=0\n"
			"t4: random, Eg., piecewise constant\n"
			"t5: linear expression\n" )
	("t2-values", po::value<std::string>(), "Pool of values for type 't2' variable(s) assigned for variable-types.\n"
			"syntax: 'x4={0,1,2}';\n Note x4 is the type 't2' variable assigned and 0/1/2 are the pool of values."
			" More values can be separated by & symbol.\n" )

	("t3-values", po::value<std::string>(), "Constant assignment for type 't3' variable(s).\n"
				"syntax: 'x1=0';\n Note x1 is the type 't3' variable reset to 0 at the jump."
				" More values can be separated by & symbol.\n" )

	("engine,e", po::value<std::string>()->default_value("learn-ha"), "set the running engine (default learn-ha): \n"
			" \n - simu : Trajectory Simulation, user supplied .slx/.mdl simulink file."
			" \n - txt2slx : model file in .txt to .SLX Matlab's model."
			" \n - learn-ha : Learns a Hybrid Automaton model from simulation trajectories."
			" \n - learn-ha-loop : Learns a Hybrid Automaton model from a simulink model."
			" \n - equi-test : perform equivalence testing of two compatible Matlab's Simulink models.")


	("model-file", po::value<std::string>(), "Cyber-Physical Systems model file, as input for the engine -txt2slx.")
	("simu-trace-file", po::value<std::string>(), "File name containing the simulation traces of the System Under Learning for engine 'learn-ha'.")
	("simulink-model-file", po::value<std::string>(), "Cyber-Physical Systems model file in .slx/.mdl format for simulation (engine=simu and learn-ha)."
			" \n When engine=equi-test two files can be supplied one followed by the other separated by blank space(s)")
	("modes,m", po::value<int>()->default_value(2), "Sets the number of desired Modes or Locations of HA, (default 2)")
	("guard", po::value<int>()->default_value(1), "Available Options are either 0 or 1:"
			"\n 0: no change in the guard\n"
			"\n 1 (default): equality (hyperplane) modified into inequality (halfspace) (+/- epsilon). Epsilon value is supplied by the option --precision-guard-range.\n")

	("invariant", po::value<int>()->default_value(0), "Simulink model construction for invariant. Available options are either 0, 1 or 2 \n"
			"\n 0 (default): include input and output in the invariant\n"
			"\n 1: include only output in the invariant\n"
			"\n 2: remove the invariant.\n")

	("solver-type", po::value<std::string>()->default_value("variable"), "ODE Solver Type for simulation of Learned Model in Matlab. Options are: \n"
			"\n variable: (default): variable time step is taken by the ODE Solver \n"
			"\n fixed: a fixed time step is taken by the ODE solver \n")
	("ode-solver", po::value<std::string>()->default_value("VariableStepAuto"), "ODE Solver for simulation of Learned Model in Matlab. Eg. ode45 (Dormand-Prince), ode15s (stiff/NDF) \n"
			"\n Supported solver for solver-type: \n"
			"=variable are VariableStepAuto(default)/ode15s/ode23s/ode23t/ode23tb/ode45/ode23/ode113/odeN \n"
			"=fixed are  FixedStepAuto/ode14x/ode1be/ode1/ode2/ode3/ode4/ode5/ode8 \n")

	("fixed-interval-data", po::value<int>()->default_value(1), "Extract simulation data as fixed interval. Available options are either 0 or 1."
			"\n 0: data extracted based on the solver in the model."
			"\n 1 (default): data extracted as fixed time-step(recommended for equivalence testing).\n" )

	("tool,T", po::value<std::string>()->default_value("pwa"), "Available Option: pwa\n"
			//"hit: Uses the HIT Library in MATLAB to learn PWA and PWARX. To-do task.\n"
			//"adha: Hybrid Automata with Affine Dynamics (Linear), from TA Henzinger group in Python and Julia. To-do task.\n"
			"pwa: A Python implementation to learn Nonlinear Hybrid Automaton.\n")

	("lmm-step-size", po::value<int>()->default_value(5), "Options are: 2/3/4/5/6. Higher values computes more accurate derivatives. 5 is set as default. A key parameter for segmentation.")
	("segment-relative-error", po::value<double>()->default_value(0.01), "set the maximum relative-difference (FwdBwd) error. Used in the Learning Algorithm. (default 0.01)")
	("segment-relative-fine-error", po::value<double>()->default_value(0.01), "set the relative-difference (Bwd) error near the boundary. Used in the Learning Algorithm. (default 0.01)")
	//("cluster-error-tol", po::value<double>()->default_value(0.01), "set the relative-difference (FwdBwd) error tolerated, used in the Learning Algorithm. (default 0.01)")
	("filter-last-segment", po::value<int>()->default_value(0), "0 disable (default) and 1 to enable filtering/removing last segment of each trajectory during segmentation.")
	("cluster-algo,c", po::value<std::string>()->default_value("dtw"), "Clustering Algorithm when --tool=pwa, available options are: \n"
			"dbscan: uses the standard DBscan algorithm (set to Default)\n"
			"piecelinear: uses the PruneSearching procedure (to be removed)\n"
			"dtw: use the Dynamic Time Warping algorithm\n") //
	("dbscan-min-samples", po::value<int>()->default_value(1), "set the minimum samples in DBSCAN algorithm (default 1)")
	("dbscan-eps-dist", po::value<double>()->default_value(0.2), "set the epsilon distance for DBSCAN algorithm (default 0.2)")
	("correlation-threshold", po::value<double>()->default_value(0.5), "set the DTW correlation threshold for similarity (default >=0.5)")
	("distance-threshold", po::value<double>()->default_value(250.0), "set the DTW distance threshold for similarity (default <=250.0)")
	("ode-speedup", po::value<int>()->default_value(50), "ODE estimation performance criteria. Sets a maximum number after which segments are pruning of ODE computation (default 50)")


	("degree,d", po::value<int>()->default_value(1), "Sets the Maximum degree of Polynomial ODE (default 1). A value of 1 learns a linear model, 2 or more for nonlinear model.")
	("boundary-degree", po::value<int>()->default_value(1), "Sets the Maximum degree of Polynomial Guard (default 1). A value of 1 learns a linear model, 2 or more for nonlinear model.")

	("extra", po::value<std::string>(), "Extra options for internal use in the tool debugging")
	("max-generate-trace-size", po::value<int>()->default_value(20), "Extra option to set trace generation size (when > simu-init-size and max-traces, default=20). Debug version")
	("seed", po::value<int>()->default_value(100), "Seed for generating random number series. Default is set to value 100.")
	("simulation-check", po::value<int>()->default_value(1), "Simulation based Testing for Safety violation enabled or disabled. 0 to disable and 1 to enable. Default is enabled.")


	//("input-file,i", po::value<std::string>(), "Time-series data as input file")
	("simu-init-size", po::value<int>()->default_value(1), "Supply the number (or size) of initial-points (randomly chosen) for simulation. Default is set to 1.")
	//("simu-init-point", po::value<std::string>(), "Select the initial-point for simulation. Multiple points can be supplied separated by & symbol \n"
	//		" syntax: 'x0=7,x1=8 & x0=10,x1=15' where x0 and x1 are system-learned variables.")	//todo: to be removed

	("output-file,o", po::value<std::string>(), "output file name for redirecting the outputs");

	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	std::string fileName;

	if (vm.count("help")) {
		std::cout << desc << "\n";
		exit(0);
		//return 0; //Just displaying the Help options and terminating the Project
	}

	//First read engine, so that based on engine, compulsory option check can be performed
	if (vm.count("engine")) {
		userInputs->setEngine((vm["engine"].as<std::string>()));
		if (boost::iequals(userInputs->getEngine(),"simu")==false) {
			if (boost::iequals(userInputs->getEngine(),"txt2slx")==false){
				if (boost::iequals(userInputs->getEngine(),"learn-ha")==false){
					if (boost::iequals(userInputs->getEngine(),"learn-ha-loop")==false){
						if(boost::iequals(userInputs->getEngine(),"equi-test")==false){
								std::cout << "Invalid engine option specified. Expected \"simu\", \"txt2slx\", \"learn-ha\", \"learn-ha-loop\", or  \"equi-test\".\n";
								throw(new exception());
						}
					}
				}
			}
		}
	}

	if (vm.count("model-file")) {
		userInputs->setModelFilename(vm["model-file"].as<std::string>());
	} else {
		if(boost::iequals(userInputs->getEngine(),"txt2slx")==true){
			std::cout << "No model file supplied, please input a Model file name using --model-file option.\n";
			throw(new exception());
		}
		// not compulsory for  simu and equi-test (for now)
	}

	if (vm.count("simulink-model-file")) {
		if (userInputs->getEngine()=="equi-test") {
			userInputs->setSimulinkModelFiles(vm["simulink-model-file"].as<std::string>());
		} else {	//for simu and learn-ha only single file is supplied
			userInputs->setSimulinkModelFilename(vm["simulink-model-file"].as<std::string>());
		}
	} else {
		//if ((boost::iequals(userInputs->getEngine(),"simu")==true) || (boost::iequals(userInputs->getEngine(),"equi-test")==true)) {
		if ((boost::iequals(userInputs->getEngine(),"simu")==true) || (boost::iequals(userInputs->getEngine(),"equi-test")==true) || (boost::iequals(userInputs->getEngine(),"learn-ha-loop")==true)) {
			std::cout << "No model file(s) supplied, please input .slx/.mdl Model filename(s) using --simulink-model-file option.\n";
			throw(new exception());
		}
		// not compulsory for  simu and equi-test (for now)
	}


	if (vm.count("simu-trace-file")) {
		userInputs->setSimuTraceFilename(vm["simu-trace-file"].as<std::string>());
	} else {
		if(boost::iequals(userInputs->getEngine(),"learn-ha")==true){
			std::cout << "No simulation trace file supplied, please input a trace file name using --simu-trace-file option.\n";
			throw(new exception());
		}
		// not compulsory for  simu and equi-test (for now)
	}


	if (vm.count("guard")) {
		userInputs->setGuard((vm["guard"].as<int>()));
		if (userInputs->getGuard() < 0 && userInputs->getGuard() > 1) { //for 0 or negative sampling-time
			std::cout << "Invalid option specified for guard. A zero or a 1 value expected.\n";
			throw(new exception());
		}
	}
	if (vm.count("invariant")) {
		userInputs->setInvariant((vm["invariant"].as<int>()));
		if (userInputs->getInvariant() < 0 && userInputs->getInvariant() > 2) { //for 0 or negative sampling-time
			std::cout << "Invalid option specified for Invariant. Expected values are either 0, 1 or 2.\n";
			throw(new exception());
		}
	}

	if (vm.count("sampling-time")) {
		userInputs->setSampleTime((vm["sampling-time"].as<double>()));
		if (userInputs->getSampleTime() <= 0) { //for 0 or negative sampling-time
			std::cout
					<< "Invalid sampling-time option specified. A positive non-zero value expected.\n";
			throw(new exception());
		}
	}

	//This Option should appear before --model
	if (vm.count("max-value")) {
		userInputs->setMaxValue((vm["max-value"].as<double>()));
		if (userInputs->getMaxValue() <= 0) { //for 0 or negative sampling-time
			std::cout << "Invalid max-value option specified. A positive non-zero Maximum possible value expected.\n";
			throw(new exception());
		}
	}



	if (vm.count("ode-solver")) { // ODE Solver only for the Learned model to be used for simulation or model (.slx) creation
		userInputs->setOdeSolver(vm["ode-solver"].as<std::string>());
	}

	if (vm.count("solver-type")) {// ODE Solver Type ("variable" or "fixed")
		userInputs->setOdeSolverType(vm["solver-type"].as<std::string>());
	}

	if (vm.count("fixed-interval-data")) { // extract simulation data using fixed timestep for passing the data to the Learning algorithm
		userInputs->setFixedIntervalData(vm["fixed-interval-data"].as<int>());
	}

	if (vm.count("variable-types")) { // Human annotation for Reset function
		userInputs->setVariableTypes(vm["variable-types"].as<std::string>());
	}


	//This Option should appear before --model
	std::map<std::string, std::string> vartype;
	if (vm.count("variable-category")) { //Todo: Assuming user respects the syntax as specified in the menu or model
		userInputs->setVariableCategory(vm["variable-category"].as<std::string>());

		vartype = userInputs->getVariableTypeMapping();

		/*
		 // ---- Debugging if parsing is done correctly
		 * for (std::map<std::string, std::string>::iterator it = vartype.begin(); it != vartype.end(); it++) {
			std::cout <<"var Name: " << it->first << " ::  " <<" var Type: " << it->second << std::endl;
		}
		// ----
		*/

	} else {
		if(boost::iequals(userInputs->getEngine(),"txt2slx")==true){	// needed for engine=txt2slx
			std::cout << "Missing variable Type/Category definition. Please set the Variable Type using option --variable-category.\n";
			throw(new exception());
		}
		if(boost::iequals(userInputs->getEngine(),"simu")==true){	// needed for engine=simu
			std::cout << "Missing variable Type/Category definition. Please set the Variable Type using option --variable-category.\n";
			throw(new exception());
		}
		if(boost::iequals(userInputs->getEngine(),"equi-test")==true){	// needed for engine=equi-test
			std::cout << "Missing variable Type/Category definition. Please set the Variable Type using option --variable-category.\n";
			throw(new exception());
		}
		if(boost::iequals(userInputs->getEngine(),"learn-ha-loop")==true){	// needed for engine=learn-ha-loop
			std::cout << "Missing variable Type/Category definition. Please set the Variable Type using option --variable-category.\n";
			throw(new exception());
		}

		// optional engine="learn-ha" i.e., the learning algorithm
	}


	if (vm.count("modes")) {
		userInputs->setModeSize((vm["modes"].as<int>()));
		if (userInputs->getModeSize() < 1) { //for 0 or negative number of locations
			std::cout << "Invalid modes option specified. A positive value is expected.\n";
//			if (log_set){
//				log_file << "Invalid modes option specified. A positive value is expected.\n";
//			}
			throw(new exception());
		}
	}



	if (vm.count("precision-equivalence")) {
		userInputs->setPrecisionEquivalence((vm["precision-equivalence"].as<double>()));
		if (userInputs->getPrecisionEquivalence() <= 0) { //for 0 or negative precision
			std::cout << "Invalid precision-equivalence value specified. A positive non-zero value expected.\n";
//			if (log_set){
//				log_file << "Invalid precision-equivalence value specified. A positive non-zero value expected.\n";
//			}
			throw(new exception());
		}
	}


	if (vm.count("precision-guard-range")) {
		userInputs->setPrecisionGuardRange((vm["precision-guard-range"].as<double>()));
		/*if (userInputs->getPrecisionGuardRange() < 0) {
			std::cout << "Invalid precision-guard-range value specified. A positive non-zero value expected.\n";
			throw(new exception());
		}*/  //disabling this check since now guard can be played with halfspace and epsilon value   <= epsilon
	}


	if (vm.count("time-horizon")) {
		userInputs->setTimeHorizon((vm["time-horizon"].as<double>()));
		if (userInputs->getTimeHorizon() <= 0) { //for 0 or negative sampling-time
			std::cout << "Invalid time-horizon option specified. A positive non-zero value expected.\n";
//			if (log_set){
//				log_file << "Invalid time-horizon option specified. A positive non-zero value expected.\n";
//			}
			throw(new exception());
		}
	}


	if (vm.count("MinMax-bounds")) {
		userInputs->setMinMaxBounds(vm["MinMax-bounds"].as<std::string>());
		//First sets the max-value to all the variable and then replace with the supplied MinMax-bounds

		userInputs->setVariableBounds();	//parses the user input bounds and assigns to the struct
		//exit(1);
	}


	if (vm.count("tool")) { //Compulsory Options but set to pwa by default
		userInputs->setTool((vm["tool"].as<std::string>()));

		if(boost::iequals(userInputs->getTool(),"pwa")==false){
			std::cout << "Invalid tool option specified. Expected \"pwa\".\n";
			throw(new exception());
		}
	}


	if (vm.count("segment-relative-error")) {	//the value \Epsilon_\FwdBwd used in the segmentation process in the Learning Algorithm
		userInputs->setClusterError((vm["segment-relative-error"].as<double>()));
		if (userInputs->getClusterError() <= 0) { //for 0 or negative precision
			std::cout << "Invalid segment-relative-error value specified. A positive non-zero value expected.\n";
			throw(new exception());
		}
	}
	/*if (vm.count("cluster-error-tol")) {
		userInputs->setClusterError((vm["cluster-error-tol"].as<double>()));
		if (userInputs->getClusterError() <= 0) { //for 0 or negative precision
			std::cout << "Invalid cluster-error value specified. A positive non-zero value expected.\n";
			throw(new exception());
		}
	}*/

	if (vm.count("segment-relative-fine-error")) {	//the value \Epsilon_\Bwd used in the segmentation process in the Learning Algorithm
		userInputs->setSegmentationFineError((vm["segment-relative-fine-error"].as<double>()));
		if (userInputs->getSegmentationFineError() <= 0) { //for 0 or negative precision
			std::cout << "Invalid segment-relative-fine-error value specified. A positive non-zero value expected.\n";
			throw(new exception());
		}
	}


	if (vm.count("lmm-step-size")) {	//enable/disable filtering out last segment during segmentation process in the Learning Algorithm
		userInputs->setLmmStepSize((vm["lmm-step-size"].as<int>()));
		if ((userInputs->getLmmStepSize() != 2)
				&& (userInputs->getLmmStepSize() != 3)
				&& (userInputs->getLmmStepSize() != 4)
				&& (userInputs->getLmmStepSize() != 5)
				&& (userInputs->getLmmStepSize() != 6)) {
			std::cout
					<< "Invalid lmm-step-size value specified. Available expected values are 2/3/4/5 and 6.\n";
			throw(new exception());
		}
	}

	if (vm.count("filter-last-segment")) {	//enable/disable filtering out last segment during segmentation process in the Learning Algorithm
		userInputs->setFilterLastSegment((vm["filter-last-segment"].as<int>()));
		if ((userInputs->getFilterLastSegment() != 0) && (userInputs->getFilterLastSegment() != 1)) { //options are either 0 or 1
			std::cout << "Invalid filter-last-segment value specified. A 0 or 1 value is expected.\n";
			throw(new exception());
		}
	}


	if (vm.count("cluster-algo")) { //Compulsory Options but set to thull by default
		userInputs->setClusterAlgorithm((vm["cluster-algo"].as<std::string>()));
		if (boost::iequals(userInputs->getClusterAlgorithm(),"dbscan")==false) {
			if(boost::iequals(userInputs->getClusterAlgorithm(),"dtw")==false){
				/*if(boost::iequals(userInputs->getClusterAlgorithm(),"piecelinear")==false){
					std::cout << "Invalid option specified. Expected \"dbscan\", or \"dtw\", or \"piecelinear\" .\n";
					throw(new exception());
				}*/
				std::cout << "Invalid option specified. Expected \"dbscan\", or \"dtw\".\n";
				throw(new exception());
			}
		}
	}


	if (vm.count("ode-speedup")) {
		userInputs->setOdeSpeedup((vm["ode-speedup"].as<int>()));
	}


	if (vm.count("dbscan-eps-dist")) {
		userInputs->setDbScanEpsDist((vm["dbscan-eps-dist"].as<double>()));
	}

	if (vm.count("dbscan-min-samples")) {
		userInputs->setDbScanMinSamples((vm["dbscan-min-samples"].as<int>()));
	}


	if (vm.count("correlation-threshold")) {
		userInputs->setCorrelationThreshold((vm["correlation-threshold"].as<double>()));
	}
	if (vm.count("distance-threshold")) {
		userInputs->setDistanceThreshold((vm["distance-threshold"].as<double>()));
	}





	if (vm.count("degree")) {
		userInputs->setPolyDegree((vm["degree"].as<int>()));
		if (userInputs->getPolyDegree() < 1) { //for 0 or negative number of locations
			std::cout << "Invalid degree option specified. A positive Integer value is expected.\n";
			throw(new exception());
		}
	}



	if (vm.count("boundary-degree")) {
		userInputs->setBoundaryDegree((vm["boundary-degree"].as<int>()));
		if (userInputs->getBoundaryDegree() < 1) { //for 0 or negative number of locations
			std::cout << "Invalid boundary-degree option specified. A positive Integer value is expected.\n";
			throw(new exception());
		}
	}


	if (vm.count("t2-values")) { //Todo: Assuming user respects the syntax as specified in the menu
		userInputs->setT2Values(vm["t2-values"].as<std::string>());
	}


	if (vm.count("t3-values")) { //Todo: Assuming user respects the syntax as specified in the menu
		userInputs->setT3Values(vm["t3-values"].as<std::string>());
	}


	if (vm.count("max-traces")) {
		userInputs->setMaxTraces((vm["max-traces"].as<int>()));
		if (userInputs->getMaxTraces() <= 0) { //for 0 or negative sampling-time
			std::cout << "Invalid max-traces option specified. A positive non-zero value expected.\n";
			throw(new exception());
		}
	}

	if (vm.count("max-generate-trace-size")) {
		userInputs->setMaxGenerateTraceSize((vm["max-generate-trace-size"].as<int>()));
	}


	if (vm.count("max-stoptime")) {
		userInputs->setMaxStoptime((vm["max-stoptime"].as<double>()));
		if (userInputs->getMaxStoptime() <= 0) { //for 0 or negative sampling-time
			std::cout << "Invalid max-stoptime option specified. A positive non-zero value expected.\n";
			throw(new exception());
		}
	}

	if (vm.count("max-stoptime-equitest")) {
		userInputs->setMaxStoptimeEquitest((vm["max-stoptime-equitest"].as<double>()));
		if (userInputs->getMaxStoptimeEquitest() <= 0) { //for 0 or negative sampling-time
			std::cout << "Invalid max-stoptime-equitest option specified. A positive non-zero value expected.\n";
			throw(new exception());
		}
	}

	if (userInputs->getMaxStoptimeEquitest() == 0 || userInputs->getMaxStoptime() == 0) {

		if (boost::iequals(userInputs->getEngine(),"equi-test")==true) {
			std::cout << "Missing max-stoptime and/or max-stoptime-equitest   options for the tool. \n";
			throw(new exception());
		}
		// not compulsory for txt2slx and simu

	}

	//Fix bigger time for Total HybridLearner to stop and smaller time for Equivalence Testing Loop
	if (userInputs->getMaxStoptimeEquitest() >  userInputs->getMaxStoptime()) {
		double tmp = userInputs->getMaxStoptime();
		userInputs->setMaxStoptime(userInputs->getMaxStoptimeEquitest());
		userInputs->setMaxStoptimeEquitest(tmp);
	}


	if (vm.count("extra")) {
		userInputs->setExtra(vm["extra"].as<std::string>());
	}

	if (vm.count("goal")) {
		userInputs->setGoalProperty(vm["goal"].as<std::string>());
	}

	if (vm.count("initial-value")) {
		userInputs->setInitialSet(vm["initial-value"].as<std::string>());
	}

	if (vm.count("input-signal-type")) {
		userInputs->setInputSignalType(vm["input-signal-type"].as<std::string>());
	}

	if (vm.count("numberOf-control-points")) {
		userInputs->setNumberOfControlPoints(vm["numberOf-control-points"].as<std::string>());
	}

	if (vm.count("sine-wave-parameter")) {
		userInputs->setInputSignalSineWaveParameter(vm["sine-wave-parameter"].as<std::string>());
	}

	if (vm.count("seed"))  {	// seed for random number generation
		userInputs->setSeed(vm["seed"].as<int>());
	}

	if (vm.count("simulation-check"))  {	// Enable or Disable Safety-violation check during initial simulations.
		userInputs->setSimulationCheck(vm["simulation-check"].as<int>());
	}


	//if (vm.count("simu-init-size") || vm.count("simu-init-point")) {
	if (vm.count("simu-init-size")) {
		if (vm.count("simu-init-size"))  {	// random points
			userInputs->setSimuInitSize(vm["simu-init-size"].as<int>());
		} else {
			userInputs->setSimuInitSize(0);
		}
//		if (vm.count("simu-init-point")) {	// user supplied points
//			userInputs->setSimuInitPoint(vm["simu-init-point"].as<std::string>());
//		}

	} else {
		std::cout << "Missing the simu-init-size parameter. \n";
		throw(new exception());
	}


	if (vm.count("output-file")) {
		userInputs->setOutputFilename(vm["output-file"].as<std::string>());
	} else {
		fileName = "out.txt";
		userInputs->setOutputFilename(fileName); //default file is set to out.txt
	}




}

//This is for the Learned model: variable name-mapping
void mapsVariable_to_Polytope(user_inputs::ptr& user, polytope::ptr& poly){

	polytope::ptr p = polytope::ptr(new polytope());
	p->setIsEmpty(false);
	p->setIsUniverse(true);

	//unsigned int dim=0;
	if (user->getModel()==1) {
		//dim = 2;	//Circular motion model
		p->insert_to_map("x0", 0);
		p->insert_to_map("x1", 1);

		//var_map->insert_to_map("x0",0);
		//var_map->insert_to_map("x1",1);
	} else if (user->getModel()==2) {
		//dim = 2;	//Oscillator model
		p->insert_to_map("x0", 0);
		p->insert_to_map("x1", 1);
	} else if (user->getModel()==3) {
		//dim = 2;	//Shared Gas Burner model
		p->insert_to_map("x0", 0);
		p->insert_to_map("x1", 1);
	} else if (user->getModel()==4) {
		//dim = 4;	//Navigation Model (but the original model has x1,x2,v1 and v2
		p->insert_to_map("x0", 0);
		p->insert_to_map("x1", 1);
		p->insert_to_map("x2", 2);
		p->insert_to_map("x3", 3);
	} else if (user->getModel()==5) {
		//dim = 5;	//AFC Model (but the original model has padel_angle, engine_speed, AF_ref, AF, and controller_mode
		p->insert_to_map("x0", 0);
		p->insert_to_map("x1", 1);
		p->insert_to_map("x2", 2);
		p->insert_to_map("x3", 3);
		p->insert_to_map("x4", 4);
	} else if (user->getModel()==6) {
		//dim = 5;	//AT Model: (but the original model has Throttle, BrakeTorque, Gear, EngineRPM, and VehicleSpeed)
		p->insert_to_map("x0", 0);
		p->insert_to_map("x1", 1);
		p->insert_to_map("x2", 2);
		p->insert_to_map("x3", 3);
		p->insert_to_map("x4", 4);
	} else if (user->getModel()==7) {
		//dim = 3;	//Ball Model: (but the original model has u, x, v
		p->insert_to_map("x0", 0);
		p->insert_to_map("x1", 1);
		p->insert_to_map("x2", 2);
	}

	poly = p;
}

