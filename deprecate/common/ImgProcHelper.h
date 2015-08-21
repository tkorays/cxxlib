#ifndef _TK_IMGPROC_HELPER_H_
#define _TK_IMGPROC_HELPER_H_
#pragma once

#include "ImgProcessor.h"
#include <iostream>
using namespace std;
using namespace cv;

class ImgProcHelper {
private:
	string fileName; // origin image file full path 
	string winNameIn; // input pic window name
	string winNameOut; // output pic window name
	void(*process)(Mat&, Mat&); // processing function
	ImgProcessor* processor;
public:
	ImgProcHelper();
	ImgProcHelper(string filename);
	void setImage(string filename); // set input image file
	void setWinName(string input, string output); // set input & output window name
	void setImgProcessor(void(*process)(Mat& input_mat,Mat& output_mat)); // set processor
	void setImgProcessor(ImgProcessor* img_proc); // set processor
	int run(); // run the processing and display result
	void checkStatus(int status);
	enum {
		NO_INPUT_FILE = 1,
		READ_FILE_FAILED = 2,
		WIN_NAME_EMPTY = 3,
		NO_PROCESS_OR = 4,
		PROC_SUCCESS = 5
	};
};
#include "ImgProcHelper_impl.h"
#endif // _TK_IMGPROC_HELPER_H_