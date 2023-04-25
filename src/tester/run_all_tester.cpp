/*
 * run_all_tester.cpp
 *
 *  Created on: 27-Feb-2023
 *      Author: amit
 */

#include <iostream>
#include <UnitTest++/UnitTest++.h>

using namespace std;


/*
TEST(Sanity)
{
	std::cout << "Running Test Sanity!" << std::endl;
	CHECK_EQUAL(1, 1);
}
*/

int main(int, const char *[])
{
	std::cout << "Running Tester!!" << std::endl;
   return UnitTest::RunAllTests();
}

