/*
 ================================================================
 
 SourceConfig
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */


#include "SourceConfig.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QIntValidator>
#include "BooleanParameter.h"
#include "EnumParameter.h"
#include "IntegerParameter.h"
#include <string>
#include <sstream>
#include "MainWindow.h"

using namespace std;

string integerToString(const long& v) {
	
	ostringstream str;
	str << v;
	return str.str();
	
}

SourceConfig::SourceConfig(SignalSource* src, QWidget* parent) : QWidget(parent)
{
	
	this->source = src;
	
	constructUI();
	setup();


}

void SourceConfig::setup() {
	

	layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignCenter);
	this->setLayout(layout);
	
	//Add the parameters group box
	layout->addWidget(this->paramGroup);
	
	//Add the buttons
	QWidget* btnContainer = new QWidget(this);
	QPushButton* btnCancel = new QPushButton(btnContainer);
	QPushButton* btnStart = new QPushButton(btnContainer);
	QHBoxLayout* btnLayout = new QHBoxLayout(btnContainer);
	btnLayout->addStretch();
	btnLayout->addWidget(btnCancel);
	btnLayout->addWidget(btnStart);
	btnContainer->setLayout(btnLayout);
	
	btnCancel->setText("Cancel");
	btnStart->setText("Start");

	//Set Max Width
	paramGroup->setMaximumWidth(400);
	btnContainer->setMaximumWidth(400);
	
	layout->addWidget(btnContainer);
	
	//Make connections
	QObject::connect(btnCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
	QObject::connect(btnStart, SIGNAL(clicked()), this, SLOT(onStart()));

}

void SourceConfig::syncParameters() {
	
	ParameterSet* params = this->source->getParameters();
	
	int i=0;

	for(Parameter* p = params->first(); p!=NULL; p = params->next()) {
		
		QWidget* f = fields[i];
		
		if(IntegerParameter* ip = dynamic_cast<IntegerParameter*>(p)) {
		
			
			ip->setValue(((QLineEdit*)f)->text().toLong());
		
		}
		else if(BooleanParameter* bp = dynamic_cast<BooleanParameter*>(p)) {
			
			bp->setValue(((QCheckBox*)f)->isChecked());
			
		}
		else if(EnumParameter* ep = dynamic_cast<EnumParameter*>(p)) {
			
			
			
		}
		
		++i;

	}
	
}

void SourceConfig::onStart() {
	
	syncParameters();

	
}

void SourceConfig::onCancel() {
	
	MainWindow::Instance()->popView();
	delete this;
	
}

void SourceConfig::addParamField(QWidget* f, Parameter* p) {
	
	paramLayout->addRow(p->getTitle(), f);
	fields.push_back(f);
	
}

void SourceConfig::constructUI() {

	paramGroup = new QGroupBox(this);
	
	string title = "Configure : " + string(this->source->getName());
	paramGroup->setTitle(title.c_str());
	
	paramLayout = new QFormLayout(paramGroup);
	
	ParameterSet* params = this->source->getParameters();
	
	for(Parameter* p = params->first(); p!=NULL; p = params->next()) {
		
		
		if(IntegerParameter* ip = dynamic_cast<IntegerParameter*>(p)) {
			
			QLineEdit* lineEdit = new QLineEdit(paramGroup);
			lineEdit->setText(integerToString(ip->getValue()).c_str());
			lineEdit->setValidator(new QIntValidator(lineEdit));
			
			addParamField(lineEdit, ip);
		}
		else if(BooleanParameter* bp = dynamic_cast<BooleanParameter*>(p)) {
			
			QCheckBox* checkbox = new QCheckBox(paramGroup);
			
			addParamField(checkbox, bp);
			
		}
		else if(EnumParameter* ep = dynamic_cast<EnumParameter*>(p)) {
			
			
			
		}
		
	}
	

}