// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;

// TODO:  �ڴ˴���������
#define DPI						(1200) // �ֱ���
#define MM_TO_PIXELS(mm)		((int)(((mm) * (DPI)) / 25.4))
#define MM_TO_INCH(mm)			((mm) / 25.4)
#define INCH_TO_MM(inch)		((inch) * 25.4)
#define INCH_TO_PIXELS(inch)	((inch) * (DPI))


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

#ifdef _DEBUG
#pragma comment(lib, "opencv_core341d.lib")
#pragma comment(lib, "opencv_highgui341d.lib")
#pragma comment(lib, "opencv_imgproc341d.lib")      
#pragma comment(lib, "opencv_imgcodecs341d.lib")
#else
#pragma comment(lib, "opencv_core341.lib")
#pragma comment(lib, "opencv_highgui341.lib")
#pragma comment(lib, "opencv_imgproc341.lib")
#pragma comment(lib, "opencv_imgcodecs340.lib")
#endif
