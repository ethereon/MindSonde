/*
 ================================================================
 
 MindSondeApp
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "MindSondeApp.h"
#include <QtGui>
#include "MainWindow.h"
#include <assert.h>
#include "AcquisitionCentral.h"

//-----------------------------------------------------------------------------

MindSondeApp* MindSondeApp::instance = NULL;

//-----------------------------------------------------------------------------

MindSondeApp::MindSondeApp() {
	
	this->activeSource =  NULL;
									  
	this->fileDaemon = NULL;
	
	this->signalView = NULL;
	
	this->impedanceView = NULL;
	
	this->activeView = NULL;
}

//-----------------------------------------------------------------------------
									  
MindSondeApp* MindSondeApp::Instance()
{
	
	if(!instance)
		instance = new MindSondeApp();
	
	return instance;
}


//-----------------------------------------------------------------------------

int MindSondeApp::execute(int argc, char** argv) {
	
	app = new QApplication(argc, argv);

	
	//Acquire the shared instance to the Main Window
	mainWindow = MainWindow::Instance();	

		
	//Construct toolbars
	createToolbar();
	
	//Set the Source Selector view as the primary one
	this->sourceSelector = new SourceSelectionView(mainWindow);
	mainWindow->pushView(sourceSelector);
	
	mainWindow->resize(800,600);
	mainWindow->show();
	mainWindow->setWindowTitle(QApplication::translate("appName","MindSonde"));

	
	return app->exec();
	
}

//-----------------------------------------------------------------------------

void MindSondeApp::setActiveSource(SignalSource* argSource) {
	
	this->activeSource = argSource;
	
}

//-----------------------------------------------------------------------------

void MindSondeApp::setFileOutputDaemon(FileOutputDaemon* argDaemon) {
	
	this->fileDaemon = argDaemon;
	
}

//-----------------------------------------------------------------------------

void MindSondeApp::activeViewChanged(QAction* axnView) {

	
	if(axnView==axnSignalView)
		setActiveView(getSignalView());
	else
		setActiveView(getImpedanceView());

	
}

//-----------------------------------------------------------------------------

void MindSondeApp::createToolbar() {
	
	acqToolbar = mainWindow->addToolBar("Acq");
	
	//Stop Acquisition
	QAction* axnStopAcq = new QAction(QIcon(":/icons/images/stop-acq.png"), "Stop Acquisition", this);
	acqToolbar->addAction(axnStopAcq);
	connect(axnStopAcq, SIGNAL(triggered()), this, SLOT(stopAcquisition()));
	
	
	//Signal View
	axnSignalView = new QAction(QIcon(":/icons/images/sine-wave.png"),"Signal View", this);
	axnSignalView->setCheckable(true);
	acqToolbar->addAction(axnSignalView);
	
	//Impedance View
	QAction* axnImpedanceView = new QAction(QIcon(":/icons/images/impedance.png"), "Impedance View", this);
	axnImpedanceView->setCheckable(true);
	acqToolbar->addAction(axnImpedanceView);
	
	//The View Group
	QActionGroup* axnViewGroup = new QActionGroup(this);	
	axnViewGroup->addAction(axnSignalView);
	axnViewGroup->addAction(axnImpedanceView);
	connect(axnViewGroup, SIGNAL(triggered(QAction*)), this, SLOT(activeViewChanged(QAction*)));
	
	//Hide the toolbar ( visible only during acquisition )
	acqToolbar->setVisible(false);

	//The signal view is active by default
	axnSignalView->setChecked(true);
	
}


//-----------------------------------------------------------------------------

View* MindSondeApp::setActiveView(View* argView, bool ignorePrev) {

	if(argView == this->activeView) return NULL;

	View* prevView = mainWindow->replaceTopView(argView);
	AcquisitionCentral* acqCentral = AcquisitionCentral::Instance();
	
	connect(acqCentral, SIGNAL(newDataAvailable(ChannelData*)), argView, SLOT(handleNewData(ChannelData*)));
	acqCentral->subscribe();
	
	this->activeView = argView;

	if(!ignorePrev) {
		
		prevView->setParent(0);
		disconnect(acqCentral, SIGNAL(newDataAvailable(ChannelData*)), prevView, SLOT(handleNewData(ChannelData*)));
		acqCentral->unsubscribe();
	}
	
	return prevView;
	
}

//-----------------------------------------------------------------------------

View* MindSondeApp::getSignalView() {
	
	if(signalView==NULL) {
		
		signalView = new SignalView(activeSource);
		
	}
	
	return signalView;
}

//-----------------------------------------------------------------------------

View* MindSondeApp::getImpedanceView() {
	
	if(impedanceView==NULL) {
		
		impedanceView = new ImpedanceView(activeSource);
		
	}
	
	return impedanceView;
	
}

//-----------------------------------------------------------------------------

void freeView(View* view) {

	if(view==NULL) return;
	
	view->setParent(0);
	
	delete view;
	
}

//-----------------------------------------------------------------------------

void MindSondeApp::destroyAllViews() {
	
	
	freeView(signalView);
	freeView(impedanceView);
	
	signalView = NULL;
	impedanceView = NULL;
	
	
}

//-----------------------------------------------------------------------------

void MindSondeApp::startFileDaemon() {
	
	if(!fileDaemon) return;
	
	fileDaemon->start();
	AcquisitionCentral::Instance()->subscribe();
	
}

//-----------------------------------------------------------------------------

void MindSondeApp::startAcquisition() {
	
	assert(activeSource!=NULL);
		
	startFileDaemon();
	
	//Setup the Acquisition Center and tell it to start broadcasting data
	AcquisitionCentral::Instance()->setSignalSource(activeSource);
	AcquisitionCentral::Instance()->start();
	
	View* prevView = setActiveView(getSignalView(),true);
	delete prevView;
	
	axnSignalView->setChecked(true);
	acqToolbar->setVisible(true);
	
}

//-----------------------------------------------------------------------------

void MindSondeApp::destroyActiveFileDaemon() {
	
	if(!fileDaemon) return;
	
	fileDaemon->stop();
	
	delete fileDaemon;
	
	fileDaemon = NULL;
	
	AcquisitionCentral::Instance()->unsubscribe();
	
}

//-----------------------------------------------------------------------------

void MindSondeApp::stopAcquisition() {

	AcquisitionCentral* acqCentral = AcquisitionCentral::Instance();

	acqCentral->stop();
	
	app->processEvents();

	destroyActiveFileDaemon();
	
	mainWindow->popView();
	destroyAllViews();
	
	//Disconnect from the active signal source
	activeSource->disconnect();
	activeSource = NULL;
	
	activeView = NULL;
	
	acqCentral->unsubscribe();
	acqToolbar->setVisible(false);
	
}

//-----------------------------------------------------------------------------
