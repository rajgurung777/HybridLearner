/*
 * equivalence_test_utils.h
 *
 *  Created on: 22-Feb-2023
 *      Author: amit
 */

#include <iostream>

#include "../../commandLineParser/parameters.h"
#include "../../utilities/vector_operations.h"



#ifndef CORE_ENGINE_EQUIVALENCE_TESTING_EQUIVALENCE_TEST_UTILS_H_
#define CORE_ENGINE_EQUIVALENCE_TESTING_EQUIVALENCE_TEST_UTILS_H_



bool compute_trace_equivalence(std::string file_one, std::string file_two, double &max_distance, parameters::ptr params);

double call_python_compute_cost(std::string file_one, std::string file_two);

double call_python_compute_DTW_cost(std::string file_one, std::string file_two);


#endif /* CORE_ENGINE_EQUIVALENCE_TESTING_EQUIVALENCE_TEST_UTILS_H_ */
