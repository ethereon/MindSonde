/*
 ================================================================
 
 SignalView
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __SIGNAL_VIEW_H__
#define __SIGNAL_VIEW_H__

#include "View.h"
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_plot_marker.h>

#include "ChannelData.h"
#include "SignalSource.h"
#include "RealtimePlot.h"
#include <vector>

class SignalView : public View {
	
	Q_OBJECT
	
	
private slots:

	void processNewData(ChannelData* channelData);
	void showChannelSelector();
	void updateView();
	void autoscalePlots();
	void scalePlots();
	void scaleChanged(int index);

private:
		
	QToolBar* tbSignalView;
	QWidget* container;
	
	QAction* axnAutoscale;
	
	int windowPeriod;
	int windowLength;
	int blockSize;
	int dataCursor;
	int channelCount; 
	double scale;

	RealtimePlot* plots;
	QwtPlotMarker* markers;
	
	const SignalSource* source;
	
	double* xValues;
	double** channels;
	
	ParameterSet visibleChannelParams;
	QDialog* channelDialog;
	
	void setupPlots();
	void allocBuffers();
	void freeBuffers();
	
	std::vector<const bool*> isChannelVisible;
	
public:
	
	SignalView(const SignalSource* src, QWidget* parent=0);
	~SignalView();
	
	
	void setup();
	void cleanup();
	
};

#endif