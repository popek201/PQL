/*
 * Field.h
 *
 *  Created on: 29 mar 2016
 *      Author: Popek
 */

#ifndef SRC_TREE_FIELD_H_
#define SRC_TREE_FIELD_H_

#include <string>

using namespace std;

class Field {
public:
	Field();
	Field(string type, string value, bool name, bool val, bool stmt);
	virtual ~Field();
	bool isName() const;
	void setName(bool name);
	bool isStmt() const;
	void setStmt(bool stmt);
	const string& getType() const;
	void setType(const string& type);
	bool isVal() const;
	void setVal(bool val);
	const string& getValue() const;
	void setValue(const string& value);

private:
	string type;
	string value;
	bool name; // DEFAULT FALSE
	bool val; // DEFAULT FALSE
	bool stmt; // DEFAULT FALSE
};

#endif /* SRC_TREE_FIELD_H_ */
