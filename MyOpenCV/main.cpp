// MyOpenCV.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "TestMat.hpp"
#include "TestImage.hpp"
#include "TestAngle.hpp"

#include "TestPerspective.hpp"
#include "TestMyPerspective.hpp"

#include "TestThreshold.hpp"
#include "TestDilateErode.hpp"
#include "TestCanny.hpp"
#include "TestHoughLine.hpp"
#include "TestHoughCircle.hpp"
#include "TestMatchTemplate.hpp"

int main()
{
	//Basic...
	//TEST_MAT();
	//TEST_IMAGE();
	//TEST_ANGLE();

	//Transform...
	//TEST_PERSPECTIVE_TRANSFORM();
	//MY_PERSPECTIVE_TRANSFORM();

	//
	//TEST_THRESHOLD();
	//TEST_DILATION();
	TEST_CANNY();
	//TEST_HOUGH_LINE();
	//TEST_HOUGH_CIRCLE();
	//TEST_MATCH_TEMPLATE();

	destroyAllWindows();
    return 0;
}

