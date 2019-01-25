#include "Catalog.h"
#include <QDir>
#include <QStorageInfo>
#include <qDebug>
#include <QRegularExpression>
#pragma once

Catalog::Catalog(QObject *parent)
	: QObject(parent)
{
	n = 0;
	extensions = "*.mp3 *.avi *.mkv *.mp4 ";
}

void Catalog::SearchFiles(QString path, QString strExts)
{
	QDir dir(path);					qDebug() << "FILLING CATALOG" << dir.absolutePath();
	QStringList exts(strExts.split(" "));
	for (QFileInfo i : dir.entryInfoList(exts,QDir::Files|QDir::AllDirs)) {

		if (i.absolutePath() == dir.absolutePath())
		{
			if (i.isDir())
			{
				FillCatalog(i.absolutePath() + "/" + i.baseName());
			}
			else
			{
				files.push_back(MediaRecord(i));
				qDebug() << "ADDING " << i.fileName();
				n += 1;
			}
		};
	};
}

void Catalog::FillCatalog(QString path, QString strExts)
{
	if(extensions != strExts)
		extensions += strExts;
	SearchFiles(path, extensions);
	
	qDebug() << n << " FILES ADDED";
	emit catalogIsReady();
}

QStringList Catalog::GetNextFileData(int i)
{
	if ((i<GetSize())&&(i>=0))
	{

		MediaRecord temp(files.at(i));
		return temp.ToString()<<temp.GetNewDir()<<QString::number(i);
	}
	return QStringList();
}

void Catalog::OrganizeFiles(QString dirName, QList<int> chfiles)
{
	qDebug() << "Directory " << dirName;
	QRegularExpression re("\\+");
	QString dir2N = dirName.replace(re, "/");
	qDebug() << "Directory " << dir2N;

	dirName.replace("\\", "/");
	
	dirs.append(dirName);
	for each (int i in chfiles)
	{
		files[i].SetNewDir(dirName);
	}
	emit dirAdded(dirName);
	emit organized();
}

void Catalog::GenerateCatalog(QString newPath)
{
	QStorageInfo storage(newPath);
	if (storage.isReadOnly())
		qDebug() << "isReadOnly:" << storage.isReadOnly();

	qDebug() << "name:" << storage.name();
	qDebug() << "filesystem type:" << storage.fileSystemType();
	qDebug() << "size:" << storage.bytesTotal() / 1000 / 1000 << "Mb";
	qDebug() << "free space:" << storage.bytesAvailable() / 1000 / 1000 << "Mb";
	qint64 totalSize = 0;
	for each (MediaRecord var in files)
	{
		if (var.IsOrganized()) { totalSize += var.FileSize(); }
	}
	qDebug() << totalSize<< "bytes";
	qDebug() << "free space:" << storage.bytesAvailable();
	qDebug() << "Enter GenerateCatalog()";

	if((totalSize<storage.bytesAvailable()) && !storage.isReadOnly())
	{
			//creating directories
		QDir root(newPath);
		for each (QString str in dirs)
		{
			root.mkpath(newPath + "/" + str);
		}
			//copying files
		int fails = 0;
		for each (MediaRecord var in files)
		{
			if (var.IsOrganized() && !var.CopyFile(newPath)) { fails++; }
		}
		qDebug() << "MEDIACATALOG IS READY"<<"\nFAILED TO COPY: "<<fails;
		emit generated(fails);
	}
}

//void Catalog::dataChanged() { if (isChanged) { isChanged = false; emit dataChanged(); } }//?сигнал не имеет реализации он просто вызывается