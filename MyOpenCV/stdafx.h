// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

#ifdef _DEBUG
#pragma comment(lib, "opencv_core340d.lib")
#pragma comment(lib, "opencv_highgui340d.lib")
#pragma comment(lib,"opencv_imgproc340d.lib")      

#else
#pragma comment(lib, "opencv_core340.lib")
#pragma comment(lib, "opencv_highgui340.lib")
#pragma comment(lib,"opencv_imgproc340.lib")
#endif
