#include <cv.h>
#include  <highgui.h>
#include <hehecv.h>
using namespace std;
//method= CV_RETR_XX.
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
	IplImage imgdata;
	char character_name[3];
};
CvxCharacter cvxCharacter(IplImage &imgdata,char *character_name){
	CvxCharacter character;
	character.imgdata=imgdata;
	character.character_name[0]=character_name[0];
	character.character_name[1]=character_name[1];
	character.character_name[2]=character_name[2];
	return character;
}
void matchCharacter(IplImage * src_img,CvSeq * contours){

}
int getFileStorageIdx(){
	CvFileStorage * file=cvOpenFileStorage("./ch_data/rec_manager.xml",0,CV_STORAGE_READ);
	int idx=cvReadIntByName(file,0,"n");
	cvReleaseFileStorage(&file);
	return idx;
}
void setFileStorageIdx(int idx){
	CvFileStorage * file=cvOpenFileStorage("./ch_data/rec_manager.xml",0,CV_STORAGE_WRITE);
	cvWriteInt(file,"n",idx);
	cvReleaseFileStorage(&file);
}
CvxCharacter getCharacterFromFile(int idx){
	char node_name[40];
	sprintf(node_name,"./ch_data/ch%d.xml",idx);
	
	CvFileStorage * file=cvOpenFileStorage(node_name,0,CV_STORAGE_READ);
	CvxCharacter ch;
	IplImage *temp_img=(IplImage*)cvReadByName(file,0,"img");
	char *ch_name=(char*)cvReadStringByName(file,0,"name");
	ch=cvxCharacter(*temp_img,ch_name);
	cvReleaseFileStorage(&file);
	return ch;
}
void WriteCharacterToFile(CvxCharacter & ch,int idx){
	char node_name[40];
	sprintf(node_name,"./ch_data/ch%d.xml",idx);
	CvFileStorage * file=cvOpenFileStorage(node_name,0,CV_STORAGE_WRITE);
	cvWriteString(file,"name",ch.character_name);
	cvWrite(file,"img",&(ch.imgdata));

	cvReleaseFileStorage(&file);
}
double SearchCharacter(CvxCharacter & ch){
	int idx=getFileStorageIdx();
	int idx_best=0;
	double m_best=1;
	char name_best[3];
	while(idx--){

		CvxCharacter ch_temp=getCharacterFromFile(idx);
		double m=cvMatchShapes(&(ch_temp.imgdata),&(ch.imgdata),CV_CONTOURS_MATCH_I1);
		if(m<m_best){
			m_best=m;
			strcpy(name_best,ch_temp.character_name);
			idx_best=idx;
		}

	}
	if(m_best<0.0001){
		cout<<"match:  "<<name_best<<" : "<<m_best<<"\n";
	}else{
		cout<<"maybe:  "<<name_best<<" : "<<m_best<<"\n";

	}
	return m_best;

}
void cvxAskQuestion(IplImage * src_img,CvSeq * contours){
	CvRect rect=cvBoundingRect(contours);
	IplImage * text_img=cvCreateImage(cvSize(rect.width,rect.height),8,3);
	IplImage * text_gray=cvCreateImage(cvSize(rect.width,rect.height),8,1);


	text_img=cvxGetSubImage(src_img,rect);
	cvCvtColor(text_img,text_gray,CV_BGR2GRAY);
	cvThreshold(text_gray,text_gray,240,255,CV_THRESH_BINARY_INV);
	cvNamedWindow("text",CV_WINDOW_NORMAL);
	cvResizeWindow("text",rect.width*5,rect.height*5);
	cvShowImage("text",text_gray);
	cvWaitKey(3);
	char answer[3]="  ";
	CvxCharacter ch=cvxCharacter(*text_gray,answer);
	if(SearchCharacter(ch)==0){
			cvWaitKey(1000);
	}else{
	
		std::cout<<"What's this text?:";
		std::cin>>answer;
		ch=cvxCharacter(*text_gray,answer);
		int idx=getFileStorageIdx();
		if(ch.character_name[0]!='?'){
			WriteCharacterToFile(ch,idx);
			setFileStorageIdx(idx+1);
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
	IplImage * src_img=cvLoadImage("E://Linhehe//CVLab//img//text4.png");
	IplImage * src_gray=cvxCreateImageSimilar(src_img,1);
	cvCvtColor(src_img,src_gray,CV_BGR2GRAY);
	IplImage * erode_img=cvxCreateImageSimilar(src_img);
	IplImage * contour_draw=cvxCreateImageSimilar(src_img);
	CvMemStorage *storage=cvCreateMemStorage();
	CvSeq *contours=cvxFindContourFromImage(src_img,storage,200);
	cvxBoundingContours(src_img,contours);
	cvxShow(src_img);
	cvWaitKey(0);
}