#ifndef _TK_IMGPROC_HELPER_IMPL_H_
#define _TK_IMGPROC_HELPER_IMPL_H_
#pragma once

#include "ImgProcHelper.h"

#include <opencv2/highgui/highgui.hpp>

ImgProcHelper::ImgProcHelper() {
	process = nullptr;
	processor = nullptr;
}

ImgProcHelper::ImgProcHelper(string filename) :ImgProcHelper() {
	fileName = filename;
}

void ImgProcHelper::setImage(string filename) {
	fileName = filename;
}

void ImgProcHelper::setWinName(string input, string output) {
	winNameIn = input;
	winNameOut = output;
}

void ImgProcHelper::setImgProcessor(void(*proc)(Mat& input_mat, Mat& output_mat)) {
	process = proc;
}

void ImgProcHelper::setImgProcessor(ImgProcessor* img_processor) {
	processor = img_processor;
}

int ImgProcHelper::run() {
	if (fileName.empty()) {
		return NO_INPUT_FILE;
	}
	if (winNameIn.empty() || winNameOut.empty()) {
		return WIN_NAME_EMPTY;
	}
	if (process == nullptr && processor == nullptr) {
		return NO_PROCESS_OR;
	}

	Mat img = imread(fileName);
	if (img.empty()) {
		return READ_FILE_FAILED;
	}

	Mat output;
	if (process!=nullptr) {
		process(img, output);
	} else {
		processor->process(img, output);
	}
	
	namedWindow(winNameIn);
	namedWindow(winNameOut);
	imshow(winNameIn, img);
	imshow(winNameOut, output);
	waitKey(0);
	return PROC_SUCCESS;
}

void ImgProcHelper::checkStatus(int status) {
	switch (status) {
	case NO_INPUT_FILE:
		cout << "No Input File..." << endl;
		break;
	case READ_FILE_FAILED:
		cout << "Read image file failed..." << endl;
		break;
	case WIN_NAME_EMPTY:
		cout << "Input or Output window name is empty..." << endl;
		break;
	case NO_PROCESS_OR:
		cout << "You did not set a process or processor..." << endl;
		break;
	case PROC_SUCCESS:
		cout << "OK..." << endl;
		break;
	default:
		break;
	}
}

#endif // _TK_IMGPROC_HELPER_IMPL_H_