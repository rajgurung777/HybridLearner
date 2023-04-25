/*
 * intermediateResult.h
 *
 *  Created on: 24-Sep-2021
 *      Author: amit
 */

#ifndef UTILITIES_INTERMEDIATERESULT_H_
#define UTILITIES_INTERMEDIATERESULT_H_

#include <string>
#include <list>
#include <iostream>
#include <boost/shared_ptr.hpp>


class intermediateResult {
private:
	std::string outputfilename_without_extension;	//for dReach
	std::string dReach_model_filename_with_path;	//output file that our tool generate
	std::string dReach_sat_smt2filename_with_path;	//Eg., osci_1_0.smt2
	std::string dReach_sat_smt2filename_with_path_without_extension;	//Eg., osci_1_0   This is used to identify the correct json file

	std::string simulink_model_filename_with_path;	//output file that our tool generate
	std::string simulink_script_filename_with_path;	//output file that our tool generate

	std::string matlab_default_path;	//Path when Matlab engine first started for Eg., "/home/amit/workspace/BBC4CPS/Release"
	std::string tool_root_path;	//Absolute Path for the Tool for Eg., "/home/amit/workspace/BBC4CPS"
	std::string matlab_path_for_original_model;	//Absolute Path of the benchmark for Eg., "/home/amit/workspace/BBC4CPS/src/benchmark/circle"
	std::string matlab_path_for_learned_model;	//Absolute Path of the learned model for Eg., "/home/amit/workspace/BBC4CPS/Release/outfilename"

	bool original_model;	//True if previous execution path is the original model ("...../BBC4CPS/src/benchmark/circle"), Otherwise False
	bool learned_model;	//True if previous execution path is the learned model ("...../BBC4CPS/Release/outfilename"), Otherwise False


	std::string learnAlgo_default_inputfile_path; //Path for the Learning Algo (Naijun's) for dumping the time-serise file Eg., "/home/amit/workspace/BBC4CPS/src/pwa/naijun"


public:
	typedef boost::shared_ptr<intermediateResult> ptr;

	const std::string& getDReachModelFilenameWithPath() const;
	void setDReachModelFilenameWithPath(
			const std::string &dReachModelFilenameWithPath);

	const std::string&  getOutputfilenameWithoutExtension() const;

	void setOutputfilenameWithoutExtension(
			const std::string &outputfilenameWithoutExtension);

	const std::string& getDReachSatSmt2filenameWithPath() const;
	void setDReachSatSmt2filenameWithPath(
			const std::string &dReachSatSmt2filenameWithPath);

	const std::string& getDReachSatSmt2filenameWithPathWithoutExtension() const;
	void setDReachSatSmt2filenameWithPathWithoutExtension(
			const std::string &dReachSatSmt2filenameWithPathWithoutExtension);

	const std::string&  getSimulinkModelFilenameWithPath() const;
	void setSimulinkModelFilenameWithPath(
			const std::string &simulinkModelFilenameWithPath);

	const std::string&  getSimulinkScriptFilenameWithPath() const;
	void setSimulinkScriptFilenameWithPath(
			const std::string &simulinkScriptFilenameWithPath);

	const std::string&  getMatlabDefaultPath() const;
	void setMatlabDefaultPath(const std::string &matlabDefaultPath);

	const std::string&  getMatlabPathForLearnedModel() const;
	void setMatlabPathForLearnedModel(
			const std::string &matlabPathForLearnedModel);

	const std::string&  getMatlabPathForOriginalModel() const;
	void setMatlabPathForOriginalModel(
			const std::string &matlabPathForOriginalModel);

	const std::string& getToolRootPath() const;
	void setToolRootPath(const std::string &toolRootPath);

	bool isLearnedModel() const;
	void setLearnedModel(bool learnedModel);

	bool isOriginalModel() const;
	void setOriginalModel(bool originalModel);

	const std::string&  getLearnAlgoDefaultInputfilePath() const;
	void setLearnAlgoDefaultInputfilePath(
			const std::string &learnAlgoDefaultInputfilePath);
};

#endif /* UTILITIES_INTERMEDIATERESULT_H_ */
