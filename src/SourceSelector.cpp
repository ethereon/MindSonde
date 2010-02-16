/*
 ================================================================
 
 SourceSelector
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */


#include "SourceSelector.h"
#include <QtGui>
#include "SourceDiscovery.h"
#include <vector>
#include "SignalSource.h"
#include "SourceConfig.h"
#include "MainWindow.h"

using namespace std;

SourceSelector::SourceSelector(QWidget *parent) : QWidget(parent)
{
	
	setup();
	populateSources();

}

void SourceSelector::showConfigurationDialog()
{


	SourceConfig* cfgDialog = new SourceConfig(signalSources[sourceList->currentRow()], this);
	MainWindow::Instance()->pushView(cfgDialog);
	
	
}

void SourceSelector::populateSources() {
	
	SourceDiscovery* s = SourceDiscovery::Instance();
	
	
	s->getSources(&signalSources);
	
	for(unsigned i=0;i<signalSources.size(); ++i) {
		
		SignalSource* src = signalSources[i];
		new QListWidgetItem(src->getName(), sourceList);
		
		
	}
	
	sourceList->setSelectionMode(QAbstractItemView::SingleSelection);
	sourceList->setCurrentRow(0);	
}

void SourceSelector::setup() {

	//Create paramLayout
	QVBoxLayout *paramLayout = new QVBoxLayout;
	paramLayout->setAlignment(Qt::AlignCenter);
	this->setLayout(paramLayout);
	
	QGroupBox* srcGroup = new QGroupBox(this);
	srcGroup->setTitle(tr("Available Signal Sources"));
	srcGroup->setAlignment(Qt::AlignCenter);
	srcGroup->setMaximumSize(300, 400);
	
	QVBoxLayout* vbox = new QVBoxLayout;
	srcGroup->setLayout(vbox);
	
	//Create source list
	sourceList = new QListWidget;
	vbox->addWidget(sourceList);
	
	
	//Create the buttons
	QPushButton* btnConnect = new QPushButton(tr("Connect"));
	QPushButton* btnRefresh = new QPushButton(tr("Refresh"));
	
	QHBoxLayout* buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(btnConnect);	
	buttonLayout->addWidget(btnRefresh);
	
	vbox->addLayout(buttonLayout);
	
	paramLayout->addWidget(srcGroup);

	
	//Make conections
	
	QObject::connect(btnConnect, SIGNAL(clicked()), this, SLOT(showConfigurationDialog()));
	

}