#pragma once
#include "stdafx.h"
#include <thread>

/**
 * @function on_trackbar
 * @������Ӧ�������Ļص�����
 */
void on_erosion_changed(int value, void* pSrc)
{
	Mat element = getStructuringElement(
		MORPH_CROSS,
		Size(2 * value + 1, 2 * value + 1),
		Point(value, value));

	//���Ͳ���
	Mat dst;
	erode(*((Mat*)pSrc), dst, element);
	imshow("���ͺ͸�ʴ", dst);
}

/**
 * @function on_trackbar
 * @������Ӧ�������Ļص�����
 */
void on_dilation_changed(int value, void* pSrc)
{
	Mat element = getStructuringElement(
		MORPH_CROSS,
		Size(2 * value + 1, 2 * value + 1),
		Point(value, value));

	//��ʴ����
	Mat dst;
	dilate(*(Mat*)pSrc, dst, element);
	imshow("���ͺ͸�ʴ", dst);
}

void TEST_DILATION()
{
	Mat src;
	src = imread("Image/cap01.jpg", 0); // �Ҷ�ͼ����
	if (!src.data)
	{
		cout << "ͼ���ʧ�ܣ�" << endl;
		return;
	}

	int nDilateSize = 0;
	int nErodeSize = 0;
	namedWindow("���ͺ͸�ʴ");
	createTrackbar("���Ͳ�����", "���ͺ͸�ʴ", &nErodeSize, 20, on_erosion_changed, &src);
	createTrackbar("��ʴϵ����", "���ͺ͸�ʴ", &nDilateSize, 20, on_dilation_changed, &src);
	on_erosion_changed(nErodeSize, &src);
	on_dilation_changed(nDilateSize, &src);

	while (char(waitKey()) != 'q')
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}