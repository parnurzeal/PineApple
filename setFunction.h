/*
 * setFunction.h
 *
 *  Created on: Jan 30, 2009
 *      Author: parnurzeal
 */

#ifndef SETFUNCTION_H_
#define SETFUNCTION_H_

#include <sys/ioctl.h>
#include "pwc-ioctl.h"
#include <linux/videodev.h>
#include <fcntl.h>
#include <unistd.h>

void set_compression_preference(int fd, int pref)
{
	if (ioctl(fd, VIDIOCPWCSCQUAL, &pref) == -1)
		printf("VIDIOCPWCSCQUAL");
}


void set_automatic_gain_control(int fd, int pref)
{
	if (ioctl(fd, VIDIOCPWCSAGC, &pref) == -1)
		printf("VIDIOCPWCSAGC");
}

void set_shutter_speed(int fd, int pref)
{
	if (ioctl(fd, VIDIOCPWCSSHUTTER, &pref) == -1)
		printf("VIDIOCPWCSSHUTTER");
}

void set_automatic_white_balance_mode(int fd, int mode, int red, int blue)
{
	struct pwc_whitebalance pwcwb;

	if (ioctl(fd, VIDIOCPWCGAWB, &pwcwb) == -1)
		printf("VIDIOCPWCGAWB");

	if (mode ==0)
		pwcwb.mode = PWC_WB_AUTO;
	else if (mode ==1)
		pwcwb.mode = PWC_WB_MANUAL;
	else if (mode ==2)
		pwcwb.mode = PWC_WB_INDOOR;
	else if (mode ==3)
		pwcwb.mode = PWC_WB_OUTDOOR;
	else if (mode ==4)
		pwcwb.mode = PWC_WB_FL;
	else
	{
		fprintf(stderr, "'%s' is not a known white balance mode.\n", mode);
		exit(1);
	}
	pwcwb.manual_red = red;
	pwcwb.manual_blue = blue;
	if (ioctl(fd, VIDIOCPWCSAWB, &pwcwb) == -1)
		printf("VIDIOCPWCSAWB");
}

void set_automatic_white_balance_mode_red(int fd, int val)
{
	struct pwc_whitebalance pwcwb;

	if (ioctl(fd, VIDIOCPWCGAWB, &pwcwb) == -1)
		printf("VIDIOCPWCGAWB");

	pwcwb.manual_red = val;

	if (ioctl(fd, VIDIOCPWCSAWB, &pwcwb) == -1)
		printf("VIDIOCPWCSAWB");
}

void set_automatic_white_balance_mode_blue(int fd, int val)
{
	struct pwc_whitebalance pwcwb;

	if (ioctl(fd, VIDIOCPWCGAWB, &pwcwb) == -1)
		printf("VIDIOCPWCGAWB");

	pwcwb.manual_blue = val;

	if (ioctl(fd, VIDIOCPWCSAWB, &pwcwb) == -1)
		printf("VIDIOCPWCSAWB");
}

void set_automatic_white_balance_speed(int fd, int val)
{
	struct pwc_wb_speed pwcwbs;

	if (ioctl(fd, VIDIOCPWCGAWBSPEED, &pwcwbs) == -1)
		printf("VIDIOCPWCGAWBSPEED");

	pwcwbs.control_speed = val;

	if (ioctl(fd, VIDIOCPWCSAWBSPEED, &pwcwbs) == -1)
		printf("VIDIOCPWCSAWBSPEED");
}

void set_automatic_white_balance_delay(int fd, int val)
{
	struct pwc_wb_speed pwcwbs;

	if (ioctl(fd, VIDIOCPWCGAWBSPEED, &pwcwbs) == -1)
		printf("VIDIOCPWCGAWBSPEED");

	pwcwbs.control_delay = val;

	if (ioctl(fd, VIDIOCPWCSAWBSPEED, &pwcwbs) == -1)
		printf("VIDIOCPWCSAWBSPEED");
}

void set_led_on_time(int fd, int val)
{
	struct pwc_leds pwcl;

	if (ioctl(fd, VIDIOCPWCGLED, &pwcl) == -1)
		printf("VIDIOCPWCGLED");

	pwcl.led_on = val;

	if (ioctl(fd, VIDIOCPWCSLED, &pwcl) == -1)
		printf("VIDIOCPWCSLED");
}

void set_led_off_time(int fd, int val)
{
	struct pwc_leds pwcl;

	if (ioctl(fd, VIDIOCPWCGLED, &pwcl) == -1)
		printf("VIDIOCPWCGLED");

	pwcl.led_off = val;

	if (ioctl(fd, VIDIOCPWCSLED, &pwcl) == -1)
		printf("VIDIOCPWCSLED");
}

void set_sharpness(int fd, int val)
{
	if (ioctl(fd, VIDIOCPWCSCONTOUR, &val) == -1)
		printf("VIDIOCPWCSCONTOUR");
}

void set_backlight_compensation(int fd, int val)
{
	if (ioctl(fd, VIDIOCPWCSBACKLIGHT, &val) == -1)
		printf("VIDIOCPWCSBACKLIGHT");
}

void set_antiflicker_mode(int fd, int val)
{
	if (ioctl(fd, VIDIOCPWCSFLICKER, &val) == -1)
		printf("VIDIOCPWCSFLICKER");
}

void set_noise_reduction(int fd, int val)
{
	if (ioctl(fd, VIDIOCPWCSDYNNOISE, &val) == -1)
		printf("VIDIOCPWCSDYNNOISE");
}
void set_brightness(int fd, long newBrightness){
	struct video_picture vid_pic;
	// retrieve the camera settings
	if (ioctl(fd, VIDIOCGPICT, &vid_pic)==-1) {perror("ioctl VIDIOCSPICT");}
	// change the brightness option
	vid_pic.brightness = newBrightness;
	// set the settings back
	if (ioctl(fd, VIDIOCSPICT, &vid_pic)==-1) {perror("ioctl VIDIOCSPICT");}
}

void set_saturation(int fd, long newSaturation){
	struct video_picture vid_pic;
	// retrieve the camera settings
	if (ioctl(fd, VIDIOCGPICT, &vid_pic)==-1) {perror("ioctl VIDIOCSPICT");}
	// change the colour option
	vid_pic.colour = newSaturation;
	// set the settings back
	if (ioctl(fd, VIDIOCSPICT, &vid_pic)==-1) {perror("ioctl VIDIOCSPICT");}
}

void set_contrast(int fd,long newContrast){
	struct video_picture vid_pic;
	if(ioctl(fd,VIDIOCGPICT,&vid_pic)==-1) { perror("ioctl VIDIOCSPICT");}
	vid_pic.contrast=newContrast;
	if(ioctl(fd,VIDIOCSPICT,&vid_pic)==-1){perror("ioctl VIDIOCSPICT");}
}
void restore_camera_setting(int fd){
	if(ioctl(fd,VIDIOCPWCRUSER)==-1)
		printf("VIDIOCPWCRUSER");
}
void save_camera_setting(int fd){
	if(ioctl(fd,VIDIOCPWCSUSER)==-1)
		printf("VIDIOCPWCSUSER");
}
void restore_factory_setting(int fd){
	if(ioctl(fd,VIDIOCPWCFACTORY)==-1)
		printf("VIDIOCPWCFACTORY");
}
void set_dimensions_and_framerate(int fd, int w, int h, int framerate)
{
	struct video_window vwin;

	/* get resolution/framerate */
	if (ioctl(fd, VIDIOCGWIN, &vwin) == -1)
		printf("VIDIOCGWIN");

	if (w > 0 && h > 0)
	{
		vwin.width = w;
		vwin.height = h;
	}

	if (vwin.flags & PWC_FPS_FRMASK)
	{
		/* set new framerate */
		vwin.flags &= ~PWC_FPS_FRMASK;
		vwin.flags |= (framerate << PWC_FPS_SHIFT);

		if (ioctl(fd, VIDIOCSWIN, &vwin) == -1)
			printf("VIDIOCSWIN");
	}
	else
	{

		exit(1);
	}
}
void dump_current_settings(int fd,int* gain,int *pWinW,int* pWinH,int* framerate,int* white_balance_mode,int* red,int* blue,int *brightness,int *saturation,int* contrast, int *noise_reduction)
{
	struct video_window vwin;
	struct video_picture vpic;
	struct pwc_whitebalance pwcwb;

	/* get resolution/framerate */
	if (ioctl(fd, VIDIOCGWIN, &vwin) == -1)
		printf("VIDIOCGWIN");

	if (vwin.flags & PWC_FPS_FRMASK)
		*framerate  = (int)((vwin.flags & PWC_FPS_FRMASK) >> PWC_FPS_SHIFT);
	*pWinW=vwin.width;
	*pWinH=vwin.height;
	/* color (etc.) settings */
	if (ioctl(fd, VIDIOCGPICT, &vpic) == -1)
		printf("VIDIOCGPICT");
	*brightness=vpic.brightness;
	*contrast=vpic.contrast;
	*saturation = vpic.colour;
	//printf("Brightness: %d\n", vpic.brightness);
	//printf("Hue: %d\n", vpic.hue);
	//printf("Colour: %d\n", vpic.colour);
	//printf("Contrast: %d\n", vpic.contrast);
	//printf("Whiteness: %d\n", vpic.whiteness);

	/* noise reduction */
	if(ioctl(fd,VIDIOCPWCGDYNNOISE,&noise_reduction)==-1)
		printf("VIDIOCPWCGDYNNOISE");

	if (ioctl(fd, VIDIOCPWCGAGC, &gain) == -1)
		printf("VIDIOCPWCGAGC");

	if (ioctl(fd, VIDIOCPWCGAWB, &pwcwb) == -1)
		printf("VIDIOCPWCGAWB");

	if (pwcwb.mode == PWC_WB_AUTO)
		*white_balance_mode = 0;
	else if (pwcwb.mode == PWC_WB_MANUAL)
		*white_balance_mode = 1;
	else if (pwcwb.mode == PWC_WB_INDOOR)
		*white_balance_mode = 2;
	else if (pwcwb.mode == PWC_WB_OUTDOOR)
		*white_balance_mode = 3;
	else if (pwcwb.mode == PWC_WB_FL)
		*white_balance_mode = 4;
	else
		printf("unknown!\n");

	*red = pwcwb.manual_red;
	*blue = pwcwb.manual_blue;

}

void manuel_camera_setting(int fd,int num){
	int pWinW=160,pWinH=120;
	int pFramerate=30;
	int pGain=31910;
	int pShutter_Speed=65535;
	int pWhite_Balance_Mode=1;
	int pRed=25555;
	int pBlue=1649;
	int pBrightness=33798;
	int pSaturation=32974;
	int pContrast=33282;
	int pSharpness=39568;
	int pNoise_Reduction=3;

	switch(num){
		case 0:{
			pFramerate=30;
			pGain=30000;
			pShutter_Speed=59000;
			pWhite_Balance_Mode=1;
			pRed=22850;
			pBlue=5400;
			pBrightness=32000;
			pSaturation=32974;
			pContrast=33282;
			pSharpness=39568;
			pNoise_Reduction=3;

		}break;
		case 1:{

//			camera 1
			pFramerate=30;
			pGain=28500;
			pShutter_Speed=60035;
			pWhite_Balance_Mode=1;
			pRed=21550;
			pBlue=5250;
			pBrightness=32100;
			pSaturation=32974;
			pContrast=33282;
			pSharpness=39568;
			pNoise_Reduction=3;

		}break;
		case 2:{

//			camera2
			pFramerate=30;
			pGain=28500;
			pShutter_Speed=60800;
			pWhite_Balance_Mode=1;
			pRed=22500;
			pBlue=5000;
			pBrightness=31650;
			pSaturation=32974;
			pContrast=33282;
			pSharpness=39568;
			pNoise_Reduction=3;

		}break;
		case 3:{

//			camera 3
			pFramerate=30;
			pGain=28510;
			pShutter_Speed=60800;
			pWhite_Balance_Mode=1;
			pRed=22000;
			pBlue=5200;
			pBrightness=33120;
			pSaturation=32974;
			pContrast=33282;
			pSharpness=39568;
			pNoise_Reduction=3;

		}break;
		case 4:{
			pFramerate=30;
			pGain=30000;
			pShutter_Speed=60800;
			pWhite_Balance_Mode=1;
			pRed=23600;
			pBlue=5400;
			pBrightness=33798;
			pSaturation=32974;
			pContrast=33282;
			pSharpness=39568;
			pNoise_Reduction=3;
		}break;
		case 5:{
			pFramerate=30;
			pGain=31900;
			pShutter_Speed=60800;
			pWhite_Balance_Mode=1;
			pRed=22500;
			pBlue=5680;
			pBrightness=33120;
			pSaturation=32974;
			pContrast=33282;
			pSharpness=39568;
			pNoise_Reduction=3;
		}break;
		case 6:{

			pFramerate=30;
			pGain=31110;
			pShutter_Speed=60800;
			pWhite_Balance_Mode=1;
			pRed=20900;
			pBlue=5400;
			pBrightness=33798;
			pSaturation=32974;
			pContrast=33282;
			pSharpness=39568;
			pNoise_Reduction=3;
		}break;
		case 7:{
			pFramerate=30;
			pGain=31100;
			pShutter_Speed=60800;
			pWhite_Balance_Mode=1;
			pRed=22260;
			pBlue=5550;
			pBrightness=33050;
			pSaturation=32974;
			pContrast=33282;
			pSharpness=39568;
			pNoise_Reduction=3;
		}break;
		case 8:{
			pFramerate=30;
			pGain=34300;
			pShutter_Speed=60800;
			pWhite_Balance_Mode=1;
			pRed=21000;
			pBlue=5800;
			pBrightness=32000;
			pSaturation=32974;
			pContrast=33282;
			pSharpness=39568;
			pNoise_Reduction=3;
		}break;
		default:{

		}
	}
//	printf("num=%d %d %d\n", num, pBlue, pWhite_Balance_Mode);
	//set_dimensions_and_framerate(fd,160,120,pFramerate);
	if(num==0||num==1||num==2||num==3)
		set_automatic_gain_control(fd,pGain);
//	if(num==0||num==2||num==3)
//		set_shutter_speed(fd,pShutter_Speed);
	set_automatic_gain_control(fd,pGain);
	set_shutter_speed(fd,pShutter_Speed);
	set_automatic_white_balance_mode(fd,pWhite_Balance_Mode,pRed,pBlue);
	set_brightness(fd,pBrightness);
//	set_contrast(fd,pContrast);
//	set_saturation(fd,pSaturation);
	if(num==2)
		set_contrast(fd,pContrast);
//	set_sharpness(fd,pSharpness);
	//set_noise_reduction(fd,pNoise_Reduction);
}
#endif /* SETFUNCTION_H_ */
