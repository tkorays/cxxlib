#ifndef _TK_CVFRADAPTER_IMPL_H_
#define _TK_CVFRADAPTER_IMPL_H_
#pragma once

#include "CvFrAdapter.h"
#include <iostream>
using namespace std;

// CvFrAdapter的实现
CvFrAdapter::CvFrAdapter() {
	Fr = createEigenFaceRecognizer(20);
}
// TODO: 初始化
void CvFrAdapter::init() {
	// 初始化再做打算
}
bool CvFrAdapter::train() {
	if (face_storage_file.empty()) {
		return false;
	} // else face_storage_file not empty 
	fs.load(face_storage_file);
	vector<Face> allface = fs.getAllFaces();
	vector<Face>::iterator allface_it = allface.begin();
	vector<Mat> faces;
	vector<int> labels;
	while (allface_it != allface.end()) {
		vector<string>::iterator img_it = (*allface_it).images.begin();
		while (img_it != (*allface_it).images.end()) {
			Mat gray_img = imread((*img_it), CV_LOAD_IMAGE_GRAYSCALE);
			if (gray_img.empty()) {
				return false;
			}
			faces.push_back(gray_img);
			labels.push_back((*allface_it).getId());
			img_it++;
			
		}
		allface_it++;
	}
	Fr->train(faces, labels);
	return true;
}
int CvFrAdapter::pridect(Mat img) {
	return Fr->predict(img);
}
void CvFrAdapter::setFaceStorage(const string fn) {
	face_storage_file = fn;
}
void CvFrAdapter::loadTrainedFile(const string fn) {
	trained_file = fn;
}
void CvFrAdapter::save(const string fn) {
	Fr->save(fn);
}
void CvFrAdapter::load(const  string fn) {
	Fr->load(fn);
}
string CvFrAdapter::getNameById(int id) {
	return fs.getNameById(id);
}

#endif // _TK_CVFRADAPTER_IMPL_H_