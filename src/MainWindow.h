/*
 ================================================================
 
 MainWindow
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __MAINWINDOW_H__
#define	__MAINWINDOW_H__


#include <QtGui>

#include "SourceSelectionView.h"
#include "View.h"
#include <vector>

class MainWindow : public QMainWindow {

    Q_OBJECT

private:

	static MainWindow* instance;
	
    QAction* axnToggleAmpState;
	
    void createToolbars();

	QStackedWidget* viewTray;
	
	std::vector<View*> viewStack;

	MainWindow();
	
public:

	static MainWindow* Instance();
	
    ~MainWindow();
	
	void pushView(View* view);
	View* popView();
	View* replaceTopView(View* view);

};

#endif

