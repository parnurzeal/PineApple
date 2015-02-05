#ifdef _CH_
#pragma package <opencv>
#endif

#include "Resource.h"
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <ctype.h>
IplImage **picture;
CvCapture ** capture;

bool paInitAll(void);
void paDestroyAll(void);

int main( int argc, char** argv ) {

	if(!paInitAll()) // if All inits work fine return true, if not return false;
		return -1;
	//cvNamedWindow("TorPictureLaew",CV_WINDOW_AUTOSIZE);
	IplImage** cpyFrame = new IplImage*[NUM_CAMERA];
    for(;;){
    	IplImage** frame = new IplImage*[NUM_CAMERA];
    	for(int i = 0;i<NUM_CAMERA;i++){
    		frame[i] = cvQueryFrame(capture[i]);
    		if(!frame[i])
    			break;
    	}
    	for(int i = 0;i<NUM_CAMERA;i++){
    		if(!picture[i]){
    			picture[i] = cvCreateImage(cvGetSize(frame[i]),8,3);
    		}
    	}
    	for(int i = 0;i<NUM_CAMERA;i++){
    		cvCopy(frame[i],picture[i],0);
    		char *tmp = new char[20];
    		sprintf(tmp,"Camera%d",i);
    		cvShowImage(tmp,picture[i]);
    	}
    	char c = cvWaitKey(10);
    	if(c==27){
    		for(int i = 0;i<NUM_CAMERA;i++){
    			char *tmp=new char[20];
    			sprintf(tmp,"Image1_%d.jpg",i);
    			cvSaveImage(tmp,picture[i]);
    		}

    		break;
    	}
    }
    paDestroyAll();
    cvDestroyWindow("TorPictureLaew");

}
bool paInitAll(){
	printf("a");
	picture= new IplImage*[NUM_CAMERA];
	capture= new CvCapture*[NUM_CAMERA];
	for(int i =0;i<NUM_CAMERA;i++){
		capture[i] = cvCaptureFromCAM(i);

		//cvSetCaptureProperty(capture[i], CV_CAP_PROP_FRAME_WIDTH, 320); //640
		//cvSetCaptureProperty(capture[i], CV_CAP_PROP_FRAME_HEIGHT, 240); //480

		if(!capture[i]){
			fprintf(stderr,"Camera %d could not initialize capturing...\n",i);
			return false;
		}
	}
	for(int i=0;i<NUM_CAMERA;i++){
		char *tmp = new char[20];
		sprintf(tmp,"Camera%d",i);
		cvNamedWindow(tmp,0);
	}
	return true;
}
void paDestroyAll(){
	for(int i = 0;i<NUM_CAMERA;i++)
	    	cvReleaseImage(&picture[i]);
	    for(int i = 0;i<NUM_CAMERA;i++){
	    	char *tmp = new char[20];
	    	sprintf(tmp,"Camera%d",i);
	    	cvDestroyWindow(tmp);
	    }
	    for(int i = 0;i<NUM_CAMERA;i++)
			cvReleaseCapture(&capture[i]);
}

