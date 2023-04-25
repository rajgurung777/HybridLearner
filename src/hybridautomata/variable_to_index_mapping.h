/*
 * variable_to_index_mapping.h
 *
 *  Created on: 22-Sep-2021
 *      Author: amit
 */

#ifndef HYBRIDAUTOMATA_VARIABLE_TO_INDEX_MAPPING_H_
#define HYBRIDAUTOMATA_VARIABLE_TO_INDEX_MAPPING_H_



#include <iostream>
#include <map>
#include <string>
//#include <utility>
#include <boost/shared_ptr.hpp>


class var_mapping {
public:
	typedef boost::shared_ptr< std::map<std::string, unsigned int> > ptr;
//	typedef boost::shared_ptr< std::map<std::string, unsigned int> > ptr_input;
//	typedef boost::shared_ptr< std::map<std::string, unsigned int> > ptr_output;

	var_mapping();

	/* Returns the variable name with the given index */
	std::string get_varname(unsigned int index);

	/* Returns the index of the parameter var_name in the variable name to dimension index mapping */
	unsigned int get_index(std::string var_name){
		//std::cout<<"Goging to search var:"<< var_name << std::endl;
		unsigned int index = var_mapping_ptr->at(var_name);
		return index;
	}
	/* Inserts a varname, dimension index into the map. */
	void insert_to_map(std::string name, unsigned int val) {
		var_mapping_ptr->insert(std::pair<std::string, unsigned int>(name, val));
	}

	/* Sets this-> map to the new map passed as parameter */
	void set_map(ptr m){
		var_mapping_ptr = m;
	}

	/*Prints the var_to_index map in the console*/
	void print_var_mapping();

	/**
	 * Returns True if the variable exists in the mapping list.
	 */
	bool isaVariable(std::string varName);

	/*
	 * Delete all mapping elements from the map
	 */
	void erase_all_mapping(){
		var_mapping_ptr->clear();
	}


	// ----------- Working with separate input and output variables --------------
	/*void insert_input_to_map(std::string name, unsigned int val) {  //Note the same index val here will also used in the var_mapping_ptr
		input_var_mapping_ptr->insert(std::pair<std::string, unsigned int>(name, val));
	}

	void insert_output_to_map(std::string name, unsigned int val) {  //Note the same index val here will also used in the var_mapping_ptr
		output_var_mapping_ptr->insert(std::pair<std::string, unsigned int>(name, val));
	}

	bool isaInputVariable(std::string varName);

	bool isaOutputVariable(std::string varName);

	static ptr_input input_var_mapping_ptr;	//Contains only the input variables
	static ptr_output output_var_mapping_ptr;	//Contains only the output variables
	*/

	// ----------- Working with separate input and output variables --------------


	virtual ~var_mapping();

	/** Return the size of the map */
	unsigned int map_size();
	static ptr var_mapping_ptr;	//Contains all system variables, both input and output

};



#endif /* HYBRIDAUTOMATA_VARIABLE_TO_INDEX_MAPPING_H_ */
