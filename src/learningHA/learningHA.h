/*
 * learningHA.h
 *
 *  Created on: 08-Sep-2021
 *      Author: amit
 */

#ifndef LEARNINGHA_LEARNINGHA_H_
#define LEARNINGHA_LEARNINGHA_H_

#include "../commandLineParser/user_inputs.h"
#include "boost/timer/timer.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include "../io_functions/summary.h"
#include "learnHA_caller.h"

void learningHA(user_inputs::ptr user_Inputs, summary::ptr &report);


#endif /* LEARNINGHA_LEARNINGHA_H_ */
