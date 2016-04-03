/*
 * QueryPreProcessor.h
 *
 *  Created on: 29 mar 2016
 *      Author: Popek
 */

#ifndef SRC_QUERYPREPROCESSOR_H_
#define SRC_QUERYPREPROCESSOR_H_

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <iterator>

#include "PQL/Field.h"
#include "Parser/Matcher.h"

using namespace std;

class QueryPreProcessor {
public:
	QueryPreProcessor();
	virtual ~QueryPreProcessor();
	void parseQuery(string query);

private:
	void writeVector(vector<string> &tab) {
		cout << "Kolejny wektor" << endl;
		for (int i = 0; i < tab.size(); i++) {
			cout << "[" << i << "] " << tab[i] << endl;
		}
	}

	vector<string> &split(const string &s, char delim, vector<string> &elems) {
		stringstream ss(s);
		string item;
		while (getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}

	vector<string> split(const string &s, char delim) {
		vector<string> elems;
		split(s, delim, elems);
		return elems;
	}

	vector<Field> makeFields(vector<string> &elems) {
		vector<Field> fields;
		vector<string> tmp = elems; //= split(elems[0], ',');

		//writeVector(tmp);

		vector<string> tokens = {"assign","stmt","while","variable","constant","prog_line"};

		Matcher* m = new Matcher();
		for (int i = 0; i < tmp.size(); i++) {
			//cout << "Tmp" << i << ": " << tmp[i] << endl;
			// Sprawdzenie czy deklaracja nie zawiera procName, varName, value albo stmt#
			if (!m->checkAll(tmp[i])) {
				for(int j = 0 ; j < tokens.size() ; j ++)
				{
					if (tmp[i].find(tokens[j]) < tmp[i].length()) {
						vector<Field> tmpFields = makeFieldType(tokens[j],tmp[i]);
						for (int j = 0; j < tmpFields.size(); j++) {
							//cout << tmpFields[j].getType() << " " << tmpFields[j].getValue() << endl;
							fields.push_back(tmpFields[j]);
						}

					}
				}
			} else {
				throwException();
			}
		}

		return fields;
	}

	vector<Field> makeFieldType(string type, string declaration) {
		//cout << "1->" << declaration << endl;

		declaration.erase(remove_if(declaration.begin(), declaration.end(), ptr_fun<int, int>(isspace)), declaration.end());

		//cout << "2->" << declaration << endl;

		declaration = declaration.substr(type.length(), declaration.length());

		//cout << "3->" << declaration << endl;

		vector<string> tmp = split(declaration, ',');
		vector<Field> declarationFields;
		for (int i = 0; i < tmp.size(); i++) {
			declarationFields.push_back(Field(type, tmp[i], false, false, false));
		}

		return declarationFields;
	}

	void throwException() {
		cout << "Query is invalid.";
		exit(1);
	}

	/// START ///

	void makeTree(vector<string> &elems)
	{
		if(elems.size() > 1) throwException();
		//if(countSelect(elems[0]) > 1) throwException();

		vector<string> queryMainTokens;
		for(int i = 0 ; i < elems.size() ; i ++)
		{
			if(elems[i].find("select") < elems[i].length()) {
				//queryMainTokens.push_back("select");
			}
			else {
				throwException();
			}

			if(elems[i].find("such that") < elems[i].length()) {
				queryMainTokens.push_back("such that");
			}
		}

		writeVector(queryMainTokens);

		vector<string> elements = splitQuery(elems[0],queryMainTokens);

		writeVector(queryParts);
	}

	int aktPos;
	int lastPos;
	int queryLength;
	string aktToken;
	string lastToken;
	vector<string> queryParts;

	vector<string> splitQuery(string query,vector<string> tokensElems)
	{
		aktPos = aktToken.length();
		lastPos = query.length();
		queryLength = query.length();

		//cout<< "START " << aktPos << " " << lastPos << " " << queryLength << endl;

		findPositions(query, tokensElems);

		return queryParts;
	}

	void findPositions(string query, vector<string> tokens)
	{
		int tmpPos;
		for(int i = 0 ; i < tokens.size() ; i ++)
		{
			tmpPos = query.find(tokens[i], aktPos);
			//cout << i << " -> " << tokens[i] << " " << aktPos << " " << lastPos << endl;
			if(tmpPos < lastPos && tmpPos < query.length())
			{
				lastPos = tmpPos;
				lastToken = aktToken;
				aktToken = tokens[i];
				//cout << "CHANGE -> " << lastPos << "|" << tmpPos << " " << aktToken << endl;
			}
		}

		//cout<< "NEXT? " << aktPos << " " << lastPos << " " << aktToken.length() << " " << queryLength << endl;

		queryParts.push_back(query.substr(aktPos-lastToken.length(),lastPos));

		query = query.substr(lastPos,queryLength);
		//aktPos = lastPos;// + aktToken.length();
		//lastPos = query.length();

		//cout<< "NEXT? " << aktPos << " " << lastPos << " " << aktToken.length() << " " << queryLength << endl;

		if(getNextPosition(tokens, query)) splitQuery(query, tokens);
	}

	bool getNextPosition(vector<string> tokens, string query)
	{
		for(int i = 0 ; i < tokens.size() ; i ++)
		{
			if(query.find(tokens[i]) < query.length())
				return true;
		}
		return false;
	}

	/// END ///

public:
	vector<Field>& getFields() {
		return fields;
	}

	void setFields(vector<Field>& fields) {
		this->fields = fields;
	}

private:
	vector<Field> fields;
};

#endif /* SRC_QUERYPREPROCESSOR_H_ */
