/*
 ================================================================
 
 SourceDiscovery
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */


#ifndef __SOURCE_DISCOVERY_H__
#define __SOURCE_DISCOVERY_H__

#include "SignalSource.h"
#include <vector>

class SourceDiscovery {
	
private:
	
 	SourceDiscovery() {}


	static SourceDiscovery* instance;
	
public:
	
	static SourceDiscovery* Instance();
	
	void getSources(std::vector<SignalSource*>* vecSources);



};


#endif