/*
 * imageFunction.h
 *
 *  Created on: Jan 1, 2009
 *      Author: Administrator
 */

#ifndef IMAGEFUNCTION_H_
#define IMAGEFUNCTION_H_
#include <QtOpenGL>
#include <QtGui>
#include "cv.h"
#include "highgui.h"

#include "alldefine.h"

extern int NUM_PIC;

/*** for drag slide ***/
extern int swap;
/**********************/

extern GLuint *textures;
extern MappingPoint **pic;
extern int kCount;
extern MappingPoint *kMapping;
extern bool test;

Point **genPTexImageBG(MappingPoint **mapPoint,bool fake);
Point **genPPosImageBG(MappingPoint **mapPoint,bool fake);

void drawBGImage(GLuint textureArray[],Point **pTexImage,Point **pPosImage,int type,QPointF *picPosition);
void drawTriImage(GLuint texture,MappingPoint *mp,int triCount,float offset,bool drawFlag);
void TestOnePic();
float *calcOffset(Point **pTexImage,Point **pPosImage,bool fake);
QImage cvToQImage(IplImage *cvImage);
void qImageToCv(QImage *src, IplImage *dst);
void equalizeColorImage(IplImage *src, IplImage *dst);
#endif /* IMAGEFUNCTION_H_ */
