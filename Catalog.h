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
	QString extensions;
	int n;
public:
	Catalog(QObject *parent = Q_NULLPTR);
	int GetSize() { return n; };
	QStringList GetNextFileData(int i);
	MediaRecord GetRecord(int i) { return files.at(i); };
public slots:
	void FillCatalog(QString path, QString strExts = "");
	void SearchFiles(QString path, QString strExts);
	void OrganizeFiles(QString dirName, QList<int> chfiles);
	void GenerateCatalog(QString newPath);
signals:
	void catalogIsReady();
	void dataChanged();
	void organized();
	void dirAdded(QString dirName);
	void generated(int fails);
};