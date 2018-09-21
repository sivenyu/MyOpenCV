#pragma once

#include "stdafx.h"

#define DPI						(1200)
//#define MM_TO_PIXELS(mm)		((int)(((mm) * (DPI)) / 25.4))
#define MM_TO_PIXELS(mm)		(mm)

#define MM_TO_INCH(mm)			((mm) / 25.4)
#define INCH_TO_MM(inch)		((inch) * 25.4)
//#define INCH_TO_PIXELS(inch)	((inch) * (DPI))
#define INCH_TO_PIXELS(inch)	(inch)

void MY_PERSPECTIVE_TRANSFORM()
{
	// 载入图像(1200*1200)
	cv::Mat srcImg = cv::imread("D:\\work\\000002\\data.bmp");
	if (srcImg.empty())
		return;

	// 四个理论靶标点坐标
	std::vector<cv::Point2f> marks;
	marks.push_back(cv::Point2f(MM_TO_PIXELS(15.6), MM_TO_PIXELS(0.37)));
	marks.push_back(cv::Point2f(MM_TO_PIXELS(14.6), MM_TO_PIXELS(13.6)));
	marks.push_back(cv::Point2f(MM_TO_PIXELS(0.42), MM_TO_PIXELS(13.6)));
	marks.push_back(cv::Point2f(MM_TO_PIXELS(0.42), MM_TO_PIXELS(0.37)));

	// 设定目的靶标点坐标
	std::vector<cv::Point2f> msr_marks;
	msr_marks.push_back(cv::Point2f(MM_TO_PIXELS(15.6-0.8), MM_TO_PIXELS(0.37+0.7))); //给定偏差
	msr_marks.push_back(cv::Point2f(MM_TO_PIXELS(14.6), MM_TO_PIXELS(13.6)));
	msr_marks.push_back(cv::Point2f(MM_TO_PIXELS(0.42), MM_TO_PIXELS(13.6)));
	msr_marks.push_back(cv::Point2f(MM_TO_PIXELS(0.42), MM_TO_PIXELS(0.37)));

	// 计算映射矩阵
	cv::Mat transmtx = cv::getPerspectiveTransform(marks, msr_marks);

	// 初始化目的图像
	//cv::Mat dstImg = cv::Mat::zeros(19200, 16800, CV_8UC1);  // 
	cv::Mat dstImg = cv::imread("D:\\work\\000002\\data2.bmp");

	// 进行透视变换
	cv::warpPerspective(srcImg, dstImg, transmtx, dstImg.size());

	// 显示结果
	cv::imshow("image", dstImg);
	// 保存结果
	imwrite("D:\\work\\000002\\out.bmp", dstImg);
	cv::waitKey();
}




void MY_TRANSFORM()
{
	std::vector<cv::Point2f> std_pts; // 玻璃尺理论数据
	std_pts.push_back(cv::Point2f(MM_TO_PIXELS(30.1785), MM_TO_PIXELS(134.027))); //右下
	std_pts.push_back(cv::Point2f(MM_TO_PIXELS(30.1785), MM_TO_PIXELS(718.227))); //右上
	std_pts.push_back(cv::Point2f(MM_TO_PIXELS(766.7785), MM_TO_PIXELS(718.227))); //左上
	std_pts.push_back(cv::Point2f(MM_TO_PIXELS(766.7785), MM_TO_PIXELS(134.027))); //左下
	cout << "玻璃尺理论坐标：" << endl;
	cout << std_pts << endl;

	std::vector<cv::Point2f> msr_pts; // 玻璃尺运动系统的测量数据
	msr_pts.push_back(cv::Point2f(MM_TO_PIXELS(30.1785), MM_TO_PIXELS(134.027))); //右下
	msr_pts.push_back(cv::Point2f(MM_TO_PIXELS(30.2765), MM_TO_PIXELS(718.217))); //右上
	msr_pts.push_back(cv::Point2f(MM_TO_PIXELS(766.8495), MM_TO_PIXELS(718.493))); //左上
	msr_pts.push_back(cv::Point2f(MM_TO_PIXELS(766.7465), MM_TO_PIXELS(134.307))); //左下
	cout << "玻璃尺测量坐标：" << endl;
	cout << msr_pts << endl;

	// 计算映射矩阵
	cv::Mat transmtx = cv::getPerspectiveTransform(msr_pts, std_pts);

	cout << "变换矩阵:" << endl;
	cout << transmtx << endl << endl;



	// 靶标点测量坐标
	double mark[4][2] = {
		{ INCH_TO_MM(2.324223), INCH_TO_MM(3.058959) },		//右下-3
		{ INCH_TO_MM(2.418523), INCH_TO_MM(19.561306) },	//右上-2
		{ INCH_TO_MM(19.197343), INCH_TO_MM(19.457905) },	//左上-1
		{ INCH_TO_MM(19.103443), INCH_TO_MM(2.955259) }		//左下-0
	};
	
	cv::Mat mMsr = cv::Mat(4, 2, CV_64FC1, mark); // 靶标点在运动系统的测量数据
	cv::Mat mDst = cv::Mat::zeros(Size(2, 4), CV_64FC1); // 靶标点直角坐标系的理论数据

	try
	{
		cout << "靶标点测量坐标（X,Y不垂直）:" << endl;
		cout << cv::format(mMsr, Formatter::FMT_C) << endl;
		cout << "=>" << endl;

		// 进行透视变换
		cv::warpPerspective(mMsr, mDst, transmtx, mDst.size(), WARP_INVERSE_MAP);
		
		cout << "靶标点理论坐标（X,Y垂直）:" << endl;
		cout << cv::format(mDst, Formatter::FMT_C) << endl;
	}
	catch (Exception ex)
	{
		cout << "Any key for exception exit!" << endl;
	}

	system("pause");
}