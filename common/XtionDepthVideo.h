#ifndef _TK_XTION_DEPTH_VIDEO_H_
#define _TK_XTION_DEPTH_VIDEO_H_

#pragma once

#if _MSC_VER > 1600
	#define _MSC_VER 1500
#endif

#include <XnCppWrapper.h>
#include <string>
#include <iostream>

/* 
	��ȡ��ȴ���������
	ʹ�÷�����
	XtionDepthVideo xdp();
	xdp>>data; 
	dataΪ�Ѿ�������ڴ�ռ䣬��ȡ������Ϊ���ֽڵģ�������short*����
	�������ǿ��԰�����д��cv::Mat::data��
 */
class XtionDepthVideo {
private:
	xn::Context context;
	XnMapOutputMode mode;
	xn::DepthGenerator dpGen;
	xn::DepthMetaData dpData;
	void CheckStatus(XnStatus s, const std::string msg) {
		if (s!=XN_STATUS_OK) {
			std::cout << msg << ":" << xnGetStatusString(s) << std::endl;
		}
	}
	XnStatus xn_result;
public:
	int width;
	int height;
	double FPS;
	XtionDepthVideo(int cols=640,int rows=480,int fps=30) {
		xn_result = context.Init();
		context.SetGlobalMirror(true);
		CheckStatus(xn_result, "Create Context Failed");

		width = cols;
		height = rows;
		FPS = fps;
		mode.nXRes = cols;
		mode.nYRes = rows;
		mode.nFPS = fps;

		xn_result = dpGen.Create(context);
		CheckStatus(xn_result, "Create DepthGenerator Failed");
		xn_result = dpGen.SetMapOutputMode(mode);
		CheckStatus(xn_result, "Set MapOutMode Failed");
		
		context.StartGeneratingAll();
	}
	/*
		��ȡ���ݵ��ڴ�ռ�
	*/
	XtionDepthVideo& operator>>(void* data) {
		xn_result = context.WaitOneUpdateAll(dpGen);
		CheckStatus(xn_result, "Updata Data Failed");

		dpGen.GetMetaData(dpData);
		memcpy(data, (void*)dpData.Data(), mode.nXRes*mode.nYRes * 2);
		return *this;
	}
	void release() {
		context.StopGeneratingAll();
		context.Release();
		dpGen.Release();
	}
	void start() {
		xn_result = context.StartGeneratingAll();
		CheckStatus(xn_result, "Already Started");
	}
	void stop() {
		xn_result = context.StopGeneratingAll();
		CheckStatus(xn_result, "Stop Failed");
	}
};



#endif // _TK_XTION_DEPTH_VIDEO_H_