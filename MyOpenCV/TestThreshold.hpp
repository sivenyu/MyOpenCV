#pragma once

#include "stdafx.h"
#include <thread>

int thresholds = 100;
int MaxValue = 255;
/**
 * @function on_trackbar
 * @������Ӧ�������Ļص�����
 */
void on_threshold_changed(int value, void* pSrc)
{
	thresholds = value;
	Mat dst = (*(Mat*)pSrc).clone();
	cv::threshold(*(Mat*)pSrc, dst, thresholds, MaxValue, CV_THRESH_BINARY);

	imshow("��ֵ��ͼ��", dst);
}
void on_maxvalue_changed(int value, void* pImg)
{
	MaxValue = value;
	Mat dst = (*(Mat*)pImg).clone();
	cv::threshold(*(Mat*)pImg, dst, thresholds, MaxValue, CV_THRESH_BINARY);

	imshow("��ֵ��ͼ��", dst);
}


void ThresholdUsage2()
{
	Mat src, dst;
	src = imread("Image/cap01.bmp", 0); // �Ҷ�ͼ����
	if (!src.data)
	{
		cout << "ͼ���ʧ�ܣ�" << endl;
		return;
	}


	namedWindow("��ֵ��ͼ��");
	createTrackbar("��ֵ��", "��ֵ��ͼ��", &thresholds, 255, on_threshold_changed, &src);
	createTrackbar("�����ֵ��", "��ֵ��ͼ��", &MaxValue, 255, on_threshold_changed, &src);
	on_threshold_changed(thresholds, &src);

	while (char(waitKey()) != 'q')
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void ThresholdUsage3()
{
	Mat src, dst;
	src = imread("Image/cap01.bmp", IMREAD_GRAYSCALE); // �Ҷ�ͼ����
	if (!src.data)
	{
		cout << "ͼ���ʧ�ܣ�" << endl;
		return;
	}

	////�ҶȻ�(��ʡ��)
	//cvtColor(src, dst, CV_BGR2GRAY);
	//namedWindow("�ҶȻ���ͼ��");
	//imshow("�ҶȻ�ͼ��", dst);

	//��ֵ����ѡ��30��200.0Ϊ��ֵ
	//cv::threshold(src, dst, 100, 255, CV_THRESH_BINARY);
	//namedWindow("��ֵ��ͼ��");
	//imshow("��ֵ��ͼ��", dst);


	// ����Ӧ��ֵ��
	const int maxVal = 255;
	int blockSize = 41;
	double C = 0;
	cv::adaptiveThreshold(src, dst, maxVal,
		cv::ADAPTIVE_THRESH_GAUSSIAN_C, //cv::ADAPTIVE_THRESH_MEAN_C,
		cv::THRESH_BINARY,
		blockSize, C);

	cv::imshow("threshold", dst);
	cv::waitKey(0);
}

void TEST_THRESHOLD()
{
	ThresholdUsage2();
	//ThresholdUsage3();

 	return;
}