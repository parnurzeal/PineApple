/********************************************************************************
** Form generated from reading ui file 'helpdialog.ui'
**
** Created: Thu Feb 5 20:33:19 2009
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_HELPDIALOG_H
#define UI_HELPDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

class Ui_HelpDialogClass
{
public:
    QLabel *label_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_3;
    QWidget *tab_2;
    QLabel *label_4;

    void setupUi(QDialog *HelpDialogClass)
    {
    if (HelpDialogClass->objectName().isEmpty())
        HelpDialogClass->setObjectName(QString::fromUtf8("HelpDialogClass"));
    HelpDialogClass->resize(517, 470);
    label_2 = new QLabel(HelpDialogClass);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(50, 20, 421, 51));
    tabWidget = new QTabWidget(HelpDialogClass);
    tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
    tabWidget->setGeometry(QRect(50, 80, 421, 351));
    tabWidget->setTabShape(QTabWidget::Rounded);
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    label_3 = new QLabel(tab);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(30, 0, 361, 311));
    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QString::fromUtf8("tab_2"));
    label_4 = new QLabel(tab_2);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(30, 0, 361, 291));
    tabWidget->addTab(tab_2, QString());

    retranslateUi(HelpDialogClass);

    tabWidget->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(HelpDialogClass);
    } // setupUi

    void retranslateUi(QDialog *HelpDialogClass)
    {
    HelpDialogClass->setWindowTitle(QApplication::translate("HelpDialogClass", "HelpDialog", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("HelpDialogClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt; font-weight:600;\">\340\270\247\340\270\264\340\270\230\340\270\265\340\270\201\340\270\262\340\270\243\340\271\203\340\270\212\340\271\211\340\270\207\340\270\262\340\270\231</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt; font-weight:600;\">PINEAPPLE : \340\271\202\340\270\233\340\270\243\340\271\201\340\270\201\340\270\243\340\270\241\340\270\233\340\270\243\340\270\260\340\270\252\340\270\262\340"
        "\270\231\340\270\240\340\270\262\340\270\236\340\270\210\340\270\262\340\270\201\340\270\201\340\270\245\340\271\211\340\270\255\340\270\207\340\271\200\340\270\247\340\271\207\340\270\232\340\271\201\340\270\204\340\270\241</p></body></html>", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("HelpDialogClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">\340\270\201\340\270\262\340\270\243\340\270\252\340\270\243\340\271\211\340\270\262\340\270\207\340\270\240\340\270\262\340\270\236\340\270\236\340\270\262\340\271\202\340\270\231\340\270\243\340\270\262\340\270\241\340\270\262\340\270\210\340\270\262\340\270\201\340\271\204\340\270\237\340\270\245\340\271\214\340\270\243\340\270\271\340\270\233\340\270\240\340\270\262\340\270\236</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px"
        "; font-size:10pt;\">1. \340\271\200\340\270\245\340\270\267\340\270\255\340\270\201 File Menu \340\270\210\340\270\262\340\270\201\340\271\200\340\270\241\340\270\231\340\270\271\340\270\232\340\270\262\340\270\243\340\271\214</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">\340\271\201\340\270\245\340\270\260\340\271\200\340\270\245\340\270\267\340\270\255\340\270\201 New Panorama</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">\340\270\210\340\270\260\340\270\241\340\270\265\340\270\253\340\270\231\340\271\211\340\270\262\340\270\225\340\271\210\340\270\262\340\270\207\340\270\212\340\271\210\340\270\247\340\270\242\340\271\200\340\270\253\340\270\245\340\270\267\340\270\255\340\271\203\340\270\231\340\270\201\340\270\262\340\270\243\340\270\252\340\270\243\340\271\211\340\270\262\340\270\207\340\270\236\340\270\262\340"
        "\271\202\340\270\231\340\270\243\340\270\262\340\270\241\340\270\262\340\270\202\340\270\266\340\271\211\340\270\231</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">2. \340\271\200\340\270\245\340\270\267\340\270\255\340\270\201 From Picture File \340\270\210\340\270\262\340\270\201\340\270\231\340\270\261\340\271\211\340\270\231\340\270\201\340\270\224\340\270\233\340\270\270\340\271\210\340\270\241 Next</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">3. \340\270\201\340\270\224\340\270\233\340\270\270\340\271\210\340\270\241 Add Picture \340\271\200\340\270\236\340\270\267\340\271\210\340\270\255\340\271\200\340\270\245\340\270\267\340\270\255\340\270\201\340\271\204\340\270\237\340\270\245\340\271\214\340\270\243\340\270\271\340\270\233\340\270\240\340\270\262\340\270\236\340\270\227\340\270\265\340\271\210\340\270\225"
        "\340\271\211\340\270\255\340\270\207\340\270\201\340\270\262\340\270\243</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">\340\270\231\340\270\263\340\270\241\340\270\262\340\270\252\340\270\243\340\271\211\340\270\262\340\270\207\340\270\240\340\270\262\340\270\236\340\270\236\340\270\262\340\271\202\340\270\231\340\270\243\340\270\262\340\270\241\340\270\262 \340\270\225\340\270\262\340\270\241\340\270\245\340\270\263\340\270\224\340\270\261\340\270\232\340\270\202\340\270\255\340\270\207\340\270\243\340\270\271\340\270\233\340\270\240\340\270\262\340\270\236</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">4. \340\270\226\340\271\211\340\270\262\340\270\225\340\271\211\340\270\255\340\270\207\340\270\201\340\270\262\340\270\243\340\270\245\340\270\232\340\270\240\340\270\262\340\270\236\340\270\227\340\270\265\340\271\210"
        "\340\271\200\340\270\245\340\270\267\340\270\255\340\270\201\340\270\255\340\270\255\340\270\201 \340\271\203\340\270\253\340\271\211\340\271\200\340\270\245\340\270\267\340\270\255\340\270\201\340\270\212\340\270\267\340\271\210\340\270\255\340\270\240\340\270\262\340\270\236\340\270\227\340\270\265\340\271\210\340\270\225\340\271\211\340\270\255\340\270\207\340\270\201\340\270\262\340\270\243</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">\340\271\201\340\270\245\340\270\260\340\270\201\340\270\224\340\270\233\340\270\270\340\271\210\340\270\241 Remove Picture</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">5. \340\271\200\340\270\241\340\270\267\340\271\210\340\270\255\340\271\200\340\270\245\340\270\267\340\270\255\340\270\201\340\270\240\340\270\262\340\270\236\340\271\204\340\270\224\340\271\211\340\270\204\340\270"
        "\243\340\270\232\340\271\201\340\270\245\340\271\211\340\270\247\340\271\203\340\270\253\340\271\211\340\270\201\340\270\224\340\270\233\340\270\270\340\271\210\340\270\241 Next</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">6. \340\270\201\340\270\224\340\270\233\340\270\270\340\271\210\340\270\241 Finish \340\270\210\340\270\260\340\271\204\340\270\224\340\271\211\340\270\240\340\270\262\340\270\236\340\270\236\340\270\262\340\271\202\340\270\231\340\270\243\340\270\262\340\270\241\340\270\262\340\270\227\340\270\265\340\271\210\340\270\252\340\270\243\340\271\211\340\270\262\340\270\207\340\271\200\340\270\252\340\270\243\340\271\207\340\270\210\340\271\200\340\270\243\340\270\265\340\270\242\340\270\232\340\270\243\340\271\211\340\270\255\340\270\242</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">7. \340\270\226\340"
        "\271\211\340\270\262\340\270\225\340\271\211\340\270\255\340\270\207\340\270\201\340\270\262\340\270\243\340\270\232\340\270\261\340\270\231\340\270\227\340\270\266\340\270\201\340\270\243\340\270\271\340\270\233\340\270\240\340\270\262\340\270\236\340\271\203\340\270\253\340\271\211\340\271\200\340\270\245\340\270\267\340\270\255\340\270\201  File Menu \340\270\210\340\270\262\340\270\201\340\271\200\340\270\241\340\270\231\340\270\271\340\270\232\340\270\262\340\270\243\340\271\214</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">\340\271\201\340\270\245\340\270\260\340\271\200\340\270\245\340\270\267\340\270\255\340\270\201 Save Panorama\340\270\260\340\270\241\340\270\265\340\270\253\340\270\231\340\271\211\340\270\262\340\270\225\340\271\210\340\270\262\340\270\207\340\270\232\340\270\261\340\270\231\340\270\227\340\270\266\340\270\201\340\271\204\340\270\237\340\270\245\340\271\214\340\270\202\340\270\266\340\271"
        "\211\340\270\231\340\270\241\340\270\262</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">\340\271\203\340\270\253\340\271\211\340\271\200\340\270\245\340\270\267\340\270\255\340\270\201\340\270\232\340\270\261\340\270\231\340\270\227\340\270\266\340\270\201\340\270\225\340\270\262\340\270\241\340\270\227\340\270\265\340\271\210\340\270\225\340\271\211\340\270\255\340\270\207\340\270\201\340\270\262\340\270\243</p></body></html>", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("HelpDialogClass", "\340\270\201\340\270\262\340\270\243\340\270\252\340\270\243\340\271\211\340\270\262\340\270\207\340\270\240\340\270\262\340\270\236\340\270\236\340\270\262\340\271\202\340\270\231\340\270\243\340\270\262\340\270\241\340\270\262", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("HelpDialogClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">\340\270\201\340\270\262\340\270\243\340\270\252\340\270\243\340\271\211\340\270\262\340\270\207\340\270\247\340\270\264\340\270\224\340\270\265\340\271\202\340\270\255\340\270\236\340\270\262\340\271\202\340\270\231\340\270\243\340\270\262\340\270\241\340\270\262\340\270\210\340\270\262\340\270\201\340\270\201\340\270\245\340\271\211\340\270\255\340\270\207\340\271\200\340\270\247\340\271\207\340\270\232\340\271\201\340\270\204\340\270\241</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-lef"
        "t:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">1. \340\271\200\340\270\245\340\270\267\340\270\255\340\270\201 File Menu \340\270\210\340\270\262\340\270\201\340\271\200\340\270\241\340\270\231\340\270\271\340\270\232\340\270\262\340\270\243\340\271\214</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">\340\271\201\340\270\245\340\270\260\340\271\200\340\270\245\340\270\267\340\270\255\340\270\201 New Panorama</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">\340\270\210\340\270\260\340\270\241\340\270\265\340\270\253\340\270\231\340\271\211\340\270\262\340\270\225\340\271\210\340\270\262\340\270\207\340\270\212\340\271\210\340\270\247\340\270\242\340\271\200\340\270\253\340\270\245\340\270\267\340\270\255\340\271\203\340\270\231\340\270\201\340\270\262\340\270\243\340\270\252\340\270\243\340"
        "\271\211\340\270\262\340\270\207\340\270\236\340\270\262\340\271\202\340\270\231\340\270\243\340\270\262\340\270\241\340\270\262\340\270\202\340\270\266\340\271\211\340\270\231</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">2. \340\271\200\340\270\245\340\270\267\340\270\255\340\270\201 From WebCam \340\270\210\340\270\262\340\270\201\340\270\231\340\270\261\340\271\211\340\270\231\340\270\201\340\270\224\340\270\233\340\270\270\340\271\210\340\270\241 Next</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">3. \340\270\201\340\270\243\340\270\255\340\270\201\340\270\210\340\270\263\340\270\231\340\270\247\340\270\231\340\270\201\340\270\245\340\271\211\340\270\255\340\270\207\340\271\200\340\270\247\340\271\207\340\270\232\340\271\201\340\270\204\340\270\241</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-le"
        "ft:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">\340\270\227\340\270\265\340\271\210\340\270\210\340\270\260\340\270\231\340\270\263\340\270\241\340\270\262\340\270\252\340\270\243\340\271\211\340\270\262\340\270\207\340\270\247\340\270\264\340\270\224\340\270\265\340\271\202\340\270\255\340\270\236\340\270\262\340\271\202\340\270\231\340\270\243\340\270\262\340\270\241\340\270\262 \340\270\210\340\270\262\340\270\201\340\270\231\340\270\261\340\271\211\340\270\231\340\270\201\340\270\224\340\270\233\340\270\270\340\271\210\340\270\241 Next</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\">4. \340\270\201\340\270\224\340\270\233\340\270\270\340\271\210\340\270\241 Finish \340\270\210\340\270\260\340\271\204\340\270\224\340\271\211\340\270\247\340\270\264\340\270\224\340\270\265\340\271\202\340\270\255\340\270\236\340\270\262\340\271\202\340\270\231\340\270\243\340\270\262\340\270\241\340"
        "\270\262\340\270\227\340\270\265\340\271\210\340\270\252\340\270\243\340\271\211\340\270\262\340\270\207\340\271\200\340\270\252\340\270\243\340\271\207\340\270\210\340\271\200\340\270\243\340\270\265\340\270\242\340\270\232\340\270\243\340\271\211\340\270\255\340\270\242</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-"
        "bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("HelpDialogClass", "\340\270\201\340\270\262\340\270\243\340\270\252\340\270\243\340\271\211\340\270\262\340\270\207\340\270\247\340\270\264\340\270\224\340\270\265\340\271\202\340\270\255\340\270\236\340\270\262\340\271\202\340\270\231\340\270\243\340\270\262\340\270\241\340\270\262", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(HelpDialogClass);
    } // retranslateUi

};

namespace Ui {
    class HelpDialogClass: public Ui_HelpDialogClass {};
} // namespace Ui

#endif // UI_HELPDIALOG_H
