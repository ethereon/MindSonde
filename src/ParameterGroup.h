/*
 ================================================================
 
 ParameterGroup
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __PARAMETER_GROUP_H__
#define __PARAMETER_GROUP_H__

#include "Parameter.h"
#include "ParameterSet.h"

class ParameterGroup : public Parameter {
	
	Q_OBJECT
	
private:
	
	ParameterSet params;
	
public:
	
	ParameterGroup() { }
	~ParameterGroup() {}
	
	ParameterSet* getParameterSet() { return &params; }
	
};

#endif