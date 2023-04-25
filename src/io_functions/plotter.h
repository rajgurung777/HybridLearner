/*
 * plotter.h
 *
 *  Created on: 26-Sep-2021
 *      Author: amit
 */

#ifndef IO_FUNCTIONS_PLOTTER_H_
#define IO_FUNCTIONS_PLOTTER_H_

#include "../commandLineParser/user_inputs.h"
#include "../utilities/intermediateResult.h"
#include "data_structs.h"


/*
 * Efficient function for printing two-output files at the same time with simpler loop
 * 1) First File named as outputfile.data containing the data for improving the Learned model (counter-example)
 * 2) Second file named as outputfile.txt contains data for Plotting using GNU-Plot utilities.
 */
void plotter(user_inputs::ptr &user, intermediateResult::ptr &intermediate, std::vector<double> &initial_CE_values, list<struct timeseries_input> &CE_data_list);

void setTimeseries_Data(list<struct timeseries_input> &res, unsigned int jump_id, string variableName, vector<double> timeVector, vector<double> dataVector);


//Testing for plotting counter-example trace prints only the two variables (not an efficient looping)
void gnu_plotter(user_inputs::ptr &user, intermediateResult::ptr &intermediate);

//Improved but prints only the file for counter-eaxample
void plot_all_variables(user_inputs::ptr &user, intermediateResult::ptr &intermediate);


#endif /* IO_FUNCTIONS_PLOTTER_H_ */
