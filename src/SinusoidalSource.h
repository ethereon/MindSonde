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

#ifndef __SINUSOIDAL_SOURCE_H__
#define __SINUSOIDAL_SOURCE_H__

#include "SignalSource.h"
#include "InterleavedChannelData.h"


class SinusoidalSource : public SignalSource {
	
private:

	void setupParameters();

	ParameterSet params;
	
	InterleavedChannelData channelData;
	
	//Source characteristics
	int frequency;
	int samplingRate;
	int channelCount;
	int blockSize;
	bool isNoisy;
	
	float increment;
	
	double time;
	
	float* samples;

	
public:
	
	SinusoidalSource();
	~SinusoidalSource();	
	
	ParameterSet* getParameters();
	

	void configure();
	const char* getName() const;
	
	unsigned getSamplingRate() const;
	unsigned getBlockSize() const ;
	unsigned getChannelCount() const;

	void connect() {}
	void disconnect() {}
	void start();
	void stop();
	ChannelData* getData();
	
};

#endif