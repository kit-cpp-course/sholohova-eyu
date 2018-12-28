#include "EnterPathDialog.h"

EnterPathDialog::EnterPathDialog(QWidget *parent)
	: QDialog(parent)
{
	lblDir = new QLabel("Enter directory name: ", this);
	editDir = new QLineEdit(this);
	dlgHLayout = new QHBoxLayout;
	dlgHLayout->addWidget(lblDir);
	dlgHLayout->addWidget(editDir);
	butAdd = new QPushButton("Add", this);
	QPushButton *butCancel = new QPushButton("Cancel", this);
	dlgButLayout = new QHBoxLayout;
	dlgButLayout->addWidget(butAdd);
	dlgButLayout->addWidget(butCancel);
	dlgLayout = new QVBoxLayout;
	dlgLayout->addLayout(dlgHLayout);
	dlgLayout->addLayout(dlgButLayout);
	setLayout(dlgLayout);
	QString dirName;
}

EnterPathDialog::~EnterPathDialog()
{
}
