/*
 ================================================================
 
 Interleaved Channel Data Parser
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef _INTERLEAVEDCHANNELDATA_H
#define	_INTERLEAVEDCHANNELDATA_H


#include "ChannelData.h"
#include <vector>

using namespace std;

class InterleavedChannelData : public ChannelData {

protected:

    void* data;

    unsigned int channelCount;
    unsigned int samplesPerChannel;

    bool isDemuxed;

    vector<float*> channels;

    void reallocChannelBuffers();
    void demuxData();


public:

    InterleavedChannelData();
    virtual ~InterleavedChannelData();

    const void* getRawData() const;
    unsigned getNumberOfChannels() const;
    unsigned getSamplesPerChannel() const;

    const void* getDataForChannel(unsigned int channel);

    void setRawData(void* argData);
    void setNumberOfChannels(unsigned int nChannels);
    void setSamplesPerChannel(unsigned int nSamples);

	void updateData();

    
};




#endif	
