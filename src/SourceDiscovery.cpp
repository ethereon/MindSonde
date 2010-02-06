/*
 ================================================================
 
 SourceDiscovery
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "SourceDiscovery.h"
#include <stddef.h>
#include "SinusoidalSource.h"

using namespace std;

SourceDiscovery* SourceDiscovery::instance = NULL;

SourceDiscovery* SourceDiscovery::Instance()
{
	
	if(!instance)
		instance = new SourceDiscovery();
	
	return instance;
}

//TODO: JUST MAKE THIS A BLOODY STATIC
//TODO: NO WAIT,THINK ABOUT GUSBAMP DISCOVERY
void SourceDiscovery::getSources(vector<SignalSource*>* vecSources)
{

	vecSources->push_back(new SinusoidalSource());

}
