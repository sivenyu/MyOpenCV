// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
using namespace std;

// TODO:  在此处定义宏变量
#define DPI						(1200) // 分辨率
#define MM_TO_PIXELS(mm)		((int)(((mm) * (DPI)) / 25.4))
#define MM_TO_INCH(mm)			((mm) / 25.4)
#define INCH_TO_MM(inch)		((inch) * 25.4)
#define INCH_TO_PIXELS(inch)	((inch) * (DPI))


// TODO:  在此处引用程序需要的其他头文件
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
