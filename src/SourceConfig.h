/*
 ================================================================
 
 SourceConfig
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */


#ifndef __SOURCE_CONFIG_H__
#define __SOURCE_CONFIG_H__

#include <QWidget>
#include "SignalSource.h"
#include <vector>
#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>

class SourceConfig : public QWidget {

	Q_OBJECT
	
private slots:

	void onCancel();
	void onStart();
	
private:
	
	SignalSource* source;
	
	QGroupBox* paramGroup;
	QVBoxLayout* layout;
	QFormLayout* paramLayout;
	
	std::vector<QWidget*> fields;
	
	void constructUI();
	void setup();
	void syncParameters();
	void addParamField(QWidget* f, Parameter* p);
	
public:

	SourceConfig(SignalSource* src, QWidget* parent = 0);


	
};
#endif