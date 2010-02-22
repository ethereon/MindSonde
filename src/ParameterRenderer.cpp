/*
 ================================================================
 
 Parameter Renderer
 MindSonde / The Myelin Project
 
 Copyright (C) 2010 Saumitro Dasgupta.
 This code is made available under the MIT License.
 <http://www.opensource.org/licenses/mit-license.html>
 
 ================================================================
 */

#include "ParameterRenderer.h"
#include "IntegerParameter.h"
#include "EnumParameter.h"
#include "BooleanParameter.h"
#include "ParameterGroup.h"
#include "MindSondeUtil.h"
#include <string>
#include <vector>

using namespace std;

QDialog* ParameterRenderer::createParameterDialog(ParameterSet* params, QWidget* parent) {
		
	QDialog* dialog = new QDialog(parent);

	QVBoxLayout* vbox = new QVBoxLayout(dialog);
	dialog->setLayout(vbox);

	QGroupBox* groupBox = new QGroupBox(dialog);
	vbox->addWidget(groupBox);
	
	QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal, dialog);
	vbox->addWidget(buttonBox);
	
	QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
	
	ParameterRenderer::generateUI(groupBox, params);
	
	return dialog;
	
	
	
}

void ParameterRenderer::generateUI(QWidget* host, ParameterSet* params) {
	
	
	QFormLayout* paramLayout = new QFormLayout(host);
	
	for(Parameter* p = params->first(); p!=NULL; p = params->next()) {
		
		
		if(IntegerParameter* ip = dynamic_cast<IntegerParameter*>(p)) {
			
			QLineEdit* lineEdit = new QLineEdit(host);
			lineEdit->setText(integerToString(ip->getValue()).c_str());
			lineEdit->setValidator(new QIntValidator(lineEdit));
			
			paramLayout->addRow(ip->getTitle(), lineEdit);
			
			QObject::connect(lineEdit, SIGNAL(textChanged(const QString&)), ip, SLOT(updateValue(const QString&)));
			
			
		}
		else if(BooleanParameter* bp = dynamic_cast<BooleanParameter*>(p)) {
			
			QCheckBox* checkbox = new QCheckBox(host);
			checkbox->setChecked(bp->getValue());
			
			paramLayout->addRow(bp->getTitle(), checkbox);
			
			QObject::connect(checkbox, SIGNAL(stateChanged (int)), bp, SLOT(updateValue(int)));
			
			
		}
		else if(EnumParameter* ep = dynamic_cast<EnumParameter*>(p)) {
			
			const vector<string> options = ep->getOptions();
			
			QComboBox* combo = new QComboBox(host);
			
			for(unsigned i=0;i<options.size();++i)
				combo->addItem(options[i].c_str());
			
			paramLayout->addRow(ep->getTitle(), combo);
			
			QObject::connect(combo, SIGNAL(currentIndexChanged(int)), ep, SLOT(updateValue(int)));
			
		} else if (ParameterGroup* pg = dynamic_cast<ParameterGroup*>(p)) {
			
			QPushButton* configButton = new QPushButton(host);
			configButton->setText("Configure...");
			paramLayout->addRow(pg->getTitle(), configButton);
			
			QDialog* dialog = ParameterRenderer::createParameterDialog(pg->getParameterSet(), host);
			
			dialog->setWindowTitle(pg->getTitle());
			QObject::connect(configButton,SIGNAL(clicked()), dialog, SLOT(exec()));
			
		}
		
	}	
	
	
	
}