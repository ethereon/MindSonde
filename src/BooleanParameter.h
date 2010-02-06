/*
 ================================================================
 
 BooleanParameter
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __MINDSONDE_BOOLEAN_PARAMETER_H__
#define __MINDSONDE_BOOLEAN_PARAMETER_H__


#include "Parameter.h"

class BooleanParameter : public Parameter {
	
private:
	
	bool value;
	
public:
	
	BooleanParameter() { value = true; }
	~BooleanParameter() {}
	
	void setValue(bool v) { value = v; }
	bool getValue() { return value; }
	
};

#endif