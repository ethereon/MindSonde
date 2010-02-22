/*
 ================================================================
 
 Parameter
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#ifndef __MINDSONDE_PARAMETER_H__
#define __MINDSONDE_PARAMETER_H__

#include <string>
#include <QtGui>

class Parameter : public QObject {
	
	Q_OBJECT
	
private:
	
	std::string name;
	std::string title;
	
public:
	
	Parameter() {}
	virtual ~Parameter() {}
	
	void setName(std::string argName) { name = argName; }
	void setTitle(std::string argTitle) { title = argTitle; }
	
	const char* getName() { return name.c_str(); }
	const char* getTitle() { return title.c_str(); }

};


#endif