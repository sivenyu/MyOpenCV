#pragma once
#include "stdafx.h"


void TEST_MAT()
{
	Mat srcImage = imread("Image/plate.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("����", srcImage);

	waitKey(0);
}