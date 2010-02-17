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

#include <string>
#include <sstream>

#include "BooleanParameter.h"
#include "EnumParameter.h"
#include "IntegerParameter.h"
#include "MainWindow.h"
#include "SignalView.h"
#include "MindSondeApp.h"
#include "AcquisitionCentral.h"

using namespace std;

string integerToString(const long& v) {
	
	ostringstream str;
	str << v;
	return str.str();
	
}

SourceConfig::SourceConfig(SignalSource* src, QWidget* parent) : View(parent)
{
	
	this->source = src;
	
	generateParamInterface();
	constructUI();


}

void SourceConfig::constructUI() {
	

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
	
	//Synchronize tha ParameterSet with the user entered values
	syncParameters();
	
	//Tell the source to configure itself with the entered parameters
	source->configure();
	
	//Tell the source to start acquisition
	source->start();
	
	//Create a Source Proxy
	//TODO: Refactor this. Make sure it gets freed later.
	SourceProxy* proxy = new SourceProxy();
	proxy->setSignalSource(this->source);
	
	//Create a Signal View
	SignalView*	signalView = new SignalView();
	signalView->setSourceProxy(proxy);
	
	//Setup the Acquisition Center and tell it to start broadcasting data
	AcquisitionCentral::Instance()->setSignalSource(this->source);
	AcquisitionCentral::Instance()->subscribe();
	AcquisitionCentral::Instance()->start();

	MainWindow::Instance()->pushView(signalView);

	
}

void SourceConfig::onCancel() {
	
	source->disconnect();
	MainWindow::Instance()->popView();
	delete this;
	
}

void SourceConfig::addParamField(QWidget* f, Parameter* p) {
	
	paramLayout->addRow(p->getTitle(), f);
	fields.push_back(f);
	
}

void SourceConfig::generateParamInterface() {

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
			checkbox->setChecked(bp->getValue());
			addParamField(checkbox, bp);
			
		}
		else if(EnumParameter* ep = dynamic_cast<EnumParameter*>(p)) {
			
			
		}
		
	}	

}

void SourceConfig::setup() {
	
	

}

void SourceConfig::cleanup() {

}