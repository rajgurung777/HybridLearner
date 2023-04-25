/*
 * data_structures.h
 *
 *  Created on: 26-Nov-2021
 *      Author: amit
 */

#ifndef MODELPARSER_DATA_STRUCTURES_H_
#define MODELPARSER_DATA_STRUCTURES_H_

#include "../utilities/math/matrix.h"

// Guard of the form Ax <= b. where A is the coeffMatrix and b is the columnVector
struct linear_guard{
	math::matrix<double> coeffMatrix;
	std::vector<double> columnVector;
};






//Converts a hyperplane guard into halfspace in the opposite direction w.r.t. a given point x
//where is guard is of the form Mx <= Bounds
void Hyperplane_to_Halfspace(math::matrix<double>& M, std::vector<double>& Bounds, std::vector<double> x) {

	for(unsigned int i = 0; i<M.size1()-1; i++){
		int count = 0;
		double sum1 = 0, sum2 = 0;
		for(unsigned int j=0; j<M.size2(); j++){
			if(abs(M(i,j)) != abs(M(i+1,j))){
				count++; // if count = 0, i^th row is half-space otherwise i^th and i+1^th row is line or region
			}
			sum1 = sum1 + M(i,j) * x[j];
			sum2 = sum2 + M(i+1,j) * x[j];
		}
		if(count == 0 && (abs(Bounds[i]) == abs(Bounds[i+1])) && (Bounds[i] != Bounds[i+1] || (Bounds[i] == 0 && Bounds[i+1] == 0))){ // start line to half-space

			//if(sum1 <= Bounds[i]){
			if(sum1 >= Bounds[i]){
				for(unsigned int j=0; j<M.size2(); j++){
					if(M(i,j) != 0){
						M(i,j) = M(i,j) * (-1);
					}
				}
				Bounds[i] = Bounds[i] * (-1);
			}
			//else if(sum2 <= Bounds[i+1]){
			else if(sum2 >= Bounds[i+1]){
				for(unsigned int j=0; j<M.size2(); j++){
					if(M(i+1,j) != 0){
						M(i+1,j) = M(i+1,j) * (-1);
					}
				}
				Bounds[i+1] = Bounds[i+1] * (-1);
			}
			i = i+1;
		}// end line to half-space
	}
	std::cout<<"converted to Halfspace"<< std::endl;
}

//Convert linear hyperplane guard into halfspace guard for the same location/side with respect to the given point x
void Hyperplane_to_Halfspace_guard_sameSide(linear_guard g, linear_guard &g1, std::vector<double> x) {
	math::matrix<double> M = g.coeffMatrix;
	std::vector<double> Bounds = g.columnVector;

	for(unsigned int i = 0; i<M.size1()-1; i++){
		int count = 0;
		double sum1 = 0, sum2 = 0;
		for(unsigned int j=0; j<M.size2(); j++){
			if(abs(M(i,j)) != abs(M(i+1,j))){
				count++; // if count = 0, i^th row is half-space otherwise i^th and i+1^th row is line or region
			}
			sum1 = sum1 + M(i,j) * x[j];
			sum2 = sum2 + M(i+1,j) * x[j];
		}
		if(count == 0 && (abs(Bounds[i]) == abs(Bounds[i+1])) && (Bounds[i] != Bounds[i+1] || (Bounds[i] == 0 && Bounds[i+1] == 0))) { // start line to half-space


			if(sum1 >= Bounds[i]) {	//Convert guard to halfspace to the same side w.r.t. point x
				for(unsigned int j=0; j<M.size2(); j++) {
					if(M(i,j) != 0){
						M(i,j) = M(i,j) * (-1);
					}
				}
				Bounds[i] = Bounds[i] * (-1);
			} else if(sum2 >= Bounds[i+1]) {
				for(unsigned int j=0; j<M.size2(); j++){
					if(M(i+1,j) != 0){
						M(i+1,j) = M(i+1,j) * (-1);
					}
				}
				Bounds[i+1] = Bounds[i+1] * (-1);
			}
			i = i+1;
		} // end line to half-space
	}
	g1.coeffMatrix = M;
	g1.columnVector = Bounds;
	std::cout << "converted to Halfspace"<< std::endl;
}



//Convert linear hyperplane guard into halfspace guard for the same location/side with respect to the given point x
void Hyperplane_to_Halfspace_guard_oppositeSide(linear_guard g, linear_guard &g1, std::vector<double> x) {
	math::matrix<double> M = g.coeffMatrix;
	std::vector<double> Bounds = g.columnVector;

	for(unsigned int i = 0; i<M.size1()-1; i++){
		int count = 0;
		double sum1 = 0, sum2 = 0;
		for(unsigned int j=0; j<M.size2(); j++){
			if(abs(M(i,j)) != abs(M(i+1,j))){
				count++; // if count = 0, i^th row is half-space otherwise i^th and i+1^th row is line or region
			}
			sum1 = sum1 + M(i,j) * x[j];
			sum2 = sum2 + M(i+1,j) * x[j];
		}
		if(count == 0 && (abs(Bounds[i]) == abs(Bounds[i+1])) && (Bounds[i] != Bounds[i+1] || (Bounds[i] == 0 && Bounds[i+1] == 0))) { // start line to half-space


			if(sum1 <= Bounds[i]) {	//Convert guard to halfspace to the same side w.r.t. point x
				for(unsigned int j=0; j<M.size2(); j++) {
					if(M(i,j) != 0){
						M(i,j) = M(i,j) * (-1);
					}
				}
				Bounds[i] = Bounds[i] * (-1);
			} else if(sum2 <= Bounds[i+1]) {
				for(unsigned int j=0; j<M.size2(); j++){
					if(M(i+1,j) != 0){
						M(i+1,j) = M(i+1,j) * (-1);
					}
				}
				Bounds[i+1] = Bounds[i+1] * (-1);
			}
			i = i+1;
		} // end line to half-space
	}
	g1.coeffMatrix = M;
	g1.columnVector = Bounds;
	std::cout << "converted to Halfspace"<< std::endl;

}



/*
Testing the above functions: which is not in use now
std::vector<double> b(2);
std::vector<double> x(2);
unsigned int row = 2, col = 2;
math::matrix<double> m1(row, col);
//	m1(0, 0) = -1;	m1(0, 1) = 1;
//	m1(1, 0) = 1;	m1(1, 1) = -1;

m1(0, 0) = 0;	m1(0, 1) = -1;
m1(1, 0) = 0;	m1(1, 1) = 1;


b[0] = 0;	//x1-x2 == 0
b[1] = 0;
cout << "Matrix M: " ;
cout << m1 ;

x[0] = 5;	// point x(6,2)
x[1] = -5;

//	Hyperplane_to_Halfspace(m1, b, x);
//	cout << "Matrix M: " ;
//	cout << m1 ;
//	cout <<"\n b[0]=" << b[0] <<"   b[1]=" << b[1] << endl;


linear_guard line_guard, this_loc_guard, next_loc_guard;
line_guard.coeffMatrix = m1;
line_guard.columnVector = b;

Hyperplane_to_Halfspace_guard_sameSide(line_guard, this_loc_guard, x);

Hyperplane_to_Halfspace_guard_oppositeSide(line_guard,  next_loc_guard, x);

cout << "Matrix this side M: " ;
cout << this_loc_guard.coeffMatrix ;
cout <<"\n b[0]=" << this_loc_guard.columnVector[0] <<"   b[1]=" << this_loc_guard.columnVector[1] << endl;


cout << "Matrix opposite side M: " ;
cout << next_loc_guard.coeffMatrix ;
cout <<"\n b[0]=" << next_loc_guard.columnVector[0] <<"   b[1]=" << next_loc_guard.columnVector[1] << endl;

//return 0;
*/





#endif /* MODELPARSER_DATA_STRUCTURES_H_ */
