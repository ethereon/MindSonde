/*
 ================================================================
 
 Interleaved Channel Data Parser
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "InterleavedChannelData.h"
#include <assert.h>
#include <vector>

//-----------------------------------------------------------------------------

InterleavedChannelData::InterleavedChannelData() {
	
	
	data = NULL;
	this->channelCount = 0;
	this->samplesPerChannel = 0;
	this->isDemuxed = false;
	this->reallocChannels = true;
	
	
}

//-----------------------------------------------------------------------------


InterleavedChannelData::~InterleavedChannelData() {
	
	
}

//-----------------------------------------------------------------------------


const void* InterleavedChannelData::getRawData() const {
	
	return this->data;
	
}

//-----------------------------------------------------------------------------

unsigned InterleavedChannelData::getNumberOfChannels() const {
	
	return this->channelCount;
	
}

//-----------------------------------------------------------------------------

unsigned InterleavedChannelData::getSamplesPerChannel() const {
	
	return this->samplesPerChannel;
	
}

//-----------------------------------------------------------------------------

void InterleavedChannelData::setRawData(void* argData) {
	
	this->data = argData;
	this->isDemuxed = false;
	
}

//-----------------------------------------------------------------------------

void InterleavedChannelData::updateData() {
	
	this->isDemuxed = false;
	
}

//-----------------------------------------------------------------------------

void InterleavedChannelData::setNumberOfChannels(unsigned int nChannels) {
	
	this->channelCount = nChannels;
	this->reallocChannels = true;
	
	
}

//-----------------------------------------------------------------------------

void InterleavedChannelData::setSamplesPerChannel(unsigned int nSamples) {
	
	this->samplesPerChannel = nSamples;
	this->reallocChannels = true;
	
}

//-----------------------------------------------------------------------------

void InterleavedChannelData::reallocChannelBuffers() {
	
	assert(this->channelCount!=0);
	assert(this->samplesPerChannel!=0);
	
	if(channels.size()!=0) {
		
		//Free old buffers
		
		while(!(this->channels.empty())) {
			
			delete this->channels.back();
			this->channels.pop_back();
		}
		
	}
	
	for(unsigned int i=0;i<this->channelCount;++i) {
		
		float* channelData = new float[this->samplesPerChannel];
		channels.push_back(channelData);
	}
	
	this->isDemuxed = false;
	
}

//-----------------------------------------------------------------------------

void InterleavedChannelData::demuxData() {
	
	
	int totalSamples = (this->channelCount)*(this->samplesPerChannel);
	
	float* dataCursor = (float*)(this->data);
	
	for(int i=0; i<totalSamples; ++i) {
		
		int channelIdx = i%(this->channelCount);
		int elemIdx = i/(this->channelCount);
		
		channels[channelIdx][elemIdx] = *dataCursor;
		dataCursor++;
		
	}
	
	
	this->isDemuxed = true;
	
}

//-----------------------------------------------------------------------------

const void* InterleavedChannelData::getDataForChannel(unsigned int channel) {
	
	//Transform from 1-based channel number to zero-based index
	channel--;
	
	assert(this->data!=NULL);
	assert(this->channelCount!=0);
	assert(this->samplesPerChannel!=0);
	
	if(channel>this->channelCount)
		return NULL;
	
	if(reallocChannels)
		this->reallocChannelBuffers();
	
	if(!(this->isDemuxed))		
		this->demuxData();
	
	return this->channels[channel];
	
}

//-----------------------------------------------------------------------------

