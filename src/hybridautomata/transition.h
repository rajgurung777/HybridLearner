/*
 * transition.h
 *
 *  Created on: 22-Sep-2021
 *      Author: amit
 */

#ifndef HYBRIDAUTOMATA_TRANSITION_H_
#define HYBRIDAUTOMATA_TRANSITION_H_


#include <string>
#include <list>
#include <boost/shared_ptr.hpp>
#include "data_structure.h"

using namespace std;

class transition {
	unsigned int trans_id;
	std::string label;
	unsigned int source_location_id;
	unsigned int destination_location_id;
	std::list<std::string> guard; //every & can be separated as a single guard string
	//std::list<std::string> assignment;
	std::list<reset_equation> assignment;

	/*
	 * Matlab fails to hit the Equality (==) guard, so to fix we modify, as done by most Software Engineers, convert equality to range by +/- epsilon.
	 * This will create two inequality instead of a single constraint
	 */
	std::list<std::string> guard_modified; //The guard is modified from the equality (==) guard into inequality

public:
	typedef boost::shared_ptr<transition> ptr;
	transition();
	transition(unsigned int trans_id, string label, unsigned int source_id, unsigned int destination_id,
			std::list<std::string> guard, std::list<reset_equation> assign);

//	const std::list<std::string>& getAssignment() const;
//	void setAssignment(const std::list<std::string>& assignment);

	unsigned int getDestinationLocationId() const;
	void setDestinationLocationId(unsigned int destinationLocationId);
	const std::list<std::string>& getGuard() const;
	void setGuard(const std::list<std::string>& guard);
	const std::string& getLabel() const;
	void setLabel(const std::string& label);
	unsigned int getSourceLocationId() const;
	void setSourceLocationId(unsigned int sourceLocationId);
	unsigned int getTransId() const;
	void setTransId(unsigned int transId);

	const std::list<std::string>& getGuardModified() const;
	void setGuardModified(const std::list<std::string> &guardModified);

	const std::list<reset_equation>& getAssignment() const;
	void setAssignment(const std::list<reset_equation> &assignment);
};




#endif /* HYBRIDAUTOMATA_TRANSITION_H_ */
