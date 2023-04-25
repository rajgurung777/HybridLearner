/*
 * myRandomNumberGenerator.cpp
 *
 *  Created on: 01-Mar-2022
 *      Author: amit
 */


#include "myRandomNumberGenerator.h"


std::vector<double> myRandomNumberGenerator::getRandomNumbers(double min, double max, unsigned int N) {
	std::vector<double> res(N);

	std::uniform_real_distribution<double> distribution(min, max);

	 for (unsigned int i=0; i<N; ++i) {
	    res[i] = distribution(generator);
	    if (min == max) {
	    	res[i] = min;	//either min or max can be set
	    }
	  }

	 return res;
}

unsigned int myRandomNumberGenerator::getSeedValue() const {
	return seedValue;
}

void myRandomNumberGenerator::setSeedValue(unsigned int seedValue) {
	this->seedValue = seedValue;
}
