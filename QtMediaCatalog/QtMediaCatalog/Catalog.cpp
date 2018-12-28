#include "Catalog.h"
#include <QDir>
#include <qDebug>
#pragma once

Catalog::Catalog(QObject *parent)
	: QObject(parent)
{
	n = 0;
	it = 0;
}

Catalog::~Catalog()
{
}

void Catalog::FillCatalog(QString path)
{
	
	QDir dir(path);qDebug() << "FILLING CATALOG"<< dir.absolutePath();
	for (QFileInfo i : dir.entryInfoList()) {
		
		if (i.absolutePath() == dir.absolutePath()) 
		{
			if (i.isDir()) 
			{
				FillCatalog(i.absolutePath()+"/"+i.baseName());
			}
			else
			{
				fileTodir tempstruct{ MediaRecord(i), "" };
				files.push_back(tempstruct);
				qDebug() << "ADDING " << i.fileName();
				MediaRecord temp(files.at(n).rec);
			
				qDebug() << "ADDED"<<temp.ToString().at(0);
				n += 1;
			}
		};
	};
	qDebug() << n << " FILES ADDED";
	emit catalogIsReady();
}

QStringList Catalog::GetNextFileData(int i)
{
	if ((i<GetSize())&&(i>=0))
	{

		MediaRecord temp(files.at(i).rec);
		return temp.ToString();
	}
	return QStringList();
}

void Catalog::OrganizeFiles(QString dirName, QList<int> chfiles)
{
}

void Catalog::GenerateCatalog(QString newPath)
{
}

