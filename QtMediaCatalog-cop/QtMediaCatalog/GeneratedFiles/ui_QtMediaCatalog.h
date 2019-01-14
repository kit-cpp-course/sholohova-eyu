/********************************************************************************
** Form generated from reading UI file 'QtMediaCatalog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTMEDIACATALOG_H
#define UI_QTMEDIACATALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtMediaCatalogClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtMediaCatalogClass)
    {
        if (QtMediaCatalogClass->objectName().isEmpty())
            QtMediaCatalogClass->setObjectName(QStringLiteral("QtMediaCatalogClass"));
        QtMediaCatalogClass->resize(600, 400);
        menuBar = new QMenuBar(QtMediaCatalogClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QtMediaCatalogClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtMediaCatalogClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtMediaCatalogClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtMediaCatalogClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtMediaCatalogClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtMediaCatalogClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtMediaCatalogClass->setStatusBar(statusBar);

        retranslateUi(QtMediaCatalogClass);

        QMetaObject::connectSlotsByName(QtMediaCatalogClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtMediaCatalogClass)
    {
        QtMediaCatalogClass->setWindowTitle(QApplication::translate("QtMediaCatalogClass", "QtMediaCatalog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtMediaCatalogClass: public Ui_QtMediaCatalogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMEDIACATALOG_H
