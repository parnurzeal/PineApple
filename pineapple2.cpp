#include "pineapple2.h"
#include <QtGui>
#include "menubar.h"
#include "newpanowizard.h"
#include "alldefine.h"
#include "glwidget.h"
#include <cv.h>
#include "imageFunction.h"
#include <QtOpenGL>
#include <QGLWidget>
#include "aboutdialog.h"
#include "helpdialog.h"

void debugWinMsgHandler(QtMsgType type, const char *msg)
{
	static QTextEdit *edit = new QTextEdit();
	edit->setWindowTitle("Debug window");
	edit->show();
	switch (type) {
		case QtDebugMsg:
		edit->append(QString("<b>Debug:</b> \%1").arg(msg));
		break;
		case QtWarningMsg:
		edit->append(QString("<b>Warning:</b> \%1").arg(msg));
		break;
		case QtCriticalMsg:
		edit->append(QString("<font color=\"red\"><b>Critical:</b></font> \%1").arg(msg));
		break;
		case QtFatalMsg:
		QMessageBox::critical(0, "Debug - Fatal", msg);
		abort();
	}
}

PineApple2::PineApple2(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
#ifdef DEBUG
	qInstallMsgHandler(debugWinMsgHandler);
#endif
	MenuBar *menuBar = new MenuBar(this);
	setMenuBar(menuBar);
	mainWidget = new GLWidget(this);
	setCentralWidget(mainWidget);
	move(100,100);
}
void PineApple2::newPano()
{
	NewPanoWizard *newPanoWizard = new NewPanoWizard(this,&srcList,&whichSrc,&numCam);
	srcList.clear();
	if(newPanoWizard->exec()){
		if(whichSrc==File){
			mainWidget->showPanoFromPic(srcList);
		} else if(whichSrc==Cam)
		{
			mainWidget->showPanoFromCam(numCam);
		} else if(whichSrc==Video)
		{
			mainWidget->showPanoFromVideo(srcList);
		}
	}
}

void PineApple2::savePano()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Panorama"));
	mainWidget->savePanoImage(fileName);
}
void PineApple2::exitPano(){
	exit(1);
}
void PineApple2::helpContentsPano(){
	HelpDialog *helpDialog = new HelpDialog();
	helpDialog->show();
}
void PineApple2::aboutPano(){
	AboutDialog *aboutDialog = new AboutDialog();
	aboutDialog->show();
}

void PineApple2::startRec() {
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Panorama"));
	mainWidget->startRec(fileName);
}

void PineApple2::stopRec() {
	mainWidget->stopRec();
}
