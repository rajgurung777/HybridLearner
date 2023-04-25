/*
 * modelConstructor.cpp
 *
 *  Created on: 23-Sep-2021
 *      Author: amit
 */

#include "modelConstructor.h"

void modelConstructor::printModelFile(hybridAutomata::ptr &H, ofstream &outfile, user_inputs::ptr &user) {
	print_header(H, outfile, user);
	locationPrinter(H, outfile);

	initialSetPrinter(H, outfile, user);
	goalPrinter(H, outfile, user);

}

void modelConstructor::print_header(hybridAutomata::ptr &H, ofstream &outfile, user_inputs::ptr &user) {
	string variable_name = "";
	double max_value = user->getMaxValue();	//Now every variable has its own min and max values
	double minValue = 0.0, maxValue = 0.0;


	outfile << "//Variables with time-horizon \n";
	//cout << "//Variables with time-horizon \n";
	outfile << "[ 0.0 , " << user->getTimeHorizon() << " ] time; \n";
	for (std::map<std::string, unsigned int>::iterator it = H->var_mapping_ptr->begin(); it != H->var_mapping_ptr->end(); it++) {
		variable_name =  (*it).first;
		getBoundValues (user->getListVariableBounds(), variable_name, minValue, maxValue);
		outfile << "[ " << minValue << " , " << maxValue << " ] " << variable_name << "; \n";
		//outfile << "[ " << -1 * max_value << " , " << max_value << " ] " << variable_name << "; \n";
		//cout << "[ " << -1 * max_value << " , " << max_value << " ] " << variable_name << "; \n";
	}
	// *********** setting bounds on lt and gt variables **********************
	//outfile << "[ 0.0 , " << user->getTimeHorizon() << " ] lt;  \n";
	outfile << "[ 0.0 , " << user->getTimeHorizon() << " ] gt;  \n";
	// *******************nbounds on lt and gt variables **********************
}

void modelConstructor::getBoundValues(std::list<struct variable_bounds> bounds, string varName, double &minValue, double &maxValue) {

	for (std::list<struct variable_bounds>::iterator it = bounds.begin(); it != bounds.end(); it++){
		if ((*it).variable_name == varName) {
			minValue = (*it).min_value;
			maxValue = (*it).max_value;
			break;
		}
	}

}

void modelConstructor::locationPrinter(hybridAutomata::ptr &H, ofstream &outfile) {

	outfile << " \n \n //Locations \n";
	//int tot_locs = H->getTotalLocations();

	std::map<int, location::ptr> list_locations;
	list_locations = H->getLocation_List();

	for (std::map<int, location::ptr>::iterator i= list_locations.begin(); i != list_locations.end(); i++) {

		location::ptr loc = (*i).second;	//since our location starts from 1

	//for (int i= 0; i< tot_locs; i++) {

		///******** REMEMBER dReach DOES NOT SUPPORT MODE=0, it will report SYNTAX ERROR.
		outfile << "{ \n";
		outfile << "  mode ";
		outfile << loc->getLocId() << "; \n";
		//cout << loc->getLocId() << "; \n";

		outfile << "  invt: \n";	//here invariant is missing in Naijun's tool
		/*  printing invariant. Syntax:
		 * invt:
		 *  (const1);
		 *  (const1);
		 *
		 */
		std::list<std::string> inv_lst = loc->getInvariant();
		for (std::list<std::string>::iterator it_inv = inv_lst.begin(); it_inv != inv_lst.end(); it_inv++) {
			outfile << "    (";
			outfile << (*it_inv);
			outfile << "); \n";
		}

		outfile << "  flow: \n";

		//location::ptr loc = H->getLocation(i);	//since our location starts from 0

		//cout<<"Location Name: "<<loc->getName() <<"  ID: "<< loc->getLocId()<<endl;
		list<flow_equation> derivatives = loc->getDerivatives();
		int var_index=0;
		for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
			//cout<<"Flow:RHS "<<(*it_flow).RHSexpression<<endl;
			outfile << "    d/dt[" << H->get_varname(var_index) << "] = ";
			outfile << (*it_flow).RHSexpression << "; \n";
			var_index++;
		}

		// **** Adding lt and gt time-derivatives for time-related specification (only gt should be enough but lt also keep track of time within a Location/mode
		//outfile << "    d/dt[lt] = 1; \n";
		outfile << "    d/dt[gt] = 1; \n";
		// ********************* lt and gt the Time-derivatives added *********************



		unsigned int range_or_equal_guard = 1;	//1 for range of epsilon and 2 for equality guard


		outfile << "  jump: \n"; //involves (guard) ==> @destinationLocID *( reset );
		list<transition::ptr> trans = loc->getOutGoingTransitions();
		//cout <<"====== Outgoing transition ======"<<endl;
		for (list<transition::ptr>::iterator it_trans = trans.begin(); it_trans != trans.end(); it_trans++) {
			outfile << "    //" << (*it_trans)->getSourceLocationId() << " --> "<< (*it_trans)->getDestinationLocationId()<<"\n";
			//cout <<"Transition ID: "<< (*it_trans)->getTransId()<< endl;
			//cout <<"Transition Label: "<< (*it_trans)->getLabel()<< endl;
			//cout <<"Transition Source-ID and Destination-ID:  "<< (*it_trans)->getSourceLocationId() << "  --->   "<< (*it_trans)->getDestinationLocationId()<< endl;
			std::list<std::string> guard = (*it_trans)->getGuard();
			list<std::string>::iterator it_guard = guard.begin();
			string rangeGuard="";
			std::list<std::string> range_Guards = (*it_trans)->getGuardModified();
			for(list<std::string>::iterator range_cons = range_Guards.begin(); range_cons != range_Guards.end(); range_cons++){
				rangeGuard += "(" + (*range_cons) + ") ";
			}
			if (range_or_equal_guard == 1){
				outfile <<"    (and "<< rangeGuard <<" ) ==> @"<<(*it_trans)->getDestinationLocationId();
			} else {	//equality guard
				//cout<<"Transition-Guard: "<< (*it_guard)<<endl;
				outfile <<"    ("<<(*it_guard) <<") ==> @"<<(*it_trans)->getDestinationLocationId();
			}


			string reset_statement = "";
			//reset_statement = resetPrinter(H);	//write a simple function for identity reset and call here
			//Now reset is not a simple identity
			reset_statement = resetPrinter((*it_trans)->getAssignment());	//write a simple function for identity reset and call here

			outfile <<"(and "<<reset_statement<<"); \n";
		}

		outfile << "} \n\n";
	}

}

//Prints only an identity mapping reset expression
string modelConstructor::resetPrinter(hybridAutomata::ptr &H){
	string reset_str="";
	//Read any one of the location and parse through the ODE's varName this contains the prime-variable
	location::ptr loc = H->getLocation(1);	//since our location starts from 1
	list<flow_equation> derivatives = loc->getDerivatives();

	for (list<flow_equation>::iterator it_flow = derivatives.begin(); it_flow != derivatives.end(); it_flow++) {
		string prime_variableName = (*it_flow).varName;	//eg x0'
		size_t pos = prime_variableName.find("'");
		string variableName = prime_variableName.substr(0, pos);	//extract only the variable name minus derivative symbol

		reset_str.append("(");
		reset_str.append(prime_variableName);
		reset_str.append(" = 1.0 * ");
		reset_str.append(variableName);
		reset_str.append(") ");
	}
	// **** Adding reset for lt and gt variables (lt' = 0; and gt'=gt will keep track of local and global time)
	//reset_str.append("(lt' = 0) (gt' = 1.0 * gt)");
	reset_str.append("(gt' = 1.0 * gt)");
	// ******************************

	return reset_str;
}

//Reset function is not an identity mapping
string modelConstructor::resetPrinter(std::list<reset_equation> reset_list){
	string reset_str="";
	for (list<reset_equation>::iterator it_reset = reset_list.begin(); it_reset != reset_list.end(); it_reset++) {

		reset_str.append("(");
		reset_str.append((*it_reset).reset_expression);
		reset_str.append(") ");
	}
	// **** Adding reset for lt and gt variables (lt' = 0; and gt'=gt will keep track of local and global time)
	//reset_str.append("(lt' = 0) (gt' = 1.0 * gt)");
	reset_str.append("(gt' = 1.0 * gt)");
	// ******************************

	return reset_str;
}


/*void modelConstructor::invariantPrinter(hybridAutomata::ptr &H, ofstream &outfile) {

}

void modelConstructor::flowPrinter(hybridAutomata::ptr &H, ofstream &outfile) {

}

void modelConstructor::jumpPrinter(hybridAutomata::ptr &H, ofstream &outfile) {

}*/

void modelConstructor::initialSetPrinter(hybridAutomata::ptr &H, ofstream &outfile, user_inputs::ptr &user) {

	//Trying to Assume that looking at the first index of the P Set the segmentation list in the learning Algorithm is the correct method to identify
	int loc_id= H->getInitialId();

	outfile << "\n" << "init: \n";
	list<string> init_set = user->getInitialSet();

	outfile << "@" << loc_id << " (and ";
	for (list<string>::iterator it_init_set = init_set.begin(); it_init_set != init_set.end(); it_init_set++) {
		outfile << "(" << *it_init_set << ") ";
	}
	// ****** initialize lt=0 and gt=0  **********
//	outfile << "(lt = 0) (gt = 0) ";
	outfile << "(gt = 0) ";
	// ********************************************
	outfile << "); \n";
}

void modelConstructor::goalPrinter(hybridAutomata::ptr &H, ofstream &outfile, user_inputs::ptr &user) {

	int forbidden_loc_id=1;

	outfile << "\n" << "goal: \n";
	list<string> goals = user->getGoalProperty();

	int tot_locs = H->getTotalLocations();
	for (int i=1; i<= tot_locs; i++) {
		location::ptr loc = H->getLocation(i);
		forbidden_loc_id=loc->getLocId();

		outfile << "@" << forbidden_loc_id << " (and ";
		for (list<string>::iterator it_goal = goals.begin(); it_goal != goals.end(); it_goal++) {
			outfile << "(" << *it_goal << ") ";
		}
		outfile << "); \n";
	}

}
