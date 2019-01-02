#pragma once
#include "stdafx.h"

Mat Do_Canny(Mat & src)
{
	Mat dst, detected_edges;
	blur(src, detected_edges, Size(3, 3));

	int threshold = 71;
	int ratio = 3;
	int kernel_size = 3;
	Canny(detected_edges, dst, threshold, threshold * ratio, kernel_size);

	return dst;
}

void TEST_MATCH_TEMPLATE()
{
	Mat src, model;
	src = imread("Image/cap01.jpg", 0);
	model = imread("Image/model01.jpg", 0);
	if (model.empty())
	{
		cout << "图像打开失败！" << endl;
		return;
	}

	Mat dst_model = Do_Canny(model);
	imshow("模板", model);

	Mat dst_source = Do_Canny(src);
	int result_cols = src.cols - model.cols + 1;
	int result_rows = src.rows - model.rows + 1;
	Mat result;
	result.create(result_cols, result_rows, CV_32FC1);

	matchTemplate(src, model, result, CV_TM_SQDIFF_NORMED);


	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	double minVal = -1;
	double maxVal;
	Point minLoc;
	Point maxLoc;
	Point matchLoc;

	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	cout << "匹配度：" << minVal << endl;

	matchLoc = minLoc;

	rectangle(src, matchLoc, Point(matchLoc.x + model.cols, matchLoc.y + model.rows), Scalar(0, 0, 255), 2, 8, 0);
	imshow("匹配结果", src);
	waitKey();
}