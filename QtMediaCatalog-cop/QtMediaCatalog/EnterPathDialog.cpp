#include "EnterPathDialog.h"

EnterPathDialog::EnterPathDialog(QWidget *parent)
	: QDialog(parent)
{
		//Widgets
	lblName = new QLabel("Enter directory name: ", this);
	editName = new QLineEdit(this);
	//в QLineEdit нужно добавить RegExp


	lblPath = new QLabel("Enter path: ", this);
	editPath = new QLineEdit(this);
	dlgButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
	dlgButtons->button(QDialogButtonBox::Ok)->setText("Generate");
	/*butAdd = new QPushButton("Add", this);
	butCancel = new QPushButton("Cancel", this);*/

			//Layouts
	dlgHNameLayout = new QHBoxLayout;
	dlgHNameLayout->addWidget(lblName);
	dlgHNameLayout->addWidget(editName);
	/*dlgButLayout = new QHBoxLayout;
	dlgButLayout->addWidget(butAdd);
	dlgButLayout->addWidget(butCancel);*/
	//dlgLayout->addLayout(dlgButLayout);
	dlgHPathLayout = new QHBoxLayout;
	dlgHPathLayout->addWidget(lblPath);
	dlgHPathLayout->addWidget(editPath);
	dlgLayout = new QVBoxLayout;
	dlgLayout->addLayout(dlgHNameLayout);
	dlgLayout->addLayout(dlgHPathLayout);
	dlgLayout->addWidget(dlgButtons);
	setLayout(dlgLayout);
	dirName = "";
	connect(dlgButtons, SIGNAL(accepted()), this, SLOT(GenerateClicked()));
	connect(dlgButtons, SIGNAL(rejected()), this, SLOT(reject()));
}

EnterPathDialog::~EnterPathDialog()
{
}

void EnterPathDialog::GenerateClicked()
{

	accept();
}
