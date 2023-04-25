/*
 * parameters.cpp
 *
 *  Created on: 21-Feb-2023
 *      Author: amit
 */

#include "parameters.h"

parameters::parameters() {
	// TODO Auto-generated constructor stub

	intermediate  = intermediateResult::ptr(new intermediateResult());
	user_Inputs = user_inputs::ptr (new user_inputs());
	init_poly = polytope::ptr(new polytope());
	H = hybridAutomata::ptr (new hybridAutomata());
//	randomGenObj  = myRandomNumberGenerator::ptr(new myRandomNumberGenerator());

}
void parameters::setParameters(const user_inputs::ptr &userInputs ,const hybridAutomata::ptr &h){
	user_Inputs = userInputs;
	H = h;
}

void parameters::setParameters(const user_inputs::ptr &userInputs ,const hybridAutomata::ptr &h, const intermediateResult::ptr &intermediate) {
	user_Inputs = userInputs;
	H = h;
	this->intermediate = intermediate;
}
void parameters::setParameters(const user_inputs::ptr &userInputs ,const hybridAutomata::ptr &h, const polytope::ptr &initPoly, const intermediateResult::ptr &intermediate){
	user_Inputs = userInputs;
	H = h;
	init_poly = initPoly;
	this->intermediate = intermediate;
}

const polytope::ptr& parameters::getInitPoly() const {
	return init_poly;
}

void parameters::setInitPoly(const polytope::ptr &initPoly) {
	init_poly = initPoly;
}

const user_inputs::ptr& parameters::getUserInputs() const {
	return user_Inputs;
}

const myRandomNumberGenerator::ptr& parameters::getRandomGenObj() const {
	return randomGenObj;
}

void parameters::setRandomGenObj(
		const myRandomNumberGenerator::ptr &randomGenObj) {
	this->randomGenObj = randomGenObj;
}

void parameters::setUserInputs(const user_inputs::ptr &userInputs) {
	user_Inputs = userInputs;
}

parameters::~parameters() {
	// TODO Auto-generated destructor stub
}

const intermediateResult::ptr& parameters::getIntermediate() const {
	return intermediate;
}

const hybridAutomata::ptr& parameters::getH() const {
	return H;
}

void parameters::setH(const hybridAutomata::ptr &h) {
	H = h;
}

void parameters::setIntermediate(const intermediateResult::ptr &intermediate) {
	this->intermediate = intermediate;
}
