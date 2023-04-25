/*
 * boost_interval_utility.h
 *
 *  Created on: Mar 20, 2013
 *      Author: frehse
 */

#ifndef BOOST_INTERVAL_UTILITY_H_
#define BOOST_INTERVAL_UTILITY_H_

/** This file includes utility functions for using the boost::numeric::interval class in SpaceEx. */

#include <boost/numeric/interval.hpp>

#include "utilities/math/numeric/comp.h"

template<class scalar_type, class policy>
std::ostream& operator<<(std::ostream& os, const boost::numeric::interval<scalar_type,policy>& p) {
	os << "[" << p.lower() << "," << p.upper() << "]";
	return os;
}

/** Forward declaration of template */
template<typename result_type, typename scalar_type>
class converter;
/** Partial specialization for boost intervals */
template<class T, class Policies>
class converter<boost::numeric::interval<T, Policies>,double> {
public:
	static inline boost::numeric::interval<T, Policies> convert(const double& x) {
		return boost::numeric::interval<T, Policies>(x);
	}
};

template<class T, class Policies> inline
boost::numeric::interval<T, Policies> pow(const boost::numeric::interval<T, Policies>& x, const boost::numeric::interval<T, Policies>& y)
{
	boost::numeric::interval<T, Policies> intv;
	if (math::numeric::is_MEQ(y.lower(),y.upper())) {
		T e = y.upper();
		int ei = (int) e;
		if (math::numeric::is_MEQ(e,T(ei))) {
			return pow(x,ei);
		}
	}
	throw std::runtime_error("pow undef");
	return intv;
};


#endif /* BOOST_INTERVAL_UTILITY_H_ */
