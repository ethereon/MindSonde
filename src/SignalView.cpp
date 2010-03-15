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
#include "ParameterRenderer.h"
#include "MindSondeUtil.h"
#include <string>
#include <cmath>

using namespace std;

//-----------------------------------------------------------------------------

SignalView::SignalView(const SignalSource* src, QWidget* parent) : View(parent) {
	
	plots = NULL;
	xValues = NULL;
	channels = NULL;
	source = NULL;
	dataCursor = 0;
	channelCount=0;
	scale = 1;
	
	//Default window period of 4 seconds
	windowPeriod = 2;
	
	//Setup plot container
	container = new QWidget(this);
	QVBoxLayout* vbox = new QVBoxLayout(this);
	this->setLayout(vbox);
	vbox->addWidget(container);

	
	//Setup the signal source and its parameters
	this->source = src;
	this->windowLength = (source->getSamplingRate()) * windowPeriod;
	this->blockSize = source->getBlockSize();
	this->channelCount = source->getChannelCount();
	
	//Setup visible channel selection dialog
	for(int i=0;i<channelCount;++i) {
		
		string title = "Channel " + integerToString(i+1);
		const char* cstr = title.c_str();
		
		const bool* b = visibleChannelParams.addBoolean(cstr,
														cstr,
														true);
		
		isChannelVisible.push_back(b);
										
		
	}
	
	channelDialog = ParameterRenderer::createParameterDialog(&visibleChannelParams, this);
	channelDialog->setWindowTitle("Visible Channels");
	
	connect(channelDialog, SIGNAL(accepted()), this, SLOT(updateView()));

	//Allocate the buffers for the samples
	allocBuffers();
	
	//Construct the plots
	setupPlots();
	

	
}

//-----------------------------------------------------------------------------

SignalView::~SignalView() {

	if(plots!=NULL) {
		
		delete [] markers;
		delete [] plots;
		
	}
	
	freeBuffers();	
	
}

//-----------------------------------------------------------------------------

void SignalView::updateView() {
	
	for(int i=0;i<channelCount;++i) {
		
		if(*(isChannelVisible[i]))
				plots[i].setVisible(true);
		else 
			plots[i].setVisible(false);
		
	}
		
}

//-----------------------------------------------------------------------------

void SignalView::showChannelSelector() {
	
	channelDialog->show();
	channelDialog->raise();
	channelDialog->activateWindow();
	
	
}

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

void SignalView::setupPlots() {
	

	assert(source!=NULL);
	assert(channels!=NULL);

	QVBoxLayout* layout = new QVBoxLayout(container);
	
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
		

		plots[i].enableAxis(QwtPlot::xBottom, false);
		   
		plots[i].enableAxis(QwtPlot::yLeft, false);
		plots[i].setMargin(0);
		plots[i].setCanvasBackground(palette.getBackgroundColor());

		//Setup update marker
		markers[i].setLinePen(QPen(Qt::red));
		markers[i].setValue(0.0,0.0);
		markers[i].setLineStyle(QwtPlotMarker::VLine);
		markers[i].attach(&plots[i]);
	}
	
	
}

//-----------------------------------------------------------------------------

void SignalView::handleNewData(ChannelData* channelData) {
		
	int endCursor = (dataCursor+blockSize)%windowLength;
	
	for(int i=0; i<channelCount; ++i) {
		

		if(!(*(isChannelVisible[i]))) {
			continue;
		}

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

//-----------------------------------------------------------------------------

void SignalView::autoscalePlots() {
		
	for(int i=0;i<channelCount;++i)
		plots[i].setAxisAutoScale(QwtPlot::yLeft);
	
}

//-----------------------------------------------------------------------------

void SignalView::scalePlots() {
	
	for(int i=0; i<channelCount; ++i)
		plots[i].setAxisScale(QwtPlot::yLeft, -scale, scale, 0);
	
}

//-----------------------------------------------------------------------------

void SignalView::scaleChanged(int index) {
	
	scale = pow(10.0, index);
	scalePlots();
	
}

//-----------------------------------------------------------------------------

void SignalView::scalingModeChanged(QAction* axnType) {
	
	if(axnType==axnAutoscale)
		autoscalePlots();
	else
		scalePlots();

	
}

//-----------------------------------------------------------------------------

void SignalView::setup() {
	
	
	//Setup Toolbar
	
	tbSignalView = new QToolBar(this);

	QAction* axnSelectChannel = new QAction(QIcon(":/icons/images/channels.png"), "Select Channels", this);
	tbSignalView->addAction(axnSelectChannel);
	
	QActionGroup* axnScaleGroup = new QActionGroup(this);
	
	axnAutoscale = new QAction(QIcon(":/icons/images/autoscale.png"), "Autoscale", this);
	axnAutoscale->setCheckable(true);
	axnAutoscale->setChecked(true);
	tbSignalView->addAction(axnAutoscale);
	axnScaleGroup->addAction(axnAutoscale);
	
	QAction* axnScale = new QAction(QIcon(":/icons/images/scale.png"), "Scale", this);
	axnScale->setCheckable(true);
	tbSignalView->addAction(axnScale);
	axnScaleGroup->addAction(axnScale);
	
	QComboBox* comboScale = new QComboBox(this);
	for(int i=0;i<10;++i)
		comboScale->addItem(QString("x E")+QString::number(i));
	
	tbSignalView->addWidget(comboScale);	
	
	MainWindow::Instance()->addToolBar(tbSignalView);
	connect(axnSelectChannel, SIGNAL(triggered()), this, SLOT(showChannelSelector()));
	connect(axnScaleGroup, SIGNAL(triggered(QAction*)), this, SLOT(scalingModeChanged(QAction*)));
	connect(comboScale, SIGNAL(currentIndexChanged(int)), this, SLOT(scaleChanged(int)));
	
}

//-----------------------------------------------------------------------------

void SignalView::cleanup() {
	
	MainWindow::Instance()->removeToolBar(tbSignalView);

}

//-----------------------------------------------------------------------------