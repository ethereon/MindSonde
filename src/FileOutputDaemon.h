/*
 ================================================================
 
 FileOutputDaemon
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __FILE_OUTPUT_DAEMON_H__
#define __FILE_OUTPUT_DAEMON_H__

#include <QtGui>
#include "DataSerializer.h"
#include <string>

class FileOutputDaemon : public QObject {
	
	
	Q_OBJECT
		
private slots:
	
	void processNewData(ChannelData* channelData);
	
private:
	
	std::string filename;
	DataSerializer* serializer;
	

	
public:
	
	FileOutputDaemon(DataSerializer* argSerializer);
	virtual ~FileOutputDaemon();
	
	void setFilename(const char* argFilename);
	
	void start();
	void stop();

};

#endif