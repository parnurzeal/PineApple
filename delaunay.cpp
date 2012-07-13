#include <cv.h>
#include <stdio.h>
#include "delaunay.h"

#define THRESHOLD_ZERO -0.02
#define roundZero(x) (0.0 >= x && x >= THRESHOLD_ZERO ? 0.0 : x)

bool isSamePoint(CvPoint2D32f pt1, CvPoint2D32f pt2)
{
	return (pt1.x == pt2.x && pt1.y == pt2.y);
}
//left = true, right = false
void copyCropImage(IplImage *src, IplImage *crop, bool side)
{
	if(side)
	{
		cvSetImageROI(src, cvRect(src->width - crop->width, 0, crop->width, crop->height));
	} else
	{
		cvSetImageROI(src, cvRect(0, 0, crop->width, crop->height));
	}
	cvCopy(src, crop);
	cvResetImageROI(src);
}

CvSubdiv2D* initDelaunay(CvMemStorage *storage, CvRect rect)
{
	CvSubdiv2D* subdiv;
	subdiv = cvCreateSubdiv2D(
	   CV_SEQ_KIND_SUBDIV2D,
	   sizeof(*subdiv),
	   sizeof(CvSubdiv2DPoint),
	   sizeof(CvQuadEdge2D),
	   storage
	);
	cvInitSubdivDelaunay2D(subdiv, rect);
	return subdiv;
}

void getTrianglesOnePair(IplImage *leftImg, IplImage *rightImg,
		IplImage *leftCrop, IplImage *rightCrop,
		IplImage *leftEqualize, IplImage *rightEqualize,
		IplImage *eig, IplImage *temp,
		IplImage *leftPyr, IplImage *rightPyr, char *status,
		Point *leftPoints, Point *rightPoints,
		MappingPoint mappingPoints[], int *numMapping)
{
//	if(!leftImg || !leftCrop || !rightImg || !rightCrop) printf("asdf");
//	printf("%d %d %d %d %d %d\n", rightImg->width, rightImg->height, rightCrop->width, rightCrop->height,leftEqualize->width, leftEqualize->height);
	copyCropImage(leftImg, leftCrop, true);
	copyCropImage(rightImg, rightCrop, false);
	cvEqualizeHist(leftCrop, leftEqualize);
	cvEqualizeHist(rightCrop, rightEqualize);
	int count = MAX_POINTS;

	float qualityLevel = QUALITY_LEVEL, minDistance = MIN_DISTANCE;

	cvGoodFeaturesToTrack(leftEqualize, eig, temp,
			leftPoints, &count, qualityLevel, minDistance);
	cvFindCornerSubPix(leftEqualize, leftPoints, count,
			cvSize(WIN_SIZE, WIN_SIZE), cvSize(-1, -1),
			cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));
	cvCalcOpticalFlowPyrLK(leftEqualize, rightEqualize,
			leftPyr, rightPyr, leftPoints, rightPoints, count,
			cvSize(WIN_SIZE, WIN_SIZE), 3, status, 0,
			cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03), 0);

	//โค้ดนี้อาจใช้เวลาเยอะ
	//-----------
	CvRect rect = {0, 0, leftCrop->width, leftCrop->height};
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSubdiv2D* subdiv = initDelaunay(storage, rect);
	//-----------

	CvPoint2D32f tem;
	tem.x = 0.0;
	tem.y = 0.0;
	int i, j, k;
	for(i = 0; i < count; ++i)
	{
		if(status[i] && leftPoints[i].x > 0 && leftPoints[i].x < CROP_WIDTH && leftPoints[i].y > 0 && leftPoints[i].y < leftCrop->width)
		{
//			printf("%f %f\n", leftPoints[i].x, leftPoints[i].y);
			if(cvSubdiv2DLocate(subdiv, leftPoints[i], NULL) == CV_PTLOC_ERROR)
			{
				status[i] = 0;
				continue;
			}
			cvSubdivDelaunay2DInsert(subdiv, leftPoints[i]);
		}
	}

	int totalEdges = subdiv->edges->total;
	int elemSize = subdiv->edges->elem_size;
	CvSeqReader reader;
	Point tempPt[3];
	int ptsIndex[3];
	CvQuadEdge2D* qEdge;
	CvSubdiv2DEdge edge;
	int minPtIndex, minGroupIndex = 0;

	*numMapping = 0;
	cvStartReadSeq((CvSeq*) (subdiv->edges), &reader, 0);

	for(i = 0; i < count; ++i)
	{
		if(status[i])
		{
			minPtIndex = i;
			break;
		}
	}

	for(i = 0; i < totalEdges; ++i)
	{
		qEdge = (CvQuadEdge2D*) (reader.ptr);
		if(CV_IS_SET_ELEM(qEdge))
		{
			edge = (CvSubdiv2DEdge) qEdge;
			tempPt[0] = (cvSubdiv2DEdgeOrg(edge))->pt;
			tempPt[1] = (cvSubdiv2DEdgeDst(edge))->pt;
			edge = cvSubdiv2DGetEdge(edge, CV_NEXT_AROUND_LEFT);
			tempPt[2] = (cvSubdiv2DEdgeDst(edge))->pt;
			ptsIndex[0] = ptsIndex[1] = ptsIndex[2] = -1;
			for(j = 0; j < count; ++j)
			{
				if(!status[j]) continue;
				if(isSamePoint(tempPt[0], leftPoints[j]))
				{
					ptsIndex[0] = j;
				} else if(isSamePoint(tempPt[1], leftPoints[j]))
				{
					ptsIndex[1] = j;
				} else if(isSamePoint(tempPt[2], leftPoints[j]))
				{
					ptsIndex[2] = j;
				}
				if(ptsIndex[0] != -1 && ptsIndex[1] != -1 && ptsIndex[2] != -1)
				{
					break;
				}
			}
			float tempRatio[3][2];
			for(k = 0; k < 3 && j < count; ++k)
			{
				tempRatio[k][0] = rightPoints[ptsIndex[k]].x / rightImg->width;
				tempRatio[k][0] = roundZero(tempRatio[k][0]);
//				tempRatio[k][0] = 0.0 >= tempRatio[k][0] &&
//						tempRatio[k][0] >= THRESHOLD_ZERO ? 0.0 : tempRatio[k][0];
				tempRatio[k][1] = rightPoints[ptsIndex[k]].y / rightImg->height;
				tempRatio[k][1] = roundZero(tempRatio[k][1]);
//				tempRatio[k][1] = 0.0 >= tempRatio[k][1] &&
//						tempRatio[k][1] >= THRESHOLD_ZERO ? 0.0 : tempRatio[k][1];
			}
			if(j < count && cvTriangleArea(leftPoints[ptsIndex[0]],
					leftPoints[ptsIndex[1]],
					leftPoints[ptsIndex[2]]) > MIN_TRIANGLE_AREA &&
					tempRatio[0][0] >= 0.0 &&
					tempRatio[0][1] >= 0.0 &&
					tempRatio[1][0] >= 0.0 &&
					tempRatio[1][1] >= 0.0 &&
					tempRatio[2][0] >= 0.0 &&
					tempRatio[2][1] >= 0.0)
			{
				for(k = 0; k < 3; ++k)
				{
					mappingPoints[*numMapping].pLeft[k].x = (leftPoints[ptsIndex[k]].x + leftImg->width - leftCrop->width) / leftImg->width;
					mappingPoints[*numMapping].pLeft[k].y = leftPoints[ptsIndex[k]].y / leftImg->height;
					mappingPoints[*numMapping].pRight[k].x = tempRatio[k][0];
					mappingPoints[*numMapping].pRight[k].y = tempRatio[k][1];
				}
				(*numMapping)++;
			}
			CV_NEXT_SEQ_ELEM(elemSize, reader);
		}
	}

//	printf("minGroupIndex = %d\n", minGroupIndex);
//
//	for(i = 0; i < *numMapping; ++i)
//	{
//		for(j = 0; j < 3; ++j)
//		{
//			if(mappingPoints[i].leftPt[j].x == leftPoints[minPtIndex].x && mappingPoints[i].leftPt[j].y == leftPoints[minPtIndex].y)
//			{
//				minGroupIndex = j;
//			}
//		}
//	}
//	printf("minGroupIndex = %d\n", minGroupIndex);
//
//	printf("minPtIndex = %d, %f, %f\n", minPtIndex, (leftPoints[minPtIndex].x + leftImg->width - leftCrop->width) / leftImg->width, leftPoints[minPtIndex].y / leftImg->height);
////	printf("minGroupIndex = %d", minGroupIndex);
//
//
//	for(i = 0; i < count; ++i)
//	{
//		if(!status[i]) continue;
//		if(leftPoints[minPtIndex].x > leftPoints[i].x)
//		{
//			minPtIndex = i;
//		}
//	}
//
//	printf("minPtIndex = %d, %f, %f\n", minPtIndex, (leftPoints[minPtIndex].x + leftImg->width - leftCrop->width) / leftImg->width, leftPoints[minPtIndex].y / leftImg->height);

	minPtIndex = minGroupIndex = 0;
	for(i = 0; i < *numMapping; ++i)
	{
		for(j = 0; j < 3; ++j)
		{
			if(mappingPoints[i].pLeft[j].x < mappingPoints[minGroupIndex].pLeft[minPtIndex].x)
			{
				minGroupIndex = i;
				minPtIndex = j;
			}
		}
	}

	MappingPoint tempMap = mappingPoints[minGroupIndex];
	mappingPoints[minGroupIndex] = mappingPoints[0];
	mappingPoints[0] = tempMap;

	Point tempPt2  = mappingPoints[0].pLeft[minPtIndex];
	mappingPoints[0].pLeft[minPtIndex] = mappingPoints[0].pLeft[0];
	mappingPoints[0].pLeft[0] =  tempPt2;
	tempPt2  = mappingPoints[0].pRight[minPtIndex];
	mappingPoints[0].pRight[minPtIndex] = mappingPoints[0].pRight[0];
	mappingPoints[0].pRight[0] =  tempPt2;

	cvReleaseMemStorage(&storage);

	for(i = 0; i < *numMapping; ++i)
	{
//		qDebug() << mappingPoints[0][i].pLeft[0].x << "  " << mappingPoints[0][i].pLeft[0].y;
//		qDebug() << mappingPoints[0][i].pLeft[1].x << "  " << mappingPoints[0][i].pLeft[1].y;
//		qDebug() << mappingPoints[0][i].pLeft[2].x << "  " << mappingPoints[0][i].pLeft[0].y;
//		qDebug() << mappingPoints[0][i].pRight[0].x << "  " << mappingPoints[0][i].pRight[0].y;
//		qDebug() << mappingPoints[0][i].pRight[1].x << "  " << mappingPoints[0][i].pRight[1].y;
//		qDebug() << mappingPoints[0][i].pRight[2].x << "  " << mappingPoints[0][i].pRight[2].y;
//		printf("%f %f %f %f %f %f\n", mappingPoints[i].pLeft[0].x,mappingPoints[i].pLeft[0].y,mappingPoints[i].pLeft[1].x,mappingPoints[i].pLeft[1].y,mappingPoints[i].pLeft[2].x,mappingPoints[i].pLeft[2].y);
//		printf("%f %f %f %f %f %f\n", mappingPoints[i].pRight[0].x,mappingPoints[i].pRight[0].y,mappingPoints[i].pRight[1].x,mappingPoints[i].pRight[1].y,mappingPoints[i].pRight[2].x,mappingPoints[i].pRight[2].y);
	}
}

void getTrianglesAllPairs(IplImage **sortImg, IplImage **imgCrop,
		IplImage **imgEqualize, IplImage **eig, IplImage **temp,
		IplImage **pyr, char **status, Point **points, int numImg,
		MappingPoint **mappingPoints, int *numMapping)
{
	int i;
	for(i = 0; i < numImg; ++i)
	{
		getTrianglesOnePair(sortImg[i], sortImg[(i + 1) % numImg],
				imgCrop[i], imgCrop[(i + 1) % numImg],
				imgEqualize[i], imgEqualize[(i + 1) % numImg],
				eig[i], temp[i],
				pyr[i], pyr[(i + 1) % numImg], status[i],
				points[i], points[(i + 1) % numImg],
				mappingPoints[i], &numMapping[i]);
	}
}
