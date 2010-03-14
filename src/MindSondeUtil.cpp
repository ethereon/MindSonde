/*
 ================================================================
 
 Utility Functions
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "MindSondeUtil.h"


#include <sstream>
#include <QtGui>

using namespace std;

//-----------------------------------------------------------------------------

string integerToString(const long& v) {
	
	stringstream str;
	str << v;
	return str.str();
	
}

//-----------------------------------------------------------------------------

string floatToString(const float& v) {
	
	stringstream str;
	str << v;
	return str.str();
	
}

//-----------------------------------------------------------------------------

void displayException(MException* ex, const char* msg) {
	
	QMessageBox msgBox;
	
	if(msg==NULL)
		msg = "MindSonde has encountered a problem.";
	
	msgBox.setText(msg);
	msgBox.setDetailedText(ex->what());
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.exec();

}

//-----------------------------------------------------------------------------