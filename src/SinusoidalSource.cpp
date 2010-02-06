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

#define SOURCE_NAME "Oscillator ( simulated sinusoidal )"

#define SOURCE_FREQ	"sFeq"
#define CHANNEL_COUNT "chanCount"
#define AWGN "awgn"

using namespace std;

SinusoidalSource::SinusoidalSource() {
	
	setupParameters();
	
}

SinusoidalSource::~SinusoidalSource() {
	
	
}

void SinusoidalSource::setupParameters() {
	
	
	params.addInteger(SOURCE_FREQ,
					  "Source Frequency (HZ)",
					  42);
	
	
	params.addInteger(CHANNEL_COUNT,
					  "Number of Channels",
					  1);
	
	
	params.addBoolean(AWGN,
					  "Additive White Gaussian Noise",
					  false);
	
	
	
}

ParameterSet* SinusoidalSource::getParameters() {
	
	return &params;
	
}

void SinusoidalSource::saveSettingsToFile(const char* filename) {
	
}

void SinusoidalSource::readSettingsFromFile(const char* filename) {
	
}


bool SinusoidalSource::configure() {
	
	return true;
}

const char* SinusoidalSource::getName() {
	
	return SOURCE_NAME;
	
}