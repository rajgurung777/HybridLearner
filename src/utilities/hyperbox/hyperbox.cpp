/*
 * hyperbox.cpp
 *
 *  Created on: 15-Oct-2021
 *      Author: amit
 */


#include "hyperbox.h"


void hyperbox::setDimensionBounds(unsigned int dim_index, double lower, double upper) {
	intervals[dim_index].first = lower;
	intervals[dim_index].second = upper;
}

std::pair<double, double> hyperbox::getDimensionBounds(unsigned int dim_index){
	bounds values;

	values.first = intervals[dim_index].first;
	values.second = intervals[dim_index].second;

	return values;
}
