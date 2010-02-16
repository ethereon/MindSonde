/*
 ================================================================
 
 SignalSource
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __SIGNAL_SOURCE_H__
#define __SIGNAL_SOURCE_H__

#include <QtGui>
#include "ParameterSet.h"
#include "ChannelData.h"

class SignalSource {
	
	
public:
	
	SignalSource() { }
	virtual ~SignalSource() {}
	
	virtual ParameterSet* getParameters()=0;
	
	//TODO: Should these be here? Perhaps move these two functions to ParameterSet.
	virtual void saveSettingsToFile(const char* filename)=0;
	virtual void readSettingsFromFile(const char* filename)=0;
	
	//Characteristics
	virtual const char* getName()=0;
	virtual unsigned getSamplingRate()=0;
	virtual unsigned getChannelCount()=0;
	virtual unsigned getBlockSize()=0;

	//Actions
	virtual bool configure()=0;
	virtual void start()=0;
	virtual void stop()=0;
	virtual ChannelData* getData()=0;

	
	
};

#endif