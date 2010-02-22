/*
 ================================================================
 
 InterleavedDataSerializer
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __INTERLEAVED_DATA_SERIALIZER_H__
#define __INTERLEAVED_DATA_SERIALIZER_H__

#include "DataSerializer.h"
#include "MException.h"
#include <string>

class InterleavedDataSerializer : public DataSerializer {
	
private:
	
	FILE* fp;
	
	int totalBlockLength;
	
	std::string filename;

public:
	
	InterleavedDataSerializer();
	~InterleavedDataSerializer();
	
	bool isOpen();
	const char* getFilename();
	
	void openFile(const char* argFilename);
	void close();
	void writeHeader(const SignalSource* source);
	void writeData(ChannelData* channelData);
	
	
};

#endif