/*
 ================================================================
 
 View
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __MINDSONDE_VIEW_H__
#define __MINDSONDE_VIEW_H__

#include <QtGui>

class View : public QWidget{
	
		Q_OBJECT
	
public:
	
	View(QWidget* parent) : QWidget(parent) {}
	virtual ~View() {}
	
	virtual void setup()=0;
	virtual void cleanup()=0;
	
};

#endif