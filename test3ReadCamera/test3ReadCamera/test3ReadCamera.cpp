// test3ReadCamera.cpp : 定义控制台应用程序的入口点。
//
#include "cv.h"
#include "highgui.h"
 
int main(int argc, char* argv[])
{
	CvCapture * capture;
	capture=cvCreateCameraCapture(0);
	IplImage *srcframe,*frame,*oldframe,*diffframe,*backframe,*foreframe,*greyframe,*intframe;
	double fps=cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
	CvSize size=cvSize(
		(int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH),
		(int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT)
		);
	CvVideoWriter * writer=cvCreateVideoWriter(
		"hehe.avi",
		CV_FOURCC('M','J','P','G'),
		fps,
		size
		);
	CvScalar sc;
	double allsc;
	double rate=0.1;

	srcframe=cvQueryFrame(capture);
	oldframe=cvCreateImage(cvSize(srcframe->width,srcframe->height),srcframe->depth,srcframe->nChannels);
diffframe=cvCreateImage(cvSize(srcframe->width,srcframe->height),srcframe->depth,srcframe->nChannels);
backframe=cvCreateImage(cvSize(srcframe->width,srcframe->height),srcframe->depth,srcframe->nChannels);

/*
	frame=cvCreateImage(cvSize(srcframe->width,srcframe->height),srcframe->depth,srcframe->nChannels);
	greyframe=cvCreateImage(cvSize(frame->width,frame->height),frame->depth,frame->nChannels);
	foreframe=cvCreateImage(cvSize(frame->width,frame->height),frame->depth,frame->nChannels);
	backframe=cvCreateImage(cvSize(frame->width,frame->height),frame->depth,frame->nChannels);
	diffframe=cvCreateImage(cvSize(frame->width,frame->height),frame->depth,frame->nChannels);
	intframe=cvCreateImage(cvSize(frame->width,frame->height),frame->depth,frame->nChannels);
	cvCopy(frame,backframe);
	*/
	int key_current=0;
	while(key_current!=27){
		
		srcframe=cvQueryFrame(capture);
		
		//cvConvertScale(srcframe,frame,1.0/256);
		cvAbsDiff(srcframe,oldframe,diffframe);
		cvCopy(srcframe,oldframe);
		/*
		cvAbsDiff(frame,backframe,foreframe);
		
		sc=cvSum(foreframe);
		cvSmooth(foreframe,foreframe,2,5);
		*/
		//cvMul(foreframe,foreframe,foreframe);

		//cvMul(frame,foreframe,greyframe);

/*
		allsc=sc.val[0]+sc.val[1]+sc.val[2];
		if(allsc<100000){
			if(rate>0.01)rate/=1.1;
			


		}else{
			if(rate*1.5<1){rate*=1.5;}
		}
		*/
		
		cvAddWeighted(srcframe,0.1,backframe,0.9,0,backframe);
		//back=back*0.9+src*0.1;
		cvNamedWindow("win1",CV_WINDOW_NORMAL);
		cvShowImage("win1",backframe);
		cvNamedWindow("win2",CV_WINDOW_NORMAL);
		cvShowImage("win2",srcframe);
		//cvWriteFrame(writer,backframe);
		key_current=cvWaitKey(5);
	}
	return 0;
}

