// FloodFill.cpp : 定义控制台应用程序的入口点。
//
#include "cv.h"
#include "highgui.h"

IplImage * img=cvLoadImage("E://Linhehe//CVLab//img//1.jpg");
IplImage * img2=cvCreateImage(cvSize(img->width,img->height),img->depth,img->nChannels);
void my_mouse(int event,int x,int y,int flags,void * param){
	if(flags == CV_EVENT_FLAG_LBUTTON)
	{
		cvFloodFill(img,cvPoint(x,y),cvScalarAll(0),cvScalarAll(4),cvScalarAll(4));
		cvShowImage("win1",img);
		

	}

}
int main(int argc, char * argv[])
{

	cvNamedWindow("win1",CV_WINDOW_NORMAL);
	cvShowImage("win1",img);
	cvCopy(img,img2);

	cvNamedWindow("win2",CV_WINDOW_NORMAL);

	cvSetMouseCallback("win1",my_mouse,(void*)img);
	while(1){
		cvSmooth(img2,img2,CV_GAUSSIAN,7,1);
		cvShowImage("win2",img2);
		cvWaitKey(10);
	}
	return 0;
}

