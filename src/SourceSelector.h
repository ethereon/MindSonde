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

#include "View.h"
#include "SignalSource.h"
#include <vector>

class SourceSelector : public View {

	Q_OBJECT

private slots:
	
	void showConfigurationDialog();
	
private:
	
	
	QListWidget* sourceList;
	std::vector<SignalSource*> signalSources;
	
	void constructUI();
	void populateSources();
	
public:
	
	SourceSelector(QWidget* parent = 0);
	
	void setup();
	void cleanup();


};

#endif