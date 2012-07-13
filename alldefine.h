#ifndef ALLDEFINE_H
#define ALLDEFINE_H

//Open Debug Windows
//#define DEBUG
//Delaunay USE?
//#define DELAUNAY

//Type of Texture Mapping
//1 using Delaunay
//2 just fix following to image scale
//3 use hand fix.. T.T
#define TYPE_TEXTURE_MAPPING 3

// Test for Dragging if finish please remove
#define Drag_Test
#define GL_WINDOWS_WIDTH 4.0

// MANUEL OR AUTOMATIC CAMERA SETTING
#define MANUEL_CAMERA_SETTING

//Define for MainWindow.
#define DEFAULT_MAINWINDOW_WIDTH 1000
#define DEFAULT_MAINWINDOW_HEIGHT 410

//Define for NewPanoWizard.
#define DISPLAY_PICTURE_WIDTH 200
#define DISPLAY_PICTURE_HEIGHT 200
#define PICTURE_FILE_FORMAT "All Image Files (*.bmp *.jpg *.jpeg *.png *.gif)"

#define CROP_WIDTH 40
#define MAX_POINTS 300
#define MAX_TRIANGLE_GROUP 300
#define QUALITY_LEVEL 0.005
#define MIN_DISTANCE 5.0
#define WIN_SIZE 10
#define MIN_TRIANGLE_AREA 0

#define MAX_ITEM 50

#include <cxcore.h>

enum { File, Cam, Video };

typedef CvPoint2D32f Point;

typedef struct MappingPoint{
	Point pLeft[3];
	Point pRight[3];
}MappingPoint;

#endif
