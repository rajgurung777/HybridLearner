/*
 * string_parser.cpp
 *
 *  Created on: 22-Jun-2018
 *      Author: rajarshi
 */


#include <boost/tokenizer.hpp>
#include "stringParser.h"


std::list<std::pair<double, std::string> > linexp_parser(std::string expr)
{
	std::list<std::pair<double, std::string> > res;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("+ ");
	tokenizer tokens(expr, sep);

	for(tokenizer::iterator tok_iter = tokens.begin(); tok_iter!=tokens.end();tok_iter++)
	{
		std::string term = *tok_iter;
		sep = boost::char_separator<char>("* ");
		tokenizer subtokens = tokenizer(term, sep);

		tokenizer::iterator iter = subtokens.begin();
		std::string item = *iter;
		double coeff = std::atof(item.c_str());

		iter++; // next token

		std::string varname;
		varname = *iter;
		std::pair<double, std::string> coeff_varname;
		coeff_varname.first = coeff;
		coeff_varname.second = varname;
		res.push_back(coeff_varname);
	}
	return res;

}

std::vector<unsigned int> path_parser(std::string path)
{
	std::vector<unsigned int> res;

	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(", ");
	tokenizer tokens(path, sep);


	unsigned int path_len = 0;
	for(tokenizer::iterator tok_iter = tokens.begin(); tok_iter!=tokens.end();tok_iter++)
	{
		path_len++;
		res.resize(path_len);

		std::string item = *tok_iter;
		unsigned int loc_id = std::atoi(item.c_str());
		res[path_len-1] = loc_id;
	}
	return res;

}

