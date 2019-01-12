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
	QVector <MediaRecord> files;	
	QStringList dirs;
	int n;
public:
	Catalog(QObject *parent = Q_NULLPTR);
	~Catalog();	
	int GetSize() { return n; };
	QStringList GetNextFileData(int i);
	MediaRecord GetRecord(int i) { return files.at(i); };
public slots:
	void FillCatalog(QString path);
	void SearchFiles(QString path);
	void OrganizeFiles(QString dirName, QList<int> chfiles);
	void GenerateCatalog(QString newPath);
signals:
	void catalogIsReady();
	void dataChanged();
	void organized();
	//void dirsFullUpdate(QStringList dirs);
	void dirAdded(QString dirName);
	void generated(int fails);
};