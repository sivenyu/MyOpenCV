#pragma once

#include "stdafx.h"



/**
 * 高斯消元法求解线性方程组
 *
 * @param A[][] - 增广矩阵
 * @param epu	- A的行数（方程数）
 * @param var	- A的列数减1（未知数个数）
 * @param ans	- 求解的变换矩阵
 */
void Gauss(double A[][9], int equ, int var, double* ans)
{ 
	int row, col;
	for (row = 0, col = 0; col<var&&row<equ; col++, row++)
	{
		// 枚举当前处理的行.
		// 找到该col列元素绝对值最大的那行与第row行交换.(为了在除法时减小误差)
		int max_r = row;
		for (int i = row + 1; i<equ; i++)
		{
			if ((1e-12)<fabs(A[i][col]) - fabs(A[max_r][col]))
			{
				max_r = i;
			}
		}
		if (max_r != row)
		{
			// 与第row行交换.
			for (int j = 0; j < var + 1; j++)
				swap(A[row][j], A[max_r][j]);
		}

		// 查找要删除的行
		for (int i = row + 1; i<equ; i++)
		{
			if (fabs(A[i][col])<(1e-12))
				continue;
			double tmp = -A[i][col] / A[row][col];
			for (int j = col; j<var + 1; j++)
			{
				A[i][j] += tmp*A[row][j];
			}
		}
	}

	// 回代求解（唯一解）
	for (int i = var - 1; i >= 0; i--)
	{
		double tmp = 0;
		for (int j = i + 1; j<var; j++)
		{
			tmp += A[i][j] * (*(ans + j));
		}
		ans[i] = (A[i][var] - tmp) / A[i][i];
	}
}

/* Calculates coefficients of perspective transformation
 * which maps (xi,yi) to (ui,vi), (i=1,2,3,4):
 *
 *      c00*xi + c01*yi + c02
 * ui = ---------------------
 *      c20*xi + c21*yi + c22
 *
 *      c10*xi + c11*yi + c12
 * vi = ---------------------
 *      c20*xi + c21*yi + c22
 *
 * Coefficients are calculated by solving linear system:
 * / x0 y0  1  0  0  0 -x0*u0 -y0*u0 \ /c00\ /u0\
 * | x1 y1  1  0  0  0 -x1*u1 -y1*u1 | |c01| |u1|
 * | x2 y2  1  0  0  0 -x2*u2 -y2*u2 | |c02| |u2|
 * | x3 y3  1  0  0  0 -x3*u3 -y3*u3 |.|c10|=|u3|,
 * |  0  0  0 x0 y0  1 -x0*v0 -y0*v0 | |c11| |v0|
 * |  0  0  0 x1 y1  1 -x1*v1 -y1*v1 | |c12| |v1|
 * |  0  0  0 x2 y2  1 -x2*v2 -y2*v2 | |c20| |v2|
 * \  0  0  0 x3 y3  1 -x3*v3 -y3*v3 / \c21/ \v3/
 *
 * where:
 *   cij - matrix coefficients, c22 = 1
 */
void my_getPerspectiveTransform(Point2f * src, Point2f * dst, double* ret)
{
	double x0 = src[0].x, x1 = src[1].x, x2 = src[3].x, x3 = src[2].x;
	double y0 = src[0].y, y1 = src[1].y, y2 = src[3].y, y3 = src[2].y;
	double u0 = dst[0].x, u1 = dst[1].x, u2 = dst[3].x, u3 = dst[2].x;
	double v0 = dst[0].y, v1 = dst[1].y, v2 = dst[3].y, v3 = dst[2].y;
	double A[8][9] = {
		{ x0, y0, 1, 0, 0, 0, -x0*u0, -y0*u0, u0 },
		{ x1, y1, 1, 0, 0, 0, -x1*u1, -y1*u1, u1 },
		{ x2, y2, 1, 0, 0, 0, -x2*u2, -y2*u2, u2 },
		{ x3, y3, 1, 0, 0, 0, -x3*u3, -y3*u3, u3 },
		{ 0, 0, 0, x0, y0, 1, -x0*v0, -y0*v0, v0 },
		{ 0, 0, 0, x1, y1, 1, -x1*v1, -y1*v1, v1 },
		{ 0, 0, 0, x2, y2, 1, -x2*v2, -y2*v2, v2 },
		{ 0, 0, 0, x3, y3, 1, -x3*v3, -y3*v3, v3 },
	};
	Gauss(A, 8, 8, ret);
	*(ret + 8) = 1;
}

/**
 * @param p   - 待变换的点坐标
 * @param mat - 变换矩阵
 */
Point2f my_Transform(Point2f p, double* mat)
{
	Point2f ret;
	double D = p.x*mat[6] + p.y*mat[7] + mat[8];
	ret.x = (p.x*mat[0] + p.y*mat[1] + mat[2]) / D;
	ret.y = (p.x*mat[3] + p.y*mat[4] + mat[5]) / D;
	return ret;
}

void MY_PERSPECTIVE_TRANSFORM()
{
	Point2f std_pts[4] = {
		cv::Point2f(30.1785, 134.027),
		cv::Point2f(766.7785, 134.027),
		cv::Point2f(30.1785, 718.227),
		cv::Point2f(766.7785, 718.227)
	};
	cout << "玻璃尺理论坐标：" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << std_pts[i].x << ", " << std_pts[i].y << endl;
	}

	Point2f msr_pts[4] = {
		cv::Point2f(30.1785, 134.027),
		cv::Point2f(766.7465, 134.307),
		cv::Point2f(30.2765, 718.217),
		cv::Point2f(766.8495, 718.493)
	};
	cout << "玻璃尺测量坐标：" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << msr_pts[i].x << ", " << msr_pts[i].y << endl;
	}

	// 计算映射矩阵
	double A[9] = { 0.0f };
	my_getPerspectiveTransform(std_pts, msr_pts, A);
	cout << "变换矩阵：" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << A[i * 3 + j] << ", ";
		}
		cout << endl;
	}

	// 靶标点测量坐标
	Point2f mark[4]= {
		cv::Point2f(INCH_TO_MM(2.324223), INCH_TO_MM(3.058959)),	//右下-3
		cv::Point2f(INCH_TO_MM(19.103443), INCH_TO_MM(2.955259)),	//左下-0
		cv::Point2f(INCH_TO_MM(2.418523), INCH_TO_MM(19.561306)),	//右上-2
		cv::Point2f(INCH_TO_MM(19.197343), INCH_TO_MM(19.457905))	//左上-1
	};

	// 导出靶标点理论坐标
	cout << endl << "靶标点变换：" << endl;
	Point2f new_mark[4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		new_mark[i] = my_Transform(mark[i], A);
		cout << "Mark[" << i << "]'s mark: [" << mark[i].x << ", " << mark[i].y << "] => ";
		cout << "[" << new_mark[i].x << ", " << new_mark[i].y <<  "]" << endl;
	}


	//验证
	my_getPerspectiveTransform(mark, new_mark, A);
	cout << endl << "验证变换矩阵：" << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << A[i * 3 + j] << ", ";
		}
		cout << endl;
	}

	system("pause");
}