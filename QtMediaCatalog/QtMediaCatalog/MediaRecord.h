#include <QObject>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#pragma once

class MediaRecord
{
private:
	QFileInfo fileInfo;

public:
	MediaRecord();
	MediaRecord(QString filePath);
	MediaRecord(QFileInfo fInfo);
	//MediaRecord(const MediaRecord& rec);
	~MediaRecord();
	void CopyFile(QString newPath);
	QStringList ToString();//returns array with file info? char*[]
};


