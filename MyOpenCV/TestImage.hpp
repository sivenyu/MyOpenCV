#pragma once

#include "stdafx.h"

/**
 * 明码处理
 */
void TestHybrid()
{
	// 叠加
	Mat barcode = imread("Image/barcode.png");
	Mat blackground = Mat(barcode.rows+100, barcode.cols + 40, CV_8UC3, Scalar::all(255));

	int xPos = (blackground.cols - barcode.cols) / 2;
	int yPos = 5;
	Mat imageROI = blackground(cv::Rect(xPos, yPos, barcode.cols, barcode.rows));
	barcode.copyTo(imageROI);

	// 添加文字
	string strText("Hello, this is a barcode 2018");
	putText(blackground, strText, cvPoint(5, 40+imageROI.rows), cv::FONT_HERSHEY_COMPLEX, 1, CvScalar(0, 0, 0), 2);

	namedWindow("result");
	imshow("result", blackground);
	waitKey();
}

void TEST_IMAGE()
{
	TestHybrid();
}