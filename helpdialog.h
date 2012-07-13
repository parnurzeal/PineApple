#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QtGui/QDialog>
#include "ui_helpdialog.h"

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    HelpDialog(QWidget *parent = 0);
    ~HelpDialog();

private:
    Ui::HelpDialogClass ui;
};

#endif // HELPDIALOG_H
