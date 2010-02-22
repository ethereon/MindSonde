/*
 ================================================================
 
 Utility Functions
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */


#ifndef __MINDSONDE_UTIL_H__
#define __MINDSONDE_UTIL_H__

#include "MException.h"
#include <string>

std::string integerToString(const long& v);
std::string floatToString(const float& v);
void displayException(MException* ex, const char* msg=NULL);

#endif