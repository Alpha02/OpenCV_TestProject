// histogramTest.cpp : 定义控制台应用程序的入口点。
//这个程序读取摄像头，将所得图像拆分成RGB三个通道，实时做出三个通道的一维直方图，然后做出GB通道的二维直方图。
#include <cv.h>
#include<highgui.h>
#include<hehecv.h>
int mysize[2];

int main(int argc, char * argv[])
{
	mysize[0]=50;
	mysize[1]=50;
	CvCapture * capture=cvCreateCameraCapture(1);
	IplImage * img;
	do{
		img=cvQueryFrame(capture);
	}while(!img);
	IplImage * img_sp0=cvCreateImage(cvSize(img->width,img->height),img->depth,1);
	IplImage * img_sp1=cvCreateImage(cvSize(img->width,img->height),img->depth,1);
	IplImage * img_sp2=cvCreateImage(cvSize(img->width,img->height),img->depth,1);
	IplImage * img_sp3=cvCreateImage(cvSize(img->width,img->height),img->depth,1);
	IplImage * img_null=cvCreateImage(cvSize(img->width,img->height),img->depth,1);
	IplImage * imgR=cvCreateImage(cvSize(img->width,img->height),img->depth,3);
	IplImage * imgG=cvCreateImage(cvSize(img->width,img->height),img->depth,3);
	IplImage * imgB=cvCreateImage(cvSize(img->width,img->height),img->depth,3);
	cvSetZero(img_null);
	CvHistogram * myHist=cvCreateHist(1,mysize,0);
	CvHistogram * myHist2=cvCreateHist(2,mysize,0);
	IplImage *imgs[1];
	cvNamedWindow("win1",CV_WINDOW_NORMAL);
	cvNamedWindow("win2",CV_WINDOW_NORMAL);
	cvNamedWindow("win3",CV_WINDOW_NORMAL);
	cvNamedWindow("hsR",CV_WINDOW_NORMAL);
	cvNamedWindow("hsG",CV_WINDOW_NORMAL);
	cvNamedWindow("hsB",CV_WINDOW_NORMAL);
	cvNamedWindow("hsGB",CV_WINDOW_NORMAL);
	while(1){
	//IplImage * img=cvLoadImage("E://Linhehe//CVLab//img//2.jpg");
	img=cvQueryFrame(capture);
	
	cvSplit(img,img_sp0,img_sp1,img_sp2,NULL);
	cvMerge(img_sp0,img_null,img_null,NULL,imgB);
	cvMerge(img_null,img_sp1,img_null,NULL,imgG);
	cvMerge(img_null,img_null,img_sp2,NULL,imgR);
	imgs[0]=img_sp0;
	cvCalcHist(imgs,myHist);
	cvxShowHistogram("hsG",myHist);
	imgs[0]=img_sp1;
	cvCalcHist(imgs,myHist);
	cvxShowHistogram("hsB",myHist);
	imgs[0]=img_sp2;
	cvCalcHist(imgs,myHist);
	cvxShowHistogram("hsR",myHist);
	imgs[0]=img_sp0;
	imgs[1]=img_sp1;
	cvCalcHist(imgs,myHist2);
	cvxShowHistogram("hsGB",myHist2);
	//cvNamedWindow("win4",CV_WINDOW_NORMAL);
	//cvShowImage("win1",img);
	cvShowImage("win1",imgR);
	cvShowImage("win2",imgG);
	cvShowImage("win3",imgB);
	
	cvWaitKey(5);
	}
	return 0;
}

