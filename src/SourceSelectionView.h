/*
 ================================================================
 
 SourceSelectionView
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
#include "SourceConfigView.h"
#include <vector>

class SourceSelectionView : public View {

	Q_OBJECT

private slots:
	
	void showConfigurationDialog();
	void refreshSources();
	
private:
	
	
	QListWidget* sourceList;
	std::vector<SignalSource*> signalSources;
	
	SourceConfigView* configView;
	
	void constructUI();
	void populateSources();
	
public:
	
	SourceSelectionView(QWidget* parent = 0);
	
	void setup();
	void cleanup();


};

#endif