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
	//в QLineEdit нужно добавить RegExp
	QHBoxLayout *dlgHLayout;
	QDialogButtonBox *dlgButtons;
	QVBoxLayout *dlgLayout;
	QString dirName;
public:
	EnterDirNameDialog(QWidget *parent);
	~EnterDirNameDialog();
	QString GetDirName() { return dirName;};
private slots:
	void AddClicked();// внутри проверка имени на наличие / \ и вывод предупреждающего сообщения
};
