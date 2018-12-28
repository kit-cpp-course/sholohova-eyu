#include <QObject>
#include <QVector>
#include <QList>
#include "MediaRecord.h"
#pragma once

class Catalog : public QObject
{
	Q_OBJECT
private:
	QString path;
	struct fileTodir {
		MediaRecord rec;
		QString dir;
	};
	QVector <fileTodir> files;
	QStringList dirs;
	int n;

	int it;
public:
	Catalog(QObject *parent = Q_NULLPTR);
	~Catalog();	
	int GetSize() { return n; };
	QStringList GetNextFileData(int i);
public slots:
	void FillCatalog(QString path);
	void OrganizeFiles(QString dirName, QList<int> chfiles);
	void GenerateCatalog(QString newPath);
	
signals:
	void catalogIsReady();
	void dataChanged();
	void organized();
};
