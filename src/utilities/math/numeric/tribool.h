/*
 * tribool.h
 *
 *  Created on: Mar 31, 2010
 *      Author: frehse
 */

#ifndef TRIBOOL_H_
#define TRIBOOL_H_

#include <string>
#include <boost/logic/tribool.hpp>

namespace math {
typedef boost::tribool tribool;

/** Returns whether t is true (and not indeterminate). */
inline tribool definitely(const tribool& t) {
	return t;
}
;

/** Returns whether t is indeterminate (and not true). */
inline bool is_indeterminate(const tribool& t) {
	return boost::logic::indeterminate(t);
}
;

/** Returns whether t is true or indeterminate. */
inline bool maybe(const tribool& t) {
	return bool(t) || boost::logic::indeterminate(t);
}
;

/** Returns the indeterminate value. */
inline tribool indeterminate() {
	return boost::indeterminate;
}

/** Returns the string corresponding to the tribool. */
inline std::string tribool_string(const tribool& t) {
	if (is_indeterminate(t)) {
		return "indeterminate";
	} else if (definitely(t)) {
		return "true";
	} else
		return "false";
}

}

#endif /* TRIBOOL_H_ */
