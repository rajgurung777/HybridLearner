/*
 * linux_utilities.h
 *
 *  Created on: 07-Nov-2021
 *      Author: amit
 */

#ifndef UTILITIES_LINUX_UTILITIES_H_
#define UTILITIES_LINUX_UTILITIES_H_


//#include <stdlib.h>
#include <iostream>
#include <string>

#include <cstddef>
#include <unistd.h>
#include <boost/shared_ptr.hpp>


class linux_utilities {
	std::string currentWorkingDirectoryName;
	std::string currentWorkingDirectoryWithPath;
	std::string parentWorkingDirectoryWithPath;



public:
	typedef boost::shared_ptr<linux_utilities> ptr;

	//Constructor to populate the current working directory's  name and path
	linux_utilities();

	//Returns the current working directory name without path
	const std::string& getCurrentWorkingDirectoryName() const;
	void setCurrentWorkingDirectoryName(
			const std::string &currentWorkingDirectoryName);

	//Return the current working directory with path excluding / character at the end
	const std::string& getCurrentWorkingDirectoryWithPath() const;
	void setCurrentWorkingDirectoryWithPath(
			const std::string &currentWorkingDirectoryWithPath);

	//Return the parent working directory with path excluding / character at the end
	const std::string& getParentWorkingDirectoryWithPath() const;
	void setParentWorkingDirectoryWithPath(
			const std::string &parentWorkingDirectoryWithPath);
};


#endif /* UTILITIES_LINUX_UTILITIES_H_ */
