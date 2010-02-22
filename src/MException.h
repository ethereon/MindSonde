/*
 ================================================================
 
 Generic MindSonde Exception Class
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __M_EXCEPTION_H__
#define __M_EXCEPTION_H__

#include <stdexcept>
#include <string>

using std::string;
using std::runtime_error;

class MException: public runtime_error {
	
public:
	
	MException() : runtime_error("Unknown argument parsing error.") {}
	MException(const string& argWhat) : runtime_error(argWhat) {}
	
	
};



#endif