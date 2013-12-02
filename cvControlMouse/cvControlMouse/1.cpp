#include<highgui.h>
#include<iostream>
using namespace std;
CvCapture* cvSetCamera(char* Window_name,int index){
	cvNamedWindow("Window_name");
	CvCapture* capture=cvCreateCameraCapture(index);
	IplImage * frame;
	int t;
	for(int i=0;i<10;i++){
		frame=cvQueryFrame(capture);
		if(!frame)
			t=0;
		t=1;
	}
	if(t==1)
		return capture;
	else{
		cout<<"fail!!!"<<endl;
		return NULL;
	}
}

IplImage *cvGetCamera(CvCapture* capture){
	IplImage *frame;
	frame=cvQueryFrame(capture);
	return frame;
}
