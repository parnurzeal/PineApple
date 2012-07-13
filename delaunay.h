#ifndef DELAUNAY_H_
#define DELAUNAY_H_

#include <cv.h>
#include "alldefine.h"

//#define CROP_WIDTH 30
#define MAX_POINTS 300
#define MAX_TRIANGLE_GROUP 300
#define QUALITY_LEVEL 0.005
#define MIN_DISTANCE 5.0
#define WIN_SIZE 10
//#define MIN_TRIANGLE_AREA 0

bool isSamePoint(CvPoint2D32f pt1, CvPoint2D32f pt2);

void copyCropImage(IplImage *src, IplImage *crop);

CvSubdiv2D* initDelaunay(CvMemStorage *storage, CvRect rect);

void getTrianglesOnePair(IplImage *leftImg, IplImage *rightImg,
		IplImage *leftCrop, IplImage *rightCrop,
		IplImage *leftEqualize, IplImage *rightEqualize,
		IplImage *eig, IplImage *temp,
		IplImage *leftPyr, IplImage *rightPyr, char *status,
		Point *leftPoints, Point *rightPoints,
		MappingPoint mappingPoints[], int *numMapping);

void getTrianglesAllPairs(IplImage **sortImg, IplImage **imgCrop,
		IplImage **imgEqualize, IplImage **eig, IplImage **temp,
		IplImage **pyr, char **status, Point **points, int numImg,
		MappingPoint **mappingPoints, int *numMapping);

#endif /* DELAUNAY_H_ */
