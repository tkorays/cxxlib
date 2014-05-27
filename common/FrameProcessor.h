#ifndef _TK_FRAME_PROCESSOR_H_
#define _TK_FRAME_PROCESSOR_H_
#pragma once


#include <opencv2/core/core.hpp>


class FrameProcessor {
public:
	virtual void process(cv::Mat& input, cv::Mat& output) = 0;
};

#endif // _TK_FRAME_PROCESSOR_H_
