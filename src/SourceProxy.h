/*
 ================================================================
 
 SourceProxy
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */


#ifndef __SOURCE_PROXY_H__
#define __SOURCE_PROXY_H__

#include "SignalSource.h"

class SourceProxy {
	
private:
	
	SignalSource* source;
	
public:
	
	SourceProxy();
	~SourceProxy();
	
	void setSignalSource(SignalSource* argSrc);
	
	unsigned getSamplingRate();
	unsigned getBlockSize();
	unsigned getChannelCount();
	
	
};

#endif