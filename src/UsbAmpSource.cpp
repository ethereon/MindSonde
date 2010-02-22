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
#include "EnumParameter.h"
#include "BooleanParameter.h"
#include "UsbAmpSource.h"
#include "MindSondeUtil.h"
#include "MException.h"
#include <vector>
#include <string>

#define SAMPLING_RATE "SamplingRate"
#define BLOCK_SIZE "BlockSize"
#define AMP_MODE "ampMode"
#define ACTIVE_CHANNELS "activeChannels"
#define TRIGGER_LINE "enableTriggerLine"
#define BANDPASS "Bandpass"
#define NOTCH "Notch"

#define ACQUIRE_INDEX 0

#define TRACE(msg) std::cout << "[USB_AMP_SOURCE] " << msg << endl;
#define SAMPLING_RATE_COUNT 9

static const int validSamplingRates[] = {32,64,128,256,512,600,1200,2400,4800 };

static vector<string> bandpassFilters;
static vector<string> notchFilters;
using namespace std;


void populateFilters(const FilterSpec* filters, int count, vector<string>* dest) {
	
	dest->push_back("<Disabled>");
	
	for(int i=0; i< count; ++i) {
		
		string hf = floatToString(filters[i].hf);
		string lf = floatToString(filters[i].lf);
		string sf = integerToString(filters[i].sf);
		string type = integerToString(filters[i].type);
		string order = integerToString(filters[i].order);
		
		string filter = hf + " to " + lf + " / " + sf + ", " + type + ", " + order;
		
		dest->push_back(filter);
		
	}
	
}

const vector<string>* getBandpassFilters() {
	
	if(bandpassFilters.size()==0) {
		
		const FilterSpec* filters = AmpLink::getBandpassFilters();
		
		populateFilters(filters, BANDPASS_FILTER_COUNT, &bandpassFilters);
		
	}
	
	return &bandpassFilters;
}

const vector<string>* getNotchFilters() {
	
	if(notchFilters.size()==0) {
		
		const FilterSpec* filters = AmpLink::getNotchFilters();
		
		populateFilters(filters, NOTCH_FILTER_COUNT, &notchFilters);
	}
	
	return &notchFilters;
}

UsbAmpSource::UsbAmpSource(int argIndex, const char* argName) {
	
	index = argIndex;
	name = argName;
	
	blockSize = NULL;
	samplingRateIdx = NULL;
	enableTriggerLine = NULL;
	modeIndex = NULL;
	
	amp.setVerbosityLevel(2);
	
	setup();
	
	buffer = NULL;
	
}

UsbAmpSource::~UsbAmpSource() {
	
	if(buffer!=NULL)
		delete buffer;
	
}

void UsbAmpSource::setup() {
	
	
	
	
	samplingRateIdx = params.addEnum(SAMPLING_RATE,
									 "Sampling Rate",
									 validSamplingRates,
									 SAMPLING_RATE_COUNT);
	
	blockSize = params.addInteger(BLOCK_SIZE,
								  "Block Size",
								  8);	
	
	
	const char* ampModes[] = { "Acquire", "Calibration ( test signal )" };
	
	modeIndex = params.addEnum(AMP_MODE,
							   "Mode",
							   ampModes,
							   2);
	
	bandpassIndex = params.addEnum(BANDPASS,
								   "Bandpass Filter",
								   getBandpassFilters());
	
	notchIndex = params.addEnum(NOTCH, "Notch Filter", getNotchFilters());
	
	enableTriggerLine = params.addBoolean(TRIGGER_LINE, "Enable trigger line", false);
	
	ParameterSet* ps = params.addGroup(ACTIVE_CHANNELS, "Active Channels");
	
	for(int i=0;i<16;++i) {
		
		string title = string("Channel ") + integerToString(i+1);
		const char* cTag = title.c_str();		
		selectedChannels.push_back(ps->addBoolean(cTag, cTag, i==0));
		
	}
	
}

ParameterSet* UsbAmpSource::getParameters() {
	
	//TODO: Make this lazy instantiate the parameters
	return &params;
}


//Characteristics
const char* UsbAmpSource::getName() const {
	
	return name.c_str();
	
}

void UsbAmpSource::getAvailableSources(std::vector<std::string>* devices) {
	
	AmpLink::getAvailableAmps(devices);
	
}
unsigned UsbAmpSource::getSamplingRate() const {
	
	return validSamplingRates[*samplingRateIdx];
	
}

unsigned UsbAmpSource::getChannelCount() const {
	
	return channelCount + (*enableTriggerLine);
	
}

unsigned UsbAmpSource::getBlockSize() const {
	
	return (unsigned)*blockSize;
	
}

//Actions
void UsbAmpSource::configure() {
	
	//Set Mode
	if(*modeIndex==ACQUIRE_INDEX)
		amp.setMode(Acquire);
	else
		amp.setMode(Calibrate);
	
	char activeChannels[16];
	
	//Set active channels
	channelCount = 0;
	
	for(int i=0;i<16;++i) {
		
		
		if(*selectedChannels[i])
			activeChannels[channelCount++] = i+1;
		
	}
	
	
	amp.setActiveChannels(activeChannels, channelCount);
	
	amp.setTriggerLineEnabled(*enableTriggerLine);
	amp.setSamplingRate(getSamplingRate());
	amp.setBufferSize(getBlockSize());

	int bi = (*bandpassIndex)-1;
	int ni = (*notchIndex)-1;

	for(int i=1;i<=16;++i) {
		
		amp.setBandpass(bi, i);
		amp.setNotch(ni, i);
	}
	
	bufferLen = getBlockSize()*getChannelCount();
	if(buffer!=NULL) delete buffer;
	buffer = new float[bufferLen];
	
	channelData.setNumberOfChannels(getChannelCount());
	channelData.setSamplesPerChannel(getBlockSize());
	channelData.setRawData(buffer);
	
}

void UsbAmpSource::connect() {
	
	if(!amp.connect(index)) {
		
		throw MException("Could not connect to g.USBamp");
		
	}
	
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
	
	amp.getData(buffer, bufferLen*4);
	
	channelData.updateData();
	return &channelData;
	
}