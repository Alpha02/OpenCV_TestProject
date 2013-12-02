#include <Windows.h>
#include <WinUser.h>
#include <math.h>
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include "includes.h"
using namespace std;
double fScreenWidth;
double fScreenHeight;
void MouseMove (int x, int y)
{
	double fx = x*(65535.0f/fScreenWidth);
	double fy = y*(65535.0f/fScreenHeight);
	INPUT Input={0};
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = fx;
	Input.mi.dy = fy;
	SendInput(1,&Input,sizeof(INPUT));
}
int main(){
	fScreenWidth =GetSystemMetrics( SM_CXSCREEN )-1;
	fScreenHeight =GetSystemMetrics( SM_CYSCREEN )-1;
	CvPoint old_point=cvPoint(0,0);
	float x,y,t=0;
	CvCapture * capture=cvSetCamera("avi",1);
	cvNamedWindow("找最亮点",CV_WINDOW_AUTOSIZE);
	while(1){
		//t+=0.02;
		IplImage * img=cvGetCamera(capture);
		CvPoint *point=Calculate_img(img);
		old_point=cvPoint((point->x+old_point.x*3)/4,(point->y+old_point.y*3)/4);
		cout<<"x="<<point->x<<endl<<"y="<<point->y<<endl;
		cvCircle(img,old_point,20,cvScalarAll(0),2);
		cvShowImage("找最亮点",img);
		double screen_x=fScreenWidth/img->width*old_point.x;
		double screen_y=fScreenHeight/img->height*old_point.y;
		MouseMove(screen_x,screen_y);
		cvWaitKey(1);
	}
	system("PAUSE");
}