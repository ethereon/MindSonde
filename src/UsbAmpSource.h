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
#include <string>
#include <vector>

class UsbAmpSource :  public SignalSource{
	
private:
	
	void setup();
	
	ParameterSet params;
	
	AmpLink amp;

	unsigned bufferLen;
	float* buffer;
	
	//Parameters
	int channelCount;
	const int* blockSize;
	const int* samplingRateIdx;
	const int* modeIndex;
	const bool* enableTriggerLine;
	const int* bandpassIndex;
	const int* notchIndex;
	
	std::vector<const bool*> selectedChannels;

	InterleavedChannelData channelData;
	
	string name;
	
	int index;
	
public:
	
	UsbAmpSource(int argIndex, const char* argName);
	~UsbAmpSource();
	
	ParameterSet* getParameters();
	
	static void getAvailableSources(std::vector<std::string>* devices);
	
	//Characteristics
	const char* getName() const;
	unsigned getSamplingRate() const;
	unsigned getChannelCount() const;
	unsigned getBlockSize() const;
	
	//Actions
	void connect();
	void disconnect();
	void configure();
	void start();
	void stop();
	ChannelData* getData();
	
};

#endif
