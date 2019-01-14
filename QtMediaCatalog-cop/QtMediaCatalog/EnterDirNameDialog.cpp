#include "EnterDirNameDialog.h"
#include <qDebug>
EnterDirNameDialog::EnterDirNameDialog(QWidget *parent)
	: QDialog(parent)
{
		//Widgets
	lblName = new QLabel("Enter directory name: ", this);
	editName = new QLineEdit(this);
	editName->setValidator(new QRegExpValidator(QRegExp("[^<>:\"|!?*]+(\|/)")));
	//в QLineEdit нужно добавить RegExp
	dlgButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
	dlgButtons->button(QDialogButtonBox::Ok)->setText("Add");
	
		// Layouts
	dlgHLayout = new QHBoxLayout;
	dlgHLayout->addWidget(lblName);
	dlgHLayout->addWidget(editName);
	dlgLayout = new QVBoxLayout;
	dlgLayout->addLayout(dlgHLayout);
	dlgLayout->addWidget(dlgButtons);
	setLayout(dlgLayout);

		//Connecting signals and slots
	connect(dlgButtons, SIGNAL(accepted()), this, SLOT(AddClicked()));
	connect(dlgButtons, &QDialogButtonBox::rejected, this, &QDialog::reject);

	dirName = "";
}

EnterDirNameDialog::~EnterDirNameDialog()
{
}

void EnterDirNameDialog::AddClicked()
{
	QRegularExpression rx(".(\\|/)+.");
	//rx.setPatternSyntax(QRegExp::RegExp);
	//replace all repeated / and \
	//replace / and \ at the beginning and at the end
	//
	dirName = editName->text();
	if ((editName->text().contains(("\\")))||(editName->text().contains(("/")))) //(editName->text().contains(("(\\|/)")))//(rx.indexIn(editName->text())>-1)
	{
		QMessageBox *msgBox = new QMessageBox(QMessageBox::NoIcon, "Add sub directory", 
			"If parent directory doesn't exist it will be created automatically. Accept?", 
			QMessageBox::Ok | QMessageBox::Cancel, this);
		qDebug() << editName->text();
		if (msgBox->exec()== QMessageBox::Ok) { accept(); }
		//else	{ reject();	}
	}
	else
	{ accept(); }
	
}
