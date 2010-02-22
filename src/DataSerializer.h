/*
 ================================================================
 
 Data Serializer Interface
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __DATA_SERIALIZER_H__
#define __DATA_SERIALIZER_H__

#include "ChannelData.h"
#include "SignalSource.h"


class DataSerializer {
	
public:
	
	DataSerializer() {}
	virtual ~DataSerializer() {}
	
	virtual bool isOpen()=0;
	virtual const char* getFilename()=0;
	
	virtual void openFile(const char* argFilename)=0;
	virtual void close()=0;

	virtual void writeHeader(const SignalSource* source)=0;
	virtual void writeData(ChannelData* channelData)=0;
	
};

#endif