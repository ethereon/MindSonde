/*
 ================================================================
 
 Parameter Renderer
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */


#ifndef __PARAMETER_RENDERER_H__
#define __PARAMETER_RENDERER_H__

#include <QtGui>
#include "ParameterSet.h"

class ParameterRenderer {
	
private:
	
	ParameterRenderer() {}
	
public:
		
	static void generateUI(QWidget* host, ParameterSet* params);
	static QDialog* createParameterDialog(ParameterSet* params, QWidget* parent);
	
};

#endif