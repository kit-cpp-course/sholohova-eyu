#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class EnterPathDialog : public QDialog
{
	Q_OBJECT

public:
	EnterPathDialog(QWidget *parent = Q_NULLPTR);
	~EnterPathDialog();
private:
	QLabel *lblDir;
	QLineEdit *editDir;
	QHBoxLayout *dlgHLayout;

	QPushButton *butAdd;
	QPushButton *butCancel;
	QHBoxLayout *dlgButLayout;
	QVBoxLayout *dlgLayout;
	QString dirName;
};
