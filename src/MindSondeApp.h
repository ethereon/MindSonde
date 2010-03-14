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
#include "ImpedanceView.h"
#include "SignalView.h"
#include <QtGui>

class MindSondeApp : public QObject {
	
	Q_OBJECT
	
	
private: // Views
	
	SignalView* signalView;
	ImpedanceView* impedanceView;
	
	QAction* axnSignalView;
	
	View* getSignalView();
	View* getImpedanceView();
	
	View* activeView;
	
	View* setActiveView(View* argView, bool ignorePrev=false);
	void destroyAllViews();

private:
	
	MindSondeApp();
	
	QApplication* app;
	
	MainWindow* mainWindow;
	
	static MindSondeApp* instance;
	
	QToolBar* acqToolbar;
	
	SourceSelectionView* sourceSelector;
	
	SignalSource* activeSource;
	
	FileOutputDaemon* fileDaemon;
	
	void createToolbar();
	void startFileDaemon();
	void destroyActiveFileDaemon();
	
	
public slots:
	
	void stopAcquisition();
	void activeViewChanged(QAction* axnView);
		
public:
	
	static MindSondeApp* Instance();
	
	int execute(int argc, char** argv);
	
	void setActiveSource(SignalSource* argSource);
	void setFileOutputDaemon(FileOutputDaemon* argDaemon);
	
	void startAcquisition();

};
