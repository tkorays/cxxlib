#ifndef _TK_VIDEO_PROCESSOR_H_
#define _TK_VIDEO_PROCESSOR_H_

#pragma once

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\video\video.hpp>

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "FrameProcessor.h"


class VideoProcessor {
private:
	cv::VideoCapture capture;
	void(*process)(cv::Mat&, cv::Mat&); // callback function
	bool callIt; // callback�Ƿ������?
	std::string winNameIn;
	std::string winNameOut;
	int delay;
	long fnumber;
	long frameToStop;
	bool stop;
	FrameProcessor* frameProcessor;

	std::vector<std::string> images;
	std::vector<std::string>::const_iterator itrImg;

	// ������Ƶ
	cv::VideoWriter writer;
	std::string outputFile;
	int currentIndex;
	int digits;
	std::string extension;


public:
	VideoProcessor() :callIt(true), delay(0), fnumber(0), stop(0), frameToStop(-1) {}

	// ���ûص�����
	void setFrameProcessor(void(*frameProcessorCallback)(cv::Mat&, cv::Mat&)) {
		frameProcessor = 0;
		process = frameProcessorCallback;
		callProcess();
	}
	void setFrameProcessor(FrameProcessor* fpPtr) {
		process = 0;
		frameProcessor = fpPtr;
		callProcess();
	}

	// ����������Ƶ
	bool setInput(std::string filename) {
		fnumber = 0;
		capture.release();
		images.clear();
		return capture.open(filename);
	}
	bool setInput(const std::vector<std::string>& imgs) {
		fnumber = 0;
		capture.release();
		images = imgs;
		return true;
	}
	bool setInput(const int v) {
		return true;
	}
	// ���������Ƶ
	bool setOutput(const std::string &filename, int codec = 0, double framerate = 0.0, bool isColor = true) {
		outputFile = filename;
		extension.clear();
		if (framerate==0.0) {
			framerate = getFrameRate();
		}
		char c[4];
		if (codec==0) {
			codec = getCodec(c);
		}
		return writer.open(outputFile, codec, framerate, getFraeSize(), isColor);
	}
	bool setOutput(const std::string& filename,const std::string& ext,int numberOfDigits=3,int startIndex=0) {
		if (numberOfDigits<0) {
			return false;
		}
		outputFile = filename;
		extension = ext;
		digits = numberOfDigits;
		currentIndex = startIndex;
		return true;
	}

	// ������ʾ
	void displayInput(std::string wn) {
		winNameIn = wn;
		cv::namedWindow(winNameIn);
	}
	void displayOutput(std::string wn) {
		winNameOut = wn;
		cv::namedWindow(winNameOut);
	}
	void dontDisplay() {
		cv::destroyWindow(winNameIn);
		cv::destroyWindow(winNameOut);
		winNameIn.clear();
		winNameOut.clear();
	}
	long getFrameRate() {
		return capture.get(CV_CAP_PROP_FPS);
	}
	cv::Size getFraeSize() {
		return cv::Size(capture.get(CV_CAP_PROP_FRAME_HEIGHT), capture.get(CV_CAP_PROP_FRAME_WIDTH));
	}

	// ������Ƶ����
	void run() {
		cv::Mat frame;
		cv::Mat output;
		if (!isOpened()) {
			return; // ���capture�Ƿ��
		}
		stop = false; // ����
		while (!isStopped()) {
			if (!readNextFrame(frame)) {
				break; // ��ȡ��һ֡ͼƬ�Ƿ����
			}
			if (winNameIn.length()!=0) {
				cv::imshow(winNameIn, frame); // ��ʾ��ȡ����Ƶ
			}
			// �Ƿ���ûص�����
			if (callIt) {
				// ѡ����ʵķ�������ֱ��process������FrameProcessor
				// ��ͬʱ�����ˣ�����ѡ��process����
				if (process) {
					process(frame, output);
				} else if (frameProcessor) {
					frameProcessor->process(frame, output);
				}
				fnumber++;// ����֡��+1
			} else {
				output = frame; // ���=����
			}
			if (outputFile.length()!=0) {
				writeNextFrame(output);
			}
			if (winNameOut.length()!=0) {
				cv::imshow(winNameOut, output);
			}
			// ����ֹͣ
			if (delay>=0 && cv::waitKey(delay)>=0) {
				stopIt();
			}
			if (frameToStop>=0 && getFrameNumber()== frameToStop) {
				stopIt();
			}
		}
	}
	void setDelay(int d) {
		delay = d;
	}
	void stopAtFrameNo(long f) {
		frameToStop = f;
	}
	long getFrameNumber() {
		long fnum = static_cast<long>(capture.get(CV_CAP_PROP_POS_FRAMES));
		return fnum;
	}
	
	bool isStopped() {
		return stop;
	}
	bool isOpened() {
		return capture.isOpened() || !images.empty();
	}
	int getCodec(char codec[4]) {
		if (images.size()!=0) {
			return -1;
		}
		union {
			int value;
			char code[4];
		}returned;
		returned.value = static_cast<int>(capture.get(CV_CAP_PROP_FOURCC));
		codec[0] = returned.code[0];
		codec[1] = returned.code[1];
		codec[2] = returned.code[2];
		codec[3] = returned.code[3];
		return returned.value;
	}
private:
	void callProcess() {
		callIt = true;
	}
	void dontCallProcess() {
		callIt = false;
	}
	void stopIt() {
		stop = true;
	}
	bool readNextFrame(cv::Mat& f) {
		if (images.size()==0) {
			return capture.read(f);
		} else {
			// ��ȡͼƬ������ͼƬ���в�Ϊ��
			if (itrImg!=images.end()) {
				f = cv::imread(*itrImg);
				itrImg++;
				return f.data != 0;
			} else {
				return false;
			}
		}
	}
	void writeNextFrame(cv::Mat& f) {
		// �����׺�����ȴ���0����д��ͼƬ�ļ������д����Ƶ��
		if (extension.length()) {
			std::stringstream ss;
			ss << outputFile << std::setfill('0')
				<< std::setw(digits)
				<< currentIndex++ << extension;
			cv::imwrite(ss.str(), f);
		} else {
			writer.write(f);
		}
	}
};




#endif // _TK_VIDEO_PROCESSOR_H_
