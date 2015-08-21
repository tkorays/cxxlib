#ifndef _TK_FEATURE_TRACKER_H_
#define _TK_FEATURE_TRACKER_H_

#pragma once
#include "VideoProcessor.h"

class FeatureTracker : public FrameProcessor {
	cv::Mat gray; // ��ǰ�Ҷ�ͼƬ
	cv::Mat gray_prev; // ֮ǰ�ĻҶ�ͼƬ
	std::vector<cv::Point2f> points[2];
	std::vector<cv::Point2f> initial; // ׷�ٵ����ʼ����
	std::vector<cv::Point2f> features; // �������
	int max_count;  // ���������
	double qlevel; // ��������
	double minDist; // ������֮�����С����
	std::vector<uchar> status; // ׷�ٵ��״̬
	std::vector<float> err; // ����
public:
	FeatureTracker() :max_count(500), qlevel(0.01), minDist(10.0) {}
	void process(cv::Mat& frame, cv::Mat& output) {
		cv::cvtColor(frame, gray, CV_BGR2GRAY); // �Ҷȱ任
		frame.copyTo(output);
		// 1. �����µ�������
		if (addNewPoints()) {
			detectFeaturesPoints();
			points[0].insert(points[0].end(), features.begin(), features.end()); // ����������
			initial.insert(initial.end(), features.begin(), features.end());
		}
		// ������Ƶ���еĵ�һ֡
		if (gray_prev.empty()) {
			gray.copyTo(gray_prev);
		}
		// 2. ׷��
		// Calculates an optical flow for a sparse feature set using the iterative Lucas-Kanade method with pyramids.
		cv::calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);
		// �ܾ�һЩ��
		int k = 0;
		for (int i = 0; i < points[1].size(); i++) {
			if (acceptTrackedPoint(i)) {
				initial[k] = initial[i];
				points[1][k++] = points[1][i];
			}
		}
		points[1].resize(k);
		initial.resize(k);
		// 3. ������ܵ�����
		handleTrackedPoints(frame, output);
		// 4. ʱ������
		std::swap(points[1], points[0]);
		cv::swap(gray_prev, gray);
	}
	// ����Ƿ����µĵ����
	bool addNewPoints() {
		return points[0].size() <= 10;
	}
	void detectFeaturesPoints() {
		cv::goodFeaturesToTrack(gray, features, max_count, qlevel, minDist); // ��������
	}
	bool acceptTrackedPoint(int i) {
		return status[i] &&
			(abs(points[0][i].x - points[1][i].x) + abs(points[0][i].y - points[1][i].y)) > 2;
	}
	void handleTrackedPoints(cv::Mat& frame, cv::Mat& output) {
		for (int i = 0; i < points[1].size(); i++) {
			cv::line(output, initial[i], points[1][i], cv::Scalar(255, 255, 255));
			cv::circle(output, points[1][i], 3, cv::Scalar(255, 255, 255), -1);
		}
	}
};

#endif //_TK_FEATURE_TRACKER_H_