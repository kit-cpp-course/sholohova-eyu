#pragma once

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QRegExp>
#include <QRegExpValidator>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

class EnterDirNameDialog : public QDialog
{
	Q_OBJECT
private:
	QLabel *lblName;
	QLineEdit *editName;
	QHBoxLayout *dlgHLayout;
	QDialogButtonBox *dlgButtons;
	QVBoxLayout *dlgLayout;
	QString dirName;
public:
	EnterDirNameDialog(QWidget *parent);
	~EnterDirNameDialog();
	QString GetDirName() { return dirName;};
private slots:
	void AddClicked();
};
