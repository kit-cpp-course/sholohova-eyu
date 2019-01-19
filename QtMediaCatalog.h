#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtMediaCatalog.h"
#include "FileDataModel.h"
#include "CheckBoxDelegate.h"
#include "ProxyModel.h"
#include <QStandardItemModel>

#include "qlayout.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include "qtreewidget.h"
#include "qtableview.h"
#include "qlist.h"
#include "Catalog.h"

class QtMediaCatalog : public QMainWindow
{
	Q_OBJECT

public:
	QtMediaCatalog(QWidget *parent = Q_NULLPTR);
private:
	Ui::QtMediaCatalogClass ui;
	QPushButton *butBrowse;
	QPushButton *butSearch;
	QPushButton *butAddToDir;
	QPushButton *butGenerateCat;
	QPushButton *butFilter;
	QLineEdit *editPath;
	QLineEdit *editExt;
	QLineEdit *editFilter;
	QComboBox *combType;
	QTableView *fileTable;
	QTreeWidget *treeDirs;
	FileDataModel *model;
	CheckBoxDelegate *chbDelegate;
	ProxyModel *filterModel;
	Catalog* catalog;
signals:
	//void BrowseClicked();
	void pathEntered(QString pathToDir, QString extensions = "");
	void dirEntered(QString dirName);
	void organizingCompleted(QString pathToCat);

public slots:
	void UpdateTable();//Catalog* catalog
	void UpdateTree(QStringList dirs);//Qlist из Catalog
	void AddDirToTree(QString dirName);
	void Generated(int fails);
private slots :
	void SearchClicked();
	void OpenFileBrowser();//?возвращать QString?
	void AddClicked();
	void GenerateClicked();
	/*void AddFileToCat();
	void GenerateCatalog();*/
};
//Catalog *dataSource;
//void setDataSource(Catalog *source);