/*
 * learningHA.cpp
 *
 *  Created on: 08-Sep-2021
 *      Author: amit
 *
 *      This is a wrapper class to implement different learning algorithm.
 */

#include "learningHA.h"

//This is a wrapper function that can call different implementation of learning algorithm. Currently, called only from engine=bbc
void learningHA(user_inputs::ptr user_Inputs, summary::ptr &report) {
	// This function is called from engine="bbc"

	std::string cmd_str="";
	if (user_Inputs->getTool()=="hit") {
		//This option will not work now, since the whole folder "src/matlabCodes/hit" have been removed.
		std::cout<<"\nNow running Matlab to execute HIT library!"<<std::endl;
		//Command syntax:  matlab -nodesktop -nodisplay -r 'functionName argument1 argument2 argument3; exit;'
		//Command syntax:  matlab -nodesktop -nodisplay -r 'amit_learnPWA inputfilename outputfilename nmodes; exit;'
		cmd_str = "cd ../src/matlabCodes/hit && matlab -nodesktop -nodisplay -r '";

		cmd_str.append("amit_learnPWA ");
		cmd_str.append(user_Inputs->getInputFilename());
		cmd_str.append(" ");
		cmd_str.append(user_Inputs->getOutputFilename());  //To redirect the model output
		cmd_str.append(" ");
		cmd_str.append(std::to_string(user_Inputs->getModeSize()));
		cmd_str.append("; exit;'");

		int x = system(cmd_str.c_str());
		if (x == -1){
			std::cout <<"Error executing cmd: " << cmd_str <<std::endl;
		}

	} else if (user_Inputs->getTool()=="pwa") {

		boost::timer::cpu_timer naijun_runtime;
		naijun_runtime.start();
		learnHA_caller(user_Inputs);	//Make is Simple and call it from everywhere. This invokes our "HA learning Algorithm".
		//system("pwd"); //although supplied cd ../src/pwa but still in the current Release location
		naijun_runtime.stop();

		double wall_clock;
		wall_clock = naijun_runtime.elapsed().wall / 1000000; //convert nanoseconds to milliseconds
//		user_clock = naijun_runtime.elapsed().user / 1000000;
//		system_clock = naijun_runtime.elapsed().system / 1000000;

		double running_time = wall_clock / (double) 1000;	//convert milliseconds to seconds
		//std::cout << "\n\n*******Learning Nonlinear Switched Dynamical Systems (specific Hybrid Automata)****\n \t Running Time (Boost/Wall clock time) (in Seconds) = " << running_time<<std::endl;
		std::cout << "\nRunning Time for learning HA (in Seconds) = " << running_time<<std::endl;

		report->setRuntimeLearningAlgo(running_time);

	} else if (user_Inputs->getTool()=="adha") {
//	} else if (user_Inputs->getTool()=="adha") {
		//std::cout<<"\nNow running Python and Julia to execute Henzinger's Source Code (Linear ADHA)"<<std::endl;
		std::cout<<"\nTo implement completely a new learning approach or different application platform!"<<std::endl;

	}

	std::cout << "\nModel Learning Phase completed ........"<<std::endl;

}


