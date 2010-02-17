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

    createToolbars();

}

//-----------------------------------------------------------------------------


MainWindow::~MainWindow() {
    
}

//-----------------------------------------------------------------------------

void MainWindow::createToolbars() {

    tbAmpControl = addToolBar(tr("Amp Control"));
	tbAmpControl->setVisible(false);

}

//-----------------------------------------------------------------------------

void MainWindow::enterAcquisitionMode() {
	
	tbAmpControl->setVisible(true);
	
}
	
//-----------------------------------------------------------------------------

void MainWindow::exitAcquisitionMode() {
	
	tbAmpControl->setVisible(false);
	
}

//-----------------------------------------------------------------------------

void MainWindow::pushView(View* view) {

	viewStack.push_back(view);
	view->setup();
	setCentralWidget(view);
	
}

//-----------------------------------------------------------------------------
View* MainWindow::popView() {
	
	if(viewStack.size()==0)
		return NULL;
	
	View* topView = viewStack.back();
	
	topView->cleanup();
	viewStack.pop_back();
	
	if(viewStack.size()!=0)
		setCentralWidget(viewStack.back());
	
}

//-----------------------------------------------------------------------------