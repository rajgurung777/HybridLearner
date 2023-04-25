/*
 * 2d_geometry.cpp
 *
 *  Created on: 30-Nov-2015
 *      Author: amit
 */

#include "2dGeometry.h"
#include <math.h>

#define PI 3.14159265

bool is_collinear(point p1, point p2, point p3) {
	double x1, y1, x2, y2, x3, y3;
	x1 = p1.first;
	y1 = p1.second;

	x2 = p2.first;
	y2 = p2.second;

	x3 = p3.first;
	y3 = p3.second;

	return math::numeric::is_colinear(x1, y1, x2, y2, x3, y3);
}

double angle_uv(std::vector<double> u, std::vector<double> v) {
	double angle_res, dot_prod = 0.0;
	assert(u.size() == v.size());
	for (unsigned int i = 0; i < u.size(); i++) {
		dot_prod = dot_prod + u[i] * v[i];
	}

	//double vector_magitude_u = 0.0, vector_sum_u = 0.0;
	double vector_magitude_u = 0.0, vector_magitude_v = 0.0, vector_sum_u = 0.0,
			vector_sum_v = 0.0;

	for (unsigned int i = 0; i < v.size(); i++) {
		vector_sum_u = vector_sum_u + u[i] * u[i];
		vector_sum_v = vector_sum_v + v[i] * v[i];
	}

	vector_magitude_u = sqrt(vector_sum_u);
	vector_magitude_v = sqrt(vector_sum_v);

	double magnitude_prod = vector_magitude_u * vector_magitude_v;
	double param = dot_prod / magnitude_prod;

	angle_res = acos (param) * 180.0 / PI;

	return angle_res;
}


std::vector<double> angle_to_vector(double angle){
	std::vector<double> u(2);
	u[0] = cos(angle * PI /180);
	u[1]= sin(angle * PI /180);
	return u;
}

std::vector<double> radian_to_vector(double radian){
	std::vector<double> u(2);
	u[0] = cos(radian);
	u[1]= sin(radian);
	return u;
}
