/*
 * data_structure.h
 *
 *  Created on: 22-Sep-2021
 *      Author: amit
 */

#ifndef HYBRIDAUTOMATA_DATA_STRUCTURE_H_
#define HYBRIDAUTOMATA_DATA_STRUCTURE_H_


#include <string>
#include <iostream>

struct flow_equation {
	bool isConstant_dynamic;
	std::string varName;	// contains the LHS of the flow equation, it include the derivative symbol (')
	std::string RHSexpression;	//if RHSexpression is number then  isConstant_dynamic will be TRUE
	std::string derivative;		//varname' = RHSexpression
};


// Example expression of one of the variable x1' = -0.0000000 * x0 + 1.0000000 * x1 + 0.0000000 * x2 + -0.0000000 * x3 + 0.0000000 * x4 + 0.000
struct reset_equation {
	std::string varName;	// contains the LHS of the reset equation, it include the prime symbol (')
	std::string RHSexpression;	// RHSexpression is RHS expression.
	std::string reset_expression;		//varname' = RHSexpression
};




#endif /* HYBRIDAUTOMATA_DATA_STRUCTURE_H_ */
