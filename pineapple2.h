#ifndef PINEAPPLE2_H
#define PINEAPPLE2_H

#include <QtGui/QMainWindow>
#include "ui_pineapple2.h"
#include <QStringList>
#include "alldefine.h"
#include "glwidget.h"

class PineApple2 : public QMainWindow
{
    Q_OBJECT

public:
    PineApple2(QWidget *parent = 0);
protected:
	QStringList srcList;
	GLWidget *mainWidget;
	int whichSrc;
	int numCam;

protected slots:
	void newPano();
	void savePano();
	void exitPano();
	void helpContentsPano();
	void aboutPano();
	void startRec();
	void stopRec();

private:
    Ui::PineApple2Class ui;
};

#endif // PINEAPPLE2_H
