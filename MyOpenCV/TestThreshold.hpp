#pragma once

#include "stdafx.h"
#include <thread>

int thresholds = 100;
int MaxValue = 255;
/**
 * @function on_trackbar
 * @定义响应滑动条的回调函数
 */
void on_threshold_changed(int value, void* pSrc)
{
	thresholds = value;
	Mat dst = (*(Mat*)pSrc).clone();
	cv::threshold(*(Mat*)pSrc, dst, thresholds, MaxValue, CV_THRESH_BINARY);

	imshow("二值化图像", dst);
}
void on_maxvalue_changed(int value, void* pImg)
{
	MaxValue = value;
	Mat dst = (*(Mat*)pImg).clone();
	cv::threshold(*(Mat*)pImg, dst, thresholds, MaxValue, CV_THRESH_BINARY);

	imshow("二值化图像", dst);
}


void ThresholdUsage2()
{
	Mat src, dst;
	src = imread("Image/cap01.bmp", 0); // 灰度图载入
	if (!src.data)
	{
		cout << "图像打开失败！" << endl;
		return;
	}


	namedWindow("二值化图像");
	createTrackbar("阈值：", "二值化图像", &thresholds, 255, on_threshold_changed, &src);
	createTrackbar("最大阈值：", "二值化图像", &MaxValue, 255, on_threshold_changed, &src);
	on_threshold_changed(thresholds, &src);

	while (char(waitKey()) != 'q')
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void ThresholdUsage3()
{
	Mat src, dst;
	src = imread("Image/cap01.bmp", IMREAD_GRAYSCALE); // 灰度图载入
	if (!src.data)
	{
		cout << "图像打开失败！" << endl;
		return;
	}

	////灰度化(可省略)
	//cvtColor(src, dst, CV_BGR2GRAY);
	//namedWindow("灰度化化图像");
	//imshow("灰度化图像", dst);

	//二值化，选择30，200.0为阈值
	//cv::threshold(src, dst, 100, 255, CV_THRESH_BINARY);
	//namedWindow("二值化图像");
	//imshow("二值化图像", dst);


	// 自适应二值化
	const int maxVal = 255;
	int blockSize = 41;
	double C = 0;
	cv::adaptiveThreshold(src, dst, maxVal,
		cv::ADAPTIVE_THRESH_GAUSSIAN_C, //cv::ADAPTIVE_THRESH_MEAN_C,
		cv::THRESH_BINARY,
		blockSize, C);

	cv::imshow("threshold", dst);
	cv::waitKey(0);
}

void TEST_THRESHOLD()
{
	ThresholdUsage2();
	//ThresholdUsage3();

 	return;
}