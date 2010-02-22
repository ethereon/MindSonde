/*
 ================================================================
 
 MainWindow
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "MainWindow.h"
#include "MindSondeApp.h"

MainWindow* MainWindow::instance = NULL;

//-----------------------------------------------------------------------------

MainWindow* MainWindow::Instance()
{
	
	if(!instance)
		instance = new MainWindow();
	
	return instance;
}

//-----------------------------------------------------------------------------

MainWindow::MainWindow() {

	viewTray = new QStackedWidget(this);
	setCentralWidget(viewTray);

}

//-----------------------------------------------------------------------------


MainWindow::~MainWindow() {
    
}

//-----------------------------------------------------------------------------

void MainWindow::pushView(View* view) {

	viewStack.push_back(view);
	view->setup();
	
	viewTray->addWidget(view);
	viewTray->setCurrentWidget(view);
}

//-----------------------------------------------------------------------------
View* MainWindow::popView() {
	
	if(viewStack.size()==0)
		return NULL;
	
	View* topView = viewStack.back();
	
	
	viewTray->removeWidget(topView);

	viewStack.pop_back();
	viewTray->setCurrentWidget(viewStack.back());
	
	topView->cleanup();

	

	return topView;
}

//-----------------------------------------------------------------------------

View* MainWindow::replaceTopView(View* view) {
	
	
	if(viewStack.size()==0)
		return NULL;
	
	view->setup();
	
	View* topView = viewStack.back();


	viewStack.pop_back();
	
	viewStack.push_back(view);
	
	viewTray->addWidget(view);
	viewTray->setCurrentWidget(view);
	
	viewTray->removeWidget(topView);

	topView->cleanup();

	
	return topView;

}