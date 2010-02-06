/*
 ================================================================
 
 SourceSelector
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __SOURCE_SELECTOR_H__
#define __SOURCE_SELECTOR_H__

#include <QWidget>
#include <QListWidget>
#include "SignalSource.h"
#include <vector>

class SourceSelector : public QWidget {

	Q_OBJECT

private slots:
	
	void showConfigurationDialog();
	
private:
	
	
	QListWidget* sourceList;
	std::vector<SignalSource*> signalSources;
	
	void setup();
	void populateSources();
	
public:
	
	SourceSelector(QWidget* parent = 0);


};

#endif