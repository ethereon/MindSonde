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

MindSondeApp* MindSondeApp::instance = NULL;

MindSondeApp::MindSondeApp() {
									  
}

									  
MindSondeApp* MindSondeApp::Instance()
{
	
	if(!instance)
		instance = new MindSondeApp();
	
	return instance;
}



int MindSondeApp::execute(int argc, char** argv) {
	
	QApplication app(argc, argv);
	
	//Acquire the shared instance to the Main Window
	mainWindow = MainWindow::Instance();	

	//Set the Source Selector view as the primary one
	this->sourceSelector = new SourceSelector(mainWindow);
	mainWindow->pushView(sourceSelector);
	
	mainWindow->resize(800,600);
	mainWindow->show();
	mainWindow->setWindowTitle(QApplication::translate("appName","MindSonde"));

	
	return app.exec();
	
}
