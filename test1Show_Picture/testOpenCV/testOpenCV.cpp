// testOpenCV.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "opencv2/opencv.hpp"
using namespace cv;
int _tmain(int argc, _TCHAR* argv[])
{
	int a=1;
	Mat img=imread("E:\\Download\\Download_Chrome\\ACG\\百变小樱\\ClowCard\\6c6dad6eddc451da416a9b56b6fd5266d1163223.jpg");
	imshow("src",img);
	waitKey();
	return 0;
}

