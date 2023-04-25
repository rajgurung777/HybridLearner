/*
 * polytope.cpp
 *
 *  Created on: 7-Oct-2021
 *      Author: amit
 */

#include "polytope.h"

using namespace std;

/*
 * to create an empty polytope call the polytope(bool true) constructor
 * to make a polytope non-empty explicit call to setIsEmpty(false) is to be invoked, even if constraints are set to the
 * polytope it will not be converted into non-empty polytope
 * Universe polytope is created by default and is unbounded by default, whenever any constraints are set it automatically
 * becomes bounded universe polytope
 */

polytope::polytope() {

	// The default polytope inequality sign is <=
	InEqualitySign = 1;
	number_facets = 0;
	system_dimension = 0;
	this->IsUniverse = true; //It is a Universe polytope
	this->IsEmpty = false;
}
polytope::polytope(bool empty) {

	//polytope();
	if(empty) // make this an empty polytope
	{
		this->IsEmpty = true;
		this->IsUniverse = false;
	}
	system_dimension = 0;
	InEqualitySign = 1;
	number_facets = 0;
	system_dimension = 0;
}

polytope::polytope(math::matrix<double> coeffMatrix,
		std::vector<double> columnVector, int InEqualitySign) {

	this->number_facets = coeffMatrix.size1();
	this->system_dimension = coeffMatrix.size2();
	this->coeffMatrix = coeffMatrix;
	this->columnVector.resize(this->number_facets);
	this->columnVector = columnVector;
	this->InEqualitySign = InEqualitySign;
	//Since constraints are set So it is not empty and is Universe but 'bounded'
	this->setIsEmpty(false); //Not an empty Polytope
	this->setIsUniverse(false); //Not a universe Polytope and is now a 'Bounded' polytope
	this->IsUniverse = false; // Assuming that the constraints passed as matrix, vector are meaningful
	this->IsEmpty = false; // assuming that the constraints are not unsatiafiable.

}

void polytope::setPolytope(math::matrix<double> coeffMatrix,
	std::vector<double> columnVector, int inEqualitySign) {
	this->setNumberFacets(coeffMatrix.size1());
	this->setSystemDimension(coeffMatrix.size2());
	this->coeffMatrix = coeffMatrix;
	this->columnVector.resize(this->number_facets);
	this->columnVector = columnVector;

	this->InEqualitySign = inEqualitySign;

	this->setIsUniverse(false); //Not a Universe Polytope and is now 'Bounded' polytope

}

void polytope::setIsEmpty(bool empty) {
	this->IsEmpty = empty;
}
bool polytope::getIsEmpty() const {
	return this->IsEmpty;
}
void polytope::setIsUniverse(bool universe) {
	this->IsUniverse = universe;
}
bool polytope::getIsUniverse() const {
	return this->IsUniverse;
}
bool polytope::isBounded() const
{
	if(coeffMatrix.size1()< system_dimension+1)
		return false;
	else
		return true;
	/* Note that the above is an incomplete simple check of boundedness.
	 * A true algorithm to check for boundeded is to be implemented. later.
	 */
}

const math::matrix<double>& polytope::getCoeffMatrix() const {
	return this->coeffMatrix;
}
void polytope::setCoeffMatrix(const math::matrix<double> coeffMatrix) {

	this->setNumberFacets(coeffMatrix.size1());
	this->setSystemDimension(coeffMatrix.size2());

	this->coeffMatrix = coeffMatrix;
	this->setIsUniverse(false); //Not a Universe Polytope and is now 'Bounded' polytope
}
void polytope::setMoreConstraints(std::vector<double> coeff_constraint,
		double bound_value) {
	this->setSystemDimension(coeff_constraint.size());	//or can be obtained from the map_size()
	//this->setSystemDimension(this->map_size());
	this->setIsUniverse(false); //Not a Universe Polytope and is now 'Bounded' polytope
	this->InEqualitySign = 1; // assuming that always less than ineq cons is added.
	// todo: make the impl to accept ineq sign as param or
	// change the func name to add_lt_inequalityCons().

	unsigned int row_size, col_size;
	row_size = this->getCoeffMatrix().size1();
	col_size = this->getCoeffMatrix().size2(); //dimension of the polytope
	if(col_size == 0) // The poly is currently empty
		col_size = coeff_constraint.size();
	else
		assert(col_size == coeff_constraint.size());
	this->coeffMatrix.resize(row_size + 1, col_size, true); //adding one more constraint
	this->columnVector.resize(row_size + 1); //adding one more constraint's bound value
	for (unsigned int i = 0; i < col_size; i++) {
		this->coeffMatrix(row_size, i) = coeff_constraint[i];
	}
	this->columnVector[row_size] = bound_value;
}

void polytope::setMoreConstraints(math::matrix<double> coeff_constraints,
		std::vector<double> bound_values) {
	// check if non-empty matrix passed. if empty, then return by doing nothing
	if(coeff_constraints.size1()==0 || coeff_constraints.size2()==0)
		return;

	this->setSystemDimension(this->map_size());
	this->setIsUniverse(false); //Not a Universe Polytope and is now 'Bounded' polytope

	unsigned int row_size, dim_size, rows_new;
	row_size = this->getCoeffMatrix().size1();
	dim_size = this->getCoeffMatrix().size2(); //dimension of the polytope
	rows_new = coeff_constraints.size1();

	assert(dim_size == coeff_constraints.size2());

	unsigned int new_total_rows = row_size + rows_new;

	this->coeffMatrix.resize(new_total_rows, dim_size, true); //adding more constraints
	this->columnVector.resize(new_total_rows); //adding more constraint's bound values

	for (unsigned int i = 0; i < rows_new; i++) {
		for (unsigned int j = 0; j < dim_size; j++) {
			this->coeffMatrix(row_size + i, j) = coeff_constraints(i, j);
		}
		this->columnVector[row_size + i] = bound_values[i];
	}

}

int polytope::getInEqualitySign() const {
	return InEqualitySign;
}
void polytope::setInEqualitySign(int inEqualitySign) {
	InEqualitySign = inEqualitySign;
}
void polytope::setColumnVector(const std::vector<double> columnVector) {
	this->columnVector.resize(this->number_facets);
	this->columnVector = columnVector;
	this->setNumberFacets(columnVector.size());
}
std::vector<double> polytope::getColumnVector() const {
	return columnVector;
}

unsigned int polytope::getNumberFacets() const {
	return number_facets;
}

void polytope::setNumberFacets(unsigned int numberFacets) {
	number_facets = numberFacets;
}

unsigned int polytope::getSystemDimension() const {
	return system_dimension;
}

void polytope::setSystemDimension(unsigned int systemDimension) {
	system_dimension = systemDimension;
}


double polytope::point_distance(std::vector<double> v) const{
	if(this->IsUniverse)
		return 0;

	if(this->IsEmpty){
		std::cout << "distance of a point from an empty polytope asked\n";
		return 0;
	}

	math::matrix<double> C = getCoeffMatrix();
	std::vector<double> b = getColumnVector();

	assert(v.size() == C.size2());
	assert(getInEqualitySign()==1);

	double distance = 0;
	double facet_distance = 0;
	double coef_sq_sum = 0;

	for(unsigned int i=0;i<C.size1();i++){
		for(unsigned int j=0;j<C.size2();j++){
			facet_distance += v[j]*C(i,j);
			coef_sq_sum += C(i,j)*C(i,j);
		}
		facet_distance -=b[i];

		if(facet_distance > 1e-10){
			distance += facet_distance/coef_sq_sum;
		}
		coef_sq_sum = 0;
		facet_distance = 0;
	}
	return distance*distance; // square of the distance is returned.

}

void polytope::printPoly() const{

	std::cout<<this->coeffMatrix;
	std::cout<<"\nVector\n";
	for(unsigned int j=0;j<columnVector.size();j++)
		std::cout << this->columnVector[j] << "    " ;
	std::cout << "\n";
}




/*
 * Reads the format " v1 >=2 & v1 <= 3 & v2 >=2 & v2 <=3"
 * Also, should be able to now read linear constrains of the format " 1*x + 2*y >=10 & 1*x + -1*y <=20"
 */
void string_to_poly(const std::string& bad_state, std::pair<int, polytope::ptr>& f_set)
{
	std::list<std::string> all_args;

	//polytope::ptr p = polytope::ptr(new polytope());
	polytope::ptr p = polytope::ptr(new polytope());
	p->setIsEmpty(false);
	p->setIsUniverse(true);

	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("&");
	tokenizer tokens(bad_state, sep);

	for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter) {
		all_args.push_back((std::string) *tok_iter);
	}

	std::string varname, tokString;
	tokenizer::iterator tok_iter;
	unsigned int i, init_locId = 1; // initial loc Id set to 1 by default

	for(std::list<std::string>::iterator iter = all_args.begin(); iter!=all_args.end();iter++) {
		tokString = *iter;
		if (tokString.find("<=")!=std::string::npos ) { // less than equal to constraint
			sep = boost::char_separator<char>("<=");
			tokens = tokenizer(tokString, sep);
			tok_iter = tokens.begin(); // tok_iter contains the lhs of a linear exp
			std::list<std::pair<double, std::string> > coeff_var_pairs = linexp_parser(*tok_iter);
			std::vector<double> cons(p->map_size(), 0);
			for(std::list<std::pair<double, std::string> >::iterator it = coeff_var_pairs.begin(); it!=coeff_var_pairs.end();++it){
				double coeff = (*it).first;
				varname = (*it).second;
 				i = p->get_index(varname);
				cons[i] = coeff;
			}
			tok_iter++;
			double bound = std::atof((*tok_iter).c_str());
			p->setMoreConstraints(cons,bound);
		} else if(tokString.find(">=")!=std::string::npos){ // greater than equal to constraint
			sep = boost::char_separator<char>(">=");
			tokens = tokenizer(tokString,sep);
			tok_iter = tokens.begin();
			std::list<std::pair<double, std::string> > coeff_var_pairs = linexp_parser(*tok_iter);
			std::vector<double> cons(p->map_size(), 0);
			for(std::list<std::pair<double, std::string> >::iterator it = coeff_var_pairs.begin(); it!=coeff_var_pairs.end();++it){
				double coeff = (*it).first;
				varname = (*it).second;
				i = p->get_index(varname);
				cons[i] = -coeff;
			}
			tok_iter++;
			double bound = std::atof((*tok_iter).c_str());
			p->setMoreConstraints(cons,-bound);
		} else if(tokString.find("=")!=std::string::npos){
			/* check if setting location id*/

			if(tokString.find("loc")!=std::string::npos){

				boost::char_separator<char> sep1("=; ");
				tokens = tokenizer(tokString, sep1);
				tok_iter = tokens.begin();
				assert(*tok_iter == "loc");

				tok_iter++;
				init_locId = std::atoi((*tok_iter).c_str());
				continue;
			}

			/*---end of loc id setting -----*/

			sep = boost::char_separator<char>("=");
			tokens = tokenizer(tokString,sep);
			tok_iter = tokens.begin(); // tok_iter contains the lhs of a linear exp
			std::list<std::pair<double, std::string> > coeff_var_pairs = linexp_parser(*tok_iter);
			std::vector<double> cons(p->map_size(), 0);
			for(std::list<std::pair<double, std::string> >::iterator it = coeff_var_pairs.begin(); it!=coeff_var_pairs.end();++it){
				double coeff = (*it).first;
				varname = (*it).second;
 				i = p->get_index(varname);	//since var_mapping is STATIC data-type so it can retain the values. But make sure to call automata creation before this
				cons[i] = coeff;
			}
			tok_iter++;
			double bound = std::atof((*tok_iter).c_str());
			p->setMoreConstraints(cons,bound);
			//-----------------------

			sep = boost::char_separator<char>(">=");
			tokens = tokenizer(tokString,sep);
			tok_iter = tokens.begin();
			coeff_var_pairs = linexp_parser(*tok_iter);
			std::vector<double> cons1(p->map_size(), 0);
			for(std::list<std::pair<double, std::string> >::iterator it = coeff_var_pairs.begin(); it!=coeff_var_pairs.end();++it){
				double coeff = (*it).first;
				varname = (*it).second;
				i = p->get_index(varname);
				cons1[i] = -coeff;
			}
			tok_iter++;
			bound = std::atof((*tok_iter).c_str());
			p->setMoreConstraints(cons1,-bound);
		} else{
			std::cout << "Error in string to poly conversion\n";
			throw std::runtime_error("forbidden state string improper\n");
		}
	}
	f_set.first = init_locId;
	f_set.second=p;
};



void string_to_polytope(const std::string bad_state, polytope::ptr &unsafe_set) {

	std::list<std::string> all_args;
	polytope::ptr p = polytope::ptr(new polytope());
	p->setIsEmpty(false);
	p->setIsUniverse(true);

	//p->setIsUniverse(false); //Not a universe Polytope
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("& ");
	tokenizer tokens(bad_state, sep);

	for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter) {
		all_args.push_back((std::string) *tok_iter);
	}

	/* get the location number from the first token */
	/*std::string locString = *all_args.begin();
	all_args.pop_front();
	boost::char_separator<char> sep1("= ");
	tokens = tokenizer(locString, sep1);

	tokenizer::iterator tok_iter = tokens.begin();

	std::string tokString = *tok_iter;
	if(tokString.compare("loc")!=0 && tokString.compare("Loc")!=0 && tokString.compare("LOC")!=0 ){
		throw std::runtime_error("forbidden state string improper: start with loc=id & ...\n use loc=-1 for any location\n");
	}
	tok_iter++;
	f_set.first = std::atoi((*tok_iter).c_str());
	*/


	std::string varname;
	std::string tokString;
	tokenizer::iterator tok_iter;
	unsigned int i;
	for(std::list<std::string>::iterator iter = all_args.begin(); iter!=all_args.end();iter++) {
		tokString = *iter;
		if (tokString.find("<=")!=std::string::npos ) { // less than equal to constraint
			sep = boost::char_separator<char>("<=");
			tokens = tokenizer(tokString, sep);
			tok_iter = tokens.begin();
			varname = *tok_iter;
			//cout <<"<= varName = " << varname <<endl;
			if ((varname == "gt") || (varname == "lt"))	//skip the lt and gt variable
				continue;
			tok_iter++;
			i = p->get_index(varname);
			std::vector<double> cons(p->map_size(),0);
			cons[i] = 1;
			double bound = std::atof((*tok_iter).c_str());
			p->setMoreConstraints(cons,bound);
		} else if(tokString.find(">=")!=std::string::npos) { // greater than equal to constraint
			sep = boost::char_separator<char>(">=");
			tokens = tokenizer(tokString,sep);
			tok_iter = tokens.begin();
			varname = *tok_iter;
			//cout <<">= varName = " << varname <<endl;
			if ((varname == "gt") || (varname == "lt"))	//skip the lt and gt variable
				continue;
			tok_iter++;
			i = p->get_index(varname);
			std::vector<double> cons(p->map_size(),0);
			cons[i] = -1;
			double bound = std::atof((*tok_iter).c_str());
			p->setMoreConstraints(cons,-bound);
		} else {
			throw std::runtime_error("forbidden state string improper: <= or >= constraint expected\n");
		}
	}
//	cout<<"constraints = "<<p->getCoeffMatrix()<<"\n";
//	cout << "forbidden location id: " << f_set.first << std::endl;
//	for (int i=0;i<p->getColumnVector().size();i++)
//		cout<<p->getColumnVector()[i]<<"\t";
//	cout<<endl;

	unsafe_set = p;
};


void string_to_polytope_withTimeBound(const std::string bad_state, polytope::ptr &unsafe_set, double &gt_lower, double &gt_upper) {

	std::list<std::string> all_args;
	polytope::ptr p = polytope::ptr(new polytope());
	p->setIsEmpty(false);
	p->setIsUniverse(true);

	//p->setIsUniverse(false); //Not a universe Polytope
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("& ");
	tokenizer tokens(bad_state, sep);

	for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter) {
		all_args.push_back((std::string) *tok_iter);
	}

	/* get the location number from the first token */
	/*std::string locString = *all_args.begin();
	all_args.pop_front();
	boost::char_separator<char> sep1("= ");
	tokens = tokenizer(locString, sep1);

	tokenizer::iterator tok_iter = tokens.begin();

	std::string tokString = *tok_iter;
	if(tokString.compare("loc")!=0 && tokString.compare("Loc")!=0 && tokString.compare("LOC")!=0 ){
		throw std::runtime_error("forbidden state string improper: start with loc=id & ...\n use loc=-1 for any location\n");
	}
	tok_iter++;
	f_set.first = std::atoi((*tok_iter).c_str());
	*/


	std::string varname;
	std::string tokString;
	tokenizer::iterator tok_iter;
	unsigned int i;
	for(std::list<std::string>::iterator iter = all_args.begin(); iter!=all_args.end();iter++) {
		tokString = *iter;
		if (tokString.find("<=")!=std::string::npos ) { // less than equal to constraint
			sep = boost::char_separator<char>("<=");
			tokens = tokenizer(tokString, sep);
			tok_iter = tokens.begin();
			varname = *tok_iter;
			//cout <<"<= varName = " << varname <<endl;
			if ((varname == "gt") || (varname == "lt")){	//skip the lt and gt variable
				tok_iter++;
				gt_upper = std::atof((*tok_iter).c_str());
				continue;
			}
			tok_iter++;
			i = p->get_index(varname);
			std::vector<double> cons(p->map_size(),0);
			cons[i] = 1;
			double bound = std::atof((*tok_iter).c_str());
			p->setMoreConstraints(cons,bound);
		} else if(tokString.find(">=")!=std::string::npos) { // greater than equal to constraint
			sep = boost::char_separator<char>(">=");
			tokens = tokenizer(tokString,sep);
			tok_iter = tokens.begin();
			varname = *tok_iter;
			//cout <<">= varName = " << varname <<endl;
			if ((varname == "gt") || (varname == "lt")) {	//skip the lt and gt variable
				tok_iter++;
				gt_lower = std::atof((*tok_iter).c_str());
				continue;
			}
			tok_iter++;
			i = p->get_index(varname);
			std::vector<double> cons(p->map_size(),0);
			cons[i] = -1;
			double bound = std::atof((*tok_iter).c_str());
			p->setMoreConstraints(cons,-bound);
		} else {
			throw std::runtime_error("forbidden state string improper: <= or >= constraint expected\n");
		}
	}
//	cout<<"constraints = "<<p->getCoeffMatrix()<<"\n";
//	cout << "forbidden location id: " << f_set.first << std::endl;
//	for (int i=0;i<p->getColumnVector().size();i++)
//		cout<<p->getColumnVector()[i]<<"\t";
//	cout<<endl;

	unsafe_set = p;
};




//void string_list_to_polytope(user_inputs::ptr &user, polytope::ptr &p) {
void string_list_to_polytope(std::list<std::string> all_args, polytope::ptr &p) {
	//std::list<std::string> all_args = user->getInitialSet();

	std::string testStr="dummy & dummy";
	//std::cout << testStr << std::endl;

	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("& ");
	tokenizer tokens(testStr, sep);

	std::string varname;
	std::string tokString;

	tokenizer::iterator tok_iter;
//	std::cout <<"Size= "<< all_args.size() <<std::endl;
	unsigned int i;
	for(std::list<std::string>::iterator iter = all_args.begin(); iter!=all_args.end();iter++) {
		tokString = *iter;
		//std::cout << tokString << std::endl;
		if (tokString.find("<=")!=std::string::npos ) { // less than equal to constraint
			sep = boost::char_separator<char>("<=");
			tokens = tokenizer(tokString,sep);
			tok_iter = tokens.begin();
			varname = *tok_iter;
			tok_iter++;

			i = p->get_index(varname);
			//std::cout <<"i = "<< i << std::endl;
			std::vector<double> cons(p->map_size(),0);
			cons[i] = 1;
			double bound = std::atof((*tok_iter).c_str());
			p->setMoreConstraints(cons,bound);
		} else if(tokString.find(">=")!=std::string::npos){ // greater than equal to constraint
			sep = boost::char_separator<char>(">=");
			tokens = tokenizer(tokString,sep);
			tok_iter = tokens.begin();
			varname = *tok_iter;
			tok_iter++;
			i = p->get_index(varname);
			std::vector<double> cons(p->map_size(),0);
			cons[i] = -1;
			double bound = std::atof((*tok_iter).c_str());

			p->setMoreConstraints(cons,-bound);


		} else if ((tokString.find("=")!=std::string::npos) || (tokString.find("==")!=std::string::npos)) {

			sep = boost::char_separator<char>("=");
			tokens = tokenizer(tokString,sep);
			tok_iter = tokens.begin();
			varname = *tok_iter;
			tok_iter++;
			i = p->get_index(varname);
			std::vector<double> cons(p->map_size(),0);
			cons[i] = 1;
			double lessThan_bound = std::atof((*tok_iter).c_str());
			p->setMoreConstraints(cons,lessThan_bound);		//lessThan_bound

			cons[i] = -1;
			p->setMoreConstraints(cons,-lessThan_bound);	//greaterThan_bound

		} else{
			throw std::runtime_error("Input (Goal/Input Set) string improper: <= or >= constraint expected\n");
		}
	}
};


