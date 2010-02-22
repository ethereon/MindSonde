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

ImpedanceView::ImpedanceView(const SignalSource* src, QWidget* parent) : View(parent)
{
	
	this->source = src;
	
	channelCount = source->getChannelCount();
	
	assert(channelCount!=0);
	
	zLabels = new QLabel[channelCount];
	
	QVBoxLayout* vbox = new QVBoxLayout(this);
	
	for(int i=0;i<channelCount;++i)
		vbox->addWidget(&zLabels[i]);

	this->setLayout(vbox);

}

ImpedanceView::~ImpedanceView() {
	
	delete [] zLabels;
	
}


void ImpedanceView::setup() {
	


}

void ImpedanceView::processNewData(ChannelData* channelData) {

		
	float *values =(float*)channelData->getDataForChannel(0);
	
	AcquisitionCentral::Instance()->releaseData();
	
}

void ImpedanceView::cleanup() {

}