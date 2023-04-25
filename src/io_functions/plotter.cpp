/*
 * plotter.cpp
 *
 *  Created on: 26-Sep-2021
 *      Author: amit
 *
 *      ***Note: I made another important observation
 *      reading the values from the json file for variables (eg x0 , x1 , etc) Take the reading from enclosure=1 and for time take enclosure=0
 *      Otherwise, both enclosure=0 should also work.
 *
 */

#include "plotter.h"
#include <string>

#include <nlohmann/json.hpp>
#include <stdlib.h>	//for use of system command
#include <iostream>
#include <fstream>
#include <list>
#include <assert.h>

//TODO: Remember to keep this json namespace separeate from std namespace, their is a bug if kept together
using json = nlohmann::json;

/*
void setInitialValue(std::vector<double> &initial_CE_values, double value, string varName) {

}
*/


void plotter(user_inputs::ptr &user, intermediateResult::ptr &intermediate, std::vector<double> &initial_CE_values, list<struct timeseries_input> &CE_data_list) {


	std::string jsonFileName = "";
//	jsonFileName.append(intermediate->getOutputfilenameWithoutExtension());
//	jsonFileName.append("/");
//	jsonFileName.append(intermediate->getOutputfilenameWithoutExtension());
	jsonFileName.append(intermediate->getDReachSatSmt2filenameWithPathWithoutExtension());
	jsonFileName.append(".smt2.json");

	std::string outfile = intermediate->getOutputfilenameWithoutExtension(); //
	outfile.append(".data"); 	//File for printing all (variables') values obtained from Counter-example Trace

	std::string outfile_plot = user->getOutputFilename(); // File for plotting the counter-example for Visualization

	std::string x_var = user->getPlotVars().first_variable;
	std::string y_var = user->getPlotVars().second_variable;

	std::ifstream ifs(jsonFileName.c_str());
	json jf = json::parse(ifs);


	list<struct timeseries_input> CE_data;
	struct timeseries_input each_CE_data; //per variable this can be pushed in CE_data

	//std::list<struct control_points> sys_variables;

	//Initialize to default setting
	for (unsigned int i=0; i < user->getSysDimension(); i++) {
		struct control_points sys_var;
		sys_var.var_index = i;
		string varName =  "x"+to_string(i);
		sys_var.var_name = varName;
		sys_var.numberOf_cp = 0;			//Not required
		sys_var.var_type = "fixed-step";	//Not required
		sys_var.cps.resize(0);				//Not required

		each_CE_data.var_detail = sys_var;
		//sys_variables.push_back(sys_var);
		CE_data.push_back(each_CE_data);
	}
	//each_CE_data.var_detail = sys_variables;





	unsigned int numberOfJumps, numberOfVariables;//, numberOfDataPoints_perJump_1, numberOfDataPoints_perJump_0;

	unsigned int var_Index1=0, var_Index2=1;	//Default variable index 0 and 1
	//Determine the index of the Plotting Variables
	for (json::iterator it = jf.begin(); it != jf.end(); ++it) { //its only a single iteration coz of just "traces"

		numberOfVariables = it.value()[0].size();

		for (unsigned int i=0; i < it.value()[0].size(); i++) { //loop through the number of variables for the 0th Jump
			std::string var_name = it.value()[0][i]["key"];		//For the 0th Jump
			//std::cout << var_name <<std::endl;
			int len = var_name.length(); // eg return 5 for "t_0_0"
			int totchars = len - 4; //4 for "_0_0", so totchars is 1

			std::string var = var_name.substr(0, totchars);
			//std::cout <<"var = " <<var <<std::endl;
			if (var == x_var) {
				var_Index1 = i;		//Variable index begin from 0 (since i starts from 0)
			} else if (var == y_var) {
				var_Index2 = i;
			}

			//Let's use here to get the initial values
			//Populating the initial values of the 1st jumps of the 1st iteration of the 1st enclosure for all variables
			// Note: This code generate initial values of the CE. The above code is used for Plotting or CE visualization
			bool flagSet = false;
			unsigned int index_is=0;
			for (unsigned int x=0; x < numberOfVariables; x++) {	//search the index of the var in json file
				std::string varName = "x" + std::to_string(x);
				if (var == varName){
					index_is = x;
					flagSet = true;
				}
			}
			if (flagSet) {
				initial_CE_values[index_is] = it.value()[0][i]["values"][0]["enclosure"][1];
			}

			//initial_CE_values[index_is] = it.value()[0][i]["values"][0]["enclosure"][1];	//Taking only the 1th enclosure.
			//setInitialValue(initial_CE_values, it.value()[0][i]["values"][0]["enclosure"][0], var); //Modified back to [0]

		}
	}

//	std::cout <<"Variable Names are " <<  x_var << "  and  " << y_var << std::endl;
//	std::cout <<"Variable indices are " <<  var_Index1 << "  and  " << var_Index2 << std::endl;
//	std::ofstream outFile;
//	outFile.open(outfile);

	std::ofstream outFile_plot;
	outFile_plot.open(outfile_plot);

	//int CEtrace_required = 1;
	//if (CEtrace_required) {
	if (!(user->getIsAbstractHsModel())) {	//required only when model has separate input and output variables

		for (json::iterator it = jf.begin(); it != jf.end(); ++it) { //its only a single iteration coz of just "traces"
			numberOfJumps = it.value().size();		//Works
			numberOfVariables = it.value()[0].size();	//Works even with 0 index, the 1st mode
			//For each Jumps
			for (unsigned int jumps=0; jumps < numberOfJumps; jumps++) {
				for (unsigned int x=0; x < numberOfVariables; x++) {	//search the index of the var in json file
					std::string var_name = it.value()[jumps][x]["key"];
					int len = var_name.length(); // eg return 5 for "t_0_0"
					int totchars = len - 4; //4 for "_0_0", so totchars is 1
					std::string var = var_name.substr(0, totchars);

					vector<double> dataVector(it.value()[jumps][x]["values"].size());	//totalDataPoints
					vector<double> timeVector(it.value()[jumps][x]["values"].size());
					//cout <<"Variable name = "<< var << "  TotalData points = " <<it.value()[jumps][x]["values"].size() <<endl;
					unsigned int i=0; //i is used again after the for-loop
					for (i = 0; i< it.value()[jumps][x]["values"].size(); i++) {	//TotalDataPoint
						//dataVector[i] = it.value()[jumps][x]["values"][i]["enclosure"][0];
						dataVector[i] = it.value()[jumps][x]["values"][i]["enclosure"][1]; //taking variable values as enclosure 1 from .json
						timeVector[i] = it.value()[jumps][x]["values"][i]["time"][0];
					}
					setTimeseries_Data(CE_data, jumps, var, timeVector, dataVector);

					// ****** Code below this is the code to append trace to the CE obtained by the model-checker.  ******
					// ****** This code is to append on to the input variables points which is same as the previous/last point where the counterexample hits/stop.
					//Heuristic Approach 1: The last point (point until time-horizon, T) holds the same point (value) at point T_ce, where T_ce is the time point when the model checker finds safety violation
					//Note: this extrapolation of points using Heuristic Approach 1 did not helped in finding VALID Counterexample.
				/*	if (jumps == (numberOfJumps - 1)) { //Last jump for every variable add one extra data-point with timeVector=time-horizon and dataVector=last-value-of-dataVector
						vector<double> dataVector_Copy(1); 	vector<double> timeVector_Copy(1);
						dataVector_Copy[0] = dataVector[i-1];
						timeVector_Copy[0] = user->getTimeHorizon();
						setTimeseries_Data(CE_data, jumps+1, var, timeVector_Copy, dataVector_Copy); //jump +1 makes sure that this is not the 1st jump (as required for joining the data)
					}
				*/

					// ---------- End of Heuristic Approach 1 -------------------------

					//Heuristic Approach 2: The next time point is computed as y = y2 + delta_y and delta_y = (y2 - y1)
					// where y1 and y2 are the last two points at time points (T_ce - time-step) and T_ce,
					// the rest of the points are computed using y = y2 + i * delta_y for T_ce <= i <= T and y respects the user supplied bounds.
					// When y reaches the bound value, the rest of the y points holds the same bound value.
			/*

					if (jumps == (numberOfJumps - 1)) { //Last jump for every variable adds extra data-points until timeVector=time-horizon

						double current_time = timeVector[i-1]; //time point when the counterexample hits safety violation
						double ce_time_step = timeVector[i-1] - timeVector[i-2]; //counterexample time-step may be smaller/bigger than the user-supplied time-step.
						double delta_y = dataVector[i-1] - dataVector[i-2]; // where y1 = dataVector[i-2] and the last point y2 = dataVector[i-1]
						double current_y = dataVector[i-1];
						// compute next point until time-horizon or bound reaches
						double next_time = current_time, next_dataValue = current_y;
						vector<double> dataVector_Copy(1); 	vector<double> timeVector_Copy(1);
						double low_value=0.0, high_value=0.0;
						user->getVariablBounds(var, low_value, high_value); //retrieves the min and max values for the given variable name
						unsigned int touched_lower_bound = 0, touched_upper_bound = 0, delta_zero = 0; //flag to detect if a bound is reached
						while (next_time <= user->getTimeHorizon()) {
							next_time = next_time + ce_time_step;
							next_dataValue = next_dataValue + delta_y;
							if (delta_y==0) { //for constant variable
								delta_zero++;
							}
							if (next_dataValue <= low_value) {
								dataVector_Copy[0] = low_value;
								touched_lower_bound++;
							} else if (next_dataValue >= high_value) {
								dataVector_Copy[0] = high_value;
								touched_upper_bound++;
							} else {
								dataVector_Copy[0] = next_dataValue;
							}
							timeVector_Copy[0] = next_time;
							setTimeseries_Data(CE_data, jumps+1, var, timeVector_Copy, dataVector_Copy); //jump +1 makes sure that this is not the 1st jump (as required for joining the data)
							if (touched_lower_bound==2 || touched_upper_bound==2) {
								break; //if boundary is reached two times break the while-loop just add/replace the 2nd repeated point as time-horizon (or last point), since Matlab's Simulink does linear interpolation by default
							}
							if (delta_zero==2) {	//for constant variable
								break;
							}
						}

						//Replacing the last value set with the value of time-horizon instead of the computed next_time
						//dataVector_Copy[0] = same as previous;
						timeVector_Copy[0] = user->getTimeHorizon();
						setTimeseries_Data(CE_data, jumps+1, var, timeVector_Copy, dataVector_Copy); //jump +1 makes sure that this is not the 1st jump (as required for joining the data)

					}
			 */

					// ---------- End of Heuristic Approach 2 -------------------------


					// ******
				}
			}
		}
	}
	// Debug -----------
	/*for (list<struct timeseries_input>::iterator itval = CE_data.begin(); itval != CE_data.end(); itval++) {
		cout <<"Variable="<<(*itval).var_detail.var_name <<endl;
		cout <<"TimeVector is: ";
		for (int i=0; i< (*itval).time_values.size(); i++) {
			cout << (*itval).time_values[i] << " , ";
		}
		cout << endl <<"DataVector is: ";
		for (int i=0; i< (*itval).var_values.size(); i++) {
			cout << (*itval).var_values[i] << " , ";
		}
		cout << endl;
	}*/
	// ------------------

	CE_data_list = CE_data;


	//int start=1;
	int plotting_required = 1;	//Now it is required for generating CE as signal

	if (plotting_required) {

		list<vector<double>> CE_trace;
		vector<double> CE_point; //each point, push this in CE_trace


		for (json::iterator it = jf.begin(); it != jf.end(); ++it) { //its only a single iteration coz of just "traces"
		  //std::cout << it.value()[0][0]["values"][0]["enclosure"] << "\n";
			numberOfJumps = it.value().size();	//Works
			numberOfVariables = it.value()[0].size();	//Works even with 0 index, the 1st mode
	/*		numberOfDataPoints_perJump_0 = it.value()[0][0]["values"].size();	//Works even with 0 index, the 1st dimension/variable
			numberOfDataPoints_perJump_1 = it.value()[1][0]["values"].size();	//Works even with 0 index, the 1st dimension/variable
			std::cout <<"numberOfJumps="<<numberOfJumps << "\n";	//Works
			std::cout <<"numberOfVariables="<<numberOfVariables << "\n";	//Works
			std::cout <<"numberOfDataPoints_perJump_0="<<numberOfDataPoints_perJump_0 << "\n";	//Works
			std::cout <<"numberOfDataPoints_perJump_1="<<numberOfDataPoints_perJump_1 << "\n";	//Works
	*/


			//For each Jumps
			for (unsigned int jumps=0; jumps < numberOfJumps; jumps++) {
				//std::list<double> d1, d2;
				//double values(numberOfVariables);
				//double var_value, time_value;
				//For the variable x_0_0 , ie, X
				//std::cout <<"Variables are: "<<it.value()[jumps][var_Index1]["key"];
				//std::cout << "   and  "<<it.value()[jumps][var_Index2]["key"]<<std::endl;

				std::list<double> var_value1, var_value2, var_time;
				unsigned int big_size_index = var_Index1;
				if (it.value()[jumps][var_Index1]["values"].size() < it.value()[jumps][var_Index2]["values"].size()){
					big_size_index = var_Index2;
				}

				//For the first variable
				for (unsigned int i = 0; i< it.value()[jumps][var_Index1]["values"].size(); i++) {
					var_value1.push_back(it.value()[jumps][var_Index1]["values"][i]["enclosure"][1]);
					if (big_size_index == var_Index1) {
						var_time.push_back(it.value()[jumps][var_Index1]["values"][i]["time"][0]);
					}
				}
				//For the second variable
				for (unsigned int i = 0; i< it.value()[jumps][var_Index2]["values"].size(); i++) {
					var_value2.push_back(it.value()[jumps][var_Index2]["values"][i]["enclosure"][1]);
					if (big_size_index == var_Index2) {
						var_time.push_back(it.value()[jumps][var_Index2]["values"][i]["time"][0]);
					}
				}
				// ************ Reading of all data for the two variables from the json done for this Jump. Now write them on file.data **********


				if (big_size_index == var_Index1) { //More data in var_Index1
					//iterate through  var_time, var_value1 and var_value2 and record the last-value of var_value2, when count== size of var_value2 then just write the last-value for var_value2
					int total_small_size = it.value()[jumps][var_Index2]["values"].size(), count=0;
					double last_value = 0;

					std::list<double>::iterator it_time = var_time.begin();  //Time values are not required only the values of the two output variables are required
					std::list<double>::iterator it2 = var_value2.begin();

					for(std::list<double>::iterator it1 = var_value1.begin(); it1 != var_value1.end(); it1++) {
//				outFile << (*it_time) << "  ";
						outFile_plot << (*it1) << " ";
						if (count < total_small_size) {
							outFile_plot << (*it2) << " ";
							last_value = (*it2);
							count++; it2++;
						} else {
							outFile_plot << last_value << " ";
							count++;
						}
						it_time++;
						outFile_plot << "\n";	//one set values done

					}

				} else { //More data in var_Index2
					//iterate through  var_time, var_value2 and var_value1 and record the last-value of var_value1, when count== size of var_value1 then just write the last-value for var_value1
					int total_small_size = it.value()[jumps][var_Index1]["values"].size(), count=0;
					double last_value = 0;

					std::list<double>::iterator it_time = var_time.begin();
					std::list<double>::iterator it1 = var_value1.begin();

					for(std::list<double>::iterator it2 = var_value2.begin(); it2 != var_value2.end(); it2++) {

//					outFile << (*it_time) << "  ";

						if (count < total_small_size) {
							outFile_plot << (*it1) << " ";
							last_value = (*it1);
							count++; it1++;
						} else {
							outFile_plot << last_value << " ";
							count++;
						}
						outFile_plot << (*it2) << " ";
						it_time++;
						outFile_plot << "\n";	//one set values done
					}
				}

				//start++;
			} //End of Jumps


			//Populating the initial values of the 1st jumps of the 1st iteration of the 1st enclosure for all variables
			// Note: Only this code is actually required by the tool. The above code is only for Plotting for CE visualization
			/*for (unsigned int var=0; var < numberOfVariables; var++) {
				//initial_CE_values[var] = it.value()[0][var]["values"][0]["enclosure"][0];	//Taking only the 0th enclosure
				initial_CE_values[var] = it.value()[0][var]["values"][0]["enclosure"][1];	//Taking only the 1th enclosure
			}*/
		}

//		outFile.close();		//CLOSING Counter-example file, with time added as 1st column (as required by the Learning Algorithm)
		outFile_plot.close();	//CLOSING Plotting file

		/*  Running gnuplotutil to plot output
		 *
		 *  graph -TX -BC -X "t" -Y "x" out.txt -s -m 2 -W 0.001 bad_trace.o -s -m 3 bad_poly -s -m 2 init_poly
		 *	where out.txt is the flowpipe output, bad_trace.o is the simulation trace (which is a concrete counterexample)
		 *	and bad_poly and init_poly are the bad set and the initial set respectively.
		 *
		 *
		 *  */
			std::string cmdStr1;
			//cmdStr1.append("graph -TX -BC out.txt -s -m 2 ");
			cmdStr1.append("graph -TX -BC -W 0.004 -X ");
			cmdStr1.append(x_var);
			cmdStr1.append(" -Y ");
			cmdStr1.append(y_var);
			cmdStr1.append("  ");
			cmdStr1.append(outfile_plot.c_str());

			//Todo: fix plotting for unbounded polytope and unrelated output/unsafe variables
			int unbounded_unrelated=0;
			if (unbounded_unrelated != 1) {
				cmdStr1.append(" -s -m 3 unsafe.txt -s -m 2 initial.txt");
			}

		int x = system(cmdStr1.c_str());
		if (x == -1) {
			std::cout <<"Error executing cmd: " << cmdStr1 <<std::endl;
		}

	} //End of plotting code
}


void setTimeseries_Data(list<struct timeseries_input> &res, unsigned int jump_id, string variableName, vector<double> timeVector, vector<double> dataVector) {

	for (std::list<struct timeseries_input>::iterator it = res.begin(); it != res.end(); it++) {
		if ((*it).var_detail.var_name == variableName) {
			if (jump_id == 0) {
				(*it).time_values = timeVector;
				(*it).var_values = dataVector;
			} else {
				//append/join with the previous timeVector and dataVector
				(*it).time_values.insert((*it).time_values.end(),timeVector.begin(), timeVector.end());
				(*it).var_values.insert((*it).var_values.end(),dataVector.begin(), dataVector.end());

				/*
				 * Todo: check if without sorting Matlab complains with this timeseries data
				 */
				/*
				sort((*it).time_values.begin(), (*it).time_values.end());
				sort((*it).var_values.begin(), (*it).var_values.end());*/

			}
			break;
		}
	}
}



void gnu_plotter(user_inputs::ptr &user, intermediateResult::ptr &intermediate){

	std::string jsonFileName = "";
//	jsonFileName.append(intermediate->getOutputfilenameWithoutExtension());
//	jsonFileName.append("/");
//	jsonFileName.append(intermediate->getOutputfilenameWithoutExtension());
	jsonFileName.append(intermediate->getDReachSatSmt2filenameWithPathWithoutExtension());
	jsonFileName.append(".smt2.json");

	std::string outfile = user->getOutputFilename();

	std::string x_var = user->getPlotVars().first_variable;
	std::string y_var = user->getPlotVars().second_variable;


	std::ifstream ifs(jsonFileName.c_str()); //Make sure to run this program from Command Terminal with the json file in the current location
	//std::ifstream ifs("XSpeed_smtFile_1.smt2.json"); //Make sure to run this program from Command Terminal with the json file in the current location
	json jf = json::parse(ifs);


	unsigned int var_Index1=0, var_Index2=1;	//Default variable index 0 and 1

	for (json::iterator it = jf.begin(); it != jf.end(); ++it) { //its only a single iteration coz of just "traces"
		for (unsigned int i=0; i < it.value()[0].size(); i++) { //loop through the number of variables
			std::string var_name = it.value()[0][i]["key"];
			//std::cout << var_name <<std::endl;
			int len = var_name.length(); // eg return 5 for "t_0_0"
			// Copy three characters of s1 (starting from position 1)
			int totchars = len - 4; //4 for "_0_0", so totchars is 1

			std::string var = var_name.substr(0, totchars);
			//std::cout <<"var = " <<var <<std::endl;
			if (var == x_var) {
				var_Index1 = i;
			} else if (var == y_var) {
				var_Index2 = i;
			}
		}
	}

	std::ofstream outFile;
	//outFile.open(user_options.getOutFilename().c_str());
	outFile.open(outfile);

	unsigned int numberOfJumps, numberOfVariables, numberOfDataPoints_perJump;
	for (json::iterator it = jf.begin(); it != jf.end(); ++it) { //its only a single iteration coz of just "traces"
	  //std::cout << it.value()[0][0]["values"][0]["enclosure"] << "\n";
		numberOfJumps = it.value().size();	//Works
		numberOfVariables = it.value()[0].size();	//Works even with 0 index, the 1st mode
		numberOfDataPoints_perJump = it.value()[0][0]["values"].size();	//Works even with 0 index, the 1st dimension/variable
		std::cout <<"numberOfJumps="<<numberOfJumps << "\n";	//Works
		std::cout <<"numberOfVariables="<<numberOfVariables << "\n";	//Works
		std::cout <<"numberOfDataPoints_perJump="<<numberOfDataPoints_perJump << "\n";	//Works
		//std::cout << it.value()[0][0]["values"].size() << "\n";	//Works

		//For each Jumps
		for (unsigned int jumps=0; jumps < numberOfJumps; jumps++) {
			std::list<double> d1, d2;
			//For the variable x_0_0 , ie, X
			std::cout <<"Variables are: "<<it.value()[jumps][var_Index1]["key"];
			std::cout << "   and  "<<it.value()[jumps][var_Index2]["key"]<<std::endl;
			for (unsigned int i = 0; i< it.value()[jumps][var_Index1]["values"].size(); i++){	//TotalDataPoint
				//d1.push_back(it.value()[jumps][var_Index1]["values"][i]["enclosure"][0]);
				d1.push_back(it.value()[jumps][var_Index1]["values"][i]["enclosure"][1]);
				//d1.push_back(it.value()[0][0]["values"][i]["enclosure"][1]);
			}

			//For the variable y_0_0 , ie, Y
			for (unsigned int i = 0; i< it.value()[jumps][var_Index2]["values"].size(); i++){	//TotalDataPoint
				//d2.push_back(it.value()[jumps][var_Index2]["values"][i]["enclosure"][0]);
				d2.push_back(it.value()[jumps][var_Index2]["values"][i]["enclosure"][1]);
				//d2.push_back(it.value()[0][1]["values"][i]["enclosure"][1]);
			}

			//After reading the data for each jump, it is written in the file so that list d1,d2 can be be free per jump
			assert(d1.size()==d2.size());
			std::list<double>::iterator ii, jj;
			for ( ii = d1.begin(), jj= d2.begin(); ii != d1.end(); ii++, jj++ ){
				outFile << *ii << " " << *jj << std::endl;
			}
			d1.clear();
			d2.clear();
		}//End of Jumps
	}
	outFile.close();

	/* Running gnuplotutil to plot output */
	std::string cmdStr1;
	//cmdStr1.append("graph -TX -BC out.txt -s -m 2 ");
	cmdStr1.append("graph -TX -BC -X ");
	cmdStr1.append(x_var);
	cmdStr1.append(" -Y ");
	cmdStr1.append(y_var);
	cmdStr1.append("  ");
	cmdStr1.append(outfile.c_str());
	//system(cmdStr1.c_str());
	int x = system(cmdStr1.c_str());
	if (x == -1) {
		std::cout <<"Error executing cmd: " << cmdStr1 <<std::endl;
	}
}


void plot_all_variables(user_inputs::ptr &user, intermediateResult::ptr &intermediate){


	std::string jsonFileName = "";
//	jsonFileName.append(intermediate->getOutputfilenameWithoutExtension());
//	jsonFileName.append("/");
//	jsonFileName.append(intermediate->getOutputfilenameWithoutExtension());
	jsonFileName.append(intermediate->getDReachSatSmt2filenameWithPathWithoutExtension());
	jsonFileName.append(".smt2.json");

	std::string outfile = intermediate->getOutputfilenameWithoutExtension(); //user->getOutputFilename();
	outfile.append(".data"); 	//File for printing all (variables') values obtained from Counter-example Trace

	std::string x_var = user->getPlotVars().first_variable;
	std::string y_var = user->getPlotVars().second_variable;


	std::ifstream ifs(jsonFileName.c_str()); //Make sure to run this program from Command Terminal with the json file in the current location
	//std::ifstream ifs("XSpeed_smtFile_1.smt2.json"); //Make sure to run this program from Command Terminal with the json file in the current location
	json jf = json::parse(ifs);



	std::ofstream outFile;
	//outFile.open(user_options.getOutFilename().c_str());
	outFile.open(outfile);

	unsigned int numberOfJumps, numberOfVariables, numberOfDataPoints_perJump_1, numberOfDataPoints_perJump_0;
	for (json::iterator it = jf.begin(); it != jf.end(); ++it) { //its only a single iteration coz of just "traces"
	  //std::cout << it.value()[0][0]["values"][0]["enclosure"] << "\n";
		numberOfJumps = it.value().size();	//Works
		numberOfVariables = it.value()[0].size();	//Works even with 0 index, the 1st mode
		numberOfDataPoints_perJump_0 = it.value()[0][0]["values"].size();	//Works even with 0 index, the 1st dimension/variable
		numberOfDataPoints_perJump_1 = it.value()[1][0]["values"].size();	//Works even with 0 index, the 1st dimension/variable
		std::cout <<"numberOfJumps="<<numberOfJumps << "\n";	//Works
		std::cout <<"numberOfVariables="<<numberOfVariables << "\n";	//Works
		std::cout <<"numberOfDataPoints_perJump_0="<<numberOfDataPoints_perJump_0 << "\n";	//Works
		std::cout <<"numberOfDataPoints_perJump_1="<<numberOfDataPoints_perJump_1 << "\n";	//Works

		//For each Jumps
		for (unsigned int jumps=0; jumps < numberOfJumps; jumps++) {
			//std::list<double> d1, d2;
			//double values(numberOfVariables);
			double var_value;
			//For the variable x_0_0 , ie, X
			//std::cout <<"Variables are: "<<it.value()[jumps][var_Index1]["key"];
			//std::cout << "   and  "<<it.value()[jumps][var_Index2]["key"]<<std::endl;

			for (unsigned int i = 0; i< it.value()[jumps][0]["values"].size(); i++){	//TotalDataPoint of 0th variable
				for (unsigned int var=0; var < numberOfVariables; var++){
					//values[var] = it.value()[jumps][var]["values"][i]["enclosure"][0];	//Taking only the 0th enclosure
					//var_value = it.value()[jumps][var]["values"][i]["enclosure"][0];	//Taking only the 0th enclosure
					var_value = it.value()[jumps][var]["values"][i]["enclosure"][1];	//Taking only the 0th enclosure
					outFile << var_value << " ";
				}
				outFile << "\n";	//one set values done
			}
		}//End of Jumps
	}
	outFile.close();

	/* Running gnuplotutil to plot output */
	std::string cmdStr1;
	//cmdStr1.append("graph -TX -BC out.txt -s -m 2 ");
	cmdStr1.append("graph -TX -BC ");
	cmdStr1.append(outfile.c_str());
	//system(cmdStr1.c_str());
	int x = system(cmdStr1.c_str());
	if (x == -1) {
		std::cout <<"Error executing cmd: " << cmdStr1 <<std::endl;
	}


}

