/*
 ================================================================
 
 SourceSelectionView
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */


#include "SourceSelectionView.h"
#include <QtGui>
#include "SourceDiscovery.h"
#include <vector>
#include "SignalSource.h"
#include "MainWindow.h"
#include "MindSondeUtil.h"
#include "MException.h"

using namespace std;

//-----------------------------------------------------------------------------

SourceSelectionView::SourceSelectionView(QWidget *parent) : View(parent)
{
	configView = NULL;
	
	constructUI();
	populateSources();

}

//-----------------------------------------------------------------------------

void SourceSelectionView::refreshSources() {
	
	sourceList->clear();
	signalSources.clear();
	
	populateSources();
	
}

//-----------------------------------------------------------------------------

void SourceSelectionView::showConfigurationDialog()
{

	SignalSource* selectedSource = signalSources[sourceList->currentRow()];

	try {
		
		selectedSource->connect();
				
		configView = new SourceConfigView(selectedSource, this);
		MainWindow::Instance()->pushView(configView);	
				
	}
	catch (MException e) {
		
		displayException(&e, "Unable to connected to the selected signal source");
		
		
	}
	
}

//-----------------------------------------------------------------------------

void SourceSelectionView::populateSources() {
	
	SourceDiscovery* s = SourceDiscovery::Instance();
	
	
	s->getSources(&signalSources);
	
	for(unsigned i=0;i<signalSources.size(); ++i) {
		
		SignalSource* src = signalSources[i];
		new QListWidgetItem(src->getName(), sourceList);
		
		
	}
	
	sourceList->setSelectionMode(QAbstractItemView::SingleSelection);
	sourceList->setCurrentRow(0);	
}

//-----------------------------------------------------------------------------

void SourceSelectionView::constructUI() {

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
	QObject::connect(btnRefresh, SIGNAL(clicked()), this, SLOT(refreshSources()));

	

}

//-----------------------------------------------------------------------------

void SourceSelectionView::setup() {

}

//-----------------------------------------------------------------------------

void SourceSelectionView::cleanup() {

}

//-----------------------------------------------------------------------------