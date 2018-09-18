// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO:  在此处引用程序需要的其他头文件

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
