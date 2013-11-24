// histogramHSV.cpp : 定义控制台应用程序的入口点。
//
#include <cv.h>
#include <highgui.h>
#include <hehecv.h>

int main(int argc, char * argv[])
{
	CvCapture * capture=cvxCreateCameraCaptureAuto();
	IplImage * img,*imgHSV,*imgH,*imgS,*imgV,*imgH_color,*img_mid,*img_white;
	int hist_size[]={20,20};
	IplImage * hist_img[2];
	CvHistogram * hist_HS=cvCreateHist(2,hist_size,0);
	char * windows_list[15]={"winH","winS","winV","winH_color","winHist","1","2","3","4","5","a","b","c","d","e"};
	cvxArrangeWindows(5,windows_list,cvSize(1366,768));
	int read_retry=0;
	do{
		img=cvQueryFrame(capture);
		read_retry++;
		if(read_retry>100){
			std::cout<<"Read Camera Fail.....";
			cvWaitKey(0);
		}
	}while(!img);
	imgHSV=cvxCreateImageSimilar(img);
	imgH_color=cvxCreateImageSimilar(img);
	imgH=cvxCreateImageSimilar(img,CVX_1_CHANNEL);
	imgS=cvxCreateImageSimilar(img,CVX_1_CHANNEL);
	imgV=cvxCreateImageSimilar(img,CVX_1_CHANNEL);
	img_mid=cvxCreateImageSimilar(img,CVX_1_CHANNEL);
	img_white=cvxCreateImageSimilar(img,CVX_1_CHANNEL);
	cvSet(img_mid,cvScalarAll(128));
	cvSet(img_white,cvScalarAll(255));
	while(1){
		img=cvQueryFrame(capture);
		cvCvtColor(img,imgHSV,CV_BGR2HSV);
		cvSplit(imgHSV,imgH,imgS,imgV,NULL);
		hist_img[0]=imgH;
		hist_img[1]=imgS;
		cvMerge(imgH,img_white,img_mid,NULL,imgH_color);
		cvCalcHist(hist_img,hist_HS);
		cvxShowHistogram("winHist",hist_HS);
		cvShowImage("winH",imgH);
		cvShowImage("winS",imgS);
		cvShowImage("winV",imgV);
		cvCvtColor(imgH_color,imgH_color,CV_HSV2BGR);
		cvShowImage("winH_color",imgH_color);
		cvWaitKey(5);
	}
	return 0;
}

