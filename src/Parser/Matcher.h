/*
 * Matcher.h
 *
 *  Created on: 31 mar 2016
 *      Author: Popek
 */

#ifndef SRC_PARSER_MATCHER_H_
#define SRC_PARSER_MATCHER_H_

#include <vector>
#include <iostream>

using namespace std;

class Matcher {
public:
	Matcher();
	virtual ~Matcher();
	vector<int> findPosition(vector<string> &elems, string token);
	bool checkTokens(string &elem, string token) {
		//cout << elem.find(token) << endl;
		if (elem.find(token) > elem.length())
			return false;
		else
			return true;
	}

	bool checkVarName(string elem) {
		return (elem.find(".varname") < elem.length());
	}

	bool checkProcName(string elem) {
		return (elem.find(".procname") < elem.length());
	}

	bool checkStmt_(string elem) {
		return (elem.find(".stmt#") < elem.length());
	}

	bool checkValue(string elem)
	{
		return (elem.find(".value") < elem.length());
	}

	bool checkAll(string elem) {
		if (!checkVarName(elem) && !checkProcName(elem) && !checkStmt_(elem) && !checkValue(elem))
			return false;
		else
			return true;
	}
};
#endif /* SRC_PARSER_MATCHER_H_ */
