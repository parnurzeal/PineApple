/*
 * glwidget.cpp
 *
 *  Created on: Dec 31, 2008
 *      Author: Administrator
 */

#include <QtGui>
#include <QtOpenGL>
#include <cv.h>

#include <QTimer>
//**for camera setting**//
#include <sys/ioctl.h>
#include "pwc-ioctl.h"
#include <linux/videodev.h>
#include <fcntl.h>
#include <unistd.h>
#include "setFunction.h"
int *fd;
//***********************/
#include "glwidget.h"
#include "imageFunction.h"
#include "alldefine.h"
#include "delaunay.h"

//**for timer ****//
#include "timer.h"
timer test_timer;
bool timerFirst=true;
double tmpTime=0;
/*******/
int numImg = 0;
int NUM_PIC=0;

//for trigger animate for cam//
QTimer *timer;
/***************************/

GLWidget::GLWidget(QWidget *parent) :QGLWidget(parent){
	object =0;
	xRot=0;
	yRot=0;
	zRot=0;
	trolltechGreen = QColor::fromCmykF(0.40,0.0,1.0,0.0);
	trolltechPurple = QColor::fromCmykF(0.39,0.39,0.0,0,0);
	picPosition = new QPointF(0,0);
}

GLWidget::~GLWidget(){
	makeCurrent();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}



 void GLWidget::initializeGL()
  {

	 //textures = new GLuint[numImg];
//	 initPineApple();
      qglClearColor(trolltechPurple.dark());
      glEnable(GL_DEPTH_TEST);

  }

void colorEqualize(IplImage *img, IplImage *eql) {
	IplImage *hsv = cvCreateImage(cvGetSize(img), 8, 3);
	cvCvtColor(img, hsv, CV_BGR2HSV);
//	printf("%s\n", hsv->channelSeq);
	IplImage *hsvArr[3];
	for(int i = 0; i < 3; ++i) {
		hsvArr[i] = cvCreateImage(cvGetSize(img), 8, 1);
	}
	cvSplit(hsv, hsvArr[0], hsvArr[1], hsvArr[2], 0);
	IplImage *vEql = cvCreateImage(cvGetSize(img), 8, 1);
	cvEqualizeHist(hsvArr[2], vEql);
	cvMerge(hsvArr[0], hsvArr[1], vEql, 0, hsv);
//	printf("%s\n", hsv->channelSeq);
	cvCvtColor(hsv, eql, CV_HSV2BGR);
	cvReleaseImage(&hsv);
	for(int i = 0; i < 3; ++i) {
		cvReleaseImage(&hsvArr[i]);
	}
	cvReleaseImage(&vEql);

//	IplImage *rgb[3];
//	IplImage *rgbEql[3];
//	for(int i = 0; i < 3; ++i) {
//		rgb[i] = cvCreateImage(cvGetSize(img), 8, 1);
//		rgbEql[i] = cvCreateImage(cvGetSize(img), 8, 1);
//	}
//	cvSplit(img, rgb[0], rgb[1], rgb[2], 0);
//	for(int i = 0; i < 3; ++i) {
//		cvEqualizeHist(rgb[i], rgbEql[i]);
//	}
//	cvMerge(rgbEql[0], rgbEql[1], rgbEql[2], 0, eql);
//	for(int i = 0; i < 3; ++i) {
//		cvReleaseImage(&rgb[i]);
//		cvReleaseImage(&rgbEql[i]);
//	}
}

 unsigned char* newTextureFormat(IplImage *tmpImage){
	 unsigned char* dstData =new unsigned char[tmpImage->width*tmpImage->height*3];
//	 unsigned char* dstData = (unsigned char*) calloc(tmpImage->width*tmpImage->height*3, sizeof(unsigned char));
	 for(int u=0;u<tmpImage->height;u++){
		 for(int y=0;y<tmpImage->width;y++){
			 dstData[(tmpImage->width*u+y)*3]=(unsigned char)tmpImage->imageData[tmpImage->widthStep*(tmpImage->height-u-1)+y*3+2];
			 dstData[(tmpImage->width*u+y)*3+1]=(unsigned char)tmpImage->imageData[tmpImage->widthStep*(tmpImage->height-u-1)+y*3+1];
			 dstData[(tmpImage->width*u+y)*3+2]=(unsigned char)tmpImage->imageData[tmpImage->widthStep*(tmpImage->height-u-1)+y*3];
		 }
	 }
	 return dstData;
 }
 GLuint newBindTexture(IplImage *tmpImage){
	 unsigned char *imgData = newTextureFormat(tmpImage);
	 //unsigned char *imgData = 0;
	 GLuint texture;
	 glGenTextures(1,&texture);
	 glBindTexture(GL_TEXTURE_2D,texture);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	 glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,tmpImage->width,tmpImage->height,0,GL_RGB,GL_UNSIGNED_BYTE,imgData);
	 delete [] imgData;
	 return texture;
 }

IplImage* newScaleImage(IplImage* tmpImage){
	CvPoint2D32f srcTri[3],dstTri[3];
	CvMat* warp_mat =cvCreateMat(2,3,CV_32FC1);
	IplImage *dst=cvCreateImage(cvSize(256,256),tmpImage->depth,tmpImage->nChannels);
	cvZero(dst);
	srcTri[0].x=0;
	srcTri[0].y=0;
	srcTri[1].x=tmpImage->width-1;
	srcTri[1].y=0;
	srcTri[2].x=0;
	srcTri[2].y=tmpImage->height-1;
	dstTri[0].x=0;
	dstTri[0].y=0;
	dstTri[1].x=255;
	dstTri[1].y=0;
	dstTri[2].x=0;
	dstTri[2].y=255;
	cvGetAffineTransform(srcTri,dstTri,warp_mat);
	cvWarpAffine(tmpImage,dst,warp_mat);
	cvReleaseMat(&warp_mat);
	return dst;
}

void GLWidget::savePanoImage(QString fileName)
{
	QImage image = grabFrameBuffer();
	image.save(fileName);
}

 void GLWidget::showPanoFromPic(QStringList srcList){
	 if(timer!=NULL)
	 {
		 timer->stop();
		 free(timer);
	 }
	 numImg = srcList.count();
	 NUM_PIC = numImg;
	 IplImage **img = new IplImage*[numImg];
	 IplImage **imgColor=new IplImage*[numImg];
	 IplImage **imgCrop = new IplImage*[numImg];
	 IplImage **imgEqualize = new IplImage*[numImg];
	 IplImage **eig = new IplImage*[numImg];
	 IplImage **temp = new IplImage*[numImg];
	 IplImage **pyr = new IplImage*[numImg];
	 char **status = new char*[numImg];
	 Point **points = new Point*[numImg];
	 MappingPoint **mappingPoints = new MappingPoint*[numImg];
	 textures = new GLuint[numImg];
	 int numMapping[numImg];

	 	int i, j, k;
	 	for(i = 0; i < numImg; ++i)
	 	{
	 		img[i] = cvLoadImage(srcList.at(i).toLocal8Bit().data(), 0);
	 		imgCrop[i] = cvCreateImage(cvSize(CROP_WIDTH, img[i]->height), 8, 1);
	 		imgEqualize[i] = cvCreateImage(cvGetSize(imgCrop[i]), 8, 1);
	 		eig[i] = cvCreateImage(cvGetSize(imgCrop[i]), IPL_DEPTH_32F, 1);
	 		temp[i] = cvCreateImage(cvGetSize(imgCrop[i]), IPL_DEPTH_32F, 1);
	 		pyr[i] = cvCreateImage(cvGetSize(imgCrop[i]), 8, 1);
	 		status[i] = new char[MAX_POINTS];
	 		points[i] = new Point[MAX_POINTS];
	 		mappingPoints[i] = new MappingPoint[MAX_POINTS];
	 		imgColor[i] = cvLoadImage(srcList.at(i).toLocal8Bit().data());
			IplImage *dst = newScaleImage(imgColor[i]);
			IplImage *dstEqualized = cvCreateImage(cvGetSize(dst), dst->depth, 3);
			equalizeColorImage(dst, dstEqualized);
	 		textures[i] = newBindTexture(dst);//bindTexture(QPixmap(srcList.at(i)),GL_TEXTURE_2D);
	 		cvReleaseImage(&dst);
	 	}

#ifdef DELAUNAY
	 	getTrianglesAllPairs(img, imgCrop, imgEqualize, eig, temp, pyr, status, points, numImg, mappingPoints, numMapping);
#endif
	 	//insert code here
	 	for(int i =0;i<numImg;i++){
	 		printf("count=%d\n",numMapping[i]);
	 	}
	 	pic = mappingPoints;
	 	this->numMapping = numMapping;
	 	glMatrixMode(GL_PROJECTION);
	 	glLoadIdentity();
#ifndef Drag_Test
		gluOrtho2D(0, 1*NUM_PIC, 0, 1);
#else
		if(GL_WINDOWS_WIDTH<=NUM_PIC)
			gluOrtho2D(0,GL_WINDOWS_WIDTH,0,1);
		else gluOrtho2D(0,1*NUM_PIC,0,1);
#endif
		glMatrixMode(GL_MODELVIEW);
	 	updateGL();
	 	for(i = 0; i < numImg; ++i)
	 	{
	 		cvReleaseImage(&imgColor[i]);
	 		cvReleaseImage(&img[i]);
	 		cvReleaseImage(&imgCrop[i]);
	 		cvReleaseImage(&imgEqualize[i]);
	 		cvReleaseImage(&eig[i]);
	 		cvReleaseImage(&temp[i]);
	 		cvReleaseImage(&pyr[i]);
	 		delete [] status[i];
	 		delete [] points[i];
	 		delete [] mappingPoints[i];
	 	}
	 	delete [] imgColor;
	 	delete [] img;
	 	delete [] imgCrop;
	 	delete [] imgEqualize;
	 	delete [] eig;
	 	delete [] temp;
	 	delete [] pyr;
	 	delete [] status;
	 	delete [] points;
	 	delete [] mappingPoints;


 }
 CvCapture **capture = 0;
 IplImage **frame=0;
 IplImage **img = 0;
 IplImage** tempImg = 0;
 IplImage **imgCrop = 0;
 IplImage **imgEqualize = 0;
 IplImage **eig = 0;
 IplImage **temp = 0;
 IplImage **pyr = 0;
 char **status = 0;
 Point **points = 0;
 MappingPoint **mappingPoints = 0;
 int *numMapping = 0;
 bool test2=true;

 bool isRec = false;
 CvVideoWriter *writer = NULL;
IplImage *recordBuffer = NULL;

 //
IplImage **eqlColor = 0;
// IplImage *dstAnimateTemp;
 //
 void fdManagement(int numCam){
	 fd = new int[numCam];
	 if(numCam>0){
		 fd[0]=open("/dev/video0",O_RDWR);
//		 ::close(fd[0]);
	 }
	 if(numCam>1){
		 fd[1]=open("/dev/video1",O_RDWR);
//		 ::close(fd[1]);
	 }
	 if(numCam>2){
		 fd[2]=open("/dev/video2",O_RDWR);
//		 ::close(fd[2]);
	 }
	 if(numCam>3){
		 fd[3]=open("/dev/video3",O_RDWR);
//		 ::close(fd[3]);
	 }
	 if(numCam>4){
		 fd[4]=open("/dev/video4",O_RDWR);
//		 ::close(fd[4]);
	 }
	 if(numCam>5){
		 fd[5]=open("/dev/video5",O_RDWR);
//		 ::close(fd[5]);
	 }
	 if(numCam>6){
		 fd[6]=open("/dev/video6",O_RDWR);
//		 ::close(fd[6]);
	 }
	 if(numCam>7){
	 	 fd[7]=open("/dev/video7",O_RDWR);
//	 	 ::close(fd[7]);
	 }
	 if(numCam>8){
	 	 fd[8]=open("/dev/video8",O_RDWR);
//	 	 ::close(fd[8]);
	 }

	 if(numCam>0){
//		 fd[0]=open("/dev/video0",O_RDWR);
		 ::close(fd[0]);
	 }
	 if(numCam>1){
//		 fd[1]=open("/dev/video1",O_RDWR);
		 ::close(fd[1]);
	 }
	 if(numCam>2){
//		 fd[2]=open("/dev/video2",O_RDWR);
		 ::close(fd[2]);
	 }
	 if(numCam>3){
//		 fd[3]=open("/dev/video3",O_RDWR);
		 ::close(fd[3]);
	 }
	 if(numCam>4){
//		 fd[4]=open("/dev/video4",O_RDWR);
		 ::close(fd[4]);
	 }
	 if(numCam>5){
//		 fd[5]=open("/dev/video5",O_RDWR);
		 ::close(fd[5]);
	 }
	 if(numCam>6){
//		 fd[6]=open("/dev/video6",O_RDWR);
		 ::close(fd[6]);
	 }
	 if(numCam>7){
//	 	 fd[7]=open("/dev/video7",O_RDWR);
	 	 ::close(fd[7]);
	 }
	 if(numCam>8){
//	 	 fd[8]=open("/dev/video8",O_RDWR);
	 	 ::close(fd[8]);
	 }
//	 if(numCam>0){
//		 fd[0]=open("/dev/video0",O_RDWR);
//		 ::close(fd[0]);
//	 }
//	 if(numCam>1){
//		 fd[1]=open("/dev/video1",O_RDWR);
//		 ::close(fd[1]);
//	 }
//	 if(numCam>2){
//		 fd[2]=open("/dev/video2",O_RDWR);
//		 ::close(fd[2]);
//	 }
//	 if(numCam>3){
//		 fd[3]=open("/dev/video3",O_RDWR);
//		 ::close(fd[3]);
//	 }
//	 if(numCam>4){
//		 fd[4]=open("/dev/video4",O_RDWR);
//		 ::close(fd[4]);
//	 }
//	 if(numCam>5){
//		 fd[5]=open("/dev/video5",O_RDWR);
//		 ::close(fd[5]);
//	 }
//	 if(numCam>6){
//		 fd[6]=open("/dev/video6",O_RDWR);
//		 ::close(fd[6]);
//	 }
//	 if(numCam>7){
//	 	 fd[7]=open("/dev/video7",O_RDWR);
//	 	 ::close(fd[7]);
//	 }
//	 if(numCam>8){
//	 	 fd[8]=open("/dev/video8",O_RDWR);
//	 	 ::close(fd[8]);
//	 }
}
void GLWidget::showPanoFromCam(int numCam)
{
//	 printf("bbb\n");
	fdManagement(numCam);
	 numImg = numCam;
	 NUM_PIC = numImg;
	 capture = new CvCapture*[numImg];
	 textures = new GLuint[numImg];
	 frame = new IplImage*[numImg];
	 img = new IplImage*[numImg];
	 tempImg = new IplImage*[numImg];
	 imgCrop = new IplImage*[numImg];
	 imgEqualize = new IplImage*[numImg];
	eig = new IplImage*[numImg];
	temp = new IplImage*[numImg];
	pyr = new IplImage*[numImg];
	status = new char*[numImg];
	points = new Point*[numImg];
	mappingPoints = new MappingPoint*[numImg];
	numMapping = new int[numImg];
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	eqlColor = new IplImage*[numImg];
#ifndef Drag_Test
		gluOrtho2D(0, 1*NUM_PIC, 0, 1);
#else
		if(GL_WINDOWS_WIDTH<=NUM_PIC)
			gluOrtho2D(0,GL_WINDOWS_WIDTH,0,1);
		else gluOrtho2D(0,1*NUM_PIC,0,1);
#endif
	glMatrixMode(GL_MODELVIEW);

//	cvNamedWindow("camera1");
//	cvNamedWindow("camera2");
//	cvNamedWindow("camera3");
//	cvNamedWindow("camera4");

 	int i, j, k;
 	for(i = 0; i < numImg; ++i)
 	{
 		printf("cam %d\n", i);
// 		printf("dddd\n");
 		if(i==8)
 			capture[i] = cvCaptureFromFile("/dev/video8");
 		else capture[i] = cvCaptureFromCAM(i);
// 		printf("aaaa\n");
 		if(!capture[i]){
 			fprintf(stderr,"Camera %d could not initialize capturing...\n",i);
 			return;
 		}
#ifdef MANUEL_CAMERA_SETTING
 		manuel_camera_setting(fd[i],i);
 		printf("i=%d, fd[i]=%d\n",i,fd[i]);
#else
 		restore_camera_setting(fd[i]);
 		//for(int j = 0;j<65535;j++);
#endif

 		frame[i] = cvQueryFrame(capture[i]);
 		img[i] = cvCreateImage(cvGetSize(frame[i]),8,3);
 		tempImg[i] = cvCreateImage(cvGetSize(img[i]), 8, 1);
 		imgCrop[i] = cvCreateImage(cvSize(CROP_WIDTH, frame[i]->height), 8, 1);
 		imgEqualize[i] = cvCreateImage(cvGetSize(imgCrop[i]), 8, 1);
 		eig[i] = cvCreateImage(cvGetSize(imgCrop[i]), IPL_DEPTH_32F, 1);
 		temp[i] = cvCreateImage(cvGetSize(imgCrop[i]), IPL_DEPTH_32F, 1);
 		pyr[i] = cvCreateImage(cvGetSize(imgCrop[i]), 8, 1);
 		status[i] = new char[MAX_POINTS];
 		points[i] = new Point[MAX_POINTS];
 		mappingPoints[i] = new MappingPoint[MAX_POINTS];
// 		textures[i] = bindTexture(QPixmap(srcList.at(i)),GL_TEXTURE_2D);

 		eqlColor[i] = cvCreateImage(cvGetSize(img[i]), 8, 3);
 	}

// 	printf("sss\n");
//
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(100);

//	for(i = 0; i < numImg; ++i)
//	{
//		cvReleaseImage(&img[i]);
//		cvReleaseImage(&imgCrop[i]);
//		cvReleaseImage(&imgEqualize[i]);
//		cvReleaseImage(&eig[i]);
//		cvReleaseImage(&temp[i]);
//		cvReleaseImage(&pyr[i]);
//		delete [] status[i];
//		delete [] points[i];
//		delete [] mappingPoints[i];
//	}
//	delete [] img;
//	delete [] imgCrop;
//	delete [] imgEqualize;
//	delete [] eig;
//	delete [] temp;
//	delete [] pyr;
//	delete [] status;
//	delete [] points;
//	delete [] mappingPoints;

}


void GLWidget::showPanoFromVideo(QStringList srcList){
	 if(timer!=NULL)
	 {
		 timer->stop();
		 free(timer);
	 }
	numImg = srcList.count();
	NUM_PIC = numImg;
	capture = new CvCapture*[numImg];
	textures = new GLuint[numImg];
	frame = new IplImage*[numImg];
	img = new IplImage*[numImg];
	tempImg = new IplImage*[numImg];
	imgCrop = new IplImage*[numImg];
	imgEqualize = new IplImage*[numImg];
	eig = new IplImage*[numImg];
	temp = new IplImage*[numImg];
	pyr = new IplImage*[numImg];
	status = new char*[numImg];
	points = new Point*[numImg];
	mappingPoints = new MappingPoint*[numImg];
	numMapping = new int[numImg];
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	eqlColor = new IplImage*[numImg];
#ifndef Drag_Test
		gluOrtho2D(0, 1*NUM_PIC, 0, 1);
#else
		if(GL_WINDOWS_WIDTH<=NUM_PIC)
			gluOrtho2D(0,GL_WINDOWS_WIDTH,0,1);
		else gluOrtho2D(0,1*NUM_PIC,0,1);
#endif
	glMatrixMode(GL_MODELVIEW);

	 	int i, j, k;
	 	for(i = 0; i < numImg; ++i)
	 	{
//	 		capture[i] = cvCaptureFromCAM(i);
	 		capture[i] = cvCaptureFromAVI(srcList.at(i).toLocal8Bit().data());
	 		if(!capture[i]){
	 			fprintf(stderr,"Camera %d could not initialize capturing...\n",i);
	 			return;
	 		}
	 		frame[i] = cvQueryFrame(capture[i]);
	 		img[i] = cvCreateImage(cvGetSize(frame[i]),8,3);
	 		tempImg[i] = cvCreateImage(cvGetSize(img[i]), 8, 1);
	 		imgCrop[i] = cvCreateImage(cvSize(CROP_WIDTH, frame[i]->height), 8, 1);
	 		imgEqualize[i] = cvCreateImage(cvGetSize(imgCrop[i]), 8, 1);
	 		eig[i] = cvCreateImage(cvGetSize(imgCrop[i]), IPL_DEPTH_32F, 1);
	 		temp[i] = cvCreateImage(cvGetSize(imgCrop[i]), IPL_DEPTH_32F, 1);
	 		pyr[i] = cvCreateImage(cvGetSize(imgCrop[i]), 8, 1);
	 		status[i] = new char[MAX_POINTS];
	 		points[i] = new Point[MAX_POINTS];
	 		mappingPoints[i] = new MappingPoint[MAX_POINTS];
	// 		textures[i] = bindTexture(QPixmap(srcList.at(i)),GL_TEXTURE_2D);

	 		eqlColor[i] = cvCreateImage(cvGetSize(img[i]), 8, 3);

//	 		img[i] = cvLoadImage(srcList.at(i).toLocal8Bit().data(), 0);
//	 		imgCrop[i] = cvCreateImage(cvSize(CROP_WIDTH, img[i]->height), 8, 1);
//	 		imgEqualize[i] = cvCreateImage(cvGetSize(imgCrop[i]), 8, 1);
//	 		eig[i] = cvCreateImage(cvGetSize(imgCrop[i]), IPL_DEPTH_32F, 1);
//	 		temp[i] = cvCreateImage(cvGetSize(imgCrop[i]), IPL_DEPTH_32F, 1);
//	 		pyr[i] = cvCreateImage(cvGetSize(imgCrop[i]), 8, 1);
//	 		status[i] = new char[MAX_POINTS];
//	 		points[i] = new Point[MAX_POINTS];
//	 		mappingPoints[i] = new MappingPoint[MAX_POINTS];
//	 		imgColor[i] = cvLoadImage(srcList.at(i).toLocal8Bit().data());
//			IplImage *dst = newScaleImage(imgColor[i]);
//			IplImage *dstEqualized = cvCreateImage(cvGetSize(dst), dst->depth, 3);
//			equalizeColorImage(dst, dstEqualized);
//	 		textures[i] = newBindTexture(dst);//bindTexture(QPixmap(srcList.at(i)),GL_TEXTURE_2D);
//	 		cvReleaseImage(&dst);
	 	}
		timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
		timer->start(32);

}

void GLWidget::animate(void){
	 for(int i = 0; i < numImg; ++i)
	 {
		 frame[i] = cvQueryFrame(capture[i]);
		 if(!frame[i])
		 {
			 break;
		 }
		 cvCopy(frame[i],img[i],0);
		 colorEqualize(img[i], eqlColor[i]);
#ifdef DELAUNAY
		 cvCvtColor(img[i], tempImg[i], CV_BGR2GRAY);
#endif
	}

#ifdef DELAUNAY
	getTrianglesAllPairs(tempImg, imgCrop, imgEqualize, eig, temp, pyr, status, points, numImg, mappingPoints, numMapping);
#endif

	if(textures!=NULL){
		for(int i = 0;i<numImg;i++)
			 glDeleteTextures(1,&textures[i]);
		delete [] textures;
	}
	textures = new GLuint[numImg];
	for(int i =0;i<numImg;i++){
		textures[i] = 0;
	}
	for(int i =0;i<numImg;i++){
		IplImage *dst = newScaleImage(eqlColor[i]);
		textures[i]= newBindTexture(dst);
		cvReleaseImage(&dst);
	}

	pic = mappingPoints;
 	this->numMapping = numMapping;
	updateGL();

	if(isRec) {
		QImage image = grabFrameBuffer();
		qImageToCv(&image, recordBuffer);
		cvWriteFrame(writer, recordBuffer);
	}

}

void GLWidget::startRec(QString fileName) {

//	writer = cvCreateVideoWriter(video, CV_FOURCC('X','V','I','D'),
//			15.00, cvSize(frame[i]->width, frame[i]->height));
	QImage image = grabFrameBuffer();
	recordBuffer = cvCreateImage(cvSize(image.width(), image.height()), 8, 3);
	qImageToCv(&image, recordBuffer);
	isRec = true;
	writer = cvCreateVideoWriter(fileName.toLocal8Bit().data(), CV_FOURCC('X','V','I','D'),
			15.00, cvSize(recordBuffer->width, recordBuffer->height));
}

void GLWidget::stopRec() {
	cvReleaseImage(&recordBuffer);
	cvReleaseVideoWriter(&writer);
	isRec = false;
}

 void GLWidget::paintGL()
  {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glLoadIdentity();
      glPushMatrix();
      glEnable(GL_TEXTURE_2D);
      if(pic == 0)
    	  return;
      //qDebug()<<"pLeft.x="<<pic[0][0].pLeft[0].x;
//      fprintf(stderr,"pLeft.x=",pic[0][0].pLeft[0].x);
      /** GEN FAKE**/
      Point **pTexImage = NULL;//genPTexImageBG(pic,true);
      Point **pPosImage = NULL;//genPPosImageBG(pic,true);

      float *offset = NULL;//calcOffset(pTexImage,pPosImage,true);

      int count;
      for(int i = 0;i<NUM_PIC-1;i++){
    	  count = numMapping[i];
		  MappingPoint *mp=pic[i];
		  //drawTriImage(textures[i],mp,count,offset[i],false);
      }
      /*************/
      drawBGImage(textures,pTexImage,pPosImage,TYPE_TEXTURE_MAPPING,picPosition);
      test = false;
//      free(offset);
//      for(int i =0;i<NUM_PIC;i++){
//    	  free(pTexImage[i]);
//      }
//      free(pTexImage);
//      for(int i = 0;i<NUM_PIC;i++){
//    	  free(pPosImage[i]);
//      }
//      free(pPosImage);
	  glPopMatrix();
	  glDisable(GL_TEXTURE_2D);
	  glFlush();
}

bool checkFirst=true;
 void GLWidget::resizeGL(int width, int height)
{
      int side = qMin(width, height);
      if(checkFirst){
		glViewport(0,0,width,height);//(width - side) / 2, (height - side) / 2, side, side);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
#ifndef Drag_Test
		gluOrtho2D(0, 1*NUM_PIC, 0, 1);
#else
		if(GL_WINDOWS_WIDTH<=NUM_PIC)
			gluOrtho2D(0,GL_WINDOWS_WIDTH,0,1);
		else gluOrtho2D(0,1*NUM_PIC,0,1);
#endif
		glMatrixMode(GL_MODELVIEW);
		checkFirst=false;
      }
 }


 QPoint dragStartPosition;
 QPoint addPosition;
 QPoint newPosition;

void GLWidget::mouseMoveEvent(QMouseEvent *event){
	if(!(event->buttons() & Qt::LeftButton))
		return;
	if((event->pos()-dragStartPosition).manhattanLength()<QApplication::startDragDistance())
		return;
	addPosition=event->pos()-newPosition;
	newPosition=event->pos();
	if(GL_WINDOWS_WIDTH<=NUM_PIC)
		(*picPosition).setX((*picPosition).x()+addPosition.x()*GL_WINDOWS_WIDTH/DEFAULT_MAINWINDOW_WIDTH);
	else (*picPosition).setX((*picPosition).x()+addPosition.x()*NUM_PIC/DEFAULT_MAINWINDOW_WIDTH);

	//qDebug()<<event->pos();
	updateGL();
}
void GLWidget::mousePressEvent(QMouseEvent *event){
	if(event->button()==Qt::LeftButton){
		dragStartPosition=event->pos();
		newPosition = dragStartPosition;
	}

}
