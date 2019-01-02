#pragma once
#include "stdafx.h"

void TEST_HOUGH_CIRCLE()
{
	Mat src, mid, dst;
	src = imread("Image/cap01.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cout << "ͼ���ʧ�ܣ�" << endl;
		return;
	}

	//namedWindow("����Բ�任");
	//imshow("����Բ�任", src);


	//��Ե���
	//Canny(src, mid, 100, 200, 3);

	// Reduce the noise so we avoid false circle detection
	GaussianBlur(src, mid, Size(9, 9), 2, 2);


	/** ����Բ�任
	 * src_gray: ����ͼ��(�Ҷ�ͼ)
	 * circles : �洢������������ : x_{ c }, y_{ c }, r ���ϵ���������ʾÿ����⵽��Բ.
	 * CV_HOUGH_GRADIENT : ָ����ⷽ��.����OpenCV��ֻ�л����ݶȷ�
	 * dp = 1 : �ۼ���ͼ��ķ��ȷֱ���
	 * min_dist = src_gray.rows / 8 : ��⵽Բ��֮�����С����
	 * param_1 = 200 : Canny��Ե�����ĸ���ֵ
	 * param_2 = 100 : Բ�ļ����ֵ.
	 * min_radius = 0 : �ܼ�⵽����СԲ�뾶, Ĭ��Ϊ0.
	 * max_radius = 0 : �ܼ�⵽�����Բ�뾶, Ĭ��Ϊ0
	 */
	vector<Vec3f> circles;
	HoughCircles(mid, circles, CV_HOUGH_GRADIENT, 1.5, mid.rows/8, 200, 150, 0, 0);

	//������ͼ�л��Ƴ�Բ 
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		//����Բ�� 
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);

		//����Բ���� 
		circle(src, center, radius, Scalar(0, 0, 0), 3, 8, 0);
	}
	imshow("����Բ", src);

	waitKey();
}