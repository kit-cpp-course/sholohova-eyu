#include "QtMediaCatalog.h"
#include "EnterPathDialog.h"
#include "EnterDirNameDialog.h"
#include <QHeaderView>
#include <QInputDialog>
#include <QRegExp>
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
	butAddToDir->setEnabled(false);
	butGenerateCat = new QPushButton("Generate Media Catalog", mainWdgt);
	butGenerateCat->setEnabled(false);
	butFilter = new QPushButton("Filter", mainWdgt);
	editFilter = new QLineEdit(mainWdgt);
	editFilter->setPlaceholderText("Enter pattern for search");
	combType = new QComboBox(mainWdgt);
	combType->insertItems(0, QStringList() << "Audio" << "Video");
	editPath = new QLineEdit(mainWdgt);
	editPath->setPlaceholderText("Path to the directory (click \"Browse\"\)");
	editPath->setReadOnly(true);
	editExt = new QLineEdit(mainWdgt);
	editExt->setPlaceholderText("Extensions");
	editExt->setValidator(new QRegExpValidator(QRegExp("([A-Z][a-z]{2,4} )+", Qt::CaseInsensitive)));
	editExt->setText("*.mp3 *.avi *.mkv *.mp4 ");
	treeDirs = new QTreeWidget(mainWdgt);
	treeDirs->setHeaderHidden(true);
	fileTable = new QTableView(mainWdgt);//QTableWidget(1,5,mainWdgt)
	model = Q_NULLPTR;
	//chbDelegate = new CheckBoxDelegate(this);//parent- fileTable?
	//fileTable->setItemDelegateForColumn(0,chbDelegate);
	filterModel = new ProxyModel(this);
	fileTable->setSortingEnabled(true);
	
	fileTable->setFixedHeight(400);
	fileTable->verticalHeader()->hide();
	fileTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	fileTable->setSelectionBehavior(QAbstractItemView::SelectRows);

		//Layout and widgets positioning 
	QGridLayout *mainLayout = new QGridLayout;
	////widgets->append(butAddToDir);
	mainLayout->addWidget(editPath, 0, 0, 1, 4, Qt::AlignVCenter);
	mainLayout->addWidget(butBrowse,0,4);//, Qt::AlignLeft
	//butBrowse->setMaximumWidth(200);
	mainLayout->addWidget(butSearch,0,5);//, Qt::AlignLeft
	//butSearch->setMaximumWidth(200);
	mainLayout->addWidget(editFilter, 2, 0, 1, 2, Qt::AlignVCenter);
	mainLayout->addWidget(combType, 2, 2, Qt::AlignJustify);
	mainLayout->addWidget(butFilter, 2, 3, Qt::AlignRight);
	combType->setGeometry(butFilter->geometry());
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
	//setBaseSize();
	setFixedSize(900, 600);

		//Connecting signals and slots
	connect(this, SIGNAL(pathEntered(QString, QString)), catalog, SLOT(FillCatalog(QString, QString)));
	connect(catalog, SIGNAL(catalogIsReady()), treeDirs, SLOT(clear()));
	connect(catalog, SIGNAL(catalogIsReady()), this, SLOT(UpdateTable()));
	//connect(catalog, SIGNAL(catalogIsReady()), butGenerateCat, SLOT([&] {setEnabled(true); }));
	connect(butBrowse, SIGNAL(clicked()), this, SLOT(OpenFileBrowser()));
	connect(butSearch, SIGNAL(clicked()), this, SLOT(SearchClicked()));
	connect(butAddToDir, SIGNAL(clicked()), this, SLOT(AddClicked()));
	connect(butGenerateCat, SIGNAL(clicked()), this, SLOT(GenerateClicked()));/*
	connect(catalog, SIGNAL(dirsFullUpdate(QStringList)), this, SLOT(UpdateTree(QStringList)));*/
	connect(catalog, SIGNAL(dirAdded(QString)), this, SLOT(AddDirToTree(QString)));
	connect(this, SIGNAL(organizingCompleted(QString)), catalog, SLOT(GenerateCatalog(QString)));
	connect(catalog, SIGNAL(generated(int)), this, SLOT(Generated(int)));
}

void QtMediaCatalog::SearchClicked() {
	qDebug() << "PATH ENTERED"<< editPath->text();
	emit pathEntered("E:/Video", editExt->text()); //(editPath->text());
	//emit pathEntered(editPath->text(), editExt->text());
}
void QtMediaCatalog::UpdateTable()
{
	if (model != Q_NULLPTR) { delete model; } //model->deleteLater();	}
		qDebug() << "INITIALIZING MODEL";
		model = new FileDataModel(this);
		model->setDataSource(catalog);
		filterModel->setSourceModel(model);
		fileTable->setModel(filterModel);
		fileTable->hideColumn(4);
		fileTable->hideColumn(5);
		//fileTable->horizontalHeader()->setMaximumSectionSize(400);
		//fileTable->resizeColumnToContents(0);
		fileTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
		fileTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
		fileTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
		fileTable->horizontalHeader()->resizeSection(0,10);
		fileTable->horizontalHeader()->resizeSection(2, 50);
		fileTable->horizontalHeader()->resizeSection(3, 100);
		fileTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);
		/*fileTable->setColumnWidth(0, 10);
		fileTable->setColumnWidth(2, 50);
		fileTable->setColumnWidth(3, 100);*/
		fileTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
		

	//connect(model, SIGNAL(noFilesChoosen()), butAddToDir, SLOT(setEnabled(false)));//[&] {AddToDir->setEnabled(false); }
	connect(model, SIGNAL(fileChoosen(bool)), butAddToDir, SLOT(setEnabled(bool)));//[&] {AddToDir->setEnabled(true); qDebug() << "LAMBDA"; }
	//separate slot? lambda?

	connect(this, SIGNAL(dirEntered(QString)), model, SLOT(SendFilesList(QString)));
	connect(model, SIGNAL(addFilesToDir(QString, QList<int>)), catalog, SLOT(OrganizeFiles(QString, QList<int>)));
	//calling invalidate() to refresh filter settings
	//we need this when adding files to directory
	//so they should be removed from the view
	connect(catalog, SIGNAL(organized()), filterModel, SLOT(invalidate()));
	connect(editFilter, SIGNAL(textChanged(QString)), filterModel, SLOT(SetSearchString(QString)));
	connect(combType, SIGNAL(currentTextChanged(QString)), filterModel, SLOT(SetFileType(QString)));
	connect(fileTable, SIGNAL(clicked(const QModelIndex &)), filterModel, SLOT(OnCellClicked(const QModelIndex &)));
	connect(filterModel, SIGNAL(srcCellClicked(const QModelIndex &)), model, SLOT(OnCellClicked(const QModelIndex &)));
}
void QtMediaCatalog::UpdateTree(QStringList dirs)
{
	// for full update
	qDebug() << "UPDATING TREE";
	QList<QTreeWidgetItem*> dirsTmp;

	for each (QString str in dirs)
	{	
		QTreeWidgetItem *item = new QTreeWidgetItem();
		item->setText(0, str);
		dirsTmp.append(item);
	}
	treeDirs->addTopLevelItems(dirsTmp);
}
void QtMediaCatalog::AddDirToTree(QString dirName)
{
	
	qDebug() << "ADDING DIR TO TREE";
	
	dirName.replace("\\", "/");
	QStringList dirsTmp = dirName.split("/");

	// if it's a top level item - add to tree
	QTreeWidgetItem* parentItem = Q_NULLPTR;
	if (treeDirs->findItems(dirsTmp[0], Qt::MatchFixedString | Qt::MatchCaseSensitive).isEmpty())
	{
		QTreeWidgetItem* temp;
		temp = new QTreeWidgetItem();
		temp->setText(0, dirsTmp[0]);
		treeDirs->addTopLevelItem(temp);
		treeDirs->expandItem(temp);
		qDebug() << "ROOT DIR ADDED" << dirsTmp[0];
		//parentItem = temp;
	}
	//if not, we should find it's root node
	//rootItems[j]->text(0) - 1st column
	QList<QTreeWidgetItem*> rootItems = treeDirs->findItems(dirsTmp[0], Qt::MatchFixedString | Qt::MatchCaseSensitive); 
	for(int j = 0; j<rootItems.size(); j++){
		
		if(rootItems[j]->text(0)== dirsTmp[0])	{ 
			parentItem = rootItems[j];
			break;
		}		
	}
	for(int i=1; i<dirsTmp.size();i++)
	{
		bool parentFound = false;
		for (int j = 0; j<parentItem->childCount(); j++) {
			
			if (parentItem->child(j)->text(0) == dirsTmp[i])
			{	
				parentItem = parentItem->child(j); 
				parentFound = true;
				break;
			}						
		}
		if(!parentFound){		
			QTreeWidgetItem* temp;
			temp = new QTreeWidgetItem();
			temp->setText(0, dirsTmp[i]);
			parentItem->addChild(temp);
			treeDirs->expandItem(temp);
			parentItem = temp;
			qDebug() << "DIR ADDED";
		}
	}
	//where to place this: (maybe separate slot so it depends on number of dirs)
	//not working if new search is done
	if(treeDirs->topLevelItemCount()!=0)
		butGenerateCat->setEnabled(true);
	else 
		butGenerateCat->setEnabled(false);
			
}
void QtMediaCatalog::Generated(int fails)
{
	QMessageBox *msgBox = new QMessageBox(QMessageBox::NoIcon, "Finished",
		QString("Mediacatalog is generated. \n Fail to copy %1 files.").arg(QString::number(fails)),
		QMessageBox::Ok, this);
	msgBox->exec();
}
void QtMediaCatalog::OpenFileBrowser() {
	qDebug() << "OPEN FILE DIALOG";
	/*QFileDialog *fileBrowser = new QFileDialog(this, tr("Choose Directory"));
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
	//bool ok;
	//// добавить проверку вводимого значения с помощью регэксп (условия по именованию папок! В ОТЧЕТ в теор часть)
	//QString dirName = QInputDialog::getText(this, "Input Dialog", "Enter directory name", QLineEdit::Normal, QString(), &ok);
	//if (ok && !dirName.isEmpty())
	//	emit dirEntered(dirName);
	//;



	EnterDirNameDialog* inputDlg = new EnterDirNameDialog(this);
	if(inputDlg->exec()==QDialog::Accepted)
	{
		QString dirName = inputDlg->GetDirName();
		//перенести проверку на пустую строку в класс диалога
		if (!dirName.isEmpty()) emit dirEntered(dirName);
	}

	//connect(butAdd, SIGNAL(clicked()), editName,SLOT)
	//проверять ввели или не ввели (отмена или ок)
	// как вообще возвращать значение из диалога? по кнопке ok сигналом в слот?
	
}

void QtMediaCatalog::GenerateClicked()
{
	//заменить на кастомный диалог с проверкой вводимой директории
	// и вводом имени каталога
	QString catalogPath = QFileDialog::getExistingDirectory(this, tr("Choose directory or create new"), "C:/",
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);
	if (!catalogPath.isEmpty()) {
		emit organizingCompleted(catalogPath);
		qDebug() << "SIGNAL EMITTED";
	}
}
