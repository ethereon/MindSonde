/*
 ================================================================
 
 Threshold Widget
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */



#include "ThresholdWidget.h"

ThresholdWidget::ThresholdWidget(QWidget* parent) : QWidget(parent)

{

	QHBoxLayout* hBox = new QHBoxLayout(this);
	hBox->setSpacing(4);
	this->setLayout(hBox);
	
	hBox->addWidget(&txtTitle);
	hBox->addWidget(&txtValue);
	
	txtTitle.setTextFormat(Qt::RichText);
	txtTitle.setAlignment(Qt::AlignCenter);
	txtValue.setTextFormat(Qt::RichText);
	
	txtTitle.setFrameShape(QFrame::StyledPanel);
	txtValue.setFrameShape(QFrame::StyledPanel);
	txtTitle.setAutoFillBackground(true);
	txtValue.setAutoFillBackground(true);
	
	txtTitle.setStyleSheet("QLabel { font-size : 24px }");
	txtValue.setStyleSheet("QLabel { font-size : 24px }");
	
	setTitle("?");
	setValue(0.0);
	
	belowThreshold = txtTitle.palette();
	aboveThreshold = txtTitle.palette();
	
	belowThreshold.setColor(txtTitle.backgroundRole(), Qt::red);
	belowThreshold.setColor(txtTitle.foregroundRole(), Qt::white);
	
	threshold = 2.0;
}


ThresholdWidget::~ThresholdWidget() {
	
}


void ThresholdWidget::setTitle(const QString& txt) {

	txtTitle.setText(txt);


}

void ThresholdWidget::setValue(double argValue) {
	
	txtValue.setText(QString::number(argValue));
	
	if(argValue>threshold) {
		
		txtValue.setPalette(aboveThreshold);
		txtTitle.setPalette(aboveThreshold);
		
	} else {
		
		txtValue.setPalette(belowThreshold);
		txtTitle.setPalette(belowThreshold);
	}

}









 