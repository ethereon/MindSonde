/*
 ================================================================
 
 SourceConfigView
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */


#include "SourceConfigView.h"
#include "MainWindow.h"
#include "MindSondeApp.h"
#include "MindSondeUtil.h"
#include "FileOutputDaemon.h"
#include "InterleavedDataSerializer.h"
#include "ParameterRenderer.h"

using namespace std;

#define COMMON_WIDTH 600

SourceConfigView::SourceConfigView(SignalSource* src, QWidget* parent) : View(parent)
{
	
	this->source = src;
	
	generateParamInterface();
	setupFileOutputGroup();
	constructUI();


}


void SourceConfigView::constructUI() {
	

	layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignCenter);
	this->setLayout(layout);
	
	//Add the parameters group box
	layout->addWidget(this->paramGroup);
	
	//Add the file output group box
	layout->addWidget(this->fileOutputGroup);
	
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
	paramGroup->setMaximumWidth(COMMON_WIDTH);
	fileOutputGroup->setMaximumWidth(COMMON_WIDTH);
	btnContainer->setMaximumWidth(COMMON_WIDTH);
	
	
	layout->addWidget(btnContainer);
	
	//Make connections
	QObject::connect(btnCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
	QObject::connect(btnStart, SIGNAL(clicked()), this, SLOT(onStart()));

}

void SourceConfigView::setupFileOutputGroup() {
	
	fileOutputGroup = new QGroupBox(this);
	fileOutputGroup->setTitle("File output");
	
	outputPathEdit = new QLineEdit;
	
	QFormLayout* formLayout = new QFormLayout(fileOutputGroup);
	formLayout->addRow("File path", outputPathEdit);
	
	QDir dir(QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation));
	QDateTime currentTime = QDateTime::currentDateTime();
	QString filename = "Data_" + currentTime.toString("yyyy_MM_hh_mm") + ".dat";
	
	outputPathEdit->setText(dir.filePath(filename));

	saveDataCheckbox = new QCheckBox(this);
	formLayout->addRow("Save data to file", saveDataCheckbox);
	
	fileOutputGroup->setLayout(formLayout);
	
	
	
}


void SourceConfigView::onStart() {
	
	//Tell the source to configure itself with the entered parameters
	source->configure();
	
	//Configure file output
	if(saveDataCheckbox->isChecked()) {
		
		QString enteredPath = outputPathEdit->text();
		QByteArray ba = enteredPath.toLatin1();
		const char *c_str = ba.data();
		

		InterleavedDataSerializer* dataSerializer = new InterleavedDataSerializer();
		dataSerializer->openFile(c_str);
		dataSerializer->writeHeader(source);
		FileOutputDaemon* fileDaemon = new FileOutputDaemon(dataSerializer);
		MindSondeApp::Instance()->setFileOutputDaemon(fileDaemon);
		
	} else {
		
		MindSondeApp::Instance()->setFileOutputDaemon(NULL);
		
	}
	
	
	
	//Enter acquisition mode
	MindSondeApp::Instance()->setActiveSource(source);
	MindSondeApp::Instance()->startAcquisition();
	

	
}

void SourceConfigView::onCancel() {
	
	source->disconnect();
	MainWindow::Instance()->popView();

	
}


void SourceConfigView::generateParamInterface() {

	paramGroup = new QGroupBox(this);	
	string title = "Configure : " + string(this->source->getName());
	paramGroup->setTitle(title.c_str());
	
	ParameterRenderer::generateUI(paramGroup, source->getParameters());


}

void SourceConfigView::setup() {
	
	

}

void SourceConfigView::cleanup() {

}