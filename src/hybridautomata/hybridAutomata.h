/*
 * hybridAutomata.h
 *
 *  Created on: 22-Sep-2021
 *      Author: amit
 */

#ifndef HYBRIDAUTOMATA_HYBRIDAUTOMATA_H_
#define HYBRIDAUTOMATA_HYBRIDAUTOMATA_H_

#include "variable_to_index_mapping.h"
#include "location.h"
#include <map>
#include <bits/stdc++.h>	//used for assert with count in: assert(list_locations.count(Loc_Id)!=0);
#include <assert.h>


using namespace std;

class hybridAutomata : public var_mapping {
	std::map<int, location::ptr> list_locations;		//mapping a list of locations based on the key=loc_id
	location::ptr initial_loc;	//May be  I will prefer to use just the ID, since initial-set is already in the user_inputs class
	unsigned int initial_id;
	int dimension;

public:
	typedef boost::shared_ptr<hybridAutomata> ptr;
	hybridAutomata();
	//hybridAutomata(std::map<int, location::ptr>& list_locs, location::ptr init_loc, int dim);
	void addInitial_Location(location::ptr& initLoc);
	location::ptr& getInitial_Location();

	//returns the location from the list of locations with location_ID as the input parameter
	location::ptr getLocation(int Loc_ID);



	void addLocation(location::ptr& loc);	//inserts location into its correctly mapped key
	int getDimension() const;
	void setDimension(int dimension);

	//This function replaces the list_locations map. Note adding duplicate location in the map is not allowed by stl::map.
	void addMapped_Locations_List(std::map<int, location::ptr>& mapped_location_list);

	std::map<int, location::ptr> getLocation_List();

	/*
	 * Returns the total number of Locations in the hybrid automata with ID = 1 to returned size
	 */
	int getTotalLocations(){
		return list_locations.size();
	}
	/*
	 * Returns the total number of Transitions in the hybrid automata
	 */
	unsigned int getTotalTransitions(){
		unsigned int totTrans=0;
		for (std::map<int, location::ptr>::iterator it=list_locations.begin(); it != list_locations.end(); it++){
			location::ptr loc = it->second;
			totTrans= totTrans + loc->getOutGoingTransitions().size();
		}
		return totTrans;
	}

	unsigned int getInitialId() const;
	void setInitialId(unsigned int initialId);
};


#endif /* HYBRIDAUTOMATA_HYBRIDAUTOMATA_H_ */
