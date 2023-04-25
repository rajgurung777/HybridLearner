/*
 * string_parser.h
 *
 *  Created on: 22-Jun-2018
 *      Author: rajarshi
 */

#ifndef UTILITIES_STRING_PARSER_H_
#define UTILITIES_STRING_PARSER_H_


#include <list>
#include <vector>
#include <utility>
#include <string>
#include <iostream>

std::list<std::pair<double, std::string> > linexp_parser(std::string expr);

/**
 * Parses a string which is a comma separated list of location ids.
 * Returns a vector of location ids in the same order from left to right, as present in the string
 */
std::vector<unsigned int> path_parser(std::string path);


#endif /* UTILITIES_STRING_PARSER_H_ */
