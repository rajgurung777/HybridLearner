/*
 * string_operations.cpp
 *
 *  Created on: 27-Feb-2023
 *      Author: amit
 */


#include "string_operations.h"



std::string getFileName_without_Path(std::string filename, std::string &fullpath){
	std::string filename_without_path;

	linux_utilities::ptr linux_util = linux_utilities::ptr (new linux_utilities());

	std::string user_filename = filename;	//user can supply: just file name or absolute path from Release folder
	std::string fileName="", filePath="", userPath="";
	std::string key="/";
	std::size_t found = user_filename.rfind(key);	// locate the last "/" character
	if (found != std::string::npos) {

		fileName = user_filename.substr(found+1);		// is "bball.slx"
		unsigned int tot_len = user_filename.length(), file_len = fileName.length();
		file_len += 1; //to exclude the last '/' character in the path
		userPath = user_filename.substr(0, tot_len - file_len);	// is "../src/test_cases/engine/learn_ha/"

		//std::cout <<"file Name=" << fileName <<"   path="<< filePath << std::endl;

		//Todo: before we add the CurrentWorkingDirectoryWithPath. check if the user supplied path is actually the absolute path like "/usr/workfile/fullpath/ball.slx"
		filePath.append(linux_util->getCurrentWorkingDirectoryWithPath());  //Release or Debug
		filePath.append("/");

		filePath.append(userPath);	//
		//std::cout <<"file Name =" << fileName <<"   path ="<< filePath << std::endl;
//		intermediate->setMatlabPathForOriginalModel(filePath);	//do this outside the function

	} else {	//no path is supplied. Only fileName is supplied by the user
		fileName = user_filename;
		filePath = linux_util->getCurrentWorkingDirectoryWithPath();
//		intermediate->setMatlabPathForOriginalModel(filePath);	//do this outside the function
	}

	filename_without_path = fileName;
	fullpath = filePath;

	return filename_without_path;
}


std::string getFileNameWithPath(std::string filename, std::string path){

	//cout << "path = "  << path << endl;
	//cout << "filename = " << filename << endl;
	string str="";
	str.append(path);
	str.append("/");
	str.append(filename);

	//cout << "filename with path = " << str << endl;
	return str;
}
