/*
 * polytope.h
 *
 *  Created on: 7-Oct-2021
 *      Author: amit
 */

#ifndef UTILITIES_POLYTOPE_POLYTOPE_H_
#define UTILITIES_POLYTOPE_POLYTOPE_H_


#include <list>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <set>
#include <utility>
#include <boost/tokenizer.hpp>


#include "../../hybridautomata/variable_to_index_mapping.h"
#include "../math/matrix.h"
#include "../math/basic_functions.h"

#include "../vector_operations.h"
#include "../math/2dGeometry.h"
#include <fstream>
#include "stringParser.h"
#include "../../commandLineParser/user_inputs.h"


//#include "math/lp_solver_ourSimplex/simplex.h"
//#include "core/math/lpSolver/lpSolver.h"

using namespace std;

/* This class is taken from the tool XSpeed [http://xspeed.nitmeghalaya.in/] but it has been modified/filtered throughly for the need of this tool.
 *
 * If a polytope is represented using intersections of halfspaces then it is of the form Ax<=b
 * where A is the coefficients Matrix of the variables 'x' and b is the columnVector
 *
 * coeffMatrix : All facets of the Polytope in Matrix form (i.e. the coefficients of the variables).
 * number_facets : Number of faces of the defined polytope.
 * dimension :  Number of variables of the system.
 * columnVector :	The values b for each facet.
 * InEqualitySign :	The in equalities sign of the bound values 'b'. Possible values are
 * 					0 :	for  Ax = b (b Equals to)
 * 					1 :	for  Ax <= b (b is Greater Than or Equals to)
 * 					2 :	for  Ax >= b (b is Less Than or Equals to)
 *
 * Removed this feature: Also include the function to compute Support Function of the defined polytope in any given direction.
 *
 * Also include the function to return the Dimension of the defined polytope.
 */

class polytope: public var_mapping {


private:
	math::matrix<double> coeffMatrix;
	std::vector<double> columnVector;
	int InEqualitySign;
	unsigned int number_facets;
	unsigned int system_dimension;
	bool IsEmpty;
	bool IsUniverse;

public:
	typedef boost::shared_ptr<polytope> ptr;
	typedef boost::shared_ptr<const polytope> const_ptr;
	polytope();
	polytope(bool empty);
	polytope(math::matrix<double> coeffMatrix, std::vector<double> columnVector,
			int InEqualitySign);
	void setIsEmpty(bool empty);
	bool getIsEmpty() const;
	void setIsUniverse(bool universe);
	bool getIsUniverse() const;
	/* Returns true if the constraints make it bounded */
	bool isBounded() const;

	void setPolytope(math::matrix<double> coeffMatrix,
			std::vector<double> columnVector, int inEqualitySign);
	/*
	 * Adds one constraint to the existing polytope by adding the
	 * coefficient constraint with the bound value to the existing list.
	 */
	void setMoreConstraints(std::vector<double> coeff_constraint,double bound_value);

	/*
	 * Adds one or more constraints to the existing polytope by adding the
	 * coefficient_constraints with the bound_values to the existing list.
	 */
	void setMoreConstraints(math::matrix<double> coeff_constraints,std::vector<double> bound_values);

	const math::matrix<double>& getCoeffMatrix() const;
	void setCoeffMatrix(const math::matrix<double> coeffMatrix);
	void setColumnVector(const std::vector<double> columnVector);

	int getInEqualitySign() const;
	void setInEqualitySign(int inEqualitySign);
	std::vector<double> getColumnVector() const;

	unsigned int getSystemDimension() const; //returns the number of variables of the polytopes.
	void setSystemDimension(unsigned int systemDimension);
	unsigned int getNumberFacets() const;
	void setNumberFacets(unsigned int numberFacets);


	/**
	 * Computes the distance of a point from the polytope.
	 * If the point is inside the polytope, a 0 distance
	 * is returned. Otherwise, the distance is the sum of
	 * distances of the point to all the faces.
	 */
	double point_distance(std::vector<double> v) const;


	//Prints the coefficient matrix and vector
	void printPoly() const;

};

/**
 * Creates a pair of <loc_id, poly> from the user given bad state string
 * which is of the form "loc=id & exp1 & exp2 & ... & expN" where each expN is of the form x>=1 or x<=2
 *  now expN can also be of the form 2*x + 3*y >=1 or  2*x + 3*y <=1
 */
void string_to_poly(const std::string& bad_state, std::pair<int, polytope::ptr>& f_set);


/*
 * Reads the format "v1 >=2 & v1 <= 3 & v2 >=2 & v2 <=3"
 * This function reads the string bad_state without the "location=id" term in the string
 * Correct format is "variableName operator double"
 */
void string_to_polytope(const std::string bad_state, polytope::ptr &unsafe_set);


void string_to_polytope_withTimeBound(const std::string bad_state, polytope::ptr &unsafe_set, double &gt_lower, double &gt_upper);

/*
 * Reads the list of strings (from user_inputs and returns a polytope of the Input set
 * we take input as the whole class of user_inputs because we want to use the selected model
 * to create variable mapping of the polytope so that variable index can be identified to read
 * the format "v1>=2 & v1<=3 & v2>=2 & v2<=3 & x0=7 & x1==9"
 * = and == are the same symbol which generate two constraints of the form var<=Value & var>=Value
 *
 */
//void string_list_to_polytope(user_inputs::ptr &user, polytope::ptr &input_set);
void string_list_to_polytope(std::list<std::string> str_args, polytope::ptr &p);

#endif /* UTILITIES_POLYTOPE_POLYTOPE_H_ */
