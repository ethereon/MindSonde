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


class SinusoidalSource : public SignalSource {
	
private:

	void setupParameters();

	ParameterSet params;

public:
	
	SinusoidalSource();
	~SinusoidalSource();	
	
	ParameterSet* getParameters();
	
	void saveSettingsToFile(const char* filename);
	void readSettingsFromFile(const char* filename);
	
	bool configure();
	
	const char* getName();
	
};

#endif