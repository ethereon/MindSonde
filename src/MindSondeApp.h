/*
 ================================================================
 
 MindSondeApp
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "MainWindow.h"
#include "AcquisitionThread.h"
#include "SignalSource.h"
#include <QtGui>

class MindSondeApp {

private:
	
	MindSondeApp();
	
	MainWindow* mainWindow;
	
	//Singleton pointer
	static MindSondeApp* instance;
	
	SourceSelector* sourceSelector;
		
public:
	
	static MindSondeApp* Instance();
	
	int execute(int argc, char** argv);
	
};
