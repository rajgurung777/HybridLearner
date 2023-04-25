/*
 * comp.h
 *
 *  Created on: Mar 31, 2010
 *      Author: frehse
 */

#ifndef COMP_H_
#define COMP_H_

//#include "utilities/math/numeric/approxComparator.h"
#include "approxComparator.h"

#include "tribool.h"

namespace math {
namespace numeric {

/** Tri-valued comparison operators that take into account
 * type-specific numeric errors.
 *
 * For exact types, the result is boolean and corresponds to
 * the exact comparison.
 */


template<typename scalar_type> tribool is_LT(const scalar_type& x,
		const scalar_type& y) {
	return math::numeric::approx_comparator<scalar_type>::is_LT(x,y);
}

template<typename scalar_type> tribool is_LE(const scalar_type& x,
		const scalar_type& y) {
	return math::numeric::approx_comparator<scalar_type>::is_LE(x,y);
}

template<typename scalar_type> tribool is_GT(const scalar_type& x,
		const scalar_type& y) {
	return math::numeric::approx_comparator<scalar_type>::is_LT(y,x);
}

template<typename scalar_type> tribool is_GE(const scalar_type& x,
		const scalar_type& y) {
	return math::numeric::approx_comparator<scalar_type>::is_LE(y,x);
}

/** Returns if x==y.
 *
 * In an inexact comparison, the result is false or indeterminate.
 * In an exact comparison, the result is true or false. */
template<typename scalar_type> tribool is_EQ(const scalar_type& x,
		const scalar_type& y) {
	return math::numeric::approx_comparator<scalar_type>::is_equal(x,y);
}

/** Returns true if x could be equal to y and false otherwise.
 *
 * The result is bool since the corresponding tribool computation
 * would at best return indeterminate. */
template<typename scalar_type> bool is_MEQ(const scalar_type& x,
		const scalar_type& y) {
	return math::numeric::approx_comparator<scalar_type>::is_maybe_equal(x,y);
}


/** Comparison using numeric comparisons. */
template <typename scalar_type>
class comp_less {
public:
	bool operator() (const scalar_type& x1, const scalar_type& x2) const {
		return is_LT(x1,x2);
	}
};

/** Comparison operator similar to std::less, return !less. */
template<typename scalar_type>
struct more {
	bool operator()(const scalar_type& x, const scalar_type& y) const {
		return y < x;
	}
	;
};



}
}

#endif /* COMP_H_ */
