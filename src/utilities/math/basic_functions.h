/*
 * basic_functions.h
 *
 *  Created on: 07-Oct-2021
 *      Author: amit
 *
 *      This file is taken from the tool XSpeed
 */

#ifndef UTILITIES_MATH_BASIC_FUNCTIONS_H_
#define UTILITIES_MATH_BASIC_FUNCTIONS_H_



/** Returns the absolute value of x. */
template<typename scalar_type> scalar_type abs_element(const scalar_type& x) {
	if (x < scalar_type(0))
		return -x;
	else
		return x;
}

/** Returns the absolute value of x. */
template<typename scalar_type> scalar_type abs(const scalar_type& x) {
	if (x < scalar_type(0))
		return -x;
	else
		return x;
}

/** Returns the max of x,y,z. */
template<typename scalar_type> scalar_type trimax(const scalar_type& x,
		const scalar_type& y, const scalar_type& z) {
	if (x > y)
		if (x > z)
			return x;
		else
			return z;
	else if (y > z)
		return y;
	else
		return z;
}

/** Returns the max of a quadratic function over a finite interval.
 *
 * The function is given by ax^2+bx+c with l<=x<=u.
 * The value of x for which the maximum is attained is returned in x_max. */
template<typename scalar_type> scalar_type quadratic_max(const scalar_type& a,
		const scalar_type& b, const scalar_type& c, const scalar_type& l,
		const scalar_type& u, scalar_type& x_max) {
	scalar_type k = -b / (scalar_type(2) * a);
	if (a < scalar_type(0) && l <= k && k <= u) {
		// the min is at k
		x_max = k;
		return (scalar_type(4) * a * c - b * b) / (scalar_type(4) * a);
	} else {
		scalar_type y_l = a * l * l + b * l + c;
		scalar_type y_u = a * u * u + b * u + c;
		if (y_u > y_l) {
			x_max = u;
			return y_u;
		} else {
			x_max = l;
			return y_l;
		}
	}
}


#endif /* UTILITIES_MATH_BASIC_FUNCTIONS_H_ */
