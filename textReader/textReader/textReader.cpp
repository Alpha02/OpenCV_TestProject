#include <cv.h>
#include  <highgui.h>
#include <hehecv.h>
#define STORAGE_FILE 1
#define STORAGE_SEQ 0
using namespace std;
//method= CV_RETR_XX.
CvMemStorage * Mem_file=cvCreateMemStorage();
CvMemStorage * Mem_seq=cvCreateMemStorage();
	CvSeq * cvxFindContourFromImage(IplImage * src_img,CvMemStorage * storage,double threshold=127,int method=CV_RETR_TREE){
	IplImage * src_gray=cvxCreateImageSimilar(src_img,1);
	cvCvtColor(src_img,src_gray,CV_BGR2GRAY);
	//cvAdaptiveThreshold(src_gray,src_gray,255);
	//cvDilate(src_gray,src_gray,0,1);
	//cvErode(src_gray,src_gray,0,1);

	cvThreshold(src_gray,src_gray,threshold,255,CV_THRESH_BINARY);
	CvSeq *contours;
	cvFindContours(src_gray,storage,&(contours),88,CV_RETR_TREE);
	cvReleaseImage(&src_gray);
	return contours;
}
struct CvxCharacter{
	CvSeq img_contour;
	char character_name[3];
};
CvxCharacter cvxCharacter(CvSeq &img_contour,char *character_name){
	CvxCharacter character;
	character.img_contour=img_contour;
	character.character_name[0]=character_name[0];
	character.character_name[1]=character_name[1];
	character.character_name[2]=character_name[2];
	return character;
}
void matchCharacter(IplImage * src_img,CvSeq * contours){

}
int getFileStorageIdx(){
	CvFileStorage * file=cvOpenFileStorage("./ch_data/rec_manager.xml",Mem_file,CV_STORAGE_READ);
	int idx=cvReadIntByName(file,0,"n");
	cvReleaseFileStorage(&file);
	return idx;
}
void setFileStorageIdx(int idx){
	CvFileStorage * file=cvOpenFileStorage("./ch_data/rec_manager.xml",Mem_file,CV_STORAGE_WRITE);
	cvWriteInt(file,"n",idx);
	cvReleaseFileStorage(&file);
}
CvxCharacter getCharacterFromFile(int idx){
	char node_name[40];
	sprintf(node_name,"./ch_data/ch%d.xml",idx);
	CvFileStorage * file=cvOpenFileStorage(node_name,Mem_file,CV_STORAGE_READ);
	CvxCharacter ch;
	CvSeq *temp_seq=(CvSeq*)cvReadByName(file,0,"img");
	CvSeq *result_seq=cvCloneSeq(temp_seq,Mem_seq);
	char *ch_name=(char*)cvReadStringByName(file,0,"name");
	ch=cvxCharacter(*result_seq,ch_name);
	cvReleaseFileStorage(&file);
	return ch;
}
double cvxMatchShapesNotRotate(CvSeq * seq1,CvSeq * seq2){
	CvMoments m1,m2;
	cvMoments(seq1,&m1);
	cvMoments(seq2,&m2);
	double mu1[7],mu2[7];
	
	mu1[0]=cvGetNormalizedCentralMoment(&m1,2,0);
	mu1[1]=cvGetNormalizedCentralMoment(&m1,1,1);
	mu1[2]=cvGetNormalizedCentralMoment(&m1,0,2);
	mu1[3]=cvGetNormalizedCentralMoment(&m1,3,0);
	mu1[4]=cvGetNormalizedCentralMoment(&m1,2,1);
	mu1[5]=cvGetNormalizedCentralMoment(&m1,1,2);
	mu1[6]=cvGetNormalizedCentralMoment(&m1,0,3);

	mu2[0]=cvGetNormalizedCentralMoment(&m2,2,0);
	mu2[1]=cvGetNormalizedCentralMoment(&m2,1,1);
	mu2[2]=cvGetNormalizedCentralMoment(&m2,0,2);
	mu2[3]=cvGetNormalizedCentralMoment(&m2,3,0);
	mu2[4]=cvGetNormalizedCentralMoment(&m2,2,1);
	mu2[5]=cvGetNormalizedCentralMoment(&m2,1,2);
	mu2[6]=cvGetNormalizedCentralMoment(&m2,0,3);
	
	int i;
	double res=0;
	for(i=0;i<7;i++){
		res+=pow(mu1[i]-mu2[i],2);
	}
	/*
	mu1[0]=cvGetNormalizedCentralMoment(&m1,1,1);
	mu1[1]=cvGetNormalizedCentralMoment(&m1,2,1);
	mu1[2]=cvGetNormalizedCentralMoment(&m1,1,2);

	mu2[0]=cvGetNormalizedCentralMoment(&m2,1,1);
	mu2[1]=cvGetNormalizedCentralMoment(&m2,2,1);
	mu2[2]=cvGetNormalizedCentralMoment(&m2,1,2);
	int i;
	double res=0;
	for(i=0;i<3;i++){
		res+=pow(mu1[i]-mu2[i],2);
	}
	*/
	return res;

}
void WriteCharacterToFile(CvxCharacter & ch,int idx){
	char node_name[40];
	sprintf(node_name,"./ch_data/ch%d.xml",idx);
	CvFileStorage * file=cvOpenFileStorage(node_name,Mem_file,CV_STORAGE_WRITE);
	cvWriteString(file,"name",ch.character_name);
	cvWrite(file,"img",&(ch.img_contour));
	cvReleaseFileStorage(&file);
}
double SearchCharacter(CvxCharacter & ch){
	int idx=getFileStorageIdx();
	int idx_best=0;
	double m_best=1;
	char name_best[3];
	while(idx--){
		CvxCharacter ch_temp=getCharacterFromFile(idx);
		double m=cvxMatchShapesNotRotate(&(ch_temp.img_contour),&(ch.img_contour));
		if(m<m_best){
			m_best=m;
			strcpy(name_best,ch_temp.character_name);
			idx_best=idx;
		}

	}

	cout<<name_best;
	return m_best;

}

void cvxAskQuestion(IplImage * src_img,CvSeq * contours){
	CvRect rect=cvBoundingRect(contours);
	IplImage * text_img=cvCreateImage(cvSize(rect.width,rect.height),8,3);
	text_img=cvxGetSubImage(src_img,rect);
	cvNamedWindow("text",CV_WINDOW_NORMAL);
	cvResizeWindow("text",rect.width*5,rect.height*5);
	cvDrawContours(text_img,contours,cvScalar(0,255,0),cvScalar(0,0,255),255,1,8,cvPoint(-rect.x,-rect.y));
	cvShowImage("text",text_img);
	cvWaitKey(3);
	char answer[3]="  ";
	CvxCharacter ch=cvxCharacter(*contours,answer);
	if(SearchCharacter(ch)<0.000001){
			cvWaitKey(1);
	}else{

		if(1){
		std::cout<<"What's this text?:";
		std::cin>>answer;
		ch=cvxCharacter(*contours,answer);
		int idx=getFileStorageIdx();
		if(ch.character_name[0]!='?'){
			WriteCharacterToFile(ch,idx);
			setFileStorageIdx(idx+1);
		}

		}
	}
	cvDestroyWindow("text");
}
void cvxBoundingContours(IplImage * src_img,CvSeq * src_contours,CvScalar color=cvScalar(rand()%255,rand()%255,rand()%255)){
	if(src_contours->h_next)cvxBoundingContours(src_img,src_contours->h_next);
	if(src_contours->v_next)cvxBoundingContours(src_img,src_contours->v_next,color);
	CvRect rect=cvBoundingRect(src_contours);
	if((rect.height>15 || rect.width>15)){

		//cvRectangle(src_img,cvPoint(rect.x,rect.y),cvPoint(rect.x+rect.width,rect.y+rect.height),color,1);
		cvxAskQuestion(src_img,src_contours);
	}
}

int main(){
	IplImage * src_img=cvLoadImage("E://Linhehe//CVLab//img//text2.png");
	IplImage * src_gray=cvxCreateImageSimilar(src_img,1);
	cvCvtColor(src_img,src_gray,CV_BGR2GRAY);
	IplImage * erode_img=cvxCreateImageSimilar(src_img);
	IplImage * contour_draw=cvxCreateImageSimilar(src_img);
	CvSeq *contours=cvxFindContourFromImage(src_img,Mem_seq,200);

	cvxBoundingContours(src_img,contours);
	cvxShow(src_img);
	cvWaitKey(0);
}