#include <cv.h>
#include <highgui.h>
#include <hehecv.h>
int g_thresh=100;
IplImage * img=NULL;
IplImage * img_gray=NULL;
CvMemStorage * g_storage=NULL;
void on_trackbar(int){
	if(g_storage==NULL){
		img_gray=cvxCreateImageSimilar(img,1,8);
		g_storage=cvCreateMemStorage();


	}else{
		cvClearMemStorage(g_storage);
	}
	CvSeq * contours=0;
	cvCvtColor(img,img_gray,CV_BGR2GRAY);
	cvThreshold(img_gray,img_gray,g_thresh,255,CV_THRESH_BINARY);
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
	img=cvQueryFrame(capture);
	img_gray=cvxCreateImageSimilar(img,1);
	cvNamedWindow("Contours",CV_WINDOW_NORMAL);
	cvCreateTrackbar("Threshold","Contours",&g_thresh,255,on_trackbar);
	on_trackbar(0);
	while(1){
		img=cvQueryFrame(capture);
		on_trackbar(0);
		cvWaitKey(2);
	}
	return 0;

}