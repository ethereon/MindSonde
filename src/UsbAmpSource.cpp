/*
 ================================================================
 
 g.UsbAmp Signal Source
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "UsbAmpSource.h"
#include "IntegerParameter.h"
#include "UsbAmpSource.h"

#define SAMPLING_RATE "SamplingRate"
#define BLOCK_SIZE "BlockSize"

#define DEFAULT_SAMPLING_RATE 128
#define DEFAULT_BLOCK_SIZE 8
#define TRACE(msg) std::cout << "[USB_AMP_SOURCE] " << msg << endl;

UsbAmpSource::UsbAmpSource() {
	
	setup();
	
}

UsbAmpSource::~UsbAmpSource() {
	
}

void UsbAmpSource::setup() {
	
	

	params.addInteger(SAMPLING_RATE,
					  "Sampling Rate",
					  DEFAULT_SAMPLING_RATE);
	

	params.addInteger(BLOCK_SIZE,
					  "Block Size",
					  DEFAULT_BLOCK_SIZE);
	
}

ParameterSet* UsbAmpSource::getParameters() {

	return &params;
}


int UsbAmpSource::getIntegerParam(const char* name) {
	
	IntegerParameter* ip = (IntegerParameter*)params.getParameterByName(name);
	return ip->getValue();
	
}

//Characteristics
const char* UsbAmpSource::getName() {
	
	return "g.USBAmp";
	
}

unsigned UsbAmpSource::getSamplingRate() {
	
	return getIntegerParam(SAMPLING_RATE);
	
}

unsigned UsbAmpSource::getChannelCount() {
	
	return 1;
	
}

unsigned UsbAmpSource::getBlockSize() {
	
	return getIntegerParam(BLOCK_SIZE);
	
}

//Actions
bool UsbAmpSource::configure() {
	
	char activeChannels[] = { 1 };
	amp.setMode(Calibrate);
	amp.setTriggerLineEnabled(false);
	amp.setActiveChannels(activeChannels, 1);
	amp.setSamplingRate(getSamplingRate());
	amp.setBufferSize(getBlockSize());

	bufferLen = getBlockSize()*getChannelCount();
	buffer = new char[bufferLen];
	
	channelData.setNumberOfChannels(getChannelCount());
	channelData.setSamplesPerChannel(getBlockSize());
	channelData.setRawData(buffer);
	
	return true;
	
}

void UsbAmpSource::connect() {
	
	if(!amp.connect())
		TRACE("Unable to connect to the amplifier!");
	
}

void UsbAmpSource::disconnect() {
	
	amp.disconnect();
	
}

void UsbAmpSource::start() {
	
	amp.start();
	
}

void UsbAmpSource::stop() {
	
	amp.stop();
	
}

ChannelData* UsbAmpSource::getData() {

	amp.getData(buffer, bufferLen);
	
	channelData.updateData();
	return &channelData;
	
}