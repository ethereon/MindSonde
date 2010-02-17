/*
 ================================================================
 
 SignalView
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "SignalView.h"
#include "ChannelData.h"
#include "AcquisitionCentral.h"
#include "assert.h"
#include "PlotPalette.h"
#include "MainWindow.h"

SignalView::SignalView(QWidget* parent) : View(parent) {
	
	plots = NULL;
	xValues = NULL;
	channels = NULL;
	source = NULL;
	dataCursor = 0;
	channelCount=0;
	
	//Default window period of 4 seconds
	windowPeriod = 4;
	
	//Initialize layout
	layout = new QVBoxLayout(this);
	this->setLayout(layout);
	
}

SignalView::~SignalView() {

	
	
}

void SignalView::allocBuffers() {

	assert(channelCount>0);
	assert(windowLength>0);
	
	
	//Setup the x-values
	
	xValues = new double[windowLength];
	
	double increment = (double)windowPeriod/windowLength;
	
	for (int i=0; i<windowLength; i++) {
	
		//Off-by-one here for the period
		xValues[i] = increment*i;

	}
	
	//Setup the channel buffers
	
	channels = new double*[channelCount];
						   
	for(int i=0;i<channelCount;++i) {
		
		channels[i] = new double[windowLength];
	
		for(int j=0;j<windowLength;channels[i][j++]=0) {}

	}
	
}

void SignalView::freeBuffers() {
	
	if(xValues!=NULL)
		delete [] xValues;
	
	if(channels!=NULL) {
		
		for(int i=0;i<channelCount;++i) {
			
			delete [] channels[i];
			
		}
		
		delete [] channels;
		
	}
	
}

void SignalView::setupPlots() {
	
	assert(source!=NULL);
	assert(channels!=NULL);

	layout->setSpacing(1);
	plots = new RealtimePlot[this->channelCount];
	markers = new QwtPlotMarker[this->channelCount];
	
	PlotPalette palette;
	
	for(int i=0;i<channelCount;++i) {
		
		QwtPlotCurve* curve = new QwtPlotCurve();
		curve->setRawData(xValues, channels[i], windowLength);
		curve->attach(&plots[i]);
		curve->setPen(QPen(palette.getCurveColor(i)));
		layout->addWidget(&plots[i]);
		
		if(i!=(channelCount-1))
		   plots[i].enableAxis(QwtPlot::xBottom, false);
		   
		//plots[i].enableAxis(QwtPlot::yLeft, false);
		plots[i].setMargin(0);
		plots[i].setCanvasBackground(palette.getBackgroundColor());
		plots[i].setAxisTitle(QwtPlot::yLeft, QString("Ch ")+QString::number(i+1));
		
		//Setup update marker
		markers[i].setLinePen(QPen(Qt::red));
		markers[i].setValue(0.0,0.0);
		markers[i].setLineStyle(QwtPlotMarker::VLine);
		markers[i].attach(&plots[i]);
	}
	
	
}



void SignalView::setSourceProxy(SourceProxy* argSrc) {
	
	
	this->source = argSrc;
	
	this->windowLength = (source->getSamplingRate()) * windowPeriod;
	this->blockSize = source->getBlockSize();
	this->channelCount = source->getChannelCount();
	
	freeBuffers();
	allocBuffers();
	setupPlots();
	
	connect(AcquisitionCentral::Instance(),
			SIGNAL(newDataAvailable(ChannelData*)),
			this,
			SLOT(processNewData(ChannelData*)));
	
}

void SignalView::processNewData(ChannelData* channelData) {
	
	int endCursor = (dataCursor+blockSize)%windowLength;
	
	for(int i=0; i<channelCount; ++i) {
		
		float *values =(float*)channelData->getDataForChannel(i+1);
		
		int cursor = dataCursor;
		
		for(int j=0;j<blockSize;++j) {
			
			channels[i][cursor] =  values[j];
			cursor = (cursor+1)%windowLength;
		}
		
		markers[i].setXValue(xValues[endCursor]);
		plots[i].replot();
		
	}
	
	dataCursor = endCursor;
	
	AcquisitionCentral::Instance()->releaseData();
	
}

void SignalView::setupDockWindows() {
	
	QDockWidget* dock = new QDockWidget("Configure",this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea |
						  Qt::RightDockWidgetArea |
						  Qt::TopDockWidgetArea |
						  Qt::BottomDockWidgetArea);
	
	MainWindow::Instance()->addDockWidget(Qt::LeftDockWidgetArea, dock);
	
	QToolBox* toolbox = new QToolBox(this);
	dock->setWidget(toolbox);
	
}

void SignalView::setup() {
	
	MainWindow::Instance()->enterAcquisitionMode();
	//setupDockWindows();

}

void SignalView::cleanup() {
	
	MainWindow::Instance()->exitAcquisitionMode();

}