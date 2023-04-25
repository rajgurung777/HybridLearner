/*This file is taken from XSpeed tool
 *
 *
 * 2d_geometry.h
 *
 *  Created on: 30-Nov-2015
 *      Author: amit
 */

#ifndef GEOMETRY_2D_H_
#define GEOMETRY_2D_H_

//#include <utilities/math/numeric/basicGeometry.h>
#include "numeric/basicGeometry.h"
#include <vector>

typedef std::pair<double, double> point;

bool is_collinear(point p1, point p2, point p3);

//Returns angle between the vector u and v
double angle_uv(std::vector<double> u, std::vector<double> v);

//Returns a vector for a given angle on a X-Y plane w.r.t. the center of a Circle where vector u(1,0) is 0 degree
// the angle increases by anti-clock wise rotation
//std::pair<double,double> angle_to_vector(double angle);

//Returns a vector for a given angle on a X-Y plane w.r.t. the center of a Circle where vector u(1,0) is 0 degree
// the angle increases by anti-clock wise rotation
std::vector<double> angle_to_vector(double angle);

//Returns a vector for a given radian on a X-Y plane w.r.t. the center of a Circle where vector u(1,0) is 0 degree
// the angle increases by anti-clock wise rotation
std::vector<double> radian_to_vector(double radian);


#endif /* GEOMETRY_2D_H_ */
