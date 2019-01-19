#include <QObject>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#pragma once
//class MediaRecord : public QObject
//{
//	Q_OBJECT
//
//public:
//	MediaRecord(QObject *parent);
//	~MediaRecord();
//};

//#include <string.h>
/*enum Extension
{
	mp3,
	mid,
	wav,
	avi,
	mp4,
	mkv,
	flv,
	xvid,
	mpeg4,
	wmv
};*/
class MediaRecord
{
private:
	//char* name;	char* fullPath;	int fileSize;	Extension fileExt;	char* type;

	QFileInfo fileInfo;
	QString newDir;
public:
	MediaRecord();
	MediaRecord(QString filePath);
	MediaRecord(QFileInfo fInfo);
	//MediaRecord(const MediaRecord& rec);
	~MediaRecord();
	bool CopyFile(QString newPath);
	QStringList ToString();//returns array with file info
	bool IsOrganized();
	void SetNewDir(QString dirName);
	QString GetNewDir();
	int FileSize() { return fileInfo.size(); };
};


