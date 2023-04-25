/*
 * file_operations.h
 *
 *  Created on: 27-Feb-2023
 *      Author: amit
 */

#ifndef UTILITIES_FILE_OPERATIONS_H_
#define UTILITIES_FILE_OPERATIONS_H_

#include <iostream>

template<typename InputIterator1, typename InputIterator2>

bool range_equal(InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, InputIterator2 last2);

bool compare_files(const std::string& filename1, const std::string& filename2);

#endif /* UTILITIES_FILE_OPERATIONS_H_ */
