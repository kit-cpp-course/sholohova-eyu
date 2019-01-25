#pragma once

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

class EnterPathDialog : public QDialog
{
	Q_OBJECT
private:
	QLabel *lblName;
	QLineEdit *editName;
	QLabel *lblPath;
	QLineEdit *editPath;
	//� QLineEdit ����� �������� RegExp

	QDialogButtonBox *dlgButtons;

	QHBoxLayout *dlgHNameLayout;
	QHBoxLayout *dlgHPathLayout;
	QVBoxLayout *dlgLayout;
	QString dirName;
	/*QPushButton *butAdd;
	QPushButton *butCancel;
	QHBoxLayout *dlgButLayout;*/
public:
	EnterPathDialog(QWidget *parent = Q_NULLPTR);
	~EnterPathDialog();
private slots:
	void GenerateClicked();// ������ �������� ���������� �� ������ � ���-�� ���������� �����
};
