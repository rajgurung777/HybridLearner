/*
 * modelConstructor.h
 *
 *  Created on: 23-Sep-2021
 *      Author: amit
 */

#ifndef DREACHMODELLING_MODELCONSTRUCTOR_H_
#define DREACHMODELLING_MODELCONSTRUCTOR_H_

#include "../hybridautomata/hybridAutomata.h"
#include "../commandLineParser/user_inputs.h"
#include "../io_functions/data_structs.h"

#include <boost/shared_ptr.hpp>
#include <iomanip>
#include <string>
#include <sstream>

#include <fstream>
#include <iostream>

using namespace std;

class modelConstructor {
	//hybridAutomata::ptr ha;

	void getBoundValues(std::list<struct variable_bounds> bounds, string varName, double &minValue, double &maxValue);
public:
	typedef boost::shared_ptr<modelConstructor> ptr;

	void printModelFile(hybridAutomata::ptr &H, ofstream &outfile, user_inputs::ptr &user) ;


	void print_header(hybridAutomata::ptr &H, ofstream &outputfile, user_inputs::ptr &user);
	void locationPrinter(hybridAutomata::ptr &H, ofstream &outfile);
//	void invariantPrinter(hybridAutomata::ptr &H, ofstream &outfile);
//	void flowPrinter(hybridAutomata::ptr &H, ofstream &outfile);
//	void jumpPrinter(hybridAutomata::ptr &H, ofstream &outfile);
	string resetPrinter(hybridAutomata::ptr &H); //Prints an identity mapping reset expression

	string resetPrinter(std::list<reset_equation> reset_list); //Prints reset expression when the reset expression is known

	void initialSetPrinter(hybridAutomata::ptr &H, ofstream &outfile, user_inputs::ptr &user);
	void goalPrinter(hybridAutomata::ptr &H, ofstream &outfile, user_inputs::ptr &user);

};


#endif /* DREACHMODELLING_MODELCONSTRUCTOR_H_ */
