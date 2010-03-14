/*
 ================================================================
 
 FileOutputDaemon
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "FileOutputDaemon.h"
#include "AcquisitionCentral.h"
#include <assert.h>

using namespace std;

//-----------------------------------------------------------------------------
	
FileOutputDaemon::FileOutputDaemon(DataSerializer* argSerializer) {
	
	serializer = argSerializer;
	
	if(serializer->isOpen())
		this->setFilename(serializer->getFilename());

}

//-----------------------------------------------------------------------------

FileOutputDaemon::~FileOutputDaemon() {
	
	delete serializer;
	
}

//-----------------------------------------------------------------------------

void FileOutputDaemon::processNewData(ChannelData* channelData) {
	
	serializer->writeData(channelData);
	AcquisitionCentral::Instance()->releaseData();

}

//-----------------------------------------------------------------------------

void FileOutputDaemon::setFilename(const char* argFilename) {
	
	filename = argFilename;
	
}

//-----------------------------------------------------------------------------

void FileOutputDaemon::start() {
	
	assert(filename.length()!=0);
	

	
	if(!serializer->isOpen())
		serializer->openFile(filename.c_str());
	
	
	//Subscribe to receive acquisition data
	
	connect(AcquisitionCentral::Instance(),
			SIGNAL(newDataAvailable(ChannelData*)),
			this,
			SLOT(processNewData(ChannelData*)));
	
	
}

//-----------------------------------------------------------------------------

void FileOutputDaemon::stop() {
	
	this->disconnect();
	serializer->close();
}

//-----------------------------------------------------------------------------