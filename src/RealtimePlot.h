/*
 ================================================================
 
 RealtimePlot
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __REALTIME_PLOT_H__
#define __REALTIME_PLOT_H__

#include <qwt/qwt_plot.h>

class RealtimePlot : public QwtPlot {

	Q_OBJECT
	
public:
	
	RealtimePlot(QWidget* parent = NULL);
	
private:
	
	int timerInterval;

	
};

#endif