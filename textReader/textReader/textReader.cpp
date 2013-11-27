#include <cv.h>
#include  <highgui.h>
#include <hehecv.h>
using namespace std;
//method= CV_RETR_XX.
CvSeq * cvxFindContourFromImage(IplImage * src_img,CvMemStorage * storage,double threshold=127,int method=CV_RETR_TREE){
	IplImage * src_gray=cvxCreateImageSimilar(src_img,1);
	cvCvtColor(src_img,src_gray,CV_BGR2GRAY);
	//cvAdaptiveThreshold(src_gray,src_gray,255);
	cvErode(src_gray,src_gray,0,1);
	cvDilate(src_gray,src_gray,0,1);
	cvThreshold(src_gray,src_gray,threshold,255,CV_THRESH_BINARY);
	cvNamedWindow("img_temp");
	cvShowImage("img_temp",src_gray);
	cvWaitKey(0);

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
void cvxBoundingContours(IplImage * src_img,CvSeq * src_contours,CvScalar color=cvScalar(rand()%255,rand()%255,rand()%255)){
	if(src_contours->h_next)cvxBoundingContours(src_img,src_contours->h_next);
	if(src_contours->v_next)cvxBoundingContours(src_img,src_contours->v_next,color);
	CvRect rect=cvBoundingRect(src_contours);
	if((rect.height>15 || rect.width>15)){
		cvRectangle(src_img,cvPoint(rect.x,rect.y),cvPoint(rect.x+rect.width,rect.y+rect.height),color,1);
	}
}
int main(){
	IplImage * src_img=cvLoadImage("E://Linhehe//CVLab//img//text3.png");
	IplImage * erode_img=cvxCreateImageSimilar(src_img);
	IplImage * contour_draw=cvxCreateImageSimilar(src_img);
	CvMemStorage *storage=cvCreateMemStorage();
	CvSeq *contours=cvxFindContourFromImage(src_img,storage,230);
	cvxBoundingContours(src_img,contours);
	cvxShow(src_img);
	cvWaitKey(0);
}