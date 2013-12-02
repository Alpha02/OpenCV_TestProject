// MostBrightestPoint.cpp : 定义控制台应用程序的入口点。
//
#include<cv.h>
#include<highgui.h>
using namespace std;
double Max_Val,Min_Val;
CvPoint B_Max_Point,B_Min_Point,G_Max_Point,G_Min_Point,R_Max_Point,R_Min_Point;
CvPoint* Calculate_img(IplImage * src_img)
{   IplImage* B_Channel=cvCreateImage(cvSize(src_img->width,src_img->height),src_img->depth,1);
    IplImage* G_Channel=cvCreateImage(cvSize(src_img->width,src_img->height),src_img->depth,1);
	IplImage* R_Channel=cvCreateImage(cvSize(src_img->width,src_img->height),src_img->depth,1);
	cvSplit(src_img,B_Channel,G_Channel,R_Channel,NULL);


    cvMinMaxLoc(G_Channel,&Min_Val,&Max_Val,&G_Min_Point,&G_Max_Point);

	 return &G_Max_Point;
}

int BrightestPoint(IplImage * img){
	cvNamedWindow("找最亮点",CV_WINDOW_AUTOSIZE);
	CvPoint*point=Calculate_img(img);
	cout<<"x="<<point->x<<endl<<"y="<<point->y<<endl;
	cvCircle(img,*point,20,cvScalarAll(0),2);
	cvShowImage("找最亮点",img);
	cvWaitKey(0);
	return 0;
}