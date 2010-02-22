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
#include <cstring>
#include "ParameterSet.h"
#include "EnumParameter.h"
#include "IntegerParameter.h"
#include "BooleanParameter.h"
#include "ParameterGroup.h"
#include "MindSondeUtil.h"

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

const bool* ParameterSet::addBoolean(const char* name, const char* title, bool value) {

	BooleanParameter* bp = new BooleanParameter();	
	bp->setName(name);
	bp->setTitle(title);
	bp->setValue(value);
	
	params.push_back((Parameter*)bp);
	
	return bp->getReference();
	
}

const int* ParameterSet::addInteger(const char* name, const char* title, int value) {
	
	IntegerParameter* ip = new IntegerParameter();
	ip->setName(name);
	ip->setTitle(title);
	ip->setValue(value);
	
	params.push_back((Parameter*)ip);
	
	return ip->getReference();
	
}

const int* ParameterSet::addEnum(const char* name, const char* title, const char** values, unsigned count) {
	
	EnumParameter* ep = new EnumParameter();
	ep->setName(name);
	ep->setTitle(title);
	
	for(unsigned i=0; i<count;++i)
		ep->addOption(values[i]);
	
	params.push_back((Parameter*)ep);
	
	return ep->getReference();
}

const int* ParameterSet::addEnum(const char* name, const char* title, const int* values, unsigned count) {
	
	
	EnumParameter* ep = new EnumParameter();
	ep->setName(name);
	ep->setTitle(title);
	
	for(unsigned i=0; i<count;++i)
		ep->addOption(integerToString(values[i]));
	
	params.push_back((Parameter*)ep);
	
	return ep->getReference();

	
	
}
const int* ParameterSet::addEnum(const char* name, const char* title, const vector<string>* values) {
	
	EnumParameter* ep = new EnumParameter();
	ep->setName(name);
	ep->setTitle(title);

	int count = (int)values->size();
	
	for(int i=0;i<count;++i)
		ep->addOption((*values)[i]);
	
	params.push_back((Parameter*)ep);
	
	return ep->getReference();
	
}

ParameterSet* ParameterSet::addGroup(const char* name, const char* title) {
	
	ParameterGroup* pg = new ParameterGroup();
	pg->setName(name);
	pg->setTitle(title);
	
	params.push_back((Parameter*)pg);
	
	return pg->getParameterSet();
	
}

Parameter* ParameterSet::getParameterByName(const char* name) const{
	
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

