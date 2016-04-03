/*
 * Field.cpp
 *
 *  Created on: 29 mar 2016
 *      Author: Popek
 */

#include "Field.h"

Field::Field() {
	this->name = false;
	this->val = false;
	this->stmt = false;
}

Field::Field(string type, string value, bool name, bool val, bool stmt) {
	this->type = type;
	this->value = value;
	this->name = name;
	this->val = val;
	this->stmt = stmt;
}

Field::~Field() {
	// TODO Auto-generated destructor stub
}

bool Field::isName() const {
	return name;
}

void Field::setName(bool name) {
	this->name = name;
}

bool Field::isStmt() const {
	return stmt;
}

void Field::setStmt(bool stmt) {
	this->stmt = stmt;
}

const string& Field::getType() const {
	return type;
}

void Field::setType(const string& type) {
	this->type = type;
}

bool Field::isVal() const {
	return val;
}

void Field::setVal(bool val) {
	this->val = val;
}

const string& Field::getValue() const {
	return value;
}

void Field::setValue(const string& value) {
	this->value = value;
}
