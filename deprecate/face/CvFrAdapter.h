#ifndef _TK_CVFRADAPTER_H_
#define _TK_CVFRADAPTER_H_
#pragma once

#include "FrAdapter.h"
#include "FaceStorage.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>
using namespace cv;

// 使用opencv的人脸识别
class CvFrAdapter : public FrAdapter {
private:
	string face_storage_file; // 用于保存图片
	string trained_file; // 训练好的参数
	Ptr<FaceRecognizer> Fr;
	FaceStorage fs;
public:
	CvFrAdapter();
	void init();
	bool train();
	int pridect(Mat img);
	string getNameById(int id);

	void setFaceStorage(const string fn);
	void loadTrainedFile(const string fn);
	void save(const string fn);
	void load(const string fn);
};


#include "CvFrAdapter_impl.h"

#endif // _TK_CVFRADAPTER_H_
