#ifndef _TK_FRADAPTER_H_
#define _TK_FRADAPTER_H_
#pragma once

#include <opencv2/core/core.hpp>

// ÊÊÅäÆ÷µÄ½Ó¿Ú
class FrAdapter {
public:
	virtual void init() = 0;
	virtual bool train() = 0;
	virtual int pridect(cv::Mat img) = 0;
	virtual string getNameById(int id) = 0;
};

#endif // _TK_FRADAPTER_H_
