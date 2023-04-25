/*
 * myRandomNumberGenerator.h
 *
 *  Created on: 01-Mar-2022
 *      Author: amit
 */

#ifndef MYRANDOMNUMBERGENERATOR_H_
#define MYRANDOMNUMBERGENERATOR_H_


#include <iostream>
#include <random>
#include <vector>
#include <boost/shared_ptr.hpp>

using namespace std;

class myRandomNumberGenerator {
	unsigned int seedValue; //to be initialized only once
	std::mt19937 generator;		//Creating generator object "Mersenne Twister pseudo-random number generator"
public:
	typedef boost::shared_ptr<myRandomNumberGenerator> ptr;


	/*  To create pseudo random number with a seed
	 *  The call to getRandomNumbers() will generate random numbers on each call.
	 *  NOTE: To generate the same sequence through out each call, this object should be assigned the same seed value. Also, note that
	 *  the seed should be provided only once i.e., at the start of the Project.
	 */
	myRandomNumberGenerator(unsigned int seed) {
		seedValue = seed;
		generator.seed(seedValue);	//seed is used so as to always generate unique sequence, even on each startup.
	}

	/*
	 * Each call of this function will generate random numbers. Of course it uses the same seed as the original generator.
	 */
	std::vector<double> getRandomNumbers(double min, double max, unsigned int N); //generate N random numbers between min and max

	unsigned int getSeedValue() const;
	void setSeedValue(unsigned int seedValue);
};


#endif /* MYRANDOMNUMBERGENERATOR_H_ */
