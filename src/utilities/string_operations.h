/*
 * string_operations.h
 *
 *  Created on: 27-Feb-2023
 *      Author: amit
 *
 *      This file holds all operations related to string data type.
 */

#ifndef UTILITIES_STRING_OPERATIONS_H_
#define UTILITIES_STRING_OPERATIONS_H_

#include <iostream>
#include "linux_utilities.h"

using namespace std;

//Takes a string of filename as input and returns filename without path
std::string getFileName_without_Path(std::string filename, std::string &fullpath);

/*
 * Takes filename and filepath as input and returns ad direct concatenation filename including fullpath
 * 	std::string filename: filename without path
 * 	std::string path: the path of the filename
 * Returns:
 * 	std::string filename-with-path
 */
std::string getFileNameWithPath(std::string filename, std::string path);

#endif /* UTILITIES_STRING_OPERATIONS_H_ */
