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
	
	Q_OBJECT
	
private:
	
	bool value;

public slots:
	
	void updateValue(int state) { value = (state==Qt::Checked); }
	
public:
	
	BooleanParameter() { value = true; }
	~BooleanParameter() {}
	
	void setValue(bool v) { value = v; }
	bool getValue() { return value; }
	const bool* getReference() { return &value; }
	
};

#endif