#pragma once
#include "stdafx.h"


void TEST_MAT()
{
	//Mat srcImage = imread("Image/plate.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//imshow("����", srcImage);
	Mat mat = imread("d:\\2.png");
	//for (int i = 0; i < mat.rows; i++)
	//{
	//	for (int j = 0; j < mat.cols; j++)
	//	{
	//		// ͨ��˳��:BGR
	//		int b = mat.at<Vec3b>(i, j)[0];
	//		cout << ((b==0)?0:1) << " ";
	//	}
	//	cout << endl;
	//}

	for (int i = 0; i < mat.rows; i++)
	{
		uchar* lineData = mat.ptr<uchar>(i);

		for (int j = 0; j < mat.cols; j++)
		{
			int b = *lineData;
			cout << ((b == 0) ? 0 : 1) << " ";
			lineData += 3;
		}
		cout << endl;
	}
	waitKey(0);
}