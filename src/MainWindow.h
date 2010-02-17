/*
 ================================================================
 
 MainWindow
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H


#include <QtGui>

#include "SourceSelector.h"
#include "View.h"
#include <vector>

class MainWindow : public QMainWindow {

    Q_OBJECT

private:

	//Singleton pointer
	static MainWindow* instance;
	
    //Toolbars
    QToolBar *tbAmpControl;

    //Actions
    QAction* axnToggleAmpState;
	
    void createToolbars();

	std::vector<View*> viewStack;

	MainWindow();
	
public:

	static MainWindow* Instance();
	
    ~MainWindow();
	
	void enterAcquisitionMode();
	void exitAcquisitionMode();
	
	void pushView(View* view);
	View* popView();
	

};

#endif	/* _MAINWINDOW_H */

