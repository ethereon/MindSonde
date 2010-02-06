/*
 ================================================================
 
 IntegerParameter
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __INTEGER_PARAMETER_H__
#define __INTEGER_PARAMETER_H__

#include "Parameter.h"

class IntegerParameter : public Parameter {
	
private:
	
	long value;
	
public:
	
	IntegerParameter() { value = 0; }
	~IntegerParameter() {}
	
	void setValue(long v) { value = v; }
	long getValue() { return value; }
	
};

#endif