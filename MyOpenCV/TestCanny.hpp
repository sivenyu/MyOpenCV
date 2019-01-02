#pragma once
#include "stdafx.h"

/**
 * @function on_trackbar
 * @定义响应滑动条的回调函数
 */
void on_canny_threshold_changed(int value, void* pSrc)
{
	Mat dst, detected_edges;
	blur(*(Mat*)pSrc, detected_edges, Size(3, 3));

	int ratio = 3;
	int kernel_size = 3;
	Canny(detected_edges, dst, value, value* ratio, kernel_size);
	
	imshow("边沿检测", dst);
}

void TEST_CANNY()
{
	Mat src;
	src = imread("Image/cap01.bmp", 0); // 灰度图载入
	if (src.empty())
	{
		cout << "图像打开失败！" << endl;
		return;
	}

	int lowThreshold;
	namedWindow("边沿检测");
	createTrackbar("阀值：", "边沿检测", &lowThreshold, 100, on_canny_threshold_changed, &src);

	on_canny_threshold_changed(0, &src);

	while (char(waitKey()) != 'q')
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}