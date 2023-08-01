#pragma once
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
// 矩形框：x0，y0为左上角坐标，x1, y1为右下角坐标。
struct Boxes
{
	float x0;
	float y0;
	float x1;
	float y1;
};


// 输出矩形框，置信度，类别，像素分割图片。
//OCR和目标检测的预测结果包含输出矩形框，置信度，类别；
//像素分割预测结果包含输出矩形框，置信度，类别，像素分割图片；
struct DetectionResult
{
	Boxes box;
	float score;
	std::string label;
	int label_index;
	cv::Mat mask;
	int row_index;
	int col_index;
	int mask_width;
	int mask_height;
};


/**
* for c++  
*/

extern "C" __declspec(dllexport) int get_batch(const char* model_name);

extern "C" __declspec(dllexport) void load_modelBefor(const char* model_name, const char* model_path, int& status, const char* device_name = "cuda", const int device_index = 0);

extern "C" __declspec(dllexport) int load_model(const char* model_name, const char* model_path, const char* device_name = "cuda", const int device_index = 0);

extern "C" __declspec(dllexport) int predict_model(const char* model_name,
	const std::vector<cv::Mat>& mats, std::vector<std::vector<DetectionResult>>& out_results, float detect_thres = -1.0);

extern "C" __declspec(dllexport) int newPredict_modelVec(const char* model_name, uchar* ImgVec, int length, int row, int col, char* ret, float detect_thres = -1.0);

extern "C" __declspec(dllexport) void destroy_model(const char* model_name);


/*
* for c#
*/
//extern "C" __declspec(dllexport) int predict_model_sharp(const char* model_name,
//	const unsigned char* input, float* output, int mask_num, float detect_thres = -1.0);

//extern "C" __declspec(dllexport) const unsigned char* get_mask_sharp(const int index);