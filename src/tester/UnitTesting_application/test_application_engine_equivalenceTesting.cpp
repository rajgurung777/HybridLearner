/*
 * test_application_engine_equivalenceTesting.cpp
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


SUITE(MainApplication_Engine_equivalenceTest_TestSuite) {

	class Application_Engine_equivalenceTest
	{
		public:
		Application_Engine_equivalenceTest() {

			}
			~Application_Engine_equivalenceTest() { /* some teardown */
			}

			void get_commandLineArguments_for_equiTest_TwoTanks(int &argc, char *argv[]) {

				std::vector<char *> args;
				string token = "./BBC4CPS";
				args.push_back(create_token(token));
				token = "--engine";
				args.push_back(create_token(token));
				token = "equi-test";
				args.push_back(create_token(token));
				token = "--simulink-model-file";
				args.push_back(create_token(token));
				token = "../src/test_cases/engine/equi_test/data/twoTanks_16.slx ../src/test_cases/engine/equi_test/data/twoTanks_32.slx";
				args.push_back(create_token(token));
				token = "--variable-category";
				args.push_back(create_token(token));
				token = "x0:input, x1:output, x2:output";
				args.push_back(create_token(token));
				token = "--initial-value";
				args.push_back(create_token(token));
				token = "x0>=-0.1 & x0<=0.1 & x1>=1.2 & x1<=1.5 & x2>=1 & x2<=1";
				args.push_back(create_token(token));
				token = "--input-signal-type";
				args.push_back(create_token(token));
				token = "x0=linear";
				args.push_back(create_token(token));
				token = "--numberOf-control-points";
				args.push_back(create_token(token));
				token = "x0=2";
				args.push_back(create_token(token));
				token = "--max-stoptime";
				args.push_back(create_token(token));
				token = "400";
				args.push_back(create_token(token));
				token = "--max-stoptime-equitest";
				args.push_back(create_token(token));
				token = "100";
				args.push_back(create_token(token));
				token = "--simu-init-size";
				args.push_back(create_token(token));
				token = "1";
				args.push_back(create_token(token));
				token = "--max-traces";
				args.push_back(create_token(token));
				token = "1";
				args.push_back(create_token(token));
				token = "--time-horizon";
				args.push_back(create_token(token));
				token = "10";
				args.push_back(create_token(token));
				token = "--sampling-time";
				args.push_back(create_token(token));
				token = "0.001";
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

	TEST_FIXTURE(Application_Engine_equivalenceTest, Test_engine_equivalenceTest_TwoTanks) {
		std::cout << "Running Test Test_engine_equivalenceTest_TwoTanks!" << std::endl;

/*
CLI command = "./BBC4CPS --engine equi-test --simulink-model-file "../src/test_cases/engine/equi_test/data/twoTanks_16.slx ../src/test_cases/engine/equi_test/data/twoTanks_32.slx"
--variable-category "x0:input, x1:output, x2:output"  --initial-value "x0>=-0.1 & x0<=0.1 & x1>=1.2 & x1<=1.5 & x2>=1 & x2<=1"
 --input-signal-type "x0=linear" --numberOf-control-points "x0=2" --max-stoptime 400 --max-stoptime-equitest 100
 --simu-init-size 1 --max-traces 1 --time-horizon 10 --sampling-time 0.001
 */

		int argc = 0;
		char *argv[25];	//This call has 25 command line arguments
		std::vector<char *> args;

		get_commandLineArguments_for_equiTest_TwoTanks(argc, argv);
		user_inputs::ptr userInputs = user_inputs::ptr(new user_inputs());

		/*cout << "argc = " << argc << endl;
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
		cout <<"argv[48] =" << argv[48] <<endl;*/



		commandLineParser(argc, argv, userInputs);
		engineSelector engSelect(userInputs);

		bool isEquivalent = engSelect.selectEquiTest();	//Testing the equi-test engine of our tool BBC4CPS

		CHECK_EQUAL(true, isEquivalent);
		cout << "*************************" << endl;

		var_mapping::var_mapping_ptr->clear(); //erase all variable mapping for HA

	}



}



