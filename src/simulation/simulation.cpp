/*
 * simulation.cpp
 *
 *  Created on: 05-Oct-2021
 *      Author: amit
 */


#include "simulation.h"

using namespace std;
using namespace matlab::engine;

/*
 * This function is called from two points:
 * 1) within a loop for multiple simulation from initial-simulation
 * 2) from equivalence-testing
 */
void simulate_model(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr& userInput, std::vector<double> initial_CE_values, intermediateResult::ptr& inter) {
	//Here we execute only simulink Model designed as Abstract HS without any separate Input and Output variables
	//unsigned int dim
	if (userInput->getModel() == 1) {
		runCircle(ep, userInput, initial_CE_values, inter);
	} else if (userInput->getModel() == 2) {
		runOscillator(ep, userInput, initial_CE_values, inter);
	} else if (userInput->getModel() == 3) {
		runSharedGasBurner(ep, userInput, initial_CE_values, inter);
	} else if (userInput->getModel() == 4) {
		runNavigation_inst1(ep, userInput, initial_CE_values, inter);
	}/* else if (userInput->getModel() == 5) {
		runAFC(ep, userInput, initial_CE_values, inter);
	}*/

	//std::cout <<"Back in the simulate Function" << std::endl;

}

/*
 * This function is called from two points:
 * 1) within a loop for multiple simulation from initial-simulation
 * 2) from equivalence-testing
 */
void simulate_model(std::unique_ptr<MATLABEngine> &ep,
		user_inputs::ptr &userInput,
		std::list<struct timeseries_input> initial_CE_values,
		std::vector<double> output_variable_init_values,
		intermediateResult::ptr &inter) {

//Here we execute only simulink Model with separate Input and Output variables
	//unsigned int dim
	/*if (userInput->getModel() == 1) {
		runCircle(ep, userInput, initial_CE_values, inter);
	} else if (userInput->getModel() == 2) {
		runOscillator(ep, userInput, initial_CE_values, inter);
	} else if (userInput->getModel() == 3) {
		runSharedGasBurner(ep, userInput, initial_CE_values, inter);
	} else if (userInput->getModel() == 4) {
		runNavigation_inst1(ep, userInput, initial_CE_values, inter);
	} else */ if (userInput->getModel() == 5) {
		runAFC(ep, userInput, initial_CE_values, inter);
	} else if (userInput->getModel() == 6) {
		runAT(ep, userInput, initial_CE_values, inter);
	} else if (userInput->getModel() == 7) {
		runBBall_with_input(ep, userInput, initial_CE_values, output_variable_init_values, inter);
	}

	//std::cout <<"Back in the simulate Function" << std::endl;

}

//simulate with multiple initial points and dump the output into another file. Now also test for safety violation break and return CE_dataStruct if violation Found.
void simulate(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr &user,
		std::list<std::vector<double> > list_initial_points,
		intermediateResult::ptr &intermediate) {

//	 std::cout <<"Inside simulate List function Engine ep = "<< ep << std::endl;
//	 std::cout <<"Inside simulate List function Engine &ep = "<< &ep << std::endl;

	/*https://stackoverflow.com/questions/19564450/concatenate-two-huge-files-in-c/19567371*/
	//std::ifstream file_a ("a.txt", std::ios_base::binary);
	//std::ifstream file_b("b.txt", std::ios_base::binary);

	std::string simuFileName = "simulation_", tmpSimuFile = "tmp_simulation_";
	simuFileName.append(user->getOutputFilename());
	//user->setInputFilename(simuFileName);
	tmpSimuFile.append(user->getOutputFilename());

	user->setSimulationFilename(simuFileName);
	std::string deleteCommand = "rm ";
	deleteCommand.append(simuFileName);
	int x = system(deleteCommand.c_str());
	if (x == -1) {
		std::cout <<"Error executing cmd: " << deleteCommand <<std::endl;
	}
	// *************** mergedFile deleted if exists ***************

	unsigned int matlab_execution_count=0;

	/*
	//std::ofstream finalFile("finalFile.txt",  std::ios_base::binary | std::ios_base::app);
	std::ofstream finalFile(simuFileName,  std::ios_base::binary | std::ios_base::app);

	 for(std::list < std::vector<double> >::iterator it=list_initial_points.begin(); it !=list_initial_points.end(); it++) {
		std::vector<double> init_point = (*it);


		simulate(ep, user, init_point, intermediate); //this will generate the file "result.tsv" for this init_point

		matlab_execution_count++;
		user->setNumberMatlabSimulationExecuted(matlab_execution_count);

		std::string resultFileName = getSimulationOutputFileName(user, intermediate);

		std::ifstream file_a (resultFileName, std::ios_base::binary);

		finalFile.seekp(0, std::ios_base::end);	//seek the record point to end_of_file
		finalFile << file_a.rdbuf();	//append the file_a in the previous file

	}*/
	/*
	 * The above approach gave error while running in our Google Cloud setup but did not show any issues in my Personal Desktop
	 *
	 * So, trying to use simple system command to concate two files into a third file. This will avoid the use of stream operation of C++
	 * ************ cat /home/amit/3dplot.plt /home/amit/amit.java > /home/amit/raj.txt	 ************************
	 */

	std::string cmd="cat ";

	for(std::list < std::vector<double> >::iterator it=list_initial_points.begin(); it !=list_initial_points.end(); it++) {
			std::vector<double> init_point = (*it);

			simulate_model(ep, user, init_point, intermediate); //this will generate the file "result.tsv" for this init_point

			std::string resultFileName = getSimulationOutputFileName(user->getModel(), intermediate->getToolRootPath());
			//cout << "Absolute path of the simulation generated output file: " << resultFileName << endl;
			/*
			 * cat resultFile > tmpSimuFile //on the 1st iteration
			 *
			 * cat  simuFileName  resultFile  >  tmpSimuFile   //from 2nd iteration onwards
			 *
			 * cp tmpSimuFile  simuFileName
			 *
			 */

			if (matlab_execution_count==0) {	//1st iteration
				cmd="cat ";
				cmd.append(resultFileName);
				cmd.append(" > ");
				cmd.append(tmpSimuFile);
				//cout <<"Iteration "<< matlab_execution_count <<"  Cmd: " << cmd <<endl;
				x = system(cmd.c_str());
				if (x == -1) {
					std::cout <<"Error executing cmd: " << cmd <<std::endl;
				}
			} else {	//2nd iterations onwards
				cmd="cat ";
				cmd.append(simuFileName);
				cmd.append(" ");
				cmd.append(resultFileName);
				cmd.append(" > ");
				cmd.append(tmpSimuFile);
				//cout <<"Iteration "<< matlab_execution_count <<"  Cmd: " << cmd <<endl;
				x = system(cmd.c_str());
				if (x == -1) {
					std::cout <<"Error executing cmd: " << cmd <<std::endl;
				}
			}

			cmd="cp ";
			cmd.append(tmpSimuFile);
			cmd.append(" ");
			cmd.append(simuFileName);
			//cout << "  Cmd: " << cmd <<endl;
			x = system(cmd.c_str());
			if (x == -1) {
				std::cout <<"Error executing cmd: " << cmd <<std::endl;
			}
			matlab_execution_count++;
			user->setNumberMatlabSimulationExecuted(matlab_execution_count);
		}

}


////simulate with multiple initial points and dump the output into another file. Now also test for safety violation break and return CE_dataStruct if violation Found.
void simulate(std::unique_ptr<MATLABEngine> &ep, user_inputs::ptr &user,
		std::list<struct timeseries_all_var> input_for_simulation, std::list<std::vector<double>> output_for_simulation,
		intermediateResult::ptr &intermediate, struct simu_dataStruct &violation_result) {

	/*https://stackoverflow.com/questions/19564450/concatenate-two-huge-files-in-c/19567371*/
	//std::ifstream file_a ("a.txt", std::ios_base::binary);
	//std::ifstream file_b("b.txt", std::ios_base::binary);

	std::string simuFileName = "simulation_", tmpSimuFile = "tmp_simulation_";
	simuFileName.append(user->getOutputFilename());
	//user->setInputFilename(simuFileName);
	tmpSimuFile.append(user->getOutputFilename());

	user->setSimulationFilename(simuFileName);
	std::string deleteCommand = "rm ";
	deleteCommand.append(simuFileName);
	deleteCommand.append(" ");
	deleteCommand.append(tmpSimuFile);
	int x = system(deleteCommand.c_str());	//Deleting simulation_modelFile.txt and tmp_simulation_modelFile.txt
	if (x == -1) {
		std::cout <<"Error executing cmd: " << deleteCommand <<std::endl;
	}
	// *************** mergedFile deleted if exists ***************

	unsigned int matlab_execution_count=0;

	/*
	//std::ofstream finalFile("finalFile.txt",  std::ios_base::binary | std::ios_base::app);
	std::ofstream finalFile(simuFileName,  std::ios_base::binary | std::ios_base::app);

	 for(std::list < std::vector<double> >::iterator it=list_initial_points.begin(); it !=list_initial_points.end(); it++) {
		std::vector<double> init_point = (*it);


		simulate(ep, user, init_point, intermediate); //this will generate the file "result.tsv" for this init_point

		matlab_execution_count++;
		user->setNumberMatlabSimulationExecuted(matlab_execution_count);

		std::string resultFileName = getSimulationOutputFileName(user, intermediate);

		std::ifstream file_a (resultFileName, std::ios_base::binary);

		finalFile.seekp(0, std::ios_base::end);	//seek the record point to end_of_file
		finalFile << file_a.rdbuf();	//append the file_a in the previous file

	}*/
	/*
	 * The above approach gave error while running in our Google Cloud setup but did not show any issues in my Personal Desktop
	 *
	 * So, trying to use simple system command to concate two files into a third file. This will avoid the use of stream operation of C++
	 * ************ cat /home/amit/3dplot.plt /home/amit/amit.java > /home/amit/raj.txt	 ************************
	 */

	simulation_trace_testing::ptr simu_test = simulation_trace_testing::ptr(new simulation_trace_testing());;

	std::string cmd="cat ";
	unsigned int counting=1;

	std::list<std::vector<double> >::iterator it_out_val = output_for_simulation.begin(); //iterator for the output variables
	for (std::list<struct timeseries_all_var>::iterator it =
			input_for_simulation.begin(); it != input_for_simulation.end(); it++, it_out_val++) {

		cout <<"counting = " << counting <<endl;

		std::list<struct timeseries_input> init_point = (*it).timeseries_signal;
		std::vector<double> output_variable_init_values = (*it_out_val);

		simulate_model(ep, user, init_point, output_variable_init_values, intermediate); //this will generate the file "result.tsv" for this init_point

		std::string resultFileName = getSimulationOutputFileName(user->getModel(), intermediate->getToolRootPath());
		//cout << "Absolute path of the simulation generated output file: " << resultFileName << endl;
		/*
		 * cat resultFile > tmpSimuFile //on the 1st iteration
		 * cat  simuFileName  resultFile  >  tmpSimuFile   //from 2nd iteration onwards
		 * cp tmpSimuFile  simuFileName
		 *
		 */

		if (matlab_execution_count==0){	//1st iteration
			cmd="cat ";
			cmd.append(resultFileName);
			cmd.append(" > ");
			cmd.append(tmpSimuFile);
			//cout <<"Iteration "<< matlab_execution_count <<"  Cmd: " << cmd <<endl;
			x = system(cmd.c_str());
			if (x == -1) {
				std::cout <<"Error executing cmd: " << cmd <<std::endl;
			}
		} else {	//2nd iterations onwards
			cmd="cat ";
			cmd.append(simuFileName);
			cmd.append(" ");
			cmd.append(resultFileName);
			cmd.append(" > ");
			cmd.append(tmpSimuFile);
			//cout <<"Iteration "<< matlab_execution_count <<"  Cmd: " << cmd <<endl;
			x = system(cmd.c_str());
			if (x == -1) {
				std::cout <<"Error executing cmd: " << cmd <<std::endl;
			}
		}

		cmd="cp ";
		cmd.append(tmpSimuFile);
		cmd.append(" ");
		cmd.append(simuFileName);
		//cout << "  Cmd: " << cmd <<endl;
		x = system(cmd.c_str());
		if (x == -1) {
			std::cout <<"Error executing cmd: " << cmd <<std::endl;
		}
		matlab_execution_count++;
		user->setNumberMatlabSimulationExecuted(matlab_execution_count);

		if (user->getSimulationCheck()) {	//1 for enabled 0 for disable
			violation_result.total_simulations += 1;
			simu_test->safetyViolationCheck(user, resultFileName, violation_result);
			if (violation_result.foundViolation) {
				break;
			}
		}

	} //End of all simulation traces
}

//Now the function returns the Absolute path
const std::string getSimulationOutputFileName(unsigned int model, const std::string &toolRootPath) {

	//std::string resultfile= intermediate->getToolRootPath();
	std::string resultfile = "";
	resultfile.append(toolRootPath);

	/*if (user->getModel() == 1) {
		//resultfile = "../src/benchmark/circle/result.tsv";
		resultfile.append("/src/benchmark/circle/result.txt");
	} else if (user->getModel() == 2) {
		//resultfile = "../src/benchmark/oscillator/result.tsv";
		resultfile.append("/src/benchmark/oscillator/result.txt");
	} else if (user->getModel() == 3){
		//resultfile = "../src/benchmark/shared_gas_burner/result.tsv";
		resultfile.append("/src/benchmark/shared_gas_burner/result.txt");
	}*/

	if (model == 1) {
		//resultfile = "../src/benchmark/circle/result.tsv";
		resultfile.append("/src/benchmark/circle/result.txt");
	} else if (model == 2) {
		//resultfile = "../src/benchmark/oscillator/result.tsv";
		resultfile.append("/src/benchmark/oscillator/result.txt");
	} else if (model == 3){
		//resultfile = "../src/benchmark/shared_gas_burner/result.tsv";
		resultfile.append("/src/benchmark/shared_gas_burner/result.txt");
	} else if (model == 4){
		//resultfile = "../src/benchmark/nav_inst1/result.tsv";
		resultfile.append("/src/benchmark/nav_inst1/result.txt");
	} else if (model == 5){
		resultfile.append("/src/benchmark/AFC/result.txt");
	} else if (model == 6){
		resultfile.append("/src/benchmark/AT/result.txt");
	} else if (model == 7){
		resultfile.append("/src/benchmark/bball_with_input/result.txt");
	}


	return resultfile;
}

bool safetyCheck(user_inputs::ptr &user, double &violation_TimeHorizon) {

//	extern  unsigned int log_set;
//	std::ofstream log_file("bbc4cps_log_file.txt",  std::ios_base::binary | std::ios_base::app);

	unsigned int dim = user->getSysDimension();

	const char* resultfile;
//TODO: we can use the intermediate class to get the absolute path
	if (user->getModel() == 1) {
		//resultfile = "../src/benchmark/circle/result.tsv";
		resultfile = "../src/benchmark/circle/result.txt";
	} else if (user->getModel() == 2) {
		//resultfile = "../src/benchmark/oscillator/result.tsv";
		resultfile = "../src/benchmark/oscillator/result.txt";
	} else if (user->getModel() == 3){
		//resultfile = "../src/benchmark/shared_gas_burner/result.tsv";
		resultfile = "../src/benchmark/shared_gas_burner/result.txt";
	} else if (user->getModel() == 4){
		resultfile = "../src/benchmark/nav_inst1/result.txt";
	} else if (user->getModel() == 5){
		resultfile = "../src/benchmark/AFC/result.txt";
	} else if (user->getModel() == 6){
		resultfile = "../src/benchmark/AT/result.txt";
	} else if (user->getModel() == 7){
		resultfile = "../src/benchmark/bball_with_input/result.txt";
	}

	//std::cout << "\nUnsafe Polytope going to create polytope: \n";
	polytope::ptr unsafe_poly;
	double gt_lower=0.0, gt_upper=user->getTimeHorizon();	//default 0 to time-horizon
	string_to_polytope_withTimeBound(user->getGoalString(), unsafe_poly, gt_lower, gt_upper);	//Returns a polytope from string along with lower and upper time bound
	//Taking care of time-constraints (gt>=10 & gt<=time-horizon)
	//cout <<"Time lower = "<< gt_lower << "  time upper=" <<gt_upper <<endl;

	std::ifstream in(resultfile);	//This is the file generated by running the simulation. So it always maintains the order of the outputs (time, variables)

	bool found=false;
	if (in) {
		std::string line1;
		double time_t=0, distance=0.0;
		std::vector<double> variable_value(dim);
		while (std::getline(in, line1)) {
			std::istringstream word(line1);
			word >> time_t;	//reads the first number which is time value

			for (unsigned int i=0; i < dim; i++) {
				word >> variable_value[i]; //Reading rest of the columns consisting of variables value.
			}
			//Step 2) Now test/check if this generated data actually Falsify the safety property.
			/*std::cout << "\nUnsafe Polytope: \n";
			std::cout << unsafe_poly->getCoeffMatrix() << "\n";
			for (unsigned int i=0; i < unsafe_poly->getColumnVector().size(); i++){
				std::cout <<unsafe_poly->getColumnVector()[i] << std::endl;
			}*/

			//Todo: check if every system variable_value[i] is within the supplied input bounds/variable's invariant
			std::list<struct variable_bounds> list_VarBounds = user->getListVariableBounds(); //this list contains the MinMax bounds
			string varName = "";
			bool isValidBound = false;
			for (unsigned int i=0; i < dim; i++) {
				//variable_value[i]; //Reading variable's value.
				varName  = "x";
				varName.append(to_string(i));
				//std::cout <<"varName = " << varName << " value = " << variable_value[i] << "\t";
				isValidBound = variableBoundCheck(varName, variable_value[i], list_VarBounds);
				if (isValidBound == false) {
					found = false;
					break;
				}
			}
			//std::cout << std::endl;
			if (isValidBound == false) { //This is required to come out of the while loop
				//found = false; //already done above
				break;  //this will skip checking the below safety property
			}

			if (time_t >= gt_lower && time_t <= gt_upper) {
				distance = unsafe_poly->point_distance(variable_value); //returns 0 if point is inside the polytope
//				cout << "distance = "<< distance<<endl;
				/*if (log_set){
					 log_file << "(";
					for (unsigned int i=0; i < dim; i++) {
						log_file << variable_value[i]; //Reading rest of the columns consisting of variables value.
						if (i != (dim - 1)){
							log_file << " , ";
						}
					}
					log_file << ")  ";
					log_file << " distance = "<< distance<<endl;
				}*/
				if (distance == 0) {
					found = true;
					//Also return the Time-Bound when the violation is Found
					violation_TimeHorizon = time_t;
					break;
				}
			}
		} //end-while

		if (found) {
			cout << "Found a Valid Counter-example!!!"<<endl;
		} else {
			cout << "NO Valid Counter-example Found!!!"<<endl;
		}
	} //end of file reading

	in.close();	//closing the file

	return found;
}

/*
 * Returns True for Valid bound.
 * Returns True if the varName is within the supplied bounds, otherwise returns False.
 */
bool variableBoundCheck(string varName, double varValue, std::list<struct variable_bounds> list_VarBounds) {
	bool flag=false, varNotFound = true;
	double epsilon = 1e-7, diffValue=0.0; // 0.0000001;
	double diffValueLow = 0.0, diffValueHigh=0.0;
	for (std::list<struct variable_bounds>::iterator it = list_VarBounds.begin(); it != list_VarBounds.end(); it++) {
		if ((*it).variable_name == varName) { //for this variable
			//cout <<"varValue=" << varValue <<"   Min value="<< (*it).min_value << " and Max value="<<(*it).max_value << endl;
			//double low = (*it).min_value - varValue,  high = varValue - (*it).max_value;
			double low = (*it).min_value,  high = (*it).max_value;
			diffValueLow = abs(low - varValue);
			diffValueHigh = abs(high - varValue);
			diffValue = abs(low - varValue);
			//if (varValue > low || cond2) && (cond3 || cond4) {
			if (((varValue > low) || (diffValueLow < epsilon)) && ((varValue < high) || (diffValueHigh < epsilon))) {
//			if ((varValue >= (*it).min_value) && (varValue <= (*it).max_value)) { //checking the bounds
			//if ((varValue >= low) && (varValue <= high)) { //checking the bounds  ToDo: equal value is not comparing correctly for Double data type
				flag = true;
			} else {
				std::cout <<"Input Bound: violated by the Variable " << varName <<" Valid bound=[" << (*it).min_value << ", " << (*it).max_value << "] but value=" << varValue << endl;
				if (varValue == low) { //900==900 this did not return TRUE
					cout <<"Here varValue("<<varValue<<") >= low("<<low<<")" <<endl;
				}
				std::cout <<"Input Bound: violated by the Variable " << varName <<" Valid bound=[" << low << ", " << high << "] but value=" << varValue << endl;
				//cout <<"Amit this is comparison problem with 900 and varValue=" << varValue << " low=" << low << " and high="<<high <<endl;
				flag = false;
			}
			varNotFound = false;
			break; //found the matching variable
		}
	}
	if (varNotFound) { //this will never get executed since all variable has some bounds or max-value as the bounds
		std::cout <<"Error: Variable bounds not assigned!" <<endl;
		flag = true; //so considering Universal bounds
	}
	return flag;
}


std::list< std::vector<double> > getInternalPoints(polytope::ptr &poly, unsigned int n, myRandomNumberGenerator::ptr &randomGenObj) {
	std::list< std::vector<double> > res;
	/*
	 * Steps:
	 * 1) First assert if poly obeys the rule (check rows should be twice as dimension AND the pattern -1 and +1 should exists with rest 0)
	 * 2) For each dimensions with extracted bounds (lower,upper) generate n randomly uniform_real_distrubution values
	 * 3) Use these values to create points for simulation
	 *
	 * todo: Note this loop implementation may not work if the order of Constraints creation do not follow increasing order of the Dimension.
	 * Need to modify it later
	 *
	 */
	math::matrix<double> A = poly->getCoeffMatrix();
	std::vector<double> bounds = poly->getColumnVector();

	unsigned int rows, cols, dim;
	rows = A.size1();
	cols = A.size2();
	dim = cols;
	assert(rows == 2 * cols);	//For hyperbox number of constraints should be bounded (lower and upper)

	hyperbox::ptr hyperbox_poly = hyperbox::ptr(new hyperbox(dim));

	//For each dimension of the hyperbox generating a list of bounded values, which can be used as points
	std::vector<std::vector<double> > hyperbox_dimension_points(dim);
	for (unsigned int i=0;i<dim;i++){
		hyperbox_dimension_points[i].resize(n);	//each dimensions will have n values for generating points
	}

	unsigned int i=0, j=0;
	double rowFirst, rowSecond, l_bound, u_bound;
	//Creating a hyperbox from initial input_poly
	while (j < cols) {	//reading the none-zero dimensions
		if (A(i,j) != 0) {	//j is the dimension we are working on
			rowFirst = j * 2;	//
			rowSecond = j * 2 + 1;

			// found the dimension with non-zero value, which should be 1
			//cout  << "  " << A(rowFirst,j) << " and Next is  " << A(rowSecond,j);
			//One of these will be -1 and the other 1. Find and accordingly create lower and upper bounds on the dimension
			if (A(rowFirst, j) < A(rowSecond, j)) {
				l_bound = -1 * bounds[rowFirst];
				u_bound = bounds[rowSecond];
			} else {
				l_bound = -1 * bounds[rowSecond];
				u_bound = bounds[rowFirst];
			}
			hyperbox_poly->setDimensionBounds(j, l_bound, u_bound);

//			hyperbox_dimension_points[j] = getRandom(l_bound, u_bound, n);	//Pseudo random which will be repeated on every execution
			//hyperbox_dimension_points[j] = getPureRandom(l_bound, u_bound, n);	//purely random which will NOT be repeated on every execution
			hyperbox_dimension_points[j] = randomGenObj->getRandomNumbers(l_bound, u_bound, n);


		}
		i +=2;
		j++;
	}

	std::vector<double> point(dim); //A single point

	for (unsigned int i=0; i< n;i++) {
		for (unsigned int j=0; j<dim; j++){
			point[j] = hyperbox_dimension_points[j][i];
		}
		res.push_back(point);
	}

	return res;
}

/*
 * nos_simulations: the total number of simulation points
 * list_var_cps: number of control-points for each variable
 * polytope::ptr &poly: is the initial input polytope which has linear-constraints having bounds on the variables
 * Outputs: is a purely random control-points for each variable for generating input-signals for each simulations
 * By using a seed
 */
std::list<std::list<struct control_points> > getInternalControlPoints(polytope::ptr &poly, unsigned int nos_simulations,
		list<struct control_points> list_var_cps, myRandomNumberGenerator::ptr &randomGenObj) {
	std::list<std::list<struct control_points>> res_data;
	std::list< std::vector<double> > res;

	math::matrix<double> A = poly->getCoeffMatrix();
	std::vector<double> bounds = poly->getColumnVector();

	unsigned int rows, cols, dim;
	rows = A.size1();
	cols = A.size2();
	dim = cols;

//	cout <<"rows =" <<rows << "   and cols =" << cols << endl;
	assert(rows == 2 * cols);	//For hyperbox number of constraints should be bounded (lower and upper)

	//For each dimension of the hyperbox generating a list of bounded values, which can be used as points
	std::vector<std::vector<double> > hyperbox_dimension_points(dim);
	unsigned int index=0;
	for (std::list<struct control_points>::iterator it = list_var_cps.begin();it != list_var_cps.end();it++){ //each-variable will have N-control-points
		int numberOf_cp = (*it).numberOf_cp;
		//cout << "var_name:" << (*it).var_name << endl;
		//cout << "cps-size:" << (*it).numberOf_cp << endl;
		hyperbox_dimension_points[index].resize(numberOf_cp);	//each dimensions will have n values for generating points
		index++;
	}
	//cout << "nos_simulations:" << nos_simulations <<endl;
	//cout << "dim:" << dim <<endl;
	//cout << "A of poly is " << A <<endl;

	for (unsigned int simu_id=0; simu_id < nos_simulations; simu_id++) { //repeated for nos_simulations times

		hyperbox::ptr hyperbox_poly = hyperbox::ptr(new hyperbox(dim));
		unsigned int i=0, j=0;
		double l_bound, u_bound;
		unsigned int rowFirst, rowSecond;
		//Creating a hyperbox from initial input_poly
		while (j < cols) {	//reading the none-zero dimensions
			//std::cout << "rows = " << rows << "  cols = " << cols << endl;
			if (A(i,j) != 0) {	//j is the dimension we are working on
				rowFirst = j * 2;	//
				rowSecond = j * 2 + 1;
				// found the dimension with non-zero value, which should be 1
				//std::cout  << "  " << A(rowFirst,j) << " and Next is  " << A(rowSecond,j);
				//One of these will be -1 and the other 1. Find and accordingly create lower and upper bounds on the dimension
				if (A(rowFirst, j) < A(rowSecond, j)) {
					l_bound = -1 * bounds[rowFirst];
					u_bound = bounds[rowSecond];
				} else {
					l_bound = -1 * bounds[rowSecond];
					u_bound = bounds[rowFirst];
				}
				hyperbox_poly->setDimensionBounds(j, l_bound, u_bound);

				//cout <<"l_bound:" << l_bound <<"   u_bound:"<< u_bound <<endl;
//				hyperbox_dimension_points[j] = getPureRandom(l_bound, u_bound, hyperbox_dimension_points[j].size());
				hyperbox_dimension_points[j] = randomGenObj->getRandomNumbers(l_bound, u_bound, hyperbox_dimension_points[j].size());
				//cout <<"Checking out the Pure-Random numbers" << endl;
				//for (int x=0; x < hyperbox_dimension_points[j].size(); x++) {
				//	cout << hyperbox_dimension_points[j][x] << "\t";
				//}

			}
			i +=2;
			j++;
		}
		index=0;
		std::list<struct control_points> list_cp;
		for (std::list<struct control_points>::iterator it = list_var_cps.begin();it != list_var_cps.end();it++){ //each-variable will have N-control-points
			struct control_points cp_data;

			cp_data.numberOf_cp = (*it).numberOf_cp;
			cp_data.var_name = (*it).var_name;
			cp_data.var_type = (*it).var_type;
			cp_data.var_index = (*it).var_index;
			cp_data.cps = hyperbox_dimension_points[index];

			list_cp.push_back(cp_data);
			index++;
		}
		res_data.push_back(list_cp);
	}


	return res_data;
}

/*
 * nos_simulations: the total number of simulation points
 * list_var_cps: number of control-points for each variable
 * polytope::ptr &poly: is the initial input polytope which has linear-constraints having bounds on the variables
 * Outputs: is a pseudo random control-points for each variable for generating input-signals for each simulations
 */
std::list<std::list<struct control_points>> getInternalControlPoints(polytope::ptr &poly, unsigned int nos_simulations, list<struct control_points> list_var_cps) {
	std::list<std::list<struct control_points>> res_data;
	std::list< std::vector<double> > res;

	math::matrix<double> A = poly->getCoeffMatrix();
	std::vector<double> bounds = poly->getColumnVector();

	unsigned int rows, cols, dim;
	rows = A.size1();
	cols = A.size2();
	dim = cols;
	assert(rows == 2 * cols);	//For hyperbox number of constraints should be bounded (lower and upper)

	//For each dimension of the hyperbox (with bounded values), generate N x CP-points
	std::vector<std::vector<double> > hyperbox_dimension_N_controlPoints(dim);


	unsigned int index=0;
	for (std::list<struct control_points>::iterator it = list_var_cps.begin();it != list_var_cps.end();it++){ //each-variable will have N-control-points
		int numberOf_cp = (*it).numberOf_cp;

		//hyperbox_dimension_points[index].resize(numberOf_cp);	//each dimensions will have n values for generating control-points
		hyperbox_dimension_N_controlPoints[index].resize(nos_simulations * numberOf_cp);	//each dimensions will have (N x cp) number of control-points

		index++;
	}

	hyperbox::ptr hyperbox_poly = hyperbox::ptr(new hyperbox(dim));
	unsigned int i=0, j=0;
	double rowFirst, rowSecond, l_bound, u_bound;
	//Creating a hyperbox from initial input_poly
	while (j < cols) {	//reading the none-zero dimensions
		if (A(i,j) != 0) {	//j is the dimension we are working on
			rowFirst = j * 2;	//
			rowSecond = j * 2 + 1;

			// found the dimension with non-zero value, which should be 1
			//cout  << "  " << A(rowFirst,j) << " and Next is  " << A(rowSecond,j);
			//One of these will be -1 and the other 1. Find and accordingly create lower and upper bounds on the dimension
			if (A(rowFirst, j) < A(rowSecond, j)) {
				l_bound = -1 * bounds[rowFirst];
				u_bound = bounds[rowSecond];
			} else {
				l_bound = -1 * bounds[rowSecond];
				u_bound = bounds[rowFirst];
			}
			hyperbox_poly->setDimensionBounds(j, l_bound, u_bound);

			hyperbox_dimension_N_controlPoints[j] = getRandom(l_bound, u_bound, hyperbox_dimension_N_controlPoints[j].size());
			/*cout <<"\nChecking out the Random numbers" << endl;
			for (int x=0; x < hyperbox_dimension_N_controlPoints[j].size(); x++) {
				cout << hyperbox_dimension_N_controlPoints[j][x] << "\t";
			}*/

		}
		i +=2;
		j++;
	}

//Now use hyperbox_dimension_N_controlPoints containing N * cp control-points for each variable we assign it into hyperbox_dimension_points containing only cp control-points for each variable

	std::vector<unsigned int> indLoc_start(cols, 0);	//For each variable this indices should be maintained. Here cols=system-dimension
	std::vector<unsigned int> indLoc_end(cols, 0);	//For each variable this indices should be maintained

	for (unsigned int simu_id=0; simu_id < nos_simulations; simu_id++) { 	//repeated for nos_simulations times
		index=0;
		//For each dimension of the hyperbox generating a list of bounded values, which can be used as points
		std::vector<std::vector<double> > hyperbox_dimension_points(dim);

		std::list<struct control_points> list_cp;
		for (std::list<struct control_points>::iterator it = list_var_cps.begin();it != list_var_cps.end();it++) { //each-variable will have N-control-points
			struct control_points cp_data;
			cp_data.numberOf_cp = (*it).numberOf_cp;
			cp_data.var_name = (*it).var_name;
			cp_data.var_type = (*it).var_type;
			cp_data.var_index = (*it).var_index;
			indLoc_end[index] = indLoc_start[index] + (*it).numberOf_cp; //extract [indLoc_start to indLoc_end) values from hyperbox_dimension_N_controlPoints for index
			for (unsigned int i = indLoc_start[index]; i < indLoc_end[index]; i++) {
				hyperbox_dimension_points[index].push_back(hyperbox_dimension_N_controlPoints[index][i]);
			}
			cp_data.cps = hyperbox_dimension_points[index];

			indLoc_start[index] = indLoc_end[index];

			list_cp.push_back(cp_data);
			index++;
		}
		res_data.push_back(list_cp);
	}

	return res_data;
}

void fixed_step_signal(double th, std::vector<double> cps, std::vector<double> &time_vector, std::vector<double> &data_vector) {
// **** This code is for ONE variable *********
	//double th=50;
	int nos_cp= cps.size();
	double hold_time_dur = th/nos_cp, small_value=1e-7;	//0.0000001; //1e-5;
	//data [cp1 cp1  cp2  cp2  cp3  cp3]
	//timeVector[0 hold_time_dur   hold_time_dur+small_value  Next-hold_time_dur  etc]
	std::vector<double> timeVector(nos_cp * 2);
	std::vector<double> dataVector(nos_cp * 2);
	//std::vector<double> cps(nos_cp);  //This is to be generated Randomly using user's input bounds
//	cps.resize(nos_cp);
//	cps[0]=40;
//	cps[1]=60;

	double sum_holdtime=0, start_val=0;
	unsigned int index=0;
	for(int i=0; i< nos_cp; i++) {
		if (i==0) {
			start_val = 0;
		} else {
			start_val = sum_holdtime + small_value;
		}
		timeVector[index] = start_val;
		dataVector[index] = cps[i];
		index++;

		sum_holdtime += hold_time_dur;
		timeVector[index] = sum_holdtime;
		dataVector[index] = cps[i];
		index++;

	}
// **** Code for ONE variable *********

	time_vector = timeVector;
	data_vector = dataVector;
}

//Function to generate constant-piecewise-linear signal, where the hold-time is fixed/uniform for each control-points
void linear_signal(double th, std::vector<double> cps, std::vector<double> &time_vector, std::vector<double> &data_vector) {
	// **** This code is only for a single variable *********
	//double th=50;
	int nos_cp= cps.size();
	double hold_time_dur=0.0;
	if (nos_cp > 1) {
		hold_time_dur = th/(nos_cp-1);
	} else if (nos_cp <= 1) {
		std::cout << "\nTerminating BBC4CPS, caused due to error in command-line inputs.\n" ;
		std::cout << "Invalid number-of-control-points. Minimum number of fixed-linear control-points for a variable is 2.\n";
		exit(0);
	}

	//data [cp1 cp2  cp3]
	//timeVector[0 hold_time_dur*1   hold_time_dur*2]
	std::vector<double> timeVector(nos_cp);
	std::vector<double> dataVector(nos_cp);

	unsigned int index=0;
	for(int i=0; i< nos_cp; i++) {
		timeVector[i] = i * hold_time_dur;
		dataVector[i] = cps[i];
	}
	timeVector[(nos_cp - 1)] = th;	//to replace with the time-horizon value for the last CP since (i*hold_time_dur) may be less than 'th' due to numerical error
	// **** Code for ONE variable *********

	time_vector = timeVector;
	data_vector = dataVector;
}

//Function to generate spline signal, where the hold-time is fixed/uniform for each control-points
void spline_signal(std::unique_ptr<MATLABEngine> &ep, double th, std::vector<double> cps, std::vector<double> &time_vector, std::vector<double> &data_vector) {
	// **** This code is only for a single variable *********
	//double th=50;
	int nos_cp= cps.size();
	double hold_time_dur=0.0;
	if (nos_cp > 1) {
		hold_time_dur = th/(nos_cp-1);
	} else if (nos_cp <= 1) {
		std::cout << "\nTerminating BBC4CPS, caused due to error in command-line inputs.\n" ;
		std::cout << "Invalid number-of-control-points. Minimum number of control-points for a variable is 2 for spline signal type.\n";
		exit(0);
	}

	//data [cp1 cp2  cp3]
	//timeVector[0 hold_time_dur*1   hold_time_dur*2]
	std::vector<double> timeVector(nos_cp);
	std::vector<double> dataVector(nos_cp);

	for(unsigned int i=0; i< nos_cp; i++) {
		timeVector[i] = i * hold_time_dur;
		dataVector[i] = cps[i];
	}
	timeVector[(nos_cp - 1)] = th;	//to replace with the time-horizon value for the last CP since (i*hold_time_dur) may be less than 'th' due to numerical error
	// **** Code for ONE variable *********

//	time_vector = timeVector;
//	data_vector = dataVector;

	//**** code above this is same as linear. Now for the above timeVector (=x) and dataVector(y) we compute sp_y = spline(x,y,query_x) *****
	/*
	 * Matlab code will be
	 * query_x = 0:time_step:time_horizon     or any value (eg 0.5) instead of time_step
	 * sp_y = spline(x,y, query_time)
	 * time_vector = query_time
	 * data_vector = sp_y
	 */

	std::string cmd1 = "thorizon = ";
	cmd1.append(to_string(th));
	cmd1.append(";");
	ep->eval(convertUTF8StringToUTF16String(cmd1));


	std::vector<double> cppData = dataVector;
	size_t x=1, y=cppData.size();
	matlab::data::ArrayFactory factory;
	auto inputArray = factory.createArray({ x, y }, cppData.cbegin(), cppData.cend());
	ep->setVariable(u"myDataVector", inputArray);

	std::vector<double> cppTime = timeVector;
	assert(y == cppTime.size());
	matlab::data::ArrayFactory factory1;
	auto inputArray1 = factory1.createArray({ x, y }, cppTime.cbegin(), cppTime.cend());
	ep->setVariable(u"myTimeVector", inputArray1);

	std::string cmd2 = "query_time = 0:0.5:";
	cmd2.append(to_string(th));
	cmd2.append(";");
	ep->eval(convertUTF8StringToUTF16String(cmd2));

	std::string cmd3 = "sp_y = spline(myTimeVector, myDataVector, query_time);";
	ep->eval(convertUTF8StringToUTF16String(cmd3));

	matlab::data::TypedArray<double> query_time = ep->getVariable(u"query_time");
	std::vector<double> query_time_values(query_time.begin(), query_time.end());

	matlab::data::TypedArray<double> sp_y = ep->getVariable(u"sp_y");
	std::vector<double> sp_values(sp_y.begin(), sp_y.end());


	/*for(int i=0; i< query_time_values.size(); i++) {
		cout << query_time_values[i] << endl;
	}
	exit(1);*/


	time_vector = query_time_values;
	data_vector = sp_values;

}


void sine_wave_signal(double timeHorizon, double amplitude, double zero_offset, std::vector<double> &time_vector, std::vector<double> &data_vector) {
// **** This code is for ONE variable. It generate a full cycle sine wave for the given amplitude with starting from zero_offset *********

	unsigned int number_of_samples = 10; //a higher value gives better sine wave and more possibilities of covering full timeHorizon
								// Best value is number_of_samples = timeHorizon. so that per unit time a sampling is done.
	double value=0;



	float rads = M_PI/180;  //angle in radian, where M_PI is the pi value
	double step_size = 360 / timeHorizon; //for one full cycle

	int nos_cp= number_of_samples + 1;

	std::vector<double> timeVector(number_of_samples + 1);
	std::vector<double> dataVector(number_of_samples + 1);

	unsigned int iteration_size = timeHorizon / (number_of_samples - 1); //to obtain less number of iterations i.e., higher iteration_size
			// rather than more iterations which will have issue on index out of bound while storing values in variables timeVector and dataVector
	unsigned int index=0;
	for(int i=0; i<=timeHorizon; i+=iteration_size)
	{
		value = (float)(amplitude * sin(step_size * i * rads) + zero_offset);
		dataVector[index] = value;
		timeVector[index] = i;
		index++;
	}

	//last value replace with i==timehorizon
	value = (float)(amplitude * sin(step_size * timeHorizon * rads) + zero_offset);

	dataVector[number_of_samples] = value;	//last index as per zero-based indexing
	timeVector[number_of_samples] = timeHorizon;


// **** Code for ONE variable *********

	time_vector = timeVector;
	data_vector = dataVector;
}


