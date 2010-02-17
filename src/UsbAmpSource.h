/*
 ================================================================
 
 g.UsbAmp Signal Source
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __USB_AMP_SOURCE_H__
#define __USB_AMP_SOURCE_H__

#include "SignalSource.h"
#include "AmpLink.h"
#include "InterleavedChannelData.h"

class UsbAmpSource :  public SignalSource{
	
private:
	
	void setup();
	
	ParameterSet params;
	
	int getIntegerParam(const char* name);
	
	AmpLink amp;

	unsigned bufferLen;
	char* buffer;
	InterleavedChannelData channelData;

public:
	
	UsbAmpSource();
	~UsbAmpSource();
	
	ParameterSet* getParameters();
	
	//Characteristics
	const char* getName();
	unsigned getSamplingRate();
	unsigned getChannelCount();
	unsigned getBlockSize();
	
	//Actions
	void connect();
	void disconnect();
	bool configure();
	void start();
	void stop();
	ChannelData* getData();
	
};

#endif
