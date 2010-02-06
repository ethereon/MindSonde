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

MainWindow* MainWindow::Instance()
{
	
	if(!instance)
		instance = new MainWindow();
	
	return instance;
}

MainWindow::MainWindow() {

	viewStack = new QStackedWidget(this);

	srcSelector = new SourceSelector;
	viewStack->addWidget(srcSelector);


	setCentralWidget(viewStack);
    createToolbars();

}

void MainWindow::pushView(QWidget* argView) {
	
	viewStack->addWidget(argView);
	viewStack->setCurrentIndex(viewStack->count()-1);
	
}

QWidget* MainWindow::popView() {
	
	QWidget* top = viewStack->currentWidget();
	
	viewStack->removeWidget(top);
	
	return top;
	
}

MainWindow::~MainWindow() {
    
}




void MainWindow::createToolbars() {

    tbAmpControl = addToolBar(tr("Amp Control"));

}