/*
 * randomGenerator.cpp
 *
 *  Created on: 15-Oct-2021
 *      Author: amit
 */


#include "randomGenerator.h"
#include <random>

std::vector<double> getRandom(double min, double max, unsigned int size){
	std::vector<double> res(size);
	std::default_random_engine generator;	//No seed used so it will repeat the sequence
	std::uniform_real_distribution<double> distribution(min, max);

	 for (unsigned int i=0; i<size; ++i) {
	    res[i] = distribution(generator);
	    if (min == max){
	    	res[i] = min;	//either min or max can be set
	    }
	  }

	 return res;
}

std::vector<double> getPureRandom(double min, double max, unsigned int size){
	std::vector<double> res(size);
	//std::default_random_engine generator;
	// Random seed
	std::random_device rd;
	// Initialize Mersenne Twister pseudo-random number generator
	std::mt19937 generator(rd());	//seed is used so always generate unique sequence, even on each startup. Here the seed is a random value rd dependent on the device

	std::uniform_real_distribution<double> distribution(min, max);

	 for (unsigned int i=0; i<size; ++i) {
	    res[i] = distribution(generator);
	    if (min == max){
	    	res[i] = min;	//either min or max can be set
	    }
	  }

	 return res;
}
