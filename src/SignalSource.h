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

#include <QWidget>
#include "ParameterSet.h"


class SignalSource {
	
	
public:
	
	SignalSource() { }
	virtual ~SignalSource() {}
	
	virtual ParameterSet* getParameters()=0;
	
	virtual void saveSettingsToFile(const char* filename)=0;
	virtual void readSettingsFromFile(const char* filename)=0;
	virtual bool configure()=0;
	
	virtual const char* getName()=0;
	
};

#endif