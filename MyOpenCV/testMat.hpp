#pragma once
#include "stdafx.h"


#pragma comment(lib, "opencv_imgcodecs340d.lib")
#pragma comment(lib, "opencv_highgui340d.lib")

void TEST_MAT()
{
	Mat srcImage = imread("bmp/1.bmp");
	imshow("Ô­Ê¼°Ð±ê", srcImage);

	waitKey(0);
}