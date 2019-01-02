#pragma once
#include "stdafx.h"

/**
 * @function on_trackbar
 * @������Ӧ�������Ļص�����
 */
void on_canny_threshold_changed(int value, void* pSrc)
{
	Mat dst, detected_edges;
	blur(*(Mat*)pSrc, detected_edges, Size(3, 3));

	int ratio = 3;
	int kernel_size = 3;
	Canny(detected_edges, dst, value, value* ratio, kernel_size);
	
	imshow("���ؼ��", dst);
}

void TEST_CANNY()
{
	Mat src;
	src = imread("Image/cap01.bmp", 0); // �Ҷ�ͼ����
	if (src.empty())
	{
		cout << "ͼ���ʧ�ܣ�" << endl;
		return;
	}

	int lowThreshold;
	namedWindow("���ؼ��");
	createTrackbar("��ֵ��", "���ؼ��", &lowThreshold, 100, on_canny_threshold_changed, &src);

	on_canny_threshold_changed(0, &src);

	while (char(waitKey()) != 'q')
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}