#pragma once

#include "stdafx.h"
       

cv::Point2f center(0, 0);

cv::Point2f computeIntersect(cv::Vec4i a, cv::Vec4i b)
{
	int x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3], x3 = b[0], y3 = b[1], x4 = b[2], y4 = b[3];
	float denom;

	if (float d = ((float)(x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4)))
	{
		cv::Point2f pt;
		pt.x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / d;
		pt.y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / d;
		return pt;
	}
	else
		return cv::Point2f(-1, -1);
}

void sortCorners(std::vector<cv::Point2f>& corners, cv::Point2f center)
{
	std::vector<cv::Point2f> top, bot;

	for (int i = 0; i < corners.size(); i++)
	{
		if (corners[i].y < center.y)
			top.push_back(corners[i]);
		else
			bot.push_back(corners[i]);
	}
	corners.clear();

	if (top.size() == 2 && bot.size() == 2)
	{
		cv::Point2f tl = top[0].x > top[1].x ? top[1] : top[0];
		cv::Point2f tr = top[0].x > top[1].x ? top[0] : top[1];
		cv::Point2f bl = bot[0].x > bot[1].x ? bot[1] : bot[0];
		cv::Point2f br = bot[0].x > bot[1].x ? bot[0] : bot[1];

		corners.push_back(tl);
		corners.push_back(tr);
		corners.push_back(br);
		corners.push_back(bl);
	}
}





void TEST_PERSPECTIVE_TRANSFORM()
{
	// 载入图像→灰度化→边缘处理得到边缘图像
	cv::Mat src = cv::imread("Image/poker.jpg");
	if (src.empty())
		return;

	cv::Mat bw;
	cv::cvtColor(src, bw, CV_BGR2GRAY);
	cv::blur(bw, bw, cv::Size(3, 3));
	cv::Canny(bw, bw, 100, 100, 3);

	// 霍夫变换进行直线检测
	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(bw, lines, 1, CV_PI / 180, 70, 30, 10);

	// Expand the lines  
	for (int i = 0; i < lines.size(); i++)
	{
		cv::Vec4i v = lines[i];
		lines[i][0] = 0;
		lines[i][1] = ((float)v[1] - v[3]) / (v[0] - v[2]) * -v[0] + v[1];
		lines[i][2] = src.cols;
		lines[i][3] = ((float)v[1] - v[3]) / (v[0] - v[2]) * (src.cols - v[2]) + v[3];
	}

	// 求出四个顶点的坐标
	std::vector<cv::Point2f> corners;
	for (int i = 0; i < lines.size(); i++)
	{
		for (int j = i + 1; j < lines.size(); j++)
		{
			cv::Point2f pt = computeIntersect(lines[i], lines[j]);
			if (pt.x >= 0 && pt.y >= 0)
				corners.push_back(pt);
		}
	}

	// 检查是不是四边形
	std::vector<cv::Point2f> approx;
	cv::approxPolyDP(cv::Mat(corners), approx, cv::arcLength(cv::Mat(corners), true) * 0.02, true);
	if (approx.size() != 4)
	{
		std::cout << "The object is not quadrilateral!" << std::endl;
		return;
	}

	// 获得中心点坐标
	for (int i = 0; i < corners.size(); i++)
		center += corners[i];
	center *= (1. / corners.size());

	sortCorners(corners, center);
	if (corners.size() == 0) {
		std::cout << "The corners were not sorted correctly!" << std::endl;
		return;
	}
	cv::Mat dst = src.clone();

	// Draw lines  
	for (int i = 0; i < lines.size(); i++)
	{
		cv::Vec4i v = lines[i];
		cv::line(dst, cv::Point(v[0], v[1]), cv::Point(v[2], v[3]), CV_RGB(0, 255, 0));
	}

	// Draw corner points  
	cv::circle(dst, corners[0], 3, CV_RGB(255, 0, 0), 2);
	cv::circle(dst, corners[1], 3, CV_RGB(0, 255, 0), 2);
	cv::circle(dst, corners[2], 3, CV_RGB(0, 0, 255), 2);
	cv::circle(dst, corners[3], 3, CV_RGB(255, 255, 255), 2);

	// Draw mass center  
	cv::circle(dst, center, 3, CV_RGB(255, 255, 0), 2);

	// 初始化目的图像
	cv::Mat quad = cv::Mat::zeros(300, 220, CV_8UC3);

	// 获取目的图像的四个顶点
	std::vector<cv::Point2f> quad_pts;
	quad_pts.push_back(cv::Point2f(0, 0));
	quad_pts.push_back(cv::Point2f(quad.cols, 0));
	quad_pts.push_back(cv::Point2f(quad.cols, quad.rows));
	quad_pts.push_back(cv::Point2f(0, quad.rows));

	cout << "原始点:" << endl;
	cout << corners << endl << endl;

	cout << "目的点:" << endl;
	cout << quad_pts << endl << endl;


	// 计算映射矩阵
	cv::Mat transmtx = cv::getPerspectiveTransform(corners, quad_pts);
	cout << "变换矩阵:" << endl;
	cout << transmtx << endl << endl;


	// 进行透视变换
	cv::warpPerspective(src, quad, transmtx, quad.size());

	// 显示结果
	cv::imshow("image", dst);
	cv::imshow("quadrilateral", quad);
	cv::waitKey();
}
