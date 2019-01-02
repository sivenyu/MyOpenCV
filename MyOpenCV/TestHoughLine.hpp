#pragma once
#include "stdafx.h"

void TEST_HOUGH_LINE()
{
	Mat src, mid, dst;
	src = imread("Image/cap01.bmp", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cout << "ͼ���ʧ�ܣ�" << endl;
		return;
	}
	namedWindow("�����߱任");
	imshow("�����߱任", src);

	//��Ե���
	Canny(src, mid, 100, 200, 3);

	cvtColor(mid, dst, CV_GRAY2BGR);

	/**
	 * dst: ��Ե�������ͼ��. ��Ӧ���Ǹ��Ҷ�ͼ (����ʵ���Ǹ���ֵ��ͼ)
	 * rho : �������� r ������ֵΪ��λ�ķֱ���. ����ʹ�� 1 ����.
	 * theta : �������� \theta �Ի���Ϊ��λ�ķֱ���.����ʹ��1��(��CV_PI/180)
	 * threshold: Ҫ����⡱ һ��ֱ���������ٵĵ����߽��� * minLinLength: �����һ��ֱ�ߵ����ٵ������. �����������ֱ�߽�������.
	 * maxLineGap: �ܱ���Ϊ��һ��ֱ���ϵ������������.
	 */
	vector<Vec4i> lines;
	HoughLinesP(mid, lines, 1, CV_PI/180, 50, 50, 40);

	//���λ���ÿ���߶�
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, CV_AA);
	}
	imshow("��Ե�����ͼ", mid);
	imshow("����Ч��ͼ", dst);

	waitKey();
}