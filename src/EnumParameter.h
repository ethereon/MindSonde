/*
 ================================================================
 
 EnumParameter
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __MINDSONDE_ENUM_PARAMETER_H__
#define __MINDSONDE_ENUM_PARAMETER_H__


#include "Parameter.h"
#include <Assert.h>

class EnumParameter : public Parameter {

private:
	
	std::vector<std::string> options;
	unsigned selectedIndex;
public:
	
	EnumParameter() { selectedIndex=0; }
	
	void addOption(const std::string& opt) {
		
		options.push_back(opt);
		
	}
	
	
	const std::vector<std::string>& getOptions() { return options; }
	
	int getIndexOfOption(const std::string& opt) {
		
		for(unsigned i=0;i<options.size();++i)
			if(options[i]==opt) return i;
		
		return -1;
		
	}
	
	void setValue(unsigned idx) {
		
		assert(idx<options.size());
		selectedIndex = idx;
	}
	
	std::string getValue() {
		
		return options[selectedIndex];
	}
	
};

#endif
