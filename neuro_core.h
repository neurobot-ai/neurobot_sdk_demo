#pragma once
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"

// Rectangular box.
// x0, y0 are the coordinates of the upper left  corner, 
// x1, y1 are the coordinates of the lower right corner.
struct Boxes
{
	float x0;
	float y0;
	float x1;
	float y1;
};



// Define the results.
// 
// For OCR and object Detection, results are rectangle box, confidence level,category.
// 
// For Pixel Segmentation, results are rectangle box, confidence level,category, pixel segmentation image.


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



//for C++ 


// Get batch_size of the model.
// 
// Parameters
//         model_name    model_name
//
// Returns 
//         batch_size of the model
// 
// 

extern "C" __declspec(dllexport) int get_batch(const char* model_name);


// Load the model.
// 
// Parameters
//         model_name    model_name
//         model_path    model_path
//         status        status after loading the model, and  zero is successful
//         device_index  the default is zero 
//
// 

extern "C" __declspec(dllexport) void load_model(const char* model_name, const char* model_path, int& status, const int device_index = 0);

// Use model to predict
// 
// Parameters
//         model_name    model_name
//         mats          the Mat data of the pictures
//         out_results   out_results
//         detect_thres  the threshold for detection
//
// Returns  
//                       zero is successful.
//					     
//         


extern "C" __declspec(dllexport) int predict_model(const char* model_name,
	const std::vector<cv::Mat>& mats, std::vector<std::vector<DetectionResult>>& out_results, float detect_thres = -1.0);


// Destroy the model
// 
// Parameters
//         model_name    model_name
//		
// 

extern "C" __declspec(dllexport) void destroy_model(const char* model_name);



// for C#

//extern "C" __declspec(dllexport) int predict_model_sharp(const char* model_name,
//	const unsigned char* input, float* output, int mask_num, float detect_thres = -1.0);

//extern "C" __declspec(dllexport) const unsigned char* get_mask_sharp(const int index);