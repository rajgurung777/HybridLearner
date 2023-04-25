/*
 * intermediateResult.cpp
 *
 *  Created on: 25-Sep-2021
 *      Author: amit
 */


#include "intermediateResult.h"


const std::string& intermediateResult::getDReachModelFilenameWithPath() const {
	return dReach_model_filename_with_path;
}

void intermediateResult::setDReachModelFilenameWithPath(
		const std::string &dReachModelFilenameWithPath) {
	dReach_model_filename_with_path = dReachModelFilenameWithPath;
}

const std::string&  intermediateResult::getOutputfilenameWithoutExtension() const {
	return outputfilename_without_extension;
}

void intermediateResult::setOutputfilenameWithoutExtension(
		const std::string &outputfilenameWithoutExtension) {
	outputfilename_without_extension = outputfilenameWithoutExtension;
}

const std::string& intermediateResult::getDReachSatSmt2filenameWithPath() const {
	return dReach_sat_smt2filename_with_path;
}

void intermediateResult::setDReachSatSmt2filenameWithPath(
		const std::string &dReachSatSmt2filenameWithPath) {
	dReach_sat_smt2filename_with_path = dReachSatSmt2filenameWithPath;
}

const std::string& intermediateResult::getDReachSatSmt2filenameWithPathWithoutExtension() const {
	return dReach_sat_smt2filename_with_path_without_extension;
}

void intermediateResult::setDReachSatSmt2filenameWithPathWithoutExtension(
		const std::string &dReachSatSmt2filenameWithPathWithoutExtension) {
	dReach_sat_smt2filename_with_path_without_extension =
			dReachSatSmt2filenameWithPathWithoutExtension;
}

const std::string&  intermediateResult::getSimulinkModelFilenameWithPath() const {
	return simulink_model_filename_with_path;
}

void intermediateResult::setSimulinkModelFilenameWithPath(
		const std::string &simulinkModelFilenameWithPath) {
	simulink_model_filename_with_path = simulinkModelFilenameWithPath;
}

const std::string&  intermediateResult::getSimulinkScriptFilenameWithPath() const {
	return simulink_script_filename_with_path;
}

void intermediateResult::setSimulinkScriptFilenameWithPath(
		const std::string &simulinkScriptFilenameWithPath) {
	simulink_script_filename_with_path = simulinkScriptFilenameWithPath;
}

const std::string&  intermediateResult::getMatlabDefaultPath() const {
	return matlab_default_path;
}

void intermediateResult::setMatlabDefaultPath(
		const std::string &matlabDefaultPath) {
	matlab_default_path = matlabDefaultPath;
}

const std::string&  intermediateResult::getMatlabPathForLearnedModel() const {
	return matlab_path_for_learned_model;
}

void intermediateResult::setMatlabPathForLearnedModel(
		const std::string &matlabPathForLearnedModel) {
	matlab_path_for_learned_model = matlabPathForLearnedModel;
}

const std::string&  intermediateResult::getMatlabPathForOriginalModel() const {
	return matlab_path_for_original_model;
}

void intermediateResult::setMatlabPathForOriginalModel(
		const std::string &matlabPathForOriginalModel) {
	matlab_path_for_original_model = matlabPathForOriginalModel;
}

const std::string&  intermediateResult::getToolRootPath() const {
	return tool_root_path;
}

bool intermediateResult::isLearnedModel() const {
	return learned_model;
}

void intermediateResult::setLearnedModel(bool learnedModel) {
	learned_model = learnedModel;
}

bool intermediateResult::isOriginalModel() const {
	return original_model;
}

void intermediateResult::setOriginalModel(bool originalModel) {
	original_model = originalModel;
}

void intermediateResult::setToolRootPath(const std::string &toolRootPath) {
	tool_root_path = toolRootPath;
}

const std::string&  intermediateResult::getLearnAlgoDefaultInputfilePath() const {
	return learnAlgo_default_inputfile_path;
}

void intermediateResult::setLearnAlgoDefaultInputfilePath(
		const std::string &learnAlgoDefaultInputfilePath) {
	learnAlgo_default_inputfile_path = learnAlgoDefaultInputfilePath;
}
