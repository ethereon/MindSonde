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

#include <QtGui>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_plot_marker.h>

//#include "SignalReceiver.h"
#include "SourceProxy.h"
#include "RealtimePlot.h"

class SignalView : public QWidget {
	
	Q_OBJECT
	
	
private slots:

	void processNewData(ChannelData* channelData);

private:
	
	QVBoxLayout* layout;
	
	int windowPeriod;
	int windowLength;
	int blockSize;
	int dataCursor;
	int channelCount; 

	RealtimePlot* plots;
	QwtPlotMarker* markers;
	
	SourceProxy* source;
	
	double* xValues;
	double** channels;
	
	void setupPlots();
	void allocBuffers();
	void freeBuffers();
public:
	
	SignalView(QWidget* parent=0);
	~SignalView();
	

	void setSourceProxy(SourceProxy* argSrc);
	
};

#endif