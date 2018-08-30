/********************************************************************************
** Form generated from reading UI file 'Laborator1011.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABORATOR1011_H
#define UI_LABORATOR1011_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Laborator1011Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Laborator1011Class)
    {
        if (Laborator1011Class->objectName().isEmpty())
            Laborator1011Class->setObjectName(QStringLiteral("Laborator1011Class"));
        Laborator1011Class->resize(600, 400);
        menuBar = new QMenuBar(Laborator1011Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        Laborator1011Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Laborator1011Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Laborator1011Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Laborator1011Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Laborator1011Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Laborator1011Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Laborator1011Class->setStatusBar(statusBar);

        retranslateUi(Laborator1011Class);

        QMetaObject::connectSlotsByName(Laborator1011Class);
    } // setupUi

    void retranslateUi(QMainWindow *Laborator1011Class)
    {
        Laborator1011Class->setWindowTitle(QApplication::translate("Laborator1011Class", "Laborator1011", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Laborator1011Class: public Ui_Laborator1011Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABORATOR1011_H
