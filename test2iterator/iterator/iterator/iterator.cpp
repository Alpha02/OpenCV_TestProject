// iterator.cpp : 定义控制台应用程序的入口点。
//这个蛋疼的程序
//将一个24位颜色的图片的每通道颜色个数从256线性地减小到1，并观察出现的变化。
//这是一个蛋疼的程序。

#include "stdafx.h"
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;
void setAllWhite(Mat & src,int N){
	Mat_<Vec3b>::iterator begin,end;
	begin=src.begin<Vec3b>();
	end=src.end<Vec3b>();
	while(begin!=end){
		for(int i=0;i<=2;i+=1){
			uchar c=(uchar)((int)((*begin)[i]/256.0*N)*(256.0/N));
			(*begin)[i]=c;
			/*
			(*begin)[i]/=N;
			(*begin)[i]*=N;
			if((*begin)[i]>255-N/2){
				(*begin)[i]=255;
			}else{
				(*begin)[i]+=N/2;
			}
			*/
		}
		begin++;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	Mat src;
	src=imread("E://Linhehe//CVLab//img//2.png");
	if(src.data==0){
		cout<<"Fail to load image..."<<endl;
	}else{
		cout<<"Load image Completed."<<endl;
		namedWindow("win");
		imshow("win",src);
		namedWindow("win2");
		Mat src2;
		src.copyTo(src2);
		for(int i=256;i>0;i-=1){
			src.copyTo(src2);
			setAllWhite(src2,i);
			imshow("win2",src2);
			cout<<i<<" colors"<<endl;
			waitKey();
		
		}
		
		waitKey();
	}
	return 0;
}

