#include "newpanowizard.h"

#include "alldefine.h"

#include <QWidget>
#include <QFileDialog>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QVariant>
#include <QLineEdit>

NewPanoWizard::NewPanoWizard(QWidget *parent, QStringList *srcList, int *whichSrc, int *numCam)
	: QWizard(parent)
{
	FinishPage *finishPage = new FinishPage(this);
	setPage(Page_Select_Source, new SelectSourcePage(this, whichSrc));
	setPage(Page_Select_Picture, new SelectPicturePage(this, srcList));
	setPage(Page_Select_Video, new SelectVideoPage(this, srcList));
	setPage(Page_Select_Cam, new SelectCamPage(this, numCam));
	setPage(Page_Finish, finishPage);
	//	registerField("numCamText*", numCamText);
	setStartId(Page_Select_Source);
	setWindowTitle(tr("New Panorama"));
	connect(this, SIGNAL(currentIdChanged(int)), finishPage, SLOT(setUpFinishPage(int)));
}

SelectSourcePage::SelectSourcePage(QWizard *parent, int *whichSrc)
	: QWizardPage(parent)
{
	setTitle(tr("Select Panorama Source"));
	picRadio = new QRadioButton(tr("From Picture File"), this);
	camRadio = new QRadioButton(tr("From WebCam"), this);
	videoRadio = new QRadioButton(tr("From Video File"), this);
//	networkRadio = new QRadioButton(tr("From Network"), this);
//	registerField("srcFromPic", picRadio);
//	registerField("srcFromCam", camRadio);
	QButtonGroup *srcButtonGroup = new QButtonGroup(this);
	picRadio->setChecked(true);
	srcButtonGroup->addButton(picRadio);
	srcButtonGroup->addButton(camRadio);
	srcButtonGroup->addButton(videoRadio);
//	srcButtonGroup->addButton(networkRadio);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(picRadio);
	mainLayout->addWidget(camRadio);
	mainLayout->addWidget(videoRadio);
	setLayout(mainLayout);
	this->whichSrc = whichSrc;
}

int SelectSourcePage::nextId() const
{
	if(picRadio->isChecked())
	{
		*whichSrc = File;
		return NewPanoWizard::Page_Select_Picture;
	} else if(camRadio->isChecked())
	{
		*whichSrc = Cam;
		return NewPanoWizard::Page_Select_Cam;
	} else if(videoRadio->isChecked())
	{
		*whichSrc = Video;
		return NewPanoWizard::Page_Select_Video;
	}
	return 0;
}

SelectPicturePage::SelectPicturePage(QWizard *parent, QStringList *srcList)
	: QWizardPage(parent)
{
	setTitle(tr("Select Picture Files"));
	openPicDialog = new QFileDialog(this, tr("Choose Picture To Make New Panorama"), tr(""), tr(PICTURE_FILE_FORMAT));
	openPicDialog->setFileMode(QFileDialog::ExistingFiles);
	picFileList = new QListWidget(this);
	addPicButton = new QPushButton(tr("Add Picture"), this);
	removePicButton = new QPushButton(tr("Remove Picture"), this);
	dispPicLabel = new QLabel(this);
	dispPicLabel->setFixedSize(DISPLAY_PICTURE_WIDTH, DISPLAY_PICTURE_HEIGHT);
	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout->addWidget(dispPicLabel);
	rightLayout->addWidget(addPicButton);
	rightLayout->addWidget(removePicButton);
	QWidget *rightWidget = new QWidget(this);
	rightWidget->setLayout(rightLayout);
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget(picFileList);
	mainLayout->addWidget(rightWidget);
	setLayout(mainLayout);
	registerField("picFileList*", picFileList);
	connect(addPicButton, SIGNAL(clicked()), this, SLOT(addPic()));
	connect(removePicButton, SIGNAL(clicked()), this, SLOT(removePic()));
	connect(picFileList, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(displayPic(QListWidgetItem*)));
	this->srcList = srcList;
}

int SelectPicturePage::nextId() const
{
	return NewPanoWizard::Page_Finish;
}

void SelectPicturePage::addPic()
{
	if(openPicDialog->exec())
	{
		picFileList->addItems(openPicDialog->selectedFiles());
		picFileList->setCurrentRow(picFileList->count() - 1);
		(*srcList) << openPicDialog->selectedFiles();
	}
}

void SelectPicturePage::removePic()
{
	delete picFileList->takeItem(picFileList->currentRow());
	srcList->removeAt(picFileList->currentRow());
}

void SelectPicturePage::displayPic(QListWidgetItem *currentItem)
{
	if(currentItem)
	{
		QPixmap dispPic(currentItem->text());
		if(dispPic.width() > dispPic.height() && dispPic.width() > dispPicLabel->width())
		{
			dispPicLabel->setPixmap(dispPic.scaledToWidth(dispPicLabel->width()));
		} else if(dispPic.height() > dispPic.width() && dispPic.height() > dispPicLabel->height())
		{
			dispPicLabel->setPixmap(dispPic.scaledToHeight(dispPicLabel->height()));
		} else
		{
			dispPicLabel->setPixmap(dispPic);
		}
	} else
	{
		dispPicLabel->clear();
	}
}

SelectCamPage::SelectCamPage(QWizard *parent, int *numCam)
	: QWizardPage(parent)
{
//	numCamText =  new QTextEdit(this);
	QLabel *numCamLabel = new QLabel(this);
	numCamLabel->setText(tr("Number of Cameras"));
	numCamText = new QLineEdit();
	numCamText->setInputMask(tr("99999"));
	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->addWidget(numCamLabel);
	layout->addWidget(numCamText);
	setLayout(layout);
	this->numCam = numCam;
}

int SelectCamPage::nextId() const
{
	*numCam = numCamText->text().toInt();
	return NewPanoWizard::Page_Finish;
}


FinishPage::FinishPage(QWizard *parent)
	: QWizardPage(parent)
{
	setTitle(tr("Finish"));
}

int FinishPage::nextId() const
{
	return -1;
}

void FinishPage::setUpFinishPage(int pageId)
{
//	if(pageId != NewPanoWizard::Page_Finish)
//		return;
//	if(field("srcFromPic").toBool())
//	{
//		setTitle(tr("Finish"));
//	} else if(field("srcFromCam").toBool())
//	{
//		setTitle(tr("Finish"));
//	}
}


SelectVideoPage::SelectVideoPage(QWizard *parent, QStringList *srcList)
	: QWizardPage(parent)
{
	setTitle(tr("Select Video Files"));
	openPicDialog = new QFileDialog(this, tr("Choose Video To Make New Panorama"), tr(""));
	openPicDialog->setFileMode(QFileDialog::ExistingFiles);
	picFileList = new QListWidget(this);
	addPicButton = new QPushButton(tr("Add Video"), this);
	removePicButton = new QPushButton(tr("Remove Video"), this);
	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout->addWidget(addPicButton);
	rightLayout->addWidget(removePicButton);
	QWidget *rightWidget = new QWidget(this);
	rightWidget->setLayout(rightLayout);
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget(picFileList);
	mainLayout->addWidget(rightWidget);
	setLayout(mainLayout);
	registerField("videoFileList*", picFileList);
	connect(addPicButton, SIGNAL(clicked()), this, SLOT(addPic()));
	connect(removePicButton, SIGNAL(clicked()), this, SLOT(removePic()));
	this->srcList = srcList;
}

int SelectVideoPage::nextId() const
{
	return NewPanoWizard::Page_Finish;
}

void SelectVideoPage::addPic()
{
	if(openPicDialog->exec())
	{
		picFileList->addItems(openPicDialog->selectedFiles());
		picFileList->setCurrentRow(picFileList->count() - 1);
		(*srcList) << openPicDialog->selectedFiles();
	}
}

void SelectVideoPage::removePic()
{
	delete picFileList->takeItem(picFileList->currentRow());
	srcList->removeAt(picFileList->currentRow());
}
