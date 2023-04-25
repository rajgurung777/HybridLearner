/*
 * matlabPlotter.cpp
 *
 *  Created on: 21-Dec-2021
 *      Author: amit
 */

#include "matlabPlotter.h"

using namespace std;

void printPolytope2File(std::unique_ptr<MATLABEngine> &ep,
		intermediateResult::ptr intermediate, user_inputs::ptr users,
		polytope::ptr poly, std::string fileName) {

	string matrixA = "", vectorB = "";

	if (poly->getCoeffMatrix().size2() == 2) {

		matrixA = "A = [";
		vectorB = "b = [";
		for (unsigned int i = 0; i < poly->getCoeffMatrix().size1(); i++) {
			for (unsigned int j = 0; j < poly->getCoeffMatrix().size2(); j++) {
				matrixA.append(to_string(poly->getCoeffMatrix()(i, j)));
				matrixA.append(" ");
			}
			matrixA.append("; ");
		}
		matrixA.append("];");

		for (unsigned int j = 0; j < poly->getColumnVector().size(); j++) {
			vectorB.append(to_string(poly->getColumnVector()[j]));
			vectorB.append(" ");
		}
		vectorB.append("]';");	//transpose to convert into a column vector

	} else {	// When system has more than 2 variable. We use only the two plotting variables
		unsigned int var1, var2;

		var1 = poly->get_index(users->getPlotVars().first_variable);
		var2 = poly->get_index(users->getPlotVars().second_variable);

		matrixA = "A = [";
		vectorB = "b = [";
		for (unsigned int i = 0; i < poly->getCoeffMatrix().size1(); i++) {
			if ((poly->getCoeffMatrix()(i,var1) != 0) || (poly->getCoeffMatrix()(i,var2) != 0) ) {
				matrixA.append(to_string(poly->getCoeffMatrix()(i, var1)));
				matrixA.append(" ");
				matrixA.append(to_string(poly->getCoeffMatrix()(i, var2)));	//	matrixA.append(" ");
				matrixA.append("; ");

				vectorB.append(to_string(poly->getColumnVector()[i]));
				vectorB.append(" ");
			}

		}
		matrixA.append("];");
		vectorB.append("]';");	//transpose to convert into a column vector
	}

	//	A = [-1.0 0.0; 1.0 0.0; 0.0 -1.0; 0.0 1.0]
	//	b = [4 3 6 5]';
//		cout << matrixA << endl;
//		cout << vectorB << endl;

	ep->eval(convertUTF8StringToUTF16String(matrixA));
	ep->eval(convertUTF8StringToUTF16String(vectorB));


	string cmd = "cd('";
	cmd.append(intermediate->getToolRootPath());
	cmd.append("/src/io_functions/matlab_util");
	cmd.append("')");
	//engEvalString(ep, "cd('../src/benchmark/oscillator')");
	ep->eval(convertUTF8StringToUTF16String(cmd));

	//ep->eval(convertUTF8StringToUTF16String("run_circle"));
	ep->eval(u"output = con2vert(A,b);");
	ep->eval(u"X = output(:,1);");		//1 the first dimension for plotting
	ep->eval(u"Y = output(:,2);");		//2 the second dimension for plotting

	ep->eval(u"xmean = mean(X);");
	ep->eval(u"ymean = mean(Y);");
	ep->eval(u"[~,j] = sort(atan2(Y-ymean, X-xmean));");
	ep->eval(u"X = X(j);");
	ep->eval(u"Y = Y(j);");
	ep->eval(u"l = length(X);");
	ep->eval(u"X(l+1) = X(1);");
	ep->eval(u"Y(l+1) = Y(1);");

	ep->eval(u"points = [X, Y];");
	ep->eval(u"result_filename = 'vertices.txt';");
	ep->eval(u"writematrix(points, result_filename, 'Delimiter', 'tab');");


	string copycommand = "";
	copycommand.append("cp ");
	copycommand.append(intermediate->getToolRootPath());
	copycommand.append("/src/io_functions/matlab_util/vertices.txt");
	copycommand.append(" ");//to the current working directory, i.e. in the Release directory
	copycommand.append(intermediate->getToolRootPath());
	copycommand.append("/Release/");
	copycommand.append(fileName);
	int x = system(copycommand.c_str());
	if (x == -1) {
		cout << "Error executing cmd: " << copycommand << endl;
	}

}
