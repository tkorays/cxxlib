#ifndef _TK_FACERECOG_H_
#define _TK_FACERECOG_H_
#pragma once
#include <string>
using namespace std;


#include <opencv2/core/core.hpp>
using namespace cv;
#include "FrAdapter.h"


class FaceRecog {
private:
	FrAdapter* Fr;
public:
	FaceRecog();
	void setFrClass(FrAdapter* fr);
	bool train();
	int pridect(cv::Mat img);
	string getNameById(int id);
};

#include "FaceRecog_impl.h"

#endif // _TK_FACERECOG_H_
