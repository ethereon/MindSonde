/*
 ================================================================
 
 AcquisitionCentral
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "AcquisitionCentral.h"
#include <assert.h>

AcquisitionCentral* AcquisitionCentral::instance = NULL;


//-----------------------------------------------------------------------------

AcquisitionCentral::AcquisitionCentral() {
	
	source = NULL;
	releasesLeft=0;
	subscriberCount=0;
	connect(&acqThread, SIGNAL(newDataAvailable(ChannelData*)), this, SLOT(acceptNewData(ChannelData*)));
	
}

//-----------------------------------------------------------------------------

AcquisitionCentral* AcquisitionCentral::Instance()
{
	
	if(!instance)
		instance = new AcquisitionCentral();
	
	return instance;
}

//-----------------------------------------------------------------------------

void AcquisitionCentral::setSignalSource(SignalSource* argSource) {
	
	
	this->source = argSource;
	
}
	
//-----------------------------------------------------------------------------
	
void AcquisitionCentral::acceptNewData(ChannelData* data) {
	
	releasesLeft = subscriberCount;
	
	emit newDataAvailable(data);
	
}

//-----------------------------------------------------------------------------

void AcquisitionCentral::subscribe() {
	
	this->subscriberCount++;
	
}

//-----------------------------------------------------------------------------

void AcquisitionCentral::unsubscribe() {
	
	this->subscriberCount--;
	
}
	
//-----------------------------------------------------------------------------

void AcquisitionCentral::releaseData() {
	
	assert(this->releasesLeft!=0);
	
	this->releasesLeft--;
	
	if(releasesLeft==0)
		acqThread.releaseMutex();
		
}

//-----------------------------------------------------------------------------

void AcquisitionCentral::start() {
	
	assert(source!=NULL);
	
	//Tell the source to start acquisition
	source->start();
	
	acqThread.setSignalSource(source);
	acqThread.start();
	

}

//-----------------------------------------------------------------------------

void AcquisitionCentral::stop() {


	acqThread.stop();
	acqThread.wait();

	//Stop the source AFTER the thread. Since the thread makes a blocking
	//call to the source's getData method, stopping it first could cause
	//the thread to freeze / exceptions.
	source->stop();

}

//-----------------------------------------------------------------------------
