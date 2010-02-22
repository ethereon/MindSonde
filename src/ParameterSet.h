/*
 ================================================================
 
 ParameterSet
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __PARAMETER_SET_H__
#define __PARAMETER_SET_H__

#include <string>
#include <vector>
#include "Parameter.h"

class ParameterSet {

	
	std::vector<Parameter*> params;
	
	unsigned idx;
	
public:

	ParameterSet();
	~ParameterSet();
	
	const bool* addBoolean(const char* name, const char* title, bool value);
	const int* addInteger(const char* name, const char* title, int value);
	
	const int* addEnum(const char* name, const char* title, const char** values, unsigned count);
	const int* addEnum(const char* name, const char* title, const int* values, unsigned count);
	const int* addEnum(const char* name, const char* title, const std::vector<std::string>* values);
	
	ParameterSet* addGroup(const char* name, const char* title);
	
	Parameter* getParameterByName(const char* name) const;
	
	Parameter* first();
	Parameter* next();
	
};
#endif