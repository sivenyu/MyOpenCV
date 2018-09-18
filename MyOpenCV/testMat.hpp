#pragma once
#include "stdafx.h"


#pragma comment(lib, "opencv_imgcodecs340d.lib")


void TEST_MAT()
{
	Mat srcImage = imread("bmp/1.bmp", 0);
	imwrite("123.png", srcImage);

	imshow("原始靶标", srcImage);

	//Mat srcImage = imread("img/plate.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//imshow("车牌", srcImage);

	waitKey(0);
}