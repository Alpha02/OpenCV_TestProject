#include <cv.h>
#include <highgui.h>
#include <hehecv.h>
int g_thresh=100;
IplImage * img_old=NULL;
IplImage * img_gray=NULL;
CvMemStorage * g_storage=NULL;
void on_trackbar(int){
	if(g_storage==NULL){
		img_gray=cvxCreateImageSimilar(img_old,1,8);
		g_storage=cvCreateMemStorage();
	}else{
		cvClearMemStorage(g_storage);
	}
	CvSeq * contours=0;
	cvCvtColor(img_old,img_gray,CV_BGR2GRAY);
	//可调节的阈值法
	//cvThreshold(img_gray,img_gray,g_thresh,255,CV_THRESH_BINARY);
	//自适应阈值法
	//AdaptiveThreshold(img_gray,img_gray,255);
	//Canny边缘检测
	cvCanny(img_gray,img_gray,50,g_thresh);

	cvFindContours(img_gray,g_storage,&contours);

	cvZero(img_gray);
	if(contours){
		cvDrawContours(img_gray,contours,cvScalarAll(255),cvScalarAll(255),100);
		cvShowImage("Contours",img_gray);
	}
}
int main(int argc, char * argv[]){
	CvCapture * capture=cvxCreateCameraCaptureAuto();

	//img=cvLoadImage("E://Linhehe//CVLab//img//6.jpg");
	IplImage * img=cvQueryFrame(capture);
	img_old=cvxCreateImageSimilar(img);
	img_gray=cvxCreateImageSimilar(img,1);
	cvNamedWindow("Contours",CV_WINDOW_NORMAL);
	cvCreateTrackbar("Threshold","Contours",&g_thresh,255,on_trackbar);
	on_trackbar(0);
	while(1){
		img=cvQueryFrame(capture);
		//一阶滞后滤波
		cvAddWeighted(img_old,0.4,img,0.6,0,img_old);

		on_trackbar(0);
		cvWaitKey(2);
	}
	return 0;

}