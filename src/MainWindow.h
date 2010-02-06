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


#include <QMainWindow>
#include <QPainter>
#include <QAction>
#include <QStackedWidget>
#include "SourceSelector.h"

class MainWindow : public QMainWindow {

    Q_OBJECT

private:

	//Singleton pointer
	static MainWindow* instance;
	
    //Toolbars
    QToolBar *tbAmpControl;

    //Actions
    QAction* axnToggleAmpState;

	SourceSelector* srcSelector;
	
	QStackedWidget* viewStack;
	
    void createToolbars();


	MainWindow();
	
public:

	static MainWindow* Instance();
	
	void pushView(QWidget* argView);
	QWidget* popView();

    ~MainWindow();



};

#endif	/* _MAINWINDOW_H */

