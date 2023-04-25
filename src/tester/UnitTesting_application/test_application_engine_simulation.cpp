/*
 * test_application_engines.cpp
 *
 *  Created on: 28-Feb-2023
 *      Author: amit
 */


#include <iostream>
#include <vector>
#include <UnitTest++/UnitTest++.h>
#include "../../utilities/file_operations.h"
//#include <boost/tokenizer.hpp>
#include "../../commandLineParser/commandLineParser.h"
#include "../../commandLineParser/user_inputs.h"
#include "../../application/engineSelector.h"
//#include "MatlabEngine.hpp"


using namespace std;
//using namespace matlab::engine;


SUITE(MainApplication_TestSuite) {

	class Application
	{
		public:
			Application() {

			}
			~Application() { /* some teardown */
			}

			void get_commandLineArguments_for_simulation_bball(int &argc, char *argv[]) {

/*
				typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
				boost::char_separator<char> sep(" ");
				tokenizer tokens(simulation_command, sep);
				argc = 0;
				std::vector<char *> args;

				for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
					//std::cout << (*tok_iter) << std::endl;
					string ss = (std::string) (*tok_iter);

					char *arg = new char[(*tok_iter).size() + 1];
					copy(ss.begin(), ss.end(), arg);
					arg[(*tok_iter).size()] = '\0';
					args.push_back(arg);
		//			boost::trim(ss);
					std::cout << "token = " << arg << std::endl;
					//argv[argc] = arg;
					argc++;
				}
				args.push_back(0);

				// now exec with &args[0], and then:
				for(size_t i = 0; i < args.size(); i++){
					argv[i] = args[i];
				 // delete[] args[i];
				}
				//But this approach does not support quotes etc
*/

/*
				std::vector<char *> args;
				std::istringstream iss(simulation_command);
				std::string token;
				while(iss >> token) {
					cout <<"token = " << token <<endl;
				  char *arg = new char[token.size() + 1];
				  copy(token.begin(), token.end(), arg);
				  arg[token.size()] = '\0';
				  args.push_back(arg);
				}
				args.push_back(0);

				// now exec with &args[0], and then:
				for(size_t i = 0; i < args.size(); i++){
					argv[i] = args[i];
				 // delete[] args[i];
				}
				//But this approach does not support quotes etc
*/

				std::vector<char *> args;
				string token = "./BBC4CPS";
				args.push_back(create_token(token));
				token = "-e";
				args.push_back(create_token(token));
				token = "simu";
				args.push_back(create_token(token));
				token = "--simulink-model-file";
				args.push_back(create_token(token));
				token = "../src/test_cases/engine/learn_ha_loop/ex_sldemo_bounce_Input.slx";
				args.push_back(create_token(token));
				token = "--variable-category";
				args.push_back(create_token(token));
				token = "u:input, x:output, v:output";
				args.push_back(create_token(token));
				token = "--output-file";
				args.push_back(create_token(token));
				token = "bball.txt";
				args.push_back(create_token(token));
				token = "--simu-init-size";
				args.push_back(create_token(token));
				token = "2";
				args.push_back(create_token(token));
				token = "--initial-value";
				args.push_back(create_token(token));
				token = "u>=-9.5 & u<=-9.9 & x>=10.2 & x<=10.5 & v>=15 & v<=15";
				args.push_back(create_token(token));
				token = "--input-signal-type";
				args.push_back(create_token(token));
				token = "u=linear";
				args.push_back(create_token(token));
				token = "--numberOf-control-points";
				args.push_back(create_token(token));
				token = "u=4";
				args.push_back(create_token(token));
				token = "--time-horizon";
				args.push_back(create_token(token));
				token = "10";
				args.push_back(create_token(token));
				token = "--sampling-time";
				args.push_back(create_token(token));
				token = "0.1";
				args.push_back(create_token(token));


				//cout <<" tokens created"  <<endl;
				for(size_t i = 0; i < args.size(); i++){
					argv[i] = args[i];
				 // delete[] args[i];
				}
				argc = args.size();
			}

			void get_commandLineArguments_for_simulation_oscillator(int &argc, char *argv[]) {


				std::vector<char *> args;
				string token = "./BBC4CPS";
				args.push_back(create_token(token));
				token = "-e";
				args.push_back(create_token(token));
				token = "simu";
				args.push_back(create_token(token));
				token = "--simulink-model-file";
				args.push_back(create_token(token));
				token = "../src/test_cases/engine/learn_ha_loop/oscillator.slx";
				args.push_back(create_token(token));
				token = "--variable-category";
				args.push_back(create_token(token));
				token = "x:output, y:output";
				args.push_back(create_token(token));
				token = "--output-file";
				args.push_back(create_token(token));
				token = "oscillator_4.txt";
				args.push_back(create_token(token));
				token = "--simu-init-size";
				args.push_back(create_token(token));
				token = "2";
				args.push_back(create_token(token));
				token = "--initial-value";
				args.push_back(create_token(token));
				token = "x>=0.01 & x<=0.09 & y>=0.01 & y<=0.09";
				args.push_back(create_token(token));

				token = "--time-horizon";
				args.push_back(create_token(token));
				token = "10";
				args.push_back(create_token(token));
				token = "--sampling-time";
				args.push_back(create_token(token));
				token = "0.1";
				args.push_back(create_token(token));


				//cout <<" tokens created"  <<endl;
				for(size_t i = 0; i < args.size(); i++){
					argv[i] = args[i];
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

	TEST_FIXTURE(Application, Test_Simulation_engine_bball) {

		std::cout << "Running Test Test_Simulation_engine_bball!" << std::endl;

		/*std::string simulation_command = "./BBC4CPS -e simu  --simulink-model-file ../src/test_cases/engine/learn_ha_loop/ex_sldemo_bounce_Input.slx "
				"--variable-category 'u:input, x:output, v:output'  --output-file bball.txt --simu-init-size 2 "
				"--initial-value 'u>=-9.5 & u<=-9.9 & x>=10.2 & x<=10.5 & v>=15 & v<=15'  --input-signal-type 'u=linear' "
				"--numberOf-control-points 'u=4'  --time-horizon 10 --sampling-time 0.1";*/


		int argc = 0;

//		char **argv;
		char *argv[21];	//This call has 21 command line arguments
		std::vector<char *> args;

		get_commandLineArguments_for_simulation_bball(argc, argv);
		/*cout <<"argc=" << argc << endl;
		cout <<"argv[0] =" << argv[0] <<endl;
		cout <<"argv[1] =" << argv[1] <<endl;
		cout <<"argv[2] =" << argv[2] <<endl;
		cout <<"argv[3] =" << argv[3] <<endl;
		cout <<"argv[4] =" << argv[4] <<endl;
		cout <<"argv[5] =" << argv[5] <<endl;
		cout <<"argv[6] =" << argv[6] <<endl;
		cout <<"argv[7] =" << argv[7] <<endl;
		cout <<"argv[8] =" << argv[8] <<endl;
		cout <<"argv[9] =" << argv[9] <<endl;
		cout <<"argv[10] =" << argv[10] <<endl;
		cout <<"argv[11] =" << argv[11] <<endl;
		cout <<"argv[12] =" << argv[12] <<endl;
		cout <<"argv[13] =" << argv[13] <<endl;
		cout <<"argv[14] =" << argv[14] <<endl;
		cout <<"argv[15] =" << argv[15] <<endl;
		cout <<"argv[16] =" << argv[16] <<endl;
		cout <<"argv[17] =" << argv[17] <<endl;
		cout <<"argv[18] =" << argv[18] <<endl;
		cout <<"argv[19] =" << argv[19] <<endl;
		cout <<"argv[20] =" << argv[20] <<endl;*/

		user_inputs::ptr userInputs = user_inputs::ptr(new user_inputs());

		commandLineParser(argc, argv, userInputs);
		engineSelector engSelect(userInputs);

		engSelect.selectSimu();	//Testing the SIMULATION engine of our tool BBC4CPS

		std::string file_generated = "simu_bball.txt", test_case_file = "../src/test_cases/engine/simu/data/simu_bball.txt";

		//bool isEqual = compare_files("file1.txt", "file2.txt");
		bool isEqual = compare_files(file_generated, test_case_file);
//		cout <<"file is " << isEqual <<"   Hello!" <<endl;
		CHECK_EQUAL(isEqual, true);
		cout << "*************************" << endl;
		//CHECK_EQUAL(1, 1);

		// Terminate MATLAB session
		//matlab::engine::terminateEngineClient();
		var_mapping::var_mapping_ptr->clear(); //erase all variable mapping for HA

	}

	TEST_FIXTURE(Application, Test_Simulation_engine_oscillator) {

		std::cout << "Running Test Test_Simulation_engine_oscillator!" << std::endl;

		/*std::string simulation_command = "./BBC4CPS -e simu  --simulink-model-file ../src/test_cases/engine/learn_ha_loop/oscillator.slx
		 * --variable-category "x:output, y:output"  --output-file oscillator_4.txt --simu-init-size 2
		 * --initial-value "x>=0.01 & x<=0.09 & y>=0.01 & y<=0.09" --time-horizon 10 --sampling-time 0.1 ";*/

		int argc = 0;
		char *argv[17];	//This call has 17 command line arguments
		std::vector<char *> args;
		get_commandLineArguments_for_simulation_oscillator(argc, argv);

		/*cout <<"argc=" << argc << endl;
		cout <<"argv[0] =" << argv[0] <<endl;
		cout <<"argv[1] =" << argv[1] <<endl;
		cout <<"argv[2] =" << argv[2] <<endl;
		cout <<"argv[3] =" << argv[3] <<endl;
		cout <<"argv[4] =" << argv[4] <<endl;
		cout <<"argv[5] =" << argv[5] <<endl;
		cout <<"argv[6] =" << argv[6] <<endl;
		cout <<"argv[7] =" << argv[7] <<endl;
		cout <<"argv[8] =" << argv[8] <<endl;
		cout <<"argv[9] =" << argv[9] <<endl;
		cout <<"argv[10] =" << argv[10] <<endl;
		cout <<"argv[11] =" << argv[11] <<endl;
		cout <<"argv[12] =" << argv[12] <<endl;
		cout <<"argv[13] =" << argv[13] <<endl;
		cout <<"argv[14] =" << argv[14] <<endl;
		cout <<"argv[15] =" << argv[15] <<endl;
		cout <<"argv[16] =" << argv[16] <<endl;*/


		user_inputs::ptr userInputs = user_inputs::ptr(new user_inputs());
		commandLineParser(argc, argv, userInputs);
		engineSelector engSelect(userInputs);

		engSelect.selectSimu();	//Testing the SIMULATION engine of our tool BBC4CPS

		std::string file_generated = "simu_oscillator_4.txt", test_case_file = "../src/test_cases/engine/simu/data/simu_oscillator_4.txt";

		bool isEqual = compare_files(file_generated, test_case_file);
		CHECK_EQUAL(true, isEqual);
		cout << "*************************" << endl;

		var_mapping::var_mapping_ptr->clear(); //erase all variable mapping for HA
	}



}

