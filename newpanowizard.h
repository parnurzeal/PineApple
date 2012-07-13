#ifndef NEWPANOWIZARD_H
#define NEWPANOWIZARD_H

#include <QWizard>
#include <QWizardPage>

class QRadioButton;
class QPushButton;
class QListWidget;
class QListWidgetItem;
class QFileDialog;
class QLabel;
class QStringList;
class QLineEdit;

class NewPanoWizard : public QWizard
{
	Q_OBJECT
	public:
		enum { Page_Select_Source, Page_Select_Picture, Page_Select_Cam, Page_Select_Video, Page_Finish };
		NewPanoWizard(QWidget *parent, QStringList *srcList, int *whichSrc, int *numCam);
	protected:
};

class SelectSourcePage : public QWizardPage
{
	//Q_OBJECT
	public:
		SelectSourcePage(QWizard *parent, int *whichSrc);
	protected:
		QRadioButton *picRadio;
		QRadioButton *camRadio;
		QRadioButton *videoRadio;
		int *whichSrc;
		int nextId() const;

};

class SelectPicturePage : public QWizardPage
{
	Q_OBJECT
	public:
		SelectPicturePage(QWizard *parent, QStringList *srcList);
	protected:
		QListWidget *picFileList;
		QPushButton *addPicButton;
		QPushButton *removePicButton;
		QFileDialog *openPicDialog;
		QLabel *dispPicLabel;
		QStringList *srcList;
		int nextId() const;
	protected slots:
		void addPic();
		void removePic();
		void displayPic(QListWidgetItem *currentItem);
};

class SelectCamPage : public QWizardPage
{
	//Q_OBJECT
	public:
		SelectCamPage(QWizard *parent, int *numCam);
	protected:
		int nextId() const;
		int *numCam;
		QLineEdit *numCamText;
};

class SelectVideoPage : public QWizardPage
{
	Q_OBJECT
	public:
		SelectVideoPage(QWizard *parent, QStringList *srcList);
	protected:
		QListWidget *picFileList;
		QPushButton *addPicButton;
		QPushButton *removePicButton;
		QFileDialog *openPicDialog;
		QStringList *srcList;
		int nextId() const;
	protected slots:
		void addPic();
		void removePic();
};

class FinishPage : public QWizardPage
{
	Q_OBJECT
	public:
		FinishPage(QWizard *parent);
	protected:
		int nextId() const;
	protected slots:
		void setUpFinishPage(int pageId);
};

#endif
