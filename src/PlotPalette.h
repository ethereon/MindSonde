/*
 ================================================================
 
 PlotPalette
 MindSonde / The Myelin Project
 
 A class for representing a plot's color scheme.
 Default scheme based on the Tango Palette.
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */


#ifndef __PLOT_PALETTE_H__
#define __PLOT_PALETTE_H__

#include <QtGui>



class PlotPalette {
	
private:
	
	QColor backgroundColor;
	QColor* curveColors;
	
	int curveColorCount;
	
public:
	
	PlotPalette() {
		
		backgroundColor = QColor(0,0,0);
		curveColorCount = 7;
		curveColors = new QColor[curveColorCount];
		
		curveColors[0] = QColor(252,233,79);
		curveColors[1] = QColor(252,175,62);
		curveColors[2] = QColor(233,185,110);
		curveColors[3] = QColor(138,226,52);
		curveColors[4] = QColor(114,159,207);
		curveColors[5] = QColor(173,127,168);
		curveColors[6] = QColor(239,41,41);
	}
	
	virtual ~PlotPalette() {
		
		delete [] curveColors;
	}
	
	
	QColor getBackgroundColor() {
		
		return backgroundColor;
		
	}
	
	QColor getCurveColor(int i) {
	
		return curveColors[i%curveColorCount];
	}
	
};

#endif