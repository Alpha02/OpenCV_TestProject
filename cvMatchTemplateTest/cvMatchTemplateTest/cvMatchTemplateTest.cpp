#include <cv.h>
#include <highgui.h>
#include <hehecv.h>
int main(int argc, char * argv[])
{
	char * win_list[]={"ImageCutter","reswin"};
	cvxArrangeWindows(2,win_list,cvSize(1366,568));
	while(1){
	IplImage * src_img=cvLoadImage("E://Linhehe//CVLab//img//6.jpg");
	IplImage * src_img2=cvLoadImage("E://Linhehe//CVLab//img//7.jpg");
	IplImage * sub_img=cvxCutImageByMouse(src_img,"ImageCutter");
	IplImage * src_img2_resize=cvxGetSubImage(
		src_img2,
		cvRect(
		sub_img->width/2,
		sub_img->height/2,
		src_img2->width-sub_img->width+1,
		src_img2->height-sub_img->height+1
		)
		);
	IplImage *result_img=cvCreateImage(
		cvSize(
		src_img2->width-sub_img->width+1,
		src_img2->height-sub_img->height+1
		),
		32,
		1
		);
	cvNamedWindow("subwin",CV_WINDOW_AUTOSIZE);
	cvShowImage("subwin",sub_img);
	cvMatchTemplate(src_img2,sub_img,result_img,CV_TM_SQDIFF);
	cvNormalize(result_img,result_img,1,0,CV_MINMAX);
	CvPoint minPoint,maxPoint;
	cvMinMaxLoc(result_img,NULL,NULL,&minPoint,&maxPoint);
	cvRectangle(src_img2_resize,cvPoint(minPoint.x-sub_img->width/2,minPoint.y-sub_img->height/2),cvPoint(minPoint.x+sub_img->width/2,minPoint.y+sub_img->height/2),cvScalar(0,255,0,255),5);
	cvNamedWindow("reswin",CV_WINDOW_NORMAL);
	cvShowImage("reswin",src_img2_resize);
	}
	return 0;
}

