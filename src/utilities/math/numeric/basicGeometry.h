/*
 * basic_geometry.h
 *
 *  Created on: Apr 29, 2010
 *      Author: frehse
 */

#ifndef BASIC_GEOMETRY_H_
#define BASIC_GEOMETRY_H_

#include "comp.h"

namespace math {
namespace numeric {

/** Returns whether 3 points are colinear.
 *
 * The points are given by (x1,y1),(x2,y2),(x3,y3).
 */
template<typename scalar_type>
bool is_colinear(const scalar_type& x1, const scalar_type& y1,
		const scalar_type& x2, const scalar_type& y2, const scalar_type& x3,
		const scalar_type& y3) {

	if (math::numeric::is_MEQ(x1, x2)) {
		if (math::numeric::is_MEQ(x2, x3)) {
			// if the x coordinates are all the same,
			// then the points are colinear
			return true;
		} else {
			scalar_type m = (y2 - y3) / (x2 - x3);
			scalar_type c = y3 - m * x3;
			return math::numeric::is_MEQ((m * x1 + c), y1);
		}
	} else {
		scalar_type m = (y2 - y1) / (x2 - x1);
		scalar_type c = y1 - m * x1;
		return math::numeric::is_MEQ((m * x3 + c), y3);
	}
}

/*
template<class scalar_type>
bool is_colinear(const scalar_type& x1, const scalar_type& y1,
		const scalar_type& x2, const scalar_type& y2, const scalar_type& x3,
		const scalar_type& y3) {

	if (math::numeric::is_MEQ(x1, x2)) {
		if (math::numeric::is_MEQ(x2, x3)) {
			// if the x coordinates are all the same,
			// then the points are colinear
			return true;
		} else {
			scalar_type m = (y2 - y3) / (x2 - x3);
			scalar_type c = y3 - m * x3;
			return math::numeric::is_MEQ((m * x1 + c), y1);
		}
	} else {
		scalar_type m = (y2 - y1) / (x2 - x1);
		scalar_type c = y1 - m * x1;
		return math::numeric::is_MEQ((m * x3 + c), y3);
	}
}
*/




/** Returns true if a,b,c is definitely ccw */
template<class scalar_type>
tribool is_ccw(const scalar_type& ax, const scalar_type& ay, const scalar_type& bx,
		const scalar_type& by, const scalar_type& cx, const scalar_type& cy) {
	scalar_type xmax = std::max(std::max(std::abs(ax),std::abs(bx)),std::abs(cx));
	scalar_type ymax = std::max(std::max(std::abs(ay),std::abs(by)),std::abs(cy));
	scalar_type m = (ax - bx) * (cy - by) - (ay - by) * (cx - bx);
	scalar_type scale = xmax*ymax;
	if(scale > 0.0)
		m = m/scale;
	if (m/scale < -1e-10)
		return true; //1e-6;
	else if (m/scale > 1e-10)
		return false;
	else
		return indeterminate();
};


}
}

#endif /* BASIC_GEOMETRY_H_ */
