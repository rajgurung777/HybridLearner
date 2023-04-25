/*
 *	This file is taken from XSpeed tool

 * vector_operations.h
 *
 *  Created on: 30-Nov-2015
 *      Author: amit
 */

#ifndef VECTOR_OPERATIONS_H_
#define VECTOR_OPERATIONS_H_

#include <vector>
#include <assert.h>
#include <set>
#include <utility>

#include "math/matrix.h"

// concatenates the second vector with the second one.
std::vector<double> vector_join(std::vector<double> v1, std::vector<double> v2);

// Elementwise addition of two vectors
std::vector<double> vector_add(std::vector<double> v1, std::vector<double> v2);


// converts the vector v into a unit vector
std::vector<double> normalize_vector(std::vector<double> v);

//returns a vector which is the bisector of vector u and v
std::vector<double> bisect_vector(std::vector<double> u, std::vector<double> v);

math::matrix<double> matrix_vertices(std::set<std::pair<double, double> > set_vertices);

//sorting the 2d vertices
math::matrix<double> sort_vertices(std::set<std::pair<double, double> > set_vertices);

bool isEqual_Vectors(std::vector<double> u, std::vector<double> v);

/*
 * Euclidean distance: between two point p and q of three dimensions is
 * 		d(p,q) = sqrt((p1 - q1)^2 + (p2 - q2)^2 + (p3 - q3)^2
 */
double euclidean_distance(std::vector<double> u, std::vector<double> v);

#endif /* VECTOR_OPERATIONS_H_ */
