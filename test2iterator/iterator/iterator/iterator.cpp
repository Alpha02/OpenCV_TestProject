// iterator.cpp : �������̨Ӧ�ó������ڵ㡣
//������۵ĳ���
//��һ��24λ��ɫ��ͼƬ��ÿͨ����ɫ������256���Եؼ�С��1�����۲���ֵı仯��
//����һ�����۵ĳ���

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

