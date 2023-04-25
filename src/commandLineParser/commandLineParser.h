/*
 * commandLineParser.h
 *
 *  Created on: 08-Sep-2021
 *      Author: amit
 */

#ifndef COMMANDLINEPARSER_COMMANDLINEPARSER_H_
#define COMMANDLINEPARSER_COMMANDLINEPARSER_H_

#include <iostream>

// *********** Command Line Boost Program Options ********
#include <boost/program_options/config.hpp>
#include "boost/program_options.hpp"
#include <boost/config.hpp>
#include <boost/program_options/detail/config_file.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/algorithm/string.hpp> //string comparison
// *********** Command Line Boost Program Options ********

#include "user_inputs.h"
#include "../io_functions/data_structs.h"
#include "../hybridautomata/variable_to_index_mapping.h"
#include "../utilities/polytope/polytope.h"


void commandLineParser(int argc, char *argv[], user_inputs::ptr& userInputs);

void mapsVariable_to_Polytope(user_inputs::ptr& user, polytope::ptr& poly);

#endif /* COMMANDLINEPARSER_COMMANDLINEPARSER_H_ */
