/*
 ================================================================
 
 RealtimePlot
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "RealtimePlot.h"

#include <qwt/qwt_painter.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_plot_canvas.h>

RealtimePlot::RealtimePlot(QWidget* parent): QwtPlot(parent)
{
	

	QwtPainter::setDeviceClipping(false);
	
	//Disable the PaintCached attribute ( double buffered). Also disable
	//the PaintPacked attribute ( enabled = less flicker at the cost of speed).
	//Disabling these two should provide some performance boost.
	canvas()->setPaintAttribute(QwtPlotCanvas::PaintCached, false);
	canvas()->setPaintAttribute(QwtPlotCanvas::PaintPacked, false);

	//No border by default
	canvas()->setLineWidth(0);

}