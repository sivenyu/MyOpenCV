#pragma once
#include "stdafx.h"

void TEST_HOUGH_CIRCLE()
{
	Mat src, mid, dst;
	src = imread("Image/cap01.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cout << "图像打开失败！" << endl;
		return;
	}

	//namedWindow("霍夫圆变换");
	//imshow("霍夫圆变换", src);


	//边缘检测
	//Canny(src, mid, 100, 200, 3);

	// Reduce the noise so we avoid false circle detection
	GaussianBlur(src, mid, Size(9, 9), 2, 2);


	/** 霍夫圆变换
	 * src_gray: 输入图像(灰度图)
	 * circles : 存储下面三个参数 : x_{ c }, y_{ c }, r 集合的容器来表示每个检测到的圆.
	 * CV_HOUGH_GRADIENT : 指定检测方法.现在OpenCV中只有霍夫梯度法
	 * dp = 1 : 累加器图像的反比分辨率
	 * min_dist = src_gray.rows / 8 : 检测到圆心之间的最小距离
	 * param_1 = 200 : Canny边缘函数的高阈值
	 * param_2 = 100 : 圆心检测阈值.
	 * min_radius = 0 : 能检测到的最小圆半径, 默认为0.
	 * max_radius = 0 : 能检测到的最大圆半径, 默认为0
	 */
	vector<Vec3f> circles;
	HoughCircles(mid, circles, CV_HOUGH_GRADIENT, 1.5, mid.rows/8, 200, 150, 0, 0);

	//依次在图中绘制出圆 
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		//绘制圆心 
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);

		//绘制圆轮廓 
		circle(src, center, radius, Scalar(0, 0, 0), 3, 8, 0);
	}
	imshow("霍夫圆", src);

	waitKey();
}