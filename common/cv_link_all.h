#ifndef _TK_CV_LINK_ALL_H_
#define _TK_CV_LINK_ALL_H_
#pragma once

#include "cv_lib.h"

#ifdef _WIN32
#pragma comment(lib,cvLIB("core"))
#pragma comment(lib,cvLIB("highgui"))
#pragma comment(lib,cvLIB("imgproc"))
#pragma comment(lib,cvLIB("calib3d"))
#pragma comment(lib,cvLIB("contrib"))
#pragma comment(lib,cvLIB("features2d"))
#pragma comment(lib,cvLIB("objdetect"))
#pragma comment(lib,cvLIB("video"))
#pragma comment(lib,cvLIB("videostab"))
#pragma comment(lib,cvLIB("ml"))
#pragma comment(lib,cvLIB("legacy"))
#pragma comment(lib,cvLIB("flann"))
#pragma comment(lib,cvLIB("ts"))
#endif

#endif // _TK_CV_LINK_ALL_H_
