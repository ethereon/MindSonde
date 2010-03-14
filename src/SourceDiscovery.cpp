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
#include "UsbAmpSource.h"
#include <string>

using namespace std;

//-----------------------------------------------------------------------------

SourceDiscovery* SourceDiscovery::instance = NULL;


//-----------------------------------------------------------------------------

SourceDiscovery* SourceDiscovery::Instance()
{
	
	if(!instance)
		instance = new SourceDiscovery();
	
	return instance;
}

//-----------------------------------------------------------------------------

void SourceDiscovery::getSources(vector<SignalSource*>* vecSources)
{
	
	if(usbAmps.size()!=0) {
		
		while(!usbAmps.empty()) {
			
			delete usbAmps.back();
			usbAmps.pop_back();
			
		}
		
	}

	vecSources->push_back(&oscillator);	
	
	vector<string> availSources;
	UsbAmpSource::getAvailableSources(&availSources);
	
	for(unsigned i=0; i<availSources.size(); ++i) {
		
		string name = "g.USBamp / " + availSources[i];
		UsbAmpSource* src =  new UsbAmpSource(i, name.c_str());
		usbAmps.push_back(src);
		vecSources->push_back(src);
		
	}
	
	

}

//-----------------------------------------------------------------------------
