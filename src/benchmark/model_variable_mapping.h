/*
 * model_variable_mapping.h
 *
 *  Created on: 08-Oct-2021
 *      Author: amit
 *
 *  This variable mapping class is required only for simulation of the Original Model.
 *
 *  It may be used for matching the variable with the supplied Property-Verification (input-set and unsafe-set),
 *  in which case the Menu information need to be modified.
 */

#ifndef BENCHMARK_MODEL_VARIABLE_MAPPING_H_
#define BENCHMARK_MODEL_VARIABLE_MAPPING_H_




#include <iostream>
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/predicate.hpp>


class model_variable_mapping {

public:

	typedef boost::shared_ptr< model_variable_mapping > ptr;
	typedef boost::shared_ptr< std::map<std::string, unsigned int> > mapping_ptr;


	model_variable_mapping(){
		variable_mapping_ptr = mapping_ptr(new std::map<std::string,unsigned int>());
	}

	/* Returns the variable name with the given index */
	std::string get_varname(unsigned int index);

	/* Returns the index of the parameter var_name in the variable name to dimension index mapping */
	unsigned int get_index(std::string var_name){
		unsigned int index = variable_mapping_ptr->at(var_name);
		return index;
	}
	/* Inserts a varname, dimension index into the map. */
	void insert_to_map(std::string name, unsigned int val)
	{
		variable_mapping_ptr->insert(std::pair<std::string, unsigned int>(name,val));
	}

	/* Sets this-> map to the new map passed as parameter */
	void set_map(mapping_ptr m){
		variable_mapping_ptr = m;
	}

	/*Prints the var_to_index map in the console*/
	void print_var_mapping();


	/**
	 * Returns True if the variable exists in the mapping list.
	 */
	bool isaVariable(std::string varName);


	//Destructor
	~model_variable_mapping();

	/** Return the size of the map */
	unsigned int map_size();

	mapping_ptr variable_mapping_ptr; //declaring a pointer instead of just the variable

};





#endif /* BENCHMARK_MODEL_VARIABLE_MAPPING_H_ */
