#pragma once
#include "stdafx.h"

//斜率计算夹角
//line_1_k为一条直线斜率，line_2_k为另一条直线斜率
float get_lines_arctan(float line_1_k, float line_2_k)
{
	float tan_k = 0; //直线夹角正切值
	float lines_arctan;//直线斜率的反正切值
	tan_k = (line_2_k - line_1_k) / (1 + line_2_k*line_1_k); //求直线夹角的公式
	lines_arctan = atan(tan_k)* 180.0 / 3.1415926;	// 弧度转角度

	return lines_arctan;	
}

// 计算两个向量夹角
// 以pt1为基准
float getAngelOfTwoVector(Point2f &pt1, Point2f &pt2, Point2f &c)
{
	// 计算两个向量的斜率角，然后相减
	float theta = atan2(pt1.x - c.x, pt1.y - c.y) - atan2(pt2.x - c.x, pt2.y - c.y);
	if (theta > CV_PI)
		theta -= 2 * CV_PI;
	if (theta < -CV_PI)
		theta += 2 * CV_PI;

	theta = theta * 180.0 / CV_PI;
	return theta;
}

void TEST_ANGLE()
{
	//
	Point2f c(0, 0);
	Point2f pt1(0, -1);
	Point2f pt2(-1, 0);

	float theta = getAngelOfTwoVector(pt1, pt2, c);

	cout << "theta: " << theta << "(度)"  << endl;
	system("pause");
}