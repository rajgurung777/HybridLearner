/*
 * linux_utilities.cpp
 *
 *  Created on: 07-Nov-2021
 *      Author: amit
 */



#include "linux_utilities.h"

using namespace std;

//Constructor to populate the current working directory's  name and path
linux_utilities::linux_utilities() {
	std::string str = "";
	char tmp[256];
	getcwd(tmp, 256);
	/*if (getcwd(tmp, 256)) == NULL) {
		cout << "Error executing command getcwd()" << endl;
	}*/

	currentWorkingDirectoryWithPath = tmp;

	//cout << "Current working directory with path: " << currentWorkingDirectoryWithPath << endl;	//Eg "/home/amit/workspace/BBC4CPS/Debug";
	std::string key ("/");	//Look for the last "/" character
	std::size_t found = std::string(tmp).rfind(key); //search from reverse for the "/" character
	//cout <<"pos = " << found <<endl;
	if (found!=std::string::npos) {
		currentWorkingDirectoryName = std::string(tmp).substr(found+1);
		//cout << "currentWorkingDirectoryName = " << currentWorkingDirectoryName << endl;
		parentWorkingDirectoryWithPath = std::string(tmp).substr(0, found); //Excluding the / character at the end
		//cout << "parentWorkingDirectoryWithPath = " << parentWorkingDirectoryWithPath << endl;
	}

}


const std::string& linux_utilities::getCurrentWorkingDirectoryName() const {
	return currentWorkingDirectoryName;
}

void linux_utilities::setCurrentWorkingDirectoryName(
		const std::string &currentWorkingDirectoryName) {
	this->currentWorkingDirectoryName = currentWorkingDirectoryName;
}

//Excluding the / character at the end
const std::string& linux_utilities::getCurrentWorkingDirectoryWithPath() const {
	return currentWorkingDirectoryWithPath;
}

void linux_utilities::setCurrentWorkingDirectoryWithPath(
		const std::string &currentWorkingDirectoryWithPath) {
	this->currentWorkingDirectoryWithPath = currentWorkingDirectoryWithPath;
}

//Excluding the / character at the end
const std::string& linux_utilities::getParentWorkingDirectoryWithPath() const {
	return parentWorkingDirectoryWithPath;
}

void linux_utilities::setParentWorkingDirectoryWithPath(
		const std::string &parentWorkingDirectoryWithPath) {
	this->parentWorkingDirectoryWithPath = parentWorkingDirectoryWithPath;
}
