/********************************************************************************
** Form generated from reading ui file 'pineapple2.ui'
**
** Created: Wed Feb 4 23:24:48 2009
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PINEAPPLE2_H
#define UI_PINEAPPLE2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

class Ui_PineApple2Class
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PineApple2Class)
    {
    if (PineApple2Class->objectName().isEmpty())
        PineApple2Class->setObjectName(QString::fromUtf8("PineApple2Class"));
    PineApple2Class->resize(1000, 410);
    centralwidget = new QWidget(PineApple2Class);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    PineApple2Class->setCentralWidget(centralwidget);
    menubar = new QMenuBar(PineApple2Class);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 1000, 25));
    PineApple2Class->setMenuBar(menubar);
    statusbar = new QStatusBar(PineApple2Class);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    PineApple2Class->setStatusBar(statusbar);

    retranslateUi(PineApple2Class);

    QMetaObject::connectSlotsByName(PineApple2Class);
    } // setupUi

    void retranslateUi(QMainWindow *PineApple2Class)
    {
    PineApple2Class->setWindowTitle(QApplication::translate("PineApple2Class", "PineApple", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(PineApple2Class);
    } // retranslateUi

};

namespace Ui {
    class PineApple2Class: public Ui_PineApple2Class {};
} // namespace Ui

#endif // UI_PINEAPPLE2_H
