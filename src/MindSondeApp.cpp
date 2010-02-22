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

MindSondeApp* MindSondeApp::instance = NULL;

MindSondeApp::MindSondeApp() {
	
	this->activeSource =  NULL;
									  
	this->fileDaemon = NULL;
}

									  
MindSondeApp* MindSondeApp::Instance()
{
	
	if(!instance)
		instance = new MindSondeApp();
	
	return instance;
}



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


void MindSondeApp::setActiveSource(SignalSource* argSource) {
	
	this->activeSource = argSource;
	
}

void MindSondeApp::setFileOutputDaemon(FileOutputDaemon* argDaemon) {
	
	this->fileDaemon = argDaemon;
	
}

void MindSondeApp::createToolbar() {
	
	acqToolbar = mainWindow->addToolBar("A");
	
	QAction* axnStopAcq = new QAction(QIcon(":/icons/images/stop-acq.png"), "Stop Acquisition", this);
	connect(axnStopAcq, SIGNAL(triggered()), this, SLOT(stopAcquisition()));
	
	QActionGroup* axnViewGroup = new QActionGroup(this);
	
	QAction* axnSignalView = new QAction(QIcon(":/icons/images/sine-wave.png"),"Signal View", this);
	connect(axnSignalView, SIGNAL(changed()), this, SLOT(showSignalView()));
	
	axnSignalView->setCheckable(true);

	axnViewGroup->addAction(axnSignalView);
	
	acqToolbar->addAction(axnStopAcq);
	acqToolbar->addAction(axnSignalView);
	acqToolbar->setVisible(false);

	//The signal view is active by default
	axnSignalView->setChecked(true);
}

void MindSondeApp::showSignalView() {
	
}

void MindSondeApp::startAcquisition() {
	
	assert(activeSource!=NULL);
	
	//Create a Signal View
	signalView = new SignalView(activeSource);
	
	if(fileDaemon) 
		fileDaemon->start();
		
	
	//Setup the Acquisition Center and tell it to start broadcasting data
	AcquisitionCentral::Instance()->setSignalSource(activeSource);
	AcquisitionCentral::Instance()->subscribe();
	AcquisitionCentral::Instance()->start();
	
	
	mainWindow->replaceTopView(signalView);
	
	acqToolbar->setVisible(true);
	
}

void MindSondeApp::stopAcquisition() {


	AcquisitionCentral::Instance()->stop();
	
	app->processEvents();

	if(fileDaemon)
		fileDaemon->stop();
	
	
	View* prevView = mainWindow->popView();
	prevView->setParent(0);
	delete prevView;
	
	//Disconnect from the active signal source
	activeSource->disconnect();
	activeSource = NULL;
	
	acqToolbar->setVisible(false);
	
}
