#include "QtMediaCatalog.h"
#include "EnterPathDialog.h"
#include <QHeaderView>
#include <QInputDialog>
#include <QFileDialog>
#include <QDir>
#include <qDebug>
#pragma once

QtMediaCatalog::QtMediaCatalog(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QWidget *mainWdgt = new QWidget(this);
	catalog = new Catalog();

		//Widgets
	butBrowse = new QPushButton(tr("Browse"), mainWdgt);//?tr
	butSearch = new QPushButton("Search", mainWdgt);
	butAddToDir = new QPushButton("Add To Directory", mainWdgt);
	butGenerateCat = new QPushButton("Generate Media Catalog", mainWdgt);
	butFilter = new QPushButton("Filter", mainWdgt);

	editPath = new QLineEdit("Path to the directory", mainWdgt);
	editPath->setReadOnly(true);
	editExt = new QLineEdit("Extensions", mainWdgt);
	treeDirs = new QTreeWidget(mainWdgt);
	fileTable = new QTableView(mainWdgt);//QTableWidget(1,5,mainWdgt)
	model = Q_NULLPTR;
	chbDelegate = new CheckBoxDelegate(this);//parent- fileTable?
	fileTable->setItemDelegateForColumn(0,chbDelegate);
	filterModel = new QSortFilterProxyModel(this);
	fileTable->setSortingEnabled(true);
	
	fileTable->setFixedHeight(400);
	fileTable->verticalHeader()->hide();
	fileTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	
	QGridLayout *mainLayout = new QGridLayout;
	
	mainLayout->addWidget(editPath, 0, 0, 1, 4, Qt::AlignTop);
	mainLayout->addWidget(butBrowse,0,4);
	mainLayout->addWidget(butSearch,0,5);
	mainLayout->addWidget(butFilter, 2, 3, Qt::AlignRight);
	butFilter->setFixedWidth(100);
	mainLayout->addWidget(editExt, 2, 4, 1, 2);
	mainLayout->addWidget(fileTable, 3, 0, 16, 4);
	mainLayout->addWidget(treeDirs, 3, 4, 16, 2);
	mainLayout->addWidget(butAddToDir,20,0);
	butAddToDir->setFixedWidth(130);
	mainLayout->addWidget(butGenerateCat,20,3);
	
	mainLayout->setAlignment(Qt::AlignTop);
	mainWdgt->setLayout(mainLayout);
	setCentralWidget(mainWdgt);
	setWindowTitle("Media Catalog");
	setFixedSize(900, 600);
	connect(this, SIGNAL(PathEntered(QString)), catalog, SLOT(FillCatalog(QString)));
	connect(catalog, SIGNAL(catalogIsReady()), this, SLOT(UpdateTable()));
	connect(butBrowse, SIGNAL(clicked()), this, SLOT(OpenFileBrowser()));
	connect(butSearch, SIGNAL(clicked()), this, SLOT(SearchClicked()));
	connect(butAddToDir, SIGNAL(clicked()), this, SLOT(AddClicked()));
	/*
	connect(butGenerateCat, SIGNAL(clicked()), this, SLOT(GenerateCatalog()));*/
}

void QtMediaCatalog::SearchClicked() {
	qDebug() << "PATH ENTERED"<< editPath->text();
	emit PathEntered(editPath->text());
	
}
void QtMediaCatalog::UpdateTable()
{
	if (model != Q_NULLPTR)	{	delete model;	} //model->deleteLater();	}
		qDebug() << "INITIALIZING MODEL";
		model = new FileDataModel(this);
		model->setDataSource(catalog);
		fileTable->setModel(model);
}
void QtMediaCatalog::OpenFileBrowser() {
	qDebug() << "OPEN FILE DIALOG";
	/*//Файловый браузер в стиле Qt
	QFileDialog *fileBrowser = new QFileDialog(this, tr("Choose Directory"));
	fileBrowser->setOptions(QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);
	fileBrowser->setFileMode(QFileDialog::Directory);
	fileBrowser->show();
	editPath->setText(fileBrowser->directory().absolutePath());//надо ли  делать exec
	*/
	editPath->setText(QFileDialog::getExistingDirectory(this, tr("Choose Directory"),
		"C:/",
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks));//native file dialog
}

void QtMediaCatalog::AddClicked()
{
	bool ok;
	QString dirName = QInputDialog::getText(this, "Input Dialog", "Enter directory name", QLineEdit::Normal, QString(), &ok);

	if (ok && !dirName.isEmpty())
		emit DirEntered(dirName);
	;
}
