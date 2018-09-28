#pragma once

#include "stdafx.h"

void fromVectorToMat(vector<Point2f> v, Mat &pts)
{
	int nbrOfPoints = (int)v.size();

	if (pts.empty())
		pts.create(2, nbrOfPoints, CV_32F);

	for (int i = 0; i < nbrOfPoints; ++i)
	{
		pts.at<float>(0, i) = v[i].x;
		pts.at<float>(1, i) = v[i].y;
	}
}

void fromMatToVector(Mat pts, vector<Point2f> &v)
{
	int nbrOfPoints = pts.cols;

	for (int i = 0; i < nbrOfPoints; ++i)
	{
		Point2f temp;
		temp.x = pts.at<float>(0, i);
		temp.y = pts.at<float>(1, i);
		v.push_back(temp);
	}
}
