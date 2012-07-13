/********************************************************************************
** Form generated from reading ui file 'aboutdialog.ui'
**
** Created: Thu Feb 5 20:33:19 2009
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>

class Ui_AboutDialogClass
{
public:
    QLabel *label;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_2;

    void setupUi(QDialog *AboutDialogClass)
    {
    if (AboutDialogClass->objectName().isEmpty())
        AboutDialogClass->setObjectName(QString::fromUtf8("AboutDialogClass"));
    AboutDialogClass->resize(496, 286);
    label = new QLabel(AboutDialogClass);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(30, 20, 151, 181));
    label->setPixmap(QPixmap(QString::fromUtf8("Untitled-1.png")));
    label->setScaledContents(true);
    label_3 = new QLabel(AboutDialogClass);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(210, 40, 271, 141));
    QFont font;
    font.setPointSize(20);
    label_3->setFont(font);
    label_5 = new QLabel(AboutDialogClass);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setGeometry(QRect(30, 210, 101, 31));
    QFont font1;
    font1.setPointSize(15);
    label_5->setFont(font1);
    label_2 = new QLabel(AboutDialogClass);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(120, 210, 241, 61));

    retranslateUi(AboutDialogClass);

    QMetaObject::connectSlotsByName(AboutDialogClass);
    } // setupUi

    void retranslateUi(QDialog *AboutDialogClass)
    {
    AboutDialogClass->setWindowTitle(QApplication::translate("AboutDialogClass", "AboutDialog", 0, QApplication::UnicodeUTF8));
    label->setText(QString());
    label_3->setText(QApplication::translate("AboutDialogClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:20pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:26pt; font-weight:600;\">PINEAPPLE</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\340\271\202\340\270\233\340\270\243\340\271\201\340\270\201\340\270\243\340\270\241\340\270\233\340\270\243\340\270\260\340\270\252\340\270\262\340\270\231\340\270\240\340\270\262\340\270\236</p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;"
        "\">\340\270\210\340\270\262\340\270\201\340\270\201\340\270\245\340\271\211\340\270\255\340\270\207\340\271\200\340\270\247\340\271\207\340\270\232\340\271\201\340\270\204\340\270\241</p></body></html>", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("AboutDialogClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:15pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">\340\270\210\340\270\261\340\270\224\340\270\227\340\270\263\340\271\202\340\270\224\340\270\242 :</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("AboutDialogClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:15pt;\"><span style=\" font-size:12pt;\">\340\270\231\340\270\262\340\270\242\340\270\230\340\270\265\340\270\243\340\270\260\340\270\236\340\270\245 \340\270\247\340\270\261\340\270\230\340\270\231\340\271\200\340\270\247\340\270\204\340\270\264\340\270\231</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\">\340\270\231\340\270\262\340\270\242\340\270\230\340\270\231\340\270\262\340\270\201\340\270\243 \340\270\245\340\270\265\340\271\210\340\270\252\340"
        "\270\226\340\270\262\340\270\236\340\270\243\340\270\247\340\270\207\340\270\250\340\270\262</p></body></html>", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(AboutDialogClass);
    } // retranslateUi

};

namespace Ui {
    class AboutDialogClass: public Ui_AboutDialogClass {};
} // namespace Ui

#endif // UI_ABOUTDIALOG_H
