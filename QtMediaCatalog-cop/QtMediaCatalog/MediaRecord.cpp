#include "MediaRecord.h"
#include <qDebug>
#pragma once

MediaRecord::MediaRecord() {}
MediaRecord::MediaRecord(QString filePath)
{
	fileInfo.setFile((filePath));
	newDir = "";
}
MediaRecord::MediaRecord(QFileInfo fInfo)
{
	fileInfo = fInfo;
	newDir = "";
}
/*MediaRecord::MediaRecord(const MediaRecord & rec)
{
	qDebug() << "In copy constructor";
	fileInfo = rec.fileInfo;
}*/
MediaRecord::~MediaRecord() {}

bool MediaRecord::CopyFile(QString newPath)
{
	if (!QFile::copy(fileInfo.absoluteFilePath(), newPath + "/" + newDir+"/" + fileInfo.fileName())) {
		qDebug() << "Copying file "<<fileInfo.absoluteFilePath()<<" failed!"
			;
		qDebug() << newPath + "/" + newDir + "/" + fileInfo.fileName();
		return false;
	}
	else
	{
		qDebug() << fileInfo.absoluteFilePath() << " is copied to:";
		qDebug() << newPath + "/" + newDir + "/" + fileInfo.fileName();
		return true;
	}
}

QStringList MediaRecord::ToString()
{
	return (QStringList() << fileInfo.fileName()
		<< fileInfo.suffix())
		<<
		(((float)fileInfo.size() / 1024 / 1024) > 1023 ? 
			QString::number((float)fileInfo.size() / 1024 / 1024 / 1024, 'f', 2) + " Gb"
			: QString::number((float)fileInfo.size() / 1024 / 1024, 'f', 2) + " Mb");
}

bool MediaRecord::IsOrganized()
{
	if (newDir == "") {
		return false;
	}
	return true;
}

void MediaRecord::SetNewDir(QString dirName)
{
	newDir = dirName;
	qDebug() << "File " << fileInfo.fileName() << " was put into " << newDir;
}

QString MediaRecord::GetNewDir()
{
	return newDir;
}

//MediaRecord::MediaRecord(QObject *parent)
//	: QObject(parent)
//{
//}
//
//MediaRecord::~MediaRecord()
//{
//}
