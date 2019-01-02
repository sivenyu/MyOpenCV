#pragma once
#include "stdafx.h"

void TEST_HOUGH_LINE()
{
	Mat src, mid, dst;
	src = imread("Image/cap01.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cout << "图像打开失败！" << endl;
		return;
	}
	namedWindow("霍夫线变换");
	imshow("霍夫线变换", src);

	//边缘检测
	Canny(src, mid, 100, 200, 3);

	cvtColor(mid, dst, CV_GRAY2BGR);

	/**
	 * dst: 边缘检测的输出图像. 它应该是个灰度图 (但事实上是个二值化图)
	 * rho : 参数极径 r 以像素值为单位的分辨率. 我们使用 1 像素.
	 * theta : 参数极角 \theta 以弧度为单位的分辨率.我们使用1度(即CV_PI/180)
	 * threshold: 要”检测” 一条直线所需最少的的曲线交点 * minLinLength: 能组成一条直线的最少点的数量. 点数量不足的直线将被抛弃.
	 * maxLineGap: 能被认为在一条直线上的亮点的最大距离.
	 */
	vector<Vec4i> lines;
	HoughLinesP(mid, lines, 1, CV_PI/180, 50, 50, 40);

	//依次画出每条线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, CV_AA);
	}
	imshow("边缘检测后的图", mid);
	imshow("最终效果图", dst);

	waitKey();
}