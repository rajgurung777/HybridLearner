/*
 * vector_operations.cpp
 *
 *  Created on: 30-Nov-2015
 *      Author: amit
 */

#include "vector_operations.h"

#include <math.h>

// converts the vector v into a unit vector
std::vector<double> normalize_vector(std::vector<double> v) {
	std::vector<double> normal_vector(v.size());

	double vector_magitude = 0, vector_sum = 0.0;

	for (unsigned int i = 0; i < v.size(); i++) {
		vector_sum = vector_sum + v[i] * v[i];
	}
	vector_magitude = sqrt(vector_sum);
	if (vector_magitude != 0) {
		for (unsigned int i = 0; i < v.size(); i++) {
			normal_vector[i] = v[i] / vector_magitude;
		}
	}
	return normal_vector;
}

//returns a vector which is the bisector of vector u and v
std::vector<double> bisect_vector(std::vector<double> u,
		std::vector<double> v) {
	std::vector<double> z(u.size());

	assert(u.size() == v.size()); //checking if u and v are of same dimension
	for (unsigned int i = 0; i < u.size(); i++) {
		z[i] = (u[i] + v[i]) / 2;
	}
	return z;
}

//Returns true if every elements of the two vectors u & v are equal otherwise false
bool isEqual_Vectors(std::vector<double> u, std::vector<double> v) {
	bool isEqual = true;
	assert(u.size() == v.size()); //checking if u and v are of same dimension
	for (unsigned int i = 0; i < u.size(); i++) {
		if (u[i] != v[i]) {
			isEqual = false;
		}
	}
	return isEqual;
}

math::matrix<double> matrix_vertices(
		std::set<std::pair<double, double> > set_vertices) {

	math::matrix<double> my_vertices(set_vertices.size(), 2); //set of 2d vertices
	typedef std::set<std::pair<double, double> > pts;
	int count = 0;
	for (pts::iterator it = set_vertices.begin(); it != set_vertices.end();
			it++) {
		my_vertices(count, 0) = (*it).first;
		my_vertices(count, 1) = (*it).second;
		count++;
	}
	return my_vertices;
}

math::matrix<double> sort_vertices(
		std::set<std::pair<double, double> > set_vertices) {

	math::matrix<double> my_vertices;
	int number_of_vertices = set_vertices.size();
	my_vertices = matrix_vertices(set_vertices); //set of vertices converted into vertices in matrix-form

	float mean_x, mean_y, sum_x = 0.0, sum_y = 0.0;
	for (int i1 = 0; i1 < (int) my_vertices.size1(); i1++) {
		sum_x = sum_x + my_vertices(i1, 0);
		sum_y = sum_y + my_vertices(i1, 1);
	}
	mean_x = sum_x / my_vertices.size1();
	mean_y = sum_y / my_vertices.size2();
	for (int i = 0; i < (int) my_vertices.size1() - 1; i++) {
		for (int i2 = i; i2 < (int) my_vertices.size1(); i2++) {
			float Point_A = atan2((my_vertices(i, 1) - mean_y),
					(my_vertices(i, 0) - mean_x));
			float Point_B = atan2((my_vertices(i2, 1) - mean_y),
					(my_vertices(i2, 0) - mean_x));
			if (Point_A > Point_B) {
				//Swapping X co-ordinate value
				float temp = my_vertices(i, 0);
				my_vertices(i, 0) = my_vertices(i2, 0);
				my_vertices(i2, 0) = temp;

				//Swapping Y co-ordinate value
				temp = my_vertices(i, 1);
				my_vertices(i, 1) = my_vertices(i2, 1);
				my_vertices(i2, 1) = temp;
			}
		}
	}
	//Repeating the first Vertex to close the figure
	my_vertices.resize(number_of_vertices + 1, 2, true); //2 being the 2d vertices
	my_vertices(number_of_vertices, 0) = my_vertices(0, 0);
	my_vertices(number_of_vertices, 1) = my_vertices(0, 1);

	return my_vertices;
}



// Concatenating the second vector with the first one.
std::vector<double> vector_join(std::vector<double> v1,
		std::vector<double> v2) {

	std::vector<double> result;
	result = v1;
	unsigned int tot_size;
	tot_size = result.size() + v2.size();
	result.resize(tot_size);

	for (unsigned int i = v1.size(), j = 0; j < v2.size(); i++, j++)
		result[i] = v2[j];

	return result;
}

// Elementwise vector addition
std::vector<double> vector_add(std::vector<double> v1,
		std::vector<double> v2) {

	std::vector<double> result;
	assert(v1.size() == v2.size());
	result.resize(v2.size());

	for (unsigned int i = 0; i < v2.size(); i++)
		result[i] = v1[i] + v2[i];

	return result;
}

//d(p,q) = sqrt((p1 - q1)^2 + (p2 - q2)^2 + (p3 - q3)^2
double euclidean_distance(std::vector<double> p, std::vector<double> q){
	double dist=0.0, diff=0.0;

	assert(p.size() == q.size());	//only when the dimensions are equal

	for (unsigned int i=0; i< p.size(); i++) {
		diff = p[i] - q[i];
		dist += diff * diff;
	}

	return sqrt(dist);
}
