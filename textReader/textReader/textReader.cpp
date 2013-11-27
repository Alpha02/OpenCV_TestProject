#include <cv.h>
#include  <highgui.h>
#include <hehecv.h>
using namespace std;
//method= CV_RETR_XX.
CvSeq * cvxFindContourFromImage(IplImage * src_img,CvMemStorage * storage,double threshold=127,int method=CV_RETR_TREE){
	IplImage * src_gray=cvxCreateImageSimilar(src_img,1);
	cvCvtColor(src_img,src_gray,CV_BGR2GRAY);
	cvThreshold(src_gray,src_gray,threshold,255,CV_THRESH_BINARY);
	if(storage==NULL)storage=cvCreateMemStorage();
	CvSeq *contours;
	cvFindContours(src_gray,storage,&(contours),88,CV_RETR_TREE);
	cvReleaseImage(&src_gray);
	return contours;
}
//This function cut the first Seq ,and keep its v_next pointer;
CvSeq * cvxGetSubSeq(CvSeq * src_seq)
{
	CvSlice new_slice=cvSlice(0,88+src_seq->total*src_seq->elem_size);
	CvSeq * newSeq=cvSeqSlice(src_seq,new_slice,src_seq->storage,1);
	
	if(src_seq->v_next!=NULL){
		newSeq->v_next=src_seq->v_next;
	}
	
	return newSeq;
}
int main(){
	IplImage * src_img=cvLoadImage("E://Linhehe//CVLab//img//text.png");
	IplImage * contour_draw=cvxCreateImageSimilar(src_img);
	CvMemStorage *storage=cvCreateMemStorage();
	CvSeq *contours=cvxFindContourFromImage(src_img,storage,240);

	int idx=0;	
	char *win_name[300];
	contours=contours->v_next;
	while(contours){
		CvRect rect=cvBoundingRect(contours);
		//cvSetImageROI(src_img,rect);
		cvRectangle(src_img,cvPoint(rect.x,rect.y),cvPoint(rect.x+rect.width,rect.y+rect.height),cvScalar(rand()%255,rand()%255,rand()%255),1);
/*
		IplImage * sub_img=cvCreateImage(cvSize(rect.width,rect.height),src_img->depth,src_img->nChannels);
		cvCopy(src_img,sub_img);
		win_name[idx]=new char[10];
		sprintf(win_name[idx],"win%d",idx);

		cvxShow(sub_img,CV_WINDOW_AUTOSIZE,win_name[idx]);
*/

		contours=contours->h_next;
		idx++;
	}
	cvxShow(src_img);
	cvWaitKey(0);
}