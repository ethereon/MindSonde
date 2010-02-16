/*
 ================================================================
 
 AcquisitionThread
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "AcquisitionThread.h"
#include <assert.h>

using namespace std;

//-----------------------------------------------------------------------------

AcquisitionThread::AcquisitionThread() {

	source = NULL;
	isStopped = false;
}

//-----------------------------------------------------------------------------

void AcquisitionThread::setSignalSource(SignalSource* argSrc) {
	
	source = argSrc;
	
}

//-----------------------------------------------------------------------------

void AcquisitionThread::run() {
	
	assert(source!=NULL);
	
	source->start();
	
	isStopped = false;
	
	while(!isStopped) {
		
		mutex.lock();
		
		data = source->getData();
		
		emit newDataAvailable(data);
		
		w.wait(&mutex);
		
		mutex.unlock();
		
	}
	
}

//-----------------------------------------------------------------------------

void AcquisitionThread::stop() {
	
	isStopped = true;

}

//-----------------------------------------------------------------------------

void AcquisitionThread::releaseMutex() {

	w.wakeAll();
	
}

//-----------------------------------------------------------------------------