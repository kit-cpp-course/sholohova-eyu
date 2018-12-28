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

	w.show();

	return a.exec();
}
