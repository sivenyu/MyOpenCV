#pragma once

#include "stdafx.h"

#define DPI						(1200) // �ֱ���
//#define MM_TO_PIXELS(mm)		((int)(((mm) * (DPI)) / 25.4))
#define MM_TO_PIXELS(mm)		(mm)

#define MM_TO_INCH(mm)			((mm) / 25.4)
#define INCH_TO_MM(inch)		((inch) * 25.4)
#define INCH_TO_PIXELS(inch)	((inch) * (DPI))


void MY_PERSPECTIVE_TRANSFORM()
{
	// ����ͼ��(1200*1200)
	cv::Mat srcImg = cv::imread("D:\\work\\000002\\preview.bmp");
	if (srcImg.empty())
		return;

	// �ĸ����۰б������
	std::vector<cv::Point2f> marks;
	marks.push_back(cv::Point2f(INCH_TO_PIXELS(15.6), INCH_TO_PIXELS(0.37)));
	marks.push_back(cv::Point2f(INCH_TO_PIXELS(14.6), INCH_TO_PIXELS(13.6)));
	marks.push_back(cv::Point2f(INCH_TO_PIXELS(0.42), INCH_TO_PIXELS(13.6)));
	marks.push_back(cv::Point2f(INCH_TO_PIXELS(0.42), INCH_TO_PIXELS(0.37)));
	cout << "ͼֽ�������꣺" << endl;
	cout << marks << endl;

	// �趨Ŀ�İб������
	std::vector<cv::Point2f> msr_marks;
	msr_marks.push_back(cv::Point2f(INCH_TO_PIXELS(15.6), INCH_TO_PIXELS(0.37))); //����ƫ��
	msr_marks.push_back(cv::Point2f(INCH_TO_PIXELS(14.6-0.1), INCH_TO_PIXELS(13.6+0.2)));
	msr_marks.push_back(cv::Point2f(INCH_TO_PIXELS(0.42), INCH_TO_PIXELS(13.6)));
	msr_marks.push_back(cv::Point2f(INCH_TO_PIXELS(0.42+0.1), INCH_TO_PIXELS(0.37-0.2)));
	cout << "ͼֽʵ�����꣺" << endl;
	cout << msr_marks << endl;

	// ����ӳ�����
	cv::Mat transmtx = cv::getPerspectiveTransform(marks, msr_marks);
	cout << "�任����:" << endl;
	cout << transmtx << endl << endl;

	// ��ʼ��Ŀ��ͼ��
	Mat dstImg = Mat::zeros(srcImg.size(), srcImg.type());
	//cv::Mat dstImg = cv::Mat::zeros(19200, 16800, CV_8UC1);  //ԭͼ��С�����쳣
	//cv::Mat dstImg = cv::Mat::zeros(8000, 7000, CV_8UC1);

	// ����͸�ӱ任
	cv::warpPerspective(srcImg, dstImg, transmtx, dstImg.size());

	// ��ʾ���
	cv::imshow("image", dstImg);
	// ������
	imwrite("D:\\work\\000002\\out.bmp", dstImg);
	cv::waitKey();
}



void MY_TRANSFORM()
{
	std::vector<cv::Point2f> std_pts; // ��������������
	std_pts.push_back(cv::Point2f(MM_TO_PIXELS(30.1785), MM_TO_PIXELS(134.027))); //����
	std_pts.push_back(cv::Point2f(MM_TO_PIXELS(766.7785), MM_TO_PIXELS(134.027))); //����
	std_pts.push_back(cv::Point2f(MM_TO_PIXELS(30.1785), MM_TO_PIXELS(718.227))); //����
	std_pts.push_back(cv::Point2f(MM_TO_PIXELS(766.7785), MM_TO_PIXELS(718.227))); //����
	cout << "�������������꣺" << endl;
	cout << std_pts << endl;

	std::vector<cv::Point2f> msr_pts; // �������˶�ϵͳ�Ĳ�������
	msr_pts.push_back(cv::Point2f(MM_TO_PIXELS(30.1785), MM_TO_PIXELS(134.027))); //����
	msr_pts.push_back(cv::Point2f(MM_TO_PIXELS(766.7465), MM_TO_PIXELS(134.307))); //����
	msr_pts.push_back(cv::Point2f(MM_TO_PIXELS(30.2765), MM_TO_PIXELS(718.217))); //����
	msr_pts.push_back(cv::Point2f(MM_TO_PIXELS(766.8495), MM_TO_PIXELS(718.493))); //����
	cout << "�����߲������꣺" << endl;
	cout << msr_pts << endl;

	// ����ӳ�����
	cv::Mat transmtx = cv::getPerspectiveTransform(msr_pts, std_pts);

	cout << "�任����:" << endl;
	cout << transmtx << endl << endl;



	// �б���������
	double mark[4][2] = {
		{ INCH_TO_MM(2.324223), INCH_TO_MM(3.058959) },		//����-3
		{ INCH_TO_MM(19.103443), INCH_TO_MM(2.955259) },		//����-0
		{ INCH_TO_MM(2.418523), INCH_TO_MM(19.561306) },	//����-2
		{ INCH_TO_MM(19.197343), INCH_TO_MM(19.457905) }	//����-1
	};
	
	cv::Mat mMsr = cv::Mat(4, 2, CV_64FC1, mark); // �б�����˶�ϵͳ�Ĳ�������
	//cv::Mat mMsr;
	//fromVectorToMat(msr_pts, mMsr);
	cv::Mat mDst = cv::Mat::zeros(Size(2, 4), CV_64FC1); // �б��ֱ������ϵ����������

	try
	{
		cout << "�б��������꣨X,Y����ֱ��:" << endl;
		cout << cv::format(mMsr, Formatter::FMT_PYTHON) << endl;
		cout << "=>" << endl;

		// ����͸�ӱ任
		cv::warpPerspective(mMsr, mDst, transmtx, mDst.size());
		
		cout << "�б���������꣨X,Y��ֱ��:" << endl;
		cout << cv::format(mDst, Formatter::FMT_PYTHON)<< endl;
	}
	catch (Exception ex)
	{
		cout << "Any key for exception exit!" << endl;
	}

	system("pause");
}