/*
 * location.cpp
 *
 *  Created on: 22-Sep-2021
 *      Author: amit
 */


#include "location.h"


location::location(){
	loc_id = 0;
}
location::location(int loc_id, string name, list<flow_equation> derivatives, list<string> invariant, std::list<transition::ptr> trans){
	this->loc_id = loc_id;
	this->Name = name;
	this->derivatives = derivatives;
	this->invariant = invariant;
	this->out_going_transitions = trans;
}

const list<flow_equation>& location::getDerivatives() const {
	return derivatives;
}

void location::setDerivatives(const list<flow_equation>& derivatives) {
	this->derivatives = derivatives;
}

const list<string>& location::getInvariant() const {
	return invariant;
}

void location::setInvariant(const list<string>& invariant) {
	this->invariant = invariant;
}

int location::getLocId() const {
	return loc_id;
}

void location::setLocId(int locId) {
	loc_id = locId;
}

const string& location::getName() const {
	return Name;
}

void location::setName(const string& name) {
	Name = name;
}

const std::list<transition::ptr>& location::getOutGoingTransitions() const {
	return out_going_transitions;
}

void location::setOutGoingTransitions(
		const std::list<transition::ptr>& outGoingTransitions) {
	out_going_transitions = outGoingTransitions;
}

