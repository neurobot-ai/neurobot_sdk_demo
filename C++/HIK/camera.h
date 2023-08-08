#ifndef __MYCAMERA_H_
#define __MYCAMERA_H_

#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include <map>
#include <opencv2/opencv.hpp>
#include <set>
#include <stdio.h>
#include <conio.h>
#include <queue>

//STEP:表示单步运行
//SERIES:表示连续运行需要外部触发
#define STOP 0
#define STEP 1
#define SERIES 2

#define HARD_TRIGGER 0
#define SOFTER_TRIGGER 1

#define OK 100
#define SCAN_ERROR 101
#define BIND_ERROR 102
#define OPEN_ERROR 103
#define GET_PACKET_FAIL 104
#define SET_PACKET_FAIL 105
#define SET_TRIGGER_FAIL 106
#define START_GRAB_FAIL 107
#define GET_IMAGEDATA_FAIL 108
#define FREE_IMAGEBUFFER_FAIL 109
#define CHOICE_DEVICE_TYPE_ERROR 110
#define OPEN_TRIGGER_FAIL 111
#define CLOSE_TRIGGER_FAIL 112
#define REGISTER_CALLBACK_FAIL 113
#define INPUT_MODE_ERROR 114
#define IMAGE_DATA_ERROR 115
#define CONVERT_PIXEL_FAIL 116
#define STOP_GRAB_ERROR 117
#define UNREGISTER_CALLBACK_ERROR 118
#define CLOSE_DEVICE_ERROR 119
#define DESTROY_HANDLE_ERROR 120
#define DEVICE_LIST_EMPTY 121

#define BASLER_STEP_ERROR 200;

//void __stdcall callBack(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);



class Camera {
public:
	virtual int scanDevice() = 0;
	virtual int bind(std::string macAddress) = 0;
	virtual int initGrab(int mode) = 0;
	virtual int startGrab(int mode, int triggerMode) = 0;
	virtual int stopGrab() = 0;
	virtual int close() = 0;
	virtual int destroy() = 0;
	virtual void softTrigger() = 0;
	static std::queue<cv::Mat> imageQ;
	virtual ~Camera() { std::cout << "~Camera" << std::endl; };
};





#endif
