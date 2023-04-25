/*
 * hyperbox.h
 *
 *  Created on: 15-Oct-2021
 *      Author: amit
 */

#ifndef UTILITIES_HYPERBOX_HYPERBOX_H_
#define UTILITIES_HYPERBOX_HYPERBOX_H_

#include <list>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "../../hybridautomata/variable_to_index_mapping.h"

class hyperbox: public var_mapping{
	typedef std::pair<double, double> bounds;
	std::vector <bounds>	intervals;
	unsigned int dimension;
public:
	typedef boost::shared_ptr<hyperbox> ptr;
	hyperbox(){
		dimension = 0;
		intervals.resize(0);
	}
	hyperbox(unsigned int dim){
		dimension = dim;
		intervals.resize(dim);
	}

	void setDimensionBounds(unsigned int dim_index, double lower, double upper);
	std::pair<double, double> getDimensionBounds(unsigned int dim_index);
};


#endif /* UTILITIES_HYPERBOX_HYPERBOX_H_ */
