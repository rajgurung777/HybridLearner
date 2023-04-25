/*
 * test_application_engine_learnHALoop.cpp
 *
 *  Created on: 02-Mar-2023
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


SUITE(MainApplication_Engine_LearnHALoop_Test_TestSuite) {

	class Application_Engine_LearnHALoop
	{
		public:
			Application_Engine_LearnHALoop() {
			}
			~Application_Engine_LearnHALoop() { /* some teardown */
			}

			void get_commandLineArguments_for_LearnHALoop_BBall(int &argc, char *argv[]) {

				std::vector<char *> args;
				string token = "./BBC4CPS";
				args.push_back(create_token(token));
				token = "--engine";
				args.push_back(create_token(token));
				token = "learn-ha-loop";
				args.push_back(create_token(token));
				token = "--simulink-model-file";
				args.push_back(create_token(token));
				token = "../src/test_cases/engine/learn_ha_loop/ex_sldemo_bounce_Input.slx";
				args.push_back(create_token(token));
				token = "--output-file";
				args.push_back(create_token(token));
				token = "bball_test.txt";
				args.push_back(create_token(token));
				token = "--variable-category";
				args.push_back(create_token(token));
				token = "u:input, x:output, v:output";
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
				token = "--modes";
				args.push_back(create_token(token));
				token = "1";
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
				token = "--fixed-interval-data";
				args.push_back(create_token(token));
				token = "1";
				args.push_back(create_token(token));
				token = "--invariant";
				args.push_back(create_token(token));
				token = "2";
				args.push_back(create_token(token));
				token = "--ode-speedup";
				args.push_back(create_token(token));
				token = "50";
				args.push_back(create_token(token));
				token = "--variable-types";
				args.push_back(create_token(token));
				token = "u=t1,x1=t1";
				args.push_back(create_token(token));
				token = "--precision-equivalence";
				args.push_back(create_token(token));
				token = "50.0";
				args.push_back(create_token(token));
				token = "--max-traces";
				args.push_back(create_token(token));
				token = "5";
				args.push_back(create_token(token));
				token = "--max-stoptime";
				args.push_back(create_token(token));
				token = "20";
				args.push_back(create_token(token));
				token = "--max-generate-trace-size";
				args.push_back(create_token(token));
				token = "1024";
				args.push_back(create_token(token));
				token = "--time-horizon";
				args.push_back(create_token(token));
				token = "13";
				args.push_back(create_token(token));
				token = "--sampling-time";
				args.push_back(create_token(token));
				token = "0.01";
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

	TEST_FIXTURE(Application_Engine_LearnHALoop, Test_engine_LearnHALoop_BBall) {
		std::cout << "Running Test Test_engine_LearnHALoop_BBall!" << std::endl;

/*
CLI command = "./BBC4CPS --engine learn-ha-loop --simulink-model-file ../src/test_cases/engine/learn_ha_loop/ex_sldemo_bounce_Input.slx
--output-file bball_4.txt  --variable-category "u:input, x:output, v:output"  --simu-init-size 2
--initial-value "u>=-9.5 & u<=-9.9 & x>=10.2 & x<=10.5 & v>=15 & v<=15"  --input-signal-type "u=linear" --numberOf-control-points "u=4"
--modes 1 --degree 1 --boundary-degree 1 --segment-relative-error 0.1  --cluster-algo dtw  --correlation-threshold 0.8 --distance-threshold 9.0
--fixed-interval-data 1 --invariant 2 --ode-speedup 50 --variable-types 'u=t1,x1=t1' --precision-equivalence 50.0 --max-traces 5
--max-stoptime 20   --max-generate-trace-size 1024  --time-horizon 13 --sampling-time 0.01
 */

		int argc = 0;
		char *argv[51];	//This call has 51 command line arguments
		std::vector<char *> args;

		get_commandLineArguments_for_LearnHALoop_BBall(argc, argv);
		user_inputs::ptr userInputs = user_inputs::ptr(new user_inputs());


		commandLineParser(argc, argv, userInputs);
		engineSelector engSelect(userInputs);

		/*
			cout << "argc = " << argc << endl;
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
			cout <<"argv[20] =" << argv[20] <<endl;
			cout <<"argv[21] =" << argv[21] <<endl;
			cout <<"argv[22] =" << argv[22] <<endl;
			cout <<"argv[23] =" << argv[23] <<endl;
			cout <<"argv[24] =" << argv[24] <<endl;
			cout <<"argv[25] =" << argv[25] <<endl;
			cout <<"argv[26] =" << argv[26] <<endl;
			cout <<"argv[27] =" << argv[27] <<endl;
			cout <<"argv[28] =" << argv[28] <<endl;
			cout <<"argv[29] =" << argv[29] <<endl;
			cout <<"argv[30] =" << argv[30] <<endl;
			cout <<"argv[31] =" << argv[31] <<endl;
			cout <<"argv[32] =" << argv[32] <<endl;
			cout <<"argv[33] =" << argv[33] <<endl;
			cout <<"argv[34] =" << argv[34] <<endl;
			cout <<"argv[35] =" << argv[35] <<endl;
			cout <<"argv[36] =" << argv[36] <<endl;
			cout <<"argv[37] =" << argv[37] <<endl;
			cout <<"argv[38] =" << argv[38] <<endl;
			cout <<"argv[39] =" << argv[39] <<endl;
			cout <<"argv[40] =" << argv[40] <<endl;
			cout <<"argv[41] =" << argv[41] <<endl;
			cout <<"argv[42] =" << argv[42] <<endl;
			cout <<"argv[43] =" << argv[43] <<endl;
			cout <<"argv[44] =" << argv[44] <<endl;
			cout <<"argv[45] =" << argv[45] <<endl;
			cout <<"argv[46] =" << argv[46] <<endl;
			cout <<"argv[47] =" << argv[47] <<endl;
			cout <<"argv[48] =" << argv[48] <<endl;
			cout <<"argv[49] =" << argv[49] <<endl;
			cout <<"argv[50] =" << argv[50] <<endl;
		*/

		engSelect.selectLearn_HA_loop();	//Testing the equi-test engine of our tool BBC4CPS
		/*
		This engine produces two script files and a .slx model (after executing one of the script) inside an output folder (by the model name).
			 script file 1: script to generate the .slx model on its execution.
			 script file 2: script to execute the .slx model for simulation.
		 */

		std::string generated_file1 = "bball_test/getModel_bball_test0.m", test_case_file1 = "../src/test_cases/engine/learn_ha_loop/data/getModel_bball_test0.m";
		bool isEqual_one = compare_files(generated_file1, test_case_file1);

		std::string generated_file2 = "bball_test/run_script_bball_test0.m", test_case_file2 = "../src/test_cases/engine/learn_ha_loop/data/run_script_bball_test0.m";
		bool isEqual_two = compare_files(generated_file2, test_case_file2);

		bool flag=true;
		if ((isEqual_one == true) && (isEqual_two == true))
			flag = true;
		else
			flag = false;

		CHECK_EQUAL(true, flag);
		cout << "*************************" << endl;

		var_mapping::var_mapping_ptr->clear(); //erase all variable mapping for HA

	}


}



