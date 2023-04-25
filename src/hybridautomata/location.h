/*
 * location.h
 *
 *  Created on: 22-Sep-2021
 *      Author: amit
 */

#ifndef HYBRIDAUTOMATA_LOCATION_H_
#define HYBRIDAUTOMATA_LOCATION_H_

#include <string>
#include <list>
#include <boost/shared_ptr.hpp>
#include "data_structure.h"
#include "transition.h"


using namespace std;

class location {
private:
	int loc_id;
	string Name;
	list<flow_equation> derivatives;
	//list<string> prefix_derivatives;
	list<string> invariant;
	std::list<transition::ptr> out_going_transitions;

public:
	typedef boost::shared_ptr<location> ptr;
	location();
	location(int loc_id, string Name, list<flow_equation> derivatives, list<string> invariant, std::list<transition::ptr> trans);
	//transition::ptr getTransition(int trans_id);	//returns a specific transition for a given trans_id

	const list<flow_equation>& getDerivatives() const;
	void setDerivatives(const list<flow_equation>& derivatives);


	const list<string>& getInvariant() const;
	void setInvariant(const list<string>& invariant);
	int getLocId() const;
	void setLocId(int locId);
	const string& getName() const;
	void setName(const string& name);
	const std::list<transition::ptr>& getOutGoingTransitions() const;
	void setOutGoingTransitions(const std::list<transition::ptr>& outGoingTransitions);

};




#endif /* HYBRIDAUTOMATA_LOCATION_H_ */
