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
	//в QLineEdit нужно добавить RegExp

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
	void GenerateClicked();// внутри проверка разрешения на запись и кол-ва свободного места
};
