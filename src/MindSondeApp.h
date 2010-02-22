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
#include "FileOutputDaemon.h"
#include "SignalView.h"
#include <QtGui>

class MindSondeApp : public QObject {
	
	Q_OBJECT

private:
	
	MindSondeApp();
	
	QApplication* app;
	
	MainWindow* mainWindow;
	
	//Singleton pointer
	static MindSondeApp* instance;
	
	QToolBar* acqToolbar;
	
	SourceSelectionView* sourceSelector;
	
	SignalSource* activeSource;
	
	FileOutputDaemon* fileDaemon;
	
	SignalView* signalView;
	
	void createToolbar();
	
	
public slots:
	
	void stopAcquisition();
	void showSignalView();
		
public:
	
	static MindSondeApp* Instance();
	
	int execute(int argc, char** argv);
	
	void setActiveSource(SignalSource* argSource);
	void setFileOutputDaemon(FileOutputDaemon* argDaemon);
	
	void startAcquisition();

};
