#ifndef APPROX_COMPARATOR_H_
#define APPROX_COMPARATOR_H_

/** This class provides comparison operators for limited precision
 * arithmetic.
 * The user define a positive bound bp and a negative bound bn.  
 * A value x is considered positive if x>=bn, and negative if
 * x<=bp. It may be zero if bn<=x<=bp. */

#include <assert.h>
//#include <utilities/math/basic_functions.h>

#include "../basic_functions.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "tribool.h"

namespace math {
namespace numeric {

template<typename scalar_type> class approx_comparator {
public:
	static bool is_exact_scalar_type() {
		return pos_error_bound == scalar_type(0);
	}
	;

	/** Corresponds to x1==x2 in the exact case.
	 *
	 * In an inexact comparison, the best result is indeterminate. */
	static math::tribool is_equal(const scalar_type& x1, const scalar_type& x2) {
		if (is_exact_scalar_type()) {
			return x1 == x2;
		} else {
			return !is_LT(x1, x2) && !is_LT(x2, x1);
		}
	}
	;

	/** Corresponds to x1==x2 in the exact case. */
	static bool is_maybe_equal(const scalar_type& x1, const scalar_type& x2) {
		return maybe(is_equal(x1,x2));
	}
	;

	static scalar_type diminished_by_error(const scalar_type& x) {
		if (x >= scalar_type(0))
			return x * sm_rel_error + neg_error_bound;
		else
			return x * lg_rel_error + neg_error_bound;
	}
	;

	static scalar_type augmented_by_error(const scalar_type& x) {
		if (x >= scalar_type(0))
			return x * lg_rel_error + pos_error_bound;
		else
			return x * sm_rel_error + pos_error_bound;
	}
	;

	/** Corresponds to x1>x2 in the exact case. */
	static bool is_maybe_strictly_larger(const scalar_type& x1,
			const scalar_type& x2) {
		if (is_exact_scalar_type()) {
			return x1 > x2;
		} else {
			return augmented_by_error(x1) > diminished_by_error(x2);
		}
	}
	;

	/** Corresponds to x1<x2 in the exact case. */
	static math::tribool is_LT(const scalar_type& x1, const scalar_type& x2) {
		if (is_exact_scalar_type()) {
			return x1 < x2;
		} else {
			if (augmented_by_error(x1) < diminished_by_error(x2))
				return true;
			else if (diminished_by_error(x1) >= augmented_by_error(x2))
				return false;
			else
				return math::indeterminate();
		}
	}
	;

	/** Corresponds to x1<=x2 in the exact case. */
	static math::tribool is_LE(const scalar_type& x1, const scalar_type& x2) {
		if (is_exact_scalar_type()) {
			return x1 <= x2;
		} else {
			if (augmented_by_error(x1) <= diminished_by_error(x2))
				return true;
			else if (diminished_by_error(x1) > augmented_by_error(x2))
				return false;
			else
				return math::indeterminate();
		}
	}
	;

	/** Corresponds to x1>x2 in the exact case. */
	static bool is_definitely_strictly_larger(const scalar_type& x1,
			const scalar_type& x2) {

		if (is_exact_scalar_type()) {
			return x1 > x2;
		} else {
			return diminished_by_error(x1) > augmented_by_error(x2);
		}
	}
	;

	/** Corresponds to x1<x2 in the exact case. */
	static bool is_definitely_strictly_smaller(const scalar_type& x1,
			const scalar_type& x2) {
		return is_definitely_strictly_larger(x2, x1);
	}
	;

	/** Corresponds to x==0 in the exact case. */
	static bool is_maybe_zero(const scalar_type& x) {
		if (is_exact_scalar_type())
			return x == scalar_type(0);
		else
			return (is_maybe_pos(x) && is_maybe_neg(x));
	}
	;

	/** Corresponds to x>=0 in the exact case. */
	static bool is_maybe_pos(const scalar_type& x) {
		return (x >= neg_error_bound);
	}
	;

	/** Corresponds to x<=0 in the exact case. */
	static bool is_maybe_neg(const scalar_type& x) {
		return (x <= pos_error_bound);
	}
	;

	/** Corresponds to x>0 in the exact case. */
	static bool is_definitely_strictly_pos(const scalar_type& x) {
		return !is_maybe_neg(x);
	}
	;

	/** Corresponds to x<0 in the exact case. */
	static bool is_definitely_strictly_neg(const scalar_type& x) {
		return !is_maybe_pos(x);
	}
	;

	/** Define a relative error bound of [1-x,1+x]. */
	static void set_rel_error_bound(const scalar_type& x) {
		assert(x >= scalar_type(0));
		lg_rel_error = scalar_type(1) + x;
		sm_rel_error = scalar_type(1) - x;
	}
	;

	/** Define an absolute error of +-x. */
	static void set_abs_error_bound(const scalar_type& x) {
		assert(x >= scalar_type(0));
		pos_error_bound = x;
		neg_error_bound = -x;
	}
	;
	static scalar_type get_rel_error_bound() {
		return lg_rel_error - scalar_type(1);
	}
	;

	static scalar_type get_abs_error_bound() {
		return pos_error_bound;
	}
	;

private:
	static scalar_type pos_error_bound;
	static scalar_type neg_error_bound;
	static scalar_type lg_rel_error;
	static scalar_type sm_rel_error;
};

template<typename scalar_type> scalar_type
		approx_comparator<scalar_type>::pos_error_bound = scalar_type(0);
template<typename scalar_type> scalar_type
		approx_comparator<scalar_type>::neg_error_bound = scalar_type(0);
template<typename scalar_type> scalar_type
		approx_comparator<scalar_type>::lg_rel_error = scalar_type(1);
template<typename scalar_type> scalar_type
		approx_comparator<scalar_type>::sm_rel_error = scalar_type(1);


template <> float approx_comparator<float>::pos_error_bound;
template <> float approx_comparator<float>::neg_error_bound;
template <> float approx_comparator<float>::lg_rel_error;
template <> float approx_comparator<float>::sm_rel_error;

template <> double approx_comparator<double>::pos_error_bound;
template <> double approx_comparator<double>::neg_error_bound;
template <> double approx_comparator<double>::lg_rel_error;
template <> double approx_comparator<double>::sm_rel_error;

template <> long double approx_comparator<long double>::pos_error_bound;
template <> long double approx_comparator<long double>::neg_error_bound;
template <> long double approx_comparator<long double>::lg_rel_error;
template <> long double approx_comparator<long double>::sm_rel_error;


/* this templates has issue with the use of header <math.h>
 *
 *
 template <> __float128 approx_comparator<__float128>::pos_error_bound;
template <> __float128 approx_comparator<__float128>::neg_error_bound;
template <> __float128 approx_comparator<__float128>::lg_rel_error;
template <> __float128 approx_comparator<__float128>::sm_rel_error;*/

}
}

#endif /*APPROX_COMPARATOR_H_*/
