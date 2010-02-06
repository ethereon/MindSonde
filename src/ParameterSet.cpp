/*
 ================================================================
 
 ParameterSet
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include <string>
#include "ParameterSet.h"
#include "EnumParameter.h"
#include "IntegerParameter.h"
#include "BooleanParameter.h"

using namespace std;

ParameterSet::ParameterSet() {

	idx=0;

}


ParameterSet::~ParameterSet() {


	while (!params.empty()) {
		
		Parameter* p = params.back();
		delete p;
		params.pop_back();
		
	}


}

void ParameterSet::addBoolean(const char* name, const char* title, bool value) {

	BooleanParameter* bp = new BooleanParameter();	
	bp->setName(name);
	bp->setTitle(title);
	bp->setValue(value);
	
	params.push_back((Parameter*)bp);
	
}

void ParameterSet::addInteger(const char* name, const char* title, long value) {
	
	IntegerParameter* ip = new IntegerParameter();
	ip->setName(name);
	ip->setTitle(title);
	ip->setValue(value);
	
	params.push_back((Parameter*)ip);
	
}

void ParameterSet::addEnum(const char* name, const char* title, const char** values, unsigned count) {
	
	EnumParameter* ep = new EnumParameter();
	ep->setName(name);
	ep->setTitle(title);
	
	for(unsigned i=0; i<count;++i)
		ep->addOption(values[i]);
	
	params.push_back((Parameter*)ep);
}

Parameter* ParameterSet::getParameterByName(const char* name) {
	
	unsigned len = params.size();
	
	for(unsigned i=0;i<len;++i)
		if(strcmp(params[i]->getName(),name)==0)
			return params[i];
	
	return NULL;
	
}

Parameter* ParameterSet::first() {
	
	idx=1;
	return params[0];
	
}

Parameter* ParameterSet::next() {

	if(idx==params.size())
		return NULL;

	return params[idx++];
	
}

