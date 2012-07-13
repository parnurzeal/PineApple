/*
 * imageFunction.cpp
 *
 *  Created on: Jan 1, 2009
 *      Author: Administrator
 */

#ifndef IMAGEFUNCTION_CPP_
#define IMAGEFUNCTION_CPP_

#include "imageFunction.h"
#include "cv.h"
#include "highgui.h"


int swap=0; // for drag slide
int kCount=0;
bool test = true;
MappingPoint **pic=NULL;
MappingPoint *kMapping=NULL;
GLuint *textures=NULL;

Point **genPTexImageBG(MappingPoint **mapPoint,bool fake){
	Point **pTexImage= new Point*[NUM_PIC];
	for(int i = 0;i<NUM_PIC;i++)
		pTexImage[i] = new Point[4];
	if(!fake){
		pTexImage[0][0].x=0;	pTexImage[0][0].y=0;
		pTexImage[0][1].x=0;	pTexImage[0][1].y=1;
		pTexImage[0][2].x=mapPoint[0][0].pLeft[0].x;	pTexImage[0][2].y=1;
		pTexImage[0][3].x=mapPoint[0][0].pLeft[0].x;	pTexImage[0][3].y=0;
		for(int i = 1;i<NUM_PIC-1;i++){
			pTexImage[i][0].x=mapPoint[i-1][0].pRight[0].x;	pTexImage[i][0].y=0;
			pTexImage[i][1].x=mapPoint[i-1][0].pRight[0].x;	pTexImage[i][1].y=1;
			pTexImage[i][2].x=mapPoint[i][0].pLeft[0].x;	pTexImage[i][2].y=1;
			pTexImage[i][3].x=mapPoint[i][0].pLeft[0].x;	pTexImage[i][3].y=0;
			//if(test) printf("pTexImage[i][1].x = %f pTexImage[i][2].x = %f\n",pTexImage[i][1].x,pTexImage[i][2].x);
		}
		pTexImage[NUM_PIC-1][0].x=mapPoint[NUM_PIC-2][0].pRight[0].x;	pTexImage[NUM_PIC-1][0].y=0;
		pTexImage[NUM_PIC-1][1].x=mapPoint[NUM_PIC-2][0].pRight[0].x;	pTexImage[NUM_PIC-1][1].y=1;
		pTexImage[NUM_PIC-1][2].x=1;	pTexImage[NUM_PIC-1][2].y=1;
		pTexImage[NUM_PIC-1][3].x=1;	pTexImage[NUM_PIC-1][3].y=0;
	}else{

	}
	return pTexImage;
}
Point **genPPosImageBG(MappingPoint **mapPoint,bool fake){
	Point **pPosImage = new Point*[NUM_PIC];
	float tmpX=0;
	float tmpY=0;
	for(int i=0;i<NUM_PIC;i++)
		pPosImage[i]=new Point[4];
	if(!fake){
		pPosImage[0][0].x=tmpX;	pPosImage[0][0].y=0;
		pPosImage[0][1].x=tmpX;	pPosImage[0][1].y=1;
		tmpX = mapPoint[0][0].pLeft[0].x;
		pPosImage[0][2].x=tmpX;	pPosImage[0][2].y=1;
		pPosImage[0][3].x=tmpX;	pPosImage[0][3].y=0;
		for(int i =1;i<NUM_PIC-1;i++){
			//tmpY=mapPoint[0][0].pLeft[0].y-mapPoint[0][0].pRight[0].y;
			//printf("tmpY=%f\n",tmpY);
			pPosImage[i][0].x=tmpX; pPosImage[i][0].y=0+tmpY;
			pPosImage[i][1].x=tmpX; pPosImage[i][1].y=1+tmpY;
			tmpX+=mapPoint[i][0].pLeft[0].x-mapPoint[i-1][0].pRight[0].x;
			pPosImage[i][2].x=tmpX; pPosImage[i][2].y=1+tmpY;
			pPosImage[i][3].x=tmpX; pPosImage[i][3].y=0+tmpY;
		}
		//tmpY=mapPoint[0][0].pLeft[0].y-mapPoint[0][0].pRight[0].y;
		//printf("tmpY=%f %f %f\n",tmpY,mapPoint[0][0].pLeft[0].y,mapPoint[0][0].pRight[0].y);
		pPosImage[NUM_PIC-1][0].x=tmpX;	pPosImage[NUM_PIC-1][0].y=0+tmpY;
		pPosImage[NUM_PIC-1][1].x=tmpX; pPosImage[NUM_PIC-1][1].y=1+tmpY;
		tmpX+=1-mapPoint[NUM_PIC-2][0].pRight[0].x;
		pPosImage[NUM_PIC-1][2].x=tmpX; pPosImage[NUM_PIC-1][2].y=1+tmpY;
		pPosImage[NUM_PIC-1][3].x=tmpX; pPosImage[NUM_PIC-1][3].y=0+tmpY;
		//if(test){
			//	for(int i= 0;i<NUM_PIC;i++){
			//		printf("pPosImage[%d][1].x = %f pPosImage[%d][2].x = %f\n",i,pPosImage[i][1].x,i,pPosImage[i][2].x);
			//	}
			//}
	}else{

	}
	return pPosImage;
}

void drawBGImage(GLuint textureArray[],Point **pTexImage,Point **pPosImage,int type,QPointF *picPosition){
	glEnable(GL_TEXTURE_2D);
	if(type==1){
		for(int i = 0;i<NUM_PIC;i++){
			glBindTexture(GL_TEXTURE_2D,textureArray[i]);
			glBegin(GL_QUADS);
				glTexCoord2f(pTexImage[i][0].x,pTexImage[i][0].y);
				glVertex2f(pPosImage[i][0].x+(*picPosition).x()
						,pPosImage[i][0].y);
				glTexCoord2f(pTexImage[i][1].x,pTexImage[i][1].y);
				glVertex2f(pPosImage[i][1].x+(*picPosition).x()
						,pPosImage[i][1].y);
				glTexCoord2f(pTexImage[i][2].x,pTexImage[i][2].y);
				glVertex2f(pPosImage[i][2].x+(*picPosition).x()
						,pPosImage[i][2].y);
				glTexCoord2f(pTexImage[i][3].x,pTexImage[i][3].y);
				glVertex2f(pPosImage[i][3].x+(*picPosition).x()
						,pPosImage[i][3].y);
			glEnd();
			if(test){
	//			printf("pTexImage[%d][1].x = %f pTexImage[%d][2].x = %f\n",i,pTexImage[i][1].x,i,pTexImage[i][2].x);
	//			printf("   pPosImage[%d][1].x = %f pPosImage[%d][2].x = %f\n",i,pPosImage[i][1].x,i,pPosImage[i][2].x);

			}
		}
	}else if(type==2){
		GLuint *tmpTextureArray = new GLuint[NUM_PIC];
		for(int i=0;i<NUM_PIC;i++)
			tmpTextureArray[i] = textureArray[i];
		if((*picPosition).x()>1.0)
		{
			swap++;
			if(swap==NUM_PIC)
				swap=0;
			(*picPosition).setX((*picPosition).x()-1.0);
		}else if((*picPosition).x()<-1.0){
			swap--;
			if(swap==-NUM_PIC)
				swap=0;
			(*picPosition).setX((*picPosition).x()+1.0);
		}
		if(swap>0){
			for(int i = 0;i<swap;i++){
				GLuint tmp;
				tmp = tmpTextureArray[NUM_PIC-1];
				for(int k=NUM_PIC-1;k>0;k--)
					tmpTextureArray[k]=tmpTextureArray[k-1];
				tmpTextureArray[0]=tmp;
			}
		}else if(swap<0){
			for(int i=swap;i<0;i++){
				GLuint tmp;
				tmp = tmpTextureArray[0];
				for(int k =0;k<NUM_PIC-1;k++)
					tmpTextureArray[k]=tmpTextureArray[k+1];
				tmpTextureArray[NUM_PIC-1]=tmp;
			}
		}
		for(int i = 0;i<NUM_PIC;i++){
			glBindTexture(GL_TEXTURE_2D,tmpTextureArray[i]);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0,0.0);
				glVertex2f(1.0*(i)+(*picPosition).x()
						,0.0);
				glTexCoord2f(0.0,1.0);
				glVertex2f(1.0*(i)+(*picPosition).x()
						,1.0);
				glTexCoord2f(1,1);
				glVertex2f(1.0*(i+1)+(*picPosition).x()
						,1.0);
				glTexCoord2f(1.0,0.0);
				glVertex2f(1.0*(i+1)+(*picPosition).x()
						,0.0);
			glEnd();
			//printf("%d ",i);
			if(test){
	//			printf("pTexImage[%d][1].x = %f pTexImage[%d][2].x = %f\n",i,pTexImage[i][1].x,i,pTexImage[i][2].x);
	//			printf("   pPosImage[%d][1].x = %f pPosImage[%d][2].x = %f\n",i,pPosImage[i][1].x,i,pPosImage[i][2].x);

			}
		}
		if((*picPosition).x()>0){
			glBindTexture(GL_TEXTURE_2D,tmpTextureArray[NUM_PIC-1]);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0,0.0);
				glVertex2f(-1.0+(*picPosition).x()
						,0.0);
				glTexCoord2f(0.0,1.0);
				glVertex2f(-1.0+(*picPosition).x()
						,1.0);
				glTexCoord2f(1,1);
				glVertex2f(0.0+(*picPosition).x()
						,1.0);
				glTexCoord2f(1.0,0.0);
				glVertex2f(0.0+(*picPosition).x()
						,0.0);
			glEnd();
		}
		if(NUM_PIC==GL_WINDOWS_WIDTH){
			if((*picPosition).x()<0){
				glBindTexture(GL_TEXTURE_2D,tmpTextureArray[0]);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0,0.0);
					glVertex2f(GL_WINDOWS_WIDTH+(*picPosition).x()
							,0.0);
					glTexCoord2f(0.0,1.0);
					glVertex2f(GL_WINDOWS_WIDTH+(*picPosition).x()
							,1.0);
					glTexCoord2f(1,1);
					glVertex2f(GL_WINDOWS_WIDTH+(*picPosition).x()+1.0
							,1.0);
					glTexCoord2f(1.0,0.0);
					glVertex2f(GL_WINDOWS_WIDTH+(*picPosition).x()+1.0
							,0.0);
				glEnd();
			}
		}
		//printf("\n");
	}else if(type==3){
		float x2=-0.038,y2=-0.028;//-0.065,y2=0.0345;//x2=-0.045,y2=0.031;
		float x3=-0.072,y3=0.049;//-0.038,y3=-0.0830;//x3=-0.033,y3=-0.0245;
		float x4=-0.044,y4=-0.008;//-0.054,y4=-0.011;//x4=-0.028,y4=-0.017;
		// x8->0=-0.044,y8->0=-0.008;
		float *xAdd = new float[NUM_PIC];
		float *yAdd = new float[NUM_PIC];
		if(NUM_PIC>0){ xAdd[0]=0;yAdd[0]=0;}
		if(NUM_PIC>1){ xAdd[1]=-0.045;yAdd[1]=0.031;}
		if(NUM_PIC>2){ xAdd[2]=-0.033;yAdd[2]=0.031-0.0245;}
		if(NUM_PIC>3){ xAdd[3]=-0.028;yAdd[3]=0.031-0.0245-0.017;}
		if(NUM_PIC>4){ xAdd[4]=-0.065;yAdd[4]=0.031-0.0245-0.017+0.0345;}
		if(NUM_PIC>5){ xAdd[5]=-0.038;yAdd[5]=0.031-0.0245-0.017+0.0345-0.0830;}
		if(NUM_PIC>6){ xAdd[6]=-0.054;yAdd[6]=0.031-0.0245-0.017+0.0345-0.0830-0.011;}
		if(NUM_PIC>7){ xAdd[7]=-0.038;yAdd[7]=0.031-0.0245-0.017+0.0345-0.0830-0.011-0.028;}
		if(NUM_PIC>8){ xAdd[8]=-0.072;yAdd[8]=0.031-0.0245-0.017+0.0345-0.0830-0.011-0.028+0.049;}
		float minY=0,maxY=0;
		for(int i=0;i<NUM_PIC;i++){
			if(yAdd[i]<minY)
				minY=yAdd[i];
			if(yAdd[i]>maxY)
				maxY=yAdd[i];
		}
		GLuint *tmpTextureArray = new GLuint[NUM_PIC];
		for(int i=0;i<NUM_PIC;i++)
			tmpTextureArray[i] = textureArray[i];
		if((*picPosition).x()>1.0)
		{
			swap++;
			if(swap==NUM_PIC)
				swap=0;
			(*picPosition).setX((*picPosition).x()-1.0);
		}else if((*picPosition).x()<-1.0){
			swap--;
			if(swap==-NUM_PIC)
				swap=0;
			(*picPosition).setX((*picPosition).x()+1.0);
		}
		if(swap>0){
			for(int i = 0;i<swap;i++){
				GLuint tmp;
				tmp = tmpTextureArray[NUM_PIC-1];
				for(int k=NUM_PIC-1;k>0;k--)
					tmpTextureArray[k]=tmpTextureArray[k-1];
				tmpTextureArray[0]=tmp;

				float tmpXAdd;
				tmpXAdd=xAdd[NUM_PIC-1];
				for(int k=NUM_PIC-1;k>0;k--)
					xAdd[k]=xAdd[k-1];
				xAdd[0]=tmpXAdd;

				float tmpYAdd;
				tmpYAdd=yAdd[NUM_PIC-1];
				for(int k =NUM_PIC-1;k>0;k--)
					yAdd[k]=yAdd[k-1];
				yAdd[0]=tmpYAdd;
			}
		}else if(swap<0){
			for(int i=swap;i<0;i++){
				GLuint tmp;
				tmp = tmpTextureArray[0];
				for(int k =0;k<NUM_PIC-1;k++)
					tmpTextureArray[k]=tmpTextureArray[k+1];
				tmpTextureArray[NUM_PIC-1]=tmp;

				float tmpXAdd;
				tmpXAdd=xAdd[0];
				for(int k = 0;k<NUM_PIC-1;k++)
					xAdd[k]=xAdd[k+1];
				xAdd[NUM_PIC-1]=tmpXAdd;

				float tmpYAdd;
				tmpYAdd=yAdd[0];
				for(int k = 0;k<NUM_PIC-1;k++)
					yAdd[k]=yAdd[k+1];
				yAdd[NUM_PIC-1]=tmpYAdd;
			}
		}
		for(int i = 0;i<NUM_PIC;i++){
			glBindTexture(GL_TEXTURE_2D,tmpTextureArray[i]);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0-xAdd[i],0.0);
				glVertex2f(1.0*i+(*picPosition).x()
						,0.0+yAdd[i]-maxY);
				glTexCoord2f(0.0-xAdd[i],1.0);
				glVertex2f(1.0*i+(*picPosition).x()
						,1.0+yAdd[i]-minY);
				glTexCoord2f(1,1);
				glVertex2f(1.0*(i+1)+(*picPosition).x()
						,1.0+yAdd[i]-minY);
				glTexCoord2f(1.0,0.0);
				glVertex2f(1.0*(i+1)+(*picPosition).x()
						,0.0+yAdd[i]-maxY);
			glEnd();
		}
		if((*picPosition).x()>0){
			glBindTexture(GL_TEXTURE_2D,tmpTextureArray[NUM_PIC-1]);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0-xAdd[NUM_PIC-1],0.0);
				glVertex2f(-1.0+(*picPosition).x()
						,0.0+yAdd[NUM_PIC-1]-maxY);
				glTexCoord2f(0.0-xAdd[NUM_PIC-1],1.0);
				glVertex2f(-1.0+(*picPosition).x()
						,1.0+yAdd[NUM_PIC-1]-minY);
				glTexCoord2f(1,1);
				glVertex2f(0.0+(*picPosition).x()
						,1.0+yAdd[NUM_PIC-1]-minY);
				glTexCoord2f(1.0,0.0);
				glVertex2f(0.0+(*picPosition).x()
						,0.0+yAdd[NUM_PIC-1]-maxY);
			glEnd();
		}
		if(NUM_PIC==GL_WINDOWS_WIDTH){
			if((*picPosition).x()<0){
				glBindTexture(GL_TEXTURE_2D,tmpTextureArray[0]);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0-xAdd[0],0.0);
					glVertex2f(GL_WINDOWS_WIDTH+(*picPosition).x()
							,0.0+yAdd[0]-maxY);
					glTexCoord2f(0.0-xAdd[0],1.0);
					glVertex2f(GL_WINDOWS_WIDTH+(*picPosition).x()
							,1.0+yAdd[0]-minY);
					glTexCoord2f(1,1);
					glVertex2f(GL_WINDOWS_WIDTH+(*picPosition).x()+1.0
							,1.0+yAdd[0]-minY);
					glTexCoord2f(1.0,0.0);
					glVertex2f(GL_WINDOWS_WIDTH+(*picPosition).x()+1.0
							,0.0+yAdd[0]-maxY);
				glEnd();
			}
		}
		/*
		glBindTexture(GL_TEXTURE_2D,textureArray[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);
			glVertex2f(0.0+(*picPosition).x()
					,0.0);
			glTexCoord2f(0.0,1.0);
			glVertex2f(0.0+(*picPosition).x()
					,1.0);
			glTexCoord2f(1,1);
			glVertex2f(1.0+(*picPosition).x()
					,1.0);
			glTexCoord2f(1.0,0.0);
			glVertex2f(1.0+(*picPosition).x()
					,0.0);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,textureArray[1]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);
			glVertex2f(1.0+x2+(*picPosition).x()
					,0.0+y2);
			glTexCoord2f(0.0,1.0);
			glVertex2f(1.0+x2+(*picPosition).x()
					,1.0+y2);
			glTexCoord2f(1,1);
			glVertex2f(2.0+x2+(*picPosition).x()
					,1.0+y2);
			glTexCoord2f(1.0,0.0);
			glVertex2f(2.0+x2+(*picPosition).x()
					,0.0+y2);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,textureArray[2]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);
			glVertex2f(2.0+x2+x3+(*picPosition).x()
					,0.0+y2+y3);
			glTexCoord2f(0.0,1.0);[1]=0.031;
		xAdd[2]=-0.033;yAdd
			glVertex2f(2.0+x2+x3+(*picPosition).x()
					,1.0+y2+y3);
			glTexCoord2f(1,1);
			glVertex2f(3.0+x2+x3+(*picPosition).x()
					,1.0+y2+y3);
			glTexCoord2f(1.0,0.0);
			glVertex2f(3.0+x2+x3+(*picPosition).x()
					,0.0+y2+y3);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,textureArray[3]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);
			glVertex2f(3.0+x2+x3+x4+(*picPosition).x()
					,0.0+y2+y3+y4);
			glTexCoord2f(0.0,1.0);
			glVertex2f(3.0+x2+x3+x4+(*picPosition).x()
					,1.0+y2+y3+y4);
			glTexCoord2f(1,1);
			glVertex2f(4.0+x2+x3+x4+(*picPosition).x()
					,1.0+y2+y3+y4);
			glTexCoord2f(1.0,0.0);
			glVertex2f(4.0+x2+x3+x4+(*picPosition).x()
					,0.0+y2+y3+y4);
		glEnd();*/
	}

	glDisable(GL_TEXTURE_2D);
}

void drawTriImage(GLuint texture,MappingPoint *mp,int triCount,float offset,bool drawFlag){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
	if(drawFlag){
		for(int i = 0;i<triCount;i++){
			glBegin(GL_TRIANGLES);
				glTexCoord2f(mp[i].pLeft[0].x,mp[i].pLeft[0].y);
				glVertex2f(mp[i].pRight[0].x+offset,mp[i].pRight[0].y);
				glTexCoord2f(mp[i].pLeft[1].x,mp[i].pLeft[1].y);
				glVertex2f(mp[i].pRight[1].x+offset,mp[i].pRight[1].y);
				glTexCoord2f(mp[i].pLeft[2].x,mp[i].pLeft[2].y);
				glVertex2f(mp[i].pRight[2].x+offset,mp[i].pRight[2].y);
			glEnd();
			if(test){
	//			printf("pLeft:: p1=(%4.0f,%4.0f) p2=(%4.0f,%4.0f) p3=(%4.0f,%4.0f)\n",
	//				mp[i].pLeft[0].x*160,120-120*mp[i].pLeft[0].y,
	//				mp[i].pLeft[1].x*160,120-120*mp[i].pLeft[1].y,
	//				mp[i].pLeft[2].x*160,120-120*mp[i].pLeft[2].y);
	//			printf("pRight::: p1=(%4.0f,%4.0f) p2=(%4.0f,%4.0f) p3=(%4.0f,%4.0f)\n\n",
	//				mp[i].pRight[0].x*160,120-120*mp[i].pRight[0].y,
	//				mp[i].pRight[1].x*160,120-120*mp[i].pRight[1].y,
	//				mp[i].pRight[2].x*160,120-120*mp[i].pRight[2].y);
	//			qDebug()<<mp[i].pRight[0].x*160<< "  " << 120-120*mp[i].pRight[0].y;
			}
		}
	}else{
	}
	glDisable(GL_TEXTURE_2D);
}
void TestOnePic(){
	glBindTexture(GL_TEXTURE_2D,textures[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0,1);
		glVertex2f(0,1);
		glTexCoord2f(0,0);
		glVertex2f(0,0);
		glTexCoord2f(1,0);
		glVertex2f(1,0);
		glTexCoord2f(1,1);
		glVertex2f(1,1);
	glEnd();
}

float *calcOffset(Point **pTexImage,Point **pPosImage,bool fake){
	float *offset = new float[NUM_PIC];
	float tmp=0;
	if(!fake){
		for(int i = 0;i<NUM_PIC-1;i++){
			offset[i] = pPosImage[i+1][0].x-pTexImage[i+1][0].x;
		}
	}else{

	}
	return offset;
}

QImage cvToQImage(IplImage *cvImage){
	char* tmpImage = cvImage->imageData;
	QImage out(QSize(cvImage->width,cvImage->height),QImage::Format_RGB32);
	for(int line=0;line<cvImage->height;line++){
		QRgb* outPixels =reinterpret_cast<QRgb*>(out.scanLine(line));
		for(int pos =0;pos<cvImage->width;pos++){
			int blue = tmpImage[line*cvImage->widthStep+pos*3];
			int green = tmpImage[line*cvImage->widthStep+pos*3+1];
			int red = tmpImage[line*cvImage->widthStep+pos*3+2];
			outPixels[pos] = qRgb(red,green,blue);
		}
	}
	return out;
}

void qImageToCv(QImage *src, IplImage *dst) {
	for(int line=0;line<src->height();line++){
		QRgb* outPixels =reinterpret_cast<QRgb*>(src->scanLine(line));
		for(int pos =0;pos<src->width();pos++){
			dst->imageData[line*dst->widthStep+pos*3] = (char) qBlue(outPixels[pos]);
			dst->imageData[line*dst->widthStep+pos*3+1] = (char) qGreen(outPixels[pos]);
			dst->imageData[line*dst->widthStep+pos*3+2] = (char) qRed(outPixels[pos]);
		}
	}
}

void equalizeColorImage(IplImage *src, IplImage *dst) {
	IplImage *split[3];
	for(int i = 0; i < 3; ++i) {
		split[i] = cvCreateImage(cvGetSize(src), src->depth, 1);
	}
	IplImage *hsvImg = cvCreateImage(cvGetSize(src), src->depth, 3);
	cvCvtColor(src, hsvImg, CV_BGR2HSV);
	cvSplit(hsvImg, split[0], split[1], split[2], 0);
	IplImage *equalizedV = cvCreateImage(cvGetSize(src), src->depth, 1);
	cvEqualizeHist(split[2], equalizedV);
	cvMerge(split[0], split[1], equalizedV, 0, hsvImg);
	cvCvtColor(hsvImg, dst, CV_HSV2BGR);
//	cvReleaseImage(&hsvImg);
//	cvReleaseImage(&equalizedV);
//	for(int i = 0; i < 3; ++i) {
//		cvReleaseImage(&split[i]);
//	}
}

#endif /* IMAGEFUNCTION_CPP_ */
