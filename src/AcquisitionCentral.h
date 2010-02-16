/*
 ================================================================
 
 AcquisitionCentral
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __ACQUISITION_CENTRAL_H__
#define __ACQUISITION_CENTRAL_H__

#include <QtGui>
#include <set>

#include "ChannelData.h"
#include "SignalSource.h"
#include "AcquisitionThread.h"

class AcquisitionCentral : public QObject {
	
	Q_OBJECT
	
private:
	
	int subscriberCount;
	int releasesLeft;
	
	SignalSource* source;
	
	AcquisitionThread acqThread;
	
	//Singleton pointer
	static AcquisitionCentral* instance;
	
	AcquisitionCentral();
	
private slots:
	
	void acceptNewData(ChannelData* data);
	
signals:
	
	void newDataAvailable(ChannelData* data);
	
	
public:
	
	static AcquisitionCentral* Instance();

	void setSignalSource(SignalSource* argSource);
	
	void start();
	void stop();
	
	void subscribe();
	void unsubscribe();
	
	
	void releaseData();
	
	
};

#endif