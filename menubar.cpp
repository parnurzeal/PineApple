#include "menubar.h"
#include "newpanowizard.h"

#include <QMenu>
#include <QAction>

MenuBar::MenuBar(QWidget *parent)
	: QMenuBar(parent)
{
	QMenu *fileMenu = new QMenu(tr("&File"), this);
	QAction *newPanoAct = new QAction(tr("&New Panorama"), fileMenu);
	fileMenu->addAction(newPanoAct);
	QAction *savePanoAct = new QAction(tr("&Save Panorama"), fileMenu);
	fileMenu->addAction(savePanoAct);
	QAction *exitPanoAct = new QAction(tr("&Exit"), fileMenu);
	fileMenu->addAction(exitPanoAct);
	addMenu(fileMenu);
	connect(newPanoAct, SIGNAL(triggered()), parent, SLOT(newPano()));
	connect(savePanoAct, SIGNAL(triggered()), parent, SLOT(savePano()));
	connect(exitPanoAct, SIGNAL(triggered()), parent, SLOT(exitPano()));
	QMenu *helpMenu = new QMenu(tr("&Help"),this);
	QAction *helpContentsPanoAct = new QAction(tr("&Help Contents"),helpMenu);
	QAction *aboutPanoAct = new QAction(tr("&About PineApple..."),helpMenu);
	helpMenu->addAction(helpContentsPanoAct);
	helpMenu->addAction(aboutPanoAct);
	addMenu(helpMenu);
	addSeparator();
	QAction *startRecAct = new QAction(tr("Start Record"), fileMenu);
	QAction *stopRecAct = new QAction(tr("Stop Record"), fileMenu);
	addAction(startRecAct);
	addAction(stopRecAct);
	connect(helpContentsPanoAct, SIGNAL(triggered()),parent,SLOT(helpContentsPano()));
	connect(aboutPanoAct, SIGNAL(triggered()),parent,SLOT(aboutPano()));
	connect(startRecAct, SIGNAL(triggered()),parent,SLOT(startRec()));
	connect(stopRecAct, SIGNAL(triggered()),parent,SLOT(stopRec()));
}
