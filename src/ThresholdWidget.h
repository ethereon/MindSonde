/*
 ================================================================
 
 Threshold Widget
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */


#ifndef __THRESHOLD_WIDGET_H__
#define __THRESHOLD_WIDGET_H__

#include <QtGui>

class ThresholdWidget : public QWidget {
	
	Q_OBJECT
	
private:
	
	QLabel txtTitle;
	QLabel txtValue;
	
	double threshold;
	
	QPalette belowThreshold;
	QPalette aboveThreshold;
	
public:
	
	ThresholdWidget(QWidget* parent=0);
	~ThresholdWidget();
	
	void setTitle(const QString& txt);
	void setValue(double argValue);
	
	void setThreshold(double argTreshold);
	
};


#endif