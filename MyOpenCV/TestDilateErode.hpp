#pragma once
#include "stdafx.h"
#include <thread>

/**
 * @function on_trackbar
 * @定义响应滑动条的回调函数
 */
void on_erosion_changed(int value, void* pSrc)
{
	Mat element = getStructuringElement(
		MORPH_CROSS,
		Size(2 * value + 1, 2 * value + 1),
		Point(value, value));

	//膨胀操作
	Mat dst;
	erode(*((Mat*)pSrc), dst, element);
	imshow("膨胀和腐蚀", dst);
}

/**
 * @function on_trackbar
 * @定义响应滑动条的回调函数
 */
void on_dilation_changed(int value, void* pSrc)
{
	Mat element = getStructuringElement(
		MORPH_CROSS,
		Size(2 * value + 1, 2 * value + 1),
		Point(value, value));

	//腐蚀操作
	Mat dst;
	dilate(*(Mat*)pSrc, dst, element);
	imshow("膨胀和腐蚀", dst);
}

void TEST_DILATION()
{
	Mat src;
	src = imread("Image/cap01.jpg", 0); // 灰度图载入
	if (!src.data)
	{
		cout << "图像打开失败！" << endl;
		return;
	}

	int nDilateSize = 0;
	int nErodeSize = 0;
	namedWindow("膨胀和腐蚀");
	createTrackbar("膨胀操作：", "膨胀和腐蚀", &nErodeSize, 20, on_erosion_changed, &src);
	createTrackbar("腐蚀系数：", "膨胀和腐蚀", &nDilateSize, 20, on_dilation_changed, &src);
	on_erosion_changed(nErodeSize, &src);
	on_dilation_changed(nDilateSize, &src);

	while (char(waitKey()) != 'q')
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}