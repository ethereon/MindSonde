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

#include <vector>
#include "Parameter.h"

class ParameterSet {

	
	std::vector<Parameter*> params;
	
	unsigned idx;
	
public:

	ParameterSet();
	~ParameterSet();
	
	void addBoolean(const char* name, const char* title, bool value);
	void addInteger(const char* name, const char* title, long value);
	void addEnum(const char* name, const char* title, const char** values, unsigned count);
	
	Parameter* getParameterByName(const char* name);
	
	Parameter* first();
	Parameter* next();
	
};
#endif