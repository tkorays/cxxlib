#ifndef _TK_FEATURE_TRACKER_H_
#define _TK_FEATURE_TRACKER_H_

#pragma once
#include "VideoProcessor.h"

class FeatureTracker : public FrameProcessor {
	cv::Mat gray; // 当前灰度图片
	cv::Mat gray_prev; // 之前的灰度图片
	std::vector<cv::Point2f> points[2];
	std::vector<cv::Point2f> initial; // 追踪点的起始坐标
	std::vector<cv::Point2f> features; // 检测特征
	int max_count;  // 最大检测特征
	double qlevel; // 特征质量
	double minDist; // 两个点之间的最小距离
	std::vector<uchar> status; // 追踪点的状态
	std::vector<float> err; // 错误
public:
	FeatureTracker() :max_count(500), qlevel(0.01), minDist(10.0) {}
	void process(cv::Mat& frame, cv::Mat& output) {
		cv::cvtColor(frame, gray, CV_BGR2GRAY); // 灰度变换
		frame.copyTo(output);
		// 1. 加入新的特征点
		if (addNewPoints()) {
			detectFeaturesPoints();
			points[0].insert(points[0].end(), features.begin(), features.end()); // 加入特征点
			initial.insert(initial.end(), features.begin(), features.end());
		}
		// 对于视频序列的第一帧
		if (gray_prev.empty()) {
			gray.copyTo(gray_prev);
		}
		// 2. 追踪
		// Calculates an optical flow for a sparse feature set using the iterative Lucas-Kanade method with pyramids.
		cv::calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);
		// 拒绝一些点
		int k = 0;
		for (int i = 0; i < points[1].size(); i++) {
			if (acceptTrackedPoint(i)) {
				initial[k] = initial[i];
				points[1][k++] = points[1][i];
			}
		}
		points[1].resize(k);
		initial.resize(k);
		// 3. 处理接受的数据
		handleTrackedPoints(frame, output);
		// 4. 时间推移
		std::swap(points[1], points[0]);
		cv::swap(gray_prev, gray);
	}
	// 检测是否有新的点加入
	bool addNewPoints() {
		return points[0].size() <= 10;
	}
	void detectFeaturesPoints() {
		cv::goodFeaturesToTrack(gray, features, max_count, qlevel, minDist); // 跟踪特征
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