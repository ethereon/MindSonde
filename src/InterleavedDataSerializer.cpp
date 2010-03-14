/*
 ================================================================
 
 InterleavedDataSerializer
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "InterleavedDataSerializer.h"
#include <stdio.h>
#include "MException.h"
#include <assert.h>

using namespace std;

//-----------------------------------------------------------------------------

InterleavedDataSerializer::InterleavedDataSerializer() {
	
	fp = NULL;
	
}

//-----------------------------------------------------------------------------

InterleavedDataSerializer::~InterleavedDataSerializer() {
	
	if(isOpen())
		close();
	
}

//-----------------------------------------------------------------------------

void InterleavedDataSerializer::openFile(const char* argFilename) {
	
	filename = argFilename;
	
	fp = fopen(argFilename, "wb");
	
	if(fp==NULL)
		throw MException("Unable to open file for writing");
	
}

//-----------------------------------------------------------------------------

void InterleavedDataSerializer::close() {
	
	assert(fp!=NULL);
	fclose(fp);
	fp = NULL;
	
}

//-----------------------------------------------------------------------------

bool InterleavedDataSerializer::isOpen() {

	return fp!=NULL;
	
}

//-----------------------------------------------------------------------------

const char* InterleavedDataSerializer::getFilename() {
	
	return filename.c_str();
	
}

//-----------------------------------------------------------------------------

void InterleavedDataSerializer::writeHeader(const SignalSource* source) {
	
	assert(source);
	
	if(!fp)
		throw MException("Attempted to write header before opening file");

	int samplingRate = source->getSamplingRate();
	int blockSize = source->getBlockSize();
	int channelCount = source->getChannelCount();
	
	fwrite(&samplingRate, sizeof(int), 1, fp);
	fwrite(&channelCount, sizeof(int), 1, fp);
	
	this->totalBlockLength = blockSize*channelCount;
	
}

//-----------------------------------------------------------------------------

void InterleavedDataSerializer::writeData(ChannelData* channelData) {
	
	assert(fp);

	const void* data = channelData->getRawData();
	fwrite(data, sizeof(float), totalBlockLength, fp);
	
	
}

//-----------------------------------------------------------------------------
