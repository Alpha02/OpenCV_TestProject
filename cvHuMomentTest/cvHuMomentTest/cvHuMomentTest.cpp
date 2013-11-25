#include <cv.h>
#include <hehecv.h>
#include <highgui.h>
CvHuMoments * cvxGetHuMomentImage(IplImage * src){
	IplImage * src_gray;
	if(src->nChannels!=1){
		src_gray=cvxCreateImageSimilar(src,1);
		cvCvtColor(src,src_gray,CV_BGR2GRAY);
	}else{
		src_gray=src;
	}
	CvMoments moment;
	cvMoments(src_gray,&moment);
	CvHuMoments *Hu_moment=new CvHuMoments;
	cvGetHuMoments(&moment,Hu_moment);
	return Hu_moment;
}
int main(int argc, char * argv[]){
	//Load 2 Image contains some digit.
	IplImage * src=cvLoadImage("E://Linhehe//CVLab//img//matchs.jpg");
	IplImage * src2=cvLoadImage("E://Linhehe//CVLab//img//matchs2.jpg");
	
	cvNamedWindow("src_img",CV_WINDOW_NORMAL);
	cvNamedWindow("src_img2",CV_WINDOW_NORMAL);
	cvNamedWindow("src_subimg",CV_WINDOW_NORMAL);
	cvNamedWindow("src_subimg2",CV_WINDOW_NORMAL);
	char* winlist[]={"src_img","src_img2","src_subimg","src_subimg2"};
	cvxArrangeWindows(4,winlist,cvSize(1100,500));
	IplImage * src_gray=cvxCreateImageSimilar(src,1);
	cvCvtColor(src,src_gray,CV_BGR2GRAY);
	IplImage * src_gray2=cvxCreateImageSimilar(src2,1);
	cvCvtColor(src2,src_gray2,CV_BGR2GRAY);


	while(1){
		//Cut.Show,and Calculate the Hu_moment
		std::cout<<"Please cut the left image by mouse~\n";
		IplImage * src_subimg=cvxCutImageByMouse(src_gray,"src_img");
		cvShowImage("src_subimg",src_subimg);	
		CvHuMoments * Hu_Src=cvxGetHuMomentImage(src_subimg);
		std::cout<<"And then cut the right image by mouse~\n";
		IplImage * src_subimg2=cvxCutImageByMouse(src_gray2,"src_img2");
		cvShowImage("src_subimg2",src_subimg2);
		CvHuMoments * Hu_Src2=cvxGetHuMomentImage(src_subimg2);
		//Match(Simpler than imaged);
		double s=cvMatchShapes(src_subimg,src_subimg2,CV_CONTOURS_MATCH_I1);
		std::cout<<"Match_result:  "<<s<<"\n";
	}
	//It is strange that digit "6" can't be matched well.....Why???
	cvWaitKey(0);
}