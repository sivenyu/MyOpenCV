#pragma once
#include "stdafx.h"

//б�ʼ���н�
//line_1_kΪһ��ֱ��б�ʣ�line_2_kΪ��һ��ֱ��б��
float get_lines_arctan(float line_1_k, float line_2_k)
{
	float tan_k = 0; //ֱ�߼н�����ֵ
	float lines_arctan;//ֱ��б�ʵķ�����ֵ
	tan_k = (line_2_k - line_1_k) / (1 + line_2_k*line_1_k); //��ֱ�߼нǵĹ�ʽ
	lines_arctan = atan(tan_k)* 180.0 / 3.1415926;	// ����ת�Ƕ�

	return lines_arctan;	
}

// �������������н�
// ��pt1Ϊ��׼
float getAngelOfTwoVector(Point2f &pt1, Point2f &pt2, Point2f &c)
{
	// ��������������б�ʽǣ�Ȼ�����
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

	cout << "theta: " << theta << "(��)"  << endl;
	system("pause");
}