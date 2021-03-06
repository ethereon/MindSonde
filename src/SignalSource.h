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

	
	//Characteristics
	virtual const char* getName() const = 0;
	virtual unsigned getSamplingRate() const = 0;
	virtual unsigned getChannelCount() const = 0;
	virtual unsigned getBlockSize() const = 0;

	//Actions
	virtual void connect()=0;
	virtual void disconnect()=0;
	virtual void configure()=0;
	virtual void start()=0;
	virtual void stop()=0;
	virtual ChannelData* getData()=0;

	
	
};

#endif