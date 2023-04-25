/*
 * test_application_engine_learnHA.cpp
 *
 *  Created on: 28-Feb-2023
 *      Author: amit
 */



#include <iostream>
#include <vector>
#include <UnitTest++/UnitTest++.h>
#include "../../utilities/file_operations.h"
#include "../../commandLineParser/commandLineParser.h"
#include "../../commandLineParser/user_inputs.h"
#include "../../application/engineSelector.h"


using namespace std;
//using namespace matlab::engine;


SUITE(MainApplication_Engine_learnHA_TestSuite) {

	class Application_Engine_learnHA
	{
		public:
		Application_Engine_learnHA() {

			}
			~Application_Engine_learnHA() { /* some teardown */
			}

			void get_commandLineArguments_for_learn_ha_oscillator(int &argc, char *argv[]) {

				std::vector<char *> args;
				string token = "./BBC4CPS";
				args.push_back(create_token(token));
				token = "--engine";
				args.push_back(create_token(token));
				token = "learn-ha";
				args.push_back(create_token(token));
				token = "--simu-trace-file";
				args.push_back(create_token(token));
				token = "../src/test_cases/engine/simu/data/simu_oscillator_4.txt";
				args.push_back(create_token(token));
				token = "--variable-category";
				args.push_back(create_token(token));
				token = "x:output, y:output";
				args.push_back(create_token(token));
				token = "--output-file";
				args.push_back(create_token(token));
				token = "oscillator_4.txt";
				args.push_back(create_token(token));
				token = "--invariant";
				args.push_back(create_token(token));
				token = "2";
				args.push_back(create_token(token));
				token = "--degree";
				args.push_back(create_token(token));
				token = "1";
				args.push_back(create_token(token));
				token = "--boundary-degree";
				args.push_back(create_token(token));
				token = "1";
				args.push_back(create_token(token));
				//token = "--cluster-error-tol";
				token = "--segment-relative-error";
				args.push_back(create_token(token));
				token = "0.1";
				args.push_back(create_token(token));
				token = "--cluster-algo";
				args.push_back(create_token(token));
				token = "dtw";
				args.push_back(create_token(token));
				token = "--correlation-threshold";
				args.push_back(create_token(token));
				token = "0.89";
				args.push_back(create_token(token));
				token = "--distance-threshold";
				args.push_back(create_token(token));
				token = "1.0";
				args.push_back(create_token(token));
				token = "--ode-speedup";
				args.push_back(create_token(token));
				token = "50";
				args.push_back(create_token(token));
				token = "--variable-types";
				args.push_back(create_token(token));
				token = "x0=t1,x1=t1";
				args.push_back(create_token(token));

				//cout <<" tokens created"  <<endl;
				for(size_t i = 0; i < args.size(); i++){
					argv[i] = args[i];
				 // delete[] args[i];
				}
				argc = args.size();
			}

			void get_commandLineArguments_for_learn_ha_bball(int &argc, char *argv[]) {

				std::vector<char *> args;
				string token = "./BBC4CPS";
				args.push_back(create_token(token));
				token = "--engine";
				args.push_back(create_token(token));
				token = "learn-ha";
				args.push_back(create_token(token));
				token = "--simu-trace-file";
				args.push_back(create_token(token));
				token = "../src/test_cases/engine/simu/data/simu_bball.txt";
				args.push_back(create_token(token));
				token = "--variable-category";
				args.push_back(create_token(token));
				token = "u:input, x:output, v:output";
				args.push_back(create_token(token));
				token = "--output-file";
				args.push_back(create_token(token));
				token = "bball.txt";
				args.push_back(create_token(token));
				token = "--invariant";
				args.push_back(create_token(token));
				token = "2";
				args.push_back(create_token(token));
				token = "--degree";
				args.push_back(create_token(token));
				token = "1";
				args.push_back(create_token(token));
				token = "--boundary-degree";
				args.push_back(create_token(token));
				token = "1";
				args.push_back(create_token(token));
//				token = "--cluster-error-tol";
				token = "--segment-relative-error";
				args.push_back(create_token(token));
				token = "0.1";
				args.push_back(create_token(token));
				token = "--cluster-algo";
				args.push_back(create_token(token));
				token = "dtw";
				args.push_back(create_token(token));
				token = "--correlation-threshold";
				args.push_back(create_token(token));
				token = "0.8";
				args.push_back(create_token(token));
				token = "--distance-threshold";
				args.push_back(create_token(token));
				token = "9.0";
				args.push_back(create_token(token));
				token = "--ode-speedup";
				args.push_back(create_token(token));
				token = "50";
				args.push_back(create_token(token));
				token = "--variable-types";
				args.push_back(create_token(token));
				token = "x0=t1,x1=t1";
				args.push_back(create_token(token));

				//cout <<" tokens created"  <<endl;
				for(size_t i = 0; i < args.size(); i++){
					argv[i] = args[i];
				 // delete[] args[i];
				}
				argc = args.size();
			}


			char * create_token(std::string str) {
				char *arg = new char[str.size() + 1];
				copy(str.begin(), str.end(), arg);
				arg[str.size()] = '\0';

				return arg;
			}
	};

	TEST_FIXTURE(Application_Engine_learnHA, Test_engine_learnHA_bballData) {
		std::cout << "Running Test Test_engine_learnHA_bballData!" << std::endl;

		/*std::string simulation_command = "./BBC4CPS --engine learn-ha --simu-trace-file ../src/test_cases/engine/simu/data/simu_oscillator_4.txt
		 * --variable-category "x:output, y:output"  --output-file oscillator_4.txt --invariant 2  --degree 1 --boundary-degree 1
		 * --segment-relative-error 0.1  --cluster-algo dtw  --correlation-threshold 0.89 --distance-threshold 1.0   --ode-speedup 50
		 * --solver-type fixed --ode-solver ode5  --variable-types 'x0=t1,x1=t1'"  */

		int argc = 0;
		char *argv[31];	//This call has 31 command line arguments
		std::vector<char *> args;

		get_commandLineArguments_for_learn_ha_bball(argc, argv);
		user_inputs::ptr userInputs = user_inputs::ptr(new user_inputs());
		commandLineParser(argc, argv, userInputs);
		engineSelector engSelect(userInputs);

		engSelect.selectLearn_HA();	//Testing the learn-ha engine of our tool BBC4CPS

		std::string file_generated = "bball.txt", test_case_file = "../src/test_cases/engine/learn_ha/data/bball.txt";
		bool isEqual = compare_files(file_generated, test_case_file);
		CHECK_EQUAL(true, isEqual);
		cout << "*************************" << endl;

		var_mapping::var_mapping_ptr->clear(); //erase all variable mapping for HA

	}


	TEST_FIXTURE(Application_Engine_learnHA, Test_engine_learnHA_oscillatorData) {
		std::cout << "Running Test Test_engine_learnHA_oscillatorData!" << std::endl;

		/*std::string simulation_command = "./BBC4CPS --engine learn-ha --simu-trace-file ../src/test_cases/engine/simu/data/simu_oscillator_4.txt
		 * --variable-category "x:output, y:output"  --output-file oscillator_4.txt --invariant 2  --degree 1 --boundary-degree 1
		 * --segment-relative-error 0.1  --cluster-algo dtw  --correlation-threshold 0.89 --distance-threshold 1.0   --ode-speedup 50
		 * --solver-type fixed --ode-solver ode5  --variable-types 'x0=t1,x1=t1'"  */

		int argc = 0;
		char *argv[31];	//This call has 31 command line arguments
		std::vector<char *> args;

		get_commandLineArguments_for_learn_ha_oscillator(argc, argv);
		user_inputs::ptr userInputs = user_inputs::ptr(new user_inputs());
		commandLineParser(argc, argv, userInputs);
		engineSelector engSelect(userInputs);

		engSelect.selectLearn_HA();	//Testing the learn-ha engine of our tool BBC4CPS

		std::string file_generated = "oscillator_4.txt", test_case_file = "../src/test_cases/engine/learn_ha/data/oscillator_4.txt";
		bool isEqual = compare_files(file_generated, test_case_file);
		CHECK_EQUAL(true, isEqual);
		cout << "*************************" << endl;

		var_mapping::var_mapping_ptr->clear(); //erase all variable mapping for HA

	}

}
