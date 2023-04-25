/*
 * simulation_datastruct.h
 *
 *  Created on: 21-Feb-2022
 *      Author: amit
 */

#ifndef SIMULATION_SIMULATION_DATASTRUCT_H_
#define SIMULATION_SIMULATION_DATASTRUCT_H_

struct simu_dataStruct {
	unsigned int total_simulations;	//total number of simulations (including this violating trace) executed until a violating simulation trace found.
	double first_violation_timeBound; //time point when the first violation is found
	bool foundViolation;	//True if violation found otherwise False
};



#endif /* SIMULATION_SIMULATION_DATASTRUCT_H_ */
