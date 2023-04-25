/*
 * randomGenerator.h
 *
 *  Created on: 15-Oct-2021
 *      Author: amit
 */

#ifndef UTILITIES_MATH_RANDOMGENERATOR_H_
#define UTILITIES_MATH_RANDOMGENERATOR_H_


#include <vector>

/*
 * Returns an array of randomly generated uniform real distribution between
 * the values min and max. The number of values is of size.
 *
 * Note: this function will always return the same sequence of values if the input is same
 */
std::vector<double> getRandom(double min, double max, unsigned int size);


/* Note: Unique sequence of values is generated even with same inputs
 */
std::vector<double> getPureRandom(double min, double max, unsigned int size);

#endif /* UTILITIES_MATH_RANDOMGENERATOR_H_ */
