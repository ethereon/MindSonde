/*
 ================================================================
 
 SinusoidalSource
 MindSonde / The Myelin Project
 
 A simulated sinusoidal signal source
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "SinusoidalSource.h"
#include "IntegerParameter.h"
#include "EnumParameter.h"
#include "BooleanParameter.h"
#include <QTimer>
#include <cmath>

#define SOURCE_NAME "Oscillator ( simulated sinusoidal )"

#define SOURCE_FREQ	"sFeq"
#define SAMPLING_RATE "sRate"
#define CHANNEL_COUNT "chanCount"
#define NOISY "noisy"
#define BLOCK_SIZE "Block size"

#define DEFAULT_FREQUENCY 11
#define DEFAULT_SAMPLING_RATE 8*DEFAULT_FREQUENCY
#define DEFAULT_CHANNEL_COUNT 1
#define DEFAULT_BLOCK_SIZE 10
#define DEFAULT_IS_NOISY true
#define SECONDS_FROM_LAUNCH (clock()/(double)CLOCKS_PER_SEC)

#ifndef PI
#define PI 3.14159265
#endif

using namespace std;

SinusoidalSource::SinusoidalSource() {
	
	frequency = DEFAULT_FREQUENCY;
	samplingRate = DEFAULT_SAMPLING_RATE;
	blockSize = DEFAULT_BLOCK_SIZE;
	channelCount = DEFAULT_CHANNEL_COUNT;
	isNoisy = DEFAULT_IS_NOISY;
	
	setupParameters();
	samples = NULL;
	
}

SinusoidalSource::~SinusoidalSource() {
	
	if(samples)
		delete [] samples;
	
}

void SinusoidalSource::setupParameters() {
	
	
	params.addInteger(SOURCE_FREQ,
					  "Source Frequency (HZ)",
					  DEFAULT_FREQUENCY);
	
	params.addInteger(SAMPLING_RATE,
					  "Sampling Rate",
					  DEFAULT_SAMPLING_RATE);
	
	
	params.addInteger(CHANNEL_COUNT,
					  "Number of Channels",
					  DEFAULT_CHANNEL_COUNT);
	
	params.addInteger(BLOCK_SIZE,
					 "Block Size",
					 DEFAULT_BLOCK_SIZE);
	
	params.addBoolean(NOISY,
					  "Add noise",
					  DEFAULT_IS_NOISY);
	
	
}

ParameterSet* SinusoidalSource::getParameters() {
	
	return &params;
	
}

void SinusoidalSource::saveSettingsToFile(const char* filename) {
	
}

void SinusoidalSource::readSettingsFromFile(const char* filename) {
	
}


bool SinusoidalSource::configure() {
	
	IntegerParameter* ip = (IntegerParameter*)params.getParameterByName(SOURCE_FREQ);
	this->frequency = ip->getValue();
	
	ip = (IntegerParameter*)params.getParameterByName(BLOCK_SIZE);
	this->blockSize = ip->getValue();
	
	ip = (IntegerParameter*)params.getParameterByName(CHANNEL_COUNT);
	this->channelCount = ip->getValue();
	
	ip = (IntegerParameter*)params.getParameterByName(SAMPLING_RATE);
	this->samplingRate = ip->getValue();
	
	BooleanParameter* bp = (BooleanParameter*)params.getParameterByName(NOISY);
	this->isNoisy = bp->getValue();
	
	channelData.setNumberOfChannels(channelCount);
	channelData.setSamplesPerChannel(blockSize);
	
	this->increment = (1.0/samplingRate);
	
	if(samples)
		delete samples;
	
	samples = new float[blockSize*channelCount];

	return true;
}

const char* SinusoidalSource::getName() {
	
	return SOURCE_NAME;
	
}

void SinusoidalSource::start() {
	
	time = 0;
	channelData.setRawData(samples);

	
}

void SinusoidalSource::stop() {
	
	
}


ChannelData* SinusoidalSource::getData() {
	
	for( int i=0;i<blockSize;++i) {
		
		int offset = i*(channelCount);
		float y = cos(2*PI*frequency*time);
		
		for(int j=0; j<channelCount; ++j) {
			
			samples[offset+j]= y;
			
			if(isNoisy)
				samples[offset+j] +=(rand()%10);
			
		}
		
		time+=increment;
	}

	channelData.updateData();
	
	return &(channelData);
	

}

unsigned SinusoidalSource::getSamplingRate() {
	
	return samplingRate;
	
}

unsigned SinusoidalSource::getBlockSize() {
	
	return blockSize;
	
}

unsigned SinusoidalSource::getChannelCount() {
	
	return channelCount;

}