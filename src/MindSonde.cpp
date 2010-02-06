/*
 ================================================================
 
 MindSonde
 The Myelin Project
 
 A robust app for BCI prototyping and EEG acquisition
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include <QtGui>
#include "MainWindow.h"

#define XSTR(name,val) QApplication::translate(name,val)

int main(int argc, char** argv) {

	QApplication app(argc, argv);

	MainWindow* mainWindow = MainWindow::Instance();	

	mainWindow->resize(800,600);
	mainWindow->show();
	mainWindow->setWindowTitle(XSTR("appName","MindSonde"));

	return app.exec();

}
