/*
 * model_variable_mapping.cpp
 *
 *  Created on: 08-Oct-2021
 *      Author: amit
 */

#include "model_variable_mapping.h"

/*
model_variable_mapping::model_variable_mapping() {

}
*/

model_variable_mapping::~model_variable_mapping() {

}

void model_variable_mapping::print_var_mapping() {

	std::cout << "The variable to index mapping is:"<<std::endl;
	for(std::map<std::string, unsigned int>::iterator it = variable_mapping_ptr->begin(); it!=variable_mapping_ptr->end();it++){
		std::cout << "Variable name = " << (*it).first;
		std::cout << " Dimension index = " << (*it).second << std::endl;
	}
}


bool model_variable_mapping::isaVariable(std::string varName) {
	bool found=false;
	for(std::map<std::string, unsigned int>::iterator it = variable_mapping_ptr->begin(); it!=variable_mapping_ptr->end();it++) {
		if (boost::iequals((*it).first, varName)) {
			found = true;
			break;
		}
	}
	return found;
}


std::string model_variable_mapping::get_varname(unsigned int index)
{
	for(std::map<std::string, unsigned int>::iterator it = variable_mapping_ptr->begin(); it!=variable_mapping_ptr->end();it++){
		if (index == (*it).second)
			return (*it).first;
	}
	throw std::runtime_error("Variable to index mapping: Function get_varname(): parameter index not in the mapping\n");
}

/* Returns the size of the map, i.e., the number of variables of the map */
unsigned int model_variable_mapping::map_size()
{
	return variable_mapping_ptr->size();
}


