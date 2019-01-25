#include <QObject>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#pragma once

class MediaRecord
{
private:
	QFileInfo fileInfo;
	QString newDir;
public:
	MediaRecord();
	MediaRecord(QString filePath);
	MediaRecord(QFileInfo fInfo);
	bool CopyFile(QString newPath);
	QStringList ToString(); //returns array with file info
	bool IsOrganized();
	void SetNewDir(QString dirName);
	QString GetNewDir();
	int FileSize() { return fileInfo.size(); };
};


