#pragma once
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"


// Bounding box
// (x0, y0) coordinates represent the upper left corner of the bounding box
// (x1, y1) coordinates represent the lower right corner of the bounding box
struct Boxes {
	float x0;
	float y0;
	float x1;
	float y1;
};


// Detection results
// For OCR and Object Detection tasks, results are bounding box (box), confidence level (score), 
//                                                 and category (label, label_index)
// For Pixel Segmentation task, results are bounding box (box), confidence level (score), category (label, label_index), 
//                                          and pixel segmentation image (mask, mask_width, mask_height)
struct DetectionResult {
	Boxes box;                   // Bounding box containing the detected object
	float score;                 // Score after predicting, ranging from 0 to 1
								 // The closer the score is to 1, the better the result is
	std::string label;           // The target's label name after predicting
	int label_index;             // Index of the label
	cv::Mat mask;                // Mask of the the detected object                         TODO: figure out what it is
	int row_index;               // Position of the the detected object, used for OCR sort  TODO: figure out what it is
	int col_index;               // Position of the the detected object, used for OCR sort  TODO: figure out what it is
	int mask_width;              // Width of the mask 										TODO: figure out what it is
	int mask_height;             // Height of the mask 										TODO: figure out what it is
};


// Functions from C++ SDK


// Get batch_size of the model
// Inputs: model_name:		Name of the model
// Modify: None
// Output: The number of samples selected for one training session.
//         It is given in the file model.conf, which is 1.
extern "C" __declspec(dllexport) int get_batch(const char* model_name);


// Load the model
// Inputs: model_name:		Name of the model
//		   model_path:   	File path which stores the model
// 		   device_name:  	Name of the device. "cuda" for GPU and "cpu" for CPU. Default: "cuda"
//		   device_index: 	Index of the device. Default: 0
// Modify: None
// Output: A status code indicating whether loading the model is successful or not.
//		   0 means success and non-zero values mean failure
//         TODO: add a link to status code explanation page
extern "C" __declspec(dllexport) int load_model(const char* model_name, const char* model_path, 
												const char* device_name = "cuda", const int device_index = 0);


// Use the model to predict and get results
// Inputs: model_name:		Name of the model
//         mats:		    An array of test images. Each image is read by OpenCV in the format of cv::Mat	
//         out_results:		An empty 2D vector which is used for storing detection results
//         detect_thres:	Threshold for detection. The default is -1.0, meaning using the default configuration.
// 							Here the default is 0.7.  TODO: ???
// Modify: out_results:		Store detection results in out_results if the model predicts successfully
// Output: A status code indicating whether the model predicts successfully or not.
//		   0 means success and non-zero values mean failure
//         TODO: add a link to status code explanation page
extern "C" __declspec(dllexport) int predict_model(const char* model_name, const std::vector<cv::Mat>& mats, 
												   std::vector<std::vector<DetectionResult>>& out_results, 
												   float detect_thres = -1.0);


// Release memory spaces (primarily for GPU) used by the model
// Inputs: model_name:		Name of the model
// Modify: None
// Output: None
extern "C" __declspec(dllexport) void destroy_model(const char* model_name);