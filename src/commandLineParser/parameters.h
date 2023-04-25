/*
 * parameters.h
 *
 *  Created on: 21-Feb-2023
 *      Author: amit
 */

#include "user_inputs.h"
#include "../utilities/polytope/polytope.h"
#include "../utilities/myRandomNumberGenerator.h"
#include "../utilities/intermediateResult.h"
#include "../hybridautomata/hybridAutomata.h"
#include <boost/shared_ptr.hpp>


#ifndef COMMANDLINEPARSER_PARAMETERS_H_
#define COMMANDLINEPARSER_PARAMETERS_H_

class parameters {

	user_inputs::ptr user_Inputs;
	polytope::ptr init_poly;
	myRandomNumberGenerator::ptr randomGenObj;
	intermediateResult::ptr intermediate;
	hybridAutomata::ptr H;



public:
	typedef boost::shared_ptr<parameters> ptr;

	parameters();
	virtual ~parameters();
	void setParameters(const user_inputs::ptr &userInputs ,const hybridAutomata::ptr &h);
	void setParameters(const user_inputs::ptr &userInputs ,const hybridAutomata::ptr &h, const intermediateResult::ptr &intermediate);
	void setParameters(const user_inputs::ptr &userInputs ,const hybridAutomata::ptr &h, const polytope::ptr &initPoly, const intermediateResult::ptr &intermediate);

	const polytope::ptr& getInitPoly() const;
	void setInitPoly(const polytope::ptr &initPoly);
	const user_inputs::ptr& getUserInputs() const;
	void setUserInputs(const user_inputs::ptr &userInputs);
	const myRandomNumberGenerator::ptr& getRandomGenObj() const;
	void setRandomGenObj(const myRandomNumberGenerator::ptr &randomGenObj);
	const intermediateResult::ptr& getIntermediate() const;
	void setIntermediate(const intermediateResult::ptr &intermediate);
	const hybridAutomata::ptr& getH() const;
	void setH(const hybridAutomata::ptr &h);
};

#endif /* COMMANDLINEPARSER_PARAMETERS_H_ */
