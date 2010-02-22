/*
 ================================================================
 
 SourceConfigView
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */


#ifndef __SOURCE_CONFIG_H__
#define __SOURCE_CONFIG_H__

#include "View.h"
#include "SignalSource.h"
#include <vector>


class SourceConfigView : public View {

	Q_OBJECT
	
private slots:

	void onCancel();
	void onStart();
	
private:
	
	SignalSource* source;
	
	QGroupBox* paramGroup;
	QGroupBox* fileOutputGroup;
	
	QLineEdit* outputPathEdit;
	QCheckBox* saveDataCheckbox;

	QVBoxLayout* layout;

	
	void constructUI();
	void generateParamInterface();
	void setupFileOutputGroup();
	
	
public:

	SourceConfigView(SignalSource* src, QWidget* parent = 0);
	
	void setup();
	void cleanup();


	
};
#endif