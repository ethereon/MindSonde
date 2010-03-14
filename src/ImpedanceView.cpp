/*
 ================================================================
 
 ImpedanceView
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "ImpedanceView.h"
#include "AcquisitionCentral.h"
#include <assert.h>
#include <limits>

//-----------------------------------------------------------------------------

ImpedanceView::ImpedanceView(const SignalSource* src, QWidget* parent) : View(parent)
{
	
	
	char buffer[20];
	
	this->source = src;
	
	channelCount = source->getChannelCount();
	
	assert(channelCount!=0);
	
	indicators = new ThresholdWidget[channelCount];
	
	QVBoxLayout* vbox = new QVBoxLayout(this);
	
	for(int i=0;i<channelCount;++i) {

		sprintf(buffer, "Channel %02d", i+1);
		indicators[i].setTitle(buffer);
		vbox->addWidget(&indicators[i]);
	}

	this->setLayout(vbox);

}

//-----------------------------------------------------------------------------

ImpedanceView::~ImpedanceView() {
	
	delete [] indicators;
	
}

//-----------------------------------------------------------------------------

void ImpedanceView::setup() {
	


}

//-----------------------------------------------------------------------------

float ImpedanceView::getAmplitude(float* values, int count) {
	
	float min = std::numeric_limits<float>::infinity();
	float max = -min;
	
	for(int i=0; i<count; ++i) {
		
		if(values[i]>max) max = values[i];
		if(values[i]<min) min = values[i];
		
	}
	
	return max - min;
	
}

//-----------------------------------------------------------------------------

void ImpedanceView::handleNewData(ChannelData* channelData) {		

	
	for(int i=0;i<channelCount;++i) {
		
		float *values =(float*)channelData->getDataForChannel(i+1);

		float amplitude = getAmplitude(values, channelData->getSamplesPerChannel());
		indicators[i].setValue(amplitude);
		
	}
	
	AcquisitionCentral::Instance()->releaseData();
	
}

//-----------------------------------------------------------------------------

void ImpedanceView::cleanup() {

}

//-----------------------------------------------------------------------------