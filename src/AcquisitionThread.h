/*
 ================================================================
 
 AcquisitionThread
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __ACQUISITION_THREAD_H__
#define __ACQUISITION_THREAD_H__

#include <QtGui>
#include "SignalSource.h"
#include <vector>

class AcquisitionThread : public QThread {
	
	Q_OBJECT
	
private:
	
	volatile bool isStopped;
	
	SignalSource* source;
	ChannelData* data;

	QMutex mutex;
	QWaitCondition w;
	

signals:
	
	void newDataAvailable(ChannelData* data);
	
public:
	
	
	AcquisitionThread();

	void setSignalSource(SignalSource* argSrc);
	void run();
	void stop();
	
	void releaseMutex();
		
};

#endif