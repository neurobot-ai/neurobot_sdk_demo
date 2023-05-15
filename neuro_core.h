#pragma once
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"

// Rectangular box.
// 
// x0, y0 are the coordinates of the upper left  corner.
// 
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
// For OCR and Object Detection, results are rectangle box, confidence level,category.
// 
// For Pixel Segmentation, results are rectangle box, confidence level,category, pixel segmentation image.


struct DetectionResult
{
	Boxes box;                   // the result's box.
	float score;                 // the score after predictiing. The more getting closer to One, the better.
	std::string label;           // the target label name after predictting.
	int label_index;             // the label's index
	cv::Mat mask;                // the mask of the result.
	int row_index;               // the position of the result, used for OCR sort.
	int col_index;               //
	int mask_width;              //  the width of mask.
	int mask_height;             //  the height of mask.
};


//For C++ 


// Get batch_size of the model.
// 
// Parameters
//         model_name   [IN]        model_name
//
// Returns 
//         The number of samples selected for one training session.
//         It is given in the file model.conf, and is ONE. 
// 
// 

extern "C" __declspec(dllexport) int get_batch(const char* model_name);

// Load the model.
// 
// Parameters
//         model_name   [IN]      model_name
//         model_path   [IN]      model_path
//         status       [OUT]     status after loading the model, and ZERO is successful
//         device_index [IN]      the default is ZERO. you can also assign it by yourself.
//
// 

extern "C" __declspec(dllexport) void load_model(const char* model_name, const char* model_path, int& status, const int device_index = 0);

// Use model to predict
// 
// Parameters  3
//         model_name   [IN]      model_name
//         mats         [IN]      the Mat data of the pictures
//         out_results  [OUT]     output results
//         detect_thres [IN]      the threshold for detection. The default is -1.0, meaning using the default configuration.
//                                Here the default is 0.7.
// 
// Returns  
//         ZERO is successful.
//					     
//         

extern "C" __declspec(dllexport) int predict_model(const char* model_name,
	const std::vector<cv::Mat>& mats, std::vector<std::vector<DetectionResult>>& out_results, float detect_thres = -1.0);

// Release memory space used by the model, mostly is GPU space.
// 
// Parameters
//         model_name   [IN]        model_name
//		
// 

extern "C" __declspec(dllexport) void destroy_model(const char* model_name);



// for C#

//extern "C" __declspec(dllexport) int predict_model_sharp(const char* model_name,
//	const unsigned char* input, float* output, int mask_num, float detect_thres = -1.0);

//extern "C" __declspec(dllexport) const unsigned char* get_mask_sharp(const int index);