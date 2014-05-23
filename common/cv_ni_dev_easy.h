/********************************************
** Author: tkorays
** CreateTime: 2014-5-10
** Description: 方便开发，自动包含常用头文件以及库
** Dependence: OpenCV以及OpenNI的路径
********************************************/

#ifndef _TK_CV_NI_DEV_EASY_H_
#define _TK_CV_NI_DEV_EASY_H_
#pragma once

#include "XtionDepthVideo.h"
#pragma comment(lib,"OpenNI.lib")

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\video\video.hpp>

#include "cv_lib.h"
#pragma comment(lib, cvLIB("core"))
#pragma comment(lib, cvLIB("imgproc"))
#pragma comment(lib, cvLIB("highgui"))
#pragma comment(lib, cvLIB("video"))

#endif // _TK_CV_NI_DEV_EASY_H_