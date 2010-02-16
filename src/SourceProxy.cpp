/*
 ================================================================
 
 SourceProxy
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */



#include "SourceProxy.h"


	
SourceProxy::SourceProxy() {
	
}

SourceProxy::~SourceProxy() {
	
}
	
void SourceProxy::setSignalSource(SignalSource* argSrc) {
	
	this->source = argSrc;
	
}
	
unsigned SourceProxy::getSamplingRate() {
	
	return source->getSamplingRate();
	
}

unsigned SourceProxy::getBlockSize() {
	
	return source->getBlockSize();
}

unsigned SourceProxy::getChannelCount() {

	return source->getChannelCount();
}
