#include "QtMediaCatalog.h"
#include "Catalog.h"
#include <QtWidgets/QApplication>

#include "qlayout.h"
#include "qlabel.h"
#include "qline.h"
#include "qpushbutton.h"
#include "qtablewidget.h"
#include "qlist.h"
#pragma once

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtMediaCatalog w;
	//?
	//Catalog* catalog;
	//QObject::connect(&w, SIGNAL(pathEntered(QString)), catalog, SLOT(FillCatalog(QString)));

	w.show();

	//Connecting signals and slots


	return a.exec();
}
