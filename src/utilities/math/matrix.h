/*
 * matrix.h
 *
 *  Created on: 07-Oct-2021
 *      Author: amit
 *
 * This class is taken from the tool XSpeed [http://xspeed.nitmeghalaya.in/] but it has been modified/filtered throughly for the need of this tool.
 */

#ifndef UTILITIES_MATH_MATRIX_H_
#define UTILITIES_MATH_MATRIX_H_



#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "expm.h"

namespace math {

template<typename scalar_type> class matrix: public boost::numeric::ublas::matrix<
		scalar_type> {
public:
	typedef boost::numeric::ublas::matrix<scalar_type> ublas_matrix_impl;
	typedef typename boost::numeric::ublas::matrix<scalar_type>::size_type size_type;
	typedef boost::numeric::ublas::vector<scalar_type> ublas_vector_impl;
	typedef typename boost::numeric::ublas::matrix<scalar_type>::array_type array_type;

	matrix();
	matrix(size_type r, size_type c);
	matrix(size_type r, size_type c, array_type data);
	/**
	 * This creates a matrix with the given dimension and assigns init_val to
	 * every member of the matrix.
	 */
	matrix(size_type r, size_type c, const scalar_type init_val);
	void matrix_exponentiation(math::matrix<scalar_type>& res, double time_tau) const;
	void matrix_exponentiation(math::matrix<scalar_type>& res) const;
	void multiply(matrix& A, matrix& res);

	//any matrix object can call this function to create another identity matrix
	void matrix_Identity(int dimension, math::matrix<scalar_type>& newIdentityMatrix);

	//calling matrix as minuend, passed as subtrahend and result as difference (minuend − subtrahend =	difference)
	void minus(matrix& B, matrix& res);
	void mult_vector(std::vector<scalar_type> v, std::vector<scalar_type> &res) const;
	// multiplies each entry of the matrix by c
	void scalar_multiply(double c);
	void transpose(matrix& re );
	/*
	 * Appends a column vector to the end of the calling matrix and returns the new resized matrix
	 */
//	void addColumn(std::vector <scalar_type> columnVector, math::matrix<scalar_type>& resized_matrix);
	scalar_type norm_inf();

	scalar_type norm_max();

	void matrix_copy(math::matrix<scalar_type>& destination);
	void matrix_join(math::matrix<scalar_type> mat2,
			math::matrix<scalar_type>& joined_matrix);
	//void matrix_Identity(math::matrix<scalar_type>& newIdentityMatrix);
	/*
	 * inverse of a matrix : Returns True if Inverse Exists otherwise returns False
	 */
	bool inverse(math::matrix<scalar_type>& res);
	/* Returns the boolean status of invertibility */
	bool isInvertible();
	/**
	 * Returns true if identity, false othwerwise
	 */
	bool isIdentity();

	/*private:
	 ublas_matrix_impl my_matrix;*/

	// overloaded operators
	bool operator==(const math::matrix<scalar_type>& M);

	/** Overloaded << operator */

	template<class U>
	friend std::ostream& operator << (std::ostream &os, const math::matrix<U> &t);

};

#include "matrix.cpp"

} // end of math namespace


#endif /* UTILITIES_MATH_MATRIX_H_ */
