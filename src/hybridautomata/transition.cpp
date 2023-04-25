/*
 * transition.cpp
 *
 *  Created on: 22-Sep-2021
 *      Author: amit
 */


#include "transition.h"



transition::transition(){
	trans_id = 0;
	label="";
	source_location_id = 0;
	destination_location_id = 0;
}

transition::transition(unsigned int trans_id, string label, unsigned int source_id, unsigned int destination_id,
		std::list<std::string> guard, std::list<reset_equation> assign){
	this->trans_id = trans_id;
	this->label = label;
	this->source_location_id = source_id;
	this->destination_location_id = destination_id;
	this->guard = guard;
	this->assignment = assign;


}

//const std::list<std::string>& transition::getAssignment() const {
//	return assignment;
//}
//void transition::setAssignment(const std::list<std::string>& assignment) {
//	this->assignment = assignment;
//}

unsigned int transition::getDestinationLocationId() const {
	return destination_location_id;
}

void transition::setDestinationLocationId(unsigned int destinationLocationId) {
	destination_location_id = destinationLocationId;
}

const std::list<std::string>& transition::getGuard() const {
	return guard;
}

void transition::setGuard(const std::list<std::string>& guard) {
	this->guard = guard;
}

const std::string& transition::getLabel() const {
	return label;
}

void transition::setLabel(const std::string& label) {
	this->label = label;
}

unsigned int transition::getSourceLocationId() const {
	return source_location_id;
}

void transition::setSourceLocationId(unsigned int sourceLocationId) {
	source_location_id = sourceLocationId;
}

unsigned int transition::getTransId() const {
	return trans_id;
}

void transition::setTransId(unsigned int transId) {
	trans_id = transId;
}

const std::list<std::string>& transition::getGuardModified() const {
	return guard_modified;
}

void transition::setGuardModified(const std::list<std::string> &guardModified) {
	guard_modified = guardModified;
}

const std::list<reset_equation>& transition::getAssignment() const {
	return assignment;
}

void transition::setAssignment(const std::list<reset_equation> &assignment) {
	this->assignment = assignment;
}
