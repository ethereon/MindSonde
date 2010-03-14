/*
 ================================================================
 
 ImpedanceView
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __IMPEDANCE_VIEW_H__
#define __IMPEDANCE_VIEW_H__

#include "View.h"
#include "SignalSource.h"
#include "ThresholdWidget.h"

class ImpedanceView : public View {
	
	Q_OBJECT
	
private slots:

	void handleNewData(ChannelData* data);

private:
	
	const SignalSource* source;
	
	ThresholdWidget* indicators;
	
	int channelCount;
	
	float getAmplitude(float* values, int count);
	
public:
	
	ImpedanceView(const SignalSource* src, QWidget* parent=0);
	~ImpedanceView();
	

	
	void setup();
	void cleanup();
	
};


#endif